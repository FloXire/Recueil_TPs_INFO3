#include <locale>
#include <string>
#include <iostream>
#include <process.h> // system("pause")
#include "FileHandling.hpp"
#include "CWordStat.h"


int main()
{
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse g�rer les carat�res accentu�s
	// Par d�fault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'�crit "fr_FR"
	std::locale::global(std::locale("fr-FR"));

	CWordStat ws;

	//...
	IterateOnFileDir<10, 10>("./textes/output/", ws);
	//...

	ws.sortFrequency();
	ws.printVect();

	system("pause");

	return(EXIT_SUCCESS);
}

