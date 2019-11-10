#ifndef HW2_ARRAYS_FACTORARRAY_H
#define HW2_ARRAYS_FACTORARRAY_H


template <class T, size_t Factor>
class FactorArray {
public:
    FactorArray() : _array(nullptr), _size(0), _capacity(0) { }

    ~FactorArray() { delete [] _array; }

    size_t size() { return _size; }

    void add(const T& item) {
        if (!_array) {
            _array = new T[1];
            _capacity = 1;
        }

        if (_size == _capacity) {
            T* newArray = new T[_capacity * Factor];
            std::copy(_array, _array + _size, newArray);
            delete [] _array;
            _array = newArray;
            _capacity *= Factor;
        }

        _array[_size] = item;
        _size++;
    }

    void add(const T& item, size_t index) {
        if (index >= _size)
            throw std::out_of_range("index out of range");

        if (_size == _capacity) {
            T* newArray = new T[_capacity * Factor];
            std::copy(_array, _array + index, newArray);
            newArray[index] = item;
            std::copy(_array + index, _array + _size, newArray + index + 1);
            delete [] _array;
            _array = newArray;
            _capacity *= Factor;
            _size++;
        } else {
            std::copy_backward(_array + index, _array + _size, _array + _size + 1);
            _array[index] = item;
            _size++;
        }
    }

    T remove(size_t index) {
        T temp = operator[](index);
        std::copy(_array + index + 1, _array + _size, _array + index);
        _size--;
        return temp;
    }

    T& operator[](size_t index) {
        return _array[index];
    }

private:
    T* _array;
    size_t _size;
    size_t _capacity;
};


#endif //HW2_ARRAYS_FACTORARRAY_H
