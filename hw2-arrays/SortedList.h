#ifndef HW2_ARRAYS_SORTEDLIST_H
#define HW2_ARRAYS_SORTEDLIST_H

#include "Stack.h"

template <class T>
class SortedList {
public:
    SortedList() : _head(nullptr) { }

    ~SortedList() { delete _head; }

    size_t size() {
        size_t counter = 0;
        auto node = _head;

        while (node) {
            counter++;

            if (node->_next) {
                node = node->_next;
            } else {
                break;
            }
        }

        return counter;
    }

    bool empty() {
        return _head == nullptr;
    }

    template <class U>
    T* find(const U& key) {
        auto node = _head;

        while (node) {
            if (node->_element == key) {
                return &(node->_element);
            }

            if (node->_next) {
                node = node->_next;
            } else {
                break;
            }
        }

        return nullptr;
    }

    T& top() {
        return _head->_element;
    }

    void enqueue(const T& element) {
        auto* newNode = new Node<T>(element);
        if (!_head) {
            _head = newNode;
            return;
        }

        auto node = _head;
        Node<T>* prev = nullptr;
        while (node) {
            if (*newNode < *node) {
                newNode->_next = node;
                if (prev) {
                    prev->_next = newNode;
                } else {
                    _head = newNode;
                }
                return;
            }

            if (node->_next) {
                prev = node;
                node = node->_next;
            } else {
                break;
            }
        }

        node->_next = newNode;
    }

    T dequeue() {
        T temp = _head->_element;
        auto node = _head;
        _head = node->_next;
        node->_next = nullptr;
        delete node;
        return temp;
    }

private:
    Node<T>* _head;
};


#endif //HW2_ARRAYS_SORTEDLIST_H
