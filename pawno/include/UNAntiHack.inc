// Union Anti Money Hack, Anti Illegal Weapon, Anti Jet-Pack (GodFather Compile) by chenza
// Support GM GodFather Only!!!

new ScriptMoney[MAX_PLAYERS];
new moneyhacktimer;

forward CheckMoneyHack();
forward Union_OnGameModeInit();
forward Union_OnPlayerConnect(playerid);
forward Union_OnPlayerDisconnect(playerid,reason);
forward Union_GameModeExitFunc();
forward Union_GiveMoney(playerid, amounttogive);
forward Union_ResetMoney(playerid);
forward Union_GetMoney(playerid);

public Union_OnGameModeInit()
{
	moneyhacktimer = SetTimer("CheckMoneyHack",5000,1);
}

public Union_GameModeExitFunc()
{
	KillTimer(moneyhacktimer);
}

public Union_GiveMoney(playerid, amounttogive)
{
	GivePlayerMoney(playerid, amounttogive);
	ScriptMoney[playerid] = (ScriptMoney[playerid] + amounttogive);
	return 1;
}

public Union_OnPlayerDisconnect(playerid,reason)
{
	ScriptMoney[playerid] = 0;
}

public Union_OnPlayerConnect(playerid)
{
	ScriptMoney[playerid] = 0;
}

public Union_ResetMoney(playerid)
{
	ResetPlayerMoney(playerid);
	ScriptMoney[playerid] = 0;
	return 1;
}

public Union_GetMoney(playerid)
{
	return ScriptMoney[playerid];
}

public CheckMoneyHack() //Anti Money Hack By ChenZa!!
{
	for(new i = 0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			new string[256];
			new giveplayer[MAX_PLAYER_NAME];
			new money = GetPlayerMoney(i);
			new pcash = Union_GetMoney(i);
			if(pcash < money)
			{
				GetPlayerName(i, giveplayer, sizeof(giveplayer));
				new year, month,day;
				getdate(year, month, day);
				new moneynumber = money-pcash;
				format(string, sizeof(string), "AdmWarning : %s use Money Cheat amount: %d", giveplayer, moneynumber);
				SendClientMessageToAll(0xFFFF00AA, string);
				Union_ResetMoney(i);
				Union_GiveMoney(i, pcash);
				Kick(i);
			}
			else
			{
				ScriptMoney[i] = money;
			}
		}
	}
  	return 1;
}

#define GivePlayerMoney Union_GiveMoney
#define ResetPlayerMoney Union_ResetMoney
#define GetPlayerMoney Union_GetMoney
