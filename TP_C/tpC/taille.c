#include <stdio.h>

int main()
{
	int a = 4;
	char b;
	double c;
	long d;
	short e;
	long double f;
	unsigned int g;
	float h;

		
	printf("%ld\n",sizeof(a));
	printf("%ld\n",sizeof(b));
	printf("%ld\n",sizeof(c));
	
	printf("%ld\n",sizeof(d));
	printf("%ld\n",sizeof(e));
	printf("%ld\n",sizeof(f));
	
	printf("%ld\n",sizeof(g));
	printf("%ld\n",sizeof(h));
	return 0;
}
