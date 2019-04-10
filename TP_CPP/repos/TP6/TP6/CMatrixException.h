#pragma once

#include <string.h>
#include <iostream>

class CMatrixException
{
public:
	CMatrixException();
	CMatrixException(const int&);
	~CMatrixException();
	CMatrixException(const CMatrixException &) = default;
	CMatrixException(CMatrixException &&) = default;
	CMatrixException& operator=(const CMatrixException&) = default;
	CMatrixException& operator=(CMatrixException&&) = default;

	char* getMessage() const;

	// Les différentes erreurs possibles
	enum CodeErreur
	{
		BadSize,
		Overflow,
		DivisionByZero,
		ImpossibleOperation,
		Unknown
	};

private:
	void setMessage(const char*);
	char* errorMessage;
};


