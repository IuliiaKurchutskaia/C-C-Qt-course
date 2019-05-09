#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name   [21];
    char surname[21];
    char number [12];
} ITEM;

bool add_book(ITEM *NewMan, const char * file_name) {
    FILE *book = fopen(file_name, "at");
    if (!book) {
        printf("Ошибка открытия справочника!");
        return false;
    }

    printf("\n\nВведите имя: ");
    scanf("%s", NewMan->name);

    printf("Введите фамилию: ");
    scanf("%s", NewMan->surname);

    printf("Введите номер: ");
    scanf("%s", NewMan->number);

    char each_string[60];
    sprintf(each_string, "%s %s %s\n", NewMan->name, NewMan->surname, NewMan->number);
    fprintf(book, "%s", each_string);

    fclose(book);

    return true;
}

bool print_book(const char * file_name) {                                    //Вывод всех имеющихся записей
    FILE *book = fopen(file_name, "rt");

    if (!book)
    {
        printf("Ошибка открытия справочника!");
        return false;
    }

    char one_line[53];

    while (fgets(one_line, sizeof(one_line), book))
        printf("\n%s", one_line);

    fclose(book);

    return true;
}

bool scan_book(const char * file_name) {                                   //Поиск определенной записи
    FILE *book = fopen(file_name, "rt");
    if (!book) {
        printf("Ошибка открытия справочника!");
        return false;
    }
    char find[21];
    char one_line[53];
    bool no_one = true;

    printf("Введите ключевые символы для поиска: ");
    scanf("%s", find);
    while (fgets(one_line, sizeof(one_line), book)) {
        char *succesful = strstr(one_line, find);
        if (succesful != NULL) {
            printf("\n%s", one_line);
            no_one = false;
        }
    }
    if (no_one)
        printf("\nСовпадений не найдено");

    fclose(book);
    return true;
}

void print_help() {
    printf("\n1.Посмотреть существующие записи\n2.Добавить новую запись\n3.Поиск по справочнику\n0.Выйти\nВы ввели: ");
}

int main(void) {
    const char * file_name = "HandBk.txt";
    ITEM NewMan;
    int choice = 0;

    printf("\nДобро пожаловать в справочник");
    print_help();

    scanf("%d", &choice);
    while (choice != 0)
    {
        switch (choice)
        {
            case 1:
                print_book(file_name);
                break;
            case 2:
                add_book(&NewMan,file_name);
                printf("\nЗапись успешно добавлена");
                break;
            case 3:
                scan_book(file_name);
                break;
            default:
                printf("Некорректная команда\n");
                break;
        }
        print_help();

        scanf("%d", &choice);
    }

    return 0;
}