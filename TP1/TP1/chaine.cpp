#include "stdafx.h"
#include "chaine.h"
#include <cstring>

Chaine::Chaine(const char *str)
{
	string = (char *) str;
	size = strlen(string);
}

unsigned int Chaine::getSize()
{
	return size;
}

const char * Chaine::getString()
{
	return string;
}

void Chaine::addString(const char * str)
{
	strcat_s(string, strlen(str), str);
	size = strlen(string);
}

void Chaine::replaceString(const char * str)
{
	string = (char *) str;
	size = strlen(string);
}
