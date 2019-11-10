#ifndef HW2_ARRAYS_SINGLEARRAY_H
#define HW2_ARRAYS_SINGLEARRAY_H


#include <algorithm>

template <class T>
class SingleArray {
public:
    SingleArray() : _array(nullptr), _size(0) { }

    ~SingleArray() { delete [] _array; }

    size_t size() { return _size; }

    void add(const T& item) {
        T* newArray = new T[_size + 1];
        std::copy(_array, _array + _size, newArray);
        delete [] _array;
        _array = newArray;
        _array[_size] = item;
        _size++;
    }

    void add(const T& item, size_t index) {
        if (index >= _size)
            throw std::out_of_range("index out of range");

        T* newArray = new T[_size + 1];
        std::copy(_array, _array + index, newArray);
        newArray[index] = item;
        std::copy(_array + index, _array + _size, newArray + index + 1);
        delete [] _array;
        _array = newArray;
        _size++;
    }

    T remove(size_t index) {
        T temp = operator[](index);
        T* newArray = new T[_size - 1];
        std::copy(_array, _array + index, newArray);
        std::copy(_array + index + 1, _array + _size, newArray + index);
        delete [] _array;
        _array = newArray;
        _size--;
        return temp;
    }

    T& operator[](size_t index) {
        if (index >= _size)
            throw std::out_of_range("index out of range");

        return _array[index];
    }

private:
    T* _array;
    size_t _size;
};


#endif //HW2_ARRAYS_SINGLEARRAY_H
