#include <stdio.h>
#include <string.h>
#include "ext.h"

//Использование volitile и goto
volatile int opt = 1;

void Fn(void) {
    if (opt == 1)
        goto start;
    start:
    printf("Значение переменной opt: %d\n", opt);
}

int main(void)
{
    //    Использование extern
    fun();

    //Использование volitile и goto
    Fn();

    //Использование const
    const char str[] = "Размер переменной opt в байтах:";
    printf(str);

    //Добавим немного магии sizeof()
    printf("%li\n",sizeof(opt));

    //Использование typedef
    typedef float tochka;
    tochka t=1.222;
    printf("\nТип float переименован в tochka и создана переменная f, равная: ");
    printf("%f\n",t);
    return 0;
}