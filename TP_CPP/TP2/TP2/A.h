#pragma once

#include <iostream>
#include "A.h"
#include "B.h"

class A
{
public:
	A(double x=0.0, double y=0.0); // Constructeur par défaut
	A(const A&); // Constructeur de recopie
	~A(); // Destructeur éventuellement virtuel
	//A &operator=(const A&); // Opérateur d'affectation
	explicit A(B b);

private:
	double x;
	double y;
};