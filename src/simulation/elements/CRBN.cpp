#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_CRBN PT_CRBN 181
Element_CRBN::Element_CRBN()
{
	Identifier = "DEFAULT_PT_CRBN";
	Name = "CRBN";
	Colour = PIXPACK(0x2E2E2E);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
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
	Meltable = 0;
	Hardness = 30;

	Weight = 70;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Carbon. Essential to organic compounds.";

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

	Update = &Element_CRBN::update;

}

//#TPT-Directive ElementHeader Element_CRBN static int update(UPDATE_FUNC_ARGS)
int Element_CRBN::update(UPDATE_FUNC_ARGS){
	parts[i].element = 1;
	int r, rx, ry;
	for (rx = -2; rx < 3; rx++)
		for (ry = -2; ry < 3; ry++)
			if (BOUNDS_CHECK && (rx || ry)){
				r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				if (parts[i].life <= 0||parts[i].life>16)parts[i].life = rand() % 15 + 1;
				int C = parts[i].life;
				int H = parts[r >> 8].life;
				switch (r & 0xFF){
				case PT_O2:
					sim->part_change_type(i, x, y, PT_CO2);
					sim->kill_part(r >> 8);
					break;
				case PT_H2:
					if (H >= 2 * C - 2){
						sim->part_change_type(i, x, y, PT_HCBN);
						sim->kill_part(r >> 8);
						parts[i].carbon = C;
						parts[i].hydrogen = H;
						parts[i].alcohol = 0;
						if (parts[i].hydrogen < 2 * parts[i].carbon + 2)parts[i].bond = rand() % (C / 2 + 1);
					}
					else if (H == 6 && C == 6){
						sim->part_change_type(i, x, y, PT_BNZN);
						sim->kill_part(r >> 8);
						parts[i].carbon = C;
						parts[i].hydrogen = H;
					}
					break;
				}
			}
	return 0;
}

Element_CRBN::~Element_CRBN() {}
