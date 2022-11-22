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

    //СЛИЯНИЕМ
    void merge(ArrayIterator start, ArrayIterator middle, ArrayIterator end, bool(*comparator)(const T&, const T&)) {

    }
    void merge_sort(ArrayIterator begin, ArrayIterator end, bool(*comparator)(const T&, const T&)) {

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
};