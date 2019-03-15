#pragma once

class Chaine
{
private:
	char* string;
	unsigned int size;

public:
	Chaine(const char *str);
	unsigned int getSize();
	const char *getString();
	void addString(const char *str);
	void replaceString(const char *str);
};