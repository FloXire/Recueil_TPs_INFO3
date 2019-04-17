#include <locale>
#include <string>
#include <iostream>
#include <process.h> // system("pause")
#include "FileHandling.hpp"
#include "CWordStat.h"
#include "CIndex.h"

/* A �xecuter en release sous visual studio */

int main()
{
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse g�rer les carat�res accentu�s
	// Par d�fault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'�crit "fr_FR"
	std::locale::global(std::locale("fr-FR"));

	
	CWordStat ws;
	IterateOnFileDir<100, 6675>("./textes/", ws);
	ws.saveStopWordList();
	
	
	CIndex index("stopWordList.txt");
	IterateOnFileDir<100, 6675>("./textes/", index);
	index.calculate();
	
	// Changement : la stopWordList a �t� raccourcies aux mots pr�sents plus d'1 fois sur 5 et moins d'1 fois sur 1000
	index.printDocs("croissante"); // Pr�sent gr�ce au changement
	index.printDocs("licorne"); // Pr�sent gr�ce au changement
	index.printDocs("albanie"); // Pr�sent gr�ce au changement
	index.printDocs("corruption"); // Pr�sent gr�ce au changement
	index.printDocs("d�clarations"); // Pr�sent m�me sans le changement
	index.printDocs("centrafrique"); // Reste dans la stopWordList malgr� le changement

	system("pause");

	return(EXIT_SUCCESS);
}

