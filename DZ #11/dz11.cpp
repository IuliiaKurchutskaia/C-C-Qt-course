//Менеджер Страничной памяти
//Киселев И.

#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MEMSIZE 500

//Проверка на свободную память для помещения в него нового эл-та
bool chk_is_free(vector <int> &a, int start, int size)
{
    for (int i=0; i<size; i++)
    {
        if (a[i+start]!=0)
            return false;
    }
    return true;
}

//Проверка оставшейся памяти
vector<pair<int,int> > left_mem(vector<int> &a)
{
    int cnt = 0;
    vector<pair<int,int> > result;
    int first = -1;
    for (int i=0; i<a.size(); i++)
    {
        if (a[i]==0)
        {
            if (first == -1)
                first = i;
            cnt++;
        }
        else
        {
            if (first != -1)
            {
                result.push_back(pair<int,int>{first,cnt});
            }
            first = -1;
            cnt = 0;
        }
    }

    if (first != -1)
    {
        result.push_back(pair<int,int>{first,cnt});
    }

    return result;
}
//Получение первого индекса для заполнения
int get_start_pos(vector<int> &a, int size)
{
    vector<pair<int, int> > l_mem = left_mem(a);

    for (int i=0; i<l_mem.size(); i++)
    {
        if (l_mem[i].second >= size)
            return l_mem[i].first;
    }

    return -1;
}
//Создание страницы в памяти
bool fvect(vector<int> &a) //,int size, int num
{
    int size, num;
    cout << "Введите размер \"страницы\": ";
    cin >> size;
    cout << "Введите номер \"страницы\": ";
    cin >> num;

    srand(time(NULL));

    int start_num = get_start_pos(a,size);
    if (start_num == -1)
    {
        return false;
    }

    for(int i=0; i<size; i++)
    {
        a[i+start_num] = num;
    }

    return true;
}
//Дефрагментация памяти
void defrag(vector <int> &a)
{
    sort(a.begin(),a.end(),greater<int>());
}
//Удаление страницы
void free_val(vector <int> &a)
{
    int num;
    cout << "Введите номер удаляемой страницы: ";
    cin >> num;

    for(int i = 0; i < a.size(); i++)
    {
        if (a[i] == num)
            a[i] = 0;
    }
}

int main()
{
    vector <int> a(MEMSIZE);
    int size,num,mod=1;

    for (int i=0; i<MEMSIZE; i++)
        a[i] = 0;
    cout << "Добро пожаловать в Менеджер Памяти" << endl;
while (mod != 0)
{
    cout << "1.Добавить \"страницу\"" << endl;
    cout << "2.Удалить \"страницу\"" << endl;
    cout << "3.Дефрагментировать память" << endl;
    cout << "4.Вывод текущего состояния памяти" << endl;
    cout << "0. Выход" << endl;
    cin >> mod;
    switch(mod)
    {
        case 1:
        {
            if (fvect(a))
                cout << "Заполнение прошло успешно\n";
            else
                cout << "Не достаточно памяти!\n";
            break;
        }
        case 2:
            free_val(a);
            break;
        case 3:
            defrag(a);
            break;
        case 4:
        {
            system("clear");
            for (auto i=0; i<a.size(); i++)
                cout << a[i] << " ";
            cout << endl;
            break;
        }
    }
}
    return 0;
}
