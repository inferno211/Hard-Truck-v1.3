#include <a_samp>
#include <dini>

forward TroxAdmins_OnPlayerConnect(playerid);
public TroxAdmins_OnPlayerConnect(playerid)
{
	SetPVarInt(playerid, "Administrator", 0);
	if(dini_Exists(SprawdzPrawaAdministratora(playerid)))
	{
		SendClientMessage(playerid, 0xFFFFFF00, "SERVER: Zostales zalogowany na konto Administratora!");
		SetPVarInt(playerid, "Administrator", 1);
	}
	return 1;
}

forward TroxAdmins_OnPlayerDisconnect(playerid, reason);
public TroxAdmins_OnPlayerDisconnect(playerid, reason)
{
	SetPVarInt(playerid, "Administrator", 0);
	return 1;
}

stock SprawdzPrawaAdministratora(playerid)
{
	new string[40];
	format(string, sizeof(string), "Admins/%s.txt", PlayerName(playerid));
	return string;
}

stock IsPlayerSpecialAdmin(playerid)
{
	if(GetPVarInt(playerid, "Administrator")==1)
	{
		return true;
	}
	return false;
}

stock PlayerName(playerid)
{
	new pName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pName, sizeof(pName));
	return pName;
}

#define IsPlayerAdmin IsPlayerSpecialAdmin