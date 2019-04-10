#include <iostream>
#include "Chaine.h"
#include "CMatrix.h"

using namespace std;

template<class T> void SwapT(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}


void SwapT(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	CMatrix c;

	cout << c(1, 2) << endl;
	c(1, 2) = 9;
	cout << c(1, 2) << endl;

	int i = 5; int j = 6;
	cout << "i=" << i << " ; j=" << j << endl;
	SwapT<int>(i, j);
	cout << "i=" << i << " ; j=" << j << endl;

	double f = 5.55, g = 6.66;
	cout << "f=" << f << " ; g=" << g << endl;
	SwapT<double>(f, g);
	cout << "f=" << f << " ; g=" << g << endl;
	/*
	Chaine s = "chaine 1", t = "chaine 2";
	cout << "s=" << s << " ; t=" << t << endl;
	SwapT(s, t);
	cout << "s=" << s << " ; t=" << t << endl;
	*/
}