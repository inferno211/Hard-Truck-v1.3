/*  Alternative RolePlay 1.0A+ Include ddd
 *
 *  (c) Copyright 2009-20010, ARP
 *
 */

#if defined _arp_included
	#endinput
#endif
#define _arp_included
#pragma library arp

#pragma tabsize 4

#include <a_samp>
#include <core>
#include <float>
#include <string>
#include <file>
#include <time>
#include <dini>

native GetPlayerLeader(playerid);

IsPlayerInPoliceCar(playerid)
{
	new pojazdid = GetPlayerVehicleID(playerid);
	If(pojazdid = 601 || pojazdid = 597 || pojazdid = 599 ||pojazdid = 596 || pojazdid = 597)
	{

		return 1;
	}
	return 0;
}

IsPlayerInAmbulance(playerid)
{
	new pojazdid = GetPlayerVehicleID(playerid);
	If(pojazdid = 416)
	{

		return 1;
	}
	return 0;
}
