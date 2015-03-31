#include <a_samp>
#include <md5>

#define FILE "RCONx.crt"

new Allow[MAX_PLAYERS];

stock rcon_OnPlayerConnect(playerid)
{
	Allow[playerid] = 0;
	new File:certif = fopen(FILE,io_read);
	new string[128];
	while(fread(certif, string))
	{
		if(strfind(string,MD5_Hash(ReturnName(playerid))))
		{
			Allow[playerid] = 0;
		}
		else Allow[playerid] = 1;
	}
}

stock rcon_OnPlayerUpdate(playerid)
{
	if(IsPlayerAdmin(playerid))
	{
	    if(Allow[playerid] == 0)
	    {
	        printf("[RCONx] Ban: %s[%d] - RCON Intruder",ReturnName(playerid),playerid);
	        SendClientMessage(playerid,0xA9C4E4AA,"RCONx - Intrusion detected - Your IP has been banned");
	        BanEx(playerid,"RCON Intruder - RCONx System");
		}
	}
}

stock HashString(string[])
{
	printf("Name: %s || Hash: %s",string,MD5_Hash(string));
}

stock ReturnName(playerid)
{
	new n[MAX_PLAYER_NAME];
	GetPlayerName(playerid,n,sizeof(n));
	return n;
}
