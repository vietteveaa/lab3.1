template <class T>
bool comparator(const T& elem1, const T& elem2) { return (elem1 < elem2); }

template <class T>
class Node {
private:
    T data;
    Node<T>* previousp;
    Node<T>* nextp;
public:
    const T& get_data() { return this->data; }
    void set_data(T item) { this->data = item; }
    Node* get_next() { return this->nextp; }
    void set_next(Node* elem) { this->nextp = elem; }
    Node* get_previous() { return this->previousp; }
    void set_previous(Node* elem) { this->previousp = elem; };
};
template <class T>
class LinkedList {
private:
    Node<T>* first;
    Node<T>* last;
public:
    LinkedList(T* items, int count) {
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

    LinkedList() = default;

    LinkedList(LinkedList<T>& list) {//const
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

public:
    int get_length() const {
        int size = 1;
        Node<T>* elem = this->first;
        while (elem->get_next() != nullptr) {
            elem = elem->get_next();
            ++size;
        }
        return size;
    }

    Node<T>* get_first() { return this->first; }
    Node<T>* get_last() { return this->last; }
    Node<T>* get(int index) {
        Node<T> *elem = this->first;
        for (int i = 0; i < index; ++i) { elem = elem->get_next(); }
        return elem;
    }

    LinkedList<T>* get_sublist(int startIndex, int endIndex) {
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

public:
    void append(const T& item) {
        auto* new_last = new Node<T>;
        auto* old_last = new Node<T>;
        new_last->set_data(item);
        new_last->set_previous(this->last);
        new_last->set_next(nullptr);
        old_last = new_last->get_previous();
        old_last->set_next(new_last);
        this->last = new_last;
    }
    void prepend(const T& item) {
        auto* new_first = new Node<T>;
        auto* old_first = new Node<T>;
        new_first->set_data(item);
        new_first->set_previous(nullptr);
        new_first->set_next(this->first);
        old_first = new_first->get_next();
        old_first->set_previous(new_first);
        this->first = new_first;
    }
    void insert_at(const T& item, int index) {
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
    LinkedList<T>* concat(LinkedList<T>* list) {
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

public:
    class Iterator {
    public:
        Node<T>* elem;
        Iterator(Node<T>* new_elem) { this->elem = new_elem; }
        Iterator& operator++() {
            elem = elem->get_next();
            return *this;
        }
        Iterator operator++(int) {
            ++(*this);
            return *this;
        }
        Iterator& operator--() {
            elem = elem->get_previous();
            return *this;
        }
        Iterator operator--(int) {
            --(*this);
            return *this;
        }
        Iterator operator+=(int count) {
            for (int i = 0; i < count; ++i)
                ++elem;
            return elem;
        }
        Iterator operator-=(int count) {
            for (int i = 0; i < count; ++i)
                --elem;
            return elem;
        }
        bool operator==(const Iterator& to_compare) { return this->elem==to_compare.elem; }
        bool operator!=(const Iterator& to_compare) { return this->elem!=to_compare.elem; }
        const T& operator*() { return this->elem->get_data(); }
    };
    Iterator begin() {
        return Iterator(first);
    }

    /////////////////////////////////////////////////СОРТИРОВКИ//////////////////////////////////////////////

public:
    //СЛИЯНИЕМ
    void split(Iterator head, Iterator& a, Iterator& b) {
        Iterator s = head, f = head;
        ++f;
        while (f != nullptr) {
            ++f;
            if (f != nullptr) {
                ++f;
                ++s;
            }
        }
        Iterator temp = s;
        ++temp;
        a = head;
        b = temp;
        s.elem->set_next(nullptr);
    }
    void merge_sort(Iterator& head, bool* comparator(const T&, const T&)) {
        Iterator head_ = head, f, s;
        Iterator temp = head;
        ++temp;
        if ((head == nullptr) || (temp == nullptr)) return;
        split(head_, f, s);
        merge_sort(f, comparator);
        merge_sort(s, comparator);
        head = merge(f, s, comparator);
    }
    void merge_sort_(bool* comparator(const T&, const T&)) {
        Iterator head_ = begin();
        merge_sort(head_, comparator);
        first = head_.elem;
    }
    Iterator merge(Iterator f, Iterator s, bool* comparator(const T&, const T&)) {
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
                ++s;
            }
            else {
                temp.elem->set_next(f.elem);
                ++f;
            }
            ++temp;
        }
        if (f != nullptr) {
            temp.elem->set_next(f.elem);
        }
        if (s != nullptr) {
            temp.elem->set_next(s.elem);
        }
    }
    //БАББЛ
    void bubble_sort() {
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
            current->set_next() = (trail->get_next())->get_next();
            j = 0;
        }
    }
};