#include "libs.h"
#include "ArraySequence.h"

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count) {
    auto* dynamic_array = new DynamicArray<T> (items, count);
    this->items = dynamic_array;
}
template <class T>
ArraySequence<T>::ArraySequence(int size) {
    auto* array = new DynamicArray<T>(size);
    this->items = array;
}
/*template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& sequence) {
    auto* array = new DynamicArray<T>(sequence.items, sequence.get_length());
    this->items = array;
}*/
template <class T>
const T& ArraySequence<T>::get_first() { return this->items->get(0); }
template <class T>
const T& ArraySequence<T>::get_last() { return this->items->get(items->get_size() - 1); }
template <class T>
const T& ArraySequence<T>::get (int index) { return this->items->get(index); }
template <class T>
Sequence<T>* ArraySequence<T>::get_subSequence(int startIndex, int endIndex) {
    auto* new_sequence = new ArraySequence(endIndex - startIndex + 1);
    int sub_array_size = endIndex - startIndex + 1;
    auto* sub_array = new DynamicArray<T>(sub_array_size);
    for (int i = 0; i < sub_array_size; ++i) { sub_array->set(i, this->items->get(startIndex + i)); }
    new_sequence->items = sub_array;
    return new_sequence;
}
template <class T>
int ArraySequence<T>::get_length() { return this->items->get_size(); }
template <class T>
void ArraySequence<T>::append(const T& item) {
    this->insert_at(item, this->get_length());
}
template <class T>
void ArraySequence<T>::prepend (const T& item) {
    this->insert_at(item, 0);
}
template <class T>
void ArraySequence<T>::insert_at (const T& item, int index) {
    this->items->resize(this->items->get_size() + 1);
    this->items->set_size(this->items->get_size() + 1);
    for (int i = this->items->get_size() - 1; i > index; --i) {
        this->items->set(i, this->items->get(i - 1));
    }
    this->items->set(index, item);
}
template <class T>
Sequence<T>* ArraySequence<T>::concat(Sequence<T>* list) {
    auto* new_array_sequence = new ArraySequence(list->get_length());
    new_array_sequence->items = new DynamicArray<T>(this->items->get_size() + list->get_length());
    int count = this->items->get_size();
    for (int i = 0; i < count; ++i) {
        new_array_sequence->items->set(i, this->items->get(i));
        new_array_sequence->items->set_size(new_array_sequence->items->get_size() + 1);
    }
    count = list->get_length();
    for (int i = 0; i < count; ++i) {
        new_array_sequence->items->set(i + this->items->get_size(), list->get(i));
        new_array_sequence->items->set_size(new_array_sequence->items->get_size() + 1);
    }
    return new_array_sequence;
}
template <class T>
void ArraySequence<T>::merge_sort_(bool(*comparator)(const T&, const T&)) {
    this->items->merge_sort_(comparator);
}
template <class T>
void ArraySequence<T>::bubble_sort(bool(*comparator)(const T&, const T&)) {
    this->items->bubble_sort(comparator);
}
template <class T>
void ArraySequence<T>::_quick_sort(bool(*comparator)(const T&, const T&)) {
    this->items->_quick_sort(comparator);
}