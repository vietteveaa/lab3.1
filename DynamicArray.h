#pragma once

template <class T>
class DynamicArray {
private:
    T *array;
    int size; // не приравнивать сразу к 0
    int capacity;
public:
    DynamicArray(T *items, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& dynamicArray);

    const T &get(int index);
    int get_size();
    int get_capacity();

    void set(int index, const T &value);
    void resize(int new_size);
    void set_size(int new_size);
    T &operator[](int index);

    class ArrayIterator {
    public:
        T *elem;

        ArrayIterator(T *elem_);
        ArrayIterator();

        ArrayIterator &operator++();
        ArrayIterator operator++(int);
        ArrayIterator &operator--();
        ArrayIterator operator--(int);

        bool operator==(const ArrayIterator &to_compare);
        bool operator!=(const ArrayIterator &to_compare);
        bool operator<(const ArrayIterator &to_compare);
        bool operator<=(const ArrayIterator &to_compare);
        const T &operator*();
    };
    ArrayIterator begin();
    ArrayIterator end();

    ArrayIterator find_middle (ArrayIterator begin, ArrayIterator end);
    int real_index (ArrayIterator elem);

    void merge(ArrayIterator start, ArrayIterator middle, ArrayIterator end, bool(*comparator)(const T&, const T&));
    void merge_sort(ArrayIterator begin, ArrayIterator end, bool(*comparator)(const T&, const T&));
    void merge_sort_(bool(*comparator)(const T&, const T&));

    void bubble_sort();

    ArrayIterator partition(ArrayIterator l, ArrayIterator pivot, bool(*comparator)(const T&, const T&));
    void quick_sort(ArrayIterator start, ArrayIterator end, bool(*comparator)(const T&, const T&));
    void _quick_sort(bool(*comparator)(const T&, const T&));
};