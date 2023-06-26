#pragma once

#include "safe_queue.h"
#include <functional>
#include <thread>
#include <future>
#include <condition_variable>
#include <list>


//���������� ��������� ���� ������ thread_pool :
//
//������ �������, ���������������� � ������������ ������ � ������������ � �����������;
//���������������� ������� ����� ��� �������� ������� �����;
//��������� ���� �� ���������� �����������.
//���������� ��������� ������ ������ thread_pool :
//
//����� work � �������� �� ������� ��������� ������ � ��������� ��. ������ ����� ���������� ������������ ������� ��� ����������.
//����� submit � �������� � ������� ��������� ������.
// � �������� ������������ ��������� ����� ����� ��������� ��� ������ ������� std::function, ��� ������ ������� package_task.
//��������� ������ �� ���������� ������������.

// F = std::function<void()>
template <class R, typename ... Args>
class thread_pool {
    std::vector<std::thread> threads;

    using work_item_t = std::pair<std::function<R(Args...)>, std::tuple<Args...>>;

    safe_queue<work_item_t> work_todo;
    std::list<std::promise<R>> promises;
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

            auto prms = std::move(promises.front());
            promises.pop_front();

            std::cout << "Work is taken by " << std::this_thread::get_id() << ": ";
            prms.set_value(std::apply(work_func, work_args));
        }
    }
    
    std::future<R> submit(std::function<R(Args...)> f, Args... args) {
        std::promise<R> prms;
        std::unique_lock lk(mx);

        std::future<R> ft = prms.get_future();
        auto work_item{ std::make_pair(f, std::make_tuple(args...)) };
        work_todo.push(work_item);
        promises.push_back(std::move(prms));
        cv.notify_one();
        return ft;
    }
};


