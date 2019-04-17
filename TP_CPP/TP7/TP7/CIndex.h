#pragma once

#include <set>
#include <string>

class CIndex
{
private:
	std::set<std::string> indexSet;

public:
	CIndex();
	CIndex(const char*);
	virtual ~CIndex() = default;
	CIndex(const CIndex &) = default;
	CIndex(CIndex &&) = default;
	CIndex& operator=(const CIndex&) = default;
	CIndex& operator=(CIndex&&) = default;

	void printSet();
};

