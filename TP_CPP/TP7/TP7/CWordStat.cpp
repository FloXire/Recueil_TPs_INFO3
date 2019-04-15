#include "CWordStat.h"
#include <iostream>
#include <utility>

CWordStat::CWordStat()
{
}

bool CWordStat::operator()(std::string& line, int numLine, int numWord, std::string word)
{
	std::cout << word << std::endl;
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
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
}
