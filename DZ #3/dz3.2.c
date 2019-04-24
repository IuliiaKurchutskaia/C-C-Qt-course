#include <stdio.h>

int main() {
    char ch;
    printf("Введите цифру 0-9: ");
    scanf("%c",&ch);
    char letter = '\0';
    switch(ch)
    {
        case '0':
            letter = 'Z';
            break;
        case '1':
            letter = 'O';
            break;
        case '2':
            letter = 'T';
            break;
        case '3':
            letter = 'T';
            break;
        case '4':
            letter = 'F';
            break;
        case '5':
            letter = 'F';
            break;
        case '6':
            letter = 'S';
            break;
        case '7':
            letter = 'S';
            break;
        case '8':
            letter = 'E';
            break;
        case '9':
            letter = 'N';
            break;
    }
    if (letter != '\0'){
        printf("Первая буква \"%c\"", letter);
    }
    else
    {
        printf("Введена не цифра!");
    }
    return 0;
}