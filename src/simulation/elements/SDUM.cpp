#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SDUM PT_SDUM 180
Element_SDUM::Element_SDUM()
{
	Identifier = "DEFAULT_PT_SDUM";
	Name = "SDUM";
	Colour = PIXPACK(0xC9C9C9);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 30;

	Weight = 70;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Sodium. An alkaline metal.";

	State = ST_SOLID;
	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_SDUM::update;

}

//#TPT-Directive ElementHeader Element_SDUM static int update(UPDATE_FUNC_ARGS)
int Element_SDUM::update(UPDATE_FUNC_ARGS){
	int r, rx, ry;
	for (rx = -2; rx < 3; rx++)
		for (ry = -2; ry < 3; ry++)
			if (BOUNDS_CHECK && (rx || ry)){
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		if (((r&0xFF)==PT_WATR)||((r&0xFF)==PT_WTRV)){
			sim->part_change_type(i, x, y, PT_SMKE);
			parts[i].temp += 100;
			parts[r >> 8].temp += parts[i].temp;
			if (rand() % 100 <= 35)sim->kill_part(r >> 8);
		}
		if ((r & 0xFF) == PT_CLRN){
			sim->part_change_type(i, x, y, PT_SALT);
			parts[r >> 8].type = PT_SMKE;
			sim->pv[y / CELL][x / CELL] ++;
		}
			}
	return 0;
}

Element_SDUM::~Element_SDUM() {}
