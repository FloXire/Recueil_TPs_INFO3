#include "B.h"
#include <iostream>

using namespace std;

B::B(double x0, double y0)
{
	cout << "B::B() - Constructeur par défaut de la classe B" << endl;
	x = x0;
	y = y0;
}

B::B(const B &)
{
	cout << "B::B(const B&) - Constructeur de recopie" << endl;
}

B::~B()
{
	cout << "B::~B() - Destructeur" << endl;
}

