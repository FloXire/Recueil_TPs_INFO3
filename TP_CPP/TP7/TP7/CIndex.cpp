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

void CIndex::printSet()
{
	for (std::set<std::string>::iterator it = indexSet.begin(); it != indexSet.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

