#pragma once

#include <set>
#include <string>
#include <map>
#include <vector>

class CIndex
{
private:
	std::set<std::string> indexSet;

	struct SDoc
	{
		std::string name;
		std::string title;
		std::map<std::string, unsigned int> wordFrequency;

		SDoc(const char* fileName) : name(fileName) {};
	};

	std::vector<SDoc*> vectDoc;

public:
	CIndex();
	CIndex(const char*);
	virtual ~CIndex() = default;
	CIndex(const CIndex &) = default;
	CIndex(CIndex &&) = default;
	CIndex& operator=(const CIndex&) = default;
	CIndex& operator=(CIndex&&) = default;

	void operator()(const char*);
	bool operator()(std::string&, int, int, std::string);

	void printSet();
};

