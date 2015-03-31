/********************************************
 * OnPlayerShootPlayer! V:2.0               *
 * Credits: wups,						    *
 * Double-O-Seven for his HS functions      *
 ********************************************/

// include
#include <a_samp>
#tryinclude <foreach>

// defines
#if defined OPSP
	#endinput
#endif
#define OPSP

#if !defined foreach
	#define foreach(%1,%2) for (new %2 = 0; %2 < MAX_PLAYERS; %2++) if (IsPlayerConnected(%2))
	#define __SSCANF_FOREACH__
#endif
// variables
static Float:phealth[MAX_PLAYERS];

// forwards
forward OnPlayerShootPlayer(shooter,target,Float:damage);

public OnPlayerUpdate(playerid)
{
	static  Float:HP,
			Float:Armour;
	GetPlayerHealth(playerid,HP);
	GetPlayerArmour(playerid,Armour);
	if(HP+Armour < phealth[playerid])
	{
		static
			Float:XZC[14];
		GetPlayerCameraPos(playerid, XZC[10], XZC[11], XZC[12]);
		GetPlayerCameraFrontVector(playerid, XZC[7], XZC[8], XZC[9]);
		GetPlayerPos(playerid, XZC[0], XZC[1], XZC[2]);
		
		foreach(Player,i)
		{
			if(i != playerid && IsPlayerInRangeOfPoint(i, 100.0, XZC[0], XZC[1], XZC[2]))
			{
	   		    GetPlayerPos(i, XZC[3], XZC[4], XZC[5]);
				GetDistanceFromPointToLine(XZC[6], XZC[7], XZC[8], XZC[9], XZC[10], XZC[11], XZC[12], XZC[3], XZC[4], XZC[5]);
				if(XZC[6] < 2.5)
				{
					CallLocalFunction("OnPlayerShootPlayer","iif",i,playerid,(phealth[playerid]-HP-Armour));
					break;
				}
			}
		}
	}
	phealth[playerid]=HP+Armour;
	return CallLocalFunction("RL_OnPlayerUpdate","i",playerid);
}

stock crossp(Float:v1x, Float:v1y, Float:v1z, Float:v2x, Float:v2y, Float:v2z, &Float:output)
{
	new
		Float:c1 = (v1y * v2z) - (v1z * v2y),
		Float:c2 = (v1z * v2x) - (v1x * v2z),
        Float:c3 = (v1x * v2y) - (v1y * v2x);
    output = floatsqroot ((c1 * c1) + (c2 * c2) + (c3 * c3));
    return 0;
}

stock GetDistanceFromPointToLine(&Float:distance, Float:line_vector_x, Float:line_vector_y, Float:line_vector_z, Float:line_x, Float:line_y, Float:line_z, Float:point_x, Float:point_y, Float:point_z)
{
	//A line is defined by a point (which is on the line (line_x/y/z)) and a vector which defines the direction (line_vector_x/y/z).
	static Float:output;
    crossp(line_vector_x, line_vector_y, line_vector_z, point_x - line_x, point_y - line_y, point_z - line_z, output);//Cross product of 2 vectors.
    distance = output / floatsqroot ((line_vector_x * line_vector_x) + (line_vector_y * line_vector_y) + (line_vector_z * line_vector_z));
	return 0;
}

stock SetPlayerHealthEx(playerid, Float:health)
{
	new Float:armour; GetPlayerArmour(playerid,armour);
	phealth[playerid]=health+armour;
	return SetPlayerHealth(playerid, health);
}

#define SetPlayerHealth SetPlayerHealthEx

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate RL_OnPlayerUpdate
forward RL_OnPlayerUpdate(playerid);