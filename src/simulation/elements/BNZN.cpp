#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_BNZN PT_BNZN 185
Element_BNZN::Element_BNZN()
{
	Identifier = "DEFAULT_PT_BNZN";
	Name = "BNZN";
	Colour = PIXPACK(0xBFB6C2);
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
	Description = "Benzene.";

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

	Update = &Element_BNZN::update;

}

//#TPT-Directive ElementHeader Element_BNZN static int update(UPDATE_FUNC_ARGS)
int Element_BNZN::update(UPDATE_FUNC_ARGS){
	parts[i].element = 1;
	int r, rx, ry;
	for (rx = -2; rx<3; rx++)
		for (ry = -2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry)){
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
			int C = parts[i].carbon;
			int H = parts[i].hydrogen;
			if (C < 6) C = 6;
			if (H < 6) H = 6;
			parts[i].energy = (parts[i].temp - R_TEMP) - rand() % 25 - 12;
			if (parts[i].energy >= 300.0f && (r & 0xFF) == PT_CRBN){
				sim->create_part(-1, x + rx, y + ry, PT_H2);
				if (parts[r >> 8].life > 25){
					C += 2;
					H += 5;
				}
				else {
					C++;
					H += 3;
				}
			} if (parts[i].energy >= 300.0f && ((r & 0xFF) == PT_HCBN || (r & 0xFF) == PT_OIL || (r & 0xFF) == PT_PRFN)){
				parts[r >> 8].benzyl = true;
			}
			parts[i].carbon = C;
			parts[i].hydrogen = H;
			}
	return 0;
}

Element_BNZN::~Element_BNZN() {}
