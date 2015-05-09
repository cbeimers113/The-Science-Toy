#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_GLUON PT_GLUON 192
Element_GLUON::Element_GLUON()
{
	Identifier = "DEFAULT_PT_GLUON";
	Name = "G-ON";
	Colour = PIXPACK(0x00aaff);
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
	Description = "Gluon. Carries the strong nuclear force.";

	State = ST_GAS;
	Properties = TYPE_ENERGY | PROP_LIFE_DEC | PROP_LIFE_KILL_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_GLUON::update;
	Graphics = &Element_GLUON::graphics;
}

//#TPT-Directive ElementHeader Element_GLUON static int update(UPDATE_FUNC_ARGS)
int Element_GLUON::update(UPDATE_FUNC_ARGS)
{
	parts[i].element = 1;
	parts[i].energy = parts[i].mass*parts[i].temp + parts[i].vx*parts[i].vx + parts[i].vy*parts[i].vy;
	int r, rx, ry;
	for (rx = -3; rx <= 3; rx++)
		for (ry = -3; ry <= 3; ry++)
			if (BOUNDS_CHECK)
			{
				r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (!(r & 0xFF))continue;
				if (abs(rx) <= 1 || abs(ry) <= 1)continue;
				sim->create_part(r >> 8, x + rx, y + ry, PT_StrongInteraction);
				parts[r >> 8].tmp = rx;
				parts[r >> 8].tmp2 = ry;
			}
	return 0;
}

int Element_GLUON::graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 30;
	*firer = 0;
	*fireg = 170;
	*fireb = 255;

	*pixel_mode |= FIRE_BLEND;
	return 1;
}

Element_GLUON::~Element_GLUON() {}
