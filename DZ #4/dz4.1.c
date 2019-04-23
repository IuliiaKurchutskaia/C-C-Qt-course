#include <stdio.h>
#include <stdbool.h>

bool is_day(int day,int month) // проверка корреткного ввода дня
{
    enum mont {january=1,february=2,march,april,may,june,july,august,september,october,november,december};

    if (month == february)
        return ((day > 0) && (day < 29));

    if (
        (month == january) ||
        (month == march)  ||
        (month == may) ||
        (month == july) ||
        (month == august) ||
        (month == october) ||
        (month == december)
        )
        return ((day >= 1)&&(day <= 31));

    else
        return ((day >= 1) && (day <= 30));

}

bool is_month(int month) // проверка корректного ввода месяца
{
    if ((month >= 1) && (month <= 12))
        return true;
    else
        return false;
}

bool is_year(int year) // проверка корректного ввода года. Без проверок на високосность.
{
    if (year <= 2019)

        return true;
    else
        return false;
}

int calculate(int date[],int size) // рекурсивный расчет суммы чисел в дате рождения
{
    if (size <= 0)
        return 0;

    return calculate(date,size-1) + date[size-1];
}

void main() {
    int day,month,year;
    printf("Введите дату рождения <ДД.ММ.ГГГГ>: ");
    scanf("%d.%d.%d", &day, &month, &year);

    int date[] = {day,month,year};
    int result = 0;

    if (is_day(day,month) && is_month(month) && is_year(year)) {
        result = calculate(date, 3);
        printf("Сумма чисел введенной даты: %d", result);
    }
    else printf("\n Ошибка ввода даты.");
}