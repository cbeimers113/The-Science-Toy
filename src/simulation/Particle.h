#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>
#include "StructProperty.h"
#include <string>

typedef unsigned int chemDat;

struct Particle
{
	int type;
	int life, ctype;
	float x, y, vx, vy;
	float temp;
	float pavg[2];
	int flags;
	int tmp;
	int tmp2;
	int element;
	int energy;
	chemDat carbon;
	chemDat hydrogen;
	chemDat oxygen;
	chemDat chlorine;
	chemDat nitrogen;
	chemDat bond;
	chemDat alcohol;
	chemDat bonds;
	chemDat halidePos1;
	chemDat halidePos2;
	chemDat halidePos3;
	chemDat halidePos4;
	bool phenyl;
	bool benzyl;
	bool strongField;
	bool weakField;
	bool electromagneticField;
	bool higgsField;
	int subFlavour;
	std::string flavour;
	float colourCharge;
	float mass;
	unsigned int dcolour;
	static std::vector<StructProperty> GetProperties();
};

#endif
