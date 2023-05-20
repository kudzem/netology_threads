#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

using namespace std::chrono_literals;

struct TLV {
    std::string type;
    unsigned length;
    void* value;
};

class Data {
    std::mutex m;
    TLV data;
    friend void my_data_swap(Data& first, Data& second);
    friend void my_data_swap2(Data& first, Data& second);
    friend void my_data_swap3(Data& first, Data& second);
public:
    void set_tlv(std::string newtype, unsigned newlength) { data.type = newtype; data.length = newlength; }
    TLV get_tlv() const { return data; }
};

void my_data_swap(Data& first, Data& second) {
    std::lock(first.m, second.m);
    std::lock_guard<std::mutex> lk1(first.m, std::adopt_lock);
    std::lock_guard<std::mutex> lk2(second.m, std::adopt_lock);
    std::swap(first.data, second.data);
};

std::mutex print_mutex;
void print_lock_info(unsigned lock_id) {
    std::lock_guard<std::mutex> lk(print_mutex);
    std::cout << "Lock(" << lock_id << ")" << std::this_thread::get_id() << std::endl;
}

void my_data_swap2(Data& first, Data& second) {
    print_lock_info(1);
    std::unique_lock<std::mutex> lk1(first.m, std::defer_lock);
    print_lock_info(2);
    std::unique_lock<std::mutex> lk2(second.m, std::defer_lock);
    std::lock(first.m, second.m);
    std::swap(first.data, second.data);
};

void my_data_swap3(Data& first, Data& second) {
    std::scoped_lock L{ first.m, second.m };
    std::swap(first.data, second.data);
};

void infinite_swap(Data& one, Data& two, unsigned limit)
{
    while(limit) {
        my_data_swap2(one, two);
        //std::cout << "Swap is done" << std::endl;
        --limit;
    }
}

int main()
{
    Data one;
    one.set_tlv("blob", 10000);
    Data two;
    two.set_tlv("table", 423456);

    try {
        unsigned number_of_threads = 10;
        std::vector<std::thread> threads;
        for (unsigned i = 0; i < number_of_threads; ++i) {
            if (i % 2) {
                std::thread t(infinite_swap, std::ref(one), std::ref(two), 100);
                threads.push_back(std::move(t));
            }
            else {
                std::thread t(infinite_swap, std::ref(two), std::ref(one), 100);
                threads.push_back(std::move(t));
            }
        }

        for (auto& t : threads) {
            t.join();
        }
    }
    catch (std::exception& e) {
        std::cout << "Exception found " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Exception found " << std::endl;
    }



    std::cout << "Check values" << std::endl;
    std::cout << "First: " << one.get_tlv().type << "/" << one.get_tlv().length << std::endl;
    std::cout << "Second: " << two.get_tlv().type << "/" << two.get_tlv().length << std::endl;

    return 0;
}