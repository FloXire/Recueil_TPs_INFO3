#include <stdio.h>
#include <math.h>

void solv()
{
	int a,b,c;
	printf("coeff de x2 : \n");
	scanf("%d", &a);
	printf("coeff de x : \n");
	scanf("%d", &b);
	printf("constante : \n");
	scanf("%d", &c);
	
	double delta;
	delta = b*b-4*a*c;
	
	if (delta > 0)
	{
		float x1, x2;
		x1 = (-b-sqrt(delta))/(2*a);
		x2 = (-b+sqrt(delta))/(2*a);
		printf("Les racines de %dx²+%dx+%d sont x1 = %lf, x2 = %lf\n", a, b, c, x1, x2);	
	}
	
	else if (delta == 0)
	{
		float x;
		x = (-b)/(2*a);
		printf("La racine de %dx²+%dx+%d est : %lf\n", a, b, c, x);
	}

	else
	{
		printf("Pas de solution réelle\n");
	}
}


int main()
{
	solv();
	return 0;
}
