#pragma once

#include <iostream>
#include "A.h"
#include "B.h"

class A
{
public:
	A(double x=0.0, double y=0.0); // Constructeur par d�faut
	A(const A&); // Constructeur de recopie
	~A(); // Destructeur �ventuellement virtuel
	//A &operator=(const A&); // Op�rateur d'affectation
	explicit A(B b);

private:
	double x;
	double y;
};