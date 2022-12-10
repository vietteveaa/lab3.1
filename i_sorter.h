#pragma once
#include "Sequence.h"

template <class T>
class ISorter {
public:
    void quick_sort(Sequence<T>* seq, bool(*comparator)(const T&, const T&));
    void bubble_sort(Sequence<T>*, bool(*comparator)(const T&, const T&));
    void merge_sort(Sequence<T>* seq, bool(*comparator)(const T&, const T&));

    void message_before(Sequence<T>* seq);
    void message_after(Sequence<T>* seq);
};