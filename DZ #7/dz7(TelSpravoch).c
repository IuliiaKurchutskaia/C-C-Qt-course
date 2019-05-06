#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char name[21];
    char surname[21];
    char number[12];
} ITEM;

bool add_book(ITEM *NewMan){
    FILE *book=fopen("HandBk.txt","at");
    if (!book){
        printf("Ошибка открытия справочника!");
        return false;
    }

    printf("\n\nВведите имя: ");
    scanf("%s",&NewMan->name);
    printf("Введите фамилию: ");
    scanf("%s",&NewMan->surname);
    printf("Введите номер: ");
    scanf("%s",&NewMan->number);

    char each_string[100];
    sprintf(each_string,"%s, %s: %s\n",NewMan->name,NewMan->surname,NewMan->number);
    fprintf(book,each_string);

    fclose(book);
    return true;
}

bool scan_book(){
    FILE *book=fopen("HandBk.txt","rt");
    if (!book){
        printf("Ошибка открытия справочника!");
        return false;
    }
    char one_string[100];
    int i=0;
    while(one_string[i]!='3') {
        fread((char *) &one_string[i], 1, 1, book);
        i++;
    }
    printf("\n%s",one_string);
    printf("\n%d",i);
    return true;
}


int main (void){
    ITEM NewMan;
    int choice=0;

    printf("Добро пожаловать в справочник\n1.Посмотреть существующие записи\n2.Добавить новую запись\nВы ввели: ");
    scanf("%d",&choice);
    switch(choice){
        case 1: scan_book();
            //printf("\nВывод справочника успешен");
            break;
        case 2:
            add_book(&NewMan);
            printf("\nЗапись успешно добавлена");
            break;
    }
/*
    printf("\n%s",NewMan.name);
    printf("\n%s",NewMan.surname);
    printf("\n%s",NewMan.number);
*/
    return 0;
}