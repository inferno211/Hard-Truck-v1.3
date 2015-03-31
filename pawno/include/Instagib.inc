/*******************************************************************************
*   				[INC] Instagib include by Matthias			               *
********************************************************************************
*                                                                              *
*	This simple include makes it incredibly easy to enable or disable 		   *
*   instagib for any player at any time. You are not allowed to rerelease	   *
*   this without my permission. I hope you enjoy it!				 		   *
*                                                                              *
*   Author: Matthias          								      	   		   *
*   Email: matthiasvaneeghem@hotmail.com					      	   		   *
*   														      	   		   *
*******************************************************************************/

forward bool:IsValidWeapon(weaponid);
forward OnPlayerInstagibKill(playerid, killerid, weaponid);

new IsInstagibWeapon[47];
new PlayerInstagibWeapon[MAX_PLAYERS][47];

stock Inst__OnPlayerConnect(playerid)
{
	for(new i = 0; i < 48; i++)
	{
	    PlayerInstagibWeapon[playerid][i] = 0;
	}
	return 1;
}

stock SetInstagibForAll(weaponid, bool:Enabled)
{
	if(!IsValidWeapon(weaponid)) return 0;

	if(Enabled)
	{
		if(IsInstagibWeapon[weaponid] == 1) return -1;
		IsInstagibWeapon[weaponid] = 1;
	}
	else
	{
		if(IsInstagibWeapon[weaponid] == 0) return -1;
 		IsInstagibWeapon[weaponid] = 0;
	}
	return 1;
}

stock SetInstagibForPlayer(playerid, weaponid, bool:Enabled)
{
	if(!IsValidWeapon(weaponid)) return 0;

	if(Enabled)
	{
		if(IsInstagibWeapon[weaponid] == 1) return -1;
		if(PlayerInstagibWeapon[playerid][weaponid] == 1) return -1;

 		PlayerInstagibWeapon[playerid][weaponid] = 1;
	}
	else
	{
		if(IsInstagibWeapon[weaponid] == 0) return -1;
		if(PlayerInstagibWeapon[playerid][weaponid] == 0) return -1;
 		PlayerInstagibWeapon[playerid][weaponid] = 0;
	}
	return 1;
}

stock GetWeaponInstagib(weaponid)
{
	if(!IsValidWeapon(weaponid)) return 0;
	if(IsInstagibWeapon[weaponid] == 1)
	{
	    return true;
	}
	else return false;
}

stock GetPlayerInstagib(playerid, weaponid)
{
	if(!IsValidWeapon(weaponid)) return 0;
	if(PlayerInstagibWeapon[playerid][weaponid] == 1)
	{
	    return true;
	}
	else return false;
}

stock bool:IsValidWeapon(weaponid)
{
	if(weaponid == 19 || weaponid == 20 || weaponid == 21 || weaponid < 0 || weaponid > 46) return false;
	return true;
}

stock Inst__OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(((oldkeys & KEY_FIRE) && !(newkeys & KEY_FIRE)) || ((newkeys & KEY_FIRE) && !(oldkeys & KEY_FIRE)) ||  (newkeys & KEY_FIRE))
	{
		for(new i = 0; i < GetMaxPlayers(); i++)
		{
		    if(IsPlayerConnected(i) && playerid != i && !IsPlayerNPC(i))
		    {
				if(IsPlayerAiming(playerid, i) && GetPlayerState(i) == PLAYER_STATE_ONFOOT)
				{
					new Weapon = GetPlayerWeapon(playerid);
					if(IsInstagibWeapon[Weapon] == 1 || PlayerInstagibWeapon[playerid][Weapon] == 1)
					{
					    SetPlayerHealth(i, 0);
					    CallRemoteFunction("OnPlayerInstagibKill", "iii", i, playerid, Weapon);
					}
    			}
			}
		}
	}
	return 1;
}

stock IsPlayerAiming(playerid, aimid)
{
	// Not my function, can't remember who made it though.
	new Float:X1, Float:Y1, Float:Z1, Float:X2, Float:Y2, Float:Z2;
	GetPlayerPos(playerid, X1, Y1, Z1);
	GetPlayerPos(aimid, X2, Y2, Z2);
	new Float:Distance = floatsqroot(floatpower(floatabs(X1-X2), 2) + floatpower(floatabs(Y1-Y2), 2));
	if(Distance < 100)
	{
		new Float:A;
	 	GetPlayerFacingAngle(playerid, A);
	 	X1 += (Distance * floatsin(-A, degrees));
	 	Y1 += (Distance * floatcos(-A, degrees));
	 	Distance = floatsqroot(floatpower(floatabs(X1-X2), 2) + floatpower(floatabs(Y1-Y2), 2));
		if(Distance < 0.5)
		{
		    return true;
		}
	}
	return false;
}