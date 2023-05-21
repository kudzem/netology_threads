#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <future>

//���������� ����������� �������� ���������� �������.
//���������� ������� ������� � ���, ��� � ��������������� ������ ��������� ���������� �������.
// ��������� � �������� ������ ����������� ������� ������������ �� i - � ����� ��������� ������(i = 1, 2, �, �), � ������� � i - �� ����� � �� ����� ����������.
// ��� ���� ��������, ��� ��� ������������� ��������(� ��� ����� ����������� ������� � ������� �����) ����������� �� ���������� ����������,
// ������� ����� ������, ������������ � ������ ����������� ��������� ������ ���� �� ���� ������� ������ �����������.
//
//����� ������������ �������� ����������� � ���� ����������� ������.
//��������� ������ ������������ � �������� ����� ����� ������ std::promise - std::future.



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