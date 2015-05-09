#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_GAS PT_GAS 10
Element_GAS::Element_GAS()
{
	Identifier = "DEFAULT_PT_GAS";
	Name = "GAS";
	Colour = PIXPACK(0xE0FF20);
	MenuVisible = 0;
	MenuSection = SC_GAS;
	Enabled = 1;
	
	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.75f;
	HotAir = 0.001f	* CFDS;
	Falldown = 0;
	
	Flammable = 600;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;
	
	Weight = 1;
	
	Temperature = R_TEMP+2.0f	+273.15f;
	HeatConduct = 42;
	Description = "Diffuses quickly and flammable. Liquefies into OIL under pressure.";
	
	State = ST_GAS;
	Properties = TYPE_GAS | PROP_NEUTPASS;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 6.0f;
	HighPressureTransition = PT_OIL;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 573.0f;
	HighTemperatureTransition = PT_FIRE;
	
	Update = &Element_GAS::update;
	
}

//#TPT-Directive ElementHeader Element_GAS static int update(UPDATE_FUNC_ARGS)
int Element_GAS::update(UPDATE_FUNC_ARGS){
	int r, rx, ry;
	for (rx = -2; rx < 3; rx++)
		for (ry = -2; ry < 3; ry++)
			if (BOUNDS_CHECK && (rx || ry)){
		r = pmap[y + ry][x + rx];
		if (!r)
			continue;
		sim->part_change_type(i, x, y, PT_HCBN);
			}
	return 0;
}

Element_GAS::~Element_GAS() {}
