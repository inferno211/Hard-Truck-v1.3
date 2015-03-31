// This file holds all common functions that don't fit in any other file

// This functions gives the player the given amount of money and scorepoints
RewardPlayer(playerid, Money, Points)
{
	// Add the given amount of money to the player's account
	APlayerData[playerid][PlayerMoney] = APlayerData[playerid][PlayerMoney] + Money;
	// Add the given amount of scorepoints to the player's account
	APlayerData[playerid][PlayerScore] = APlayerData[playerid][PlayerScore] + Points;
}

// This function creates the vehicle and saves the vehicle-lodel in the AVehicleData-array (can only be used during GameModeInit)
// It also sets the fuel to maximum
Vehicle_AddStatic(vModel, Float:vX, Float:vY, Float:vZ, Float:vRotation, vC1, vC2, vSpawnDelay)
{
	// Create a new static vehicle during GameModeInit
	new vid = AddStaticVehicleEx(vModel, vX, vY, vZ, vRotation, vC1, vC2, vSpawnDelay);
	// Save the vehicle-model
    AVehicleData[vid][Model] = vModel;
	// Set the fuel to maximum so the vehicle can be used
    AVehicleData[vid][Fuel] = MaxFuel;
	// Save the colors
    AVehicleData[vid][Color1] = vC1;
    AVehicleData[vid][Color2] = vC2;
	// Set this vehicle as a static vehicle
	AVehicleData[vid][StaticVehicle] = true;

	return vid;
}

// This function is the same as Vehicle_AddStatic, but uses CreateVehicle instead of AddStaticVehicleEx, so can be used everywhere
Vehicle_Create(vModel, Float:vX, Float:vY, Float:vZ, Float:vRotation, vC1, vC2, vSpawnDelay)
{
	// Create a new static vehicle during GameModeInit
	new vid = CreateVehicle(vModel, vX, vY, vZ, vRotation, vC1, vC2, vSpawnDelay);
	// Save the vehicle-model
    AVehicleData[vid][Model] = vModel;
	// Set the fuel to maximum so the vehicle can be used
    AVehicleData[vid][Fuel] = MaxFuel;
	// Save the colors
    AVehicleData[vid][Color1] = vC1;
    AVehicleData[vid][Color2] = vC2;

	return vid;
}

// This function deletes the vehicle and clears all the data (is only used for player-owned vehicles)
Vehicle_Delete(vid)
{
	// Setup local variables
	new HouseID, CarSlot;

	// Get the HouseID and CarSlot where the vehicle is linked to
	HouseID = AVehicleData[vid][BelongsToHouse];
	// Loop through all carslots of this house to find the vehicle-id
	for (new i; i < 5; i++)
	{
		// Check if this carslot holds the same vehicle-id
	    if (AHouseData[HouseID][VehicleIDs][i] == vid)
	    {
	        CarSlot = i; // The carslot has been found where the vehicle is stored, remember it
			break; // Stop the for-loop
		}
	}

	// Delete the vehicle
	DestroyVehicle(vid);
	// Clear the data
	AHouseData[HouseID][VehicleIDs][CarSlot] = 0;
	AVehicleData[vid][Owned] = false;
	AVehicleData[vid][Owner] = 0;
	AVehicleData[vid][Model] = 0;
	AVehicleData[vid][PaintJob] = 0;
	for (new i; i < 14; i++)
	    AVehicleData[vid][Components][i] = 0;
	AVehicleData[vid][Color1] = 0;
	AVehicleData[vid][Color2] = 0;
	AVehicleData[vid][SpawnX] = 0.0;
	AVehicleData[vid][SpawnY] = 0.0;
	AVehicleData[vid][SpawnZ] = 0.0;
	AVehicleData[vid][SpawnRot] = 0.0;
	AVehicleData[vid][BelongsToHouse] = 0;
}

// This function returns "1" if both locations are not closeby and returns "0" if both locations are close to eachother
Locations_CheckDistance(LocationA, LocationB, Float:Range)
{
	// Setup local variables
	new Float:Xa, Float:Ya, Float:Xb, Float:Yb, Float:X, Float:Y;

	// Get the coordinates of LocationA
	Xa = ALocations[LocationA][LocX];
	Ya = ALocations[LocationA][LocY];
	// Get the coordinates of LocationB
	Xb = ALocations[LocationB][LocX];
	Yb = ALocations[LocationB][LocY];

	// Calculate the distances between both locations
	Y = Yb - Ya;
	X = Xb - Xa;

	// Check if both locations are further apart then the range indicates
	if (((X * X) + (Y * Y)) > (Range * Range))
		return 1; // Location B is further away from Location A than Range indicates
	else
	    return 0; // both locations are closer to eachother than Range indicates
}

// This function ports all non-admin players out of the given area to the location specified
Player_PortOutAdminZone(playerid, Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2, Float:x3, Float:y3, Float:z3)
{
	// Setup local variables
	new Float:x, Float:y, Float:z;

	// Get the player's coordinates
	GetPlayerPos(playerid, x, y, z);

	// Check if the player is not an admin
	if (APlayerData[playerid][PlayerLevel] == 0)
		if ((x1 < x) && (x < x2))
		    if ((y1 < y) && (y < y2))
		        if ((z1 < z) && (z < z2))
				{
					SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You're not allowed inside an admin-area");
					SetPlayerPos(playerid, x3, y3, z3); // Port the player out of the area
				}
}

// This function sends the given text to all admins
SendAdminText(playerid, command[], text[])
{
	// Setup local variables
	new Name[24], Msg[128];

	// Loop through all players
	for (new i; i < MAX_PLAYERS; i++)
	{
		// Check if the player is an admin
		if (APlayerData[i][PlayerLevel] > 0)
		{
			// Get the player's name
			GetPlayerName(playerid, Name, sizeof(Name));
			// Send the given text to the admin
			format(Msg, 128, "{00FFCC}%s used: %s %s", Name, command, text);
			SendClientMessage(i, 0xFFFFFFFF, Msg);
		}
	}
}

// This timer informs the player how long he will be frozen
forward Player_FreezeTimer(playerid);
public Player_FreezeTimer(playerid)
{
	// Setup local variables
	new Msg[128];

	// Decrease the remaining time this player will be frozen
    APlayerData[playerid][PlayerFrozen]--;

	// Check if the player is allowed to move again
	if (APlayerData[playerid][PlayerFrozen] > 0)
	{
		// Construct the message to inform the player how long he stays frozen
		if (APlayerData[playerid][PlayerFrozen] >= 60)
			format(Msg, 128, "Frozen for %i minutes", APlayerData[playerid][PlayerFrozen] / 60);
		else
			format(Msg, 128, "Frozen for %i seconds", APlayerData[playerid][PlayerFrozen]);

		// Display the message to inform the player how long he stays frozen
		GameTextForPlayer(playerid, Msg, 1000, 4);
	}
	else // The timer has run out, so allow his to move again
	    TogglePlayerControllable(playerid, 1);
}

// This function creates a list of commands, starting from the FirstCommand and automatically shows the dialog
CommandList_Create(playerid)
{
	// Setup local variables
	new Counter, CommandList[1000], DialogTitle[128];

	// Only add 4 commands to the list, starting from the FirstItem
	for (new i = APlayerData[playerid][DialogFirstItem]; i < sizeof(ACommands); i++)
	{
		// Increase a counter (which holds the number of commands that have been added to the list
		Counter++;

		// Check if the maximum hasn't been reached yet
		if (Counter <= 5)
		{
		    // Check if this command is valid for this player
			if (APlayerData[playerid][PlayerLevel] >= ACommands[i][CommandLevel])
			{
				// Check if the command is used for admins or not
				if (ACommands[i][CommandLevel] == 0)
				{
				    // Add the commandname and description to the list
					format(CommandList, 500, "%s%s{00FF00}%s", CommandList, "\n", ACommands[i][CommandStructure]); // Add the name of the next command to the list on the next line
					format(CommandList, 500, "%s%s\t\t{FFFF00}%s", CommandList, "\n", ACommands[i][CommandDescription]); // Add the description of the next command to the list on the next line
				}
				else
				{
				    // Add the commandname and description to the list
					format(CommandList, 500, "%s%sLvl %i: {00FF00}%s", CommandList, "\n", ACommands[i][CommandLevel], ACommands[i][CommandStructure]); // Add the name of the next command to the list on the next line
					format(CommandList, 500, "%s%s\t\t{FFFF00}%s", CommandList, "\n", ACommands[i][CommandDescription]); // Add the description of the next command to the list on the next line
				}
			}
			else
				break;
		}
		else // 5 commands have been added to the list (now Counter = 6)
		{
		    // Add an empty line and "Next..." to the list to let the player know there are more commands
			format(CommandList, 500, "%s%s%s", CommandList, "\n \n", TXT_DialogEntryNext);
			// Also stop the For-loop
			break;
		}
	}

	// Construct the title for the dialog (to include a page number)
	format(DialogTitle, 128, TXT_DialogCommandTitle, (APlayerData[playerid][DialogFirstItem] / 5) + 1);
	// Show the commands in a dialog
	ShowPlayerDialog(playerid, DialogPlayerCommands, DIALOG_STYLE_LIST, DialogTitle, CommandList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);

	return 1;
}

