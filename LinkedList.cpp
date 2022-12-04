#include "libs.h"
#include "LinkedList.h"

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
    auto* previous = new Node<T>;
    this->first = previous;
    previous->set_previous(nullptr);
    previous->set_data(items[0]);
    for (int i = 1; i < count; ++i) {
        auto* next = new Node<T>;
        next->set_previous(previous);
        previous->set_next(next);
        next->set_data(items[i]);
        previous = next;
        this->last = next;
        next->set_next(nullptr);
    }
}
template <class T>
LinkedList<T>::LinkedList() = default;

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& list) {//const
    auto* previous_elem = new Node<T>;
    Node<T>* elem = list.first;
    int count = list.GetLenght();
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

template <class T>
int LinkedList<T>::get_length() const {
    int size = 1;
    Node<T>* elem = this->first;
    while (elem->get_next() != nullptr) {
        elem = elem->get_next();
        ++size;
    }
    return size;
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
    template<class T>
    void LinkedList<T>::bubble_sort() {
        int j = 0, counter = this->get_length();
        Node<T>* current = this->first;
        Node<T>* trail = this->first;
        Node<T>* temp = nullptr;

        for (int i = 0; i < counter; ++i) {
            while (current != nullptr) {
                if (trail->get_data() > current->get_data()) {
                    temp = current->get_next();
                    current->set_next(trail);
                    trail->set_next(temp);

                    temp = current;
                    current = trail;
                    trail = temp;

                    if (j == 0) { this->first = trail; }
                }
                ++j;
                trail = current;
                current = current->get_next();
            }

            trail = first;
            current = trail->get_next();
            current->set_next((trail->get_next())->get_next());
            j = 0;
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