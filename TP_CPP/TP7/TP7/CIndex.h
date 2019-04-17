#pragma once

#include <set>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

class CIndex
{
private:
	std::set<std::string> indexSet;

	struct SDoc
	{
		std::string name;
		std::string title;
		
		struct SStatWord
		{
			float tfidf;
			unsigned int occurences;
		};
		
		std::map<std::string, SStatWord> wordFrequency;

		SDoc(const char* fileName) : name(fileName) {};
	};

	std::vector<SDoc*> vectDoc;
	std::unordered_map<std::string, std::vector<SDoc*>> indexMap;

public:
	CIndex();
	CIndex(const char*);
	virtual ~CIndex();
	CIndex(const CIndex &) = default;
	CIndex(CIndex &&) = default;
	CIndex& operator=(const CIndex&) = default;
	CIndex& operator=(CIndex&&) = default;

	void operator()(const char*);
	bool operator()(std::string&, int, int, std::string);

	void calculate();

	void printSet();
	void printVect();
	void printMap();
	void printDocs(const char*);
};

