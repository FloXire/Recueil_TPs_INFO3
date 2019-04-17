#include <locale>
#include <string>
#include <iostream>
#include <process.h> // system("pause")
#include "FileHandling.hpp"
#include "CWordStat.h"
#include "CIndex.h"

/* A éxecuter en release sous visual studio */

int main()
{
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse gérer les caratères accentués
	// Par défault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'écrit "fr_FR"
	std::locale::global(std::locale("fr-FR"));

	
	CWordStat ws;
	IterateOnFileDir<100, 6675>("./textes/", ws);
	ws.saveStopWordList();
	
	
	CIndex index("stopWordList.txt");
	IterateOnFileDir<100, 6675>("./textes/", index);
	index.calculate();
	
	// Changement : la stopWordList a été raccourcies aux mots présents plus d'1 fois sur 5 et moins d'1 fois sur 1000
	index.printDocs("croissante"); // Présent grâce au changement
	index.printDocs("licorne"); // Présent grâce au changement
	index.printDocs("albanie"); // Présent grâce au changement
	index.printDocs("corruption"); // Présent grâce au changement
	index.printDocs("déclarations"); // Présent même sans le changement
	index.printDocs("centrafrique"); // Reste dans la stopWordList malgré le changement

	system("pause");

	return(EXIT_SUCCESS);
}

