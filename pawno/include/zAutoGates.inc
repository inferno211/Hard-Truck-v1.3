/*  
	zAutoGates
	1.0
	by ziomal432
*/

#if defined zAutoGates_included
	#endinput
#endif
#define zAutoGates_included
#pragma library zAutoGates

#define MAX_GATES 20 //limit iloœci bram

enum E_GATES
{
	bool:gCreated,
	gObjectID,
	gGateState,
	Float:gOpenedPos[6],
	Float:gClosedPos[6],
	gOpeningSpeed,
	gClosingSpeed,
	Float:gDistance,
};

new GateData[MAX_GATES][E_GATES];

forward OnGateOpened(gateid);
forward OnGateClosed(gateid);
forward OnGateCreated(gateid);
forward GateTimer();

zAutoGates_OnGameModeInit()
{
	SetTimer("GateTimer", 1000, 1);
	return 1;
}

CreateGate(modelid, Float:OpenPosX, Float:OpenPosY, Float:OpenPosZ, Float:OpenRotX, Float:OpenRotY, Float:OpenRotZ, Float:ClosePosX, Float:ClosePosY, Float:ClosePosZ, Float:CloseRotX, Float:CloseRotY, Float:CloseRotZ, OpeningSpeed, ClosingSpeed, Float:Distance)
{
	for(new g; g < MAX_GATES; g++)
	{
		if(GateData[g][gCreated] == false)
		{
			GateData[g][gCreated] = true;
			GateData[g][gObjectID] = CreateObject(modelid, ClosePosX, ClosePosY, ClosePosZ, CloseRotX, CloseRotY, CloseRotZ);
			GateData[g][gGateState] = 0;
			GateData[g][gOpenedPos][0] = OpenPosX;
			GateData[g][gOpenedPos][1] = OpenPosY;
			GateData[g][gOpenedPos][2] = OpenPosZ;
			GateData[g][gOpenedPos][3] = OpenRotX;
			GateData[g][gOpenedPos][4] = OpenRotY;
			GateData[g][gOpenedPos][5] = OpenRotZ;
			GateData[g][gClosedPos][0] = ClosePosX;
			GateData[g][gClosedPos][1] = ClosePosY;
			GateData[g][gClosedPos][2] = ClosePosZ;
			GateData[g][gClosedPos][3] = CloseRotX;
			GateData[g][gClosedPos][4] = CloseRotY;
			GateData[g][gClosedPos][5] = CloseRotZ;
			GateData[g][gOpeningSpeed] = OpeningSpeed;
			GateData[g][gClosingSpeed] = ClosingSpeed;
			GateData[g][gDistance] = Distance;

			CallLocalFunction("OnGateCreated", "d", g);
			return g;
		}
	}
	return -1;
}

public GateTimer()
{
	new tempInt;

	for(new g; g < MAX_GATES; g++)
	{
		if(GateData[g][gCreated] == true)
		{
			tempInt = IsAnyPlayerNearGate(g);

			if(tempInt == 0 && GateData[g][gGateState] == 0)
			{
				GateData[g][gGateState] = 1;
				MoveObject(GateData[g][gObjectID], GateData[g][gOpenedPos][0], GateData[g][gOpenedPos][1], GateData[g][gOpenedPos][2], GateData[g][gOpeningSpeed]);
				SetObjectRot(GateData[g][gObjectID], GateData[g][gOpenedPos][3], GateData[g][gOpenedPos][4], GateData[g][gOpenedPos][5]);
				CallLocalFunction("OnGateOpened", "d", g);
			}
			else if(tempInt == 1 && GateData[g][gGateState] == 1)
			{
				GateData[g][gGateState] = 0;
				MoveObject(GateData[g][gObjectID], GateData[g][gClosedPos][0], GateData[g][gClosedPos][1], GateData[g][gClosedPos][2], GateData[g][gOpeningSpeed]);
				SetObjectRot(GateData[g][gObjectID], GateData[g][gClosedPos][3], GateData[g][gClosedPos][4], GateData[g][gClosedPos][5]);
				CallLocalFunction("OnGateClosed", "d", g);
			}
		}
	}
	return 1;
}

IsAnyPlayerNearGate(gateid)
{
	for(new player; player < GetMaxPlayers(); player++)
	{
		if(IsPlayerInRangeOfPoint(player, GateData[gateid][gDistance], GateData[gateid][gClosedPos][0], GateData[gateid][gClosedPos][1], GateData[gateid][gClosedPos][2]))
		{
			return 1;
		}
	}
	return 0;
}

