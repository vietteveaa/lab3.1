#include "i_sorter.h"
#include "libs.h"

template <class T>
void ISorter<T>::quick_sort(Sequence<T>* seq, bool(*comparator)(const T&, const T&)) {
    high_resolution_clock::time_point t_start, t_end;
    duration<double> time_span;
    message_before(seq);
    t_start = high_resolution_clock::now();
    seq->_quick_sort(comparator);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    message_after(seq);
    cout << "Время, которое было затрачено на работу алгоритма, составило " << time_span.count() << " секунд" << endl;
    cout << endl;
}
template <class T>
void ISorter<T>::bubble_sort(Sequence<T>* seq, bool(*comparator)(const T&, const T&)) {
    high_resolution_clock::time_point t_start, t_end;
    duration<double> time_span;
    message_before(seq);
    t_start = high_resolution_clock::now();
    seq->bubble_sort(comparator);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    message_after(seq);
    cout << "Время, которое было затрачено на работу алгоритма, составило " << time_span.count() << " секунд" << endl;
    cout << endl;
}
template <class T>
void ISorter<T>::merge_sort(Sequence<T>* seq, bool(*comparator)(const T&, const T&)) {
    high_resolution_clock::time_point t_start, t_end;
    duration<double> time_span;
    message_before(seq);
    t_start = high_resolution_clock::now();
    seq->merge_sort_(comparator);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    message_after(seq);
    cout << "Время, которое было затрачено на работу алгоритма, составило " << time_span.count() << " секунд" << endl;
    cout << endl;
}

template<class T>
void ISorter<T>::message_before(Sequence<T>* seq) {
    cout << "Последовательность до сортировки: " << endl;
    for (int i = 0; i < seq->get_length(); i++) {
        cout << seq->get(i) << ' ';
    }
    cout << endl;
}
template<class T>
void ISorter<T>::message_after(Sequence<T>* seq) {
    cout << "Последовательность после сортировки: " << endl;
    for (int i = 0; i < seq->get_length(); i++) {
        cout << seq->get(i) << ' ';
    }
    cout << endl;
}