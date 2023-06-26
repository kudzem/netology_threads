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

void do_nothing(void) {
    std::cout << "I do nothing" << std::endl;
}

void print_number(int a) {
    std::cout << "Number:" << a << std::endl;
}

int main()
{
    thread_pool<int, int, int> workers;
 
    for (int i = 0; i < 10; ++i) {
        workers.submit(sum, i, 10);
        workers.submit(mult, i, 10);

        std::this_thread::sleep_for(10ms);
    }

    workers.stop();

    thread_pool<void, int> workers2;

    for (int i = 0; i < 10; ++i) {
        workers2.submit(print_number, i);
        workers2.submit(print_number, -i);
        workers2.submit(print_number, -2*i);
        workers2.submit(print_number, -3*i);

        std::this_thread::sleep_for(10ms);
    }

    workers.stop();

    thread_pool<void> workers3;

    for (int i = 0; i < 10; ++i) {
        workers3.submit(do_nothing);

        std::this_thread::sleep_for(10ms);
    }

    workers3.stop();

    return 0;
}