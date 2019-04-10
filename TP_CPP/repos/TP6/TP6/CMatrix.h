#pragma once

#include "CMatrixException.h"
#include <initializer_list>

template<class T, int L=3, int C=3>
class CMatrix
{
public:
	CMatrix();
	CMatrix(std::initializer_list<T>);
	virtual ~CMatrix() = default;
	CMatrix(const CMatrix &) = default;
	CMatrix(CMatrix &&) = default;
	CMatrix& operator=(const CMatrix&) = default;
	CMatrix& operator=(CMatrix&&) = default;

	T* operator[](int);
	T operator()(int, int) const;
	T& operator()(int, int);

	static void sum(T&, double);
	static void diff(T&, double);
	static void mult(T&, double);
	static void div(T&, double);

	void operator+=(double);
	void operator-=(double);
	void operator*=(double);
	void operator/=(double);

	template<typename F>
	void operators(double, F);

private:
	T tab[L][C];


	/* CLASSES PERMETTANT DE GENERER DES OBJETS FONCTEURS */

	class Mult
	{
	public:
		void operator()(T& arrCase, int b);   // La surcharge de l'opérateur ()
	};

	class Div
	{
	public:
		void operator()(T& arrCase, int b);   // La surcharge de l'opérateur ()
	};

	class Sum
	{
	public:
		void operator()(T& arrCase, int b);   // La surcharge de l'opérateur ()
	};

	class Diff
	{
	public:
		void operator()(T& arrCase, int b);   // La surcharge de l'opérateur ()
	};


	/* FONCTEURS */

	Mult multiplication;
	Div division;
	Sum somme;
	Diff difference;
};

template<class T, int N>
T prodScalaire(const CMatrix<T, N, 1>&, const CMatrix<T, N, 1>&);

template<class T, int L, int C>
CMatrix<T, L, C>::CMatrix()
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < C; j++)
		{
			tab[i][j] = static_cast<T>(0);
		}
	}
}

template<class T, int L, int C>
CMatrix<T, L, C>::CMatrix(std::initializer_list<T> list)
{
	if (list.size() != L * C)
	{
		throw CMatrixException(CMatrixException::CodeErreur::BadSize);
	}


	int i = 0, j = 0;
	for (const auto &elmt : list)
	{
		tab[i][j] = elmt;

		if (j == C - 1)
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
}

// Permet de récuperer la valeur d'une case avec obj[]
template<class T, int L, int C>
T* CMatrix<T, L, C>::operator[](int a)
{
	if (a >= L || a < 0)
	{
		throw CMatrixException(CMatrixException::CodeErreur::Overflow);
	}

	return tab[a];
}

// Permet de récupérer la valeur d'une case avec obj() (l-value)
template<class T, int L, int C>
T CMatrix<T, L, C>::operator()(int i, int j) const
{
	if (i >= L || i < 0 || j >= C || j < 0)
	{
		throw CMatrixException(CMatrixException::CodeErreur::Overflow);
	}

	return tab[i][j];
}

// Permet de transformer une case en r-value pour la modifier
template<class T, int L, int C>
T& CMatrix<T, L, C>::operator()(int i, int j)
{
	if (i >= L || i < 0 || j >= C || j < 0)
	{
		throw CMatrixException(CMatrixException::CodeErreur::Overflow);
	}

	return tab[i][j];
}


/* OPERATIONS SANS LAMBDA */

template<class T, int L, int C>
void CMatrix<T, L, C>::sum(T& caseArr, double a)
{
	caseArr += static_cast<T>(a);
}

template<class T, int L, int C>
void CMatrix<T, L, C>::diff(T& caseArr, double a)
{
	caseArr -= static_cast<T>(a);
}

template<class T, int L, int C>
void CMatrix<T, L, C>::mult(T& caseArr, double a)
{
	caseArr *= static_cast<T>(a);
}

template<class T, int L, int C>
void CMatrix<T, L, C>::div(T& caseArr, double a)
{
	caseArr /= static_cast<T>(a);
}


/* OPERATIONS AVEC LAMBDA */

template<class T, int L, int C>
void CMatrix<T, L, C>::operator+=(double a)
{
	operators(a, [](T& arrCase, double a) { arrCase += static_cast<T>(a); }); // ou operators (a, somme);
}

template<class T, int L, int C>
void CMatrix<T, L, C>::operator-=(double a)
{
	operators(a, [](T& arrCase, double a) { arrCase -= static_cast<T>(a); }); // ou operators (a, difference);
}

template<class T, int L, int C>
void CMatrix<T, L, C>::operator*=(double a)
{
	operators(a, [](T& arrCase, double a) { arrCase *= static_cast<T>(a); }); // ou operators (a, multiplication);
}

template<class T, int L, int C>
void CMatrix<T, L, C>::operator/=(double a)
{
	if (a == 0)
	{
		throw CMatrixException(CMatrixException::CodeErreur::DivisionByZero);
	}

	operators(a, [](T& arrCase, double a) { arrCase /= static_cast<T>(a); }); // ou operators (a, division);
}

// Opérators permet de factoriser le code pour pouvoir réaliser n'importe quelle opération sur l'ensemble des cases de la matrice
template<class T, int L, int C>
template<typename F>
void CMatrix<T, L, C>::operators(double a, F func)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < C; j++)
		{
			func(tab[i][j], a);
		}
	}
}

template<class T, int L, int C>
inline void CMatrix<T, L, C>::Mult::operator()(T & arrCase, int b)
{
	arrCase *= b;
}

template<class T, int L, int C>
inline void CMatrix<T, L, C>::Div::operator()(T & arrCase, int b)
{
	arrCase /= b;
}

template<class T, int L, int C>
inline void CMatrix<T, L, C>::Sum::operator()(T & arrCase, int b)
{
	arrCase += b;
}

template<class T, int L, int C>
inline void CMatrix<T, L, C>::Diff::operator()(T & arrCase, int b)
{
	arrCase -= b;
}

template<class T, int N = 3>
inline T prodScalaire(CMatrix<T, N, 1>& vect1, CMatrix<T, N, 1>& vect2)
{
	T res = 0;
	for (int i = 0; i < N; i++)
	{
		res += vect1[i][0] * vect2[i][0];
	}

	return res;
}

template class CMatrix<int>;
template class CMatrix<double>;