#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <future>

//����������� ������������ ������� ��������� for_each.
//������� ������ ��������� ��������� �� ������ � ����� ���������� � ������ �������������� �������.
//��� ���������� ���������� ���������� ��������� ��������� �� ��������� ������ � ��� ������� �����
// ��������� ��������� ������, ����������� �������������� ������� � ����� ����������.


template<class It, class Function>
//Function own_for_each_parallel(It first, It last, Function f)
void own_for_each_parallel(It first, It last, Function f)
{
    //std::cout << "Start " << *first << std::endl;
    size_t size = std::distance(first, last);
    if (std::distance(first, last) < 3) {
        std::cout << "Start*" << *first << std::endl;
        //return std::for_each(first, last, f);
        std::for_each(first, last, f);
        std::cout << "End*" << std::endl;
        return;
    }

    It mid = first + size/2;
    //std::future<void> res = std::async(std::launch::async, &own_for_each_parallel<It, Function>, first, mid, f);
    std::async(std::launch::async, &own_for_each_parallel<It, Function>, first, mid, f);
    own_for_each_parallel(mid, last, f);
    //res.get();
    //std::cout << "End" << std::endl;
    return;
}

int main()
{
    std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
    own_for_each_parallel(v.begin(), v.end(), [](int& value) { value *= value; });
    own_for_each_parallel(v.begin(), v.end(), [](int& value) { std::cout << value << " "; });

    return 0;
}