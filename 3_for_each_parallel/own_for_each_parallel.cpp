#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <future>

//Реализовать параллельный вариант оператора for_each.
//Функция должна принимать итераторы на начало и конец контейнера и ссылку обрабатывающую функцию.
//При реализации необходимо рекурсивно разделить контейнер на несколько блоков и для каждого блока
// запустить отдельную задачу, применяющую обрабатывающую функцию к части контейнера.


template<class It, class Function>
Function own_for_each_parallel(It first, It last, Function f)
{
    size_t size = std::distance(first, last);
    if (std::distance(first, last) < 3) {
        return std::for_each(first, last, f);
    }

    It mid = first + size/2;
    std::future<Function> res = std::async(std::launch::async, &own_for_each_parallel<It, Function>, first, mid, f);
    own_for_each_parallel(mid, last, f);
    res.get();

    return f;
}

int main()
{
    std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
    own_for_each_parallel(v.begin(), v.end(), [](int& value) { value *= value; });

    for_each(v.begin(), v.end(), [](int& value) { std::cout << value << " "; });
    return 0;
}