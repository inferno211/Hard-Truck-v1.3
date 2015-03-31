#if defined irpapi_loaded
  #endinput
#endif
#define irpapi_loaded

#include <a_samp>

#define dcmd(%1,%2,%3) if (!strcmp((%3)[1], #%1, true, (%2)) && ((((%3)[(%2) + 1] == '\0') && (dcmd_%1(playerid, ""))) || (((%3)[(%2) + 1] == ' ') && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#define foreach(%2,%1) \
        for (new %2 = 0; %2 < %1; %2++)

// Pojazdy
#define MAX_DB_VEHICLES  3000

// Kolory
#define BEZOWY        0xFFFFADAA
#define BIALY         0xFFFFFFAA
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

#define COLOR_INFO    0xFFFFFFFF
#define COLOR_ERROR   0xAE0000FF
#define COLOR_WARNING 0xEDB50CFF
#define COLOR_SUCCESS 0x00D700FF

#define COLOR_FADE1   0xE6E6E6E6
#define COLOR_FADE2   0xC8C8C8C8
#define COLOR_FADE3   0xAAAAAAAA
#define COLOR_FADE4   0x8C8C8C8C
#define COLOR_FADE5   0x6E6E6E6E

#define COLOR_GRAD1   0xB4B5B7FF
#define COLOR_GRAD2   0xBFC0C2FF
#define COLOR_GRAD3   0xCBCCCEFF
#define COLOR_GRAD4   0xD8D8D8FF
#define COLOR_GRAD5   0xE3E3E3FF
#define COLOR_GRAD6   0xF0F0F0FF

#define COLOR_SENTW   0x649E32FF
#define COLOR_REVIW   0x64D032FF

// Teams
#define TEAM_DEFAULT  0

// Dialogs
#define DIALOG_LOGIN       1
#define DIALOG_NICK        2
#define DIALOG_INFO        3
#define DIALOG_STATS       4
#define DIALOG_VEH_LIST    10
#define DIALOG_VEH_UNSPAWN 11

// Owners
#define OWNER_NONE    0
#define OWNER_PLAYER  1
#define OWNER_ORG     2
#define OWNER_BIZZ    3
#define OWNER_WORK    4
#define OWNER_ADMIN   5

native mysql_check();

native GetVehicleID(uid);
native GetHighestVehicleUID();
native iRP_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay);
native CreateVehicleFromDB(uid);
native GetVehicleName(vehicleid);
native GetVehicleModelName(modelid);

native PlayerToPlayer(playerid, destid, Float:radius);
native PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
native PlayerToVehicle(Float:radi, playerid, vehicleid);
native GetDistanceToVehicle(playerid, vehicleid);
native GetClosestVehicle(playerid);

native SendPlayerText(Float:radi, playerid, string2[], col1, col2, col3, col4, col5);
native ClearClientChat(playerid);

native ShowPlayerStats(playerid, showplayerid);
native OnPlayerSave(playerid);

native PlayerName(playerid);
native PlayerName2(playerid);
native sscanf(string[], format[], {Float,_}:...);

native SendClientMessageFormat(playerid, color, const format[], {Float,_}:...);
native SendClientMessageToAllFormat(color, const format[], {Float,_}:...);
native SendPlayerInfoDialog(playerid, const title[], const format[], {Float,_}:...);


// Players on-server
enum ePlayer
{
	pUID,
	pAdmin,
	pGlobalAcc,
	pSkin,
	Float:pHP
}
stock PlayerData[MAX_PLAYERS][ePlayer];

// Vehicles on-server
enum eCar
{
	vehUID
}
stock VehicleData[MAX_VEHICLES][eCar];

// Vehicles in-database
enum eVehicles
{
	vUID,
	vModel,
	Float:vX,
	Float:vY,
	Float:vZ,
	Float:vAngle,
	vColor1,
	vColor2,
	vOwnerType,
	vOwner,
	vLock,
	vFuel,
	Float:vHP
}
stock DbVehicles[MAX_DB_VEHICLES][eVehicles];

stock Logged[MAX_PLAYERS];