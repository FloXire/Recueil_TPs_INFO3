#include "A.h"
#include <iostream>

using namespace std;

A::A(double x0, double y0)
{
	cout << "A::A() - Constructeur par défaut de la classe A" << endl;
	x = x0;
	y = y0;
}

A::A(const A &)
{
	cout << "A::A(const A&) - Constructeur de recopie" << endl;
	x = A.x;
	y = A.y;
}

A::~A()
{
	cout << "A::~A() - Destructeur" << endl;
}

A::A(B b)
{
	cout << "A(B)" << endl;

}

/*
A & A::operator=(const A &)
{
	cout << "A::operator=(const A &) - Opérateur d'affectation" << endl;
	return &A;
}
*/