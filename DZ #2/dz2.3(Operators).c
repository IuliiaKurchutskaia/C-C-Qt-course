#include<stdio.h>

int main()
{
	int a=0,b=0,c=0;
	for(int i=1; i<10; i++)
	{
		
		a++;
		b+=a;
		c+=b;
		b*=i/2;
		c%=i;
		printf("i= %d\na = %d, b = %d, c = %d\n\n",i,a,b,c);
	}
}
