#include "utils.h"
#include <iostream>

int alpha_to_num(char c)
{
    if ( c >= 'A' && c <= 'J')
        return c - 'A';

    if ( c >= 'a' && c <= 'j')
        return c - 'a';
}

bool is_available_alpha(char c)
{
    if ( c >= 'A' && c <= 'J')
        return true;
    if ( c >= 'a' && c <= 'j')
        return true;

    return false;
}

bool is_available_digit(int c)
{
    int digit = c;
    if (digit >= 0 && digit <= 9)
        return true;

    return false;
}

pair<int, int> utils::ask_pos()
{
    int i;
    cout << "Введите строку: ";
    cin >> i;

    while ( !is_available_digit(i) ) {
        cout << "Вы ввели не число. Введите цифру от 0 до 9" << endl
             << "Введите строку: " << endl;
        cin >> i;
    }

    char j;
    cout << "Введите столбец: ";
    cin >> j;
    while ( !is_available_alpha(j) ){
        cout << "Вы ввели неверный символ. Введите букву от a до j" << endl
             << "Введите столбец: " << endl;
        cin >> j;
    }

    return pair<int, int>{i, alpha_to_num(j)};
}
