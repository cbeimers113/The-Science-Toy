#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_HXDE PT_HXDE 184
Element_HXDE::Element_HXDE()
{
	Identifier = "DEFAULT_PT_HXDE";
	Name = "HXDE";
	Colour = PIXPACK(0xD2B8DB);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.10f;
	Gravity = 0.00f;
	Diffusion = 3.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 1;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Hydroxide ion.";

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

	Update = &Element_HXDE::update;

}

//#TPT-Directive ElementHeader Element_HXDE static int update(UPDATE_FUNC_ARGS)
int Element_HXDE::update(UPDATE_FUNC_ARGS){
	parts[i].element = 1;
	int r, rx, ry;
	for (rx = -2; rx<3; rx++)
		for (ry = -2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry)){
			r = pmap[y + ry][x + rx];
			if (!r)
			continue;
			if ((r & 0xFF) == PT_H2 && parts[i].temp >= 300.0f){
				sim->part_change_type(i, x, y, PT_WTRV);
				sim->kill_part(r >> 8);
			}
			}
	return 0;
}

Element_HXDE::~Element_HXDE() {}
