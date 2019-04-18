#pragma once

#include <map>
#include <string>
#include <vector>

class CWordStat
{
private:
	std::map<std::string, unsigned int> occurences;
	std::vector<std::pair<std::string, unsigned int>> sortFrequency(); // Tri des clés d'occurences dans un vecteur

public:
	CWordStat();
	virtual ~CWordStat() = default;
	CWordStat(const CWordStat &) = default;
	CWordStat(CWordStat &&) = default;
	CWordStat& operator=(const CWordStat&) = default;
	CWordStat& operator=(CWordStat&&) = default;

	void operator()(const char*);
	bool operator()(std::string&, int, int, std::string);

	void printMap();
	void saveStopWordList(); // Ecriture de la stopWordList dans un fichier
};

