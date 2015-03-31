#if defined AntyCheat_included
 #endinput
#endif
#define AntyCheat_included

#include <a_samp>

/* Native's
 native AC_OnGameModeInit();
 native AC_OnPlayerConnect(playerid);
 native AC_OnPlayerSpawn(playerid);
 native GiveMoney(playerid, money);
 native SetMoney(playerid, money);
 native GetMoney(playerid);
 native ResetMoney(playerid);
 native OnMoneyUpdate(playerid);
 native SetHealth(playerid, Float:health);
 native SetArmour(playerid, Float:armour);
 native GiveWeapon(playerid, weaponid, ammo);
 native ResetWeapons(playerid);
*/

forward AC_OnGameModeInit();
public AC_OnGameModeInit()
 return SetTimer("AC_Timer", 2500, true);

forward AC_OnPlayerConnect(playerid);
public AC_OnPlayerConnect(playerid)
{


 SetPVarInt(playerid, "AC_MONEY", 0);
 SetPVarFloat(playerid, "AC_HEALTH", 50.0);
 SetPVarFloat(playerid, "AC_ARMOUR", 0);
 
 for(new i; i < 47; i++)
     AC_SetPVarForamted(playerid, "AC_WEAPON", i, 0);
 
 return 1;
}

forward AC_OnPlayerSpawn(playerid);
public AC_OnPlayerSpawn(playerid)
 return SetPVarInt(playerid, "AC_SPAWNED", 1);

forward AC_Timer();
public AC_Timer()
{
 for(new playerid; playerid < GetMaxPlayers(); playerid++)
 {
  if(!IsPlayerConnected(playerid)) continue;

  // Anty Money Hack
  OnMoneyUpdate(playerid);

  //Anty Health & Armour Hack
  new Float:AC_HEALTH, Float:AC_ARMOUR;

  GetPlayerHealth(playerid, AC_HEALTH);
  GetPlayerArmour(playerid, AC_ARMOUR);

  if(AC_HEALTH > GetPVarFloat(playerid, "AC_ARMOUR"))
   SetPlayerArmour(playerid, GetPVarFloat(playerid, "AC_ARMOUR"));

  if(AC_ARMOUR > GetPVarFloat(playerid, "AC_HEALTH"))
      SetPlayerHealth(playerid,  GetPlayerHealth(playerid, AC_HEALTH));

  // Anty Weapon Hack
  if(GetPlayerWeapon(playerid != 0) && GetPVarInt(playerid, "AC_SPAWNED") && !AC_GetPVarForamted(playerid, "AC_WEAPON", GetPlayerWeapon(playerid)))
   Kick(playerid);
 }
 return 1;
}

// Funkcje Anty Money Cheat
stock GiveMoney(playerid, money)
 return SetPVarInt(playerid, "money", GetPVarInt(playerid, "money") + money) & OnMoneyUpdate(playerid);

stock SetMoney(playerid, money)
 return SetPVarInt(playerid, "money", money) & OnMoneyUpdate(playerid);

stock GetMoney(playerid)
 return GetPVarInt(playerid, "money");

stock ResetMoney(playerid)
 return SetPVarInt(playerid, "money", 0) & OnMoneyUpdate(playerid);

stock OnMoneyUpdate(playerid)
 return ResetPlayerMoney(playerid) & GivePlayerMoney(playerid, GetPVarInt(playerid, "money"));

// Funkcje Anty Health & Armour Cheat
stock SetHealth(playerid, Float:health)
 return SetPVarFloat(playerid, "AC_HEALTH", health) & SetPlayerHealth(playerid, health);

stock SetArmour(playerid, Float:armour)
 return SetPVarFloat(playerid, "AC_ARMOUR", armour) & SetPlayerArmour(playerid, armour);


// Funkcje Anty Weapon Cheat
stock GiveWeapon(playerid, weaponid, ammo)
 return AC_SetPVarForamted(playerid, "AC_WEAPON", weaponid, 1) & GivePlayerWeapon(playerid, weaponid, ammo);

stock ResetWeapons(playerid)
{
 for(new i; i < 47; i++) AC_SetPVarForamted(playerid, "AC_WEAPON", i, 0);
 return ResetPlayerWeapons(playerid);
}

// Pozosta³e
stock AC_SetPVarForamted(playerid, const var[], weaponid, val)
{
 new TMP_GiveWeapon[32];
 format(TMP_GiveWeapon, 32, "%s_%d", var, weaponid);
 SetPVarInt(playerid, TMP_GiveWeapon, val);
 return 1;
}

stock AC_GetPVarForamted(playerid, const var[], weaponid)
{
 new TMP_GiveWeapon[32];
 format(TMP_GiveWeapon, 32, "%s_%d", var, weaponid);
 return GetPVarInt(playerid, TMP_GiveWeapon);
}

#define GivePlayerMoney GiveMoney
#define SetPlayerMoney SetMoney
#define GetPlayerMoney GetMoney
#define ResetPlayerMoney ResetMoney