#pragma once

#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items;
public:
    ArraySequence(T* items, int count);
    ArraySequence(int size);
    ArraySequence(const ArraySequence<T>& sequence);
    const T& get_first() override;
    const T& get_last() override;
    const T& get (int index) override;
    Sequence<T>* get_subSequence(int startIndex, int endIndex) override;
    int get_length() override;
    void append(const T& item) override;
    void prepend (const T& item) override;
    void insert_at (const T& item, int index) override;
    Sequence<T>* concat(Sequence<T>* list) override;
    void merge_sort_(bool(*comparator)(const T&, const T&)) override;
    void bubble_sort() override;
    void _quick_sort(bool(*comparator)(const T&, const T&)) override;
};