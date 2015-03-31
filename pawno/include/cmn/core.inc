#if defined cmn_included
	#endinput
#endif
#define cmn_included
#define CHECK_INTERVAL 5
#define MAX_STUNT_BONUS 500
#define CASINO_INTERIOR_IDS 1
#define LOG_FILE_PATH "cmn\\log.txt"
#define CONFIG_FILE_PATH "cmn\\configuration.txt"
#define BLACKLIST_PATH "cmn\\blacklist.txt"
#define BLOCKED_PATH "cmn\\blocked\\"

enum _structure
{
	_money,
	_health,
	_armour,
	_weapon,
	_ammo,
	_case1,
	_case2,
	_spawned,
	_suspected,
 	_freezed
}

new _player[MAX_PLAYERS][_structure];
new _activated[_structure];
new _weapons[MAX_PLAYERS][13];
new _ammos[MAX_PLAYERS][13];

#include "cmn\functions.txt"

forward _check();
public _check()
{
	for(new playerid = 0;playerid < MAX_PLAYERS;playerid++)
	{
		if((_player[playerid][_spawned]) && (!_player[playerid][_case2])) // player connected
		{
			#include "cmn\detect\money.txt"
			#include "cmn\detect\health.txt"			
			#include "cmn\detect\armour.txt"
			#include "cmn\detect\weapon.txt"
			#include "cmn\detect\ammo.txt"
		}
	}
}

#include "cmn\system.txt"
#include "cmn\cover.txt"