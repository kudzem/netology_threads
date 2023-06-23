#include <iostream>
#include <thread>
#include <chrono>
#include "thread_pool.h"

using namespace std::chrono_literals;

void test1() {
    std::cout << "test 1" << std::endl;
}

void test2() {
    std::cout << "test 2" << std::endl;
}

int main()
{
    thread_pool<std::function<void()>> workers;

    for (int i = 0; i < 10; ++i) {
        workers.submit(test1);
        workers.submit(test2);

        std::this_thread::sleep_for(1s);
    }

    workers.stop();

    return 0;
}