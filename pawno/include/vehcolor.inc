/*
Copyright 2010
Includ by Terminator3
*/

#if defined _vehcolor_included
	#endinput
#endif
#define _vehcolor_included
#pragma library vehcolor

#include <a_samp>

new VeHcolors[MAX_VEHICLES][2];
forward OnVehColorChange(vehicleid, color1, color2);
forward OnVehSpawn(vehicleid);
//------------------------------------------------------------------------------


stock SetVehColor(vehicleid, color1, color2)
{
	if(color1==-1)color1=random(127);
	if(color2==-1)color2=random(127);
	ChangeVehicleColor(vehicleid, color1, color2);
	VeHcolors[vehicleid][0]=color1;
	VeHcolors[vehicleid][1]=color2;
}

stock CveH(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay)
{
	if(color1==-1)color1=random(127);
	if(color2==-1)color2=random(127);
	new id=CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay);
	VeHcolors[id][0]=color1;
	VeHcolors[id][1]=color2;
}

stock ASVeh(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2)
{
	if(color1==-1)color1=random(127);
	if(color2==-1)color2=random(127);
	new id=AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2);
	VeHcolors[id][0]=color1;
	VeHcolors[id][1]=color2;
}

stock ASVehEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay)
{
	if(color1==-1)color1=random(127);
	if(color2==-1)color2=random(127);
	new id=AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay);
	VeHcolors[id][0]=color1;
	VeHcolors[id][1]=color2;
}

stock GetVehicleColor(vehicleid, &color1, &color2)
{
	color1=VeHcolors[vehicleid][0];
	color2=VeHcolors[vehicleid][1];
}



public OnVehColorChange(vehicleid, color1, color2)
{
	color1=VeHcolors[vehicleid][0];
	color2=VeHcolors[vehicleid][1];
}

#if !defined dont_change_color_at_spawn

public OnVehSpawn(vehicleid)
{
	new color1=random(127);
	new color2=random(127);
	color1=VeHcolors[vehicleid][0];
	color2=VeHcolors[vehicleid][1];
	ChangeVehicleColor(vehicleid, color1, color2);
	return 1;
}
#else
public OnVehSpawn(vehicleid)
{
	ChangeVehicleColor(vehicleid, VeHcolors[vehicleid][0], VeHcolors[vehicleid][1]);
	return 1;
}
#endif


#if !defined DONT_REPLACE_NATIVES

#define CreateVehicle CveH
#define ChangeVehicleColor SetVehColor
#define AddStaticVehicle ASVeh
#define AddStaticVehicleEx ASVehEx

#endif