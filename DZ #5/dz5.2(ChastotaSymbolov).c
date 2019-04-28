#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char sym;
    int count;
} PAIR;

void add_pair(PAIR p, PAIR old_pairs[], size_t *pairs_size)
{

    int newSize = *pairs_size;
    newSize++;

    old_pairs = realloc(old_pairs, newSize * sizeof(PAIR));
    old_pairs[(*pairs_size)] = p;

    //  Увеличиваем размер
    *pairs_size = newSize;
}

int main(void)
{

    FILE *fp;
    fp = fopen("/home/acer/CLionProjects/Les5/file.txt","rt");
    if (!fp){
        printf("Ошибка открытия файла!\n");
        return 0;
    }
    char symbol;
    size_t actual_read = fread((char*)&symbol,1,1,fp);
    size_t pairs_size = 0;
    PAIR *pairs=(PAIR*) malloc(pairs_size);
    while (actual_read!=0)
    {
        bool found = false;

        for (int i=0; i< pairs_size; i++) {
            if (pairs[i].sym == symbol) {
                pairs[i].count++;
                found = true;
            }
        }
        if ( !found ) {
            PAIR newpair = {symbol, 1};
            add_pair(newpair, pairs, &pairs_size);
        }

        actual_read = fread((char*)&symbol, sizeof(char),1,fp);
    }

    for (int i=0; i<pairs_size; i++)
        printf("%c - %d\n",pairs[i].sym,pairs[i].count);
    fclose(fp);
    return 0;
}