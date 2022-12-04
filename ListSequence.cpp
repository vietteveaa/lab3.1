#include "libs.h"
#include "ListSequence.h"

template <class T>
ListSequence<T>::ListSequence(T *items, int count) {
    auto *list = new LinkedList<T>(items, count);
    this->linkedlist = list;
}
template <class T>
ListSequence<T>::ListSequence() {
    auto* list = new LinkedList<T>();
    this->linkedlist - list;
}
template <class T>
ListSequence<T>::ListSequence(const LinkedList<T> &sequence) {
    auto *list = new LinkedList<T>(sequence);
    this->linkedlist - list;
}
template <class T>
const T& ListSequence<T>::get_first() { return this->linkedlist->get_first()->get_data(); }
template <class T>
const T& ListSequence<T>::get_last() { return this->linkedlist->get_last()->get_data(); }
template <class T>
const T& ListSequence<T>::get(int index) { return this->linkedlist->get(index)->get_data(); }
template <class T>
Sequence<T>* ListSequence<T>::get_subSequence(int startIndex, int endIndex) {
    auto* new_list_sequence = new ListSequence;
    new_list_sequence->linkedlist = this->linkedlist->get_sublist(startIndex, endIndex);
    return new_list_sequence;
}
template <class T>
int ListSequence<T>::get_length() { return this->linkedlist->get_length(); }
template <class T>
void ListSequence<T>::append(const T& item) { this->linkedlist->append(item); }
template <class T>
void ListSequence<T>::prepend(const T& item) { this->linkedlist->prepend(item); }
template <class T>
void ListSequence<T>::insert_at (const T& item, int index) { this->linkedlist->insert_at(item, index); }
template <class T>
Sequence<T>* ListSequence<T>::concat(Sequence<T>* list) {
    auto* new_list_sequence = new ListSequence;
    int count = this->linkedlist->get_length();
    for (int i = 0; i < count; ++i) { new_list_sequence->append(this->get(i)); }
    count = list->get_length();
    for (int i = 0; i < count; ++i) { new_list_sequence->append(list->get(i)); }
    return new_list_sequence;
}
template <class T>
void ListSequence<T>::merge_sort_(bool (*comparator)(const T &, const T &)) {
    this->linkedlist->merge_sort_(comparator);
}
template <class T>
void ListSequence<T>::bubble_sort() {
    this->linkedlist->bubble_sort();
}
template <class T>
void ListSequence<T>::_quick_sort(bool (*comparator)(const T &, const T &)) {
    this->linkedlist->_quick_sort(comparator);
}