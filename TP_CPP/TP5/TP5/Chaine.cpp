#include "Chaine.h"
#include <string.h>
#include <malloc.h>

#define _CRT_SECURE_NO_WARNINGS

//#define CHAINE_USE_NEW

Chaine::Chaine() :
	String(nullptr),
	Size(0)
{
	AddString("");
}

Chaine::Chaine(const Chaine &chaine) :
String(nullptr),
Size(0)
{
	AddString(chaine.String);
}

Chaine::Chaine(Chaine &&chaine) :
String(chaine.String),
Size(chaine.Size)
{
	chaine.String=nullptr;
	chaine.Size=0;
}

Chaine::Chaine(char *str) :
	String(nullptr),
	Size(0)
{
	AddString(str);
}

Chaine::~Chaine()
{
#ifdef CHAINE_USE_NEW
	delete[] String;
#else
	free(String);
#endif
}

void Chaine::AddString(const char *str)
{
	unsigned int sizeStr;

	sizeStr=(unsigned int)strlen(str);

#ifdef CHAINE_USE_NEW
	char *strTemp;

	strTemp=new char[Size+sizeStr+1];
	if (String) strcpy(strTemp,String);
	delete[] String;
	String=strTemp;
#else
	String=(char*)realloc(String,(Size+sizeStr+1)*sizeof(char));
#endif

	strcpy_s(&String[Size], sizeof &String[Size],str);
	Size+=sizeStr;
}

void Chaine::ReplaceString(const char *str)
{
	Size=(unsigned int)strlen(str);

#ifdef CHAINE_USE_NEW
	char *strTemp;

	strTemp=new char[Size+1];
	delete[] String;
	String=strTemp;
#else
	String=(char*)realloc(String,(Size+1)*sizeof(char));
#endif

	strcpy_s(String, sizeof String, str);
}
