#include "libs.h"
#include "LinkedList.h"

template <class T>
Node<T>::Node(): data(0), nextp(nullptr), previousp(nullptr) {}
template <class T>
Node<T>::~Node() {
    delete data;
    delete nextp;
    delete previousp;
}
template <class T>
const T& Node<T>::get_data() { return this->data; }
template <class T>
void Node<T>::set_data(T item) { this->data = item; }
template <class T>
Node<T>* Node<T>::get_next() { return this->nextp; }
template <class T>
void Node<T>::set_next(Node<T>* elem) { this->nextp = elem; }
template <class T>
Node<T>* Node<T>::get_previous() { return this->previousp; }
template <class T>
void Node<T>::set_previous(Node<T>* elem) { this->previousp = elem; };


template <class T>
LinkedList<T>::LinkedList(T* items, int count) {
    if (count == 0) {
        first = nullptr;
        last = nullptr;
        size = 0;
    }
    else {
        Node<T>* current = new Node<T>;
        first = current;
        size = 0;
        for (int i = 0; i < count; i++) {
            current->set_data(items[i]);
            last = current;
            if (i != count - 1) {
                Node<T>* new_node = new Node<T>;
                current->set_next(new_node);
                current = current->get_next();
            }
            size++;
        }
    }
}
template <class T>
LinkedList<T>::LinkedList() {
    first->set_data(0);
    last->set_data(0);
    first->set_previous(nullptr);
    first->set_next(last);
    last->set_previous(first);
    last->set_next(nullptr);
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& list) {//const
    auto* previous_elem = new Node<T>;
    Node<T>* elem = list.first;
    int count = list.get_length();
    this->first = previous_elem;
    previous_elem->set_data(elem->get_data());
    elem = elem->get_next;
    for (int i = 1; i < count; ++i) {
        auto* next_elem = new Node<T>;
        previous_elem->set_next(next_elem);
        next_elem->set_previous(previous_elem);
        next_elem->set_data(elem->get_next());
        previous_elem = previous_elem->get_next();
        elem = elem->get_next();
        this->last = next_elem;
        next_elem->set_next(nullptr);
    }
}
template<class T>
LinkedList<T>::~LinkedList() {
    Node<T>* curr = first;
    while (curr) {
        Node<T>* to_be_deleted;
        to_be_deleted = curr->get_next();
        delete to_be_deleted;
    }
}

template <class T>
int LinkedList<T>::get_length() const {
    return this->size;
}

template <class T>
Node<T>* LinkedList<T>::get_first() { return this->first; }
template <class T>
Node<T>* LinkedList<T>::get_last() { return this->last; }
template <class T>
Node<T>* LinkedList<T>::get(int index) {
    Node<T> *elem = this->first;
    for (int i = 0; i < index; ++i) { elem = elem->get_next(); }
    return elem;
}

template <class T>
LinkedList<T>* LinkedList<T>::get_sublist(int startIndex, int endIndex) {
    Node<T>* elem = this->first;
    T* items = new T [endIndex - startIndex + 1];
    for (int i = 0; i < startIndex; ++i) { elem = elem->get_next(); }
    for (int i = startIndex; i <= endIndex; ++i) {
        items[i-startIndex] = elem->get_data();
        elem = elem->get_next();
    }
    auto* sublist = new LinkedList(items, endIndex - startIndex +1);
    return sublist;
}

template <class T>
void LinkedList<T>::append(const T& item) {
    auto* new_last = new Node<T>;
    auto* old_last = new Node<T>;
    new_last->set_data(item);
    new_last->set_previous(this->last);
    new_last->set_next(nullptr);
    old_last = this->last;
    old_last->set_next(new_last);
    this->last = new_last;
    size++;
}
template <class T>
void LinkedList<T>::prepend(const T& item) {
    auto* new_first = new Node<T>;
    auto* old_first = new Node<T>;
    new_first->set_data(item);
    new_first->set_previous(nullptr);
    new_first->set_next(this->first);
    old_first = this->first;
    old_first->set_previous(new_first);
    this->first = new_first;
    size++;
}
template <class T>
void LinkedList<T>::insert_at(const T& item, int index) {
    Node<T>* next_elem = this->first;
    for (int i = 0; i < index; ++i) { next_elem = next_elem->get_next(); }
    Node<T>* previous_elem = next_elem->get_previous();
    auto* new_elem = new Node<T>;
    new_elem->set_data(item);
    new_elem->set_next(next_elem);
    new_elem->set_previous(previous_elem);
    next_elem->set_previous(new_elem);
    previous_elem->set_next(new_elem);
    size++;
}
template <class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>* list) {
    auto* new_list = new LinkedList(this);
    auto* elem = new Node<T>;
    elem = list->first;
    int count = list->get_length();
    for (int i = 0; i < count; ++i) {
        new_list->append(elem);
        elem = elem->get_next();
    }
    return new_list;
}

    /////////////////////////////////////////////////ИТЕРАТОРЫ///////////////////////////////////////////////

template <class T>
LinkedList<T>::Iterator::Iterator(Node<T>* new_elem) { this->elem = new_elem; }
template<class T>
LinkedList<T>::Iterator::Iterator() : elem(nullptr) {};

template <class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    elem = elem->get_next();
    return *this;
}
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
    ++(*this);
    return *this;
}
template <class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--() {
    elem = elem->get_previous();
    return *this;
}
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int) {
    --(*this);
    return *this;
}
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator+=(int count) {
    for (int i = 0; i < count; ++i)
        ++elem;
    return elem;
}
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator-=(int count) {
    for (int i = 0; i < count; ++i)
        --elem;
    return elem;
}
template<class T>
bool LinkedList<T>::Iterator::operator==(const Iterator& to_compare) { return this->elem==to_compare.elem; }
template<class T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& to_compare) { return this->elem!=to_compare.elem; }
template<class T>
const T& LinkedList<T>::Iterator::operator*() { return this->elem->get_data(); }

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return Iterator(first);
}
template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return Iterator(last);
}
    /////////////////////////////////////////////////СОРТИРОВКИ//////////////////////////////////////////////

//СЛИЯНИЕМ

template<class T>
void LinkedList<T>::split(Iterator head, Iterator& f, Iterator& s) {
    Iterator slow = head, fast = head;
    ++fast;
    while (fast != nullptr) {
        ++fast;
        if (fast != nullptr) {
            ++fast;
            ++slow;
        }
    }
    Iterator temp = slow;
    ++temp;
    f = head;
    s = temp;
    slow.elem->set_next(nullptr);
    temp.elem->set_previous(nullptr);
}
template<class T>
void LinkedList<T>::merge_sort(Iterator& head, bool(*comparator)(const T&, const T&)) {
    Iterator head_ = head;
    Iterator f, s;
    Iterator temp = head;
    ++temp;
    if ((head_ == nullptr) || (temp == nullptr)) return;
    split(head_, f, s);
    merge_sort(f, comparator);
    merge_sort(s, comparator);
    head = merge(f, s, comparator);
}
template<class T>
void LinkedList<T>::merge_sort_(bool(*comparator)(const T&, const T&)) {
    Iterator head_ = begin();
    merge_sort(head_, comparator);
    first = head_.elem;
}
template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::merge(Iterator f, Iterator s, bool(*comparator)(const T&, const T&)) {
    Iterator result = nullptr;
    if (s == nullptr) return f;
    if (f == nullptr) return s;
    if (comparator(s.operator*(), f.operator*())) {
        result = s;
        ++s;
    }
    else {
        result = f;
        ++f;
    }
    Iterator temp = result;
    while (f != nullptr && s != nullptr) {
        if (comparator(s.operator*(), f.operator*())) {
            temp.elem->set_next(s.elem);
            s.elem->set_previous(temp.elem);
            ++s;
        }
        else {
            temp.elem->set_next(f.elem);
            f.elem->set_previous(temp.elem);
            ++f;
        }
        ++temp;
    }
    if (f != nullptr) {
        temp.elem->set_next(f.elem);
        f.elem->set_previous(temp.elem);
    }
    if (s != nullptr) {
        temp.elem->set_next(s.elem);
        s.elem->set_previous(temp.elem);
    }
    return result;
}

//БАББЛ

template <class T>
Node<T>* swap (Node<T>* ptr1, Node<T>* ptr2) {
    Node<T>* tmp = ptr2->get_next();
    ptr2->get_next()->set_previous(ptr1);
    ptr2->set_next(ptr1);
    ptr2->set_previous(ptr1->get_previous());
    ptr1->get_previous()->set_next(ptr2);
    ptr1->set_next(tmp);
    ptr1->set_previous(ptr2);
    return ptr2;
}
template <class T>
void bubble_sort(Node<T>** first, int count) {
    Node<T>** link;
    int i, j, swapped;
    for (i = 0; i <= count; ++i) {
        link = first;
        swapped = 0;
        for (j = 0; j < count - i - 1; ++j) {
            Node<T>* ptr1 = *link;
            Node<T>* ptr2 = ptr1->get_next();
            if (ptr1->get_data() > ptr2->get_data()) {
                *link = swap(ptr1, ptr2);
                swapped = 1;
            }
            link = &(*link)->get_next();
        }
        if (swapped == 0)
            break;
    }
}

//БЫСТРАЯ СОРТИРОВКА

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::partition(Iterator head, Iterator tail, bool(*comparator)(const T&, const T&)) {
    Iterator pivot = head;
    Iterator curr = head;
    while ((curr != nullptr) && (curr != tail)) {
        if (comparator(curr.operator*(), tail.operator*())) {
            pivot = head;
            T temp = head.operator*();
            head.elem->set_data(curr.operator*());
            curr.elem->set_data(temp);
            ++head;
        }
        ++curr;
    }
    T temp = head.operator*();
    head.elem->set_data(tail.operator*());
    tail.elem->set_data(temp);
    return pivot;
}
template<class T>
void LinkedList<T>::quick_sort(Iterator head, Iterator tail, bool(*comparator)(const T&, const T&)) {
    if (head == tail) { return; }
    Iterator pivot = partition(head, tail, comparator);
    quick_sort(pivot.elem->get_next(), tail, comparator);
    quick_sort(head, pivot, comparator);
}
template<class T>
void LinkedList<T>::_quick_sort(bool(*comparator)(const T&, const T&)) {
    quick_sort(first, last, comparator);
}