#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <ctime>
#include <cmath>
using namespace std;
struct Human
{
    string FIO;
    string DateOfBirth;
    unsigned int passportNumber;
    void Fill()
    {
        srand(time(0));
        vector <string> names = { "Nikolay", "Oleg", "Vadim", "Alexander", "Artem" };
        vector <string> surnames = { "Tedeev" , "Karelov", "Kuznetsov", "Galinov", "Chernykh" };
        vector <string> patronymic = { "Andreevich","Alexandrovich", "Mikhailovich", "Petrovich","Dmitryevich" };

        FIO = surnames[rand() % surnames.size()] + " " + names[rand() % names.size()] + " " + patronymic[rand() % patronymic.size()];
        DateOfBirth = to_string(rand() % 28 + 1) + "." + to_string(rand() % 12 + 1) + "." + to_string(rand() % 100 + 1921);
        passportNumber = rand() % 6000 + 1;
    }
};
vector<Human> CreateArray(int size)
{
    srand(time(0));
    vector <Human> result;
    vector <string> names = { "Nikolay", "Oleg", "Vadim", "Alexander", "Artem" };
    vector <string> surnames = { "Tedeev" , "Karelov", "Kuznetsov", "Galinov", "Chernykh" };
    vector <string> patronymic = { "Andreevich","Alexandrovich", "Mikhailovich", "Petrovich","Dmitryevich" };
    for (int i = 0; i < size; i++)
    {
        Human NewPerson;
        NewPerson.FIO = surnames[rand() % surnames.size()] + " " + names[rand() % names.size()] + " " + patronymic[rand() % patronymic.size()];
        NewPerson.DateOfBirth = to_string(rand() % 28 + 1) + "." + to_string(rand() % 12 + 1) + "." + to_string(rand() % 100 + 1921);
        NewPerson.passportNumber = rand() % 6000 + 1;
        result.push_back(NewPerson);
    }
    return result;
}
void Print_list(vector <Human> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "===============================================================" << endl;
        cout << i + 1 << "-й пользователь:" << endl;
        cout << "ФИО:\t" << list[i].FIO << endl;
        cout << "Дата рождения:\t" << list[i].DateOfBirth << endl;
        cout << "Номер паспорта:\t" << list[i].passportNumber << endl;

    }
}
struct Hash_table 
{
public:
    int key;
    vector<Human> human_list;
    void Hash_func(string date, int size)
    {
        float tmp = stoi(date) * 0.34534963;
        float intpart;
        float floatpart;
        floatpart = modf(tmp, &intpart);
        key = trunc(size * floatpart);
    }
    void Add_list(Human person) 
    {
        human_list.push_back(person);
    }
};
void Sort(vector<Hash_table>& list)
{
    for (int step = list.size() / 2; step > 0; step /= 2)
    {
        for (int i = step; i < list.size(); i++)
        {
            for (int j = i; j >= step; j -= step) 
            {
                if (list[j].key < list[j - step].key)
                    swap(list[j], list[j - step]);
            }
        }
    }
}
void Fill_hash_table(vector<Hash_table>& hash_list, vector<Human> list) 
{
    for (int i = 0; i < list.size(); i++) 
    {
        Hash_table tmp;
        tmp.Hash_func(list[i].DateOfBirth, list.size());
        tmp.Add_list(list[i]);
        hash_list.push_back(tmp);
    }
    Sort(hash_list);
    int size = hash_list.size();
    for (int i = 0; i < size - 1;) 
    {
        if (hash_list[i].key == hash_list[i + 1].key)
        {
            hash_list[i].human_list.push_back(hash_list[i + 1].human_list[0]);
            hash_list.erase(hash_list.begin() + i + 1);
            size--;
        }
        else
            i++;
    }
}
void Find_withHash(vector<Hash_table> hash_list, string key_string, int size)
{
    float tmp = stoi(key_string) * 0.34534963;
    float intpart;
    float floatpart;
    floatpart = modf(tmp, &intpart);
    int key_hash = trunc(size * floatpart);
    for (int i = 0; i < hash_list.size(); i++)
    {
        if (hash_list[i].key == key_hash)
        {
            cout << "Элемент с таким ключом найден:" << endl;
            for (int j = 0; j < hash_list[i].human_list.size(); j++) 
            {
                if (key_string == hash_list[i].human_list[j].DateOfBirth) 
                {
                    cout << "Хеш:\t" << hash_list[i].key << endl;
                    cout << "ФИО:\t" << hash_list[i].human_list[j].FIO << endl;
                    cout << "Дата рождения:\t" << hash_list[i].human_list[j].DateOfBirth << endl;
                    cout << "Номер паспорта:\t" << hash_list[i].human_list[j].passportNumber << endl;
                }
            }
            cout << "===========================================================" << endl;
            return;
        }
    }
    cout << "Элементов с таким ключом нет!" << endl;
}
void Find_withHash(vector<Hash_table> hash_list, int key_hash)
{
    for (int i = 0; i < hash_list.size(); i++) 
    {
        if (hash_list[i].key == key_hash) 
        {
            cout << "Элемент(ы) с таким ключом найдены:" << endl;
            Print_list(hash_list[i].human_list);
            cout << "===========================================================" << endl;
            return;
        }
    }
    cout << "Элементов с таким ключом нет!" << endl;
}
void Print_hashTable(vector<Hash_table> hash_list)
{
    for (int i = 0; i < hash_list.size(); i++) 
    {
        cout << "--------------------------------------------------------" << endl;
        cout << i + 1 << "-й хеш:\t" << hash_list[i].key << endl;
        cout << "Элементы с этим хешем:" << endl;
        for (int j = 0; j < hash_list[i].human_list.size(); j++) 
        {
            cout << j + 1 << "-й пользователь:" << endl;
            cout << "ФИО:\t" << hash_list[i].human_list[j].FIO << endl;
            cout << "Дата рождения:\t" << hash_list[i].human_list[j].DateOfBirth << endl;
            cout << "Номер паспорта:\t" << hash_list[i].human_list[j].passportNumber << endl;
            cout << endl;
        }
    }
}
int main() 
{
    setlocale(LC_ALL,"ru");
    int size;
    cin >> size;
    vector <Human> list = CreateArray(size);
    vector<Hash_table> hash_list;
    Print_list(list);
    Fill_hash_table(hash_list, list);
    cout << "===========================================================" << endl << endl;
    cout << "Таблица хешей:" << endl;
    Print_hashTable(hash_list);
    cout << "===========================================================" << endl << endl;

    cout << "===========================================================" << endl << endl;
    string Key;
    cout << "Введите дату, по которой собираетесь искать (через точку, без нулей):\t";
    cin >> Key;
    Find_withHash(hash_list, Key, list.size());
    cout << "===========================================================" << endl << endl;
    int key;
    cout << "Введите хеш, по которому собираетесь искать:\t";
    cin >> key;
    Find_withHash(hash_list, key);
}