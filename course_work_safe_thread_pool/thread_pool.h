#pragma once

#include "safe_queue.h"
#include <functional>
#include <thread>
#include <condition_variable>


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
template <class F>
class thread_pool {
    std::vector<std::thread> threads;
    safe_queue<F> work_todo;
    bool stopFlag = false;
    std::condition_variable cv;
    std::mutex mx;

public:
    thread_pool(unsigned pool_size) {
        for (unsigned i = 0; i < pool_size; ++i)
        {
            this->threads.emplace_back(std::thread(std::bind(&thread_pool::work, this)));
        }

        for (auto& t : threads) {
            t.detach();
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
            
            auto work_item = work_todo.pop();
            std::cout << "Work is taken by " << std::this_thread::get_id() << ": ";
            work_item();
            //std::this_thread::sleep_for(200ms);
        }
    }
    
    void submit(F f) {
        std::unique_lock lk(mx);
        work_todo.push(f);
        cv.notify_one();
        return;
    }
};

