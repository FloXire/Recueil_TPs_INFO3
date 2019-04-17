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

void CIndex::operator()(const char *fileName)
{
	SDoc* doc = new SDoc(fileName);
	vectDoc.push_back(doc);
}

bool CIndex::operator()(std::string& line, int numLine, int numWord, std::string word)
{
	SDoc* currentDoc = vectDoc[vectDoc.size() - 1];

	if (numLine == 1) // Le numéro de ligne correspond au titre
	{
		// Si on n'a pas déjà fixé le titre, on le fait
		if (currentDoc->title != line)
			currentDoc->title = line;
	}

	// Si le mot n'est pas dans la stop word list
	if (indexSet.find(word) != indexSet.end())
	{
		// Si le mot n'est pas déjà dans wordFrequency
		if (currentDoc->wordFrequency.find(word) == currentDoc->wordFrequency.end())
		{
			currentDoc->wordFrequency.insert(std::make_pair(word, 1));
		}
		else
		{
			currentDoc->wordFrequency[word]++;
		}
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

