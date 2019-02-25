#include <stdio.h>
#include <math.h>

void permute()
{
	int a,b,c,z;
	
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	z = a;
	a = c;
	c = b;
	b = z;

	printf("A=%d,B=%d,C=%d\n", a,b,c);

}


int main()
{
	permute();
	return 0;
}
