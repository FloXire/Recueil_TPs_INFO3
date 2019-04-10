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
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse g�rer les carat�res accentu�s
	// Par d�fault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'�crit "fr_FR"
	std::locale::global(std::locale("fr-FR"));

	//...
	IterateOnFileDir<100,6675>("./textes/output/",test);
	//...

	int i;
	std::cin >> i;

	return(EXIT_SUCCESS);
}

