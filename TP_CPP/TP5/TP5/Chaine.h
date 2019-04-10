#ifndef _Chaine_h
	#define _Chaine_h

class Chaine
{
public:
	Chaine();
	Chaine(char *str);
	Chaine(const Chaine &chaine);
	Chaine(Chaine &&chaine);
	~Chaine();

	inline const char* GetString() const { return(String); }
	inline unsigned int GetSize() const { return(Size); }
	void AddString(const char *str);
	void ReplaceString(const char *str);

private:
	char *String;
	unsigned int Size;
};

#endif
