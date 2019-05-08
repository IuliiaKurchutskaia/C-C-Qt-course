#include<stdio.h>

int main ()
{
	int e,b;
	char im,fam;
	printf("Введите инициалы на английском языке через запятую: ");
	scanf("%c,%c",&im,&fam);
	e=im;
	b=fam;
	printf("\nКод введенного символа по таблице ASCII\nDec: %d,%d\nHEX: %x,%x\nOCT: %o,%o \n",e,b,e,b,e,b);
}
