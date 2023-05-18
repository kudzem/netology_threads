#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std::chrono_literals;

/*
Написать программу для расчета суммы двух векторов.
Распараллелить данную программу на 2, 4, 8 и 16 потоков.
Определить какое количество потоков дает самый быстрый результат.
Сравнить результаты выполнения для массивов из 1000, 10 000, 100 000 и 1 000 000 элементов.
Время выполнения для каждого варианта свести в таблицу и вывести ее в консоль.
Первый запущенный поток должен вывести на экран доступное количество аппаратных ядер.
*/

void sum_vector_ranges(unsigned data_size,
    std::vector<int>::iterator start,
    std::vector<int>::iterator start2,
    std::vector<int>::iterator start3,
    unsigned thread_number)
{
    unsigned data_size_to_log = data_size;
    while (data_size--) {
        *start3 = *start + *start2;
        ++start++;
        ++start2++;
        ++start3++;
    }

    //std::cout << "Sum thread " << thread_number << " for data size " << data_size_to_log << " completed" << std::endl;
};

void sum_vectors(unsigned data_size,
                 const unsigned number_of_threads, 
                 std::vector<int>& v1, 
                 std::vector<int>& v2,
                 std::vector<int>& sum)
{
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < number_of_threads; ++i) {
        unsigned shift = data_size / number_of_threads * i;
        std::thread t(sum_vector_ranges,
                      data_size/ number_of_threads,
                      v1.begin() + shift,
                      v2.begin() + shift,
                      sum.begin() + shift,
                      i);
        threads.push_back(std::move(t));
    }

    for (auto& t : threads) {
        t.join();
    }
};

int main()
{
    unsigned number_of_experiments = 2;
    std::vector<int> v1, v2, sum;

    std::map<unsigned, std::map<unsigned, std::vector<std::chrono::duration<double>>>> measurements;
    std::vector<unsigned> number_of_threads_to_measure = { 1, 2, 4, 8, 16 };
    std::vector<unsigned> data_size_variants = { 1000, 10000, 100000, 1000000 };

    for (const auto& data_size : data_size_variants)
    {
        v1.resize(data_size);
        v2.resize(data_size);
        sum.resize(data_size);

        for (const auto& number_of_threads : number_of_threads_to_measure) 
        {
            for (int i = 0; i < number_of_experiments; ++i)
            {
                auto start = std::chrono::steady_clock::now();
                sum_vectors(data_size,
                    number_of_threads,
                    v1,
                    v2,
                    sum);

                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;

                std::cout << "Size = " << data_size << ", n of threads = " << number_of_threads
                          << ", elapsed time = " << elapsed_seconds.count() << "s\n";

                measurements[data_size][number_of_threads].push_back(elapsed_seconds);
            }
        }
    }

    std::cout << "V\\T";
    for (const auto& n_of_threads : number_of_threads_to_measure) {
        std::cout << "\t" << n_of_threads;
    }
    std::cout << std::endl;

    for (const auto& [data_size, data] : measurements) {
        std::cout << data_size;
        for (const auto& [n_of_threads, durations] : data) {
            int avg_duration = 0;
            for (std::chrono::duration<double> duration : durations) {
                avg_duration += std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
            }
            avg_duration /= number_of_experiments;
            std::cout << "\t" << avg_duration;
        }
        std::cout << std::endl;
    }

    std::cout << std::thread::hardware_concurrency() << " concurrent threads are supported.";

    return 0;
}