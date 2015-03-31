#include <a_samp>

// ---- STYLES
#define FIGHT_NORMAL 	0
#define FIGHT_BOXING 	1
#define FIGHT_KARATE 	2
#define FIGHT_GANGSTER 	3
//---- HIT SOUND
#define SOUND 			1130

forward KickWaitNull(playerid);

new FightStyle[MAX_PLAYERS];
new KickState[MAX_PLAYERS];
new KickWait[MAX_PLAYERS];

forward Fight_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
public Fight_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_FIRE && newkeys != KEY_SPRINT && GetPlayerWeapon(playerid) == 0 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(GetPlayerFightingStyle(playerid) == FIGHT_KARATE)
		{
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
			if(KickWait[playerid] == 0)
			{
				if(KickState[playerid] == 0)
				{
					KickState[playerid] = 1;
					ApplyAnimation(playerid,"FIGHT_C","FightC_1",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
				if(KickState[playerid] == 1)
				{
					KickState[playerid] = 2;
					ApplyAnimation(playerid,"FIGHT_C","FightC_2",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
				if(KickState[playerid] == 2)
				{
					KickState[playerid] = 0;
					ApplyAnimation(playerid,"FIGHT_C","FightC_3",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
			}
			else
			{
				ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
			}
		}
		else if(GetPlayerFightingStyle(playerid) == FIGHT_BOXING)
		{
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
			if(KickWait[playerid] == 0)
			{
				if(KickState[playerid] == 0)
				{
					KickState[playerid] = 1;
					ApplyAnimation(playerid,"FIGHT_B","FightB_1",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
				if(KickState[playerid] == 1)
				{
					KickState[playerid] = 2;
					ApplyAnimation(playerid,"FIGHT_B","FightB_2",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
				if(KickState[playerid] == 2)
				{
					KickState[playerid] = 0;
					ApplyAnimation(playerid,"FIGHT_B","FightB_3",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
			}
			else
			{
				ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
			}
		}
		else if(GetPlayerFightingStyle(playerid) == FIGHT_GANGSTER)
		{
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
			if(KickWait[playerid] == 0)
			{
				if(KickState[playerid] == 0)
				{
					KickState[playerid] = 1;
					ApplyAnimation(playerid,"FIGHT_D","FightD_1",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
				if(KickState[playerid] == 1)
				{
					KickState[playerid] = 2;
					ApplyAnimation(playerid,"FIGHT_D","FightD_2",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
				if(KickState[playerid] == 2)
				{
					KickState[playerid] = 0;
					ApplyAnimation(playerid,"FIGHT_D","FightD_3",4.1,0,1,1,0,0);
					KickWait[playerid] = 1;
					SetTimerEx("KickWaitNull", 1100, 0, "i", playerid);
					HurtClosestPlayer(playerid);
					return 1;
				}
			}
			else
			{
				ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
			}		
		}
	}
	return 1;
}

public KickWaitNull(playerid)
{
	KickWait[playerid] = 0;
}


stock SetPlayerFightingStyle(playerid, style)
{
	FightStyle[playerid] = style;
}

stock HurtClosestPlayer(playerid)
{
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(IsPlayerConnected(i) && i != playerid)
		{
			if(GetDistanceBetweenPlayers(playerid, i) <= 1)
			{
				new Float:h;
				//new Float:kickA;
				//new Float:hitA;
				GetPlayerHealth(i, h);
				SetPlayerHealth(i, h-5);
				/*
				GetPlayerFacingAngle(playerid, kickA);
				GetPlayerFacingAngle(i, hitA);
				if(hitA < 180)
				{
					hitA = hitA+180;
					SetPlayerFacingAngle(i, hitA);
				}
				else
				{
					hitA = hitA-180;
					SetPlayerFacingAngle(i, hitA);
				}*/
				if(KickState[playerid] == 1)
				{
					if(GetPlayerFightingStyle(playerid) == FIGHT_BOXING) ApplyAnimation(i,"FIGHT_B","HitB_1",4.1,0,1,1,0,0);
					if(GetPlayerFightingStyle(playerid) == FIGHT_KARATE) ApplyAnimation(i,"FIGHT_C","HitC_1",4.1,0,1,1,0,0);
					if(GetPlayerFightingStyle(playerid) == FIGHT_GANGSTER) ApplyAnimation(i,"FIGHT_D","HitD_1",4.1,0,1,1,0,0);
					PlaySound(playerid, SOUND);
					PlaySound(i, SOUND);
					return 1;
				}
				if(KickState[playerid] == 2)
				{
					if(GetPlayerFightingStyle(playerid) == FIGHT_BOXING) ApplyAnimation(i,"FIGHT_B","HitB_2",4.1,0,1,1,0,0);
					if(GetPlayerFightingStyle(playerid) == FIGHT_KARATE) ApplyAnimation(i,"FIGHT_C","HitC_2",4.1,0,1,1,0,0);
					if(GetPlayerFightingStyle(playerid) == FIGHT_GANGSTER) ApplyAnimation(i,"FIGHT_D","HitD_2",4.1,0,1,1,0,0);
					PlaySound(playerid, SOUND);
					PlaySound(i, SOUND);
					return 1;
				}
				if(KickState[playerid] == 3)
				{
					if(GetPlayerFightingStyle(playerid) == FIGHT_BOXING) ApplyAnimation(i,"FIGHT_B","HitB_3",4.1,0,1,1,0,0);
					if(GetPlayerFightingStyle(playerid) == FIGHT_KARATE) ApplyAnimation(i,"FIGHT_C","HitC_3",4.1,0,1,1,0,0);
					if(GetPlayerFightingStyle(playerid) == FIGHT_GANGSTER	) ApplyAnimation(i,"FIGHT_D","HitD_3",4.1,0,1,1,0,0);
					PlaySound(playerid, SOUND);
					PlaySound(i, SOUND);
					return 1;
				}
			}
		}
	}
	return 1;
}

stock PlaySound(playerid, soundid)
{
	PlayerPlaySound(playerid, soundid, 0, 0, 0);
}

stock GetDistanceBetweenPlayers(playerid, playerid2)
{
    new Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2;
    new Float:tmpdis;
    GetPlayerPos(playerid, x1, y1, z1);
    GetPlayerPos(playerid2, x2, y2, z2);
    tmpdis = floatsqroot(floatpower(floatabs(floatsub(x2, x1)), 2) + floatpower(floatabs(floatsub(y2, y1)), 2) + floatpower(floatabs(floatsub(z2, z1)), 2));
    return floatround(tmpdis);
}