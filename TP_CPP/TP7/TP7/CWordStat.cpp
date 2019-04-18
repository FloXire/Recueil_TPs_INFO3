#include "CWordStat.h"
#include "ExtractWords.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>

CWordStat::CWordStat()
{
}

void CWordStat::operator()(const char *file)
{
	extractWords(file, *this);
}

bool CWordStat::operator()(std::string& line, int numLine, int numWord, std::string word)
{
	// L'expression suivante est valable si le mot est ou n'est pas déjà dans occurences
	occurences[word]++;
	return true;
}

void CWordStat::printMap()
{
	for (std::map<std::string, unsigned int>::iterator it = occurences.begin(); it != occurences.end(); ++it)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

std::vector<std::pair<std::string, unsigned int>> CWordStat::sortFrequency()
{
	// Vecteur de paires (mot, nombreOccurences)
	std::vector<std::pair<std::string, unsigned int>> sortedVect;

	// Remplissage du vecteur
	for (auto &pair : occurences)
	{
		sortedVect.push_back(pair);
	}

	// Tri du vecteur par occurence décroissante
	std::sort(sortedVect.begin(), sortedVect.end(), [](const std::pair<std::string, unsigned int> &p1, const std::pair<std::string, unsigned int> &p2) { return p1.second > p2.second; });

	return sortedVect;
}

void CWordStat::saveStopWordList()
{
	auto sortedVect = sortFrequency();
	std::ofstream outputFile("stopWordList.txt");

	auto limit1 = sortedVect.size() / 5;
	auto limit2 = sortedVect.size() / 1000;

	auto it = sortedVect.begin();
	auto rit = sortedVect.rbegin();

	// Ecriture des mots apparaissant le plus fréquemment (plus d'1 fois sur 5) dans la stopWordList
	while (occurences[it->first] > limit1 && it != sortedVect.end())
	{
		outputFile << it->first;
		outputFile << "\n";
		it++;
	}

	// Ecriture des mots apparaissant le moins fréquemment (moins d'1 fois sur 1000) dans la stopWordList
	while (occurences[rit->first] <= limit2 && rit != sortedVect.rend())
	{
		outputFile << rit->first;
		outputFile << "\n";
		rit++;
	}

	outputFile.close();
}
