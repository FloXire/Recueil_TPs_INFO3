#pragma once

#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

template <class F>
void extractWords(const char *file, F& func)
{
	std::ifstream fileStream(file);
	std::string line;
	std::regex pattern(R"#(\w[\w\-]*)#");
	int numLine;
	int numWord;

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
			auto start = std::sregex_iterator(line.begin(), line.end(), pattern);
			auto end = std::sregex_iterator();

			numWord = 1;
			for (std::sregex_iterator i = start; i != end; ++i)
			{
				std::smatch match = *i;
				std::string match_str = match.str();

				std::transform(match_str.begin(), match_str.end(), match_str.begin(), tolower);
				if (!func(line, numLine, numWord, match_str))
					break;

				numWord++;
			}

			numLine++;
		}
	}
}