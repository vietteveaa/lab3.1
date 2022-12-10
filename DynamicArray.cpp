#include "libs.h"
#include "DynamicArray.h"

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    this->array = new T[count];
    this->size = count; // размер с запасом
    this->capacity = count;
    memcpy(this->array, items, sizeof(T) * count);
}
template <class T>
DynamicArray<T>::DynamicArray(int size) {
    auto new_array = new T[size];
    this->array = new_array;
    this->capacity = size;
}
template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {
    auto* new_array = new T[dynamicArray.capacity];
    this->array = new_array;
    this->size = dynamicArray.size;
    this->capacity = dynamicArray.capacity;
    for (int i = 0; i < this->size; ++i) { this->array[i] = dynamicArray.array[i]; }
}
template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] array;
}

template <class T>
const T& DynamicArray<T>::get(int index) { return this->array[index]; } // const T& где нужна копия
template <class T>
int DynamicArray<T>::get_size() { return this->size; }
template <class T>
int DynamicArray<T>::get_capacity() { return this->capacity; }

template <class T>
void DynamicArray<T>::set(int index, const T& value) { this->array[index] = value; }
template <class T>
void DynamicArray<T>::resize(int new_size) {
    T* buffer_array = new T[this->size]; // убрать лишнее копирование
    memcpy (buffer_array, this->array, sizeof(T) * this->size);
    int old_size = this->size;
    delete[] this->array;
    this->array = new T[new_size];
    if (old_size < new_size) {
        this->size = old_size;
        this->capacity = new_size;
        for (int i = 0; i < old_size; ++i) { this->array[i] = buffer_array[i]; }
    }
    else {
        this->size = new_size;
        this->capacity = new_size;
        for (int i = 0; i < new_size; ++i) { this->array[i] = buffer_array[i]; }
    }
}
template <class T>
void DynamicArray<T>::set_size(int new_size) { this->size = new_size; }
template <class T>
T& DynamicArray<T>::operator[](int index) { return this->array[index]; }

    ///////////////////////////////////////ИТЕРАТОРЫ////////////////////////////////////////

template <class T>
DynamicArray<T>::ArrayIterator::ArrayIterator(T* elem_) : elem(elem_) {};
template <class T>
DynamicArray<T>::ArrayIterator::ArrayIterator() : elem(nullptr) {};
template <class T>
typename DynamicArray<T>::ArrayIterator& DynamicArray<T>::ArrayIterator::operator++() {
    elem = elem + 1;
    return *this;
}
template <class T>
typename DynamicArray<T>::ArrayIterator DynamicArray<T>::ArrayIterator::operator++(int) {
    ArrayIterator result = *this;
    ++(*this);
    return result;
}
template <class T>
typename DynamicArray<T>::ArrayIterator& DynamicArray<T>::ArrayIterator::operator--() {
    elem = elem - 1;
    return *this;
}
template <class T>
typename DynamicArray<T>::ArrayIterator DynamicArray<T>::ArrayIterator::operator--(int) {
    ArrayIterator result = *this;
    --(*this);
    return result;
}
template <class T>
bool DynamicArray<T>::ArrayIterator::operator==(const ArrayIterator& to_compare) { return this->elem==to_compare.elem; }
template <class T>
bool DynamicArray<T>::ArrayIterator::operator!=(const ArrayIterator& to_compare) { return this->elem!=to_compare.elem; }
template <class T>
bool DynamicArray<T>::ArrayIterator::operator<(const ArrayIterator& to_compare) { return this->elem<to_compare.elem; }
template <class T>
bool DynamicArray<T>::ArrayIterator::operator<=(const ArrayIterator& to_compare) { return this->elem<=to_compare.elem; }
template <class T>
const T& DynamicArray<T>::ArrayIterator::operator*() { return *elem; }
template <class T>
typename DynamicArray<T>::ArrayIterator DynamicArray<T>::begin() { return ArrayIterator(array + 0); }
template <class T>
typename DynamicArray<T>::ArrayIterator DynamicArray<T>::end() { return ArrayIterator(array + size - 1); }

    ///////////////////////////////////////////////СОРТИРОВКИ//////////////////////////////////////////////

template <class T>
typename DynamicArray<T>::ArrayIterator DynamicArray<T>::find_middle (ArrayIterator begin, ArrayIterator end) {
    if (begin == nullptr)
        return nullptr;
    ArrayIterator slow = begin, fast = begin;
    ++fast;
    if (begin == end)
        return end;
    while (fast != end) {
        ++fast;
        if (fast != end) {
            ++slow;
            ++fast;
        }
        else ++slow;
    }
    return slow;
}
template <class T>
int DynamicArray<T>::real_index (ArrayIterator elem) {
    int counter = 0;
    for (ArrayIterator ptr = array; ptr < end(); ++ptr) {
        if (ptr == elem)
            return counter - 1;
        ++counter;
    }
    return -1;
}

    //СЛИЯНИЕМ

template <class T>
void DynamicArray<T>::merge(ArrayIterator start, ArrayIterator& middle, ArrayIterator end, bool(*comparator)(const T&, const T&)) {
    ArrayIterator front_trail = middle;
    int real = real_index(middle);
    ++front_trail;
    ArrayIterator first_subarray_length = middle;
    ArrayIterator second_subarray_length = end;
    ArrayIterator first_subarray_index = start;
    ArrayIterator second_subarray_index = front_trail;
    int merged_array_index;
    T* merged_array = new T[real_index(end) + 1];
    while (first_subarray_index <= first_subarray_length && second_subarray_index <= second_subarray_length) {
        if (comparator(second_subarray_index.operator*(), first_subarray_index.operator*())) {
            *(merged_array + merged_array_index) = second_subarray_index.operator*();
            ++second_subarray_index;
        }
        else {
            *(merged_array + merged_array_index) = first_subarray_index.operator*();
            ++first_subarray_index;
        }
        ++merged_array_index;
    }
    while (first_subarray_index <= first_subarray_length) {
        *(merged_array + merged_array_index) = first_subarray_index.operator*();
        ++first_subarray_index;
        ++merged_array_index;
    }
    while (second_subarray_index <= second_subarray_length) {
        *(merged_array + merged_array_index) = second_subarray_index.operator*();
        ++second_subarray_index;
        ++merged_array_index;
    }
    int counter = 0;
    for (ArrayIterator ptr = start; ptr <= end; ++ptr) {
        *(ptr.elem) = *(merged_array + counter);
        ++counter;
    }
}
template <class T>
void DynamicArray<T>::merge_sort(ArrayIterator begin, ArrayIterator end, bool(*comparator)(const T&, const T&)) {
    if (begin <= end) {
        ArrayIterator middle = find_middle(begin, end);
        ArrayIterator temp = middle;
        ++temp;
        merge_sort(begin, middle, comparator);
        merge_sort(temp, end, comparator);
        merge(begin, middle, end, comparator);
    }
}
template <class T>
void DynamicArray<T>::merge_sort_(bool(*comparator)(const T&, const T&)) {
    merge_sort(begin(), end(), comparator);
}

    //БАББЛ

template <class T>
void DynamicArray<T>::bubble_sort(bool(*comparator)(const T&, const T&)) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j+ 1];
                array[j + 1] = temp;
            }
        }
    }
}

    //БЫСТРАЯ СОРТИРОВКА

template <class T>
typename DynamicArray<T>::ArrayIterator DynamicArray<T>::partition(ArrayIterator begin, ArrayIterator end, bool(*comparator)(const T&, const T&)) {
    T pivot = end.operator*();
    ArrayIterator i = begin;
    --i;
    while (begin < end) {
        if (comparator(begin.operator*(), pivot)) {
            ++i;
            T temp = i.operator*();
            *(i.elem) = begin.operator*();
            *(begin.elem) = temp;
        }
        ++begin;
    }
    ArrayIterator I = i;
    ++I;
    T temp = I.operator*();
    *(I.elem) = pivot;
    *(end.elem) = temp;
    return I;
}
template <class T>
void DynamicArray<T>::quick_sort(ArrayIterator start, ArrayIterator end, bool(*comparator)(const T&, const T&)) {
    if (start < end) {
        ArrayIterator pivot = partition(start, end, comparator);
        ArrayIterator left = pivot;
        ArrayIterator right = pivot;
        --left;
        ++right;
        quick_sort(start, left, comparator);
        quick_sort(right, end, comparator);
    }
}
template <class T>
void DynamicArray<T>::_quick_sort(bool(*comparator)(const T&, const T&)) {
    quick_sort(begin(), end(), comparator);
}