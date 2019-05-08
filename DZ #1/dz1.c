#include<stdio.h>
#include<math.h>

int b=2;

void sec()
{
	int a=5;
	printf("a = %d\n",a*=a);
	printf("b = %d\n\n",++b);
}
double kvadr(int a)
{
	a*=a;
	return a;
}
void main  ()
{
	
	int a = 9;
	char str;
	printf("\nФункция <main>\n \n");
	printf("a = %d\n",a);
	printf("b = %d\n \n",b);
	printf("Функция <sec>\n \n");
	sec();
	printf("Функция <kvadr> b*b: %d\n\n",(int)kvadr(b));
	printf("Остаток от деления 5 на 3: %d\n\n", 5%b);
	printf("Квадратный корень из 3: %f\n \n", sqrt(b));
	printf("Программа написана: Киселевым И.А.\n");
}


