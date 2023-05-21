#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <future>

//Необходимо реализовать алгоритм сортировки выбором.
//Сортировка выбором состоит в том, что в неупорядоченном списке находится наименьший элемент.
// Выбранный в исходном списке минимальный элемент записывается на i - е место исходного списка(i = 1, 2, …, п), а элемент с i - го места – на место выбранного.
// При этом очевидно, что уже упорядоченные элементы(а они будут расположены начиная с первого места) исключаются из дальнейшей сортировки,
// поэтому длина списка, участвующего в каждом последующем просмотре должна быть на один элемент меньше предыдущего.
//
//Поиск минимального элемента реализовать в виде асинхронной задачи.
//Результат должен возвращаться в основной поток через связку std::promise - std::future.



template<class It>
void my_min_element(It first, It last, std::promise<It>& p) {
    It min = std::min_element(first, last);
    p.set_value(min);
}

template<class It>
void selection_sort(It first, It last)
{
    for (It it = first; it != last; ++it) {
        std::promise<It> p;
        std::future<It> min_element_future = p.get_future();
        std::async(my_min_element<It>, it, last, std::move(p));
        It min_element = min_element_future.get();
        if (min_element != it) {
            std::swap(*min_element, *it);
        }
    }
}

int main()
{
    std::vector<int> data;
    std::srand(std::time(nullptr));
    for (int i = 0; i < 1000; ++i) {
        data.push_back(std::rand() % 100);
    }

    selection_sort(data.begin(), data.end());

    for_each(data.begin(), data.end(), [](int& value) { std::cout << value << " "; });
    return 0;
}