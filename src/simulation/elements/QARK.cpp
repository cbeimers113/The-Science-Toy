#include "simulation/Elements.h"
#include <string>
#include <algorithm>

//#TPT-Directive ElementClass Element_QARK PT_QARK 187
Element_QARK::Element_QARK()
{
	Identifier = "DEFAULT_PT_QARK";
	Name = "QARK";
	Colour = PIXPACK(0xCFCFCF);
	MenuVisible = 1;
	MenuSection = SC_QUANTUM;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = -.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 61;
	Description = "Quark. Has unique flavour, colour charge, mass, and energy level.";

	State = ST_GAS;
	Properties = TYPE_ENERGY | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_QARK::update;
	Graphics = &Element_QARK::graphics;
}

//#TPT-Directive ElementHeader Element_QARK static int update(UPDATE_FUNC_ARGS)
int Element_QARK::update(UPDATE_FUNC_ARGS)
{
	parts[i].element = 1;
	parts[i].energy = parts[i].mass*parts[i].temp + parts[i].vx*parts[i].vx + parts[i].vy*parts[i].vy;
	int r, rx, ry;
	for (rx = -3; rx <= 3; rx++)
		for (ry = -3; ry <= 3; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				std::string data = parts[i].flavour;
				std::transform(data.begin(), data.end(), data.begin(), ::tolower);
				if (parts[i].flavour != "up" || parts[i].flavour != "down" || parts[i].flavour != "charm" || parts[i].flavour != "strange" || parts[i].flavour != "top" || parts[i].flavour != "bottom"){
					int q = rand() % 6;
					parts[i].flavour = q == 0 ? "Up" : q == 1 ? "Down" : q == 2 ? "Charm" : q == 3 ? "Strange" : q == 4 ? "Top" : "Bottom";
				}
				if (parts[i].subFlavour < 0)parts[i].subFlavour = 0;
				if (parts[i].subFlavour > 5)parts[i].subFlavour = 5;
				switch (parts[i].subFlavour){
				case 0:
					if (parts[i].flavour != "Up"){
						parts[i].flavour = "Up";
						parts[i].mass = 2.3f + (rand() % 12 - 6) / 10.0f;
						parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
						parts[i].life = 150;
					}
					break;
				case 1:
					if (parts[i].flavour != "Down"){
						parts[i].flavour = "Down";
						parts[i].mass = 4.8f + (rand() % 8 - 4) / 10.0f;
						parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
						parts[i].life = 150;
					}
					break;
				case 2:
					if (parts[i].flavour != "Charm"){
						parts[i].flavour = "Charm";
						parts[i].mass = 1290.0f + (rand() % 1600 - 800) / 10.0f;
						parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
						parts[i].life = 100;
					}
					break;
				case 3:
					if (parts[i].flavour != "Strange"){
						parts[i].flavour = "Strange";
						parts[i].mass = 95.0f + (rand() % 1000 - 500) / 10.0f;
						parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
						parts[i].life = 100;
					}
					break;
				case 4:
					if (parts[i].flavour != "Top"){
						parts[i].flavour = "Top";
						parts[i].mass = 173340.0f + (rand() % 5400 - 2700) / 10.0f;
						parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
						parts[i].life = 25;
					}
					break;
				case 5:
					if (parts[i].flavour != "Bottom"){
						parts[i].flavour = "Bottom";
						parts[i].mass = 4180.0f + (rand() % 600 - 300) / 10.0f;
						parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
						parts[i].life = 50;
					}
					break;
				}
				if (parts[i].life <= 0){
					if (parts[i].flavour == "Up"){
						if (rand() % 100 <= 5)sim->part_change_type(i, x, y, PT_ELEC);
						else{
							parts[i].flavour = "Down";
							parts[i].mass = 4.8f + (rand() % 8 - 4) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 150;
							parts[i].subFlavour = 1;
						}
					}
					else if (parts[i].flavour == "Down"){
						if (rand() % 100 <= 5)sim->part_change_type(i, x, y, PT_ELEC);
						else{
							parts[i].flavour = "Up";
							parts[i].mass = 2.3f + (rand() % 12 - 6) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 150;
							parts[i].subFlavour = 0;
						}
					}
					else if (parts[i].flavour == "Strange"){
						parts[i].flavour = "Up";
						parts[i].mass = 2.3f + (rand() % 12 - 6) / 10.0f;
						parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
						parts[i].life = 150;
						parts[i].subFlavour = 0;
					}
					else if (parts[i].flavour == "Charm"){
						if (rand() % 100 <= 5){
							parts[i].flavour = "Down";
							parts[i].mass = 4.8f + (rand() % 8 - 4) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 150;
							parts[i].subFlavour = 2;
						}
						else{
							parts[i].flavour = "Strange";
							parts[i].mass = 95.0f + (rand() % 1000 - 500) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 100;
							parts[i].subFlavour = 3;
						}
					}
					else if (parts[i].flavour == "Top"){
						int decay = rand() % 100;
						if (decay == 0){
							parts[i].flavour = "Down";
							parts[i].mass = 4.8f + (rand() % 8 - 4) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 150;
							parts[i].subFlavour = 1;
						}
						else if (decay == 1 || decay == 2){
							parts[i].flavour = "Strange";
							parts[i].mass = 95.0f + (rand() % 1000 - 500) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 100;
							parts[i].subFlavour = 3;
						}
						else{
							parts[i].flavour = "Bottom";
							parts[i].mass = 4180.0f + (rand() % 600 - 300) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 50;
							parts[i].subFlavour = 5;
						}
					}
					else if (parts[i].flavour == "Bottom"){
						if (rand() % 100 <= 0){
							parts[i].flavour = "Charm";
							parts[i].mass = 1290.0f + (rand() % 1600 - 800) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 100;
							parts[i].subFlavour = 4;
						}
						else{
							parts[i].flavour = "Up";
							parts[i].mass = 2.3f + (rand() % 12 - 6) / 10.0f;
							parts[i].dcolour = 0xff000000 + parts[i].colourCharge;
							parts[i].life = 150;
							parts[i].subFlavour = 0;
						}
					}
				}
				if ((r & 0xff) == PT_QARK){
					if (parts[i].flavour == "Up"&&parts[r >> 8].flavour == "Down"&&parts[i].colourCharge != parts[r >> 8].colourCharge&&parts[i].strongField&&parts[r >> 8].strongField){
						if (rand() % 100 < 50){
							parts[i].dcolour = 0;
							parts[i].life = rand() % 480 + 480;
							sim->part_change_type(i, x, y, PT_NEUT);
							sim->kill_part(r >> 8);
						}
						else{
							parts[i].dcolour = 0;
							parts[i].life = rand() % 480 + 480;
							sim->part_change_type(i, x, y, PT_PROT);
							sim->kill_part(r >> 8);
						}
					}
				}
				else if ((r & 0xFF) == PT_StrongInteraction){
					parts[i].vx = parts[r >> 8].tmp;
					parts[i].vy = parts[r >> 8].tmp2;
					parts[i].strongField = true;
				}
				else {
					if(parts[i].life%2==0)parts[i].strongField = false;
				}
				if (rand() % 100 <= 5)parts[i].vx *= -1;
				if (rand() % 100 <= 5)parts[i].vy *= -1;
				if(parts[i].life>0)if (rand()%parts[i].life<=5)sim->kill_part(i);
			}
	return 0;
}

//#TPT-Directive ElementHeader Element_QARK static int graphics(GRAPHICS_FUNC_ARGS)
int Element_QARK::graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 10;
	*firer = 250;
	*fireg = 170;
	*fireb = 170;

	*pixel_mode |= FIRE_BLEND;
	return 1;
}

Element_QARK::~Element_QARK() {}
