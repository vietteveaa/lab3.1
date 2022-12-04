#include "libs.h"
#include "LinkedList.cpp"
#include "DynamicArray.cpp"
#include "smth.cpp"
#include "ListSequence.cpp"
#include "ArraySequence.cpp"

int main() {
    int array[4] = {-1, -23, 5, 70};

    ListSequence<int> list_to_test_qs(array, 4);
    list_to_test_qs.append(10);
    list_to_test_qs.prepend(5);
    list_to_test_qs.insert_at(-7, 2);
    ListSequence<int> list_to_test_ms(array, 4);
    list_to_test_ms.append(10);
    list_to_test_ms.prepend(5);
    list_to_test_ms.insert_at(-7, 2);
    cout << "List given:" << endl;
    for (int i = 0; i < list_to_test_qs.get_length(); ++i) {
        cout << list_to_test_qs.get(i) << " ";
    }
    cout << endl;
    list_to_test_qs._quick_sort(comparator);
    cout << "List sorted (quick sort):" << endl;
    for (int i = 0; i < list_to_test_qs.get_length(); ++i) {
        cout << list_to_test_qs.get(i) << " ";
    }
    cout << endl;
    cout << "List given:" << endl;
    for (int i = 0; i < list_to_test_ms.get_length(); ++i) {
        cout << list_to_test_ms.get(i) << " ";
    }
    cout << endl;
    list_to_test_ms.merge_sort_(comparator);
    cout << "List sorted (merge sort):" << endl;
    for (int i = 0; i < list_to_test_ms.get_length(); ++i) {
        cout << list_to_test_ms.get(i) << " ";
    }
    cout << endl << endl << endl;




    ArraySequence<int> array_to_test_qs(array, 4);
    array_to_test_qs.append(10);
    array_to_test_qs.prepend(5);
    array_to_test_qs.insert_at(-7, 2);
    ArraySequence<int> array_to_test_bs(array, 4);
    cout << "Array given:" << endl;
    for (int i = 0; i < array_to_test_qs.get_length(); ++i) {
        cout << array_to_test_qs.get(i) << " ";
    }
    cout << endl;
    array_to_test_qs._quick_sort(comparator);
    cout << "Array sorted (quick sort):" << endl;
    for (int i = 0; i < array_to_test_qs.get_length(); ++i) {
        cout << array_to_test_qs.get(i) << " ";
    }
    cout << endl;
    cout << "Array given:" << endl;
    for (int i = 0; i < array_to_test_bs.get_length(); ++i) {
        cout << array_to_test_bs.get(i) << " ";
    }
    cout << endl;
    array_to_test_bs.bubble_sort();
    cout << "Array sorted (bubble sort):" << endl;
    for (int i = 0; i < array_to_test_bs.get_length(); ++i) {
        cout << array_to_test_bs.get(i) << " ";
    }
    cout << endl;
    return 0;
};