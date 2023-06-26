#include <iostream>
#include <thread>
#include <chrono>
#include "thread_pool.h"

using namespace std::chrono_literals;

int sum(int a, int b=0) {
    int res = a + b;
    std::cout << "sum(" << a << "+" << b << ")" << "="  << res << std::endl;
    return res;
}

int mult(int a, int b=0) {
    int res = a * b;
    std::cout << "sum(" << a << "+" << b << ")" << "=" << res << std::endl;
    return res;
}

int do_nothing(void) {
    std::cout << "I do nothing" << std::endl;
    return 0;
}

int print_number(int a) {
    std::cout << "Number:" << a << std::endl;
    return 0;
}

int main()
{
    thread_pool<int, int, int> workers;
 
    for (int i = 0; i < 10; ++i) {
        auto res = workers.submit(sum, i, 10);
        auto res2 = workers.submit(mult, i, 10);

        int v1 = res.get();
        int v2 = res2.get();
        std::cout << "Got value" << v1 << std::endl;
        std::cout << "Got value" << v2 << std::endl;
        std::this_thread::sleep_for(10ms);
    }

    workers.stop();

    thread_pool<int, int> workers2;

    for (int i = 0; i < 10; ++i) {
        workers2.submit(print_number, i);
        workers2.submit(print_number, -i);
        workers2.submit(print_number, -2*i);
        workers2.submit(print_number, -3*i);

        std::this_thread::sleep_for(10ms);
    }

    workers.stop();

    thread_pool<int> workers3;

    for (int i = 0; i < 10; ++i) {
        auto res = workers3.submit(do_nothing);

        res.get();

        std::this_thread::sleep_for(10ms);
    }

    workers3.stop();

    return 0;
}