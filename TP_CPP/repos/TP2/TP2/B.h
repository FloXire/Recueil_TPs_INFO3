#pragma once

class B
{
public:
	B(double x = 0.0, double y = 0.0); // Constructeur par d�faut
	B(const B&); // Constructeur de recopie
	~B(); // Destructeur �ventuellement virtuel
	//A &operator=(const A&); // Op�rateur d'affectation

private:
	double x;
	double y;
};