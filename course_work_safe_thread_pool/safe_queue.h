#pragma once

#include <mutex>
#include <queue>

//2. Шаблонный класс safe_queue, представляющий собой реализацию очереди, безопасной относительно одновременного доступа из нескольких потоков.
//Минимально требуемые поля класса safe_queue :
//
//очередь std::queue для хранения задач;
//std::mutex для реализации блокировки;
//std::condtional_variables для уведомлений.
//Минимально требуемые методы класса safe_queue :
//
//метод push – записывает в начало очереди новую задачу.При этом захватывает мьютекс, а после окончания операции нотифицируется условная переменная.
//метод pop – находится в ожидании, пока не придут уведомление на условную переменную.При нотификации условной переменной данные считываются из очереди.
//Остальные методы на усмотрение разработчика.


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