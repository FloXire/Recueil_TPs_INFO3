#include "CMatrix.h"
#include "CMatrixException.h"
#include <iostream>


int main()
{
	try
	{
		/* OPERATIONS SUR UNE MATRICE */

		CMatrix<double> mat = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		std::cout << "mat : " << std::endl;
		std::cout << mat << std::endl;

		mat += 2.0;
		std::cout << "mat += 2.0 : " << std::endl;
		std::cout << mat << std::endl;

		mat -= 1;
		std::cout << "mat -= 1 : " << std::endl;
		std::cout << mat << std::endl;

		mat *= 5.0;
		std::cout << "mat *= 5.0 : " << std::endl;
		std::cout << mat << std::endl;

		mat /= 2;
		std::cout << "mat /= 2 : " << std::endl;
		std::cout << mat << std::endl;


		/* PRODUIT SCALAIRE */

		CMatrix<int, 3, 1> vect1 = { 1,2,3 };
		CMatrix<double, 3, 1> vect2 = { 1.1,2.2,3.3 };
		
		std::cout << "vect1 : " << std::endl;
		std::cout << vect1 << std::endl;
		std::cout << "vect2 : " << std::endl;
		std::cout << vect2 << std::endl;

		auto scal = prodScalaire(vect1, vect2);
		std::cout << "Produit scalaire entre vect1 et vect 2 : " << scal << std::endl;


		/* PRODUIT MATRICIEL */

		CMatrix<int, 2, 3> mat1 = { 1, 2, 3, 4, 5, 6 };
		CMatrix<double, 3, 4> mat2 = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10, 11.1, 12.2 };

		std::cout << "mat1 : " << std::endl;
		std::cout << mat1 << std::endl;
		std::cout << "mat2 :" << std::endl;
		std::cout << mat2 << std::endl;

		auto mult = matMult(mat1, mat2);
		std::cout << "Produit matriciel entre mat1 et mat 2: " << std::endl << mult << std::endl;


		// Test du mécanisme d'exception : division par 0
		CMatrix<double> matError = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		matError /= 0;
	}
	catch (const CMatrixException& error)
	{
		std::cout << error.getMessage() << std::endl;
	}

	return 0;
}

