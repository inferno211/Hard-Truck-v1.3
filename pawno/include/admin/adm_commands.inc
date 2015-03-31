//
// Created: 18.12.2007
// Aurthor: Dmitry Frolov (FP)
//

#if defined _adm_commands_included
#endinput
#endif

#define _adm_commands_included
#pragma library adm_commands
#include "base"
#include "utils\gtoutils"
#include "player"
#include "account"
#include "race"

forward AdmCommandHandler(playerid,text[]);

public AdmCommandHandler(playerid,text[]) // process player commands
{
if (!IsPlayerConnected(playerid)) return 0;
if ( (!IsPlayerAdmin(playerid)) && (!IsPlayerAdm(playerid)) )
{
return 0;
}

new cmd[20];
new idx;
//set(cmd,strcharsplit(text, idx,strchar(" ")));
//if(strcomp(cmd, "/admin", true) == 0) return 0;

set(cmd,strcharsplit(text, idx,strchar(" ")));

if(strcomp(cmd, "/cmdlist", true) == 1)
{
//SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);
  SendClientMessage(playerid, COLOUR_LIGHTBLUE, "A: '/say <text>', '/pinfo <ID>'");
  SendClientMessage(playerid, COLOUR_LIGHTBLUE, "A: '/akill <ID>', '/paralyze <ID>', '/deparalyze <ID>'");
  SendClientMessage(playerid, COLOUR_LIGHTBLUE, "A: '/tele-set', '/tele-loc', '/tele-to <ID>', '/tele-here <ID>', '/tele-hereall'");
  SendClientMessage(playerid, COLOUR_LIGHTBLUE, "A: '/sethealth <ID>', '/setarm <ID>', '/givexp <ID> <xp>', '/agivecash <ID> <cash>', '/givegun <ID> <IDgun>'");
}


if(strcomp(cmd, "/about", true) == 1)
{
//SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);
  SendClientMessage(playerid, COLOUR_LIGHTBLUE, lang_texts[15][47]);
  SendClientMessage(playerid, COLOUR_LIGHTBLUE, lang_texts[15][48]);
  SendClientMessage(playerid, COLOUR_LIGHTBLUE, lang_texts[15][49]);
}

if(strcomp(cmd, "/say", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new string[MAX_STRING];
set(string,text);
strdel(string, 0, idx);
format(string,sizeof(string), lang_texts[12][37] ,string);
SendClientMessageToAll(COLOUR_BLUE, string);
return 1;
}


if(strcomp(cmd, "/pinfo", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid=INACTIVE_PLAYER_ID;

receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS))
{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][34] ,oGetPlayerName(receiverid),receiverid);
SendPlayerFormattedText(playerid,string, 0,COLOUR_YELLOW);

new sid;
sid=Player[receiverid][Status];
if (sid>0 && sid<10) {format(string,sizeof(string),lang_texts[12][87],sid);}
else if (sid>10) {format(string,sizeof(string),lang_texts[12][86],sid);}
else {format(string,sizeof(string),lang_texts[12][88]);}
//Status
SendPlayerFormattedText(playerid,string, 0,COLOUR_LIGHTRED);

format(string,sizeof(string), lang_texts[12][35] ,Player[receiverid][Level],Player[receiverid][XP]);	//Level, XP
SendPlayerFormattedText(playerid,string, 0,COLOUR_WHITE);
format(string,sizeof(string), lang_texts[12][36] ,Player[receiverid][Money],Player[receiverid][Bank]);	//Money, Bank
SendPlayerFormattedText(playerid,string, 0,COLOUR_WHITE);

format(string,sizeof(string), lang_texts[12][38] ,Player[receiverid][Deaths],Player[receiverid][Kills]);	//Kills, Deaths
SendPlayerFormattedText(playerid,string, 0,COLOUR_WHITE);
format(string,sizeof(string), lang_texts[12][71] ,Player[receiverid][Jailed],Player[receiverid][Muted]);	//Jailed, Muted
SendPlayerFormattedText(playerid,string, 0,COLOUR_WHITE);

new PlayerIP[256];
GetPlayerIp(receiverid,PlayerIP,256);
format(string,sizeof(string), lang_texts[12][72] ,GetPlayerPing(receiverid),PlayerIP);
SendPlayerFormattedText(playerid,string, 0,COLOUR_WHITE);
return 1;
}


//Добавить сюда REPLACE Запрещенных символов

if(strcomp(cmd, "/admincnn", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new string[MAX_STRING];
set(string,text);
strdel(string, 0, idx);
format(string,sizeof(string), "%s" ,string);
//SendClientMessageToAll(COLOUR_YELLOW, string);
GameTextForAll(string,4000,6);
return 1;
}

//--------------------------------------------KICK


if(strcomp(cmd, "/akill", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid=INACTIVE_PLAYER_ID;

receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)))
{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}
SetPlayerHealth(receiverid, 0);
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][62] ,oGetPlayerName(receiverid),receiverid);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
format(string,sizeof(string), lang_texts[12][63] ,oGetPlayerName(playerid));
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);
return 1;
}




//--------------------------------------------------TELEPORT
if(strcomp(cmd, "/tele-set", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

GetPlayerPos(playerid, LocX[playerid], LocY[playerid], LocZ[playerid] );
GetPlayerFacingAngle(playerid, Ang[playerid] );
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][68] ,LocX[playerid],LocY[playerid],LocZ[playerid],Ang[playerid]);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
return 1;
}

if (strcomp(cmd, "/tele-loc", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, cmd);
if(LocX[playerid] == 0.0 && LocY[playerid] == 0.0 && LocZ[playerid] == 0.0) {
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][69]);
SendPlayerFormattedText(playerid,string, 0,COLOUR_RED);
} else {
	if(IsPlayerInAnyVehicle(playerid)) {
		new VehicleID;
		VehicleID = GetPlayerVehicleID(playerid);
		SetVehiclePos(VehicleID, LocX[playerid], LocY[playerid], LocZ[playerid] );
		SetPlayerFacingAngle(playerid, Ang[playerid] );
		} else {
			SetPlayerPos(playerid, LocX[playerid], LocY[playerid], LocZ[playerid] );
			SetPlayerFacingAngle(playerid, Ang[playerid] );
			}
	new string[MAX_STRING];
	format(string,sizeof(string), lang_texts[12][70]);
	SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
	}
return 1;
}


if(strcomp(cmd, "/tele-to", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
//if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)) )

if ((receiverid < 0) || (receiverid >= MAX_PLAYERS))

{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}
new Float:X;
new Float:Y;
new Float:Z;
new Float:Angle;
if(IsPlayerInAnyVehicle(playerid)) {
//They're in a vehicle. Transport it, too.
new VehicleID;
VehicleID = GetPlayerVehicleID(playerid);
GetPlayerPos(receiverid,X,Y,Z);
GetPlayerFacingAngle(receiverid,Angle);
SetVehiclePos(VehicleID, X + 3.01, Y + 3.01, Z + 1);
SetPlayerFacingAngle(playerid,Angle);
} else {
	GetPlayerPos(receiverid,X,Y,Z);
	GetPlayerFacingAngle(receiverid,Angle);
	SetPlayerFacingAngle(playerid,Angle);
	X=X+(random(2)-random(4));Y=Y+(random(2)-random(4));	
	SetPlayerPos(playerid, X, Y, Z + 1);
	}
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][66] ,oGetPlayerName(receiverid),receiverid);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
return 1;
}

if(strcomp(cmd, "/tele-here", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}
if ( (IsPlayerConnected(receiverid) == 0) && !IsPlayerInAnyDM(receiverid) )
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}
new Float:X;
new Float:Y;
new Float:Z;
new Float:Angle;
if(IsPlayerInAnyVehicle(receiverid)) {
//They're in a vehicle. Transport it, too.
new VehicleID;
GetPlayerPos(playerid,X,Y,Z);
VehicleID = GetPlayerVehicleID(receiverid);
SetVehiclePos(VehicleID, X + 3.01, Y + 3.01, Z + 1);
GetPlayerFacingAngle(playerid,Angle);
SetPlayerFacingAngle(receiverid,Angle);
} else {
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
	SetPlayerFacingAngle(receiverid,Angle);
	X=X+(random(2)-random(4));Y=Y+(random(2)-random(4));	
	SetPlayerPos(receiverid, X, Y, Z + 1);
	}
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][66] ,oGetPlayerName(playerid),playerid);
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);
format(string,sizeof(string), lang_texts[12][67] ,oGetPlayerName(receiverid),receiverid);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
return 1;
}


if(strcomp(cmd, "/tele-hereall", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new Float:X;
new Float:Y;
new Float:Z;
new Float:Angle;
GetPlayerPos(playerid,X,Y,Z);
GetPlayerFacingAngle(playerid,Angle);
new string[MAX_STRING];

for (new id = 0; id < MAX_PLAYERS; id++)
{
if ( (id < playerid) || (id > playerid))
	{
	if (IsPlayerConnected(id) && (Player[id][Jailed] == 0) && !IsPlayerAdmin(id)  && !IsPlayerInAnyDM(id) )
		{
		if (IsPlayerConnected(id) == 0) { return 0; }
		SetPlayerFacingAngle(id,Angle);
		X=X+(random(2)-random(4));Y=Y+(random(2)-random(4));	
		SetPlayerPos(id, X, Y, Z);
		format(string,sizeof(string), lang_texts[12][66] ,oGetPlayerName(playerid),playerid);
		SendPlayerFormattedText(id,string, 0,COLOUR_XP_GOOD);
		}
	}
}
format(string,sizeof(string), lang_texts[12][74]);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
return 1;
}

if(strcomp(cmd, "/sethealth", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)))
{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}
new hltamount;
hltamount = strval(strcharsplit(text, idx,strchar(" ")));
if ((hltamount < 10) || (hltamount > 300))
{
SendPlayerFormattedText(playerid, lang_texts[12][44] , 0,COLOUR_RED);
return 1;
}
SetPlayerHealth(receiverid, hltamount);
return 1;
}


if(strcomp(cmd, "/setarm", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)))
{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}
new armamount;
armamount = strval(strcharsplit(text, idx,strchar(" ")));
if ((armamount < 0) || (armamount > 300))
{
SendPlayerFormattedText(playerid, lang_texts[12][44] , 0,COLOUR_RED);
return 1;
}
SetPlayerArmour(receiverid, armamount);
return 1;
}



if(strcomp(cmd, "/givexp", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}

if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}

new xpamount;
xpamount = strval(strcharsplit(text, idx,strchar(" ")));

if ((xpamount == 0) || (xpamount > MAX_LVLXP))
{
SendPlayerFormattedText(playerid, lang_texts[12][4] , 0,COLOUR_RED);
return 1;
}

new xpamountkeep;
xpamountkeep = GetPlayerXP(receiverid)+xpamount;

if ((!IsPlayerAdmin(receiverid) && xpamountkeep >MAX_LVLXP) || (IsPlayerAdmin(receiverid) && xpamountkeep > MAX_XP))
{
    SendPlayerFormattedText(playerid, lang_texts[12][40] , 0,COLOUR_RED);
	if (IsPlayerAdmin(receiverid))
	{
	xpamount = xpamountkeep-MAX_XP;
	} else {
	xpamount = xpamountkeep-MAX_LVLXP;
	}
}

//GivePlayerXP(receiverid,xpamount,1);
SetPlayerXP(receiverid,Player[receiverid][XP]+xpamount);
Player[receiverid][XP]=GetPlayerXP(receiverid);

CheckPlayerLevel(receiverid);
new string[MAX_STRING];

if (xpamount > 0)
{
format(string,sizeof(string), lang_texts[12][5] ,oGetPlayerName(playerid),xpamount);
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);

format(string,sizeof(string), lang_texts[12][6] ,oGetPlayerName(receiverid),xpamount,GetPlayerXP(receiverid));
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
}
else
{
format(string,sizeof(string), lang_texts[12][7] ,oGetPlayerName(playerid),xpamount);
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);

format(string,sizeof(string), lang_texts[12][8] ,oGetPlayerName(receiverid),xpamount,GetPlayerXP(receiverid));
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
}

return 1;
}


if(strcomp(cmd, "/agivecash", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));

if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][9] , 0,COLOUR_RED);
return 1;
}

if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][10] , 0,COLOUR_RED);
return 1;
}

new cashamount;
cashamount = strval(strcharsplit(text, idx,strchar(" ")));

if ((cashamount < -999999) || (cashamount == 0) || (cashamount > 999999))
{
SendPlayerFormattedText(playerid, lang_texts[12][11] , 0,COLOUR_RED);
return 1;
}

oGivePlayerMoney(receiverid,cashamount,1);

new string[MAX_STRING];

if (cashamount > 0)
{
format(string,sizeof(string), lang_texts[12][12] ,oGetPlayerName(playerid),cashamount);
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);

format(string,sizeof(string), lang_texts[12][13] ,oGetPlayerName(receiverid),cashamount,GetPlayerMoney(receiverid));
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
}
else
{
format(string,sizeof(string), lang_texts[12][14] ,oGetPlayerName(playerid),cashamount);
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);

format(string,sizeof(string), lang_texts[12][15] ,oGetPlayerName(receiverid),cashamount,GetPlayerMoney(receiverid));
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
}
return 1;
}

//----------------------------------------------------------------------------------------------GUN
if(strcomp(cmd, "/givegun", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][9] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][10] , 0,COLOUR_RED);
return 1;
}
new ammamount;
ammamount = strval(strcharsplit(text, idx,strchar(" ")));

if ((ammamount < 0) || (ammamount > 46))
{
SendPlayerFormattedText(playerid, lang_texts[12][45] , 0,COLOUR_RED);
return 1;
}

GivePlayerWeapon(receiverid,ammamount,1000);

new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][46] ,oGetPlayerName(playerid),oGetWeaponName(ammamount), ammamount,1000);			//игроку
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);
format(string,sizeof(string), lang_texts[12][47] ,oGetPlayerName(receiverid),receiverid,oGetWeaponName(ammamount) ,ammamount,1000);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
return 1;
}

if(strcomp(cmd, "/paralyze", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][9] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][10] , 0,COLOUR_RED);
return 1;
}
TogglePlayerControllable(receiverid,0);

new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][54] ,oGetPlayerName(playerid));			//игроку
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);
format(string,sizeof(string), lang_texts[12][55] ,oGetPlayerName(receiverid));
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
return 1;
}

if(strcomp(cmd, "/deparalyze", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || (IsPlayerAdmin(receiverid) && !IsPlayerAdmin(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][9] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][10] , 0,COLOUR_RED);
return 1;
}
TogglePlayerControllable(receiverid,1);

new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][56] ,oGetPlayerName(playerid));			//игроку
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);
format(string,sizeof(string), lang_texts[12][57] ,oGetPlayerName(receiverid));
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
return 1;
}







return 0;
}