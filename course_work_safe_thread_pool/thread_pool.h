#pragma once

#include "safe_queue.h"
#include <functional>
#include <thread>
#include <condition_variable>


//Минимально требуемые поля класса thread_pool :
//
//вектор потоков, инициализируемых в конструкторе класса и уничтожаемых в деструкторе;
//потокобезопасная очередь задач для хранения очереди работ;
//остальные поля на усмотрение разработчка.
//Минимально требуемые методы класса thread_pool :
//
//метод work – выбирает из очереди очередную задачи и исполняет ее. Данный метод передается конструктору потоков для исполнения.
//метод submit – помещает в очередь очередную задачу.
// В качестве принимаемого аргумента метод может принимать или объект шаблона std::function, или объект шаблона package_task.
//Остальные методы на усмотрение разработчика.

// F = std::function<void()>
template <class R, typename ... Args>
class thread_pool {
    std::vector<std::thread> threads;

    safe_queue<std::pair<std::function<R(Args...)>, std::tuple<Args...>>> work_todo;
    bool stopFlag = false;
    std::condition_variable cv;
    std::mutex mx;

public:

    thread_pool() : thread_pool(std::thread::hardware_concurrency()) {}
    thread_pool(unsigned pool_size) {

        for (unsigned i = 0; i < pool_size; ++i)
        {
            this->threads.emplace_back(std::thread(std::bind(&thread_pool::work, this)));
        }
    }

    virtual ~thread_pool()
    {
        stop();
        for (auto& t : this->threads) {
            t.join();
        }
    }


    bool isStopped() { return stopFlag; }

    void stop() {
        std::unique_lock lk(mx);
        stopFlag = true;
        cv.notify_all();
    }

    void work() {
        while (!stopFlag) {
            std::unique_lock lk(mx);
            cv.wait(lk, [this] () { return !this->work_todo.empty() || this->isStopped(); });
            
            if (this->isStopped()) break;

            auto [work_func, work_args] = work_todo.front();
            work_todo.pop();

            std::cout << "Work is taken by " << std::this_thread::get_id() << ": ";
            std::apply(work_func, work_args);
        }
    }
    
    void submit(std::function<R(Args...)> f, Args... args) {
        std::unique_lock lk(mx);
        work_todo.push(std::make_pair(f,std::tuple(args...)));
        cv.notify_one();
        return;
    }
};


