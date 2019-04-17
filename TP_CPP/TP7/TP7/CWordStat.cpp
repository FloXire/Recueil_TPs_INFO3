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
	//std::cout << word << std::endl;
	if (occurences.find(word) == occurences.end())
	{
		occurences.insert(std::make_pair(word, 1));
	}
	else
	{
		occurences[word]++;
	}

	return true;
}

void CWordStat::printMap()
{
	for (std::map<std::string, unsigned int>::iterator it = occurences.begin(); it != occurences.end(); ++it)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

void CWordStat::printVect()
{
	for (std::vector<std::string>::iterator it = sortVect.begin(); it != sortVect.end(); ++it)
	{
		std::cout << *it << " : " << occurences[*it] << std::endl;
	}
}

void CWordStat::sortFrequency()
{
	// Remplissage du vecteur
	for (std::map<std::string, unsigned int>::iterator it = occurences.begin(); it != occurences.end(); ++it)
	{
		sortVect.push_back(it->first);
	}

	std::sort(sortVect.begin(), sortVect.end(), [this](std::string s1, std::string s2) { return this->occurences[s1] > this->occurences[s2]; });
}

void CWordStat::saveStopWordList()
{
	std::ofstream outputFile("stopWordList.txt");

	auto limit1 = sortVect.size() / 5;
	auto limit2 = sortVect.size() / 100;

	std::vector<std::string>::iterator it = sortVect.begin();
	std::vector<std::string>::reverse_iterator rit = sortVect.rbegin();

	// Ecriture des mots appraissant le plus fréquemment dans la stopWordList
	while (occurences[*it] > limit1 && it != sortVect.end())
	{
		outputFile << *it;
		outputFile << "\n";
		it++;
	}

	// Ecriture des mots appraissant le moins fréquemment dans la stopWordList
	while (occurences[*rit] < limit2 && rit != sortVect.rend())
	{
		outputFile << *rit;
		outputFile << "\n";
		rit++;
	}

	outputFile.close();
}
