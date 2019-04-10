#include "CMatrix.h"
#include "CMatrixException.h"
#include <iostream>


int main()
{
	
	try
	{
		CMatrix<double> mat = { 1,2,3,4,5,6,7,8,9 };
		mat *= 2;
		std::cout << mat[0][0] << std::endl;
	}
	catch (const CMatrixException& error)
	{
		std::cout << error.getMessage() << std::endl;
	}
	

	try
	{
		CMatrix<int, 3, 1> vect1 = { 1,2,3 };
		CMatrix<int, 3, 1> vect2 = { 1,2,3 };
		int res = prodScalaire<int>(vect1, vect2);
	}
	catch (const CMatrixException& error)
	{
		std::cout << error.getMessage() << std::endl;
	}

	return 0;
}

