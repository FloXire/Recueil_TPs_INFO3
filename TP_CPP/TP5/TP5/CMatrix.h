#pragma once
class CMatrix
{
public:
	CMatrix();
	virtual ~CMatrix() = default;
	CMatrix(const CMatrix &);
	CMatrix(CMatrix &&);
	CMatrix& operator=(const CMatrix&)=default;
	CMatrix& operator=(CMatrix&&)=default;

	int operator()(int, int);
	//CMatrix& operator()(int, int) operator=(int);

private:
	int tab[3][3];
};

