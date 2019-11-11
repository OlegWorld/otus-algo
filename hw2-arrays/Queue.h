#ifndef HW2_ARRAYS_QUEUE_H
#define HW2_ARRAYS_QUEUE_H

#include "Stack.h"


template <class T>
class Queue {
public:
    Queue() : _head(nullptr), _tail(nullptr) { }

    size_t size() {
        if (empty())
            return 0;

        size_t counter = 0;
        auto node = _head;

        while (node != _tail) {
            node = node->_next;
            counter++;
        }

        return counter + 1;
    }

    void enqueue(const T& element) {
        if (!_head && !_tail) {
            _head = new Node<T>(element);
            _tail = _head;
        } else {
            auto node = _tail;
            _tail = new Node<T>(element);
            node->_next = _tail;
        }
    }

    T dequeue() {
        auto node = _head;

        if (_head == _tail) {
            _tail = nullptr;
        }

        _head = _head->_next;
        node->_next = nullptr;
        auto temp = node->_element;
        delete node;
        return temp;
    }

    bool empty() {
        return !_head && !_tail;
    }

private:
    Node<T>* _head;
    Node<T>* _tail;
};


#endif //HW2_ARRAYS_QUEUE_H
