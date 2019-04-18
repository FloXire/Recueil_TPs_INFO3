#include <locale>
#include <string>
#include <iostream>
#include <process.h> // system("pause")
#include <chrono>
#include <thread>

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
	
	unsigned int nbCores = std::thread::hardware_concurrency();

	std::cout << std::endl << "Votre processeur possède " << nbCores << " coeurs." << std::endl;

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	index.launchThreadCalc(nbCores);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << std::endl << "Temps de tri de l'index avec " << nbCores << " threads : " << diff.count() << " secondes." << std::endl << std::endl;

	// Temps moyen sur 100 tris sans multithreading : 0.647016 secondes

	// 2 threads : 0.348953 secondes
	// 3 threads : 0.270049 secondes 
	// 4 threads : 0.21176 secondes (4 = nbCores de mon processeur)
	// 5 threads : 0.224528 secondes
	// 6 threads : 0.235593 secondes

	// Changement : la stopWordList a été raccourcie aux mots présents plus d'1 fois sur 5 et moins d'1 fois sur 1000
	index.printDocs("croissante"); // Présent grâce au changement
	index.printDocs("licorne"); // Présent grâce au changement
	index.printDocs("albanie"); // Présent grâce au changement
	index.printDocs("corruption"); // Présent grâce au changement
	index.printDocs("déclarations"); // Présent même sans le changement
	index.printDocs("centrafrique"); // Reste dans la stopWordList malgré le changement

	system("pause");

	return(EXIT_SUCCESS);
}

