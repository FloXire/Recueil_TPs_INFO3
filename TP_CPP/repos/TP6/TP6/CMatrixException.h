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

	enum CodeErreur
	{
		BadSize,
		Overflow,
		DivisionByZero,
		Unknown
	};

private:
	void setMessage(const char*);
	char* errorMessage;
};


