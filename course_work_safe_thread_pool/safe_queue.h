#pragma once

#include <mutex>
#include <queue>
#include <optional>

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

    void pop() {
        std::lock_guard<std::mutex> lk(mx);
        if (q.empty()) return;
        q.pop();
    }

    T front() {
        std::lock_guard<std::mutex> lk(mx);
        return q.front();
    }

    bool empty() {
        std::lock_guard<std::mutex> lk(mx);
        return q.empty();
    }
};