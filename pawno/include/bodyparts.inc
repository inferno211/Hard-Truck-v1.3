/*
									Body Part Detection - Detect a player's body part
									                By Seif
										Spolszczone przez IceColdKilla dla pawno.pl
*/
/*x---------------------------------Important-------------------------------------x*/
//**INCLUDY**//
#include <a_samp>

#if !defined function
	#define function%0(%1) forward %0(%1); public %0(%1)
#endif
/*x---------------------------------Defining-------------------------------------x*/
#define MAX_DISTANCE_UNIT   100.0   // max dystans z którego mo¿na celowaæ do gracza
//**CZÊŒCI CIA£A**//
#define BODY_PART_HEAD  1
#define BODY_PART_TORSO 2
#define BODY_PART_LEGS  3

//#define SCRIPT_DEBUG
/*x---------------------------------CallBacki-------------------------------------x*/
/*/
	native IsPlayerAimingBodyPart(playerid, bodypart);
	native IsPlayerAimingTargetBodyPart(playerid, targetid, bodypart);
*/
/*
											---[IsPlayerAimingBodyPart]---
			»playerid: gracz
			»bodypart: czêœæ cia³a któr¹ chcesz sprawdziæ
			*Return: 1 jeœli tak, 0 jeœli nie
		*-------------------------------------------------------------------*
		| Sprawdza czy gracz celuje w jak¹œ czêœæ cia³a innego gracza.	|
		*-------------------------------------------------------------------*
*/
#if defined SCRIPT_DEBUG
	new shootpick[100];
#endif
function IsPlayerAimingBodyPart(playerid, bodypart)
{
    #if defined SCRIPT_DEBUG
		new c;
	#endif
	// Pobieramy pozycje kamery
	new Float:x, Float:y, Float:z, Float:a;
	new Float:vx, Float:vy, Float:vz;
	new Float:cx, Float:cy, Float:cz;
	new Float:offset;
	new Float:radius;
	GetPlayerCameraFrontVector(playerid, vx, vy, vz);
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerFacingAngle(playerid, a);
	// Spawdza czy gracz celuje z danej odleg³oœci
	for(new Float:d; d < MAX_DISTANCE_UNIT; d += 0.5)
	{
		switch (GetPlayerWeapon(playerid))
		{
		    case 24, 29, 22, 23, 25, 26, 27, 28, 32: offset = 0.11;
		    case 30, 31: offset = 0.07;
		    case 33: offset = 0.045;
		    default: offset = 0.0;
		}
	    switch (GetPlayerWeapon(playerid))
	    {
	        case 22, 26, 28, 32:
	        {
			    // podwójne bronie, nie jest dok³adne, ale dzia³a
			    x = vx*d+cx;
			    y = vy*d+cy;
	        }
	        default:
	        {
	    		// to jest dla broni które zmieniaj¹ k¹t kiedy celujesz gdzie indziej
	            x = cx + (d * floatsin(-a, degrees));
	    		y = cy + (d * floatcos(-a, degrees));
	        }
	    }

	    z = (vz+offset)*d+cz;
	    switch (bodypart)
	    {
	        case BODY_PART_HEAD: z -= 0.0, radius = 0.3;  // offsety dla headshotów
	        case BODY_PART_TORSO: z += 0.6, radius = 0.5;
	        case BODY_PART_LEGS: z += 1.2, radius = 0.4;
	    }

		#if defined SCRIPT_DEBUG
	        if (IsValidObject(shootpick[c])) DestroyObject(shootpick[c]);
			shootpick[c] = CreateObject(1274, x, y, z, 0.0, 0.0, 0.0);
			c++;
		#endif
		
	    for(new i, m = GetMaxPlayers(); i < m; i++)
	    {
			if (!IsPlayerConnected(i)) continue;
			if (playerid == i) continue;
			if (GetPlayerSpecialAction(i) == SPECIAL_ACTION_DUCK)
			{
				if (IsPlayerInRangeOfPoint(i, radius+0.2, x, y, z+1.2-1.3-(bodypart==BODY_PART_TORSO?0.42:0.0)))
				{
					return i;
				}
			}
			else if (IsPlayerInRangeOfPoint(i, radius, x, y, z-0.8))
			{
				return i;
			}
		}
	}
	return INVALID_PLAYER_ID;
}

/*
											---[IsPlayerAimingTargetBodyPart]---
			»playerid: gracz
			»targetid: cel
			»bodypart: czêœæ cia³a któr¹ chcesz spawdziæ
			*Return: 1 jeœli tak, 0 jeœli nie
		*-------------------------------------------------------------------*
		|	Spawdza czy gracz celuje w czêœæ cia³a danego gracza	|
		*-------------------------------------------------------------------*
*/
function IsPlayerAimingTargetBodyPart(playerid, targetid, bodypart)
{
    #if defined SCRIPT_DEBUG
		new c;
	#endif
	// pobieramy pozycje kamery
	new Float:x, Float:y, Float:z, Float:a;
	new Float:vx, Float:vy, Float:vz;
	new Float:cx, Float:cy, Float:cz;
	new Float:offset;
	new Float:radius;
	GetPlayerCameraFrontVector(playerid, vx, vy, vz);
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerFacingAngle(playerid, a);
	// spawdza czy gracz celuje z danej odleg³oœci
	for(new Float:d; d < MAX_DISTANCE_UNIT; d += 0.5)
	{
		switch (GetPlayerWeapon(playerid))
		{
		    case 24, 29, 22, 23, 25, 26, 27, 28, 32: offset = 0.11;
		    case 30, 31: offset = 0.07;
		    case 33, 34: offset = 0.0;
		}
	    switch (GetPlayerWeapon(playerid))
	    {
	        case 22, 26, 28, 32:
	        {
			    // podwójne bronie, nie jest doskona³e, ale dzia³a
			    x = vx*d+cx;
			    y = vy*d+cy;
	        }
	        default:
	        {
	    		// to jest dla broni które zmieniaj¹ k¹t kiedy celujesz gdzie indziej
	            x = cx + (d * floatsin(-a, degrees));
	    		y = cy + (d * floatcos(-a, degrees));
	        }
	    }

	    z = (vz+offset)*d+cz;
	    switch (bodypart)
	    {
	        case BODY_PART_HEAD: z -= 0.0, radius = 0.3;  // offsety dla headshotów
	        case BODY_PART_TORSO: z += 0.6, radius = 0.5;
	        case BODY_PART_LEGS: z += 1.2, radius = 0.4;
	    }

		#if defined SCRIPT_DEBUG
	        if (IsValidObject(shootpick[c])) DestroyObject(shootpick[c]);
			shootpick[c] = CreateObject(1274, x, y, z, 0.0, 0.0, 0.0);
			c++;
		#endif

		if (GetPlayerSpecialAction(targetid) == SPECIAL_ACTION_DUCK)
		{
			if (IsPlayerInRangeOfPoint(targetid, radius+0.2, x, y, z+1.2-1.3-(bodypart==BODY_PART_TORSO?0.42:0.0)))
			{
				return 1;
			}
		}
		else if (IsPlayerInRangeOfPoint(targetid, radius, x, y, z-0.8))
		{
			return 1;
		}
	}
	return 0;
}
