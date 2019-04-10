#include "Complexe.h"
#define _USE_MATH_DEFINES
#include <cmath>


Complexe::Complexe(double reel, double imaginaire)
{
	this->reel = reel;
	this->imaginaire = imaginaire;
}

Complexe::Complexe(const Complexe &C)
{
	this->reel = C.reel;
	this->imaginaire = C.imaginaire;
}

void Complexe::homothetie(double nb)
{
	reel *= nb;
	imaginaire *= nb;
}

double Complexe::getReel(void) const
{
	return reel;
}

double Complexe::getIm(void) const
{
	return imaginaire;
}

double Complexe::getMod(void) const
{
	return sqrt(reel*reel + imaginaire*imaginaire);
}

double Complexe::getArg(void) const
{
	if (imaginaire == 0.0)
	{
		if (reel >= 0)
		{
			return 0;
		}
		else
		{
			return M_PI;
		}
	}
	else if (reel == 0.0)
	{
		if (imaginaire > 0)
		{
			return M_PI / 2;
		}
		else if (imaginaire < 0)
		{
			return -M_PI / 2;
		}
	}
	else
	{
		return atan(imaginaire/reel);
	}
}

Complexe operator+(const Complexe &c1, const Complexe &c2)
{
	return Complexe(c1.getReel() + c2.getReel(), c1.getIm() + c2.getIm());
}

Complexe operator-(const Complexe &c1, const Complexe &c2)
{
	return Complexe(c1.getReel() - c2.getReel(), c1.getIm() - c2.getIm());
}