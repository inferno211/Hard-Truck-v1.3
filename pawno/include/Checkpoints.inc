/*
	INCLUDE STWORZONY PRZEZ FIRE DRAGON'A !
	UKRADNIESZ MOJ¥ PRACÊ TO UMRZE CI MATKA !
*/

/*------------------------------------------------------------------------------
native CreateCheckpoint(Float: x, Float: y, Float: z, Float: Size, Float: VDistance);
native DestroyCheckpoint(checkid);
native bool: IsPlayerInCheckPoint(playerid, checkid);
*/

#define MAX_CHECKS      10

forward OnPlayerGetCheckPoint(playerid, checkid);
enum _Checkpoints
{
	Float: cX,
	Float: cY,
	Float: cZ,
	Float: cSize,
	Float: Viev_Distance,
	bool: IsCreated,
	bool: IsShown
};

new
	cID,
	Checkpoints[MAX_CHECKS][_Checkpoints];


stock CreateCheckpoint(Float: x, Float: y, Float: z, Float: Size, Float: VDistance)
{
    cID++;
    Checkpoints[cID][cX] = x;
    Checkpoints[cID][cY] = y;
    Checkpoints[cID][cZ] = z;
    Checkpoints[cID][cSize] = Size;
    Checkpoints[cID][Viev_Distance] = VDistance;
    Checkpoints[cID][IsCreated] = true;
    return cID;
}

stock DestroyCheckpoint(checkid)
{
    Checkpoints[checkid][cX] = 0;
    Checkpoints[checkid][cY] = 0;
    Checkpoints[checkid][cZ] = 0;
    Checkpoints[checkid][cSize] = 0;
    Checkpoints[checkid][Viev_Distance] = 0;
    Checkpoints[checkid][IsCreated] = false;
    return 1;
}

stock bool: IsPlayerInCheckPoint(playerid, checkid)
{
	if(PTP(Checkpoints[checkid][cSize], playerid, Checkpoints[checkid][cX], Checkpoints[checkid][cY], Checkpoints[checkid][cZ])) return true;
	return false;
}

stock SteamCheckpoints(playerid)
{
	new Float: pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	for(new i = 0; i < MAX_CHECKS; i++)
	{
	    if(Checkpoints[i][IsCreated] == false) continue;
	    if(Checkpoints[i][IsShown] == true) goto p_next;
		if(GetDistanceEx(pos[0], pos[1], pos[2], Checkpoints[i][cX], Checkpoints[i][cY], Checkpoints[i][cZ]) <= Checkpoints[i][Viev_Distance])
		{
		    SetPlayerCheckpoint(playerid, Checkpoints[i][cX], Checkpoints[i][cY], Checkpoints[i][cZ], Checkpoints[i][cSize]);
		    Checkpoints[i][IsShown] = true;
		}
		p_next:
		if(GetDistanceEx(pos[0], pos[1], pos[2], Checkpoints[i][cX], Checkpoints[i][cY], Checkpoints[i][cZ]) > Checkpoints[i][Viev_Distance])
		{
		    if(Checkpoints[i][IsShown] == true) DisablePlayerCheckpoint(playerid);
		    Checkpoints[i][IsShown] = false;
		}
  	}
  	return 1;
}

stock OnPlayerEnterCheckpointEx(playerid)
{
	for(new i = 0; i < cID; i++)
	{
	    if(Checkpoints[i][IsShown] == true)
	    {
			CallRemoteFunction("OnPlayerGetCheckPoint", "ii", playerid, i);
	    }
	}
	return 1;
}

stock GetDistanceEx(Float: oldposx, Float: oldposy, Float: oldposz, Float: x, Float: y, Float: z)
{
	new Float:dis;
	dis = floatsqroot(floatpower(floatabs(floatsub(x,oldposx)),2)+floatpower(floatabs(floatsub(y,oldposy)),2)+floatpower(floatabs(floatsub(z,oldposz)),2));
	return floatround(dis);
}

stock PTP(Float:radi,playerid,Float:x,Float:y,Float:z)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	tempposx = (oldposx -x);
	tempposy = (oldposy -y);
	tempposz = (oldposz -z);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) return 1;
	return 0;
}
