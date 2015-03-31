#if defined _xstreamer_included
	#endinput
#endif
#define _xstreamer_included
#pragma library xstreamer

#include <a_samp>

//------------------------------------------------------------------------------

native CreateStreamedObject(modelid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,virtualworld = 0,interior = 0);
native DestroyStreamedObject(objectid);
native MoveStreamedObject(objectid,Float:x,Float:y,Float:z,Float:speed);
native StopStreamedObject(objectid);
native DestroyObjectsCreatedByMe();
native StreamObjects(playerid,Float:x,Float:y,Float:z,virtualworld = 0,interior = 0);
native UpdateMovingObjects();

forward OnStreamedObjectMoved(objectid);

stock xstreamer_SetPlayerPos(playerid,Float:x,Float:y,Float:z)
{
	UpdateMovingObjects();
	StreamObjects(playerid,x,y,z,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
	SetPlayerPos(playerid,x,y,z);
}

stock xstreamer_SetPlayerInterior(playerid,interiorid)
{
	new
		Float:x,
		Float:y,
		Float:z;
	GetPlayerPos(playerid,x,y,z);
	UpdateMovingObjects();
	StreamObjects(playerid,x,y,z,GetPlayerVirtualWorld(playerid),interiorid);
	SetPlayerInterior(playerid,interiorid);
}

stock xstreamer_SetPlayerVirtualWorld(playerid,vwid)
{
	new
		Float:x,
		Float:y,
		Float:z;
	GetPlayerPos(playerid,x,y,z);
	UpdateMovingObjects();
	StreamObjects(playerid,x,y,z,vwid,GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(playerid,vwid);
}

#if !defined DONT_REPLACE_NATIVES

#define SetPlayerPos xstreamer_SetPlayerPos
#define SetPlayerInterior xstreamer_SetPlayerInterior
#define SetPlayerVirtualWorld xstreamer_SetPlayerVirtualWorld
#define CreateObject CreateStreamedObject
#define DestroyObject DestroyStreamedObject
#define MoveObject MoveStreamedObject
#define StopObject StopStreamedObject

#endif
