//Середа Егор ЭН-24, Вариант 25

#define _CRT_SECURE_NO_WARNINGS
#define NAME_LENGTH 31

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <ctime>
#include <intrin.h>
#include <iomanip>

using namespace std;

bool is_digit(const char* S) {
    const char* temp = "0123456789-+";
    unsigned point_count = 0;

    for (int i = 0; i < strlen(S); i++) {
        if ((i > 0) && (S[i] == '+' || S[i] == '-')) return false;
        if (S[i] == '.') {
            point_count++;
            if (point_count > 1) return false;
        }
        if (!strchr(temp, S[i])) return false;
    }
    return true;
}//Функция узнает есть ли число в строке.

class fio
{
    char* surname;
    char* name;
    char* middlename;
    friend class worker;

public:

    fio();
    fio(const fio& a);
    ~fio();

    void define_fio();
    void display_fio();

    char* get_name() { return name; }
    char* get_surname() { return surname; }
    char* get_middlename() { return middlename; }

    void define_surname() { cin >> surname; }
    void define_name() { cin >> name; }
    void define_middlename() { cin >> middlename; }

};
class worker
{
    int otd;
    double okl;
    fio FIO;
    static int CountOfWorkers;

public:
    worker();
    ~worker();

    void CopyWorker(const worker& source);
    void define_worker(fio& fnam);
    void define_worker(const char* name, const char* surname, const char* middlename, int otd, double okl);
    void display();

    void incr_count() { CountOfWorkers++; }
    void decr_count() { CountOfWorkers--; }

    char* get_name() { return FIO.name; }
    char* get_surname() { return FIO.surname; }
    char* get_middlename() { return FIO.middlename; }

    int get_otd() { return otd; }
    double get_okl() { return okl; }

    int get_CountOfWorkers() { return CountOfWorkers; }

    friend istream& operator >> (istream& in, worker& source)
    {
        char buf[40];
        char* buf2;
        double temp = 0;
        int tempcount = 0;
        cout << "Введите отдел: ";
        while (true)
        {
            in >> buf;
            if (is_digit(buf))
            {
                source.otd = atoi(buf);
                break;
            }
            else
            {
                cout << "Введите число." << endl;
                system("pause");
            }
        }

        cout << "Введите оклад: ";
        while (true)
        {
            in >> buf;

            buf2 = strtok(buf, ".");
            char* buf3 = (char*)malloc(strlen(buf2) + 1);
            strcpy(buf3, buf2);


            buf2 = strtok(NULL, ".");
            if (buf2 != NULL)
            {
                char* buf4 = (char*)malloc(strlen(buf2) + 1);
                strcpy(buf4, buf2);
                tempcount = pow(10, strlen(buf4));
                temp = atof(buf4) / (tempcount);
                temp = atof(buf3) + temp;
            }
            else
            {
                temp = atof(buf3);
            }

            source.okl = temp;

            if (source.okl > 0)
            {
                break;
            }
            else { cout << "Неверное значение, введите вновь."; }
        }

        cout << "Введите фамилию: ";
        source.FIO.define_surname();

        cout << "Введите имя: ";
        source.FIO.define_name();

        cout << "Введите отчество: ";
        source.FIO.define_middlename();
        return in;
    }

    friend void operator== (worker& workSource, fio& fioSource)
    {
        int k = 0;

        if (strcmp(workSource.get_name(), fioSource.get_name()) == 0) k++;
        if (strcmp(workSource.get_surname(), fioSource.get_surname()) == 0) k++;
        if (strcmp(workSource.get_middlename(), fioSource.get_middlename()) == 0) k++;
        if (k == 3) workSource.display();
    }
    friend bool operator== (worker& workSource, int otd)
    {
        if (workSource.get_otd() == otd)
            return 1;
        else
            return 0;
    }

    friend ostream& operator << (ostream& out, worker& source)
    {
        return out << "Имя, отчество и фамилия: " << setw(20) << source.get_name() << setw(20) << source.get_surname() << setw(20) << source.get_middlename() << endl << "Номер отдела: " << setw(20) << source.get_otd() << endl << "Оклад: " << setw(20) << source.get_okl() << endl;
    }

    friend struct comp;

};


fio::fio() : name(new char[NAME_LENGTH + 1]), surname(new char[NAME_LENGTH + 1]), middlename(new char[NAME_LENGTH + 1])
{

    name[0] = '\0';
    surname[0] = '\0';
    middlename[0] = '\0';
}//Конструктор ФИО
fio::~fio()
{
    if (name)
    {
        name = nullptr;
    }

    if (surname)
    {
        surname = nullptr;
    }

    if (middlename)
    {
        middlename = nullptr;
    }

}//Деструктор ФИО
fio::fio(const fio& a) : name(new char[NAME_LENGTH + 1]), surname(new char[NAME_LENGTH + 1]), middlename(new char[NAME_LENGTH + 1])
{
    strcpy(name, a.name);
    strcpy(surname, a.surname);
    strcpy(middlename, a.middlename);

};
void fio::define_fio()
{
    char str[NAME_LENGTH];

    cout << "Введите name: ";
    cin >> str;
    name = new char[strlen(str) + 1];
    strcpy(name, str);
    cout << endl;

    cout << "Введите surname: ";
    cin >> str;
    surname = new char[strlen(str) + 1];
    strcpy(surname, str);
    cout << endl;

    cout << "Введите middlename: ";
    cin >> str;
    middlename = new char[strlen(str) + 1];
    strcpy(middlename, str);
    cout << endl;

}//Задает ФИО
void fio::display_fio()
{

    cout << "name:  " << name << endl;
    cout << "surname:  " << surname << endl;
    cout << "middlename:  " << middlename << endl;
    cout << endl;
}


int worker::CountOfWorkers = 0;

worker::worker() : otd(0), okl(0)
{
    CountOfWorkers++;
}
worker::~worker()
{
    CountOfWorkers--;
}
void worker::define_worker(fio& fnam)
{
    char buf[40];
    char* buf2;
    double temp = 0;
    int tempcount = 0;

    FIO.name = fnam.name;
    FIO.surname = fnam.surname;
    FIO.middlename = fnam.middlename;

    cout << "Введите отдел: ";
    while (true)
    {
        cin >> buf;
        if (is_digit(buf))
        {
            otd = atoi(buf);
            break;
        }
        else
        {
            cout << "Введите число." << endl;
            system("pause");
        }
    }
    cout << endl;

    cout << "Введите оклад: ";
    while (true)
    {
        cin >> buf;

        buf2 = strtok(buf, ".");
        char* buf3 = (char*)malloc(strlen(buf2) + 1);
        strcpy(buf3, buf2);


        buf2 = strtok(NULL, ".");
        if (buf2 != NULL)
        {
            char* buf4 = (char*)malloc(strlen(buf2) + 1);
            strcpy(buf4, buf2);
            tempcount = pow(10, strlen(buf4));
            temp = atof(buf4) / (tempcount);
            temp = atof(buf3) + temp;
        }
        else
        {
            temp = atof(buf3);
        }
        okl = temp;
        if (okl > 0)
        {
            break;
        }
        else { cout << "Неверное значение, введите вновь."; }
    }
    cout << endl;
}
void worker::define_worker(const char* Name, const char* Surname, const char* Middlename, int Otd, double Okl)

{
    strcpy(FIO.name, Name);
    strcpy(FIO.surname, Surname);
    strcpy(FIO.middlename, Middlename);
    otd = Otd;
    okl = Okl;
}//Задаем работника
void worker::CopyWorker(const worker& source)
{
    strcpy(FIO.name, source.FIO.name);
    strcpy(FIO.surname, source.FIO.surname);
    strcpy(FIO.middlename, source.FIO.middlename);

    otd = source.otd;
    okl = source.okl;
}//Копируем работника
void worker::display()
{
    cout << endl;
    for (int i = 0; i < 90; i++)
        cout << "~";
    cout << endl;
    cout << setw(15) << "ФИО:" << setw(20) << "|" << get_name() << "|" << setw(20) << "|" << get_surname() << "|" << setw(20) << "|" << get_middlename() << "|";
    cout << endl;
    for (int i = 0; i < 30; i++)
        cout << " - ";
    cout << endl;
    cout << setw(15) << "Отдел и оклад:" << setw(30) << otd << setw(30) << okl;
    cout << endl;
    for (int i = 0; i < 90; i++)
        cout << "~";
    cout << endl;

}//Показываем работника
worker* AddWorker(worker* sourceArr, int amount)
{
    if (!amount)
        sourceArr = new worker[1];
    else
    {
        worker* tempWorkerArr = new worker[amount + 1];
        for (int i = 0; i < amount; i++)
            tempWorkerArr[i].CopyWorker(sourceArr[i]);
        delete[] sourceArr;
        sourceArr = tempWorkerArr;
        return sourceArr;
    }
}//Добавляем объект в массив


void SortByOtd(list<worker> source, int otd)                                     //Фильтр по типу
{
    list<worker>::iterator it;
    int i = 0;
    for (it = source.begin(); it != source.end(); ++it)
    {
        if (*it == otd)
            cout << *it;
    }
}
worker* SortByOkl(worker* sourceArr, int amount)
{
    worker Temp;
    for (int i = 0; i < amount - 1; i++)
    {
        for (int j = 0; j < amount - i - 1; j++)
        {
            if (sourceArr[j].get_okl() < sourceArr[j + 1].get_okl())
            {
                Temp.CopyWorker(sourceArr[j]);
                sourceArr[j].CopyWorker(sourceArr[j + 1]);
                sourceArr[j + 1].CopyWorker(Temp);
            }
        }
    }
    return sourceArr;
}//Сортировка по окладу

void LoadFromFile(list<worker> &Source)                                        //Загрузка из файла
{
    char buf[255];
    int amount = 0;
    worker LoadedObj;

    FILE* fp = fopen("ArrOfWorkers.txt", "r");
    if (fp == NULL) {
        fp = fopen("ArrOfWorkers.txt", "w");
        fclose(fp);
        fp = fopen("ArrOfWorkers.txt", "r");
    }

    ifstream fin;
    ofstream fout;

    while (fgets(buf, 3000, fp) != NULL)
    {
        int otd = 0;
        double okl = 0;
        char* word;

        word = strtok(buf, "|");

        char* name = (char*)malloc(strlen(word) + 1);
        strcpy(name, word);

        word = strtok(NULL, "|");
        char* surname = (char*)malloc(strlen(word) + 1);
        strcpy(surname, word);

        word = strtok(NULL, "|");
        char* middlename = (char*)malloc(strlen(word) + 1);
        strcpy(middlename, word);

        otd = atoi(strtok(NULL, "|"));

        okl = atof(strtok(NULL, "|"));

        LoadedObj.define_worker(name, surname, middlename, otd, okl);

        Source.push_back(LoadedObj);
        amount++;
    }
}
void WriteToFile(list <worker> source, int amount)                                  //Запись в файл
{
    list<worker>::iterator it;
    worker Temp;
    FILE*
        fp = fopen("ArrOfWorkers.txt", "r");
    if (fp == NULL)
    {
        fp = fopen("ArrOfWorkers.txt", "w");
        fclose(fp);
        fp = fopen("ArrOfWorkers.txt", "r");
    }
    fp = fopen("ArrOfWorkers.txt", "w");


    system("cls");
    for (it = source.begin(); it != source.end(); ++it)
    {
        Temp.CopyWorker(*it);
        fprintf(fp, "%s|%s|%s|%i|%f\n", Temp.get_name(), Temp.get_surname(), Temp.get_middlename(), Temp.get_otd(), Temp.get_okl());
    }
}

bool comp (worker& p1, worker& p2)
{
    if (p1.get_okl() > p2.get_okl())return true;
    else return false;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    worker TempList;
    worker LoadedObj;
    list<worker>workerArr;
    fio FIO;
    list<worker>::iterator it;
    list<worker>::iterator it2;
    int  amount = 0, x = 0, z = 0;
    char menu[1];
    char buf[255];

    LoadFromFile(workerArr);



    while (true)
    {
        system("cls");
        cout << "Введите номер пункта меню: " << endl << "1. Добавить поставщика" << "\t" << "2. Показать всё" << "\t" << "3. Фильтр по номеру отдела." << "\t" << "4. Сортировка по окладу." << "\n" << "5. Поиск работников с заданной фамилией." << "6. Стереть объект в конце списка. " << "\t" << "7. Выход." << "\t" << endl;
        strcpy(menu, "0");
        cin >> menu;
        amount = workerArr.size();
        switch (atoi(menu))
        {
        case 1:
        {
            cout << "1. Добавить в конец. 2. Добавить в выбранный индекс. 3. Выход." << endl;
            cin >> menu;
            switch (atoi(menu))
            {
        case 1:
            {

                FIO.define_fio();
                TempList.define_worker(FIO);
                workerArr.push_back(TempList);
                amount++;
                break;

            }

            case 2:
            {
            cout << "Введите номер элемента который хотите заполнить: ";
            cin >> x;
                if ((x > 0) && (x < amount))
                {
                    x = x - 1;
                    it = workerArr.begin();
                    while (z != x) { it++; z++; }
                    FIO.define_fio();
                    TempList.define_worker(FIO);
                    workerArr.insert(it, TempList);
                    break;
                }
                else
                {
                    cout << "Вы вышли за пределы списка." << endl;
                    system("pause");
                    break;
                }

            }

            default:
            {
                break;
            }
            }
        break;
        }

        case 2:
        {
            for (it = workerArr.begin(); it != workerArr.end(); ++it)
            {
                cout << *it << endl;
                for (int i = 0; i < 30; i++)
                    cout << " - ";
                cout << endl;
            }
            system("pause");
            break;
        }

        case 3:
        {
            cout << "Введите номер отдела, чьих сотрудников вы хотите найти: ";
            cin >> x;
            SortByOtd(workerArr, x);
            system("pause");
            break;
        }

        case 4:
        {
            workerArr.sort(comp);
            system("pause");
            break;
        }

        case 5:
        {
            fio temp;
            temp.define_fio();
            for (it = workerArr.begin(); it != workerArr.end(); ++it)
            {
                *it == temp;
            }
            system("pause");
            break;
        }

        case 6:
        {
            it2 = workerArr.end();
            if (amount)
            {

                workerArr.pop_back();
                cout << "Удаление прошло успешно.";
                system("pause");

            }
            else
            {
                cout << "Список итак пуст.";
                system("pause");
            }
            break;
        }

        case 7:
        {
            WriteToFile(workerArr, amount);
            exit(0);
        }

        default:
        {
            system("cls");
            cout << "Неверное значение.";
            break;
        }
        }
    }


    return 0;
}