#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_CLRN PT_CLRN 179
Element_CLRN::Element_CLRN()
{
	Identifier = "DEFAULT_PT_CLRN";
	Name = "CLRN";
	Colour = PIXPACK(0xF7FA9D);
	MenuVisible = 1;
	MenuSection = SC_GAS;
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
	Description = "Chlorine. A Halogen.";

	State = ST_GAS;
	Properties = TYPE_GAS|PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CLRN::update;

}

//#TPT-Directive ElementHeader Element_CLRN static int update(UPDATE_FUNC_ARGS)
int Element_CLRN::update(UPDATE_FUNC_ARGS){
	parts[i].element = 1;
	int r, rx, ry;
	for (rx = -2; rx<3; rx++)
		for (ry = -2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry)){
				r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				if (parts[i].life <= 0)parts[i].life = rand() % 2 + 1;
				if ((r & 0xFF) == PT_H2){
					parts[r>>8].type = PT_NONE;
					parts[i].ctype = PT_CLRN;
					parts[i].life += 500;
					sim->part_change_type(i, x, y, PT_ACID);
				}
			}
	return 0;
}


Element_CLRN::~Element_CLRN() {}
