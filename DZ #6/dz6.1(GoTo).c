#include <stdio.h>

int main(void)
{
    int i = 0;
    Pechataem:
    printf("%d ",++i);
    if (i<100)
        goto Pechataem;
    return 0;
}