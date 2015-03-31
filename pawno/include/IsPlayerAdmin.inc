
// Phoenix Admin for gamemodes
// Use #incluse <IsPlayerAdmin> to include it in your gamemode

#if defined _IsPlayerAdmin_included
  #endinput
#endif
#define _IsPlayerAdmin_included
#pragma library IsPlayerAdmin

#include <a_samp>
#include <Phoenixdudb>

#pragma unused ret_memcpy


stock IsPlayerPAdmin(playerid) // Verifies if the Player is an admin
{

new name[MAX_PLAYER_NAME];  GetPlayerName(playerid, name, sizeof(name));
new file[256], tmp, tmp2; 

format(file,256,"/phoenixadm/users/%s.sav",udb_encode(name));
tmp = dini_Int(file,"level");
tmp2 = dini_Int(file,"loggedin");

if( (IsPlayerConnected(playerid)) && (tmp > 0) && (tmp2 == 1) )
	return true;
else return false;

}


stock IsPlayerAdminLevel(playerid, level) //Verifies what LEVEL, The admin/player is. (0=Player)
{

new name[MAX_PLAYER_NAME];  GetPlayerName(playerid, name, sizeof(name));
new file[256], tmp, tmp2; 

format(file,256,"/phoenixadm/users/%s.sav",udb_encode(name));
tmp = dini_Int(file,"level");
tmp2 = dini_Int(file,"loggedin");
//printf("tmp = %d, tmp2(logged) = %d, level = %d", tmp, tmp2, level );
if( (IsPlayerConnected(playerid)) && (tmp >= level) && (tmp2 != 0) )
	return true;
else return false;

}


stock IsPlayerRegistered(playerid)// Verifies if the Player is Registered in Phoenix Admin Database
{

new name[MAX_PLAYER_NAME];  GetPlayerName(playerid, name, sizeof(name));
new file[256], tmp;

format(file,256,"/phoenixadm/users/%s.sav",udb_encode(name));
tmp = dini_Int(file,"loggedin");
//printf("tmp = %d", tmp);
if( (IsPlayerConnected(playerid)) && (tmp == 1) )
	return true;
else return false;

}
