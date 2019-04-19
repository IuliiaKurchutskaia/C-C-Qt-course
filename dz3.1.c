#include <stdio.h>

int main() {
    int i = 0;
    do
        {
        i++;
        printf("До вложенных циклов\n");
        int qt=4;
            while(qt!=0)
            {
                printf("qt = %d\n",qt);
                for(int i = 0; i<2; i++)
                {

                    printf("В цикле for: %d \n",i);
                }
                qt--;
            }
            printf("После вложенных циклов\n \n");
        } while(i<1);
    return 0;
}
