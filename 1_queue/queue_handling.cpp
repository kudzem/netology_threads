#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

unsigned queue_size = 0;

void produce(unsigned number_of_clients) {
    while (number_of_clients--) {
        ++queue_size;
        std::cout << "Queue increased to " << queue_size << std::endl;
        std::this_thread::sleep_for(1s);
    };

    std::cout << "Last client came" << std::endl;
}

void serve() {
    std::this_thread::sleep_for(2s);
    while (queue_size) {
        --queue_size;
        std::cout << "Queue decreased to " << queue_size << std::endl;
        std::this_thread::sleep_for(2s);
     };

    std::cout << "No more clients" << std::endl;
}

int main()
{
    std::cout << "How many clients we gonna serve today? ";
    unsigned number_of_clients = 0;
    std::cin >> number_of_clients;

    std::thread tp(produce, number_of_clients);
    std::thread tc(serve);

    tp.join();
    tc.join();

    return 0;
}