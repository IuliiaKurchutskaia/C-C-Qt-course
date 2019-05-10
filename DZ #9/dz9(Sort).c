//Сортировки и расчет времени их выполнения

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_ARRAY 1000
#define CNT_OF_CALC 10

int comp(const int *i, const int *j) {
    return *i - *j;
}

int bubble_sort() {
    int arr[SIZE_OF_ARRAY];
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
        arr[i] = 0 + rand() % 10;

    clock_t begin = clock();
    for (int i = 0; i < SIZE_OF_ARRAY - 1; i++)
        for (int j = 0; j < SIZE_OF_ARRAY - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = arr[j];
            }
    clock_t end = clock();

    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC * 1000000;

    return (int) time_spent;
}

int standart_sort() {
    int arr[SIZE_OF_ARRAY];
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
        arr[i] = 0 + rand() % 10;

    clock_t begin = clock();
    qsort(arr, SIZE_OF_ARRAY, sizeof(int), (int (*)(const void *, const void *)) comp);
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC * 1000000;

    return (int) time_spent;
}

int min_sort() {
    int arr[SIZE_OF_ARRAY];
    int k, x;
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
        arr[i] = 0 + rand() % 10;

    clock_t begin = clock();
    for (int i = 0; i < SIZE_OF_ARRAY; i++) {
        k = i;
        x = arr[i];
        for (int j = i + 1; j < SIZE_OF_ARRAY; j++)
            if (arr[j] < x) {
                k = j;
                x = arr[j];
            }
        arr[k] = arr[i];
        arr[i] = x;
    }
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC * 1000000;

    return (int) time_spent;
}

int main() {
    srand(time(NULL));
    int arrays[CNT_OF_CALC];

    //Qsort

    double sred = 0;
    for (int i = 0; i < CNT_OF_CALC; i++) {
        arrays[i] = standart_sort();
        sred += arrays[i];
    }
    qsort(arrays, CNT_OF_CALC, sizeof(int), (int (*)(const void *, const void *)) comp);
    printf("Время стандартной сортировки qsort:\n");
    printf("Минимальное время: %d мкс\nСреднее время: %d мкс\nМаксимальное время: %d мкс\n", arrays[0],
           (int) sred / CNT_OF_CALC,
           arrays[CNT_OF_CALC - 1]);

    //Пузырьком

    sred = 0;
    for (int i = 0; i < CNT_OF_CALC; i++) {
        arrays[i] = bubble_sort();
        sred += arrays[i];
    }
    qsort(arrays, CNT_OF_CALC, sizeof(int), (int (*)(const void *, const void *)) comp);
    printf("\nВремя сортивки \"пузырьком\":\n");
    printf("Минимальное время: %d мкс\nСреднее время: %d мкс\nМаксимальное время: %d мкс\n", arrays[0],
           (int) sred / CNT_OF_CALC,
           arrays[CNT_OF_CALC - 1]);

    //Минимумом

    sred = 0;
    for (int i = 0; i < CNT_OF_CALC; i++) {
        arrays[i] = min_sort();
        sred += arrays[i];
    }
    qsort(arrays, CNT_OF_CALC, sizeof(int), (int (*)(const void *, const void *)) comp);
    printf("\nВремя сортивки \"минимумом\":\n");
    printf("Минимальное время: %d мкс\nСреднее время: %d мкс\nМаксимальное время: %d мкс\n", arrays[0],
           (int) sred / CNT_OF_CALC,
           arrays[CNT_OF_CALC - 1]);

    return (0);
}