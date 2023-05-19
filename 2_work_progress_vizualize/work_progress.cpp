//Создать консольное приложение для имитации многопоточного расчёта.
//Количество потоков, длина расчёта должны быть заданы переменными.
//В консоль во время работы программы должно построчно для каждого потока выводиться :
//
//• Номер потока по порядку;
//• Идентификатор потока;
//• Заполняющийся индикатор(наподобие прогресс - бара) визуализирующий процесс «расчёта»;
//• По завершении работы каждого потока в соответствующей строке выводить суммарное время, затраченное при работке потока.


#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <mutex>


std::mutex progress_sync;
std::condition_variable cv;
bool progress_done = false;

const unsigned progress_bar_length = 50;
const unsigned max_task_complexity = 10;
const unsigned min_task_complexity = 1;
const unsigned max_time_for_one_task = 1000; 

struct Task {

    Task(unsigned id, unsigned complexity) : id(id), progress(0), complexity(complexity), duration(0) {}

    unsigned id;
    unsigned complexity;
    unsigned progress = 0;
    std::chrono::duration<double> duration;
    std::thread::id threadId;
};

void work(Task& task) {

    auto start = std::chrono::steady_clock::now();

    //std::cout << "Task " << task.id << " started" << std::endl;

    task.threadId = std::this_thread::get_id();

    while (true) {
        int time_to_make_a_progress = std::rand() % max_time_for_one_task;
        //std::cout << "Working on task " << task.id << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_make_a_progress));
        {
            std::lock_guard<std::mutex> lk(progress_sync);
            task.progress++;
            progress_done = true;
            cv.notify_one();

            if (task.progress == task.complexity) break;
            //std::cout << "Progress done in task " << task.id << std::endl;
        }
        
    };

    auto end = std::chrono::steady_clock::now();
    {
        std::lock_guard<std::mutex> lk(progress_sync);
        task.duration = end - start;
    }
}

std::string get_progress_bar(unsigned progress, unsigned limit) {
    return std::string(progress_bar_length*progress/limit, '=');
}

int main()
{
    const unsigned number_of_tasks = 5;

    std::srand(std::time(nullptr));
    std::vector<Task> tasks;
    for (int i = 0; i < number_of_tasks; ++i) 
    {
        unsigned task_complexity = std::rand() % (max_task_complexity + 1);
        task_complexity = std::max(task_complexity, min_task_complexity);
        tasks.emplace_back(i, task_complexity);
    }

    std::vector<std::thread> ts;
    for (auto& task : tasks)
    {
        std::thread t(work, std::ref(task));
        ts.push_back(std::move(t));
    }
    
    for (auto& t : ts) {
        t.detach();
    }

    while (true)
    {
        //std::cout << "Waiting for progress" << std::endl;
        std::unique_lock lk(progress_sync);        
        cv.wait(lk, [] { return progress_done; });
        //std::cout << "Progress done in some task " << std::endl;
        progress_done = false;

#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
        int total_work_left = 0;
        for (auto& task : tasks)
        {
            std::cout << "ThrIdx(" << task.id << "), ThrId(" << task.threadId << "), Progress(" << task.progress
                      << "/" << task.complexity << ") "
                      << std::setw(progress_bar_length)
                << std::setw(progress_bar_length) << std::left
                      << get_progress_bar(task.progress, task.complexity) 
                      << " Duration: " << task.duration.count() << "s\n"
                      << std::endl;
            total_work_left += (task.complexity - task.progress);
        }

        if (total_work_left == 0) break;
    }

    return 0;
}