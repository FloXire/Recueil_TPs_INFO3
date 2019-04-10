#include <locale>
#include <iostream>
#include <fstream>
#include "FileHandling.hpp"

void test(const char *file)
{
	std::cout << file << std::endl;
}



int main()
{
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse gérer les caratères accentués
	// Par défault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'écrit "fr_FR"
	std::locale::global(std::locale("fr-FR"));

	//...
	IterateOnFileDir<100,6675>("./textes/output/",test);
	//...

	int i;
	std::cin >> i;

	return(EXIT_SUCCESS);
}

