// This Include is made and copyright by www.SA-Script-Crew.de.tf, MaCcA.
// Only use it with credits, please!

/*
native ClientLanguageText(playerid, color, const message0[], const message1[]);
native ClientLanguageTextToAll(color, const message0[], const message1[]);
native GameLanguageText(playerid, const message0[], const message1[], time, style);
native GameLanguageTextToAll(const message0[], const message1[], time, style);
native SetPlayerLanguage(playerid, language);
*/

new PlayerLanguage[MAX_PLAYERS] = 0;

stock SetPlayerLanguage(playerid, language)
{
    if(language == 0)
 	{
		PlayerLanguage[playerid] = 0;
		return 1;
	}
	if(language == 1)
	{
		PlayerLanguage[playerid] = 1;
		return 1;
	}
	return 1;
}

stock ClientLanguageText(playerid, color, const message0[], const message1[])
{
	if(PlayerLanguage[playerid] == 0)
 	{
		SendClientMessage(playerid, color, message0);
		return 1;
	}
	if(PlayerLanguage[playerid] == 1)
	{
		SendClientMessage(playerid, color, message1);
		return 1;
	}
	return 1;
}

stock ClientLanguageTextToAll(color, const message0[], const message1[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(PlayerLanguage[i] == 0)
	    {
	        SendClientMessage(i, color, message0);
	        return 1;
	    }
	    if(PlayerLanguage[i] == 1)
	    {
	        SendClientMessage(i, color, message1);
	        return 1;
	    }
	}
	return 1;
}

stock GameLanguageText(playerid, const message0[], const message1[], time, style)
{
	if(PlayerLanguage[playerid] == 0)
	{
		GameTextForPlayer(playerid, message0, time, style);
		return 1;
	}
	if(PlayerLanguage[playerid] == 1)
	{
		GameTextForPlayer(playerid, message1, time, style);
		return 1;
	}
	return 1;
}

stock GameLanguageTextToAll(const message0[], const message1[], time, style)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(PlayerLanguage[i] == 0)
	    {
	        GameTextForPlayer(i, message0, time, style);
	        return 1;
	    }
	    if(PlayerLanguage[i] == 1)
	    {
	        GameTextForPlayer(i, message1, time, style);
	        return 1;
	    }
	}
	return 1;
}