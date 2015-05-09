#include "simulation/Elements.h"
#include "../Air.h"
//#TPT-Directive ElementClass Element_URAN PT_URAN 32
Element_URAN::Element_URAN()
{
	Identifier = "DEFAULT_PT_URAN";
	Name = "URAN";
	Colour = PIXPACK(0x707020);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.4f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 90;

	Temperature = R_TEMP + 30.0f + 273.15f;
	HeatConduct = 251;
	Description = "Heavy particles. Generates heat under pressure.";

	State = ST_SOLID;
	Properties = TYPE_PART | PROP_RADIOACTIVE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_URAN::update;

}

//#TPT-Directive ElementHeader Element_URAN static int update(UPDATE_FUNC_ARGS)
int Element_URAN::update(UPDATE_FUNC_ARGS)
{
	if (!sim->legacy_enable && sim->pv[y / CELL][x / CELL] > 0.0f)
	{
		if (parts[i].temp == MIN_TEMP)
		{
			parts[i].temp += .01f;
		}
		else
		{
			float atemp = parts[i].temp + (-MIN_TEMP);
			parts[i].temp = restrict_flt((atemp*(1 + (sim->pv[y / CELL][x / CELL] / 2000))) + MIN_TEMP, MIN_TEMP, MAX_TEMP);
		}
	}
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				if (parts[i].temp >= 9000.0f && sim->pv[y / CELL][x / CELL] >= 200.0f){
					parts[i].temp += 1500.0f;
					sim->part_change_type(i, x, y, PT_CRBN);
					int k = rand() % 5;
					sim->create_part(r >> 8, x + rx, y + ry, k == 0 ? PT_NBLE : k == 1 ? PT_PROT : k == 2 ? PT_QARK : PT_NEUT);
					parts[r >> 8].temp += 1500.0f;
					int rad = rand() % 5 + 3;
					for (int yy = -rad; yy <= rad; yy++){
						for (int xx = -rad; xx <= rad; xx++){
							if (xx*xx + yy*yy <= rad*rad + rad*0.8f + 1 && xx*xx + yy*yy >= rad*rad - rad*0.8f - 1){
								sim->pv[y / CELL + yy][x / CELL + xx] += 256.0f;
								sim->hv[y / CELL + yy][x / CELL + xx] += 2048.0f;
								int j = rand() % 11;
								parts[r>>8].type = j==0?PT_NBLE:j==1?PT_CRBN:j==2?PT_PROT:j==3||j==4||j==5?PT_ELEC:PT_NEUT;
							}
						}
					}
				}
			}
	return 0;
}


Element_URAN::~Element_URAN() {}
