#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE_OF_ARRAY 1000

int comp (const int *i, const int *j)
{
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
    return (int)time_spent;
}

int standart_sort(){
    int arr[SIZE_OF_ARRAY];
    for (int i=0;i<SIZE_OF_ARRAY;i++)
        arr[i]=0+rand()%10;

    clock_t begin = clock();
    qsort(arr,SIZE_OF_ARRAY,sizeof(int),(int(*) (const void *, const void *)) comp);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC*1000000;
//    return printf("\nВремя стандартной сортивки qsort: %d мкс",(int)time_spent);

    return (int)time_spent;
}

int min_sort(){
    int arr[SIZE_OF_ARRAY];
    int k,x;
    for (int i=0;i<SIZE_OF_ARRAY;i++)
        arr[i]=0+rand()%10;

    clock_t begin = clock();
    for (int i=0; i<SIZE_OF_ARRAY; i++){
        k=i;
        x=arr[i];
        for (int j=i+1; j<SIZE_OF_ARRAY; j++)
            if(arr[j]<x){
                k=j;
                x=arr[j];
            }
        arr[k]=arr[i];
        arr[i]=x;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC*1000000;

    return (int) time_spent;
}

int main () {
    srand(time(NULL));
    printf("Время стандартной сортивки qsort: %d мкс\n",standart_sort());
    printf("Время сортивки \"пузырьком\": %d мкс\n",bubble_sort());
    printf("Время сортивки \"минимумом\": %d мкс\n",min_sort());

    return(0);
}