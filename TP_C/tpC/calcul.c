#include <stdio.h>
#include <math.h>

double dist(double x1, double y1, double x2, double y2)
{
	double result = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
	return result;
}


int main()
{
	double x1 = 4;
	double y1 = 6;
	double x2 = 5;
	double y2 = 8;
	printf("La distance entre les points (%f, %f) et (%f, %f) est %g\n", x1, y1, x2, y2, dist(x1, y1, x2, y2));
	return 0;
}
