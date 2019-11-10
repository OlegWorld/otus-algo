#ifndef HW2_ARRAYS_MATRIXARRAY_H
#define HW2_ARRAYS_MATRIXARRAY_H

#include "SingleArray.h"
#include "VectorArray.h"


template <class T, size_t Vector>
class MatrixArray {
public:
class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        iterator(SingleArray<VectorArray<T, Vector>>& array, size_t arrayIndex, size_t elementIndex)
            :_array(array), _arrayIndex(arrayIndex), _elementIndex(elementIndex) { }

        iterator& operator++() {
            if (++_elementIndex == Vector) {
                _elementIndex = 0;
                ++_arrayIndex;
            }

            return *this;
        }

        iterator& operator--() {
            if (--_elementIndex == -1) {
                _elementIndex = Vector - 1;
                --_arrayIndex;
            }

            return *this;
        }

        T& operator*() {
            return _array[_arrayIndex][_elementIndex];
        }

        T* operator->() {
            return &_array[_arrayIndex][_elementIndex];
        }

        bool operator==(const iterator& rhs) {
            return (&_array == &rhs._array && _elementIndex == rhs._elementIndex && _arrayIndex == rhs._arrayIndex);
        }

        bool operator!=(const iterator& rhs) {
            return !operator==(rhs);
        }

    private:
        SingleArray<VectorArray<T, Vector>>& _array;
        size_t _arrayIndex;
        size_t _elementIndex;
    };

public:
    explicit MatrixArray() : _size(0) { }

    size_t size() { return _size; }

    void add(const T& item) {
        if (_size == _array.size() * Vector) {
            _array.add(VectorArray<T, Vector>());
        }
        _array[_size / Vector].add(item);
        _size++;
    }

    void add(const T& item, size_t index) {
        if (index >= _size)
            throw std::out_of_range("index out of range");

        if (_size == _array.size() * Vector) {
            _array.add(VectorArray<T, Vector>());
            iterator beg(_array, index / Vector, index % Vector);
            iterator endOld(_array, _array.size() - 1, Vector - 1);
            iterator endNew(_array, _array.size(), 0);
            std::copy_backward(beg, endOld, endNew);

        } else {
            iterator beg(_array, index / Vector, index % Vector);
            iterator endOld(_array, _array.size() - 1, _size % Vector);
            iterator endNew(_array, _array.size() - 1, _size % Vector + 1);
            std::copy_backward(beg, endOld, endNew);
        }
        _array[index / Vector][index % Vector] = item;
        _size++;
    }

    T remove(size_t index) {
        T temp = operator[](index);

        if (_size % Vector == 1) {
            T last = _array[_array.size() - 1][0];
            _array.remove(_size / Vector);
            iterator begOld(_array, (index + 1) / Vector, (index + 1) % Vector);
            iterator begNew(_array, index / Vector, index % Vector);
            iterator end(_array, _array.size(), 0);
            std::copy(begOld, end, begNew);
            _array[_array.size() - 1][Vector - 1] = last;
        } else {
            iterator begOld(_array, (index + 1) / Vector, (index + 1) % Vector);
            iterator begNew(_array, index / Vector, index % Vector);
            iterator end(_array, _size / Vector, _size % Vector);
            std::copy(begOld, end, begNew);
        }
        _size--;

        return temp;
    }

    T& operator[](size_t index) {
        return _array[index / Vector][index % Vector];
    }

private:
    SingleArray<VectorArray<T, Vector>> _array;
    size_t _size;
};


#endif //HW2_ARRAYS_MATRIXARRAY_H
