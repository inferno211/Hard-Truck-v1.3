#if defined prpapi_loaded
  #endinput
#endif
#define prpapi_loaded

#include <a_samp>

#define dcmd(%1,%2,%3) if (!strcmp((%3)[1], #%1, true, (%2)) && ((((%3)[(%2) + 1] == '\0') && (dcmd_%1(playerid, ""))) || (((%3)[(%2) + 1] == ' ') && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))

#define BEZOWY        0xFFFFADAA
#define BIALY         0xFFFFFFAA
#define BLEKITNY      0x33CCFFAA
#define BORDOWY       0x99001FAA
#define BRAZOWY       0x997A00AA
#define DARK_ZIELONY  0x336633AA
#define CZARNY        0x000000AA
#define CZERWONY      0xFF0000AA
#define FIOLETOWY     0xC2A2DAAA
#define NIEBIESKI     0x0000FFAA
#define POMARANCZOWY  0xFF8000AA
#define ROZOWY        0xFF66CCAA
#define SZARY         0xB0B0B0AA
#define ZIELONY       0x00CC00AA
#define ZOLTY         0xFFFF00AA
#define LCZERWONY     0xFF6347AA

#define STRING_LEN        512

#define PLACE_NONE        0
#define PLACE_PLAYER      1
#define PLACE_VEHICLE     2
#define PLACE_HOUSE       3
 
#define FAMILY_PD         0
#define FAMILY_SANNEWS    1
#define FAMILY_HOSPITAL   2
#define FAMILY_GOV        4

#define BIZZTYPE_NONE     0
#define BIZZTYPE_BAR      1
#define BIZZTYPE_STACJA   2
#define BIZZTYPE_WARSZTAT 3

#define ITEM_NONE         0
#define ITEM_GUN          1
#define ITEM_PHONE        2
#define ITEM_RADIO        3
#define ITEM_WATCH        4
#define ITEM_NARZEDZIA    5
#define ITEM_KARNISTER    6

#define WORK_NONE         0
#define WORK_SWEEPER      1
#define WORK_TRASH        2

#define MAX_ITEMS         998

native SQL_Connect(sqlhost[], sqluser[], sqlpass[], sqldb[]);
native SQL_Disconnect();
native SQL_Check();

native SQL_SaveCar(idx);
native SQL_SaveBizz(n);
native SQL_SaveShop(n);
native SQL_SaveItem(n);
native SQL_SaveHouse(n);

native PlayerName(playerid);
native PlayerName2(playerid);

native UnderscoreToSpace(name[]);
native sscanf(string[], format[], {Float,_}:...);
native explode(string[], dest[][], token = ' ', max = sizeof (dest), ml = sizeof (dest[]));

native FloatToInt(Float:var);

native SendClientMessageToAllEx(Float:radi, playerid, color, string2[]);
native ProxDetector(Float:radi, playerid, string2[],col1,col2,col3,col4,col5);
native ProxDetectorS(Float:radi, playerid, targetid);
native PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
native PlayerToVeh(Float:radi,playerid,carid);

native ScriptGivePlayerMoney(playerid, cashvar);

native RemovePlayerWeapon(playerid, weaponid);
native GetWeaponAmmo(playerid, weaponid);

native ClearPlayerChat(playerid);
native SendBizzMessage(bizz, color, string2[]);
native SendFamilyMessage(family, color, string2[]);
native SendRadioMessage(senderid, kanal, string2[]);
native SendMessageToAdmins(color, string2[]);
native SendWantedMessage(wantedid, reason[]);
native SendTaxiMessage(string2[]);
native SendDepartamentMessage(string2[]);
native SendOOCMessage(color, string2[]);

native GetPlayerFamily(playerid);
native GetPlayerBizz(playerid);

native GetPlayerWeaponSlot(playerid, weaponid);
native GetPlayerWeaponAmmo(playerid, weaponid);
native GetPlayerUseWeapon(playerid);
native GetPlayerItemTypeCount(playerid, itemtype);
native DeleteItem(itemid);
native HavePlayerWeapon(playerid, weaponid);
native GetPlayerItemTypeID(playerid, itemtype);
native GetPlayerIDBySQLID(sqlid);

native CountPlayerWarns(playerid);

native GetVehicleIDByUID(vehuid);
native GetVehicleDriver(vehicleid);
native GetDistanceToCar(playerid,vehicleid);
native GetClosestCar(playerid);
native GetVehicleName(vehicleid);
native GetVehicleName2(modelid);

//_Enumy
enum pInfo
{
	pHaslo[128],
	pAdmin,
	pSkin,
	pCash,
	pBankCash,
	pAge,
	pBan,
	pCrash,
	pAJ,
	pAJTime,
	pBW,
	pBWTime,
	pJail,
	pJailTime,
	pOnlineTime,
	pPremium,
	pFamMember,
	pFamRank,
	pFamSkin,
	pBizzMember,
	pBizzRank,
	pWork,
	pWorkPoints,
	pHotel,
	pHotelLock,
	pCK,
	pDowod,
	pCarLic,
	pMotorLic,
	pFlyLic,
	pGunLic,
	Float:pPosX,
	Float:pPosY,
	Float:pPosZ,
	pInt,
	pInLocal,
	pOwnHouse,
	pHouse,
	pDeaths,
	pKills,
	pSex,
	pSQLID
}
stock PlayerInfo[MAX_PLAYERS][pInfo];