#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_StrongInteraction PT_StrongInteraction 189
Element_StrongInteraction::Element_StrongInteraction()
{
	Identifier = "DEFAULT_PT_StrongInteraction";
	Name = "SNI";
	Colour = PIXPACK(0x000000);
	MenuVisible = 1;
	MenuSection = SC_CRACKER;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.00f;
	Loss = 0.00f;
	Collision = -.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 100;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 61;
	Description = "The strong nuclear interaction.";

	State = ST_SOLID;
	Properties = TYPE_ENERGY | PROP_LIFE_DEC |PROP_LIFE_KILL_DEC | PROP_NEUTPENETRATE | PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_StrongInteraction::update;
}

//#TPT-Directive ElementHeader Element_StrongInteraction static int update(UPDATE_FUNC_ARGS)
int Element_StrongInteraction::update(UPDATE_FUNC_ARGS)
{
	parts[i].element = 1;
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;

			}
	return 0;
}

Element_StrongInteraction::~Element_StrongInteraction() {}
