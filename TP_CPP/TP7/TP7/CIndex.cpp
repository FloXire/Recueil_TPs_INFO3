#include "CIndex.h"
#include "ExtractWords.h"

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

CIndex::~CIndex()
{
	for (auto &doc : vectDoc)
	{
		delete doc;
	}
}

void CIndex::operator()(const char *fileName)
{
	SDoc* doc = new SDoc(fileName);
	vectDoc.push_back(doc);

	extractWords(fileName, *this);
}

bool CIndex::operator()(std::string& line, int numLine, int numWord, std::string word)
{
	SDoc* currentDoc = vectDoc[vectDoc.size() - 1];

	if (numLine == 1) // Le num�ro de ligne correspond au titre
	{
		// Si on n'a pas d�j� fix� le titre, on le fait
		if (currentDoc->title != line)
			currentDoc->title = line;
	}

	// Si le mot n'est pas dans la stop word list
	if (indexSet.find(word) == indexSet.end())
	{
		// L'expression suivante est valable si le mot est ou n'est pas d�j� dans wordFrequency
		currentDoc->wordFrequency[word].occurences++;

		// Si le document n'est pas d�j� dans le vecteur de document (acc�s au dernier document associ� au mot car le foncteur est appel� dans l'ordre des documents)
		if (indexMap[word].empty() || indexMap[word][indexMap[word].size() - 1] != currentDoc)
			indexMap[word].push_back(currentDoc);
	}

	return true;
}

void CIndex::calculate()
{
	/* Partie calcul de tous les tfidf */

	for (std::unordered_map<std::string, std::vector<SDoc*>>::iterator itMap = indexMap.begin(); itMap != indexMap.end(); itMap++)
	{
		std::string word = itMap->first;
		// sizeVect est �galement au nombre de documents contenant le mot word
		auto sizeVect = itMap->second.size();
		
		for (std::vector<SDoc*>::iterator itVect = itMap->second.begin(); itVect != itMap->second.end(); itVect++)
		{
			// Calcul du tfidf = nb occurences du mot dans le doc / nb docs contenant ce mot
			(*itVect)->wordFrequency[word].tfidf = static_cast<float>((*itVect)->wordFrequency[word].occurences) / static_cast<float>(sizeVect);
		}

		/* Partie tri du vecteur de document associ� � chaque mot de indexMap */
		std::sort(itMap->second.begin(), itMap->second.end(), [&word](SDoc* doc1, SDoc* doc2) { return doc1->wordFrequency[word].tfidf > doc2->wordFrequency[word].tfidf; });
	}
}

void CIndex::printSet()
{
	for (std::set<std::string>::iterator it = indexSet.begin(); it != indexSet.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

void CIndex::printVect()
{
	for (std::vector<SDoc*>::iterator itVect = vectDoc.begin(); itVect != vectDoc.end(); itVect++)
	{
		std::cout << "--------- Fichier ---------" << std::endl << (*itVect)->name << std::endl << std::endl;
		std::cout << "--------- Titre ---------" << std::endl << (*itVect)->title << std::endl << std::endl;
		
		std::cout << "--------- Mots ---------" << std::endl;

		for (std::map<std::string, SDoc::SStatWord>::iterator itMap = (*itVect)->wordFrequency.begin(); itMap != (*itVect)->wordFrequency.end(); itMap++)
		{
			std::cout << itMap->first << " est apparu " << itMap->second.occurences << " fois" << std::endl;
		}

		std::cout << std::endl << std::endl;
	}
}

void CIndex::printMap()
{
	for (std::unordered_map<std::string, std::vector<SDoc*>>::iterator itMap = indexMap.begin(); itMap != indexMap.end(); itMap++)
	{
		std::cout << "Mot : " << itMap->first << std::endl;
		std::cout << "Documents : " << std::endl << std::endl;

		for (std::vector<SDoc*>::iterator itVect = itMap->second.begin(); itVect != itMap->second.end(); itVect++)
		{
			std::cout << "    - Nom : " << (*itVect)->name << std::endl;
			std::cout << "    - tfidf : " << (*itVect)->wordFrequency[itMap->first].tfidf << std::endl << std::endl;
		}

		std::cout << std::endl;
	}
}

void CIndex::printDocs(const char *strWord)
{
	std::string word(strWord);
	std::cout << "Mot : " << word << std::endl;
	std::cout << "Documents : " << std::endl << std::endl;

	for (std::vector<SDoc*>::iterator itVect = indexMap[word].begin(); itVect != indexMap[word].end(); itVect++)
	{
		std::cout << "    - Emplacement : " << (*itVect)->name << std::endl;
		std::cout << "    - Titre : " << (*itVect)->title << std::endl;
		std::cout << "    - tfidf : " << (*itVect)->wordFrequency[word].tfidf << std::endl << std::endl;
	}

	std::cout << std::endl;
}
