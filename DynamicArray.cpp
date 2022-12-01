#include <string.h>

template <class T>
bool comparator(const T& elem1, const T& elem2) { return (elem1 < elem2); }

template <class T>
class DynamicArray {
private:
    T* array;
    int size; // не приравнивать сразу к 0
    int capacity;
public:
    DynamicArray(T* items, int count) {
        this->array = new T[count];
        this->size = count; // размер с запасом
        this->capacity = count;
        memcpy(this->array, items, sizeof(T) * count);
    }

    DynamicArray(int size) {
        auto new_array = new T[size];
        this->array = new_array;
        this->capacity = size;
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) {
        auto* new_array = new T[dynamicArray.capacity];
        this->array = new_array;
        this->size = dynamicArray.size;
        this->capacity = dynamicArray.capacity;
        for (int i = 0; i < this->size; ++i) { this->array[i] = dynamicArray.array[i]; }
    }

public:
    const T& get(int index) { return this->array[index]; } // const T& где нужна копия
    int get_size() { return this->size; }
    int get_capacity() { return this->capacity; }

public:
    void set(int index, const T& value) { this->array[index] = value; }
    void resize(int new_size) {
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
    void set_size(int new_size) { this->size = new_size; }
    T& operator[](int index) { return this->array[index]; }

    ///////////////////////////////////////ИТЕРАТОРЫ////////////////////////////////////////

    class ArrayIterator {
    public:
        T* elem;
        ArrayIterator(T* elem_) : elem(elem_) {};
        ArrayIterator() : elem(nullptr) {};
        ArrayIterator& operator++() {
            elem = elem + 1;
            return *this;
        }
        ArrayIterator operator++(int) {
            ++(*this);
            return *this;
        }
        ArrayIterator& operator--() {
            elem = elem - 1;
            return *this;
        }
        ArrayIterator operator--(int) {
            --(*this);
            return *this;
        }
        bool operator==(const ArrayIterator& to_compare) { return this->elem==to_compare.elem; }
        bool operator!=(const ArrayIterator& to_compare) { return this->elem!=to_compare.elem; }
        bool operator<(const ArrayIterator& to_compare) { return this->elem<to_compare.elem; }
        bool operator<=(const ArrayIterator& to_compare) { return this->elem<=to_compare.elem; }
        const T& operator*() { return *elem; }
    };
    ArrayIterator begin() { return ArrayIterator(array + 0); }
    ArrayIterator end() { return ArrayIterator(array + size - 1); }

    ///////////////////////////////////////////////СОРТИРОВКИ//////////////////////////////////////////////

    ArrayIterator find_middle (ArrayIterator begin, ArrayIterator end) {
        if (begin == nullptr) { return nullptr; }
        if(begin == end) { return end; }
        ArrayIterator s = begin, f = begin;
        ++f;
        while (f != end) {
            ++f;
            if (f != end) {
                ++s;
                ++f;
            }
            else ++s;
        }
        return s;
    }
    int real_index (ArrayIterator elem) {
        int counter = 0;
        for (ArrayIterator ptr = array; ptr < end(); ++ptr) {
            if (ptr == elem) { return counter - 1; }
            ++counter;
        }
        return -1;
    }

    //СЛИЯНИЕМ
    void merge(ArrayIterator start, ArrayIterator middle, ArrayIterator end, bool(*comparator)(const T&, const T&)) {
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
                *(merged_array + merged_array_index) = first_subarray_index.operator*();
                ++first_subarray_index;
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
    void merge_sort(ArrayIterator begin, ArrayIterator end, bool(*comparator)(const T&, const T&)) {
        if (begin <= end) {
            ArrayIterator middle = find_middle(begin, end);
            ArrayIterator temp = middle;
            ++temp;
            merge_sort(begin, middle, comparator);
            merge_sort(temp, end, comparator);
            merge(begin, middle, end, comparator);
        }
    }
    void merge_sort_(bool(*comparator)(const T&, const T&)) {
        merge_sort(begin(), end(), comparator);
    }

    //БАББЛ
    void bubble_sort() {
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
    ArrayIterator partition(ArrayIterator l, ArrayIterator pivot, bool(*comparator)(const T&, const T&)) {
        T piv = pivot.operator*();
        ArrayIterator i = l->get_previous();
        while (l < pivot) {
            if (comparator(l.operator*(), piv)) {
                ++i;
                T temp = i.operator*();
                *(i.elem) = l.operator*();
                *(l.elem) = temp;
            }
            ++l;
        }
        ArrayIterator I = i;
        ++I;
        T temp = I.operator*();
        *(I.elem) = piv;
        *(pivot.elem) = temp;
        return I;
    }
    void quick_sort(ArrayIterator start, ArrayIterator end, bool(*comparator)(const T&, const T&)) {
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
    void _quick_sort(bool(*comparator)(const T&, const T&)) {
        quick_sort(begin(), end(), comparator);
    }
};