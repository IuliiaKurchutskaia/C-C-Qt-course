#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
#include <time.h>

int create_massiv(int *c, int size) {

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int flag = 0 + rand() % 2;
        if (flag)
            c[i] = 0 + rand() % 48;
        else
            c[i] = 58 + rand() % 128;
    }
}

int out_massiv(const int *c,int size){
    for (int i=0; i<size; i++){
        printf("%c, ",c[i]);
    }
    printf("\n");
}

int main(void)
{
    int size,massiv[size];

    printf("Введите размер массива: ");
    scanf("%d",&size);
    create_massiv(massiv,size);
    printf("Полученный массив выглядит так\n");
    out_massiv(massiv,size);
    return 0;
}