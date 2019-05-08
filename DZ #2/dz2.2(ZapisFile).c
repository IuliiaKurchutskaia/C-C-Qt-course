#include<stdio.h>

int main()
{
	FILE *fp;
	char name,family;	
	fp = fopen("txtfile","a");
	printf("Введите инициалы в формате <Имя,Фамилия>: ");
	scanf("%c,%c",&name,&family);
	fprintf(fp,"%c,%c\n",name,family);
	printf("Инициалы добавлены в файл.\n");
}
