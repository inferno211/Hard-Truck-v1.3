/*
  Anti Tibia Kids++
         by
      Przemcio

Trzy dodatkowe funkcje:
- Anty Money Cheat,
- Anty Health Cheat,
- Anty ArmourCheat,
- Anty Strval Crash.
*/

#if defined _atk_included
	#endinput
#endif
#define _atk_included
#pragma library atk

//Rozne definicje
#define ATK_dcmd(%1,%2,%3) if((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (ATK_dcmd_%1(playerid, ""))) || (((%3)[(%2) + 1] == 32) && (ATK_dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define ATK_MAX_STRING 100
#define ATK_ConfigDirectory "Anti Tibia Kids/AntyCheatConfig.ini"

//Definicje kolorow
#define ATK_RED 0xFF0000AA
#define ATK_GREEN 0x33AA33AA
#define ATK_WHITE 0xFFFFFFFF

//Enum'y
enum ATK_Opcje
{
	//Opcje
	bool:AntyCrash,
	AntiMoneyCheat,
	AntiHealthCheat,
	AntiArmourCheat,
	
	//Inne
	ATK_HighestID
}

enum ATK_GraczeInfo
{
	//Anty Money Cheat
	Kasa,

	//Anty Health Cheat/Vehicle Health Cheat
	Float:Zycie,
	Float:ZycieWozu,
	
	//Anty Armor Cheat
	Float:Kamizelka,
	
	//Inne
	bool:Pobrane,
	bool:Prot,
	TimerPobierz,
	TimerProtekcja
}

//Tablice
new ATK_Anty[ATK_Opcje];
new ATK_GraczInfo[MAX_PLAYERS][ATK_GraczeInfo];

//Forward'y (Timer'y)
forward ATK_AntyMoneyCheat();
forward ATK_AntyHealthCheat();
forward ATK_AntyArmourCheat();

//Forward (Timer'y Ex)
forward ATK_Pobierz(playerid);
forward ATK_Protekcja(playerid);

//Native'y
/*
	native ATK_strval(const string[]);
	native ATK_GivePlayerMoney(playerid, money);
	native ATK_SetPlayerHealth(playerid, Float:health);
	native ATK_SetPlayerArmour(playerid, Float:armour);
	native ATK_SetVehicleHealth(playerid, Float:health);
	native ATK_GetPlayerMoney(playerid);
	native ATK_GetPlayerHealth(playerid, &Float:health);
	native ATK_GetPlayerArmour(playerid, &Float:armour);
*/

//Callback'i
stock ATK_OnGameModeInit()
{
    //Wczytywanie - cheat'y
	if(ATK_dini_Int(ATK_ConfigDirectory, "AntyMoneyCheat") == 1)
		ATK_Anty[AntiMoneyCheat] = SetTimer("ATK_AntyMoneyCheat", 3000, 1);
    if(ATK_dini_Int(ATK_ConfigDirectory, "AntyHealthCheat") == 1)
		ATK_Anty[AntiHealthCheat] = SetTimer("ATK_AntyHealthCheat", 3000, 1);
    if(ATK_dini_Int(ATK_ConfigDirectory, "AntyArmorCheat") == 1)
		ATK_Anty[AntiArmourCheat] = SetTimer("ATK_AntyArmourCheat", 3000, 1);

	//Wczytywanie - inne
    ATK_Anty[AntyCrash] = bool:ATK_dini_Int(ATK_ConfigDirectory, "AntyStrvalCrash");
	return 1;
}

stock ATK_OnPlayerConnect(playerid)
{
    ATK_Anty[ATK_HighestID] = playerid > ATK_Anty[ATK_HighestID] - 1 ? playerid + 1 : ATK_Anty[ATK_HighestID];
	return 1;
}

stock ATK_OnPlayerDisconnect(playerid)
{
    if(playerid == ATK_Anty[ATK_HighestID] - 1)
		for(new i; i < ATK_Anty[ATK_HighestID]; i++)
		    ATK_Anty[ATK_HighestID] = IsPlayerConnected(i) ? i + 1 : ATK_Anty[ATK_HighestID];
	return 1;
}

stock ATK_OnPlayerSpawn(playerid)
{
	if(ATK_Anty[AntiMoneyCheat] != 0 || ATK_Anty[AntiHealthCheat] != 0 || ATK_Anty[AntiArmourCheat] != 0)
	{
		ATK_GraczInfo[playerid][Pobrane] = false;
		ATK_GraczInfo[playerid][TimerPobierz] = SetTimerEx("ATK_Pobierz", 3000, 0, "d", playerid);
	}
	return 1;
}

stock ATK_OnPlayerCommandText(playerid, cmdtext[])
{
	ATK_DashToUnderline(cmdtext);

	//On/Off
	ATK_dcmd(atk_money, 9, cmdtext);
	ATK_dcmd(atk_health, 10, cmdtext);
	ATK_dcmd(atk_armor, 9, cmdtext);
	ATK_dcmd(atk_crash, 9, cmdtext);
	if(strfind(cmdtext, "atk-money", true) != -1 || strfind(cmdtext, "atk-health", true) != -1 || strfind(cmdtext, "atk-armor", true) != -1 || strfind(cmdtext, "atk-crash", true) != -1)
		return 1;
	return 0;
}

stock ATK_OnPlayerPickUpPickup(playerid)
{
	if(ATK_GraczInfo[playerid][Prot] == false)
	{
		ATK_GraczInfo[playerid][Prot] = true;
		ATK_GraczInfo[playerid][TimerProtekcja] = SetTimerEx("ATK_Protekcja", 1000, 0, "d", playerid);
	}
	return 1;
}

stock ATK_OnPlayerStateChange(playerid, newstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
	    new Float:HP;
	    GetVehicleHealth(GetPlayerVehicleID(playerid), HP);
	    ATK_GraczInfo[playerid][ZycieWozu] = HP;
	}
	return 1;
}

//Timer'y
public ATK_AntyMoneyCheat()
{
    new VehID;
	new VehModel;
	for(new i; i < ATK_Anty[ATK_HighestID]; i++)
	{
	    if(IsPlayerConnected(i) && !IsPlayerAdmin(i))
	    {
			VehID = GetPlayerVehicleID(i);
	    	VehModel = GetVehicleModel(VehID);
			if(GetPlayerMoney(i) > ATK_GraczInfo[i][Kasa] && VehModel != 420 && VehModel != 438 && !ATK_IsPlayerInCasino(i) && ATK_GraczInfo[i][Pobrane] == true && ATK_GraczInfo[i][Prot] == false)
			{
		    	ATK_SetPlayerMoney(i, ATK_GraczInfo[i][Kasa]);
		    	return 1;
			}
			ATK_GraczInfo[i][Kasa] = GetPlayerMoney(i) != ATK_GraczInfo[i][Kasa] ? GetPlayerMoney(i) : ATK_GraczInfo[i][Kasa];
	   	}
	}
	return 1;
}

public ATK_AntyHealthCheat()
{
	new Float:HP;
	new VehID;
	new VehModel;
	for(new i; i < ATK_Anty[ATK_HighestID]; i++)
	{
	    if(IsPlayerConnected(i) && !IsPlayerAdmin(i))
	    {
	        GetPlayerHealth(i, HP);
	    	VehID = GetPlayerVehicleID(i);
		    VehModel = GetVehicleModel(VehID);
			if(!ATK_IsPlayerNearVendingMachine(i) && !ATK_IsPlayerInFastFood(i) && VehModel != 416 && HP > ATK_GraczInfo[i][Zycie] && ATK_GraczInfo[i][Zycie] != 0 && ATK_GraczInfo[i][Pobrane] == true && ATK_GraczInfo[i][Prot] == false)
			{
 	 			SetPlayerHealth(i, ATK_GraczInfo[i][Zycie]);
 	 			return 1;
			}
			ATK_GraczInfo[i][Zycie] = HP != ATK_GraczInfo[i][Zycie] ? HP : ATK_GraczInfo[i][Zycie];
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
			{
			    GetVehicleHealth(VehID, HP);
		    	if(!ATK_IsPlayerInPayNSpray(i) && !ATK_IsPlayerInTuningSalon(i) && (HP - ATK_GraczInfo[i][ZycieWozu]) > 1 && ATK_GraczInfo[i][ZycieWozu] != 0 && ATK_GraczInfo[i][Pobrane] == true && ATK_GraczInfo[i][Prot] == false)
		    	{
 	 				SetVehicleHealth(VehID, ATK_GraczInfo[i][ZycieWozu]);
 	 				return 1;
				}
				ATK_GraczInfo[i][ZycieWozu] = HP != ATK_GraczInfo[i][ZycieWozu] ? HP : ATK_GraczInfo[i][ZycieWozu];
			}
		}
	}
	return 1;
}

public ATK_AntyArmourCheat()
{
	new Float:Armour;
	new VehID;
	new VehModel;
	for(new i; i < ATK_Anty[ATK_HighestID]; i++)
	{
	    if(IsPlayerConnected(i) && !IsPlayerAdmin(i))
	    {
	    	GetPlayerArmour(i, Armour);
	    	VehID = GetPlayerVehicleID(i);
	    	VehModel = GetVehicleModel(VehID);
			if(!ATK_IsPlayerInAmmuNation(i) && VehModel != 427 && Armour > ATK_GraczInfo[i][Kamizelka] && ATK_GraczInfo[i][Pobrane] == true && ATK_GraczInfo[i][Prot] == false)
			{
		    	ATK_SetPlayerArmour(i, ATK_GraczInfo[i][Kamizelka]);
		    	return 1;
			}
			ATK_GraczInfo[i][Kamizelka] = Armour != ATK_GraczInfo[i][Kamizelka] ? Armour : ATK_GraczInfo[i][Kamizelka];
		}
	}
	return 1;
}

//Timer'y Ex
public ATK_Pobierz(playerid)
{
    new Float:HP;
    ATK_GraczInfo[playerid][Pobrane] = true;
	ATK_GraczInfo[playerid][Kasa] = GetPlayerMoney(playerid);
	GetPlayerHealth(playerid, HP);
	ATK_GraczInfo[playerid][Zycie] = HP;
	GetPlayerArmour(playerid, HP);
	ATK_GraczInfo[playerid][Kamizelka] = HP;
	return KillTimer(ATK_GraczInfo[playerid][TimerPobierz]);
}

public ATK_Protekcja(playerid)
{
    ATK_GraczInfo[playerid][Prot] = false;
	return KillTimer(ATK_GraczInfo[playerid][TimerProtekcja]);
}

//Komendy
stock ATK_dcmd_atk_money(playerid, cmdtext[])
{
	if(IsPlayerAdmin(playerid))
	{
    	new idx;
		new tmp[140];
		tmp = ATK_strtok(cmdtext, idx, ' ');
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, ATK_WHITE, "U¯YJ: /amoneycheat [on - w³¹cz, off - wy³¹cz].");
			return 1;
		}
		if(strcmp(tmp, "on", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyMoneyCheat") == 0)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyMoneyCheat", 1);
				ATK_Anty[AntiMoneyCheat] = SetTimer("ATK_AntyMoneyCheat", 1000, 1);
				for(new i; i < ATK_Anty[ATK_HighestID]; i++)
				    if(IsPlayerConnected(i))
				    {
				    	ATK_GraczInfo[i][Pobrane] = false;
						ATK_GraczInfo[i][TimerPobierz] = SetTimerEx("ATK_Pobierz", 1000, 0, "d", i);
					}
				SendClientMessage(playerid, ATK_GREEN, "Anty Money Cheat w³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Money Cheat jest ju¿ w³¹czony!");
			return 1;
		}
		if(strcmp(tmp, "off", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyMoneyCheat") == 1)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyMoneyCheat", 0);
				KillTimer(ATK_Anty[AntiMoneyCheat]);
				ATK_Anty[AntiMoneyCheat] = 0;
				SendClientMessage(playerid, ATK_GREEN, "Anty Money Cheat wy³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Money Cheat jest ju¿ wy³¹czony!");
			return 1;
		}
	}
	else
		SendClientMessage(playerid, ATK_RED, "Nie jesteœ adminem!");
	return 1;
}

stock ATK_dcmd_atk_armor(playerid, cmdtext[])
{
	if(IsPlayerAdmin(playerid))
	{
    	new idx;
		new tmp[140];
		tmp = ATK_strtok(cmdtext, idx, ' ');
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, ATK_WHITE, "U¯YJ: /aarmor [on - w³¹cz, off - wy³¹cz].");
			return 1;
		}
		if(strcmp(tmp, "on", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyArmorCheat") == 0)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyArmorCheat", 1);
				ATK_Anty[AntiArmourCheat] = SetTimer("ATK_AntyArmourCheat", 1000, 1);
				for(new i; i < ATK_Anty[ATK_HighestID]; i++)
				    if(IsPlayerConnected(i))
				    {
				    	ATK_GraczInfo[i][Pobrane] = false;
						ATK_GraczInfo[i][TimerPobierz] = SetTimerEx("ATK_Pobierz", 1000, 0, "d", i);
					}
				SendClientMessage(playerid, ATK_GREEN, "Anty Armor Cheat w³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Armor Cheat jest ju¿ w³¹czony!");
			return 1;
		}
		if(strcmp(tmp, "off", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyArmorCheat") == 1)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyArmorCheat", 0);
				KillTimer(ATK_Anty[AntiArmourCheat]);
				ATK_Anty[AntiArmourCheat] = 0;
				SendClientMessage(playerid, ATK_GREEN, "Anty Armor Cheat wy³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Armor Cheat jest ju¿ wy³¹czony!");
			return 1;
		}
	}
	else
		SendClientMessage(playerid, ATK_RED, "Nie jesteœ adminem!");
	return 1;
}

stock ATK_dcmd_atk_health(playerid, cmdtext[])
{
	if(IsPlayerAdmin(playerid))
	{
    	new idx;
		new tmp[140];
		tmp = ATK_strtok(cmdtext, idx, ' ');
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, ATK_WHITE, "U¯YJ: /ahealth [on - w³¹cz, off - wy³¹cz].");
			return 1;
		}
		if(strcmp(tmp, "on", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyHealthCheat") == 0)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyHealthCheat", 1);
				ATK_Anty[AntiHealthCheat] = SetTimer("ATK_AntyHealthCheat", 1000, 1);
				for(new i; i < ATK_Anty[ATK_HighestID]; i++)
				    if(IsPlayerConnected(i))
				    {
				    	ATK_GraczInfo[i][Pobrane] = false;
						ATK_GraczInfo[i][TimerPobierz] = SetTimerEx("ATK_Pobierz", 1000, 0, "d", i);
					}
				SendClientMessage(playerid, ATK_GREEN, "Anty Health Cheat w³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Health Cheat jest ju¿ w³¹czony!");
			return 1;
		}
		if(strcmp(tmp, "off", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyHealthCheat") == 1)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyHealthCheat", 0);
				KillTimer(ATK_Anty[AntiHealthCheat]);
				ATK_Anty[AntiHealthCheat] = 0;
				SendClientMessage(playerid, ATK_GREEN, "Anty Health Cheat wy³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Health Cheat jest ju¿ wy³¹czony!");
			return 1;
		}
	}
	else
		SendClientMessage(playerid, ATK_RED, "Nie jesteœ adminem!");
	return 1;
}

ATK_dcmd_atk_crash(playerid, cmdtext[])
{
	if(IsPlayerAdmin(playerid))
	{
    	new idx;
		new tmp[140];
		tmp = ATK_strtok(cmdtext, idx, ' ');
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, ATK_WHITE, "U¯YJ: /acrash [on - w³¹cz, off - wy³¹cz].");
			return 1;
		}
		if(strcmp(tmp, "on", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyCommandCrash") == 0)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyCommandCrash", 1);
				ATK_Anty[AntyCrash] = true;
				SendClientMessage(playerid, ATK_GREEN, "Anty Command Crash w³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Command Crash jest ju¿ w³¹czony!");
			return 1;
		}
		if(strcmp(tmp, "off", true) == 0)
		{
			if(ATK_dini_Int(ATK_ConfigDirectory, "AntyCommandCrash") == 1)
			{
				ATK_dini_IntSet(ATK_ConfigDirectory, "AntyCommandCrash", 0);
				ATK_Anty[AntyCrash] = false;
				SendClientMessage(playerid, ATK_GREEN, "Anty Command Crash wy³¹czony.");
			}
			else
				SendClientMessage(playerid, ATK_RED, "Anty Command Crash jest ju¿ wy³¹czony!");
			return 1;
		}
	}
	else
		SendClientMessage(playerid, ATK_RED, "Nie jesteœ adminem!");
	return 1;
}

//Funkcje
stock ATK_strval(const string[]) //By Przemcio
{
	if(ATK_Anty[AntyCrash] == true)
	{
		if(strlen(string) < 49)
	    	return strval(string);
	}
	else
	    return strval(string);
	return -1;
}

stock ATK_GivePlayerMoney(playerid, money) //By Przemcio
{
	GivePlayerMoney(playerid, money);
	ATK_GraczInfo[playerid][Kasa] = ATK_Anty[AntiMoneyCheat] != 0 ? money + ATK_GraczInfo[playerid][Kasa] : ATK_GraczInfo[playerid][Kasa];
}

stock ATK_SetPlayerHealth(playerid, Float:health) //By Przemcio
{
	SetPlayerHealth(playerid, health);
	ATK_GraczInfo[playerid][Zycie] = ATK_Anty[AntiHealthCheat] != 0 ? health : ATK_GraczInfo[playerid][Zycie];
}

stock ATK_SetPlayerArmour(playerid, Float:armour) //By Przemcio
{
	SetPlayerArmour(playerid, armour);
	ATK_GraczInfo[playerid][Kamizelka] = ATK_Anty[AntiArmourCheat] != 0 ? armour : ATK_GraczInfo[playerid][Kamizelka];
}

stock ATK_SetVehicleHealth(vehicleid, Float:health) //By Przemcio
{
	SetVehicleHealth(vehicleid, health);
	ATK_GraczInfo[ATK_VehicleDriverID(vehicleid)][ZycieWozu] = ATK_Anty[AntiHealthCheat] != 0 ? health : ATK_GraczInfo[ATK_VehicleDriverID(vehicleid)][ZycieWozu];
}

stock ATK_GetPlayerMoney(playerid) //By Przemcio
    if(ATK_Anty[AntiMoneyCheat] != 0)
		return ATK_GraczInfo[playerid][Kasa];
	else
	    return GetPlayerMoney(playerid);
	
stock ATK_GetPlayerHealth(playerid, &Float:health) //By Przemcio
	if(ATK_Anty[AntiHealthCheat] != 0)
		health = ATK_GraczInfo[playerid][Zycie];
	else
		GetPlayerHealth(playerid, health);
	
stock ATK_GetPlayerArmour(playerid, &Float:armour) //By Przemcio
    if(ATK_Anty[AntiArmourCheat] != 0)
		armour = ATK_GraczInfo[playerid][Kamizelka];
	else
	    GetPlayerArmour(playerid, armour);
	
stock ATK_DashToUnderline(string[]) //By Przemcio
{
	for(new i; i < strlen(string); i++)
	{
	    if(string[i] == '-')
	    {
	        string[i] = '_';
	        break;
		}
		if(string[i] == '_')
	    {
	        string[i] = '-';
	        break;
	 	}
	}
}

stock ATK_IsPlayerInFastFood(playerid) //By Przemcio
{
	new Float:Koordy[3];
	GetPlayerPos(playerid, Koordy[0], Koordy[1], Koordy[2]);
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 377.7908,-67.4344,1001.5078))
	    return 1;
    if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 369.4730,-6.0175,1001.8516))
	    return 1;
    if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 373.9136,-118.8029,1001.4922))
	    return 1;
	return 0;
}

stock ATK_IsPlayerNearVendingMachine(playerid) //By Przemcio
{
    new Float:Koordy[3];
	GetPlayerPos(playerid, Koordy[0], Koordy[1], Koordy[2]);
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2480.86,-1959.27,12.9609))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1634.11,-2237.53,12.8906))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2139.52,-1161.48,23.3594))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2153.23,-1016.15,62.2344))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -1350.12,493.859,10.5859))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2229.19,286.414,34.7031))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1659.46,1722.86,10.2188))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2647.7,1129.66,10.2188))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2845.73,1295.05,10.7891))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1398.84,2222.61,10.4219))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -1455.12,2591.66,55.2344))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -76.0312,1227.99,19.125))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 662.43,-552.164,15.7109))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -253.742,2599.76,62.2422))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2271.73,-76.4609,25.9609))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1789.21,-1369.27,15.1641))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1729.79,-1943.05,12.9453))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2060.12,-1897.64,12.9297))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1928.73,-1772.45,12.9453))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2325.98,-1645.13,14.2109))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2352.18,-1357.16,23.7734))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1154.73,-1460.89,15.1562))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -1350.12,492.289,10.5859))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2118.97,-423.648,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2118.62,-422.414,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2097.27,-398.336,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2092.09,-490.055,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2063.27,-490.055,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2005.65,-490.055,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2034.46,-490.055,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2068.56,-398.336,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2039.85,-398.336,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2011.14,-398.336,34.7266))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -1980.79,142.664,27.0703))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2319.99,2532.85,10.2188))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1520.15,1055.27,10.00))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2503.14,1243.7,10.2188))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2085.77,2071.36,10.4531))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -862.828,1536.61,21.9844))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -14.7031,1175.36,18.9531))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -253.742,2597.95,62.2422))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 201.016,-107.617,0.898438))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1277.84,372.516,18.95))
		return 1;
	return 0;
}

stock ATK_IsPlayerInAmmuNation(playerid) //By Przemcio
{
    new Float:Koordy[3];
	GetPlayerPos(playerid, Koordy[0], Koordy[1], Koordy[2]);
   	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 295.3189,-80.7289,1001.5156))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 290.0399,-109.2075,1001.5156))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 295.6118,-38.5151,1001.5156))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 314.2589,-133.6644,999.6016))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 311.9561,-166.1419,999.60))
		return 1;
	return 0;
}

stock ATK_IsPlayerInTuningSalon(playerid) //By Przemcio
{
    new Float:Koordy[3];
	GetPlayerPos(playerid, Koordy[0], Koordy[1], Koordy[2]);
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 617.5361,-1.9900,1000.6451))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 615.2859,-124.2390,997.6894))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 616.7832,-74.8151,997.88))
		return 1;
	return 0;
}

stock ATK_IsPlayerInPayNSpray(playerid) //By Przemcio
{
    new Float:Koordy[3];
	GetPlayerPos(playerid, Koordy[0], Koordy[1], Koordy[2]);
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 719.9293, -458.3104, 16.3359))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -1420.4791, 2585.3062, 55.8433))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -100.1498, 1116.8021, 19.7417))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2065.5261, -1831.4979, 13.5469))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -2425.7446, 1021.7225, 50.3977))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1972.6194, 2162.5034, 11.0703))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 487.8560, -1738.7234, 11.1429))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 1024.9244, -1025.3754, 32.1016))
		return 1;
	if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], 2393.6694, 1490.1978, 10.8274))
		return 1;
    if(ATK_PlayerToPoint(3, Koordy[0], Koordy[1], Koordy[2], -1904.5692, 284.2686, 41.0469))
		return 1;
	return 0;
}

stock ATK_IsPlayerInCasino(playerid) //By Przemcio
{
    new Float:Koordy[3];
	new Interior = GetPlayerInterior(playerid);
	GetPlayerPos(playerid, Koordy[0], Koordy[1], Koordy[2]);
	if(ATK_IsPlayerInArea(Koordy[0], Koordy[1], 2142.4832, 2291.7983, 1573.4381, 1632.1499) && Interior == 1)
	    return 1;
    if(ATK_IsPlayerInArea(Koordy[0], Koordy[1], 1925.1508, 1974.3478, 968.2357, 1067.4281) && Interior == 10)
	    return 1;
    if(ATK_IsPlayerInArea(Koordy[0], Koordy[1], 1116.3370, 1143.4181, -11.2906, 10.6788) && Interior == 12)
	    return 1;
	return 0;
}

stock ATK_PlayerToPoint(Float:radi, Float:PlayerPosX, Float:PlayerPosY, Float:PlayerPosZ, Float:x, Float:y, Float:z) //Optimized by Przemcio
{
	new Float:tempposx, Float:tempposy, Float:tempposz;
	tempposx = (PlayerPosX - x);
	tempposy = (PlayerPosY - y);
	tempposz = (PlayerPosZ - z);
	if(((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		return 1;
	return 0;
}

stock ATK_VehicleDriverID(vehicleid) //By Jan "DracoBlue" Schütze
{
	for(new i; i < ATK_Anty[ATK_HighestID]; i++)
  		if((IsPlayerConnected(i)) && (GetPlayerVehicleID(i) == vehicleid) && (GetPlayerState(i) == 2))
	   		return i;
	return -1;
}

stock ATK_IsPlayerInArea(Float:PlayerPosX, Float:PlayerPosY, Float:minx, Float:maxx, Float:miny, Float:maxy) //By Alex "Y_Less" Cole (Optimized by Przemcio)
{
	if(PlayerPosX > minx && PlayerPosX < maxx && PlayerPosY > miny && PlayerPosY < maxy)
		return 1;
	return 0;
}

stock ATK_SetPlayerMoney(playerid, money) //By Jan "DracoBlue" Schütze (Edited by Sacky)
	GivePlayerMoney(playerid, money - GetPlayerMoney(playerid));
	
stock ATK_strtok(const string[], &index, seperator = ' ') //By Jan "DracoBlue" Schütze (Optimized by Przemcio)
{
	new length = strlen(string);
	new offset = index;
	new result[140];
	while((index < length) && (string[index] != seperator) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	index = (index < length) && (string[index] == seperator) ? index + 1 : index;
	return result;
}

stock ATK_equal(str1[], str2[], bool:ignorecase) //By Jan "DracoBlue" Schütze (Stolen from dutils.inc)
{
    if(strlen(str1) != strlen(str2))
		return false;
    if(strcmp(str1, str2, ignorecase) == 0)
		return true;
    return false;
}

stock ATK_strlower(txt[]) //By Jan "DracoBlue" Schütze (Stolen from dutils.inc)
{
	new tmp[ATK_MAX_STRING];
	tmp[0] = 0;
	if(txt[0] == 0)
		return tmp;
	new i = 0;
	for(i = 0; i < strlen(txt); i++)
		tmp[i] = tolower(txt[i]);
	tmp[strlen(txt)] = 0;
	return tmp;
}

stock ATK_ret_memcpy(source[], index = 0, numbytes) //By Jan "DracoBlue" Schütze (Stolen from dutils.inc)
{
	new tmp[ATK_MAX_STRING];
	new i = 0;
	tmp[0] = 0;
	if(index >= strlen(source))
		return tmp;
	numbytes = numbytes + index >= strlen(source) ? strlen(source) - index : numbytes;
	if(numbytes <= 0)
		return tmp;
	for(i = index; i < numbytes + index; i++)
	{
		tmp[i - index] = source[i];
		if(source[i] == 0)
			return tmp;
	}
	tmp[numbytes] = 0;
	return tmp;
}

stock ATK_set(dest[], source[]) //By Jan "DracoBlue" Schütze (Stolen from dutils.inc)
{
	new count = strlen(source);
	new i = 0;
	for(i = 0; i < count; i++)
		dest[i] = source[i];
	dest[count] = 0;
}

stock ATK_StripNewLine(string[]) //By Jan "DracoBlue" Schütze (Stolen from dutils.inc)
{
	new len = strlen(string);
	if(string[0] == 0)
		return ;
	if((string[len - 1] == '\n') || (string[len - 1] == '\r'))
	{
		string[len - 1] = 0;
		if(string[0] == 0)
			return ;
		if((string[len - 2] == '\n') || (string[len - 2] == '\r'))
			string[len - 2] = 0;
	}
}

stock ATK_fcopytextfile(oldname[], newname[]) //By Jan "DracoBlue" Schütze (Stolen from dutils.inc)
{
	new File:ohnd, File:nhnd;
	if(!fexist(oldname))
		return false;
	ohnd = fopen(oldname, io_read);
	nhnd = fopen(newname, io_write);
	new tmpres[ATK_MAX_STRING];
	while(fread(ohnd, tmpres))
	{
		ATK_StripNewLine(tmpres);
		format(tmpres, sizeof(tmpres), "%s\r\n", tmpres);
		fwrite(nhnd, tmpres);
	}
	fclose(ohnd);
	fclose(nhnd);
	return true;
}

stock ATK_dini_Set(filename[], key[], value[]) //By Jan "DracoBlue" Schütze (Stolen from dini.inc)
{
	new File:fohnd, File:fwhnd;
	new bool:wasset = false;
	new tmpres[ATK_MAX_STRING];
	if(key[0] == 0)
		return false;
	format(tmpres, sizeof(tmpres), "%s.part", filename);
	fohnd = fopen(filename, io_read);
	if(!fohnd)
		return false;
	fremove(tmpres);
	fwhnd = fopen(tmpres, io_write);
	while(fread(fohnd, tmpres))
	{
		ATK_StripNewLine(tmpres);
		if((!wasset) && (ATK_equal(ATK_dini_PRIVATE_ExtractKey(tmpres), key, true)))
		{
			format(tmpres, sizeof(tmpres), "%s=%s", key, value);
			wasset = true;
		}
		fwrite(fwhnd, tmpres);
		fwrite(fwhnd, "\r\n");
	}

	if(!wasset)
	{
		format(tmpres, sizeof(tmpres), "%s=%s", key, value);
		fwrite(fwhnd, tmpres);
		fwrite(fwhnd, "\r\n");
	}
	fclose(fohnd);
	fclose(fwhnd);
	format(tmpres, sizeof(tmpres), "%s.part", filename);
	if(ATK_fcopytextfile(tmpres, filename))
		return fremove(tmpres);
	return false;
}

stock ATK_dini_IntSet(filename[], key[], value) //By Jan "DracoBlue" Schütze (Stolen from dini.inc)
{
   new valuestring[ATK_MAX_STRING];
   format(valuestring, sizeof(valuestring), "%d", value);
   return ATK_dini_Set(filename, key, valuestring);
}

stock ATK_dini_Int(filename[], key[]) //By Jan "DracoBlue" Schütze (Stolen from dini.inc)
	return strval(ATK_dini_Get(filename, key));

stock ATK_dini_Get(filename[], key[]) //By Jan "DracoBlue" Schütze (Stolen from dini.inc)
{
	new File:fohnd;
	new tmpres[ATK_MAX_STRING];
	new tmpres2[ATK_MAX_STRING];
	tmpres[0] = 0;
	fohnd = fopen(filename, io_read);
	if(!fohnd)
		return tmpres;
	while(fread(fohnd,tmpres))
	{
		ATK_StripNewLine(tmpres);
		if(ATK_equal(ATK_dini_PRIVATE_ExtractKey(tmpres), key, true))
		{
			tmpres2[0] = 0;
			strcat(tmpres2, ATK_dini_PRIVATE_ExtractValue(tmpres));
			fclose(fohnd);
			return tmpres2;
		}
	}
	fclose(fohnd);
	return tmpres;
}

stock ATK_dini_PRIVATE_ExtractKey(line[]) //By Jan "DracoBlue" Schütze (Stolen from dini.inc)
{
	new tmp[ATK_MAX_STRING];
	tmp[0] = 0;
	if(strfind(line, "=", true) == -1)
		return tmp;
	ATK_set(tmp, ATK_strlower(ATK_ret_memcpy(line, 0, strfind(line, "=", true))));
	return tmp;
}

stock ATK_dini_PRIVATE_ExtractValue(line[]) //By Jan "DracoBlue" Schütze (Stolen from dini.inc)
{
    new tmp[ATK_MAX_STRING];
    tmp[0] = 0;
    if(strfind(line, "=", true) == -1)
		return tmp;
    ATK_set(tmp, ATK_ret_memcpy(line, strfind(line, "=", true) + 1, strlen(line)));
    return tmp;
}

//Podmiana funkcji za funkcje z Anti Tibia Kids
#define strval ATK_strval
#define GivePlayerMoney ATK_GivePlayerMoney
#define SetPlayerHealth ATK_SetPlayerHealth
#define SetPlayerArmour ATK_SetPlayerArmour
#define SetVehicleHealth ATK_SetVehicleHealth
#define GetPlayerMoney ATK_GetPlayerMoney
#define GetPlayerHealth ATK_GetPlayerHealth
#define GetPlayerArmour ATK_GetPlayerArmour
