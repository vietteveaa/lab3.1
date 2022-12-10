#pragma once

template <class T>
class Sequence {
public:
    virtual const T& get_first() = 0;
    virtual const T& get_last() = 0;
    virtual const T& get(int index) = 0;
    virtual Sequence<T>* get_subSequence(int startIndex, int endIndex) = 0;
    virtual int get_length() = 0;
    virtual void append(const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void insert_at(const T& item, int index) = 0;
    virtual Sequence<T>* concat(Sequence<T>* list) = 0;
    virtual void merge_sort_(bool(*comparator)(const T&, const T&)) = 0;
    virtual void bubble_sort(bool(*comparator)(const T&, const T&)) = 0;
    virtual void _quick_sort(bool(*comparator)(const T&, const T&)) = 0;
};