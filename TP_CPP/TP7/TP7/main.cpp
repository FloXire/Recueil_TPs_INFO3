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

	/*
	CWordStat ws;
	IterateOnFileDir<100, 6675>("./textes/output/", ws);
	ws.saveStopWordList();
	*/
	
	CIndex index("stopWordList.txt");
	IterateOnFileDir<100, 6675>("./textes/output/", index);
	index.calculate();
	//index.printDocs("eau");
	//index.printDocs("nucl�aire");

	system("pause");

	return(EXIT_SUCCESS);
}

