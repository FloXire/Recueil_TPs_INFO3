#pragma once

class Complexe
{
public:
	Complexe() = default;
	Complexe(double reel = 0.0, double imaginaire = 0.0); // Constructeur par défaut
	Complexe(const Complexe&); // Constructeur de recopie
	~Complexe() = default; // Destructeur : on utilise le destructeur par défaut
	Complexe& operator=(const Complexe&) = default;
	Complexe& operator=(Complexe&&) = default;

	friend Complexe operator+(const Complexe&, const Complexe&);
	friend Complexe operator-(const Complexe&, const Complexe&);

	void homothetie(double);
	double getReel(void) const; // Const car ne modifie pas l'objet
	double getIm(void) const;
	double getMod(void) const;
	double getArg(void) const;

private:
	double reel;
	double imaginaire;
};