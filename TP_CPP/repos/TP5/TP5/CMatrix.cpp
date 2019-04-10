#include "CMatrix.h"



CMatrix::CMatrix()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tab[i][j] = 0;
		}
	}
}

CMatrix::CMatrix(const CMatrix &)
{
	
}

CMatrix::CMatrix(CMatrix &&)
{
	
}

int CMatrix::operator()(int i, int j)
{
	return tab[i][j];
}



