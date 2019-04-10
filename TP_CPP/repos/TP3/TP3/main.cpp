#include "Complexe.h"
#include <iostream>

int main()
{
	Complexe v1(-5, 0), v2(5.4, -85);
	Complexe v3 = v1 + v2;
	Complexe v4 = v1 - v2;

	v1.homothetie(5);

	std::cout << "v1 : " << v1.getReel() << " " << v1.getIm() << std::endl;
	std::cout << "mod et arg v1 : " << v1.getMod() << " " << v1.getArg() << std::endl;
	std::cout << "v3 : " << v3.getReel() << " " << v3.getIm() << std::endl;
	std::cout << "v4 : " << v4.getReel() << " " << v4.getIm() << std::endl;

	/*if (v1 == v2)
		cout << endl << "Les complexes sont identiques !";
	else
		cout << endl << "Les complexes sont différents !";*/
}