/* Inter Role Play: INCLUDE
    _/  _/_/_/    _/_/_/
       _/    _/  _/    _/
  _/  _/_/_/    _/_/_/
 _/  _/    _/  _/
_/  _/    _/  _/
*/

#if defined _samp_included
	#endinput
#endif
#include <a_samp>
#include <zcmd>

#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#define chrtoupper(%1) \
        (((%1) > 0x60 && (%1) <= 0x7A) ? ((%1) ^ 0x20) : (%1))
#define chrtolower(%1) \
        (((%1) > 0x40 && (%1) <= 0x5A) ? ((%1) | 0x20) : (%1))
#define foreach(%2,%1) \
        for (new %2 = 0; %2 < %1; %2++)
#define kutas irp_AddEvent
#define PlayerToPoint(%0,%1,%2,%3,%4) IsPlayerInRangeOfPoint(%1,%0,%2,%3,%4)

#define MAX_DOORS 100 // no bo tak

// Kolory
#define BEZOWY        0xFFFFADAA
#define BIALY         0xFFFFFFFF //AA
#define BLEKITNY      0x33CCFFAA
#define BORDOWY       0x99001FAA
#define BRAZOWY       0x997A00AA
#define DARK_ZIELONY  0x336633AA
#define CZARNY        0x000000AA
#define CZERWONY      0xFF0000AA
#define FIOLETOWY     0xC2A2DAAA
#define FIOLETOWY2    0xE0EA64AA
#define NIEBIESKI     0x0000FFAA
#define POMARANCZOWY  0xFF8000AA
#define ROZOWY        0xFF66CCAA
#define SZARY         0xB0B0B0AA
#define ZIELONY       0x00CC00AA
#define ZOLTY         0xFFFF00AA
#define RED           0xFF0000AA
#define LCZERWONY     0xFF6347AA

// Owners
#define OWNER_NONE    0
#define OWNER_PLAYER  1
#define OWNER_ORG     2
#define OWNER_BIZZ    3
#define OWNER_WORK    4
#define OWNER_ADMIN   5

// Miejsce przedmiotow
#define PLACE_NONE       0
#define PLACE_PLAYER     1
#define PLACE_VEHICLE    2
#define PLACE_HOUSE      3

// Typy przedmiotów
#define ITEM_NONE        0 // bez funkcji
#define ITEM_WEAPON      1 // bronie
#define ITEM_PHONE       2 // telefon
#define ITEM_RADIO       3 // radio
#define ITEM_WATCH       4 // zegarek
#define ITEM_KANISTER    5 // kanister
#define ITEM_BALL        6 // pilka do nogi
#define ITEM_CUBE        7 // kostka do gry (random 1-6)
#define ITEM_CIGGY       8 // fajki
#define ITEM_LICENSE     9 // licencje
#define ITEM_SKATE      10 // rolki
#define ITEM_GPS        11 // gps
#define ITEM_FOOD       12 // jedzenie
#define ITEM_BANDANA    13 // bandana
#define ITEM_CLOTH      14 // ubranie
/////////////////////////////

stock Logged[MAX_PLAYERS];

// Players on-server
enum ePlayer
{
	pUID,
	pAdmin,
	pGlobalAcc,
	pSkin,
	Float:pHP,
	pCash
}
stock PlayerData[MAX_PLAYERS][ePlayer];

// Vehicles on-server
enum eCar
{
	vehUID
}
stock VehicleData[MAX_VEHICLES][eCar];

enum dDoors
{
	dUID,

	dOwnerType,
	dOwner,

	Float:dEnterX,
	Float:dEnterY,
	Float:dEnterZ,
	Float:dEnterAng,
	dEnterInt,
	dEnterVw,

	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	Float:dExitAng,
	dExitInt,
	dExitVw,

	dLock,
	dPickupID,
	dName[32],
	dGPS
}
stock DoorData[MAX_DOORS][dDoors];


native sscanf(const data[], const format[], {Float,_}:...);
native unformat(const data[], const format[], {Float,_}:...) = sscanf;

native mysql_check();
native GetVehicleID(uid);
native GetPickupID(type, id);
native PlayerToPlayer(playerid, destid, Float:radius);
native PlayerToVehicle(Float:radi, playerid, vehicleid);
native AddDoors(playerid, ownertype, owner, comment[32]);
native SaveDoors(uid);
native AddItem(type, name[], owner, value1, value2, place, Float:posx, Float:posy, Float:posz, vehid, houseid, reserved);
native DeleteItem(itemid);
native GivePlayerItem(playerid, name[], type, value1, value2);
native GetPlayerWeaponAmmo(playerid, weaponid);
native HavePlayerWeapon(playerid, weaponid);
native GetPlayerUseWeapon(playerid);
native GetPlayerUseWeaponID(playerid);
native AddVehicle(model, Float:x, Float:y, Float:z, Float:angle, color1, color2, ownertype, owner);
native SaveVehicle(vehicleuid);
native ShowPlayerStats(playerid, showplayerid);
native ListPlayerItems(playerid, ownerid, type, button[]);
native SendPlayerText(Float:radi, playerid, string2[], col1, col2, col3, col4, col5);
native SendClientMessageToAdmins(color, string1[]);
native iRP_GivePlayerMoney(playerid, money);
native iRP_SetPlayerHealth(playerid, Float:health);
native iRP_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay);
native CreateVehicleFromDB(uid);
native OnPlayerSave(playierd);
native PlayerName(playerid);  // @return: "player_name"
native PlayerName2(playerid); // @return: "player name"
native WeaponName(weaponid);
native GetVehicleName(vehicleid)
native GetVehicleModelName(modelid);
native GetDistanceToVehicle(playerid,vehicleid);
native yesno(value);
native FloatToInt(Float:var)
native ExplodeCharFound(text[]);
native GetPlayerSQLName(sqlid);
native RemovePlayerWeapon(playerid, weaponid);
native SetWeaponAmmo(playerid, weaponid, ammo);
native GetItemTypeName(type);
native kutas(event[]);