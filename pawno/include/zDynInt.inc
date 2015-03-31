/*
 * zDynInt 3.0
 * by Ziomal (raven.yz)
 * PAWNO.PL
 * Wszystkie prawa zastrze¿one
 * Wersja okrojona z okien kupowania
*/

#if defined zDynInt_included
	#endinput
#endif
#define zDynInt_included
#pragma library zDynInt
#define MAX_INTERIORS 500
//zmieñ 500 na wiêcej jeœli chcesz mieæ wiêcej interiorów!

enum E_zDynInt_INTERIOR
{
	bool:iActive,
	iUniverseID,
	iEnterPickup,
	iExitPickup,
	Float:iEnteredPos[3],
	Float:iExitedPos[3]
};

new zDynInt_InteriorData[MAX_INTERIORS][E_zDynInt_INTERIOR];

zDynInt_OnGameModeInit()
{
	DisableInteriorEnterExits();
	return 1;
}

zDynInt_OnGameModeExit()
{
	for(new i; i < MAX_INTERIORS; i++)
	{
		DestroyPickup(zDynInt_InteriorData[i][iEnterPickup]);
		DestroyPickup(zDynInt_InteriorData[i][iExitPickup]);
	}
	return 1;
}

zDynInt_OnPlayerPickUpPickup(playerid, pickupid)
{
	for(new i; i < MAX_INTERIORS; i++)
	{
		if(zDynInt_InteriorData[i][iActive] == true)
		{
			if(pickupid == zDynInt_InteriorData[i][iEnterPickup])
			{
				SetPlayerInterior(playerid, zDynInt_InteriorData[i][iUniverseID]);
				SetPlayerPos(playerid, zDynInt_InteriorData[i][iEnteredPos][0], zDynInt_InteriorData[i][iEnteredPos][1], zDynInt_InteriorData[i][iEnteredPos][2]);
				SetPlayerVirtualWorld(playerid, i + 1);
			}

			if(pickupid == zDynInt_InteriorData[i][iExitPickup])
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerPos(playerid, zDynInt_InteriorData[i][iExitedPos][0], zDynInt_InteriorData[i][iExitedPos][1], zDynInt_InteriorData[i][iExitedPos][2]);
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
	}
	return 1;
}

stock CreateInterior(universe, Float:iEnterPosX, Float:iEnterPosY, Float:iEnterPosZ,
Float:iEnteredPosX, Float:iEnteredPosY, Float:iEnteredPosZ,
Float:iExitPosX, Float:iExitPosY, Float:iExitPosZ,
Float:iExitedPosX, Float:iExitedPosY, Float:iExitedPosZ)
{
	for(new interior; interior < MAX_INTERIORS; interior++)
	{
		if(zDynInt_InteriorData[interior][iActive] == false)
		{
			zDynInt_InteriorData[interior][iActive] = true;
			zDynInt_InteriorData[interior][iUniverseID] = universe;
			zDynInt_InteriorData[interior][iEnterPickup] = CreatePickup(1318, 1, iEnterPosX, iEnterPosY, iEnterPosZ, 0);
			zDynInt_InteriorData[interior][iExitPickup] = CreatePickup(1318, 1, iExitPosX, iExitPosY, iExitPosZ, interior + 1);
			zDynInt_InteriorData[interior][iEnteredPos][0] = iEnteredPosX;
			zDynInt_InteriorData[interior][iEnteredPos][1] = iEnteredPosY;
			zDynInt_InteriorData[interior][iEnteredPos][2] = iEnteredPosZ;
			zDynInt_InteriorData[interior][iExitedPos][0] = iExitedPosX;
			zDynInt_InteriorData[interior][iExitedPos][1] = iExitedPosY;
			zDynInt_InteriorData[interior][iExitedPos][2] = iExitedPosZ;
			return interior;
		}
	}
	return -1;
}

stock DestroyInterior(interiorid)
{
	if(interiorid < 0 || interiorid >= MAX_INTERIORS)
	{
		return 0;
	}

	zDynInt_InteriorData[interior][iCreated] = false;
	DestroyPickup(zDynInt_InteriorData[interior][iEnterPickup]);
	DestroyPickup(zDynInt_InteriorData[interior][iExitPickup]);
	return 1;
}

