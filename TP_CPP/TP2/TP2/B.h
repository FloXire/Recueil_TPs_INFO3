#pragma once

class B
{
public:
	B(double x = 0.0, double y = 0.0); // Constructeur par défaut
	B(const B&); // Constructeur de recopie
	~B(); // Destructeur éventuellement virtuel
	//A &operator=(const A&); // Opérateur d'affectation

private:
	double x;
	double y;
};