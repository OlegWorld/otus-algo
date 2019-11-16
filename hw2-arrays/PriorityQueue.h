#ifndef HW2_ARRAYS_PRIORITYQUEUE_H
#define HW2_ARRAYS_PRIORITYQUEUE_H

#include "SortedList.h"
#include "Queue.h"

template <class FirstT, class SecondT>
struct Pair {
    Pair(const FirstT& f, const SecondT& s) : first(f), second(s) { }

    FirstT first;
    SecondT second;
};

template <class FirstT, class SecondT>
bool operator<(const Pair<FirstT, SecondT>& lhs, const Pair<FirstT, SecondT>& rhs) {
    return lhs.first < rhs.first;
}

template <class FirstT, class SecondT>
bool operator==(const Pair<FirstT, SecondT>& lhs, const FirstT& rhs) {
    return lhs.first == rhs;
}

template <class PriorityT, class T>
class PriorityQueue {
public:
    PriorityQueue() = default;

    void enqueue(const PriorityT& priority, const T& element) {
        auto* target = _priorityQueue.find(priority);
        if (target)
            target->second.enqueue(element);
        else
        {
            auto q = Queue<T>();
            q.enqueue(element);
            Pair<PriorityT, Queue<T>> temp = Pair(priority, q);
            _priorityQueue.enqueue(temp);
        }
    }

    T dequeue() {
        auto& tempPair = _priorityQueue.top();
        auto tempEl = tempPair.second.dequeue();
        if (tempPair.second.empty()) {
            _priorityQueue.dequeue();
        }

        return tempEl;
    }

    bool empty() {
        return _priorityQueue.empty();
    }

private:
    SortedList<Pair<PriorityT, Queue<T>>> _priorityQueue;
};


#endif //HW2_ARRAYS_PRIORITYQUEUE_H
