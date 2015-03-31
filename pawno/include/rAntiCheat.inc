#include <a_samp>
#include <foreach>
#include <dini>

#pragma unused ret_memcpy



          //////////////////////////////////////////////
          //                                          //
          //   RenisiL - AntiMoney Cheat              //
          //                                          //
          // Scriptas: RenisiL(Deividas Kavaliauskas) //
          //                                          //
          //   Sripto Versija: v0.1.1                 //
          //                                          //
          //   I?leidimo Data: 2010/06/21             //
          //                                          //
          //////////////////////////////////////////////

//------------------------------------------------------------------------------
// Spalvos
//------------------------------------------------------------------------------

#define COLOR_ZALIA	         0x98B13430

//------------------------------------------------------------------------------
// Golgal kintamieji
//------------------------------------------------------------------------------

new
    bool:Spawned[ MAX_PLAYERS ],
    pPinigai    [ MAX_PLAYERS ],
	AntiMoneyHackGuard;

//------------------------------------------------------------------------------
// forward
//------------------------------------------------------------------------------

forward RInit_OnPlayerConnect   ( playerid );
forward RInit_OnPlayerDeath     ( playerid, killerid, reason );
forward RInit_OnPlayerDisconnect( playerid, reason );
forward RInit_OnPlayerSpawn     ( playerid );
forward RInit_OnPlayerUpdate    ( playerid );
//------------------------------------------------------------------------------
// CallBack: OnPlayerUpdate
//------------------------------------------------------------------------------

public RInit_OnPlayerUpdate( playerid )
{
    R_AntiCheat( );
	return 1;
}
//------------------------------------------------------------------------------
// Stock: Init
//------------------------------------------------------------------------------
stock Init( )
{
	if( ! dini_Exists( "rAntiCheat.ni" ) )
	{
		print(" AntiCheat Aktivuotas" );
		dini_Create( "rAntiCheat.ini" );
		dini_IntSet( "rAntiCheat.ini" , "rAntiMoneyHack", true ); // Reik?më true Aktivuoja AntiCheat
																  // Reik?më false i?iungia Anticheat
	}

	AntiMoneyHackGuard = dini_Int( "AntiCheat.cfg", "AntiMoneyHack" );

	foreach(Player, i) // Optimizuoti negalima
	{
		Spawned[ i ] = false;
	}
}
//------------------------------------------------------------------------------
// Stock: AntiCheat
//------------------------------------------------------------------------------
stock AntiCheat( playerid, UseCheat[ ] )
{
	new
	    string1[ 126 ],
	    string2[ 126 ],
	    ip     [ 16 ],
        Vardas [ MAX_PLAYER_NAME ],
        File:cfgFile = fopen( "AntiChetas.cfg", io_append );

    GetPlayerIp      ( playerid, ip, sizeof( ip ) );
	GetPlayerName    ( playerid, Vardas, sizeof( Vardas ) );
    format           ( string2, sizeof( string2 ), "\n [AntiCheat]: Uzblokuotas %s | ID: %d | IP: %s ", Vardas, playerid, ip );
	format           ( string1, sizeof( string1 ), "[AntiCheat]: %s [Naudoja %s ] Jis ira u?blokuotas." , Vardas, UseCheat );
	SendClientMessage( playerid, COLOR_ZALIA, string1 );
	fwrite( cfgFile, string2 );
	fclose( cfgFile );

	BanEx( playerid, "AntiCheat: MoneyHack" );
	Spawned[ playerid ] = false;
	return 1;
}
//------------------------------------------------------------------------------
// Funckija: R_AntiCheat
//------------------------------------------------------------------------------
stock R_AntiCheat( )
{
	foreach(Player, i) // Optimizuoti negalima
    {
		if( Spawned[ i ] )
		{
		    if( pPinigai[ i ] - GetPlayerMoney( i ) == 1 )
			{
				pPinigai[ i ] = GetPlayerMoney( i );
			}
		    if( AntiMoneyHackGuard )
	    	{
		    	if( GetPlayerMoney( i ) != pPinigai[ i ] )
		    	{
			    	ResetPlayerMoney( i );
			    	GivePlayerMoney( i, pPinigai[ i ] );
                    AntiCheat( i, "MoneyHack" );
			    	return 1;
		    	}
		    }
        }
	}
	return true;
}
//------------------------------------------------------------------------------
// CallBack: OnPlayerSpawn
//------------------------------------------------------------------------------
public RInit_OnPlayerSpawn( playerid )
{
 	Spawned[ playerid ] = false;

	SetTimerEx( "SpawnedPlayer" , 3000, 0, "i", playerid );
	return true;
}
//------------------------------------------------------------------------------
// CallBack: OnPlayerConnect
//------------------------------------------------------------------------------
public RInit_OnPlayerConnect( playerid )
{
	pPinigai[ playerid ] = false;

	SendClientMessage( playerid, COLOR_ZALIA, "Serveris naudoja RenisiL AntiCheat Sistema" );
	SendClientMessage( playerid, COLOR_ZALIA, "Sripto Versija: v0.1.1" );
	return true;
}
//------------------------------------------------------------------------------
// CallBack: OnPlayerDisconnect
//------------------------------------------------------------------------------
public RInit_OnPlayerDisconnect( playerid, reason )
{
	Spawned[ playerid ] = false;
	return true;
}
//------------------------------------------------------------------------------
// CallBack: OnPlayerDeath
//------------------------------------------------------------------------------
public RInit_OnPlayerDeath( playerid, killerid, reason )
{
    Spawned[ playerid ] = false;
	return true;
}
//------------------------------------------------------------------------------
// Stock: R_GivePlayerMoney
//------------------------------------------------------------------------------
stock R_GivePlayerMoney( playerid, money )
{
	pPinigai[ playerid ]+= money;
	return GivePlayerMoney( playerid, money );
}
//------------------------------------------------------------------------------
// Stock: R_GetPlayerMoney
//------------------------------------------------------------------------------
stock R_GetPlayerMoney( playerid )
{
	return pPinigai[ playerid ];
}
//------------------------------------------------------------------------------
// Stock: R_RewsetPlayerMoney
//------------------------------------------------------------------------------
stock R_ResetPlayerMoney( playerid )
{
	pPinigai[ playerid ] = 0;
	return ResetPlayerMoney( playerid );
}
//------------------------------------------------------------------------------
// Funkcija: PlayerSpawned
//------------------------------------------------------------------------------
forward SpawnedPlayer( playerid );
public SpawnedPlayer( playerid )
{
	Spawned[ playerid ] = true;
	return true;
}

          //------------------------------------
          //    Include Pabaiga 2010/2011     //
          //------------------------------------