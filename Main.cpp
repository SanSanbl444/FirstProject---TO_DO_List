/*
//   ��������� "������ ���"
//
//   1. ���������� ���.
//   2. �������� ���.
//   3. �������������� ���.
//   4. ����� ��� ��:
//      - ��������;
//      - ����������;
//      - ��������;
//      - ���� � ������� ����������.
//   5. ����������� ������ ���:
//      - �� ����;
//      - �� ������;
//      - �� �����.
//      ��� ����������� ������ ���� ����������:
//      - �� ����������;
//      - �� ���� � ������� ����������.
//
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <conio.h>      // ��� _getch()

using namespace std;

struct WorkTask                                     // ��������� ����� ������ "����"
{
    int id;                                         // ���������� ����� ����
    string name;                                    // ������� �������� ����
    int priority;                                   // ��������� ����
    string description;                             // �������� ����
    tm time_work_task;                              // ��������� ������ � ������� ������ �������, ����, ���� � �.�.
};

void isFileAvailable ();                                                    // �������� ������� ����� � �������
void selectingNumberAction (int *number_action);                            // ����� �������� � ��������� �� ������
int getTolalNumbersWorkTasksInFile ();                                      // ���������� ������ ���������� ���, ������������ � �����
int getMaxNumbersWorkTasksInFile (int count_id);                            // ���������� ������������� ID �� ������������� �����
void getTotalArrayWorkTasks (WorkTask *input_array, int count_id);          // ��������� ����� ������� ��� �� ������������� �����
void writeArrayInFile (WorkTask *input_array, int count_id);                // ������� ����� � ������ � ���� ��������� �������
void getSortingArrayByID (WorkTask *sorting_array, int temp_count);         // ���������� �������� ������� �� ����������� �� ID
void getSortingArrayByPriority (WorkTask *sorting_array, int temp_count);   // ���������� �������� ������� �� ����������� �� ����������
void getSortingArrayByDate (WorkTask *sorting_array, int temp_count);       // ���������� �������� ������� �� ����������� �� ������� ����������
void outputSingleElementArrayOfWorkTasks (WorkTask *input_array, int number_task);      // ����� �� ����� ������ �������� �������� ������� ��������� WorkTask
void outputSingleElemenInputArrayOfWorkTasks (WorkTask *input_array, int number, int index_element);    // ����� �� ����� ������ �������� ��������� ������� ��������� WorkTask
void deleteSingleElementArrayofWorkTasks (WorkTask *input_array, int count_id, int number_delete_id);   // �������� ������ ���� �� ����� ������� ���
int returnMaxDayOnMonth (int year, int month);                                        // ���������� ������������ ���������� ���� � ������


int main () {
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);

    int number_action;                              // ����� �������� � ��������� �� ������

    isFileAvailable();                              // �������� ������� �����

    do {
        selectingNumberAction (&number_action);     // ���� ��������

        switch (number_action) {

            // ���������� ������ ���� � ����� ������ ���
            case 1: {
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();     // ������� id

                WorkTask new_task;

              // ������ ID ������ ����
                new_task.id = getMaxNumbersWorkTasksInFile(count_id) + 1;

              // ������ �������� ������ ����
                cout << "������� ������� �������� ����: ";
                getchar();                          // �� �������� ��� ���� ������ � ���������� MSVS
                getline(cin, new_task.name);

              // ������ ���������� ������ ����
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                cout << "���������� ���� (1 - 5):\n\n"
                     << "1 - ������ ���������\n"
                     << "....................\n"
                     << "5 - ������ ���������\n\n"
                     << "������� ��������� ���� (1 - 5): ";

                while (!(cin >> new_task.priority)
                       ||  (new_task.priority < 1)
                       ||  (new_task.priority > 5))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\n������ ������������ ���������\n"
                         << "��������� ������ ���� �� 1 �� 5\n\n"
                         << "������� ��������� ���� (1 - 5): ";
                }

              // ������ �������� ������ ����
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                cout << "������� �������� (����) ����: ";
                getchar();                          // �� �������� ��� ���� ������ � ���������� MSVS
                getline(cin, new_task.description);

              // ������ ���� ���������� ����
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                cout << "������� ��� ���������� ���� (2022 - 2100, ������ XXXX): ";

                while (!(cin >> new_task.time_work_task.tm_year)
                       ||  (new_task.time_work_task.tm_year < 2022)
                       ||  (new_task.time_work_task.tm_year > 2100))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\n������ ������������ ����� ����\n"
                         << "��� ������ ���� �� 2022 �� 2100 � ������� XXXX\n\n"
                         << "������� ��� ���������� ���� (2022 - 2100, ������ XXXX): ";
                }

              // ������ ������ ���������� ����
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                cout << "������� ����� ����� ���������� ���� (1 - 12): ";

                while (!(cin >> new_task.time_work_task.tm_mon)
                       ||  (new_task.time_work_task.tm_mon < 1)
                       ||  (new_task.time_work_task.tm_mon > 12))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\n������ ������������ ����� ������\n"
                         << "����� ������ ������ ���� �� 1 �� 12\n\n"
                         << "������� ����� ������ ���������� ���� (1 - 12): ";
                }

              // ������ ��� ���������� ����
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                // �������� 31-������� �������
                if (new_task.time_work_task.tm_mon == 1
                    || new_task.time_work_task.tm_mon == 3
                    || new_task.time_work_task.tm_mon == 5
                    || new_task.time_work_task.tm_mon == 7
                    || new_task.time_work_task.tm_mon == 8
                    || new_task.time_work_task.tm_mon == 10
                    || new_task.time_work_task.tm_mon == 12)
                {
                    cout << "������� ���� ���������� ���� (1 - 31): ";

                    while (!(cin >> new_task.time_work_task.tm_mday)
                           ||  (new_task.time_work_task.tm_mday < 1)
                           ||  (new_task.time_work_task.tm_mday > 31))
                    {
                        cin.clear();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\n������ ������������ ���� ������\n"
                             << "���������� ���� � ���� ������ ����� ���� �� 1 �� 31\n\n"
                             << "������� ���� ���������� ���� (1 - 31): ";
                    }
                }

                // �������� 30-������ �������
                else if (new_task.time_work_task.tm_mon == 4
                         || new_task.time_work_task.tm_mon == 6
                         || new_task.time_work_task.tm_mon == 9
                         || new_task.time_work_task.tm_mon == 11) {
                    cout << "������� ���� ���������� ���� (1 - 30): ";

                    while (!(cin >> new_task.time_work_task.tm_mday)
                           ||  (new_task.time_work_task.tm_mday < 1)
                           ||  (new_task.time_work_task.tm_mday > 30))
                    {
                        cin.clear();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\n������ ������������ ���� ������\n"
                             << "���������� ���� � ���� ������ ����� ���� �� 1 �� 30\n\n"
                             << "������� ���� ���������� ���� (1 - 30): ";
                    }
                }

                // �������� ��������
                else if (new_task.time_work_task.tm_mon == 2) {
                  // �������� ������������ ���������� ����
                    bool year_temp_bool = false;
                    if (new_task.time_work_task.tm_year % 4 == 0) {
                        if (new_task.time_work_task.tm_year % 100 == 0) {
                            if (new_task.time_work_task.tm_year % 400 == 0) {
                                year_temp_bool = true;
                            }
                        } else {
                            year_temp_bool = true;
                        }
                    }

                    if (year_temp_bool == true) {
                        cout << "������� ���� ���������� ���� (1 - 29): ";

                        while (!(cin >> new_task.time_work_task.tm_mday)
                               ||  (new_task.time_work_task.tm_mday < 1)
                               ||  (new_task.time_work_task.tm_mday > 29))
                        {
                            cin.clear();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ���� ������\n"
                                 << "���������� ���� � ���� ������ ���� ����� ���� �� 1 �� 29\n\n"
                                 << "������� ���� ���������� ���� (1 - 29): ";
                        }
                    } else {
                        cout << "������� ���� ���������� ���� (1 - 28): ";

                        while (!(cin >> new_task.time_work_task.tm_mday)
                               ||  (new_task.time_work_task.tm_mday < 1)
                               ||  (new_task.time_work_task.tm_mday > 28))
                        {
                            cin.clear();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ���� ������\n"
                                 << "���������� ���� � ���� ������ ���� ����� ���� �� 1 �� 28\n\n"
                                 << "������� ���� ���������� ���� (1 - 28): ";
                        }
                    }
                }       // end of  �������� ��������

              // ������ ���� ���������� ����
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                cout << "������� ��� ���������� ���� (0 - 23, ������ 24-� �������): ";

                while (!(cin >> new_task.time_work_task.tm_hour)
                       ||  (new_task.time_work_task.tm_hour < 0)
                       ||  (new_task.time_work_task.tm_hour > 23))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\n������ ������������ ���\n"
                         << "����� ���� ������ ���� �� 0 �� 23\n\n"
                         << "������� ��� ���������� ���� (0 - 23): ";
                }

              // ������ ����� ���������� ����
                system ("cls");
                cout << "���������� ������ ���� � ������ �����:\n\n\n";
                cout << "������� ������ ���������� ���� (0 - 59): ";

                while (!(cin >> new_task.time_work_task.tm_min)
                       ||  (new_task.time_work_task.tm_min < 0)
                       ||  (new_task.time_work_task.tm_min > 59))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\n��� ����� ����� � �����\n"
                         << "����� ����� ������ ���� �� 0 �� 59\n\n"
                         << "������� ������ ���������� ���� (0 - 59): ";
                }

              // ������ � ���� ������ ����
                ofstream file_work_task_write;
                file_work_task_write.open ("TO_DO_List.txt", ios::app);

                file_work_task_write << "ID ����:         \t"
                                     << new_task.id
                                     << endl
                                     << "�������� ����:   \t"
                                     << new_task.name
                                     << endl
                                     << "��������� ����:  \t"
                                     << new_task.priority
                                     << endl
                                     << "�������� ����:   \t"
                                     << new_task.description
                                     << endl
                                     << "����� ����������:\t"
                                     << new_task.time_work_task.tm_hour
                                     << ":"
                                     << new_task.time_work_task.tm_min
                                     << "\t"
                                     << new_task.time_work_task.tm_mday
                                     << " "
                                     << new_task.time_work_task.tm_mon
                                     << " "
                                     << new_task.time_work_task.tm_year
                                     << endl
                                     << endl;

                file_work_task_write.close ();
                system ("cls");
                cout << "���������� �������� � ���� !!!\n\n\n";

                system ("pause");
                break;  // out of  case 1
            }           // end of  case 1


            // �������� ������ ���� �� ������ ������ ���
            case 2: {
                system ("cls");
                cout << "�������� ���� �� ������ �����:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // ������� id

                if (count_id == 0) {
                    cout << "������ ������� !!!\n"
                         << "������ ���� !!!\n\n\n";
                    system("pause");
                    break;
                } else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // ������ ���� ���

                    // ��������� ������� ���� ���
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // ����� ���������� ����
                    int delete_task;
                    cout << "����� � ������ "
                         << count_id
                         << " ���:\n\n"
                         << "ID:\t�������� ����:\n";

                    for (int i = 0; i < count_id; i++) {
                        cout << main_array_tasks[i].id
                             << "\t"
                             << main_array_tasks[i].name
                             << endl;
                    }

                    cout << "\n\n������� ID (���������� �����) ����, ������� ����� �������: ";
                    bool number_id_is_has = false;
                    while (!(number_id_is_has)) {
                        cin >> delete_task;
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        for (int i = 0; i < count_id; i++) {
                            if (main_array_tasks[i].id == delete_task) {
                                number_id_is_has = true;
                                break;
                            } else {
                                number_id_is_has = false;
                            }
                        }
                        if (number_id_is_has == false){
                            cout << "\n\n������ ������������ ID (����� ����) !!!\n"
                                 << "������ ���� �� ���������� !!!\n\n"
                                 << "������� ID (���������� �����) ����, ������� ����� �������: ";
                        }
                    }

                    cout << "\n\n������� ����:\n";
                    outputSingleElementArrayOfWorkTasks(main_array_tasks, delete_task);

                    cout << "����������� �������� ����� ���� ��� ���������� �� ��������\n"
                         << "Y = ��, N = ���\n\n"
                         << "������� ���� �����: ";

                    char select = _getch();
                    cout << select;
                    _getch();
                    while ((select != 'Y') && (select != 'N')) {
                        cin.clear();
                        cout << "\n\n������������� �� �������� !!!\n"
                             << "Y = ��, N = ���\n\n"
                             << "������� ���� �����: ";
                        select = _getch();
                        cout << select;
                        _getch();
                    }

                    if (select == 'Y') {
                        deleteSingleElementArrayofWorkTasks (main_array_tasks, count_id, delete_task);
                        delete[]main_array_tasks;
                        cout << "\n\n\n\n���� ������� !!!\n\n\n";
                        system("pause");
                        break;  // out of  case 2
                    } else {
                        delete[]main_array_tasks;
                        cout << "\n\n\n\n�� ���������� �� �������� !!!\n\n\n";
                        system ("pause");
                        break;  // out of  case 2
                    }

                    delete[]main_array_tasks;
                }
            }           // end of  case 2


            // �������������� ������ ���� �� ������ ������ ���
            case 3: {
                system ("cls");
                cout << "�������������� ���� �� ������ �����:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // ������� id

                if (count_id == 0) {
                    cout << "������ ������������� !!!\n"
                        << "������ ���� !!!\n\n\n";
                    system ("pause");
                    break;
                } else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // ������ ���� ���

                    // ��������� ������� ���� ���
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // ����� ���� ��� ��������������
                    int change_task;
                    cout << "����� � ������ "
                         << count_id
                         << " ���:\n\n"
                         << "ID:\t�������� ����:\n";

                    for (int i = 0; i < count_id; i++) {
                        cout << main_array_tasks[i].id
                             << "\t"
                             << main_array_tasks[i].name
                             << endl;
                    }

                    cout << "\n\n������� ID (���������� �����) ����, ������� ����� �������������: ";
                    bool number_id_is_has = false;
                    while (!(number_id_is_has)) {
                        cin >> change_task;
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        for (int i = 0; i < count_id; i++) {
                            if (main_array_tasks[i].id == change_task) {
                                number_id_is_has = true;
                                break;
                            }
                            else {
                                number_id_is_has = false;
                            }
                        }
                        if (number_id_is_has == false) {
                            cout << "\n\n������ ������������ ID (����� ����) !!!\n"
                                 << "������ ���� �� ���������� !!!\n\n"
                                 << "������� ID (���������� �����) ����, ������� ����� �������������: ";
                        }
                    }

                    int index_change_task;
                    for (int i = 0; i < count_id; i++) {
                        if (main_array_tasks[i].id == change_task) {
                            index_change_task = i;
                            break;
                        }
                    }

                    system("cls");
                    cout << "\n\n����������� ����:\n";
                    outputSingleElementArrayOfWorkTasks (main_array_tasks, change_task);

                    cout << "����� ���� ����� �������������?\n"
                         << "1 - �������� ����\n"
                         << "2 - ��������� ����\n"
                         << "3 - �������� ����\n"
                         << "4 - ����� ��������� ����\n\n\n"
                         << "������� ����� ���� ��� ��������������: ";

                    int number_change_action;
                    while (!(cin >> number_change_action) || number_change_action < 1 || number_change_action > 4) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\n��� ������ ���� !!!\n"
                             << "������� ������ � ������� ��� ��� !!!"
                             << "������� ����� ���� ��� ��������������: ";;
                    }

                    if (number_change_action == 1) {
                        cout << "\n\n\n������� ����� �������� ����: ";
                        getchar ();                          // �� �������� ��� ���� ������ � ���������� MSVS
                        getline (cin, main_array_tasks[index_change_task].name);
                    } else if (number_change_action == 2) {
                        cout << "\n\n\n������� ����� ��������� ���� (1 - 5):\n\n"
                            << "1 - ������ ���������\n"
                            << "....................\n"
                            << "5 - ������ ���������\n\n"
                            << "������� ����� ��������� ���� (1 - 5): ";
                        while (!(cin >> main_array_tasks[index_change_task].priority)
                               || (main_array_tasks[index_change_task].priority < 1)
                               || (main_array_tasks[index_change_task].priority > 5)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ���������\n"
                                 << "��������� ������ ���� �� 1 �� 5\n\n"
                                 << "������� ��������� ���� (1 - 5): ";
                        }
                    } else if (number_change_action == 3) {
                        cout << "\n\n\n������� ����� �������� (����) ����: ";
                        getchar ();                          // �� �������� ��� ���� ������ � ���������� MSVS
                        getline (cin, main_array_tasks[index_change_task].description);
                    } else if (number_change_action == 4) {
                        cout << "\n\n\n������� ����� ��� ���������� ���� (2022 - 2100, ������ XXXX): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_year)
                               || (main_array_tasks[index_change_task].time_work_task.tm_year < 2022)
                               || (main_array_tasks[index_change_task].time_work_task.tm_year > 2100)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ����� ����\n"
                                 << "��� ������ ���� �� 2022 �� 2100 � ������� XXXX\n\n"
                                 << "������� ����� ��� ���������� ���� (2022 - 2100, ������ XXXX): ";
                        }

                        // ������ ������ ���������� ����
                        cout << "\n\n\n������� ����� ����� ������ ���������� ���� (1 - 12): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mon)
                               || (main_array_tasks[index_change_task].time_work_task.tm_mon < 1)
                               || (main_array_tasks[index_change_task].time_work_task.tm_mon > 12)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ����� ������\n"
                                << "����� ������ ������ ���� �� 1 �� 12\n\n"
                                << "������� ����� ����� ������ ���������� ���� (1 - 12): ";
                        }

                        // ������ ��� ���������� ����
                        // �������� 31-������� �������
                        if (main_array_tasks[index_change_task].time_work_task.tm_mon == 1
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 3
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 5
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 7
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 8
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 10
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 12) {
                            cout << "\n\n\n������� ����� ���� ���������� ���� (1 - 31): ";

                            while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday > 31)) {
                                cin.clear ();
                                while (cin.get () != '\n') {
                                    continue;
                                }
                                cout << "\n\n������ ������������ ���� ������\n"
                                     << "���������� ���� � ���� ������ ����� ���� �� 1 �� 31\n\n"
                                     << "������� ����� ���� ���������� ���� (1 - 31): ";
                            }
                        }

                        // �������� 30-������ �������
                        else if (main_array_tasks[index_change_task].time_work_task.tm_mon == 4
                                 || main_array_tasks[index_change_task].time_work_task.tm_mon == 6
                                 || main_array_tasks[index_change_task].time_work_task.tm_mon == 9
                                 || main_array_tasks[index_change_task].time_work_task.tm_mon == 11) {
                            cout << "\n\n\n������� ����� ���� ���������� ���� (1 - 30): ";

                            while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday > 30)) {
                                cin.clear ();
                                while (cin.get () != '\n') {
                                    continue;
                                }
                                cout << "\n\n������ ������������ ���� ������\n"
                                     << "���������� ���� � ���� ������ ����� ���� �� 1 �� 30\n\n"
                                     << "������� ����� ���� ���������� ���� (1 - 30): ";
                            }
                        }

                        // �������� ��������
                        else if (main_array_tasks[index_change_task].time_work_task.tm_mon == 2) {
                            // �������� ������������ ���������� ����
                            bool year_temp_bool = false;
                            if (main_array_tasks[index_change_task].time_work_task.tm_year % 4 == 0) {
                                if (main_array_tasks[index_change_task].time_work_task.tm_year % 100 == 0) {
                                    if (main_array_tasks[index_change_task].time_work_task.tm_year % 400 == 0) {
                                        year_temp_bool = true;
                                    }
                                } else {
                                    year_temp_bool = true;
                                }
                            }

                            if (year_temp_bool == true) {
                                cout << "\n\n\n������� ����� ���� ���������� ���� (1 - 29): ";

                                while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday > 29)) {
                                    cin.clear ();
                                    while (cin.get () != '\n') {
                                        continue;
                                    }
                                    cout << "\n\n������ ������������ ���� ������\n"
                                         << "���������� ���� � ���� ������ ���� ����� ���� �� 1 �� 29\n\n"
                                         << "������� ����� ���� ���������� ���� (1 - 29): ";
                                }
                            } else {
                                cout << "\n\n\n������� ����� ���� ���������� ���� (1 - 28): ";

                                while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday > 28)) {
                                    cin.clear ();
                                    while (cin.get () != '\n') {
                                        continue;
                                    }
                                    cout << "\n\n������ ������������ ���� ������\n"
                                         << "���������� ���� � ���� ������ ���� ����� ���� �� 1 �� 28\n\n"
                                         << "������� ����� ���� ���������� ���� (1 - 28): ";
                                }
                            }
                        }       // end of  �������� ��������

                      // ������ ���� ���������� ����
                        cout << "\n\n\n������� ����� ��� ���������� ���� (0 - 23, ������ 24-� �������): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_hour)
                               || (main_array_tasks[index_change_task].time_work_task.tm_hour < 0)
                               || (main_array_tasks[index_change_task].time_work_task.tm_hour > 23)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ���\n"
                                 << "����� ���� ������ ���� �� 0 �� 23\n\n"
                                 << "������� ����� ��� ���������� ���� (0 - 23): ";
                        }

                        // ������ ����� ���������� ����
                        cout << "\n\n\n������� ����� ������ ���������� ���� (0 - 59): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_min)
                               || (main_array_tasks[index_change_task].time_work_task.tm_min < 0)
                               || (main_array_tasks[index_change_task].time_work_task.tm_min > 59)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n��� ����� ����� � �����\n"
                                 << "����� ����� ������ ���� �� 0 �� 59\n\n"
                                 << "������� ����� ������ ���������� ���� (0 - 59): ";
                        }
                    }   // end of  else if 

                    writeArrayInFile (main_array_tasks, count_id);
                    delete[]main_array_tasks;

                    cout << "\n\n\n���� ������� ��������������� � ������������ !!!\n\n\n\n";
                    system ("pause");
                }
                break;  // out of  case 3
            }           // end of  case 3


            // ����� ���
            case 4: {
                system ("cls");
                cout << "����� ���� �� ������ �����:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // ������� id

                if (count_id == 0) {
                    cout << "������ ������ !!!\n"
                        << "������ ���� !!!\n\n\n";
                    system ("pause");
                    break;
                } else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // ������ ���� ���

                    // ��������� ������� ���� ���
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // ����� ���� ��� ������
                    cout << "�� ������ ��������� ����� ������ ����?\n"
                         << "1 - ����� �� �������� ����\n"
                         << "2 - ����� �� ���������� ����\n"
                         << "3 - ����� �� �������� ����\n"
                         << "4 - ����� �� ���� ���������� ����\n\n\n"
                         << "������� ����� �������� ��� ������: ";

                    int index_found_task;
                    while (!(cin >> index_found_task) || index_found_task < 1 || index_found_task > 4) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\n��� ������ �������� ��� ������ !!!\n"
                             << "������� ������ � ������� ��� ��� !!!"
                             << "������� ����� �������� ��� ������: ";;
                    }

                    WorkTask found_task;
                    int index_name_task = 0;

                    // ����� �� �������� ����
                    if (index_found_task == 1) {
                        cout << "\n\n\n������� �������� ���� ��� ������: ";
                        getchar ();                          // �� �������� ��� ���� ������ � ���������� MSVS
                        getline (cin, found_task.name);
                        cout << endl;

                        for (int i = 0; i < count_id; i++) {
                            if (main_array_tasks[i].name == found_task.name) {
                                index_name_task = main_array_tasks[i].id;
                                outputSingleElementArrayOfWorkTasks (main_array_tasks, index_name_task);
                                cout << endl;
                            }
                        }
                        if (index_name_task == 0) {
                            cout << "\n\n��� � ����� ��������� �� ������� !!!\n\n\n\n";
                            system ("pause");
                        } else {
                            system ("pause");
                        }
                    }
                    //����� �� ���������� ����
                    else if (index_found_task == 2) {
                        cout << "\n\n\n������� ��������� ��� ��� ������ (1 - 5):\n\n"
                             << "1 - ������ ���������\n"
                             << "....................\n"
                             << "5 - ������ ���������\n\n"
                             << "������� ��������� ��� ������ (1 - 5): ";
                        while (!(cin >> found_task.priority)
                               || (found_task.priority < 1)
                               || (found_task.priority > 5)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ���������\n"
                                 << "��������� ������ ���� �� 1 �� 5\n\n"
                                 << "������� ���������� ��������� ���� ��� ������ (1 - 5): ";
                        }
                        cout << endl;

                        for (int i = 0; i < count_id; i++) {
                            if (main_array_tasks[i].priority == found_task.priority) {
                                index_name_task = main_array_tasks[i].id;
                                outputSingleElementArrayOfWorkTasks (main_array_tasks, index_name_task);
                                cout << endl;
                            }
                        }
                        if (index_name_task == 0) {
                            cout << "\n\n��� � ����� ����������� �� ������� !!!\n\n\n\n";
                            system ("pause");
                        } else {
                            system ("pause");
                        }
                    }
                    //����� �� �������� ����
                    else if (index_found_task == 3) {
                        cout << "\n\n\n������� ������ �������� ���� ��� ������: ";
                        getchar ();                          // �� �������� ��� ���� ������ � ���������� MSVS
                        getline (cin, found_task.description);
                        cout << endl;

                        for (int i = 0; i < count_id; i++) {
                            if (main_array_tasks[i].description == found_task.description) {
                                index_name_task = main_array_tasks[i].id;
                                outputSingleElementArrayOfWorkTasks (main_array_tasks, index_name_task);
                                cout << endl;
                            }
                        }
                        if (index_name_task == 0) {
                            cout << "\n\n��� � ����� ��������� �� ������� !!!\n\n\n\n";
                            system ("pause");
                        } else {
                            system ("pause");
                        }
                    }
                    // ����� �� ���� ����������
                    else if (index_found_task == 4) {
                        cout << "\n\n\n������� ���� ���������� ���� ��� ������ (1 - 31): ";
                        while (!(cin >> found_task.time_work_task.tm_mday)
                               || (found_task.time_work_task.tm_mday < 1)
                               || (found_task.time_work_task.tm_mday > 31)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n����� ���� �� ���������� !!!\n"
                                 << "������� ���������� ���� ���������� ���� ��� ������ (1 - 31): ";
                        }

                        cout << "\n\n������� ����� ������ ���������� ���� ��� ������ (1 - 12): ";
                        while (!(cin >> found_task.time_work_task.tm_mon)
                               || (found_task.time_work_task.tm_mon < 1)
                               || (found_task.time_work_task.tm_mon > 12)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������ �� ���������� !!!\n"
                                 << "������� ���������� ����� ������ ���������� ���� ��� ������ (1 - 12): ";
                        }

                        cout << "\n\n������� ��� ���������� ���� ��� ������ (2022 - 2100): ";
                        while (!(cin >> found_task.time_work_task.tm_year)
                               || (found_task.time_work_task.tm_year < 2022)
                               || (found_task.time_work_task.tm_year > 2100)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\n������ ������������ ��� !!!\n"
                                 << "������� ���������� ��� ���������� ���� ��� ������ (2022 - 2100): ";
                        }

                        system("cls");
                        cout << "���������� ������ ����:\n\n";

                        for (int i = 0; i < count_id; i++) {
                            if (main_array_tasks[i].time_work_task.tm_year == found_task.time_work_task.tm_year) {
                                if (main_array_tasks[i].time_work_task.tm_mon == found_task.time_work_task.tm_mon) {
                                    if (main_array_tasks[i].time_work_task.tm_mday == found_task.time_work_task.tm_mday) {
                                        index_name_task = main_array_tasks[i].id;
                                        outputSingleElementArrayOfWorkTasks (main_array_tasks, index_name_task);
                                        cout << endl;
                                    }
                                }
                            }
                        }
                        if (index_name_task == 0) {
                            cout << "\n\n��� �� ��������� ���� �� ������� !!!\n\n\n\n";
                            system ("pause");
                        }
                        else {
                            system ("pause");
                        }
                    }
                    delete[]main_array_tasks;
                }
                break;  // out of  case 4
            }           // end of  case 4


            // ����������� ��� �� ����������
            case 5: {
                system ("cls");
                cout << "����������� ������ ��� �� ����������:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // ������� id

                if (count_id == 0) {
                    cout << "������ ���������� !!!\n"
                         << "������ ���� !!!\n\n\n";
                    system ("pause");
                    break;
                }
                else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // ������ ���� ���

                    // ��������� ������� ���� ���
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // ����� ��������� ��� ����������� ���
                    cout << "�� ������ ��������� ���������� ����?\n"
                        << "1 - ����������� ��� �� �������\n"
                        << "2 - ����������� ��� �� ������\n"
                        << "3 - ����������� ��� �� �����\n\n\n"
                        << "������� ����� ��������� ��� �����������: ";

                    int index_output_task;
                    while (!(cin >> index_output_task) || index_output_task < 1 || index_output_task > 3) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\n��� ������ ��������� ��� ����������� !!!\n"
                             << "������� ������ � ������� ��� ��� !!!"
                             << "������� ����� ��������� ��� ����������� (1 - 3): ";;
                    }
                    system ("cls");


                    cout << "��� ������������� ����?\n"
                        << "1 - ���������� �� ���������� ���\n"
                        << "2 - ���������� �� ������� ���������� ���\n"
                        << "\n\n������� ����� ��������� ���������� ��� �����������: ";

                    int index_sort_output_task;
                    while (!(cin >> index_sort_output_task) || index_sort_output_task < 1 || index_sort_output_task > 2) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\n��� ������ ��������� ��� ���������� !!!\n"
                             << "������� ������ � ������� ��� ��� !!!"
                             << "������� ����� ��������� ���������� ��� ����������� (1 - 2): ";;
                    }
                    system ("cls");

                    tm local_time;                          // ��������� ������ � ������� ������ �������� �������, ����, ���� � �.�.
                    tm local_time_week;                     // ����� ������
                    time_t time_now = time (0);             // ��������� ������� �������� ���������� �������
                    localtime_s (&local_time, &time_now);   // ������ � local_time �������� ���������� �������, ����, ���� � �.�.

                    local_time_week = local_time;

                    int index_name_task = 0;

                    // ����������� �� ������� ����
                    if (index_output_task == 1) {
                        cout << "������ ��� �� �������:\n\n\n";

                        for (int i = 0; i < count_id; i++) {
                            if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                if (main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1) {
                                    if (main_array_tasks[i].time_work_task.tm_mday == local_time.tm_mday) {
                                        index_name_task++;
                                    }
                                }
                            }
                        }

                        if (index_name_task == 0) {
                            cout << "\n\n��� �� ������� �� ���������� !!!\n\n\n\n";
                            system ("pause");
                        }
                        else {
                            WorkTask *output_array_task = new WorkTask[index_name_task];
                            int temp_index = 0;

                            for (int i = 0; i < count_id; i++) {
                                if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                    if (main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1) {
                                        if (main_array_tasks[i].time_work_task.tm_mday == local_time.tm_mday) {
                                            output_array_task[temp_index] = main_array_tasks[i];
                                            temp_index++;
                                        }
                                    }
                                }
                            }

                            // ���������� �� ����������
                            if (index_sort_output_task == 1) {
                                getSortingArrayByPriority(output_array_task, index_name_task);
                            }
                            // ���������� �� ������� ����������
                            else if (index_sort_output_task == 2) {
                                getSortingArrayByDate(output_array_task, index_name_task);
                            }
                            // ����� ���������������� ������ �� ����
                            for (int i = 0; i < index_name_task; i++) {
                                outputSingleElemenInputArrayOfWorkTasks (output_array_task, index_name_task, i);
                            }
                            delete[]output_array_task;
                            system ("pause");
                        }
                    }
                    // ����������� �� ������
                    else if (index_output_task == 2) {
                        cout << "������ ��� �� ������:\n\n\n";
                        int max_day = returnMaxDayOnMonth(local_time.tm_year, local_time.tm_mon + 1);

                        if (local_time.tm_mday + 7 > max_day) {
                            if (local_time.tm_mon == 11) {
                                local_time_week.tm_year++;
                                local_time_week.tm_mon = 0;
                                local_time_week.tm_mday = 7 - (max_day - local_time.tm_mday);
                                for (int i = 0; i < count_id; i++) {
                                    if ((main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900)
                                        || (main_array_tasks[i].time_work_task.tm_year == local_time_week.tm_year + 1900)) {
                                            if ((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                                || (main_array_tasks[i].time_work_task.tm_mon == local_time_week.tm_mon + 1)) {
                                                    if ((main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday)
                                                        || (main_array_tasks[i].time_work_task.tm_mday <= local_time_week.tm_mday)) {
                                                            index_name_task++;
                                                    }
                                            }
                                    }
                                }
                            }
                            else {
                                local_time_week.tm_mon++;
                                local_time_week.tm_mday = 7 - (max_day - local_time.tm_mday);
                                for (int i = 0; i < count_id; i++) {
                                    if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                        if ((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                            || (main_array_tasks[i].time_work_task.tm_mon == local_time_week.tm_mon + 1)) {
                                                if ((main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday)
                                                    || (main_array_tasks[i].time_work_task.tm_mday <= local_time_week.tm_mday)) {
                                                        index_name_task++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            for (int i = 0; i < count_id; i++) {
                                if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                    if (main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1) {
                                        if ((main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday)
                                            && (main_array_tasks[i].time_work_task.tm_mday <= local_time.tm_mday + 7)) {
                                                index_name_task++;
                                        }
                                    }
                                }
                            }
                        }

                        if (index_name_task == 0) {
                            cout << "\n\n��� �� ������ �� ���������� !!!\n\n\n\n";
                            system ("pause");
                        }
                        else {
                            WorkTask *output_array_task = new WorkTask[index_name_task];
                            int temp_index = 0;

                            if (local_time.tm_mday + 7 > max_day) {
                                if (local_time.tm_mon == 11) {
                                    for (int i = 0; i < count_id; i++) {
                                        if ((main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900)
                                            || (main_array_tasks[i].time_work_task.tm_year == local_time_week.tm_year + 1900)) {
                                            if ((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                                || (main_array_tasks[i].time_work_task.tm_mon == local_time_week.tm_mon + 1)) {
                                                    if ((main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday)
                                                        || (main_array_tasks[i].time_work_task.tm_mday <= local_time_week.tm_mday)) {
                                                            output_array_task[temp_index] = main_array_tasks[i];
                                                            temp_index++;
                                                    }
                                            }
                                        }
                                    }
                                }
                                else {
                                    for (int i = 0; i < count_id; i++) {
                                        if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                            if ((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                                || (main_array_tasks[i].time_work_task.tm_mon == local_time_week.tm_mon + 1)) {
                                                    if ((main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday)
                                                        || (main_array_tasks[i].time_work_task.tm_mday <= local_time_week.tm_mday)) {
                                                            output_array_task[temp_index] = main_array_tasks[i];
                                                            temp_index++;
                                                    }
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                for (int i = 0; i < count_id; i++) {
                                    if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                        if (main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1) {
                                            if ((main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday)
                                                && (main_array_tasks[i].time_work_task.tm_mday <= local_time.tm_mday + 7)) {
                                                    output_array_task[temp_index] = main_array_tasks[i];
                                                    temp_index++;
                                            }
                                        }
                                    }
                                }
                            }

                            // ���������� �� ����������
                            if (index_sort_output_task == 1) {
                                getSortingArrayByPriority (output_array_task, index_name_task);
                            }
                            // ���������� �� ������� ����������
                            else if (index_sort_output_task == 2) {
                                getSortingArrayByDate (output_array_task, index_name_task);
                            }
                            // ����� ���������������� ������� �� ������
                            for (int i = 0; i < index_name_task; i++) {
                                outputSingleElemenInputArrayOfWorkTasks (output_array_task, index_name_task, i);
                            }
                            system ("pause");
                        }
                    }
                    // ����������� �� �����
                    else if (index_output_task == 3) {
                        cout << "������ ��� �� �����:\n\n\n";

                        if (local_time.tm_mon == 11) {
                            for (int i = 0; i < count_id; i++) {
                                if ((main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900)
                                    || (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1901)) {
                                    if (((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                          && (main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday))
                                       || ((main_array_tasks[i].time_work_task.tm_mon == 1)
                                            && (main_array_tasks[i].time_work_task.tm_mday <= local_time.tm_mday))) {
                                                    index_name_task++;
                                    }
                                }
                            }
                        }
                        else {
                            for (int i = 0; i < count_id; i++) {
                                if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                    if (((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                          && (main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday))
                                       || ((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 2)
                                            && (main_array_tasks[i].time_work_task.tm_mday <= local_time.tm_mday))) {
                                                    index_name_task++;
                                    }
                                }
                            }
                        }

                        if (index_name_task == 0) {
                            cout << "\n\n��� �� ����� �� ���������� !!!\n\n\n\n";
                            system ("pause");
                        }
                        else {
                            WorkTask *output_array_task = new WorkTask[index_name_task];
                            int temp_index = 0;

                            if (local_time.tm_mon == 11) {
                                for (int i = 0; i < count_id; i++) {
                                    if ((main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900)
                                        || (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1901)) {
                                        if (((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                             && (main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday))
                                            || ((main_array_tasks[i].time_work_task.tm_mon == 1)
                                                && (main_array_tasks[i].time_work_task.tm_mday <= local_time.tm_mday))) {
                                                        index_name_task++;
                                        }
                                    }
                                }
                            }
                            else {
                                for (int i = 0; i < count_id; i++) {
                                    if (main_array_tasks[i].time_work_task.tm_year == local_time.tm_year + 1900) {
                                        if (((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 1)
                                             && (main_array_tasks[i].time_work_task.tm_mday >= local_time.tm_mday))
                                           || ((main_array_tasks[i].time_work_task.tm_mon == local_time.tm_mon + 2)
                                               && (main_array_tasks[i].time_work_task.tm_mday <= local_time.tm_mday))) {
                                                        output_array_task[temp_index] = main_array_tasks[i];
                                                        temp_index++;
                                        }
                                    }
                                }
                            }

                            // ���������� �� ����������
                            if (index_sort_output_task == 1) {
                                getSortingArrayByPriority (output_array_task, index_name_task);
                            }
                            // ���������� �� ������� ����������
                            else if (index_sort_output_task == 2) {
                                getSortingArrayByDate (output_array_task, index_name_task);
                            }
                            // ����� ���������������� ������� �� ������
                            for (int i = 0; i < index_name_task; i++) {
                                outputSingleElemenInputArrayOfWorkTasks (output_array_task, index_name_task, i);
                            }
                            delete[]output_array_task;
                            system ("pause");
                        }
                    }
                    delete[]main_array_tasks;
                }

                break;  // out of  case 5
            }           // end of  case 5


            // ����� �� ���������
            case 6: {
                system ("cls");
                cout << "\n\n\n������� �� ����������� ���������� !!!";
                break;  // out of  case 6
            }           // end of  case 6
        }       // end of  switch (number_action)

    } while (number_action != 6);           // end of MAIN  do - while

    cout << "\n\n\n\n";
    system ("pause");
    return 0;
}   // end of int main()


// �������� ������� �����, ���� ����� ���, �� ������
void isFileAvailable () {
    ifstream file_work_task_read;                       // �������� ������� ������ "ifstream" ��� ������ �����
    file_work_task_read.open ("TO_DO_List.txt");        // �������� ������� ��� ������

    if (file_work_task_read.is_open ()) {               // �������� �������� �����
        file_work_task_read.close();
    } else {
        file_work_task_read.close();
        ofstream file_work_task_write;
        file_work_task_write.open ("TO_DO_List.txt");
        file_work_task_write.close ();
    }
}


// ������ ������ �������� �� �������� ����������
void selectingNumberAction (int *number_action) {
    system ("cls");
    cout << "��������� ������ ��� !!!\n\n\n"
         << "��� ������ �������� ???\n\n"
         << "�������� ����� �������� �� ������:\n"
         << "1 - ���������� ������ ����\n"
         << "2 - �������� ������������� ����\n"
         << "3 - �������������� ������������� ����\n"
         << "4 - ����� ���\n"
         << "5 - ����������� ��� �� ����������\n"
         << "6 - ����� �� ���������\n\n\n"
         << "������� ����� ��������: ";

    while (!(cin >> *number_action) || *number_action < 1 || *number_action > 6) {
        cin.clear();
        while (cin.get() != '\n') {
            continue;
        }
        cout << "\n\n��� ������ �������� !!!\n"
             << "������� ������ � ������� ��� ��� !!!"
             << "������� ����� ��������: ";;
    }
}


// ��������� ������ ���������� ��� � ������������ �����
int getTolalNumbersWorkTasksInFile () {
    string temp;
    int count_id = 0;                           // ������� ���������� ������� (id)

    ifstream file_work_task_read;
    file_work_task_read.open ("TO_DO_List.txt");
    while (!file_work_task_read.eof ()) {
        getline (file_work_task_read, temp);
        count_id++;
    }
    file_work_task_read.close ();
    count_id /= 6;                              // ����� ���������� ������������ �������
    return count_id;
}


// ���������� ������������� ID �� ������������� �����
int getMaxNumbersWorkTasksInFile (int count_id) {
    WorkTask *main_array_tasks = new WorkTask[count_id];    // ������ ���� ���

    // ��������� ������� ���� ���
    getTotalArrayWorkTasks (main_array_tasks, count_id);

    int MAX = 0;
    for (int i = 0; i < count_id; i++) {
        if (main_array_tasks[i].id > MAX) {
            MAX = main_array_tasks[i].id;
        }
    }
    return MAX;
}


// ��������� ����� ������� ��� �� ������������� �����
void getTotalArrayWorkTasks (WorkTask *input_array, int count_id) {
    string temp;                                    // ����������� ������ �� �����
    int length_str_temp;                            // ����� ����������� ������

    ifstream file_work_task_read;                   // �������� ������� ������ "ifstream" ��� ������ �����
    file_work_task_read.open ("TO_DO_List.txt");    // �������� ������� ��� ������

    while (!file_work_task_read.eof ()) {
        for (int i = 0; i < count_id; i++) {
            for (int j = 1; j <= 6; j++) {
                string temp2;
                getline (file_work_task_read, temp);
                length_str_temp = temp.length ();
                char Q;
                int temp_count = 0;                 // ����� �������� �������
                int temp_count2 = 0;                // ��������� ��� ����������
                if (length_str_temp != 0) {
                    for (int k = 0; k <= length_str_temp; k++) {
                        Q = temp[k];
                        if (Q == '\t') {
                            temp_count = length_str_temp - k - 1;
                            temp_count2 = k;
                            break;
                        }
                    }

                    char *SA = new char[temp_count];

                    for (int z = 0; z <= temp_count; z++) {
                        SA[z] = temp[temp_count2 + 1];
                        temp_count2++;
                    }

                    temp2 = SA;
                }
                else {
                    continue;
                }

                if (j == 1) {
                    input_array[i].id = stoi (temp2);           // ������ "���� id"
                }
                else if (j == 2) {
                    input_array[i].name = temp2;                // ������ "���� name"
                }
                else if (j == 3) {
                    input_array[i].priority = stoi (temp2);     // ������ "���� priority"
                }
                else if (j == 4) {
                    input_array[i].description = temp2;         // ������ "���� description"
                }
                else if (j == 5) {
                    string tempHour;
                    string tempMin;
                    string tempDay;
                    string tempMonth;
                    string tempYear;
                    int count = 0;

                    // ���������� �����
                    for (int k = 0; k < 3; k++) {
                        if (temp2[k] != ':') {
                            tempHour.insert(count, 1, temp2[k]);
                            count++;
                        } else {
                            count = 0;
                            break;
                        }
                    }
                    input_array[i].time_work_task.tm_hour = stoi (tempHour);    // ������ "���� �����"

                    // ���������� �����
                    for (int k = 0; k < temp2.length(); k++) {
                        if (temp2[k] == ':') {
                            for (int k2 = 0; k2 < 3; k2++) {
                                if (temp2[k] != '\t') {
                                    k++;
                                    tempMin.insert (count, 1, temp2[k]);
                                    count++;
                                } else {
                                    break;
                                }
                            }
                            count = 0;
                            break;
                        }
                    }
                    input_array[i].time_work_task.tm_min = stoi (tempMin);      // ������ "���� �����"

                    // ���������� ����
                    for (int k = 0; k < temp2.length (); k++) {
                        if (temp2[k] == '\t') {
                            for (int k2 = 0; k2 < 3; k2++) {
                                if (temp2[k] != ' ') {
                                    k++;
                                    tempDay.insert (count, 1, temp2[k]);
                                    count++;
                                } else {
                                    break;
                                }
                            }
                            count = 0;
                            break;
                        }
                    }
                    input_array[i].time_work_task.tm_mday = stoi (tempDay);     // ������ "���� ����"

                    // ���������� �������
                    for (int k = 0; k < temp2.length (); k++) {
                        if (temp2[k] == ' ') {
                            for (int k2 = 0; k2 < 3; k2++) {
                                k++;
                                if (temp2[k] != ' ') {
                                    tempMonth.insert (count, 1, temp2[k]);
                                    count++;
                                }
                                else {
                                    break;
                                }
                            }
                            count = 0;
                            break;
                        }
                    }
                    input_array[i].time_work_task.tm_mon = stoi (tempMonth);     // ������ "���� �������"

                    // ���������� ����
                    for (int k = temp2.length() - 4; k < temp2.length(); k++) {
                        tempYear.insert (count, 1, temp2[k]);
                        count++;
                    }
                    input_array[i].time_work_task.tm_year = stoi (tempYear);     // ������ "���� �����"
                } // end of  else if (j = 5)
            }
        }
    }       // end of  while
    file_work_task_read.close ();

    getSortingArrayByID(input_array, count_id);
}


// ���������� �������� ������� �� ����������� �� ID
void getSortingArrayByID (WorkTask *sorting_array, int temp_count) {
    WorkTask temp;
    for (int i = 0; i < temp_count; i++) {
        for (int j = 0; j < temp_count - 1; j++) {
            if (sorting_array[j].id > sorting_array[j + 1].id) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
        }
    }
}


// ����� �� ����� ������ �������� �������� ������� ��������� WorkTask �� ��������� ID
void outputSingleElementArrayOfWorkTasks (WorkTask *input_array, int number_task) {

    for (int i = 0; i < getTolalNumbersWorkTasksInFile(); i++) {
        if (input_array[i].id == number_task) {
            cout << "ID ����: \t\t"
                 << input_array[i].id
                 << endl
                 << "�������� ����: \t\t"
                 << input_array[i].name
                 << endl
                 << "��������� ����: \t"
                 << input_array[i].priority
                 << endl
                 << "�������� ����: \t\t"
                 << input_array[i].description
                 << endl
                 << "����� ����������: \t"
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_hour
                 << ":"
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_min
                 << "   "
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_mday
                 << "_"
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_mon
                 << "_"
                 << input_array[i].time_work_task.tm_year
                 << "\n\n\n\n";
        }
    }
}


// ����� �� ����� ������ �������� ��������� ������� ��������� WorkTask
void outputSingleElemenInputArrayOfWorkTasks (WorkTask *input_array, int number, int index_element) {

    for (int i = 0; i < number; i++) {
        if (i == index_element){
            cout << "ID ����: \t\t"
                 << input_array[i].id
                 << endl
                 << "�������� ����: \t\t"
                 << input_array[i].name
                 << endl
                 << "��������� ����: \t"
                 << input_array[i].priority
                 << endl
                 << "�������� ����: \t\t"
                 << input_array[i].description
                 << endl
                 << "����� ����������: \t"
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_hour
                 << ":"
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_min
                 << "   "
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_mday
                 << "_"
                 << setfill ('0')
                 << setw (2)
                 << input_array[i].time_work_task.tm_mon
                 << "_"
                 << input_array[i].time_work_task.tm_year
                 << "\n\n\n\n";
        }
    }
}


// �������� ������ ���� �� ����� ������� ���
void deleteSingleElementArrayofWorkTasks (WorkTask *input_array, int count_id, int number_delete_id) {
    WorkTask *temp_array = new WorkTask[count_id - 1];
    int index_delete_task = 0;
    for (int i = 0; i < count_id; i++) {
        if (input_array[i].id == number_delete_id) {
            index_delete_task = i;
        }
    }

    for (int i = 0; i < index_delete_task; i++) {
        temp_array[i] = input_array[i];
    }

    for (int i = index_delete_task; i < count_id - 1; i++) {
        temp_array[i] = input_array[i+1];
    }
    writeArrayInFile (temp_array, count_id - 1);
    delete[]temp_array;
}


// ������� ����� � ������ � ���� ��������� �������
void writeArrayInFile (WorkTask *input_array, int count_id) {
    ofstream file_work_task_write;
    file_work_task_write.open ("TO_DO_List.txt");

    for (int i = 0; i < count_id; i++) {
        file_work_task_write << "ID ����:         \t"
                             << input_array[i].id
                             << endl
                             << "�������� ����:   \t"
                             << input_array[i].name
                             << endl
                             << "��������� ����:  \t"
                             << input_array[i].priority
                             << endl
                             << "�������� ����:   \t"
                             << input_array[i].description
                             << endl
                             << "����� ����������:\t"
                             << input_array[i].time_work_task.tm_hour
                             << ":"
                             << input_array[i].time_work_task.tm_min
                             << "\t"
                             << input_array[i].time_work_task.tm_mday
                             << " "
                             << input_array[i].time_work_task.tm_mon
                             << " "
                             << input_array[i].time_work_task.tm_year
                             << endl
                             << endl;
    }
    file_work_task_write.close ();
}


// ���������� �������� ������� �� ����������� �� ����������
void getSortingArrayByPriority (WorkTask *sorting_array, int temp_count) {
    WorkTask temp;
    for (int i = 0; i < temp_count; i++) {
        for (int j = 0; j < temp_count - 1; j++) {
            if (sorting_array[j].priority > sorting_array[j + 1].priority) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
        }
    }
}


// ���������� �������� ������� �� ����������� �� ������� ����������
void getSortingArrayByDate (WorkTask *sorting_array, int temp_count) {
    WorkTask temp;
    for (int i = 0; i < temp_count; i++) {
        for (int j = 0; j < temp_count - 1; j++) {
            // ���������� �� �����
            if (sorting_array[j].time_work_task.tm_year > sorting_array[j + 1].time_work_task.tm_year) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // ���������� �� ������� � ��������� ���������� �� �����
            if ((sorting_array[j].time_work_task.tm_mon > sorting_array[j + 1].time_work_task.tm_mon)
                && (sorting_array[j].time_work_task.tm_year >= sorting_array[j + 1].time_work_task.tm_year)) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // ���������� �� ���� � ��������� ���������� �� ����� � �������
            if ((sorting_array[j].time_work_task.tm_mday > sorting_array[j + 1].time_work_task.tm_mday)
                && (sorting_array[j].time_work_task.tm_mon >= sorting_array[j + 1].time_work_task.tm_mon)
                && (sorting_array[j].time_work_task.tm_year >= sorting_array[j + 1].time_work_task.tm_year)) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // ���������� �� ����� � ��������� ���������� �� ����� � ������� � ����
            if ((sorting_array[j].time_work_task.tm_hour > sorting_array[j + 1].time_work_task.tm_hour)
                && (sorting_array[j].time_work_task.tm_mday >= sorting_array[j + 1].time_work_task.tm_mday)
                && (sorting_array[j].time_work_task.tm_mon >= sorting_array[j + 1].time_work_task.tm_mon)
                && (sorting_array[j].time_work_task.tm_year >= sorting_array[j + 1].time_work_task.tm_year)) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // ���������� �� ������� � ��������� ���������� �� ����� � ������� � ���� � �����
            if ((sorting_array[j].time_work_task.tm_min > sorting_array[j + 1].time_work_task.tm_min)
                && (sorting_array[j].time_work_task.tm_hour >= sorting_array[j + 1].time_work_task.tm_hour)
                && (sorting_array[j].time_work_task.tm_mday >= sorting_array[j + 1].time_work_task.tm_mday)
                && (sorting_array[j].time_work_task.tm_mon >= sorting_array[j + 1].time_work_task.tm_mon)
                && (sorting_array[j].time_work_task.tm_year >= sorting_array[j + 1].time_work_task.tm_year)) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
        }
    }
}


// ���������� ������������ ���������� ���� � ������
int returnMaxDayOnMonth (int year, int month) {
    int max_day;
    if (month == 1          // ������
        || month == 3       // ����
        || month == 5       // ���
        || month == 7       // ����
        || month == 8       // ������
        || month == 10      // �������
        || month == 12) {   // �������
        max_day = 31;
    }
    else if (month == 4          // ������
             || month == 6       // ����
             || month == 9       // ��������
             || month == 11) {   // ������
        max_day = 30;
    }
    else if (month == 2) {
        // �������� ������������ �������� ����
        bool year_temp_bool = false;
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0) {
                    year_temp_bool = true;
                }
            } else {
                year_temp_bool = true;
            }
        }

        if (year_temp_bool == true) {
            max_day = 29;
        }
        else {
            max_day = 28;
        }
    }

    return max_day;
}