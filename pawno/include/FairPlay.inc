#include <a_samp>

forward INC_GivePlayerMoney(playerid, money);
public INC_GivePlayerMoney(playerid, money)
{
	return CallRemoteFunction("FP_GivePlayerMoney", "ii", playerid, money);
}

forward INC_GetPlayerMoney(playerid);
public INC_GetPlayerMoney(playerid)
{
	return CallRemoteFunction("FP_GetPlayerMoney", "i", playerid);
}

forward INC_ResetPlayerMoney(playerid);
public INC_ResetPlayerMoney(playerid)
{
	return CallRemoteFunction("FP_ResetPlayerMoney", "i", playerid);
}

forward INC_GivePlayerWeapon(playerid, weaponid, ammo);
public INC_GivePlayerWeapon(playerid, weaponid, ammo)
{
	return CallRemoteFunction("FP_GivePlayerWeapon", "iii", playerid, weaponid, ammo);
}

forward INC_ResetPlayerWeapons(playerid);
public INC_ResetPlayerWeapons(playerid)
{
    return CallRemoteFunction("FP_ResetPlayerWeapons", "i", playerid);
}

forward INC_PutPlayerInVehicle(playerid,vehicleid,seatid);
public INC_PutPlayerInVehicle(playerid,vehicleid,seatid)
{
	return CallRemoteFunction("FP_PutPlayerInVehicle", "iii", playerid, vehicleid, seatid);
}   

forward INC_SetPlayerPos(playerid,Float:x, Float:y, Float:z);
public INC_SetPlayerPos(playerid,Float:x, Float:y, Float:z)
{
	return CallRemoteFunction("FP_SetPlayerPos", "dfff", playerid, x, y, z);
}

forward INC_SetPlayerPosFindZ(playerid,Float:x, Float:y, Float:z);
public INC_SetPlayerPosFindZ(playerid,Float:x, Float:y, Float:z)
{
	return CallRemoteFunction("FP_SetPlayerPosFindZ", "dfff", playerid, x, y, z);
}

forward INC_SetPlayerPosFindZ(playerid,Float:x, Float:y, Float:z);
public INC_SetVehiclePos(vehicleid,Float:x, Float:y, Float:z)
{
	return CallRemoteFunction("FP_SetVehiclePos", "dfff", vehicleid, x, y, z);
}

forward INC_SetPlayerVelocity(playerid,Float:x, Float:y, Float:z);
public INC_SetPlayerVelocity(playerid,Float:x, Float:y, Float:z)
{
	return CallRemoteFunction("FP_SetPlayerVelocity", "dfff", playerid, x, y, z);
}

forward INC_SetVehicleVelocity(vehicleid,Float:x, Float:y, Float:z);
public INC_SetVehicleVelocity(vehicleid,Float:x, Float:y, Float:z)
{
	return CallRemoteFunction("FP_SetVehicleVelocity", "dfff", vehicleid, x, y, z);
}

forward INC_SetDisabledWeapon(weaponid);
public INC_SetDisabledWeapon(weaponid)
{
	return CallRemoteFunction("FP_SetDisabledWeapon", "d", weaponid);
}

forward INC_EnableDisabledWeapon(weaponid);
public INC_EnableDisabledWeapon(weaponid)
{
	return CallRemoteFunction("FP_EnableDisabledWeapon", "d", weaponid);
}

forward INC_TogglePlayerControllable(playerid, toggle);
public INC_TogglePlayerControllable(playerid, toggle)
{
	return CallRemoteFunction("FP_TogglePlayerControllable", "dd", playerid, toggle);
}

forward INC_SetPlayerHealth(playerid, Float:health);
public INC_SetPlayerHealth(playerid, Float:health)
{
	return CallRemoteFunction("FP_SetPlayerHealth", "df", playerid, health);
}

forward INC_SetPlayerArmour(playerid, Float:armour);
public INC_SetPlayerArmour(playerid, Float:armour)
{
	return CallRemoteFunction("FP_SetPlayerArmour", "df", playerid, armour);
}

#define GivePlayerMoney INC_GivePlayerMoney
#define GetPlayerMoney INC_GetPlayerMoney
#define ResetPlayerMoney INC_ResetPlayerMoney
#define GivePlayerWeapon INC_GivePlayerWeapon
#define ResetPlayerWeapons INC_ResetPlayerWeapons
#define PutPlayerInVehicle INC_PutPlayerInVehicle   
#define SetPlayerPos INC_SetPlayerPos
#define SetPlayerPosFindZ INC_SetPlayerPosFindZ
#define SetVehiclePos INC_SetVehiclePos
#define SetPlayerVelocity INC_SetPlayerVelocity
#define SetVehicleVelocity INC_SetVehicleVelocity
#define SetDisabledWeapon INC_SetDisabledWeapon
#define EnableDisabledWeapon INC_EnableDisabledWeapon
#define TogglePlayerControllable INC_TogglePlayerControllable
#define SetPlayerHealth INC_SetPlayerHealth
#define SetPlayerArmour INC_SetPlayerArmour
