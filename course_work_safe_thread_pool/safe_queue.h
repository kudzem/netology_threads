#pragma once

#include <mutex>
#include <queue>

//2. ��������� ����� safe_queue, �������������� ����� ���������� �������, ���������� ������������ �������������� ������� �� ���������� �������.
//���������� ��������� ���� ������ safe_queue :
//
//������� std::queue ��� �������� �����;
//std::mutex ��� ���������� ����������;
//std::condtional_variables ��� �����������.
//���������� ��������� ������ ������ safe_queue :
//
//����� push � ���������� � ������ ������� ����� ������.��� ���� ����������� �������, � ����� ��������� �������� �������������� �������� ����������.
//����� pop � ��������� � ��������, ���� �� ������ ����������� �� �������� ����������.��� ����������� �������� ���������� ������ ����������� �� �������.
//��������� ������ �� ���������� ������������.


template <typename T>
class safe_queue {
private:
    std::queue<T> q;
    std::mutex mx;

public:

    void push(T f) {
        std::lock_guard<std::mutex> lk(mx);
        q.push(f);
        return;
    }

    T pop() {
        std::lock_guard<std::mutex> lk(mx);
        auto f = q.front();
        q.pop();
        return f;
    }

    bool empty() {
        std::lock_guard<std::mutex> lk(mx);
        return q.empty();
    }
};