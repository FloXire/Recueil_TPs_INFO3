#include "CMatrixException.h"

CMatrixException::CMatrixException()
{
	errorMessage = nullptr;
}

CMatrixException::CMatrixException(const int& errCode)
{
	errorMessage = nullptr;

	switch (errCode)
	{
		case CodeErreur::BadSize:
		{
			setMessage("[BadSize] Erreur : incoherence avec les dimensions de la matrice");
			break;
		}
		case CodeErreur::Overflow:
		{
			setMessage("[Overflow] Erreur de depassement des dimensions de la matrice");
			break;
		}
		case CodeErreur::DivisionByZero:
		{
			setMessage("[DivisionByZero] Erreur car tentative de division par zero");
			break;
		}
		default:
		{
			setMessage("[Unknown] Erreur inconnue");
			break;
		}
	}
}

CMatrixException::~CMatrixException()
{
	if (errorMessage != nullptr)
		delete[] errorMessage;
}

char* CMatrixException::getMessage() const
{
	return errorMessage;
}

void CMatrixException::setMessage(const char* str)
{
	unsigned int sizeStr = strlen(str);
	if (errorMessage)
	{
		delete[] errorMessage;
		errorMessage = nullptr;
	}

	errorMessage = new char[sizeStr + 1];

	strcpy_s(errorMessage, sizeStr + 1, str); // On set le message d'erreur
}
