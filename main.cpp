#include "libs.h"
#include "LinkedList.cpp"
#include "DynamicArray.cpp"
#include "smth.cpp"
#include "i_sorter.cpp"
#include "ListSequence.cpp"
#include "ArraySequence.cpp"

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int option0, option1, option2, option3;
    int item, index, index_beginning, index_ending;
    int length = 0;

    fstream file_for_writing, file_for_saving;
    fstream file;
    string name_of_file, str1;
    int item0;
    int* array_from_file = new int[10000];

    ISorter<int> tmp;

    high_resolution_clock::time_point t_start, t_end;
    duration<double> time_span1, time_span2, time_span3, time_span4, time_span5, time_span6, time_span7, time_span8, time_span9;

    int array[1] = {0};
    ListSequence<int> list(array, 1);
    Sequence<int>* sequence = &list;

    int* items1 = new int[50000];
    for (int i = 0; i < 50000; i++)
        items1[i] = rand();
    int* items2 = new int[60000];
    for (int i = 0; i < 60000; i++)
        items2[i] = rand();
    int* items3 = new int[70000];
    for (int i = 0; i < 70000; i++)
        items3[i] = rand();

    ListSequence<int> list_ex1(items1, 50000);
    Sequence<int>* sequence_ex1_bis = &list_ex1;
    Sequence<int>* sequence_ex1_qs = sequence_ex1_bis;
    Sequence<int>* sequence_ex1_ms = sequence_ex1_bis;

    ListSequence<int> list_ex2(items2, 60000);
    Sequence<int>* sequence_ex2_bis = &list_ex2;
    Sequence<int>* sequence_ex2_qs = sequence_ex2_bis;
    Sequence<int>* sequence_ex2_ms = sequence_ex2_bis;

    ListSequence<int> list_ex3(items3, 70000);
    Sequence<int>* sequence_ex3_bis = &list_ex3;
    Sequence<int>* sequence_ex3_qs = sequence_ex3_bis;
    Sequence<int>* sequence_ex3_ms = sequence_ex3_bis;

    do {
        cout << endl;
        cout << "РАБОТА С ПОСЛЕДОВАТЕЛЬНОСТЯМИ" << endl;
        cout << "-----------------------------" << endl;
        cout << endl;
        cout << "Что вы хотите сделать ? Выберите нужную опцию из списка ниже" << endl;
        cout << endl;
        cout << "1 - Получить последовательность из файла" << endl;
        cout << "2 – Вставить элемент в последовательность" << endl;
        cout << "3 – Получить элемент последовательности" << endl;
        cout << "4 - Узнать длину последовательности" << endl;
        cout << "5 - Получить подпоследовательность" << endl;
        cout << "6 - Отсортировать последовательность" << endl;
        cout << "7 - Сравнить алгоритмы сортировки" << endl;
        cout << "8 - Отобразить последовательность" << endl;
        cout << "9 - Сохранить последовательность в файл" << endl;
        cout << "10 - Очистить экран" << endl;
        cout << "11 - Завершить работу" << endl;

        cout << endl;

        cin >> option0;
        cout << endl;
        switch (option0) {
            case 1:
                cout << "Введите название файла, из которого хотите получить последовательность: ";
                cin >> name_of_file;
                file_for_writing.open(name_of_file, fstream::out);
                if (!file_for_writing.is_open())
                    cout << "Ошибка открытия файла!" << endl;
                else {
                    for (int i = 0; i < 10000; i++)
                        file_for_writing << rand() << ' ';
                    file_for_writing << endl;
                    file_for_writing << endl;
                    file_for_writing.close();
                    file_for_writing.open(name_of_file, fstream::in);
                    for (int i = 0; i < 10000; i++)
                        file_for_writing >> array_from_file[i];
                    for (int i = 0; i < 10000; i++)
                        sequence->append(array_from_file[i]);
                }
                file_for_writing.close();
                file_for_writing.open(name_of_file, fstream::out);
                if (!file_for_writing.is_open())
                    cout << "Ошибка открытия файла!" << endl;
                else
                    while (getline(file_for_writing, str1))
                        file_for_writing << " ";
                file_for_writing.close();
                break;
            case 2:
                cout << "Какой элемент вы хотите вставить в последовательность? Введите его: ";
                cin >> item;
                cout << endl;
                cout << "Выберете интересующее вас предложение: " << endl;
                cout << "1 - вставить элемент в начало" << endl;
                cout << "2 - вставить элемент в конец" << endl;
                cout << "3 - вставить элемент по индексу" << endl;
                cout << endl;
                cin >> option1;
                switch (option1) {
                    case 1:
                        sequence->prepend(item);
                        break;
                    case 2:
                        sequence->append(item);
                        break;
                    case 3:
                        cout << endl;
                        cout << "На какое место вы хотите поместить элемент? Введите его: ";
                        cin >> index;
                        sequence->insert_at(item, index);
                        break;
                    default:
                        cout << endl;
                        cout << "Введённый вами номер отсутствует в списке!" << endl;
                        break;
                }
                break;
            case 3:
                cout << "Какой элемент последовательности вы хотите получить? Введите его номер: ";
                cin >> index;
                cout << endl;
                cout << sequence->get(index) << endl;
                break;
            case 4:
                cout << sequence->get_length() << endl;
                break;
            case 5:
                cout << "Введите индексы начала и конца подпоследовательности, которую хотите получить: ";
                cin >> index_beginning >> index_ending;
                cout << endl;
                sequence->get_subSequence(index_beginning, index_ending);
                break;
            case 6:
                cout << "Какую сортировку вы хотите использовать?" << endl;
                cout << "1 - сортировку пузырьком" << endl;
                cout << "2 - быструю сортировку" << endl;
                cout << "3 - сортировку слиянием" << endl;
                cout << endl;
                cin >> option2;
                cout << endl;
                switch (option2) {
                    case 1:
                        tmp.bubble_sort(sequence);
                        cout << endl;
                        break;
                    case 2:
                        tmp.quick_sort(sequence, comparator);
                        cout << endl;
                        break;
                    case 3:
                        tmp.merge_sort(sequence, comparator);
                        cout << endl;
                        break;
                    default:
                        cout << endl;
                        cout << "Введённый вами номер отсутствует в списке!" << endl;
                        cout << endl;
                        break;
                }
                break;
            case 7:

                //быстрая сортировка
                t_start = high_resolution_clock::now();
                sequence_ex1_qs->_quick_sort(comparator);
                t_end = high_resolution_clock::now();
                time_span4 = duration_cast<duration<double>>(t_end - t_start);

                t_start = high_resolution_clock::now();
                sequence_ex2_qs->_quick_sort(comparator);
                t_end = high_resolution_clock::now();
                time_span5 = duration_cast<duration<double>>(t_end - t_start);

                t_start = high_resolution_clock::now();
                sequence_ex3_qs->_quick_sort(comparator);
                t_end = high_resolution_clock::now();
                time_span6 = duration_cast<duration<double>>(t_end - t_start);

                //сортировка слиянием
                t_start = high_resolution_clock::now();
                sequence_ex1_ms->merge_sort_(comparator);
                t_end = high_resolution_clock::now();
                time_span7 = duration_cast<duration<double>>(t_end - t_start);

                t_start = high_resolution_clock::now();
                sequence_ex2_ms->merge_sort_(comparator);
                t_end = high_resolution_clock::now();
                time_span8 = duration_cast<duration<double>>(t_end - t_start);

                t_start = high_resolution_clock::now();
                sequence_ex3_ms->merge_sort_(comparator);
                t_end = high_resolution_clock::now();
                time_span9 = duration_cast<duration<double>>(t_end - t_start);

                //сортировка пузырьком
                t_start = high_resolution_clock::now();
                sequence_ex1_bis->bubble_sort();
                t_end = high_resolution_clock::now();
                time_span1 = duration_cast<duration<double>>(t_end - t_start);

                t_start = high_resolution_clock::now();
                sequence_ex2_bis->bubble_sort();
                t_end = high_resolution_clock::now();
                time_span2 = duration_cast<duration<double>>(t_end - t_start);

                t_start = high_resolution_clock::now();
                sequence_ex3_bis->bubble_sort();
                t_end = high_resolution_clock::now();
                time_span3 = duration_cast<duration<double>>(t_end - t_start);


                file.open("comparison.csv", fstream::out | fstream::in | fstream::app);
                //Количество элементов;Время работы алгоритма сортировки пузырьком;Время работы алгоритма быстрой сортировки;Время работы алгоритма сортировки слиянием
//                file << 50000 << ";";............................................................................................l << time_span1.count() << ";" << time_span4.count() << ";" << time_span7.count() << ";" << "\n";
                file << 60000 << ";" << time_span2.count() << ";" << time_span5.count() << ";" << time_span8.count() << ";" << "\n";
                file << 70000 << ";" << time_span3.count() << ";" << time_span6.count() << ";" << time_span9.count() << ";" << "\n";
                file.close();
                cout << "Результаты сравнительного анализа можно увидеть в файле comparison.csv" << endl;
                cout << endl;
                break;
            case 8:
                for (int i = 0; i < sequence->get_length(); i++) {
                    cout << sequence->get(i) << ' ';
                }
                cout << endl;
                break;
            case 9:
                cout << "Введите название файла, в который хотите сохранить последовательность: ";
                cin >> name_of_file;
                file_for_saving.open(name_of_file, fstream::out);
                if (!file_for_saving.is_open())
                    cout << "Ошибка открытия файла!" << endl;
                else {
                    for (int i = 0; i < sequence->get_length(); i++)
                        file_for_saving << sequence->get(i) << ' ';
                    file_for_saving << endl;
                    file_for_saving << endl;
                }
                file_for_saving.close();
                break;
            case 10:
                system("cls");
                break;
            case 11:
                break;
            default:
                cout << "Введённый вами номер отсутствует в списке!" << endl;
                break;
        }
    } while (option0 != 11);
    return 0;
}