//
// Created: 18.12.2007
// Aurthor: Dmitry Frolov (FP)
//

#if defined _mod_commands_included
#endinput
#endif

#define _mod_commands_included
#pragma library mod_commands
#include "base"
#include "player"

forward ModCommandHandler(playerid,text[]);
forward ModSpecialCommandHandler(playerid,text[]);

public ModCommandHandler(playerid,text[]) // process player commands
{
if (!IsPlayerConnected(playerid)) return 0;
if ( !IsPlayerMod(playerid) && !IsPlayerAdmin(playerid) && !IsPlayerAdm(playerid) )
{
return 0;
}
new cmd[20];
new idx;

//set(cmd,strcharsplit(text, idx,strchar(" ")));
//if(strcomp(cmd, "/mod", true) == 0) return 0;
set(cmd,strcharsplit(text, idx,strchar(" ")));

if(strcomp(cmd, "/cmdlist", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

  SendClientMessage(playerid, COLOUR_LIGHTGREEN, "M: '/carresp', '/remcar <ID>', '/kick <ID>'");
  SendClientMessage(playerid, COLOUR_LIGHTGREEN, "M: '/cmdlist', '/about', '/mute <ID>', '/unmute <ID>', '/jail <ID>', '/unjail <ID>', '/plist'");
}

if(strcomp(cmd, "/about", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);
  SendClientMessage(playerid, COLOUR_LIGHTGREEN, lang_texts[15][41]);
  SendClientMessage(playerid, COLOUR_LIGHTGREEN, lang_texts[15][42]);
  SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[15][43]);
  SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[15][44]);
}

if(strcomp(cmd, "/plist", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

SendClientMessage(playerid, COLOUR_YELLOW, lang_texts[15][46]);
new ccount;

for (new id = 0; id < MAX_PLAYERS; id++)
{
if ( IsPlayerConnected(id) && Player[id][Jailed] ==1 )
	{
	new string[MAX_STRING];
	if ( Player[id][Jailtime] >0 ) {format(string,sizeof(string), lang_texts[18][3] ,oGetPlayerName(id), id, Player[id][Jailtime]);}
	else  {format(string,sizeof(string), lang_texts[18][4] ,oGetPlayerName(id), id);}
	SendClientMessage(playerid, COLOUR_LIGHTRED, string);
	ccount++;
	}
	if ( IsPlayerConnected(id) && Player[id][Muted] ==1 )
	{
	new string[MAX_STRING];
	if ( Player[id][Mutetime] >0 ) {format(string,sizeof(string), lang_texts[18][5] ,oGetPlayerName(id), id, Player[id][Mutetime]);}
	else  {format(string,sizeof(string), lang_texts[18][6] ,oGetPlayerName(id), id);}
	SendClientMessage(playerid, COLOUR_LIGHTGREEN, string);
	ccount++;
	}
}
if (ccount==0) { SendClientMessage(playerid, COLOUR_XP_GOOD, lang_texts[18][7] );}
return 1;
}

if(strcomp(cmd, "/remcar", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid = strval(strcharsplit(text, idx,strchar(" ")));
if ((receiverid < 0) || (receiverid >= MAX_PLAYERS) || IsPlayerAdmin(receiverid) )
{
SendPlayerFormattedText(playerid, lang_texts[12][2] , 0,COLOUR_RED);
return 1;
}
if (IsPlayerConnected(receiverid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][3] , 0,COLOUR_RED);
return 1;
}
if(IsPlayerInAnyVehicle(receiverid))
{
RemovePlayerFromVehicle(receiverid);
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][64] ,oGetPlayerName(receiverid),receiverid);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
format(string,sizeof(string), lang_texts[12][65] ,oGetPlayerName(playerid));
SendPlayerFormattedText(receiverid,string, 0,COLOUR_XP_GOOD);
return 1;
} else {
	new string[MAX_STRING];
	format(string,sizeof(string), lang_texts[12][73] ,oGetPlayerName(receiverid),receiverid);
	SendPlayerFormattedText(playerid,string, 0,COLOUR_RED);
	return 1;
	}
}

if(strcomp(cmd, "/kick", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new receiverid;
receiverid=INACTIVE_PLAYER_ID;

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
new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][60] ,oGetPlayerName(receiverid),receiverid);
SendPlayerFormattedText(playerid,string, 0,COLOUR_XP_GOOD);
format(string,sizeof(string), lang_texts[12][61] ,oGetPlayerName(receiverid),receiverid);
SendClientMessageToAll(COLOUR_WHITE, string);

Kick(receiverid);

return 1;
}


if ((strcomp(cmd, "/carresp", true) == 1) && IsPlayerInAnyVehicle(playerid) )
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

//SetVehicleHealth(GetPlayerVehicleID(playerid), 1.0);
SetVehicleToRespawn(GetPlayerVehicleID(playerid));
new string[MAX_STRING];
format(string,sizeof(string), "*** Траспорт (ИД %d) возвращен на свой респавн.", GetPlayerVehicleID(playerid) );
SendPlayerFormattedText(playerid,string, 0,COLOUR_WHITE);
}


if (strcomp(cmd, "/mute", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

//new tmp[256];
//tmp = strcharsplit(text, idx,strchar(" "));
//if(!strlen(tmp))
//{
//SendClientMessage(playerid, COLOUR_MISC,  lang_texts[18][1] );
//return 1;
//}

new muteid;
muteid = strval(strcharsplit(text, idx,strchar(" ")));

if ((muteid < 0) || (muteid >= MAX_PLAYERS))
{
SendPlayerFormattedText(playerid, lang_texts[12][22] , 0,COLOUR_RED);
return 1;
}

if (IsPlayerConnected(muteid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][23] , 0,COLOUR_RED);
return 1;
}

Player[muteid][Muted] = 1;

new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][24] ,oGetPlayerName(playerid));
SendPlayerFormattedText(muteid,string, 0,COLOUR_RED);

//GIVE MUTE INFO
SetPlayerWantedLevel(muteid, 3);
format(string,sizeof(string), lang_texts[12][50], oGetPlayerName(muteid));
//GameTextForAll(string,5000,4);
SendClientMessageToAll(COLOUR_WHITE, string);
printf("SERVER : %s Has Been Muted by %s",oGetPlayerName(muteid),oGetPlayerName(playerid));

return 1;
}

if (strcomp(cmd, "/unmute", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

//new tmp[256];
//tmp = strcharsplit(text, idx,strchar(" "));
//if(!strlen(tmp))
//{
//SendClientMessage(playerid, COLOUR_MISC,  lang_texts[18][2] );
//return 1;
//}


new unmuteid;
unmuteid = strval(strcharsplit(text, idx,strchar(" ")));

if ((unmuteid < 0) || (unmuteid >= MAX_PLAYERS))
{
SendPlayerFormattedText(playerid, lang_texts[12][25] , 0,COLOUR_RED);
return 1;
}

if (IsPlayerConnected(unmuteid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][26] , 0,COLOUR_RED);
return 1;
}

Player[unmuteid][Muted] = 0;

new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][27] ,oGetPlayerName(playerid));
SendPlayerFormattedText(unmuteid,string, 0,COLOUR_GREEN);

//GIVE UNMUTE INFO
SetPlayerWantedLevel(unmuteid, 0);
format(string,sizeof(string), lang_texts[12][51], oGetPlayerName(unmuteid));
//GameTextForAll(string,5000,4);
SendClientMessageToAll(COLOUR_WHITE, string);
printf("SERVER : %s Has Been UNMuted by %s",oGetPlayerName(unmuteid),oGetPlayerName(playerid));

return 1;
}




//Внимание! - Посаженный в тюрьму или "заткнутый" - не сможет обойти это - ни выходом, ни самоубийством!

if(strcomp(cmd, "/jail", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new jailid;
jailid = strval(strcharsplit(text, idx,strchar(" ")));

if ((jailid < 0) || (jailid >= MAX_PLAYERS) || (IsPlayerAdmin(jailid) && !IsPlayerAdmin(playerid)) || (IsPlayerAdm(jailid) && IsPlayerMod(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][16] , 0,COLOUR_RED);
return 1;
}

if (IsPlayerConnected(jailid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][17] , 0,COLOUR_RED);
return 1;
}

Player[jailid][Jailed] = 1;

new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][18] ,oGetPlayerName(playerid));
SendPlayerFormattedText(jailid,string, 0,COLOUR_RED);

//GIVE JAIL INFO
SetPlayerWantedLevel(jailid, 6);
SetPlayerArmour(jailid, 0);
SetPlayerHealth(jailid, 10);
//ResetPlayerMoney(jailid);
//ResetPlayerWeapons(jailid);

ADMDropAmmo(jailid);

PlayerPlaySound(jailid,1082,198.3797,160.8905,1003.0300);

format(string,sizeof(string), "~r~%s ~w~has been Jailed", oGetPlayerName(jailid));
//format(string,sizeof(string), "~r~%s ~w~ЪШЧ APECTOBAH Ц зOCAЩEH B TЖPШЗи", oGetPlayerName(jailid));

GameTextForAll(string,5000,4);
printf("SERVER : %s Has Been Jailed by %s",oGetPlayerName(jailid),oGetPlayerName(playerid));

format(string,sizeof(string), lang_texts[12][52], oGetPlayerName(jailid));
SendClientMessageToAll(COLOUR_WHITE, string);



JailPlayer(jailid);
return 1;
}


if(strcomp(cmd, "/unjail", true) == 1)
{
SendMessageToAdmins(playerid,COLOUR_LIGHTGREEN, text);

new unjailid;
unjailid = strval(strcharsplit(text, idx,strchar(" ")));

if ((unjailid < 0) || (unjailid >= MAX_PLAYERS) || (IsPlayerAdmin(unjailid) && !IsPlayerAdmin(playerid)) || (IsPlayerAdm(unjailid) && IsPlayerMod(playerid)) )
{
SendPlayerFormattedText(playerid, lang_texts[12][19] , 0,COLOUR_RED);
return 1;
}

if (IsPlayerConnected(unjailid) == 0)
{
SendPlayerFormattedText(playerid, lang_texts[12][20] , 0,COLOUR_RED);
return 1;
}

Player[unjailid][Jailed] = 0;

new string[MAX_STRING];
format(string,sizeof(string), lang_texts[12][21] ,oGetPlayerName(playerid));
SendPlayerFormattedText(unjailid,string, 0,COLOUR_GREEN);

//GIVE UNJAIL INFO
SetPlayerWantedLevel(unjailid, 0);

format(string,sizeof(string), "~r~%s ~w~Now is Free", oGetPlayerName(unjailid));
GameTextForAll(string,5000,4);
printf("SERVER : %s Has Been UNJailed by %s",oGetPlayerName(unjailid),oGetPlayerName(playerid));

format(string,sizeof(string), lang_texts[12][53], oGetPlayerName(unjailid));
SendClientMessageToAll(COLOUR_WHITE, string);

UnJailPlayer(unjailid);
return 1;
}




return 0;
}



public ModSpecialCommandHandler(playerid,text[])
{
if (!IsPlayerConnected(playerid)) return 0;

if(text[0] == '#')
{
new string[MAX_STRING];
strmid(string,text,1,strlen(text));
new count = 0;
for (new adminid=0; adminid<MAX_PLAYERS;adminid++)
{
if ( IsPlayerMod(adminid) )
	{
	new message[MAX_STRING];
	format(message,sizeof(message), lang_texts[12][79] ,oGetPlayerName(playerid),string);
	SendPlayerFormattedText(adminid,message, 0,COLOUR_RED);
	count++;
	}
}
if (count == 0)
	{
	SendPlayerFormattedText(playerid, lang_texts[12][80] , 0,COLOUR_RED);
	return 0;
	} else {
	new message[MAX_STRING];
	format(message,sizeof(message), lang_texts[12][81] ,string);
	SendPlayerFormattedText(playerid,message, 0,COLOUR_GREEN);
	return 0;
	}
}
return 0;
}