/*
//   Программа "СПИСОК ДЕЛ"
//
//   1. Добавление дел.
//   2. Удаление дел.
//   3. Редактирование дел.
//   4. Поиск дел по:
//      - названию;
//      - приоритету;
//      - описанию;
//      - дате и времени исполнения.
//   5. Отображение списка дел:
//      - на день;
//      - на неделю;
//      - на месяц.
//      При отображении должна быть сортировка:
//      - по приоритету;
//      - по дате и времени исполнения.
//
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <conio.h>      // для _getch()

using namespace std;

struct WorkTask                                     // структура одной записи "ДЕЛО"
{
    int id;                                         // порядковый номер дела
    string name;                                    // краткое название дела
    int priority;                                   // приоритет дела
    string description;                             // описание дела
    tm time_work_task;                              // структура данных с ПОЛНЫМИ полями времени, даты, года и т.п.
};

void isFileAvailable ();                                                    // проверка наличия файла с данными
void selectingNumberAction (int *number_action);                            // выбор действия в программе из списка
int getTolalNumbersWorkTasksInFile ();                                      // полученние общего количества ДЕЛ, существующих в файле
int getMaxNumbersWorkTasksInFile (int count_id);                            // полученние МАКСИМАЛЬНОГО ID из существующешл файла
void getTotalArrayWorkTasks (WorkTask *input_array, int count_id);          // получение ВСЕГО массива дел из существующего файла
void writeArrayInFile (WorkTask *input_array, int count_id);                // очистка ФАЙЛА и запись в ФАЙЛ принятого массива
void getSortingArrayByID (WorkTask *sorting_array, int temp_count);         // сортировка входного массива по возрастанию по ID
void getSortingArrayByPriority (WorkTask *sorting_array, int temp_count);   // сортировка входного массива по возрастанию по приоритету
void getSortingArrayByDate (WorkTask *sorting_array, int temp_count);       // сортировка входного массива по возрастанию по времени выполнения
void outputSingleElementArrayOfWorkTasks (WorkTask *input_array, int number_task);      // вывод на экран ОДНОГО ЭЛЕМЕНТА ГЛАВНОГО массива структуры WorkTask
void outputSingleElemenInputArrayOfWorkTasks (WorkTask *input_array, int number, int index_element);    // вывод на экран ОДНОГО ЭЛЕМЕНТА принятого массива структуры WorkTask
void deleteSingleElementArrayofWorkTasks (WorkTask *input_array, int count_id, int number_delete_id);   // удаление одного дела из всего массива дел
int returnMaxDayOnMonth (int year, int month);                                        // возвращает максимальное количество дней в месяце


int main () {
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);

    int number_action;                              // номер действия в программе из списка

    isFileAvailable();                              // проверка наличия файла

    do {
        selectingNumberAction (&number_action);     // ввод действия

        switch (number_action) {

            // добавление ОДНОГО дела в общий список дел
            case 1: {
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();     // счетчик id

                WorkTask new_task;

              // запись ID нового дела
                new_task.id = getMaxNumbersWorkTasksInFile(count_id) + 1;

              // запись НАЗВАНИЯ нового дела
                cout << "Введите краткое название дела: ";
                getchar();                          // НЕ РАБОТАЕТ БЕЗ этой строки в компляторе MSVS
                getline(cin, new_task.name);

              // запись ПРИОРИТЕТА нового дела
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                cout << "Приоритеты дела (1 - 5):\n\n"
                     << "1 - низший приоритет\n"
                     << "....................\n"
                     << "5 - высший приоритет\n\n"
                     << "Введите приоритет дела (1 - 5): ";

                while (!(cin >> new_task.priority)
                       ||  (new_task.priority < 1)
                       ||  (new_task.priority > 5))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\nВведен неправильный приоритет\n"
                         << "Приоритет должен быть от 1 до 5\n\n"
                         << "Введите приоритет дела (1 - 5): ";
                }

              // запись ОПИСАНИЯ нового дела
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                cout << "Введите описание (суть) дела: ";
                getchar();                          // НЕ РАБОТАЕТ БЕЗ этой строки в компляторе MSVS
                getline(cin, new_task.description);

              // запись ГОДА выполнения дела
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                cout << "Введите год выполнения дела (2022 - 2100, формат XXXX): ";

                while (!(cin >> new_task.time_work_task.tm_year)
                       ||  (new_task.time_work_task.tm_year < 2022)
                       ||  (new_task.time_work_task.tm_year > 2100))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\nВведен неправильный номер года\n"
                         << "Год должен быть от 2022 до 2100 в формате XXXX\n\n"
                         << "Введите год выполнения дела (2022 - 2100, формат XXXX): ";
                }

              // запись МЕСЯЦА выполнения дела
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                cout << "Введите номер месяц выполнения дела (1 - 12): ";

                while (!(cin >> new_task.time_work_task.tm_mon)
                       ||  (new_task.time_work_task.tm_mon < 1)
                       ||  (new_task.time_work_task.tm_mon > 12))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\nВведен неправильный номер месяца\n"
                         << "Номер месяца должен быть от 1 до 12\n\n"
                         << "Введите номер месяца выполнения дела (1 - 12): ";
                }

              // запись ДНЯ выполнения дела
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                // проверка 31-дневных месяцев
                if (new_task.time_work_task.tm_mon == 1
                    || new_task.time_work_task.tm_mon == 3
                    || new_task.time_work_task.tm_mon == 5
                    || new_task.time_work_task.tm_mon == 7
                    || new_task.time_work_task.tm_mon == 8
                    || new_task.time_work_task.tm_mon == 10
                    || new_task.time_work_task.tm_mon == 12)
                {
                    cout << "Введите день выполнения дела (1 - 31): ";

                    while (!(cin >> new_task.time_work_task.tm_mday)
                           ||  (new_task.time_work_task.tm_mday < 1)
                           ||  (new_task.time_work_task.tm_mday > 31))
                    {
                        cin.clear();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\nВведен неправильный день месяца\n"
                             << "Количество дней в этом месяце может быть от 1 до 31\n\n"
                             << "Введите день выполнения дела (1 - 31): ";
                    }
                }

                // проверка 30-днвных месяцев
                else if (new_task.time_work_task.tm_mon == 4
                         || new_task.time_work_task.tm_mon == 6
                         || new_task.time_work_task.tm_mon == 9
                         || new_task.time_work_task.tm_mon == 11) {
                    cout << "Введите день выполнения дела (1 - 30): ";

                    while (!(cin >> new_task.time_work_task.tm_mday)
                           ||  (new_task.time_work_task.tm_mday < 1)
                           ||  (new_task.time_work_task.tm_mday > 30))
                    {
                        cin.clear();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\nВведен неправильный день месяца\n"
                             << "Количество дней в этом месяце может быть от 1 до 30\n\n"
                             << "Введите день выполнения дела (1 - 30): ";
                    }
                }

                // проверка ФЕВРАЛЕЙ
                else if (new_task.time_work_task.tm_mon == 2) {
                  // проверка вискостности введенного года
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
                        cout << "Введите день выполнения дела (1 - 29): ";

                        while (!(cin >> new_task.time_work_task.tm_mday)
                               ||  (new_task.time_work_task.tm_mday < 1)
                               ||  (new_task.time_work_task.tm_mday > 29))
                        {
                            cin.clear();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный день месяца\n"
                                 << "Количество дней в этом месяце года может быть от 1 до 29\n\n"
                                 << "Введите день выполнения дела (1 - 29): ";
                        }
                    } else {
                        cout << "Введите день выполнения дела (1 - 28): ";

                        while (!(cin >> new_task.time_work_task.tm_mday)
                               ||  (new_task.time_work_task.tm_mday < 1)
                               ||  (new_task.time_work_task.tm_mday > 28))
                        {
                            cin.clear();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный день месяца\n"
                                 << "Количество дней в этом месяце года может быть от 1 до 28\n\n"
                                 << "Введите день выполнения дела (1 - 28): ";
                        }
                    }
                }       // end of  проверка ФЕВРАЛЕЙ

              // запись ЧАСА выполнения дела
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                cout << "Введите час выполнения дела (0 - 23, формат 24-х часовой): ";

                while (!(cin >> new_task.time_work_task.tm_hour)
                       ||  (new_task.time_work_task.tm_hour < 0)
                       ||  (new_task.time_work_task.tm_hour > 23))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\nВведен неправильный час\n"
                         << "Номер часа должен быть от 0 до 23\n\n"
                         << "Введите час выполнения дела (0 - 23): ";
                }

              // запись МИНУТ выполнения дела
                system ("cls");
                cout << "Добавление нового дела в список задач:\n\n\n";
                cout << "Введите минуты выполнения дела (0 - 59): ";

                while (!(cin >> new_task.time_work_task.tm_min)
                       ||  (new_task.time_work_task.tm_min < 0)
                       ||  (new_task.time_work_task.tm_min > 59))
                {
                    cin.clear();
                    while (cin.get () != '\n') {
                        continue;
                    }
                    cout << "\n\nНет таких минут в часах\n"
                         << "Номер минут должен быть от 0 до 59\n\n"
                         << "Введите минуты выполнения дела (0 - 59): ";
                }

              // запись в ФАЙЛ нового дела
                ofstream file_work_task_write;
                file_work_task_write.open ("TO_DO_List.txt", ios::app);

                file_work_task_write << "ID дела:         \t"
                                     << new_task.id
                                     << endl
                                     << "Название дела:   \t"
                                     << new_task.name
                                     << endl
                                     << "Приоритет дела:  \t"
                                     << new_task.priority
                                     << endl
                                     << "Описание дела:   \t"
                                     << new_task.description
                                     << endl
                                     << "Время выполнения:\t"
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
                cout << "Информация записана в файл !!!\n\n\n";

                system ("pause");
                break;  // out of  case 1
            }           // end of  case 1


            // удаление ОДНОГО дела из общего списка дел
            case 2: {
                system ("cls");
                cout << "Удаление дела из списка задач:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // счетчик id

                if (count_id == 0) {
                    cout << "Нечего удалять !!!\n"
                         << "Список ПУСТ !!!\n\n\n";
                    system("pause");
                    break;
                } else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // массив ВСЕХ дел

                    // получение массива ВСЕХ дел
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // выбор удаляемого дела
                    int delete_task;
                    cout << "Всего в списке "
                         << count_id
                         << " дел:\n\n"
                         << "ID:\tНазвание дела:\n";

                    for (int i = 0; i < count_id; i++) {
                        cout << main_array_tasks[i].id
                             << "\t"
                             << main_array_tasks[i].name
                             << endl;
                    }

                    cout << "\n\nВведите ID (порядковый номер) дела, которое будем удалять: ";
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
                            cout << "\n\nВведен неправильный ID (номер дела) !!!\n"
                                 << "Такого дела не существует !!!\n\n"
                                 << "Введите ID (порядковый номер) дела, которое будем удалять: ";
                        }
                    }

                    cout << "\n\nУдаляем ДЕЛО:\n";
                    outputSingleElementArrayOfWorkTasks(main_array_tasks, delete_task);

                    cout << "Подтвердите удаление этого дела или откажитесь от удаления\n"
                         << "Y = да, N = нет\n\n"
                         << "Введите свой выбор: ";

                    char select = _getch();
                    cout << select;
                    _getch();
                    while ((select != 'Y') && (select != 'N')) {
                        cin.clear();
                        cout << "\n\nПотдверждение не получено !!!\n"
                             << "Y = да, N = нет\n\n"
                             << "Введите свой выбор: ";
                        select = _getch();
                        cout << select;
                        _getch();
                    }

                    if (select == 'Y') {
                        deleteSingleElementArrayofWorkTasks (main_array_tasks, count_id, delete_task);
                        delete[]main_array_tasks;
                        cout << "\n\n\n\nДело удалено !!!\n\n\n";
                        system("pause");
                        break;  // out of  case 2
                    } else {
                        delete[]main_array_tasks;
                        cout << "\n\n\n\nВы отказались от удаления !!!\n\n\n";
                        system ("pause");
                        break;  // out of  case 2
                    }

                    delete[]main_array_tasks;
                }
            }           // end of  case 2


            // редактирование ОДНОГО дела из общего списка дел
            case 3: {
                system ("cls");
                cout << "Редактирование дела из списка задач:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // счетчик id

                if (count_id == 0) {
                    cout << "Нечего редактировать !!!\n"
                        << "Список ПУСТ !!!\n\n\n";
                    system ("pause");
                    break;
                } else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // массив ВСЕХ дел

                    // получение массива ВСЕХ дел
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // выбор дела для редактирования
                    int change_task;
                    cout << "Всего в списке "
                         << count_id
                         << " дел:\n\n"
                         << "ID:\tНазвание дела:\n";

                    for (int i = 0; i < count_id; i++) {
                        cout << main_array_tasks[i].id
                             << "\t"
                             << main_array_tasks[i].name
                             << endl;
                    }

                    cout << "\n\nВведите ID (порядковый номер) дела, которое будем редактировать: ";
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
                            cout << "\n\nВведен неправильный ID (номер дела) !!!\n"
                                 << "Такого дела не существует !!!\n\n"
                                 << "Введите ID (порядковый номер) дела, которое будем редактировать: ";
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
                    cout << "\n\nРедактируем ДЕЛО:\n";
                    outputSingleElementArrayOfWorkTasks (main_array_tasks, change_task);

                    cout << "Какое поле будем редактировать?\n"
                         << "1 - Название дела\n"
                         << "2 - Приоритет дела\n"
                         << "3 - Описание дела\n"
                         << "4 - Время выпонения дела\n\n\n"
                         << "Введите номер поля для редактирования: ";

                    int number_change_action;
                    while (!(cin >> number_change_action) || number_change_action < 1 || number_change_action > 4) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\nНет такого поля !!!\n"
                             << "Смотрим список и пробуем еще раз !!!"
                             << "Введите номер поля для редактирования: ";;
                    }

                    if (number_change_action == 1) {
                        cout << "\n\n\nВведите новое название дела: ";
                        getchar ();                          // НЕ РАБОТАЕТ БЕЗ этой строки в компляторе MSVS
                        getline (cin, main_array_tasks[index_change_task].name);
                    } else if (number_change_action == 2) {
                        cout << "\n\n\nВведите новый приоритет дела (1 - 5):\n\n"
                            << "1 - низший приоритет\n"
                            << "....................\n"
                            << "5 - высший приоритет\n\n"
                            << "Введите новый приоритет дела (1 - 5): ";
                        while (!(cin >> main_array_tasks[index_change_task].priority)
                               || (main_array_tasks[index_change_task].priority < 1)
                               || (main_array_tasks[index_change_task].priority > 5)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный приоритет\n"
                                 << "Приоритет должен быть от 1 до 5\n\n"
                                 << "Введите приоритет дела (1 - 5): ";
                        }
                    } else if (number_change_action == 3) {
                        cout << "\n\n\nВведите новое описание (суть) дела: ";
                        getchar ();                          // НЕ РАБОТАЕТ БЕЗ этой строки в компляторе MSVS
                        getline (cin, main_array_tasks[index_change_task].description);
                    } else if (number_change_action == 4) {
                        cout << "\n\n\nВведите новый год выполнения дела (2022 - 2100, формат XXXX): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_year)
                               || (main_array_tasks[index_change_task].time_work_task.tm_year < 2022)
                               || (main_array_tasks[index_change_task].time_work_task.tm_year > 2100)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный номер года\n"
                                 << "Год должен быть от 2022 до 2100 в формате XXXX\n\n"
                                 << "Введите новый год выполнения дела (2022 - 2100, формат XXXX): ";
                        }

                        // запись МЕСЯЦА выполнения дела
                        cout << "\n\n\nВведите новый номер месяца выполнения дела (1 - 12): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mon)
                               || (main_array_tasks[index_change_task].time_work_task.tm_mon < 1)
                               || (main_array_tasks[index_change_task].time_work_task.tm_mon > 12)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный номер месяца\n"
                                << "Номер месяца должен быть от 1 до 12\n\n"
                                << "Введите новый номер месяца выполнения дела (1 - 12): ";
                        }

                        // запись ДНЯ выполнения дела
                        // проверка 31-дневных месяцев
                        if (main_array_tasks[index_change_task].time_work_task.tm_mon == 1
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 3
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 5
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 7
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 8
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 10
                            || main_array_tasks[index_change_task].time_work_task.tm_mon == 12) {
                            cout << "\n\n\nВведите новый день выполнения дела (1 - 31): ";

                            while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday > 31)) {
                                cin.clear ();
                                while (cin.get () != '\n') {
                                    continue;
                                }
                                cout << "\n\nВведен неправильный день месяца\n"
                                     << "Количество дней в этом месяце может быть от 1 до 31\n\n"
                                     << "Введите новый день выполнения дела (1 - 31): ";
                            }
                        }

                        // проверка 30-днвных месяцев
                        else if (main_array_tasks[index_change_task].time_work_task.tm_mon == 4
                                 || main_array_tasks[index_change_task].time_work_task.tm_mon == 6
                                 || main_array_tasks[index_change_task].time_work_task.tm_mon == 9
                                 || main_array_tasks[index_change_task].time_work_task.tm_mon == 11) {
                            cout << "\n\n\nВведите новый день выполнения дела (1 - 30): ";

                            while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                   || (main_array_tasks[index_change_task].time_work_task.tm_mday > 30)) {
                                cin.clear ();
                                while (cin.get () != '\n') {
                                    continue;
                                }
                                cout << "\n\nВведен неправильный день месяца\n"
                                     << "Количество дней в этом месяце может быть от 1 до 30\n\n"
                                     << "Введите новый день выполнения дела (1 - 30): ";
                            }
                        }

                        // проверка ФЕВРАЛЕЙ
                        else if (main_array_tasks[index_change_task].time_work_task.tm_mon == 2) {
                            // проверка вискостности введенного года
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
                                cout << "\n\n\nВведите новый день выполнения дела (1 - 29): ";

                                while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday > 29)) {
                                    cin.clear ();
                                    while (cin.get () != '\n') {
                                        continue;
                                    }
                                    cout << "\n\nВведен неправильный день месяца\n"
                                         << "Количество дней в этом месяце года может быть от 1 до 29\n\n"
                                         << "Введите новый день выполнения дела (1 - 29): ";
                                }
                            } else {
                                cout << "\n\n\nВведите новый день выполнения дела (1 - 28): ";

                                while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_mday)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday < 1)
                                       || (main_array_tasks[index_change_task].time_work_task.tm_mday > 28)) {
                                    cin.clear ();
                                    while (cin.get () != '\n') {
                                        continue;
                                    }
                                    cout << "\n\nВведен неправильный день месяца\n"
                                         << "Количество дней в этом месяце года может быть от 1 до 28\n\n"
                                         << "Введите новый день выполнения дела (1 - 28): ";
                                }
                            }
                        }       // end of  проверка ФЕВРАЛЕЙ

                      // запись ЧАСА выполнения дела
                        cout << "\n\n\nВведите новый час выполнения дела (0 - 23, формат 24-х часовой): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_hour)
                               || (main_array_tasks[index_change_task].time_work_task.tm_hour < 0)
                               || (main_array_tasks[index_change_task].time_work_task.tm_hour > 23)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный час\n"
                                 << "Номер часа должен быть от 0 до 23\n\n"
                                 << "Введите новый час выполнения дела (0 - 23): ";
                        }

                        // запись МИНУТ выполнения дела
                        cout << "\n\n\nВведите новые минуты выполнения дела (0 - 59): ";

                        while (!(cin >> main_array_tasks[index_change_task].time_work_task.tm_min)
                               || (main_array_tasks[index_change_task].time_work_task.tm_min < 0)
                               || (main_array_tasks[index_change_task].time_work_task.tm_min > 59)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nНет таких минут в часах\n"
                                 << "Номер минут должен быть от 0 до 59\n\n"
                                 << "Введите новые минуты выполнения дела (0 - 59): ";
                        }
                    }   // end of  else if 

                    writeArrayInFile (main_array_tasks, count_id);
                    delete[]main_array_tasks;

                    cout << "\n\n\nДело успешно отредактировано и перезаписано !!!\n\n\n\n";
                    system ("pause");
                }
                break;  // out of  case 3
            }           // end of  case 3


            // поиск дел
            case 4: {
                system ("cls");
                cout << "Поиск дела из списка задач:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // счетчик id

                if (count_id == 0) {
                    cout << "Нечего искать !!!\n"
                        << "Список ПУСТ !!!\n\n\n";
                    system ("pause");
                    break;
                } else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // массив ВСЕХ дел

                    // получение массива ВСЕХ дел
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // выбор дела для поиска
                    cout << "По какому параметру будем искать дело?\n"
                         << "1 - Поиск по названию дела\n"
                         << "2 - Поиск по приоритету дела\n"
                         << "3 - Поиск по описанию дела\n"
                         << "4 - Поиск по дате выполнения дела\n\n\n"
                         << "Введите номер критерия для поиска: ";

                    int index_found_task;
                    while (!(cin >> index_found_task) || index_found_task < 1 || index_found_task > 4) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\nНет такого критерия для поиска !!!\n"
                             << "Смотрим список и пробуем еще раз !!!"
                             << "Введите номер критерия для поиска: ";;
                    }

                    WorkTask found_task;
                    int index_name_task = 0;

                    // поиск по названию дела
                    if (index_found_task == 1) {
                        cout << "\n\n\nВведите название дела для поиска: ";
                        getchar ();                          // НЕ РАБОТАЕТ БЕЗ этой строки в компляторе MSVS
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
                            cout << "\n\nДел с таким названием не найдено !!!\n\n\n\n";
                            system ("pause");
                        } else {
                            system ("pause");
                        }
                    }
                    //поиск по приоритету дела
                    else if (index_found_task == 2) {
                        cout << "\n\n\nВведите приоритет дел для поиска (1 - 5):\n\n"
                             << "1 - низший приоритет\n"
                             << "....................\n"
                             << "5 - высший приоритет\n\n"
                             << "Введите приоритет для поиска (1 - 5): ";
                        while (!(cin >> found_task.priority)
                               || (found_task.priority < 1)
                               || (found_task.priority > 5)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный приоритет\n"
                                 << "Приоритет должен быть от 1 до 5\n\n"
                                 << "Введите правильный приоритет дела для поиска (1 - 5): ";
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
                            cout << "\n\nДел с таким приоритетом не найдено !!!\n\n\n\n";
                            system ("pause");
                        } else {
                            system ("pause");
                        }
                    }
                    //поиск по описанию дела
                    else if (index_found_task == 3) {
                        cout << "\n\n\nВведите полное описание дела для поиска: ";
                        getchar ();                          // НЕ РАБОТАЕТ БЕЗ этой строки в компляторе MSVS
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
                            cout << "\n\nДел с таким описанием не найдено !!!\n\n\n\n";
                            system ("pause");
                        } else {
                            system ("pause");
                        }
                    }
                    // поиск по дате выполнения
                    else if (index_found_task == 4) {
                        cout << "\n\n\nВведите день выполнения дела для поиска (1 - 31): ";
                        while (!(cin >> found_task.time_work_task.tm_mday)
                               || (found_task.time_work_task.tm_mday < 1)
                               || (found_task.time_work_task.tm_mday > 31)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nТаких дней не существует !!!\n"
                                 << "Введите правильный день выполнения дела для поиска (1 - 31): ";
                        }

                        cout << "\n\nВведите номер месяца выполнения дела для поиска (1 - 12): ";
                        while (!(cin >> found_task.time_work_task.tm_mon)
                               || (found_task.time_work_task.tm_mon < 1)
                               || (found_task.time_work_task.tm_mon > 12)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nТакого месяца не существует !!!\n"
                                 << "Введите правильный номер месяца выполнения дела для поиска (1 - 12): ";
                        }

                        cout << "\n\nВведите год выполнения дела для поиска (2022 - 2100): ";
                        while (!(cin >> found_task.time_work_task.tm_year)
                               || (found_task.time_work_task.tm_year < 2022)
                               || (found_task.time_work_task.tm_year > 2100)) {
                            cin.clear ();
                            while (cin.get () != '\n') {
                                continue;
                            }
                            cout << "\n\nВведен неправильный год !!!\n"
                                 << "Введите правильный год выполнения дела для поиска (2022 - 2100): ";
                        }

                        system("cls");
                        cout << "Результаты поиска дела:\n\n";

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
                            cout << "\n\nДел на указанную дату не найдено !!!\n\n\n\n";
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


            // отображение дел по параметрам
            case 5: {
                system ("cls");
                cout << "Отображение списка дел по параметрам:\n\n\n";
                int count_id = getTolalNumbersWorkTasksInFile ();           // счетчик id

                if (count_id == 0) {
                    cout << "Нечего показывать !!!\n"
                         << "Список ПУСТ !!!\n\n\n";
                    system ("pause");
                    break;
                }
                else {
                    WorkTask *main_array_tasks = new WorkTask[count_id];    // массив ВСЕХ дел

                    // получение массива ВСЕХ дел
                    getTotalArrayWorkTasks (main_array_tasks, count_id);

                    // выбор параметра для отображения дел
                    cout << "По какому параметру отобразить дела?\n"
                        << "1 - Отображение дел на сегодня\n"
                        << "2 - Отображение дел на неделю\n"
                        << "3 - Отображение дел на месяц\n\n\n"
                        << "Введите номер параметра для отображения: ";

                    int index_output_task;
                    while (!(cin >> index_output_task) || index_output_task < 1 || index_output_task > 3) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\nНет такого параметра для отображения !!!\n"
                             << "Смотрим список и пробуем еще раз !!!"
                             << "Введите номер параметра для отображения (1 - 3): ";;
                    }
                    system ("cls");


                    cout << "Как отсортировать дела?\n"
                        << "1 - Сортировка по приоритету дел\n"
                        << "2 - Сортировка по времени выполнения дел\n"
                        << "\n\nВведите номер параметра сортировки для отображения: ";

                    int index_sort_output_task;
                    while (!(cin >> index_sort_output_task) || index_sort_output_task < 1 || index_sort_output_task > 2) {
                        cin.clear ();
                        while (cin.get () != '\n') {
                            continue;
                        }
                        cout << "\n\nНет такого параметра для сортировки !!!\n"
                             << "Смотрим список и пробуем еще раз !!!"
                             << "Введите номер параметра сортировки для отображения (1 - 2): ";;
                    }
                    system ("cls");

                    tm local_time;                          // структура данных с ПОЛНЫМИ полями ТЕКУЩЕГО времени, даты, года и т.п.
                    tm local_time_week;                     // ЧЕРЕЗ НЕДЕЛЮ
                    time_t time_now = time (0);             // получение ПОЛНОГО текущего системного времени
                    localtime_s (&local_time, &time_now);   // запись в local_time ТЕКУЩЕГО системного времени, даты, года и т.п.

                    local_time_week = local_time;

                    int index_name_task = 0;

                    // отображения на текущий день
                    if (index_output_task == 1) {
                        cout << "Список дел на сегодня:\n\n\n";

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
                            cout << "\n\nДел на сегодня не обнаружено !!!\n\n\n\n";
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

                            // сортировка по приоритету
                            if (index_sort_output_task == 1) {
                                getSortingArrayByPriority(output_array_task, index_name_task);
                            }
                            // сортировка по времени выполнения
                            else if (index_sort_output_task == 2) {
                                getSortingArrayByDate(output_array_task, index_name_task);
                            }
                            // вывод отсортированного массив на день
                            for (int i = 0; i < index_name_task; i++) {
                                outputSingleElemenInputArrayOfWorkTasks (output_array_task, index_name_task, i);
                            }
                            delete[]output_array_task;
                            system ("pause");
                        }
                    }
                    // отображение на неделю
                    else if (index_output_task == 2) {
                        cout << "Список дел на неделю:\n\n\n";
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
                            cout << "\n\nДел на неделю не обнаружено !!!\n\n\n\n";
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

                            // сортировка по приоритету
                            if (index_sort_output_task == 1) {
                                getSortingArrayByPriority (output_array_task, index_name_task);
                            }
                            // сортировка по времени выполнения
                            else if (index_sort_output_task == 2) {
                                getSortingArrayByDate (output_array_task, index_name_task);
                            }
                            // вывод отсортированного массива на неделю
                            for (int i = 0; i < index_name_task; i++) {
                                outputSingleElemenInputArrayOfWorkTasks (output_array_task, index_name_task, i);
                            }
                            system ("pause");
                        }
                    }
                    // отображение на месяц
                    else if (index_output_task == 3) {
                        cout << "Список дел на месяц:\n\n\n";

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
                            cout << "\n\nДел на месяц не обнаружено !!!\n\n\n\n";
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

                            // сортировка по приоритету
                            if (index_sort_output_task == 1) {
                                getSortingArrayByPriority (output_array_task, index_name_task);
                            }
                            // сортировка по времени выполнения
                            else if (index_sort_output_task == 2) {
                                getSortingArrayByDate (output_array_task, index_name_task);
                            }
                            // вывод отсортированного массива на неделю
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


            // выход из программы
            case 6: {
                system ("cls");
                cout << "\n\n\nСпасибо за пользование программой !!!";
                break;  // out of  case 6
            }           // end of  case 6
        }       // end of  switch (number_action)

    } while (number_action != 6);           // end of MAIN  do - while

    cout << "\n\n\n\n";
    system ("pause");
    return 0;
}   // end of int main()


// проверка наличия файла, если файла нет, то создаёт
void isFileAvailable () {
    ifstream file_work_task_read;                       // создание объекта класса "ifstream" для ЧТЕНИЯ файла
    file_work_task_read.open ("TO_DO_List.txt");        // открытие объекта для ЧТЕНИЯ

    if (file_work_task_read.is_open ()) {               // проверка открытия файла
        file_work_task_read.close();
    } else {
        file_work_task_read.close();
        ofstream file_work_task_write;
        file_work_task_write.open ("TO_DO_List.txt");
        file_work_task_write.close ();
    }
}


// запись номера действия во входящую переменную
void selectingNumberAction (int *number_action) {
    system ("cls");
    cout << "ПРОГРАММА СПИСОК ДЕЛ !!!\n\n\n"
         << "Что делать изволите ???\n\n"
         << "Выберите номер действия из списка:\n"
         << "1 - добавление нового дела\n"
         << "2 - удаление существуюшего дела\n"
         << "3 - редактирование существующего дела\n"
         << "4 - поиск дел\n"
         << "5 - отображение дел по параметрам\n"
         << "6 - выход из программы\n\n\n"
         << "Введите номер действия: ";

    while (!(cin >> *number_action) || *number_action < 1 || *number_action > 6) {
        cin.clear();
        while (cin.get() != '\n') {
            continue;
        }
        cout << "\n\nНет такого действия !!!\n"
             << "Смотрим список и пробуем еще раз !!!"
             << "Введите номер действия: ";;
    }
}


// получение общего количества дел в существующим файле
int getTolalNumbersWorkTasksInFile () {
    string temp;
    int count_id = 0;                           // счетчик количества записей (id)

    ifstream file_work_task_read;
    file_work_task_read.open ("TO_DO_List.txt");
    while (!file_work_task_read.eof ()) {
        getline (file_work_task_read, temp);
        count_id++;
    }
    file_work_task_read.close ();
    count_id /= 6;                              // общее количество существующих записей
    return count_id;
}


// полученние МАКСИМАЛЬНОГО ID из существующешл файла
int getMaxNumbersWorkTasksInFile (int count_id) {
    WorkTask *main_array_tasks = new WorkTask[count_id];    // массив ВСЕХ дел

    // получение массива ВСЕХ дел
    getTotalArrayWorkTasks (main_array_tasks, count_id);

    int MAX = 0;
    for (int i = 0; i < count_id; i++) {
        if (main_array_tasks[i].id > MAX) {
            MAX = main_array_tasks[i].id;
        }
    }
    return MAX;
}


// получение ВСЕГО массива дел из существующего файла
void getTotalArrayWorkTasks (WorkTask *input_array, int count_id) {
    string temp;                                    // считываемая строка из файла
    int length_str_temp;                            // длина считываемой строки

    ifstream file_work_task_read;                   // создание объекта класса "ifstream" для ЧТЕНИЯ файла
    file_work_task_read.open ("TO_DO_List.txt");    // открытие объекта для ЧТЕНИЯ

    while (!file_work_task_read.eof ()) {
        for (int i = 0; i < count_id; i++) {
            for (int j = 1; j <= 6; j++) {
                string temp2;
                getline (file_work_task_read, temp);
                length_str_temp = temp.length ();
                char Q;
                int temp_count = 0;                 // всего символов считать
                int temp_count2 = 0;                // начальный для считывания
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
                    input_array[i].id = stoi (temp2);           // запись "поля id"
                }
                else if (j == 2) {
                    input_array[i].name = temp2;                // запись "поля name"
                }
                else if (j == 3) {
                    input_array[i].priority = stoi (temp2);     // запись "поля priority"
                }
                else if (j == 4) {
                    input_array[i].description = temp2;         // запись "поля description"
                }
                else if (j == 5) {
                    string tempHour;
                    string tempMin;
                    string tempDay;
                    string tempMonth;
                    string tempYear;
                    int count = 0;

                    // заполнение ЧАСОВ
                    for (int k = 0; k < 3; k++) {
                        if (temp2[k] != ':') {
                            tempHour.insert(count, 1, temp2[k]);
                            count++;
                        } else {
                            count = 0;
                            break;
                        }
                    }
                    input_array[i].time_work_task.tm_hour = stoi (tempHour);    // запись "поля часов"

                    // заполнение МИНУТ
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
                    input_array[i].time_work_task.tm_min = stoi (tempMin);      // запись "поля минут"

                    // заполнение ДНЕЙ
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
                    input_array[i].time_work_task.tm_mday = stoi (tempDay);     // запись "поля дней"

                    // заполнение МЕСЯЦЕВ
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
                    input_array[i].time_work_task.tm_mon = stoi (tempMonth);     // запись "поля месяцев"

                    // заполнение ГОДА
                    for (int k = temp2.length() - 4; k < temp2.length(); k++) {
                        tempYear.insert (count, 1, temp2[k]);
                        count++;
                    }
                    input_array[i].time_work_task.tm_year = stoi (tempYear);     // запись "поля годов"
                } // end of  else if (j = 5)
            }
        }
    }       // end of  while
    file_work_task_read.close ();

    getSortingArrayByID(input_array, count_id);
}


// сортировка входного массива по возрастанию по ID
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


// вывод на экран ОДНОГО ЭЛЕМЕНТА ГЛАВНОГО массива структуры WorkTask по принятому ID
void outputSingleElementArrayOfWorkTasks (WorkTask *input_array, int number_task) {

    for (int i = 0; i < getTolalNumbersWorkTasksInFile(); i++) {
        if (input_array[i].id == number_task) {
            cout << "ID дела: \t\t"
                 << input_array[i].id
                 << endl
                 << "Название дела: \t\t"
                 << input_array[i].name
                 << endl
                 << "Приоритет дела: \t"
                 << input_array[i].priority
                 << endl
                 << "Описание дела: \t\t"
                 << input_array[i].description
                 << endl
                 << "Время выполнения: \t"
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


// вывод на экран ОДНОГО ЭЛЕМЕНТА принятого массива структуры WorkTask
void outputSingleElemenInputArrayOfWorkTasks (WorkTask *input_array, int number, int index_element) {

    for (int i = 0; i < number; i++) {
        if (i == index_element){
            cout << "ID дела: \t\t"
                 << input_array[i].id
                 << endl
                 << "Название дела: \t\t"
                 << input_array[i].name
                 << endl
                 << "Приоритет дела: \t"
                 << input_array[i].priority
                 << endl
                 << "Описание дела: \t\t"
                 << input_array[i].description
                 << endl
                 << "Время выполнения: \t"
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


// удаление одного дела из всего массива дел
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


// очистка ФАЙЛА и запись в ФАЙЛ принятого массива
void writeArrayInFile (WorkTask *input_array, int count_id) {
    ofstream file_work_task_write;
    file_work_task_write.open ("TO_DO_List.txt");

    for (int i = 0; i < count_id; i++) {
        file_work_task_write << "ID дела:         \t"
                             << input_array[i].id
                             << endl
                             << "Название дела:   \t"
                             << input_array[i].name
                             << endl
                             << "Приоритет дела:  \t"
                             << input_array[i].priority
                             << endl
                             << "Описание дела:   \t"
                             << input_array[i].description
                             << endl
                             << "Время выполнения:\t"
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


// сортировка входного массива по возрастанию по приоритету
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


// сортировка входного массива по возрастанию по времени выполнения
void getSortingArrayByDate (WorkTask *sorting_array, int temp_count) {
    WorkTask temp;
    for (int i = 0; i < temp_count; i++) {
        for (int j = 0; j < temp_count - 1; j++) {
            // сортировка по годам
            if (sorting_array[j].time_work_task.tm_year > sorting_array[j + 1].time_work_task.tm_year) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // сортировка по месяцам с проверкой сортировки по годам
            if ((sorting_array[j].time_work_task.tm_mon > sorting_array[j + 1].time_work_task.tm_mon)
                && (sorting_array[j].time_work_task.tm_year >= sorting_array[j + 1].time_work_task.tm_year)) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // сортировка по дням с проверкой сортировки по годам И месяцам
            if ((sorting_array[j].time_work_task.tm_mday > sorting_array[j + 1].time_work_task.tm_mday)
                && (sorting_array[j].time_work_task.tm_mon >= sorting_array[j + 1].time_work_task.tm_mon)
                && (sorting_array[j].time_work_task.tm_year >= sorting_array[j + 1].time_work_task.tm_year)) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // сортировка по часам с проверкой сортировки по годам И месяцам И дням
            if ((sorting_array[j].time_work_task.tm_hour > sorting_array[j + 1].time_work_task.tm_hour)
                && (sorting_array[j].time_work_task.tm_mday >= sorting_array[j + 1].time_work_task.tm_mday)
                && (sorting_array[j].time_work_task.tm_mon >= sorting_array[j + 1].time_work_task.tm_mon)
                && (sorting_array[j].time_work_task.tm_year >= sorting_array[j + 1].time_work_task.tm_year)) {
                temp = sorting_array[j + 1];
                sorting_array[j + 1] = sorting_array[j];
                sorting_array[j] = temp;
            }
            // сортировка по минутам с проверкой сортировки по годам И месяцам И дням И часам
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


// возвращает максимальное количество дней в месяце
int returnMaxDayOnMonth (int year, int month) {
    int max_day;
    if (month == 1          // январь
        || month == 3       // март
        || month == 5       // май
        || month == 7       // июль
        || month == 8       // август
        || month == 10      // октябрь
        || month == 12) {   // декабрь
        max_day = 31;
    }
    else if (month == 4          // апрель
             || month == 6       // июнь
             || month == 9       // сентябрь
             || month == 11) {   // ноябрь
        max_day = 30;
    }
    else if (month == 2) {
        // проверка вискостности текущего года
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