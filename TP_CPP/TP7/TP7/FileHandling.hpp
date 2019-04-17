#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

class FileHandling
{
private:
	struct DirListStruct;
	typedef DirListStruct* DIRHANDLE;
	enum class ETypeResult
	{
		FILE_DIR,
		ONLY_FILE,
		ONLY_DIR
	};

public:
	FileHandling(const char *baseDir);
	FileHandling(const std::string &s) : FileHandling(s.c_str()) {}
	virtual ~FileHandling();
	inline bool GetNext(std::string &str) { return(GetNextElmt(str,ETypeResult::FILE_DIR)); }
	inline bool GetNextFile(std::string &str) { return(GetNextElmt(str,ETypeResult::ONLY_FILE)); }
	inline bool GetNextDir(std::string &str) { return(GetNextElmt(str,ETypeResult::ONLY_DIR)); }

public:
	static bool isFile(const char *file);
	static bool isDir(const char *file);
	static void ParseFileName(const char * const file,std::string &dir,std::string &fileName,std::string &ext);
	static size_t GetFileSize(const char * const file);

private:
	FileHandling(const FileHandling &obj) {}
	FileHandling& operator=(const FileHandling &obj) {}
	bool GetNextElmt(std::string &str,ETypeResult kind);

private:
	DIRHANDLE hDir;
};

template <class F>
void extractWords(const char *file, F& ws)
{
	std::ifstream fileStream;
	std::string line;
	int numLine;
	int numWord;

	fileStream.open(file);

	if (fileStream.fail())
	{
		std::cerr << "Impossible d'accéder au fichier" << std::endl;
		exit(-1);
	}
	else
	{
		numLine = 1;

		while (!fileStream.eof())
		{
			std::getline(fileStream, line);

			std::regex pattern(R"#(\w[\w\-]*)#");
			auto start = std::sregex_iterator(line.begin(), line.end(), pattern);
			auto end = std::sregex_iterator();
			
			numWord = 1;
			for (std::sregex_iterator i = start; i != end; ++i)
			{
				std::smatch match = *i;
				std::string match_str = match.str();

				std::transform(match_str.begin(), match_str.end(), match_str.begin(), tolower);
				if (!ws(line, numLine, numWord, match_str))
					break;

				numWord++;
			}

			numLine++;
		}
	}
}

template <int I = 0, int Limit = 0, class F>
void IterateOnFileDir(const char *baseDir, F& ws)
{
	std::string fileName;

	FileHandling dirList(baseDir);
	int i = 0;
	while ((Limit == 0 || i<Limit) && dirList.GetNextFile(fileName))
	{
		std::string file(baseDir);
		file += fileName;

		//std::cout << file.c_str() << std::endl;
		extractWords(file.c_str(), ws);

		++i;
		if (I != 0 && i%I == 0)
		{
			std::cout << i << " fichier";
			if (i>1) std::cout << 's';
			std::cout << " traité";
			if (i>1) std::cout << 's';
			std::cout << std::endl;
		}
	}
}