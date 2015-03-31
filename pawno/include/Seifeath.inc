/*
							Seifeath - Seif's custom death list include
*/
/*x---------------------------------Important-------------------------------------x*/
//**INCLUDES**//
#include <a_samp>
//**PRAGMAS**//

//**MISC**//

/*x---------------------------------Defining-------------------------------------x*/
//**VARIABLES**//
new DeathMsgName[5][128];
new DeathMsgWeapon[5][128];
new DeathMsgName2[5][128];
new DeathColorName[5];
new DeathColorName2[5];
new Text:DeathMsg_Name[5];
new Text:DeathMsg_Weapon[5];
new Text:DeathMsg_Name2[5];
//new Text:DeathMsg_Box;
new Float:DeathMsgY = 412.000000;

// BY Simon - edited by Seif
new ReasonNames[][32] = {
	{"Fist"}, // 0
	{"Brass Knuckles"}, // 1
	{"Golf Club"}, // 2
	{"Night Stick"}, // 3
	{"Knife"}, // 4
	{"Baseball Bat"}, // 5
	{"Shovel"}, // 6
	{"Pool Cue"}, // 7
	{"Katana"}, // 8
	{"Chainsaw"}, // 9
	{"Purple Dildo"}, // 10
	{"Big Vibrator"}, // 11
	{"Med Vibrator"}, // 12
	{"Small Vibrator"}, // 13
	{"Flowers"}, // 14
	{"Cane"}, // 15
	{"Grenade"}, // 16
	{"Teargas"}, // 17
	{"Molotov"}, // 18
	{"???"}, // 19
	{"???"}, // 20
	{"???"}, // 21
	{"Colt 45"}, // 22
	{"SD Pistol"}, // 23
	{"Desert Eagle"}, // 24
	{"Shotgun"}, // 25
	{"Sawnoff"}, // 26
	{"Combat Shotty"}, // 27
	{"Micro Uzi"}, // 28
	{"MP5"}, // 29
	{"AK47"}, // 30
	{"M4"}, // 31
	{"Tec9"}, // 32
	{"Country Rifle"}, // 33
	{"Sniper Rifle"}, // 34
	{"Rocket Launcher"}, // 35
	{"Heat-Seeking RPG"}, // 36
	{"Flamethrower"}, // 37
	{"Minigun"}, // 38
	{"Satchel Charge"}, // 39
	{"Detonator"}, // 40
	{"Spray Can"}, // 41
	{"Fire Extinguisher"}, // 42
	{"Camera"}, // 43
	{"Night Vision Goggles"}, // 44
	{"Infrared Vision Goggles"}, // 45
	{"Parachute"}, // 46
	{"???"} // 47
};
// **FORWARDS** //

/*x---------------------------------CallBacks-------------------------------------x*/
forward Seifeath_OnInit();
public  Seifeath_OnInit()
{
    /*DeathMsg_Box = TextDrawCreate(150.000000,363.000000,"_~n~~n~~n~~n~~n~~n~~n~");
    TextDrawUseBox(DeathMsg_Box,1);
	TextDrawBoxColor(DeathMsg_Box,0xff000033);
	TextDrawTextSize(DeathMsg_Box,354.000000,0.000000);
	TextDrawAlignment(DeathMsg_Box,0);
	TextDrawBackgroundColor(DeathMsg_Box,0x000000ff);
	TextDrawFont(DeathMsg_Box,2);
	TextDrawLetterSize(DeathMsg_Box,0.499998,1.000000);
	TextDrawColor(DeathMsg_Box,0xffffffff);
	TextDrawSetOutline(DeathMsg_Box,1);
	TextDrawSetProportional(DeathMsg_Box,1);
	TextDrawSetShadow(DeathMsg_Box,1);*/
	for(new t = 0; t < 5; t++)
	{
	    printf("%f",DeathMsgY);
	    Seifeath_CreateDeathMessage(t, DeathMsgY);
	    TextDrawShowForAll(DeathMsg_Name[t]);
	    TextDrawShowForAll(DeathMsg_Weapon[t]);
	    TextDrawShowForAll(DeathMsg_Name2[t]);
	    DeathMsgY -= 12.0;
		strmid(DeathMsgName[t], "_", 0, 1);
		strmid(DeathMsgWeapon[t], "_", 0, 1);
		strmid(DeathMsgName2[t], "_", 0, 1);
	}
	//TextDrawShowForAll(DeathMsg_Box);
	DeathMsgY = 364.000000;
}

forward Seifeath_OnExit();
public  Seifeath_OnExit()
{
	for(new t = 0; t < 5; t++)
	{
	    TextDrawDestroy(DeathMsg_Name[t]);
	    TextDrawDestroy(DeathMsg_Name2[t]);
	    TextDrawDestroy(DeathMsg_Weapon[t]);
	}
	//TextDrawDestroy(DeathMsg_Box);
}

forward Seifeath_OnPlayerConnect(playerid);
public  Seifeath_OnPlayerConnect(playerid)
{
//    TextDrawShowForPlayer(playerid, DeathMsg_Box);
	for(new t = 0; t < 5; t++)
	{
		TextDrawShowForPlayer(playerid, DeathMsg_Name[t]);
	 	TextDrawShowForPlayer(playerid, DeathMsg_Weapon[t]);
		TextDrawShowForPlayer(playerid, DeathMsg_Name2[t]);
	}
}

forward Seifeath_CreateDeathMessage(id, Float:y);
public  Seifeath_CreateDeathMessage(id, Float:y)
{
    DeathMsg_Name[id] = TextDrawCreate(142.000000,y,"_");
	DeathMsg_Weapon[id] = TextDrawCreate(232.000000,y,"_");
	DeathMsg_Name2[id] = TextDrawCreate(281.000000,y,"_");
	TextDrawUseBox(DeathMsg_Weapon[id],1);
	TextDrawBoxColor(DeathMsg_Weapon[id],0x000000B4);
	TextDrawTextSize(DeathMsg_Weapon[id],266.000000,0.000000);
	TextDrawAlignment(DeathMsg_Name[id],0);
	TextDrawAlignment(DeathMsg_Weapon[id],0);
	TextDrawAlignment(DeathMsg_Name2[id],0);
	TextDrawBackgroundColor(DeathMsg_Name[id],0x000000ff);
	TextDrawBackgroundColor(DeathMsg_Weapon[id],0x000000ff);
	TextDrawBackgroundColor(DeathMsg_Name2[id],0x000000ff);
	TextDrawFont(DeathMsg_Name[id],1);
	TextDrawLetterSize(DeathMsg_Name[id],0.200000,0.700000);
	TextDrawFont(DeathMsg_Weapon[id],2);
	TextDrawLetterSize(DeathMsg_Weapon[id],0.099999,0.699999);
	TextDrawFont(DeathMsg_Name2[id],1);
	TextDrawLetterSize(DeathMsg_Name2[id],0.200000,0.700000);
	TextDrawColor(DeathMsg_Name[id],0xff0000cc);
	TextDrawColor(DeathMsg_Weapon[id],0xffffffff);
	TextDrawColor(DeathMsg_Name2[id],0xff0000cc);
	TextDrawSetOutline(DeathMsg_Name[id],1);
	TextDrawSetOutline(DeathMsg_Weapon[id],1);
	TextDrawSetOutline(DeathMsg_Name2[id],1);
	TextDrawSetProportional(DeathMsg_Name[id],1);
	TextDrawSetProportional(DeathMsg_Weapon[id],1);
	TextDrawSetProportional(DeathMsg_Name2[id],1);
	TextDrawSetShadow(DeathMsg_Name[id],1);
	TextDrawSetShadow(DeathMsg_Weapon[id],1);
	TextDrawSetShadow(DeathMsg_Name2[id],1);
}

forward SendDeathText(killerid, victimid, reason);
public  SendDeathText(killerid, victimid, reason)
{
	new killername[MAX_PLAYER_NAME];
	new victimname[MAX_PLAYER_NAME];
	if (!IsPlayerConnected(killerid) || killerid == INVALID_PLAYER_ID) strmid(killername, " ", 0, 1);
	else GetPlayerName(killerid, killername, sizeof(killername));
	if (!IsPlayerConnected(victimid) || victimid == INVALID_PLAYER_ID) strmid(victimname, " ", 0, 1);
	else GetPlayerName(victimid, victimname, sizeof(victimname));
    for(new t = 4; t > 0; t--)
	{
	    printf("loop %d", t);
	    /*if (strlen(GetReasonName(reason)) > 12)
		{
			TextDrawTextSize(DeathMsg_Weapon[t],266.000000+(strlen(GetReasonName(reason))-12),0.000000);
			TextDrawShowForAll(DeathMsg_Weapon[t]);
		}*/
     	TextDrawSetString(DeathMsg_Name[t], DeathMsgName[t-1]);
	    TextDrawSetString(DeathMsg_Weapon[t], DeathMsgWeapon[t-1]);
	    TextDrawSetString(DeathMsg_Name2[t], DeathMsgName2[t-1]);
    	strmid(DeathMsgName[t], DeathMsgName[t-1], 0, strlen(DeathMsgName[t-1]), 128);
    	strmid(DeathMsgWeapon[t], DeathMsgWeapon[t-1], 0, strlen(DeathMsgWeapon[t-1]), 128);
    	strmid(DeathMsgName2[t], DeathMsgName2[t-1], 0, strlen(DeathMsgName2[t-1]), 128);
    	DeathColorName[t] = DeathColorName[t-1];
    	DeathColorName2[t] = DeathColorName2[t-1];
    	TextDrawColor(DeathMsg_Name[t], DeathColorName[t-1]);
    	TextDrawColor(DeathMsg_Name2[t], DeathColorName2[t-1]);
    	TextDrawShowForAll(DeathMsg_Name[t]);
    	TextDrawShowForAll(DeathMsg_Name2[t]);
	}
	/*if (strlen(GetReasonName(reason)) > 12)
	{
		TextDrawTextSize(DeathMsg_Weapon[0],266.000000+(strlen(GetReasonName(reason))-12),0.000000);
		TextDrawShowForAll(DeathMsg_Weapon[0]);
	}*/
	TextDrawColor(DeathMsg_Name[0], GetPlayerColor(killerid));

   	TextDrawColor(DeathMsg_Name2[0], GetPlayerColor(victimid));
   	print("dbg2");
	TextDrawSetString(DeathMsg_Name[0], killername);
	print("dbg3");
   	TextDrawSetString(DeathMsg_Weapon[0], GetReasonName(reason, killerid));
   	print("dbg4");
   	TextDrawSetString(DeathMsg_Name2[0], victimname);
   	print("dbg5");
    strmid(DeathMsgName[0], killername, 0, strlen(killername), 128);
    print("dbg6");
   	strmid(DeathMsgWeapon[0], GetReasonName(reason, killerid), 0, strlen(GetReasonName(reason, killerid)), 128);
   	print("dbg7");
   	strmid(DeathMsgName2[0], victimname, 0, strlen(victimname), 128);
   	print("dbg8");
    DeathColorName[0] = GetPlayerColor(killerid);
    print("dbg9");
   	DeathColorName2[0] = GetPlayerColor(victimid);
   	print("dbg10");
    TextDrawShowForAll(DeathMsg_Name[0]);
    print("dbg11");
   	TextDrawShowForAll(DeathMsg_Name2[0]);
   	print("dbg12");
}

GetReasonName(reason, killerid)
{
	new reas[50];
	if (reason == 31 && GetPlayerState(killerid) == PLAYER_STATE_DRIVER && GetVehicleModel(GetPlayerVehicleID(killerid)) == 447)
	{
	    strmid(reas, "Sparrow M4", 0, strlen("Sparrow M4"), 50);
 		return reas;
	}
	else if (reason == 38 && GetPlayerState(killerid) == PLAYER_STATE_DRIVER && GetVehicleModel(GetPlayerVehicleID(killerid)) == 425)
	{
	    strmid(reas, "Hunter Minigun", 0, strlen("Hunter Minigun"), 50);
 		return reas;
	}
	else if (reason == 49)
	{
	    strmid(reas, "Vehicle", 0, strlen("Vehicle"), 50);
 		return reas;
	}
	else if (reason == 50)
	{
	    strmid(reas, "Heli Blades", 0, strlen("Heli Blades"), 50);
 		return reas;
	}
	else if (reason == 51 && GetPlayerState(killerid) == PLAYER_STATE_DRIVER && GetVehicleModel(GetPlayerVehicleID(killerid)) == 520)
	{
	    strmid(reas, "Hydra Missile", 0, strlen("Hydra Missile"), 50);
 		return reas;
	}
	else if (reason == 51 && GetPlayerState(killerid) == PLAYER_STATE_DRIVER && GetVehicleModel(GetPlayerVehicleID(killerid)) == 425)
	{
	    strmid(reas, "Hunter Missile", 0, strlen("Hunter Missile"), 50);
 		return reas;
	}
	else if (reason == 51)
	{
	    strmid(reas, "Explosion", 0, strlen("Explosion"), 50);
 		return reas;
	}
	else if (reason == 53)
	{
	    strmid(reas, "Drowned", 0, strlen("Drowned"), 50);
 		return reas;
	}
	else if (reason == 54)
	{
	    strmid(reas, "Collision", 0, strlen("Collision"), 50);
 		return reas;
	}
	else if (reason == 200)
	{
	    strmid(reas, "Connected", 0, strlen("Connected"), 50);
 		return reas;
	}
	else if (reason == 201)
	{
	    strmid(reas, "Disconnected", 0, strlen("Disconnected"), 50);
 		return reas;
	}
	else if (reason == 255)
	{
	    strmid(reas, "Suicide", 0, strlen("Suicide"), 50);
 		return reas;
	}
	else if (reason > sizeof(ReasonNames))
	{
	    strmid(reas, "???", 0, strlen("???"), 50);
 		return reas;
	}
	strmid(reas, ReasonNames[reason], 0, strlen(ReasonNames[reason]), 50);
	return reas;
}

forward SetPlayerColorFix(playerid);
public  SetPlayerColorFix(playerid)
	return SetPlayerColor(playerid,((random(256)*16777216)+(random(256)*65536)+(random(256)*256)+255));
