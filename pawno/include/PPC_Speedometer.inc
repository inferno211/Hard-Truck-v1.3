// Forward the function needed to update the speedometer (used by a timer)
forward Speedometer_Update(playerid);
forward RefuelVehicle(playerid);

// This function sets up the speedometer for the given player
Speedometer_Setup(playerid)
{
	// Setup the speedometer for the player
	APlayerData[playerid][SpeedometerText] = TextDrawCreate(500.0, 395.0, " ");
	APlayerData[playerid][FuelGauge] = TextDrawCreate(500.0, 410.0, " ");
	// Enable the TextDraw for this player
	TextDrawShowForPlayer(playerid, APlayerData[playerid][SpeedometerText]);
	TextDrawShowForPlayer(playerid, APlayerData[playerid][FuelGauge]);
	// Start the speedometer timer
	APlayerData[playerid][SpeedometerTimer] = SetTimerEx("Speedometer_Update", 500, true, "i", playerid);

	return 1;
}

// This function cleans up the speedometer for the given player
Speedometer_Cleanup(playerid)
{
	// Destroy the speedometer textdraw
	TextDrawDestroy(APlayerData[playerid][SpeedometerText]);
	TextDrawDestroy(APlayerData[playerid][FuelGauge]);
	// Kill the speedometer timer
	KillTimer(APlayerData[playerid][SpeedometerTimer]);
	// Set player speed to 0
	APlayerData[playerid][PlayerSpeed] = 0;

	return 1;
}

// This function gets called by a timer which runs every 500ms to display and update the speedometer
public Speedometer_Update(playerid)
{
	// Setup local variables
	new vehicleid, Float:speed_x, Float:speed_y, Float:speed_z, Float:final_speed, speed_string[50], final_speed_int, Float:vehiclehealth;
	new FuelString[50], FuelStatus[20];
	new Msg[128], Name[24], Float:Armour;

	// Get the ID of the player's vehicle
	vehicleid = GetPlayerVehicleID(playerid);

	// Money and score hacks are neutralized here (every 0.5 seconds), as the speedometer sets the player money and score
	// to the value that's stored on the server
	// This should also fix the bug that player's money is resetted to 0 when doing a sudden server-restart without kicking the players first

	//******************************************************************************************************************************
	// Anti-hack stuff
	//******************************************************************************************************************************
	// Reset the player's money and set it to the stored value in the player's account (do the same for scorepoints)
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, APlayerData[playerid][PlayerMoney]);
	SetPlayerScore(playerid, APlayerData[playerid][PlayerScore]);

	// Port anyone out of the area who is not an admin and inside the area 69
	Player_PortOutAdminZone(playerid, 106.0, 1805.0, -50.0, 285.0, 1940.0, 40.0, 15.0, 1732.0, 25.0);

	// Weapon hacks are also neutralized here, except for police players (if they are allowed to have weapons)
	if ((PoliceGetsWeapons == true) && (APlayerData[playerid][PlayerClass] == ClassPolice))
	{
	    // Do nothing
	}
	else
		ResetPlayerWeapons(playerid); // Remove all weapons from the player

	// Check if the player got any armour (= health-hack)
	GetPlayerArmour(playerid, Armour);
	if (Armour > 1.0)
	{
		SendClientMessage(playerid, 0xFFFFFFFF, TXT_KickHealthHack);
		Kick(playerid);
	}

	// Check if the speed is higher than 300 (kick player if it is)
	if (APlayerData[playerid][PlayerSpeed] > 300)
	{
		SendClientMessage(playerid, 0xFFFFFFFF, TXT_KickSpeedHack);
	    Kick(playerid);
	}

	// Check if the player is not allowed to have a jetpack (admins lvl 3 and higher can use /fly, so they will be excluded)
	if (APlayerData[playerid][PlayerLevel] < 3)
	{
		// Check if the player is using a jetpack
		if (GetPlayerSpecialAction(playerid) == 2)
		{
			SendClientMessage(playerid, 0xFFFFFFFF, TXT_KickJetPackHack);
			Kick(playerid);
		}
	}

	//******************************************************************************************************************************
	// End of anti-hack stuff
	//******************************************************************************************************************************

	// Check and toggle spectate-mode when needed (when target player entered or exited his vehicle)
	if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
	{
	    // Get the target player's ID and name
	    new OtherPlayer = APlayerData[playerid][SpectateID];
		GetPlayerName(OtherPlayer, Name, sizeof(Name));

		// Use the same worldid and interiorid as the OtherPlayer
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(OtherPlayer));
		SetPlayerInterior(playerid, GetPlayerInterior(OtherPlayer));

		// Check if the player is spectating a player
		if (APlayerData[playerid][SpectateType] == ADMIN_SPEC_TYPE_PLAYER)
		{
		    // Check if the target player has entered a vehicle
		    if (GetPlayerVehicleSeat(OtherPlayer) != -1)
		    {
				// Change spectate mode to vehicle
				PlayerSpectateVehicle(playerid, GetPlayerVehicleID(OtherPlayer));
				APlayerData[playerid][SpectateID] = OtherPlayer;
				APlayerData[playerid][SpectateVehicle] = GetPlayerVehicleID(OtherPlayer);
				APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_VEHICLE;
				format(Msg, 128, "{00FF00}Player {FFFF00}%s{00FF00} has entered a vehicle, changing spectate mode to match", Name);
				SendClientMessage(playerid, 0xFFFFFFFF, Msg);
		    }
		}
		else // The player is spectating a vehicle
		{
		    // Check if the target player has exited a vehicle
		    if (GetPlayerVehicleSeat(OtherPlayer) == -1)
		    {
				// Change spectate mode to player
				PlayerSpectatePlayer(playerid, OtherPlayer);
				SetPlayerInterior(playerid, GetPlayerInterior(OtherPlayer));
				APlayerData[playerid][SpectateID] = OtherPlayer;
				APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_PLAYER;
				format(Msg, 128, "{00FF00}Player {FFFF00}%s{00FF00} has exited a vehicle, changing spectate mode to match", Name);
				SendClientMessage(playerid, 0xFFFFFFFF, Msg);
		    }
		}
	}

	// When the player got a wanted level and a police player warned him to stop, a timer is started and a variable is set to "true"
	// Check if this variable has been set
	if (APlayerData[playerid][PoliceWarnedMe] == true)
	{
	    // Check if the player has no wanted level anymore (after finishing a overloaded mission, player got fined, ...)
		if (GetPlayerWantedLevel(playerid) == 0)
		{
			APlayerData[playerid][PoliceCanJailMe] = false; // Clear the variable
			APlayerData[playerid][PoliceWarnedMe] = false; // Clear the variable
			APlayerData[playerid][Value_PoliceCanJailMe] = 0; // Clear the remaining time for the timer
			KillTimer(APlayerData[playerid][Timer_PoliceCanJailMe]); // Kill the timer
		}
	}

	// If the player is inside a vehicle
	if(vehicleid != 0)
	{
		// Get the vehicles velocity
		GetVehicleVelocity(vehicleid, speed_x, speed_y, speed_z);
		// Calculate the speed (in kph)
		final_speed = floatsqroot(((speed_x * speed_x) + (speed_y * speed_y)) + (speed_z * speed_z)) * 158.179;
		// Convert the float value to an int value
		final_speed_int = floatround(final_speed, floatround_round);
		// Also save the speed for the player
		APlayerData[playerid][PlayerSpeed] = final_speed_int;
		// Setup the string to display for the player and display it
		format(speed_string, 50, TXT_SpeedometerSpeed, final_speed_int);
		TextDrawSetString(APlayerData[playerid][SpeedometerText], speed_string);

		// Add the speed to the stats (this will be the meters driven in total)
		APlayerData[playerid][StatsMetersDriven] = APlayerData[playerid][StatsMetersDriven] + (final_speed / 7.2);

		// Also display the vehicle's health through the player-health bar
		GetVehicleHealth(vehicleid, vehiclehealth);
		SetPlayerHealth(playerid, vehiclehealth / 10.0);

		// Check if the speed is above 10kph and the fuel of the vehicle isn't empty yet
		if ((final_speed_int > 10) && (AVehicleData[vehicleid][Fuel] > 0))
			AVehicleData[vehicleid][Fuel] = AVehicleData[vehicleid][Fuel] - 1; // Decrease the fuel for this vehicle every time the timer is run

		// Construct the fuelgauge
		if ((AVehicleData[vehicleid][Fuel] > 0) && (AVehicleData[vehicleid][Fuel] < 100000))
			format(FuelStatus, 20, "~g~%s~r~%s", "I", "IIIIIIIII"); // Fuel is between 0% and 10% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 1)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 2)))
			format(FuelStatus, 20, "~g~%s~r~%s", "II", "IIIIIIII"); // Fuel is between 10% and 20% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 2)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 3)))
			format(FuelStatus, 20, "~g~%s~r~%s", "III", "IIIIIII"); // Fuel is between 20% and 30% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 3)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 4)))
			format(FuelStatus, 20, "~g~%s~r~%s", "IIII", "IIIIII"); // Fuel is between 30% and 40% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 4)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 5)))
			format(FuelStatus, 20, "~g~%s~r~%s", "IIIII", "IIIII"); // Fuel is between 40% and 50% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 5)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 6)))
			format(FuelStatus, 20, "~g~%s~r~%s", "IIIIII", "IIII"); // Fuel is between 50% and 60% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 6)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 7)))
			format(FuelStatus, 20, "~g~%s~r~%s", "IIIIIII", "III"); // Fuel is between 60% and 70% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 7)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 8)))
			format(FuelStatus, 20, "~g~%s~r~%s", "IIIIIIII", "II"); // Fuel is between 70% and 80% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 8)) && (AVehicleData[vehicleid][Fuel] < ((MaxFuel / 10) * 9)))
			format(FuelStatus, 20, "~g~%s~r~%s", "IIIIIIIII", "I"); // Fuel is between 80% and 90% full

		if ((AVehicleData[vehicleid][Fuel] >= ((MaxFuel / 10) * 9)) && (AVehicleData[vehicleid][Fuel] <= MaxFuel))
			format(FuelStatus, 20, "~g~%s", "IIIIIIIIII"); // Fuel is between 90% and 100% full (all bars are green)

		if (AVehicleData[vehicleid][Fuel] == 0)
			format(FuelStatus, 20, "~r~%s", "IIIIIIIIII"); // Fuel is empty (all bars are red)

		// Format the final fuel-gauge readout
		format(FuelString, 50, TXT_SpeedometerFuel, FuelStatus);
		// Display the fuel-gauge
		TextDrawSetString(APlayerData[playerid][FuelGauge], FuelString);

		// Check if the vehicle is out of fuel
		if (AVehicleData[vehicleid][Fuel] == 0)
		{
			// Stop the engine and turn off the lights
			new engine,lights,alarm,doors,bonnet,boot,objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vehicleid, 0, 0, alarm, doors, bonnet, boot, objective);
		}

		// Eject a player when he's not the owner of the vehicle (though he can be passenger in a vehicle owned by somebody else)
		if (APlayerData[playerid][PlayerEjected] == false)
			EjectPlayerFromAlienVehicle(playerid);

		// Also check if the player isn't speeding near a speedcamera (not for police-players)
		if (APlayerData[playerid][PlayerClass] != ClassPolice)
			CheckPlayerSpeeding(playerid);
	}
	else
	{
		// If the player is not inside a vehicle, display an empty string (looks like the speedometer is gone)
		TextDrawSetString(APlayerData[playerid][SpeedometerText], " ");
		TextDrawSetString(APlayerData[playerid][FuelGauge], " ");
		// Set the speed of the player to 0
		APlayerData[playerid][PlayerSpeed] = 0;
		// Also set the ejected-status as "false", as the player isn't inside the vehicle anymore (eject-cycle finished)
		APlayerData[playerid][PlayerEjected] = false;
	}
}



// This function checks if the player is inside a valid vehicle (not owned or owned by himself)
// and kicks him out when he entered a vehicle that belongs to somebody else
EjectPlayerFromAlienVehicle(playerid)
{
	// Setup local variables
	new vehicleid, Name[24], Msg[128];

	// Get the player's name (the one who is trying to enter the vehicle)
	GetPlayerName(playerid, Name, sizeof(Name));

    // Get the id of the vehicle
    vehicleid = GetPlayerVehicleID(playerid);

	// Check if the player entered as driver AND if the vehicle is owned by someone
	if ((GetPlayerVehicleSeat(playerid) == 0) && (AVehicleData[vehicleid][Owned] == true))
	{
		// Check if the vehicle is owned by somebody else (strcmp will not be 0)
		if (strcmp(AVehicleData[vehicleid][Owner], Name, false) != 0)
		{
			// Set the player as ejected already (this prevents this function to be executed multiple times
			// until the player is finally out of the vehicle)
		    APlayerData[playerid][PlayerEjected] = true;
			// Force the player out of the vehicle
			RemovePlayerFromVehicle(playerid);
			// Let the player know he cannot use somebody else's vehicle
			format(Msg, 128, TXT_SpeedometerCannotUseVehicle, AVehicleData[vehicleid][Owner]);
			SendClientMessage(playerid, 0xFFFFFFFF, Msg);
		}
	}

	return 1;
}



// This timer-function is called when a player picks up a refuelpickup
public RefuelVehicle(playerid)
{
	new RefuelMsg[128];
	// Get the vehicle-id of the player's vehicle
	new vID = GetPlayerVehicleID(playerid);
	// Calculate the amount of fuel that needs to be refuelled
	new Amount = MaxFuel - AVehicleData[vID][Fuel];
	// Calculate the price to refuel
	new RefuelPrice = (Amount * RefuelMaxPrice) / MaxFuel;

	// Check if the player has enough cash
	if (APlayerData[playerid][PlayerMoney] >= RefuelPrice)
	{
		// Refuel the vehicle
		AVehicleData[vID][Fuel] = MaxFuel;
		// Withdraw the money from the player
		RewardPlayer(playerid, -RefuelPrice, 0);
		// Let the player know he refuelled his vehicle
		format(RefuelMsg, 128, TXT_RefuelledVehicle, RefuelPrice);
		SendClientMessage(playerid, 0xFFFFFFFF, RefuelMsg);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_CannotRefuelVehicle);

	// Allow the player to move again
	TogglePlayerControllable(playerid, 1);

	return 1;
}



// This function checks if the player is speeding near a speedcamera
CheckPlayerSpeeding(playerid)
{
	// Check if the player hasn't been caught speeding recently
	if (APlayerData[playerid][PlayerCaughtSpeeding] == 0)
	{
		// Loop through all speedcameras
		for (new CamID; CamID < MAX_CAMERAS; CamID++)
		{
		    // Check if this camera has been created
		    if (ACameras[CamID][CamSpeed] != 0)
		    {
				// Check if the player is the driver of the vehicle
				if (GetPlayerVehicleSeat(playerid) == 0)
				{
					// Check if the player's speed is greater than the speed allowed by this camera (no need to process a distance-check if not speeding)
					if (APlayerData[playerid][PlayerSpeed] > ACameras[CamID][CamSpeed])
					{
						// Check if the player is near the camera
						if (IsPlayerInRangeOfPoint(playerid, 50.0, ACameras[CamID][CamX], ACameras[CamID][CamY], ACameras[CamID][CamZ]))
						{
						    // Prevent the player being caught multiple times by the same speed-camera
						    APlayerData[playerid][PlayerCaughtSpeeding] = 20;
						    // Increase the wanted-level of this player by 1 star
						    SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 1);
						    // Let the player know he's been caught speeding
						    SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerCaughtSpeeding);
						}
					}
				}
		    }
		    else
		    	break; // Stop the for-loop, all existing cameras have been processed
		}
	}
	else // If the player has been caught before, reduce the value until it's 0 again, then he can be caught again
	    APlayerData[playerid][PlayerCaughtSpeeding]--;
}

