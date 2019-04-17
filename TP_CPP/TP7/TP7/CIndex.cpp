#include "CIndex.h"
#include <fstream>
#include <iostream>

CIndex::CIndex() : CIndex("stopWordList.txt")
{
}

CIndex::CIndex(const char *file)
{
	std::ifstream inputFile(file);
	std::string word;

	while (inputFile >> word)
	{
		indexSet.insert(word);
	}
}

bool CIndex::operator()(std::string& line, int numLine, int numWord, std::string word)
{
	if (numLine == 1) // Nouveau fichier, on crée une nouvelle instance de SDoc
	{
		SDoc* doc = new SDoc;
		doc->name = "";
		doc->title = "";
	}

	return true;
}

void CIndex::printSet()
{
	for (std::set<std::string>::iterator it = indexSet.begin(); it != indexSet.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

