#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main() {
    FILE *file[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        char myfile[16];
        sprintf(myfile, "myfile_%d", i);
        file[i] = fopen(myfile, "w");
        for (int a = 0; a<1000; a++) {
            fprintf(file[i], "%d; ", rand()%100);
        }
        fclose(file[i]);
    }
}