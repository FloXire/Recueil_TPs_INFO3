#pragma once

#include <map>
#include <string>


class CWordStat
{
private:
	std::map<std::string, unsigned int> occurences;

public:
	CWordStat();
	virtual ~CWordStat() = default;
	CWordStat(const CWordStat &) = default;
	CWordStat(CWordStat &&) = default;
	CWordStat& operator=(const CWordStat&) = default;
	CWordStat& operator=(CWordStat&&) = default;

	bool operator()(std::string&, int, int, std::string);

	void printMap();
};

