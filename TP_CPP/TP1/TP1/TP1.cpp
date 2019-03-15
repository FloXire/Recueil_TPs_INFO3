// TP1.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <stdio.h>
#include "chaine.h"

int SommeDesCarres(int n)
{
	int i, somme = 0;

	for (i = 0; i <= n; i++)
		somme += i * i;

	return(somme);
}

int main()
{
	Chaine str("SLT");

	printf_s("%s\n", str.getString());
	printf_s("%d\n", str.getSize());

	str.replaceString("Bonjour");

	printf_s("%s\n", str.getString());
	printf_s("%d\n", str.getSize());


	return 0;
}

