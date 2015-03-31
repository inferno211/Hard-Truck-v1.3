/* SA:MP Surface To Air Missile (SAM) Sites */

/* 	The original version of this release (0.1) was a great work except for one thing.
	The missiles were never straight, they went to other vehicles and after a long run
	time all aircraft within the SAM site's range just exploded.
	
	Here is a list of bugfixes:
	
	• Missiles now run smoothly to your vehicle, they do not chase other vehicles (Tested with 2 SAM sites and 6 Vehicles)
	• Missiles will now chase your vehicleid, instead of the playerid.
	    This is what the system got confused about, so it chased any player(0.2) or vehicles(All)

	List of known bugs:
	
	• CreateSAM(Ex) does not create the SAM Site object. Weird
	
This system:

Version: 0.3.2
Release: 3
Bugs: 1 (Known)

DO NOT RE-DISTRIBUTE ANY CONTENT IN THIS SCRIPT WITHOUT MY CONCENT - CONTACT OF http://forum.sa-mp.com ({Awaran};)
*/

#include <a_samp>

#define MAX_SAMS 20
#define DEFAULT_MISSILE_SPEED 60
#define DEFAULT_SAM_RANGE 150
#define MISSILE_DRAG_TIME 25000 //milliseconds

new sOBJECT[MAX_SAMS];
new resttime;

enum SamS
{
	samida,
	Float:SX,
	Float:SY,
	Float:SZ,
	Float:speed,
	Float:range,
	chaseid,
	Fired,
	Ex,
	cancel,
};

new Sam[MAX_SAMS][SamS];
new Missile[MAX_SAMS];
new FireMissileKill[MAX_SAMS];
new FireMissileKill2[MAX_SAMS];
new DragKill[MAX_SAMS];
new Text3D:SamLabel[MAX_SAMS];
forward OnSamSiteUpdate(samid, playerid);

/*natives
native AddStaticSAM(samid,Float:X, Float:Y, Float:Z);
native AddStaticSAMEx(samid, Float:X, Float:Y, Float:Z, srange, sspeed);
native BUGED:CreateSAM(samid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ);
native BUGGED:CreateSAMEx(samid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, srange, sspeed);
native CreateSamLabel(samid, label[], color, Float:DrawDistance, LOS);
native SAM_start();
native SAM_cancel(samid);
*/

stock AddStaticSAM(samid,Float:X, Float:Y, Float:Z)
{
	Sam[samid][samida] = samid;
	Sam[samid][SX] = X;
	Sam[samid][SY] = Y;
	Sam[samid][SZ] = Z;
    Sam[samid][speed] = DEFAULT_MISSILE_SPEED;
    Sam[samid][range] = DEFAULT_SAM_RANGE;
    Sam[samid][chaseid] = -1;
	Sam[samid][Fired] = 0;
	Sam[samid][Ex] = 0;
	return samid;
}

stock AddStaticSAMEx(samid, Float:X, Float:Y, Float:Z, Float:srange, Float:sspeed)
{
	Sam[samid][samida] = MAX_SAMS;
	Sam[samid][SX] = X;
	Sam[samid][SY] = Y;
	Sam[samid][SZ] = Z;
    Sam[samid][speed] = sspeed;
    Sam[samid][range] = srange;
    Sam[samid][chaseid] = -1;
    Sam[samid][Fired] = 0;
    Sam[samid][Ex] = 1;
    return samid;
}

stock CreateSAM(samid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ)
{
	return -1;/*
	Sam[samid][samida] = MAX_SAMS;
	Sam[samid][SX] = X;
	Sam[samid][SY] = Y;
	Sam[samid][SZ] = Z;
    Sam[samid][speed] = DEFAULT_MISSILE_SPEED;
    Sam[samid][range] = DEFAULT_SAM_RANGE;
    Sam[samid][chaseid] = -1;
    Sam[samid][Fired] = 0;
    sOBJECT[samid] = CreateObject(3884,X,Y,X,rX,rY,rZ);
    Sam[samid][Ex] = 0;
    return samid;*/
}

stock CreateSAMEx(samid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:srange, Float:sspeed)
{
	return -1;/*
	Sam[samid][samida] = MAX_SAMS;
	Sam[samid][SX] = X;
	Sam[samid][SY] = Y;
	Sam[samid][SZ] = Z;
    Sam[samid][speed] = sspeed;
    Sam[samid][range] = srange;
    Sam[samid][chaseid] = -1;
    Sam[samid][Fired] = 0;
    sOBJECT[samid] = CreateObject(3884,X,Y,X,rX,rY,rZ);
    Sam[samid][Ex] = 1;
    return samid;*/
}

stock SAM_cancel(samid)
{
	Sam[samid][cancel] = 1;
}

stock SAM_start()
{
	resttime = SetTimer("SamLive",500,true);
	SetTimer("Restart",1800000,false);
	print("\n--------------------------------------");
	print(" Surface To Air Missiles System Loaded");
	print("                 0.3.2");
	print("--------------------------------------\n");
	return 1;
}

stock CreateSamLabel(samid, label[], color, Float:DrawDistance, LOS)
{
	new string[128];
	format(string,sizeof(string),"%s(%d)",label,samid);
	SamLabel[samid] = Create3DTextLabel(string,color,Sam[samid][SX],Sam[samid][SY],Sam[samid][SZ] + 2.00,DrawDistance,0,LOS);
	return 1;
}

forward SamLive();
public SamLive()
{
	for(new s = 0; s <MAX_SAMS; s++)
	{
	    SamConfig(s);
	}
}

forward SamConfig(samid);
public SamConfig(samid)
{
	for(new i = 0; i <MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(Sam[samid][Fired] == 0)
	        {
	            if(IsPlayerInAnyVehicle(i))
	            {
	                new veh = GetPlayerVehicleID(i);
	                if(IsAirVehicle(veh))
					{
					    if(Sam[samid][Ex] == 1)
					    {
					        if(IsPlayerInRangeOfPoint(i,Sam[samid][range],Sam[samid][SX],Sam[samid][SY],Sam[samid][SZ]))
					        {
					            OnSamSiteUpdate(samid, i);
					            if(Sam[samid][cancel] == 1)
								{
									Sam[samid][cancel] = 0;
									return 1;
								}
					            Missile[samid] = CreateObject(354,Sam[samid][SX],Sam[samid][SY],Sam[samid][SZ],0,0,0);
					            Sam[samid][Fired] = 1;
					            Sam[samid][chaseid] = veh;
					            FireSam(samid,i,veh);
							}
						}
						else
						{
						    if(IsPlayerInRangeOfPoint(i,DEFAULT_SAM_RANGE,Sam[samid][SX],Sam[samid][SY],Sam[samid][SZ]))
        					{
								OnSamSiteUpdate(samid, i);
								if(Sam[samid][cancel] == 1)
								{
									Sam[samid][cancel] = 0;
									return 1;
								}
	           		 			Missile[samid] = CreateObject(354,Sam[samid][SX],Sam[samid][SY],Sam[samid][SZ],0,0,0);
	          	  				Sam[samid][Fired] = 1;
	          	  				Sam[samid][chaseid] = veh;
	            				FireSam(samid,i,veh);
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

forward FireSam(samid, playerid, vehicleid);
public FireSam(samid, playerid, vehicleid)
{
	if(Sam[samid][chaseid] != vehicleid) return 1;
	FireMissileKill[samid] = SetTimerEx("Fire",500,true,"iii",playerid, samid, vehicleid);
	FireMissileKill2[samid] = SetTimerEx("Destroy",300,true,"iii",playerid,samid,vehicleid);
	DragKill[samid] = SetTimerEx("Drag",MISSILE_DRAG_TIME,false,"ii",samid, playerid);
	return 1;
}

forward Fire(playerid, samid, vehicleid);
public Fire(playerid, samid, vehicleid)
{
	if(vehicleid == Sam[samid][chaseid])
	{
	    new Float:X,
	        Float:Y,
	        Float:Z;
		GetVehiclePos(vehicleid,X,Y,Z);
		if(Sam[samid][Ex] == 1)
		{
		    StopObject(Missile[samid]);
		    MoveObject(Missile[samid],X,Y,Z,Sam[samid][speed]);
		}
		else
		{
		    StopObject(Missile[samid]);
		    MoveObject(Missile[samid],X,Y,Z,DEFAULT_MISSILE_SPEED);
		}
	}
}

forward Destroy(playerid, samid, vehicleid);
public Destroy(playerid, samid, vehicleid)
{
	new Float:OX,
		Float:OY,
		Float:OZ;
	GetObjectPos(Missile[samid],OX,OY,OZ);
	if(IsPlayerInRangeOfPoint(playerid,3,OX,OY,OZ))
	{
	    CreateExplosion(OX,OY,OZ,2,10);
	    CreateExplosion(OX,OY,OZ,2,10);
	    CreateExplosion(OX,OY,OZ,2,10);
		KillTimer(FireMissileKill[samid]);
		KillTimer(FireMissileKill2[samid]);
		SetVehicleHealth(vehicleid,0);
		KillTimer(DragKill[samid]);
		SetTimerEx("FireSet",5000,false,"i",samid);
		DestroyObject(Missile[samid]);
	}
	return 1;
}

forward FireSet(samid);
public FireSet(samid)
{
	Sam[samid][Fired] = 0;
}

forward Drag(samid, playerid);
public Drag(samid, playerid)
{
	new Float:OX,
	    Float:OY,
	    Float:OZ;
	GetObjectPos(Missile[samid],OX,OY,OZ);
	CreateExplosion(OX,OY,OZ,2,2.00);
    CreateExplosion(OX,OY,OZ,2,2.00);
    CreateExplosion(OX,OY,OZ,2,2.00);
    Sam[samid][Fired] = 0;
    DestroyObject(Missile[samid]);
}

forward Restart();
public Restart()
{
	KillTimer(resttime);
	SAM_start();
}

stock IsAirVehicle(carid)
{
    new AirVeh[] = { 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469 };
    for(new i = 0; i < sizeof(AirVeh); i++)
    {
        if(GetVehicleModel(carid) == AirVeh[i]) return 1;
    }
    return 0;
}


