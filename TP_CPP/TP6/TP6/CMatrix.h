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

	// Permet d'afficher la matrice complète de façon simple grâce à la surchage de l'opérateur <<
	template<class T, int L, int C>
	friend std::ostream& operator<<(std::ostream&, const CMatrix<T, L, C>&); // Fonction amie qui a accès à l'attribut private tab

	/* 
	Ces 4 fonctions ont été remplacées par des lambda (ou des foncteurs). 
	Le mot clé static permet de pouvoir passer ces fonctions en paramètre d'une autre fonction
	*/
	static void sum(T&, double);
	static void diff(T&, double);
	static void mult(T&, double);
	static void div(T&, double);

	// Surcharge d'opérateurs
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


	/* DECLARATION DES FONCTEURS */

	Mult multiplication;
	Div division;
	Sum somme;
	Diff difference;
};

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

// Initialisation de la matrice avec une initializer_list
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

// Permet de transformer et récupérer une case en r-value pour la modifier
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
	operators(a, [](T& arrCase, double a) { arrCase += static_cast<T>(a); }); // ou operators (a, somme); pour utiliser le foncteur
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

// Produit de deux vecteurs template pouvant être de types différents
template<class T1, class T2, int N1, int N2>
auto prodScalaire(CMatrix<T1, N1, 1>& vect1, CMatrix<T2, N2, 1>& vect2) 
-> decltype(vect1[0][0] * vect2[0][0]) // decltype permet de déterminer le type de retour
{
	if (N1 != N2) // Calcul impossible
	{
		throw CMatrixException(CMatrixException::CodeErreur::ImpossibleOperation);
	}

	decltype(vect1[0][0] * vect2[0][0]) res = 0;

	for (unsigned int i = 0; i < N1; i++)
	{
		res += vect1[i][0] * vect2[i][0];
	}

	return res;
}

/*
L1 et C1 : nombre de lignes et de colonnes de mat1
L2 et C2 : nombre de lignes et de colonnes de mat2
*/
// Produit de deux matrices template pouvant être de types différents
template<class T1, class T2, int L1, int L2, int C1, int C2>
auto matMult(CMatrix<T1, L1, C1>& mat1, CMatrix<T2, L2, C2>& mat2)
-> CMatrix<decltype(mat1[0][0] * mat2[0][0]), L1, C2> // decltype permet de déterminer le type de valeur dans la matrice de retour
{
	if (C1 != L2) // Calcul impossible
	{
		throw CMatrixException(CMatrixException::CodeErreur::ImpossibleOperation);
	}

	CMatrix<decltype(mat1[0][0] * mat2[0][0]), L1, C2> res; // Déclaration de la matrice de type decltype()

	for (unsigned int i = 0; i < L1; i++)
	{
		for (unsigned int j = 0; j < C2; j++)
		{
			res[i][j] = 0;

			for (unsigned int k = 0; k < C1; k++)
			{
				res[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	return res;
}

// Permet de pouvoir afficher la matrice grâce à std::cout << mat << std::endl;
template<class T, int L, int C>
std::ostream& operator<<(std::ostream &stream, const CMatrix<T, L, C> &mat)
{
	for (unsigned int i = 0; i < L; i++)
	{
		stream << "[";
		for (unsigned int j = 0; j < C; j++)
		{
			stream << mat.tab[i][j];
			if (j != C - 1)
			{
				stream << ", ";
			}
		}
		stream << "]" << std::endl;
	}

	return stream;
}

template class CMatrix<int>;
template class CMatrix<double>;
