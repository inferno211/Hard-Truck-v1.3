/***********************************
^ [INC] oStreamer 2.3 by LeNy 2010 ^
^     Wszelkie prawa zastrze¿one   ^
***********************************/

//------------------------------------------------------------------------------
#include <a_samp>

#if defined _oStreamer_included
	#endinput
#endif
#define _oStreamer_included
#pragma library oStreamer

//------------------------------------------------------------------------------
#define DestroyObject o_DestroyObject
#define CreateObject o_CreateObject

//------------------------------------------------------------------------------
stock o_OnPlayerConnect(playerid)
{
return CallRemoteFunction("o_ConnectPlayer","i",playerid);
}

//------------------------------------------------------------------------------
stock o_OnPlayerDisconnect(playerid)
{
return CallRemoteFunction("o_DisconnectPlayer","i",playerid);
}

//------------------------------------------------------------------------------
stock o_CreateObject(oModel, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ)
{
return CallRemoteFunction("o_CreateObj","iffffff",oModel, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ);
}

//------------------------------------------------------------------------------
stock o_DestroyObject(oModel)
{
return CallRemoteFunction("o_DestroyObj","i",oModel);
}

//------------------------------------------------------------------------------
stock o_OnGameModeInt()
{
return CallRemoteFunction("o_oStreamerLoad","s","oStreamer 2.3");
}
