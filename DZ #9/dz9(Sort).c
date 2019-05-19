//Сортировки и расчет времени их выполнения

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_ARRAY 10000
#define CNT_OF_CALC 10

int bubble_sort(int *b) {  //пузырьковая сортировка
    clock_t begin = clock();

    for (int i = 0; i < SIZE_OF_ARRAY - 1; i++)
        for (int j = 0; j < SIZE_OF_ARRAY - 1 - i; j++)
            if (b[j] > b[j + 1]) {
                int tmp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = tmp;
            }
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC * 1000;

    return (int) time_spent;
}

int compare(const int *i, const int *j) {
    return *i - *j;
}

int standart_sort(int *q) {  //qsort
    clock_t begin = clock();

    qsort(q, SIZE_OF_ARRAY, sizeof(int), (int (*)(const void *, const void *)) compare);
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC * 100000;

    return (int) time_spent;
}

int min_sort(int *m) { //сортировка мининумом
    int k, x;

    clock_t begin = clock();

    for (int i = 0; i < SIZE_OF_ARRAY; i++) {
        k = i;
        x = m[i];
        for (int j = i + 1; j < SIZE_OF_ARRAY; j++)
            if (m[j] < x) {
                k = j;
                x = m[j];
            }
        m[k] = m[i];
        m[i] = x;
    }
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC * 1000;

    return (int) time_spent;
}

int middle_calc(int *b) {     //вычисление среднего значения
    double sred = 0;
    for (int i = 0; i < CNT_OF_CALC; i++)
        sred += b[i];

    return (int) sred / CNT_OF_CALC;
}

int main() {
    srand(time(NULL));
    int arrays[CNT_OF_CALC];
    int basic_array[SIZE_OF_ARRAY];  //базовый массив
    int b_basic_array[SIZE_OF_ARRAY]; //копия массива №1
    int q_basic_array[SIZE_OF_ARRAY]; //копия массива №1
    int m_basic_array[SIZE_OF_ARRAY]; //копия массива №1
    int cnt_bubble[CNT_OF_CALC]; //время для пузырьковой
    int cnt_qsort[CNT_OF_CALC]; //время для qsort
    int cnt_min[CNT_OF_CALC]; //время для минимума

    for (int cnt = 0; cnt < CNT_OF_CALC; cnt++) {
        for (int i = 0; i < SIZE_OF_ARRAY; i++) {  //заполнение всех исходных массивов
            basic_array[i] = 0 + rand() % 10;
            b_basic_array[i] = basic_array[i];
            q_basic_array[i] = basic_array[i];
            m_basic_array[i] = basic_array[i];
        } //заполнение массивов времени
        cnt_bubble[cnt] = bubble_sort(b_basic_array);
        cnt_qsort[cnt] = standart_sort(q_basic_array);
        cnt_min[cnt] = min_sort(m_basic_array);
    }
    qsort(cnt_bubble, CNT_OF_CALC, sizeof(int), (int (*)(const void *, const void *)) compare);
    qsort(cnt_qsort, CNT_OF_CALC, sizeof(int), (int (*)(const void *, const void *)) compare);
    qsort(cnt_min, CNT_OF_CALC, sizeof(int), (int (*)(const void *, const void *)) compare);

    printf("Время сортировки \"пузырьком\":\n");
    printf("Минимальное время: %d мкс\nСреднее время: %d мкс\nМаксимальное время: %d мкс\n\n", cnt_bubble[0],
           middle_calc(cnt_bubble),
           cnt_bubble[CNT_OF_CALC - 1]);

    printf("Время стандартной сортировки qsort:\n");
    printf("Минимальное время: %d мкс\nСреднее время: %d мкс\nМаксимальное время: %d мкс\n\n", cnt_qsort[0],
           middle_calc(cnt_qsort),
           cnt_qsort[CNT_OF_CALC - 1]);

    printf("Время сортивки \"минимумом\":\n");
    printf("Минимальное время: %d мкс\nСреднее время: %d мкс\nМаксимальное время: %d мкс\n", cnt_min[0],
           middle_calc(cnt_min),
           cnt_min[CNT_OF_CALC - 1]);

    return (0);
}