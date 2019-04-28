#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    fp = fopen("/home/acer/CLionProjects/Les5/file.txt", "rt");
    if (!fp) {
        printf("Ошибка открытия файла!\n");
        return 0;
    }

    char symbol;
    int count = 0;
    while (fread((char *) &symbol, sizeof(char), 1, fp))
        count++;

    printf("Размер считанных данных: %d байт", count - 1);

    fclose(fp);
    return 0;
}