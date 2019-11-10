#ifndef HW2_ARRAYS_LIST_H
#define HW2_ARRAYS_LIST_H

template <class T> class List;
template <class T> class SortedList;

template <class T>
class Node {
public:
    friend class List<T>;
    friend class SortedList<T>;

    explicit Node(const T& element) : _element(element), _next(nullptr) { }

    Node(const T& element, Node* n) : _element(element), _next(n) { }

    ~Node() {
        if (_next)
            delete _next;
    }

    bool operator<(const Node& rhs) {
        return _element < rhs._element;
    }

private:
    T _element;
    Node* _next;
};


template <class T>
class List {
public:
    List() : _head(nullptr) { }

    ~List() { delete _head; }

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

    void add(const T& element) {
        auto* newNode = new Node<T>(element, _head);
        _head = newNode;
    }

    void add(const T& element, size_t index) {
        size_t counter = 0;
        auto node = _head;
        Node<T>* prev = nullptr;

        while (node) {
            if (counter == index) {
                auto newNode = new Node<T>(element, node);
                prev->_next = newNode;
                return;
            }

            if (node->_next) {
                prev = node;
                node = node->_next;
                counter++;
            } else {
                break;
            }
        }

        throw std::out_of_range("index out of range");
    }

    T remove(size_t index) {
        size_t counter = 0;
        auto node = _head;
        Node<T>* prev = nullptr;

        while (node) {
            if (counter == index) {
                if (prev) {
                    prev->_next = node->_next;
                } else {
                    _head = node->_next;
                }
                node->_next = nullptr;
                T temp = node->_element;
                delete node;
                return temp;
            }

            if (node->_next) {
                prev = node;
                node = node->_next;
                counter++;
            } else {
                break;
            }
        }

        throw std::out_of_range("index out of range");
    }

    T& operator[](size_t index) {
        size_t counter = 0;
        auto node = _head;

        while (node) {
            if (counter == index) {
                return node->_element;
            }

            if (node->_next) {
                node = node->_next;
                counter++;
            } else {
                break;
            }
        }

        throw std::out_of_range("index out of range");
    }

private:
    Node<T>* _head;
};


#endif //HW2_ARRAYS_LIST_H
