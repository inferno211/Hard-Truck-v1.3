//  ** Checkpoint Streamer **
//  ** by NoGravity        **
//  ** v 1.0               **
//  ** released 18/11/10   **
/*  ** Natives:            **

native CreateStreamedCheckpoint(Float: CorX, Float: CorY, Float: CorZ, Float: Size, Interior = 0, VirtualWorld = 0, ViewDistance = 150.0);
native DestroyStreamedCheckpoint(CPID);
native IsPlayerInStreamedCheckpoint(playerid, CPID);
native GetPlayerStreamedCheckpointId(playerid);
native ClearCheckpoints();
native Streamer_OnGameModeInit();
native Streamer_OnGameModeExit();

*/

forward CP_Stream();


#if !defined _samp_included
	#endinput
#endif

// ======================================
//     ** Centrum sterowania **



	//Maksymalna iloœæ Checkpointów:

#define Checkpoint_Limit 100

	//Iloœæ graczy w tablicach (Polecam skróciæ)

#define Players_Limit 256

	//Iloœæ graczy w funkcji (Polecam skróciæ)

#define Players GetMaxPlayers()

	//Zasiêg widocznoœci Checkpointów

#define View_Distance 30.0

	//Czas co jaki wykonywaæ ma siê timer Streamer'a (w milisekundach)

#define Timer_Time 1500



//     ** Koniec ** 
// ======================================

enum CheckpointInfo
{
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:Size,
	Float:Viewdistance,
	Interior,
	VirtualWorld
};

new
	CheckpointID = -1,
	PlayerCheckpoint[Players_Limit] = -1,
	CheckpointData[Checkpoint_Limit][CheckpointInfo],
	CheckpointOff[Checkpoint_Limit],
	StreamerTimer,
	bool:Limited = false;

Streamer_OnGameModeInit()
{
	print(" ==================\n  Checkpoint Streamer 1.0\n  by NoGravity Loaded...\n ==================");
	StreamerTimer = SetTimer("CP_Stream", Timer_Time, 1);
	return 1;
}

Streamer_OnGameModeExit()
{
	print(" ==================\n  Checkpoint Streamer 1.0\n  by NoGravity Unloaded...\n ==================");
	KillTimer(StreamerTimer);
	return 1;
}	

public CP_Stream()
{
	for(new Player; Player < Players; Player ++)
	{
		new bool:IsClose = false;
		if(IsPlayerConnected(Player))
		{
			for(new Checkpoint; Checkpoint < Checkpoint_Limit; Checkpoint ++)
			{
				if(CheckpointOff[Checkpoint] == 0)
				{
					if(IsPlayerInRangeOfPoint(Player, CheckpointData[Checkpoint][Viewdistance], CheckpointData[Checkpoint][PosX], CheckpointData[Checkpoint][PosY], CheckpointData[Checkpoint][PosZ])
					&& GetPlayerInterior(Player) == CheckpointData[Checkpoint][Interior]
					&& GetPlayerVirtualWorld(Player) == CheckpointData[Checkpoint][VirtualWorld])
					{
						SetPlayerCheckpoint(Player, CheckpointData[Checkpoint][PosX], CheckpointData[Checkpoint][PosY], CheckpointData[Checkpoint][PosZ], CheckpointData[Checkpoint][Size]);
						PlayerCheckpoint[Player] = Checkpoint;
						IsClose = true;
					}
				}
			}
			if(!IsClose)
			{
				DisablePlayerCheckpoint(Player);
				PlayerCheckpoint[Player] = -1;
			}
		}
	}
}

stock CreateStreamedCheckpoint(Float: Xf, Float: Yf, Float: Zf, Float:CP_Size, CP_Interior = 0, CP_VirtualWorld = 0, Float: CP_ViewDistance = View_Distance)
{
	CheckpointID ++;
	
	if((CheckpointID > Checkpoint_Limit) || Limited)
	{
		new OldCPID = CheckpointID;
		Limited = true;
		for(new r; r < Checkpoint_Limit; r ++)
		{
			if(1 == CheckpointOff[r])
			{
				CheckpointID = r;
			}
		}
		if(CheckpointID == OldCPID) return -1;
	}
		
	CheckpointData[CheckpointID][PosX] = Xf;
	CheckpointData[CheckpointID][PosY] = Yf;
	CheckpointData[CheckpointID][PosZ] = Zf;
	CheckpointData[CheckpointID][Size] = CP_Size;
	CheckpointData[CheckpointID][Viewdistance] = CP_ViewDistance;
	CheckpointData[CheckpointID][Interior] = CP_Interior;
	CheckpointData[CheckpointID][VirtualWorld] = CP_VirtualWorld;
	CheckpointOff[CheckpointID] = 0;

	return CheckpointID;
}

stock DestroyStreamedCheckpoint(CPID)
{
	if(CPID > Checkpoint_Limit)
		return 0;
	CheckpointOff[CPID] = 1;
	for(new Player; Player < Players; Player++)
		if(PlayerCheckpoint[Player] == CPID)
			DisablePlayerCheckpoint(Player);
	return 1;
}

#define GetPlayerStreamedCheckpointID GetPlayerStreamedCheckpointId

stock GetPlayerStreamedCheckpointId(playerid)
{
	if(IsPlayerConnected(playerid)) return PlayerCheckpoint[playerid];
	return -1;
}

stock IsPlayerInStreamedCheckpoint(playerid, CPID)
{
	if(IsPlayerInCheckpoint(playerid) && PlayerCheckpoint[playerid] == CPID)
		return 1;
	return 0;
}

stock ClearCheckpoints(/* No parameters expected */)
{
	for(new r; r < Checkpoints_Limit; r++)
	{
		CheckpointOff[r] = 1;
		CheckpointData[r][PosX] = 0.0;
		CheckpointData[r][PosY] = 0.0;
		CheckpointData[r][PosZ] = 0.0;
		CheckpointData[r][Size] = 0.0;
		CheckpointData[r][Viewdistance] = 0.0;
		CheckpointData[r][Interior] = 0;
		CheckpointData[r][VirtualWorld] = 0;
	}
	CheckpointID = -1;
	Limited = false;
}