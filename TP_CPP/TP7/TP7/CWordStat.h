#pragma once

#include <map>
#include <string>
#include <vector>

class CWordStat
{
private:
	std::vector<std::string> sortVect;

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
	void printVect();

	void sortFrequency();
	void saveStopWordList();

	std::map<std::string, unsigned int> occurences;
};

