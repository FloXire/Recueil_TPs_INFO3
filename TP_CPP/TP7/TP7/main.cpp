#include <locale>
#include <string>
#include <iostream>
#include "FileHandling.hpp"
#include "CWordStat.h"


int main()
{
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse gérer les caratères accentués
	// Par défault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'écrit "fr_FR"
	std::locale::global(std::locale("fr-FR"));

	CWordStat ws;

	//...
	IterateOnFileDir<1, 10>("./textes/output/", ws);
	//...

	int i;
	std::cin >> i;

	ws.printMap();

	int j;
	std::cin >> j;

	return(EXIT_SUCCESS);
}

