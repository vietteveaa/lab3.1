#pragma once

template <class T>
class Node {
private:
    T data;
    Node<T>* previousp;
    Node<T>* nextp;
public:
    Node();
    ~Node();
    const T& get_data();
    void set_data(T item);
    Node<T>* get_next();
    void set_next(Node<T>* elem);
    Node<T>* get_previous();
    void set_previous(Node<T>* elem);
};
template <class T>
class LinkedList {
private:
    Node<T> *first;
    Node<T> *last;
    int size;
public:
    LinkedList(T *items, int count);
    LinkedList();
    LinkedList(LinkedList<T>& list);
    ~LinkedList();

    int get_length() const;
    Node<T>* get_first();
    Node<T>* get_last();
    Node<T>* get(int index);
    LinkedList<T>* get_sublist(int startIndex, int endIndex);

    void append(const T& item);
    void prepend(const T& item);
    void insert_at(const T& item, int index);
    LinkedList<T>* concat(LinkedList<T>* list);

    class Iterator {
    public:
        Node<T>* elem;
        Iterator(Node<T>* new_elem);
        Iterator();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator operator+=(int count);
        Iterator operator-=(int count);
        bool operator==(const Iterator& to_compare);
        bool operator!=(const Iterator& to_compare);
        const T& operator*();
    };
    Iterator begin();
    Iterator end();

    void split(Iterator head, Iterator& a, Iterator& b);
    void merge_sort(Iterator& head, bool (*comparator)(const T&, const T&));
    void merge_sort_(bool (*comparator)(const T&, const T&));
    Iterator merge(Iterator f, Iterator s, bool (*comparator)(const T&, const T&));

    Node<T>* swap(Node<T>*, Node<T>*);
    void bubble_sort(Node<T>** first, int count, bool(*comparator)(const T&, const T&));

    Iterator partition(Iterator head, Iterator tail, bool(*comparator)(const T&, const T&));
    void quick_sort(Iterator head, Iterator tail, bool(*comparator)(const T&, const T&));
    void _quick_sort(bool(*comparator)(const T&, const T&));
};