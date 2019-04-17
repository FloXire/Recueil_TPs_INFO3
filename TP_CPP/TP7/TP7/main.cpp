#include <locale>
#include <string>
#include <iostream>
#include <process.h> // system("pause")
#include "FileHandling.hpp"
#include "CWordStat.h"
#include "CIndex.h"

int main()
{
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse gérer les caratères accentués
	// Par défault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'écrit "fr_FR"
	std::locale::global(std::locale("fr-FR"));

	CWordStat ws;
	IterateOnFileDir<100, 6675>("./textes/output/", ws);
	ws.saveStopWordList();

	/*
	CIndex index("stopWordList.txt");
	IterateOnFileDir<100, 100>("./textes/output/", index);
	index.printVect();
	*/

	system("pause");

	return(EXIT_SUCCESS);
}

