// Process the Register-dialog
Dialog_Register(playerid, response, inputtext[])
{
	new file[100], Name[MAX_PLAYER_NAME]; // Setup local variables
	GetPlayerName(playerid, Name, sizeof(Name)); // Get the playername
	format(file, sizeof(file), PlayerFile, Name); // Construct the complete filename for this player's account

	switch (response) // Check which button was clicked
	{
		case 1: // Player clicked "Register"
		{
			// Check if the player entered a password
			if(strlen(inputtext)>0)
			{
				// Store the password
				format(APlayerData[playerid][PlayerPassword], 50, "%s", inputtext);

				// Create the file and save default data to it, then reload it (so all data is put into the correct place)
				PlayerFile_Create(playerid);
				PlayerFile_Load(playerid);

				// Send a message to the client to inform him that his account has been registered
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_AccountRegistered);
				APlayerData[playerid][LoggedIn] = true; // The player has logged in properly
			}
			else
			{
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_WrongPassword);
				Kick(playerid);
			}
		}
	    case 0: // Player clicked "Cancel"
		{
			// Show a message that the player must be registered to play on this server
			SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerMustRegister);
		    // Kick the player
			Kick(playerid);
		}
	}

	return 1;
}



// Process the login-dialog
Dialog_Login(playerid, response, inputtext[])
{
	switch (response) // Check which button was clicked
	{
	    case 1: // Player clicked "Login"
		{
			// Check if the player entered a password
			if (strlen(inputtext) > 0)
			{
				// Check if the entered password is the same as the password saved in the player's account
			    if (strcmp(APlayerData[playerid][PlayerPassword], inputtext, false) == 0)
				{
					APlayerData[playerid][LoggedIn] = true; // The player has logged in properly
					SendClientMessage(playerid, 0xFFFFFFFF, TXT_LoggedIn); // Send a message to the client to inform him that he logged in properly
				}
				else
				{
					SendClientMessage(playerid, 0xFFFFFFFF, TXT_WrongPassword);
					Kick(playerid);
				}
			}
			else
			{
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_WrongPassword);
				Kick(playerid);
			}
		}
	    case 0: // Player clicked "Cancel"
		{
			// Show a message that the player must be logged in to play on this server
			SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerMustLogin);
		    // Kick the player
			Kick(playerid);
		}
	}

	return 1;
}



// Process the rescue dialog
Dialog_Rescue(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Check the class of the player
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassTruckDriver:
		{
			// Set the spawn coordinates based on the selection in the list
			switch (listitem)
			{
				case 0: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -525.0, -502.0, 26.0, 0.0, 0, 0, 0, 0, 0, 0);
				case 1: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -74.7, -1137.5, 4.5, 0.0, 0, 0, 0, 0, 0, 0);
				case 2: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 1457.0, 975.5, 11.0, 0.0, 0, 0, 0, 0, 0, 0);
				case 3: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -2136.0, -247.5, 36.5, 270.0, 0, 0, 0, 0, 0, 0);
				case 4: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 1766.5, -2040.7, 14.0, 270.0, 0, 0, 0, 0, 0, 0);
				case 5: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -546.0, 2594.0, 54.0, 270.0, 0, 0, 0, 0, 0, 0);
				case 6: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 332.0, 900.0, 25.0, 205.0, 0, 0, 0, 0, 0, 0);
				case 7: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -1575.0, -2724.0, 49.0, 146.0, 0, 0, 0, 0, 0, 0);
			}
		}
		case ClassBusDriver:
		{
			// Set the spawn coordinates based on the selection in the list
			switch (listitem)
			{
				case 0: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 1809.0, -1905.0, 13.6, 90.0, 0, 0, 0, 0, 0, 0);
				case 1: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -1983.0, 110.0, 27.7, 180.0, 0, 0, 0, 0, 0, 0);
				case 2: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 1060.0, 1260.0, 11.0, 270.0, 0, 0, 0, 0, 0, 0);
			}
		}
		case ClassPilot:
		{
			// Set the spawn coordinates based on the selection in the list
			switch (listitem)
			{
				case 0: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 2010.0, -2345.0, 13.6, 90.0, 0, 0, 0, 0, 0, 0);
				case 1: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -1211.0, -105.0, 14.2, 135.0, 0, 0, 0, 0, 0, 0);
				case 2: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 1630.0, 1615.0, 10.9, 90.0, 0, 0, 0, 0, 0, 0);
			}
		}
		case ClassPolice:
		{
			// Set the spawn coordinates based on the selection in the list
			switch (listitem)
			{
				case 0: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 1568.5, -1693.5, 6.0, 180.0, 0, 0, 0, 0, 0, 0);
				case 1: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -1590.0, 716.25, -5.0, 270.0, 0, 0, 0, 0, 0, 0);
				case 2: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 2275.0, 2460.0, 10.9, 90.0, 0, 0, 0, 0, 0, 0);
			}
		}
		case ClassCourier:
		{
			// Set the spawn coordinates based on the selection in the list
			switch (listitem)
			{
				case 0: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 798.0, -618.75, 16.4, 0.0, 0, 0, 0, 0, 0, 0);
				case 1: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), -1849.25, -135.0, 12.0, 90.0, 0, 0, 0, 0, 0, 0);
				case 2: SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), 1050.5, 1931.0, 10.9, 270.0, 0, 0, 0, 0, 0, 0);
			}
		}
	}

	SpawnPlayer(playerid); // Force the player to spawn at the requested coordinates
	SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerRescued); // Send the player a message that using "/rescue" costs $200
	// Reduce the player's money by 200
	RewardPlayer(playerid, -200, 0);

	return 1;
}



// Process the BuyLicense dialog
Dialog_BuyLicenses(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	switch (listitem)
	{
		case 0: // Player wants to buy a trucker license
		{
			// Check if the player is a trucker
			if (APlayerData[playerid][PlayerClass] == ClassTruckDriver)
			{
			    // Check if the player hasn't acquired his trucker's license yet
				if (APlayerData[playerid][TruckerLicense] == 0)
				{
					// Check if the player has enough money and enough score
					if ((APlayerData[playerid][PlayerMoney] >= 50000) && (APlayerData[playerid][PlayerScore] >= 100))
					{
						// Withdraw the money and score from the player's account
						RewardPlayer(playerid, -50000, -100);
						// Give the player the trucker's license
						APlayerData[playerid][TruckerLicense] = 1;
						// Let the player know he acquired his trucker's license
						SendClientMessage(playerid, 0xFFFFFFFF, TXT_TruckerLicenseBought);
					}
					else
					    SendClientMessage(playerid, 0xFFFFFFFF, TXT_TruckerLicenseNotEnoughMoney);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, TXT_TruckerLicenseOwned);
			}
			else
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_TruckerLicenseWrongClass);
		}
		case 1: // Player wants to buy a busdriver license
		{
			// Check if the player is a busdriver
			if (APlayerData[playerid][PlayerClass] == ClassBusDriver)
			{
			    // Check if the player hasn't acquired his busdriver's license yet
				if (APlayerData[playerid][BusLicense] == 0)
				{
					// Check if the player has enough money and enough score
					if ((APlayerData[playerid][PlayerMoney] >= 25000) && (APlayerData[playerid][PlayerScore] >= 50))
					{
						// Withdraw the money and score from the player's account
						RewardPlayer(playerid, -25000, -50);
						// Give the player the busdriver's license
						APlayerData[playerid][BusLicense] = 1;
						// Let the player know he acquired his busdriver's license
						SendClientMessage(playerid, 0xFFFFFFFF, TXT_BusLicenseBought);
					}
					else
					    SendClientMessage(playerid, 0xFFFFFFFF, TXT_BusLicenseNotEnoughMoney);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, TXT_BusLicenseOwned);
			}
			else
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_BusLicenseWrongClass);
		}
	}

	return 1;
}



// Process the work dialog for licensed truckers (show the list of loads after the player selected to choose his own load)
Dialog_TruckerSelectJobMethod(playerid, response, listitem)
{
	// Setup local variables
	new ProductList[50], NumProducts, TotalLoadList[1000];

	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Select what to do after the player chose "Select your own load" or "Auto assigned load"
	switch (listitem)
	{
		case 0: // Let the player choose his own load
		{
			switch (GetVehicleModel(GetPlayerVehicleID(playerid))) // Check the vehicle-model of the player to decide which loads the player can carry
			{
				case VehicleFlatbed, VehicleDFT30: // If the player's vehicle is a "Flatbed" or "DFT-30"
					ProductList = Product_GetList(PCV_TruckerNoTrailer, NumProducts); // Build a list of products defined for truckers without a trailer
				case VehicleCementTruck: // If the player's vehicle is a "CementTruck"
					ProductList = Product_GetList(PCV_TruckerCementTruck, NumProducts); // Build a list of products defined for truckers witha cement truck
				case VehicleLineRunner, VehicleTanker, VehicleRoadTrain: // If the player's vehicle is a "LineRunner", "Tanker" or "RoadTrain"
				{
					switch (GetVehicleModel(GetVehicleTrailer(GetPlayerVehicleID(playerid)))) // Select the loads based on the trailer model of the player
					{
						case VehicleTrailerCargo: // A cargo-trailer is attached
							ProductList = Product_GetList(PCV_TruckerCargoTrailer, NumProducts); // Build a list of products defined for truckers with a cargo-trailer
						case VehicleTrailerOre: // An Ore-trailer is attached
							ProductList = Product_GetList(PCV_TruckerOreTrailer, NumProducts); // Build a list of products defined for truckers with an ore-trailer
						case VehicleTrailerFluids: // A fluids-trailer is attached
							ProductList = Product_GetList(PCV_TruckerFluidsTrailer, NumProducts); // Build a list of products defined for truckers with a fluids-trailer
					}
				}
			}

			// Build the List with product-names
			for (new i; i < NumProducts; i++)
				format(TotalLoadList, 1000, "%s%s\n", TotalLoadList, ALoads[ProductList[i]][LoadName]);

			// Let the player choose a load
 			ShowPlayerDialog(playerid, DialogTruckerSelectLoad, DIALOG_STYLE_LIST, TXT_TruckerDialogSelectLoad, TotalLoadList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
		}

		case 1: Trucker_StartRandomJob(playerid); // Start a random trucker-job
	}

	return 1;
}



// Process the selected load and create the startlocation-dialog
Dialog_TruckerSelectLoad(playerid, response, listitem)
{
    // Setup local variables
	new TotalStartLocList[1000], ProductList[50], NumProducts, ProductID, LocID;

	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// First get the list of products again, so we can retrieve the selected load from it
	switch (GetVehicleModel(GetPlayerVehicleID(playerid))) // Check the vehicle-model of the player
	{
		case VehicleFlatbed, VehicleDFT30: // If the player's vehicle is a "Flatbed" or "DFT-30"
			ProductList = Product_GetList(PCV_TruckerNoTrailer, NumProducts); // Build a list of products defined for truckers without a trailer
		case VehicleCementTruck: // If the player's vehicle is a "CementTruck"
			ProductList = Product_GetList(PCV_TruckerCementTruck, NumProducts); // Build a list of products defined for truckers witha cement truck
		case VehicleLineRunner, VehicleTanker, VehicleRoadTrain: // If the player's vehicle is a "LineRunner", "Tanker" or "RoadTrain"
		{
			switch (GetVehicleModel(GetVehicleTrailer(GetPlayerVehicleID(playerid)))) // Select the loads based on the trailer model of the player
			{
				case VehicleTrailerCargo: // A cargo-trailer is attached
					ProductList = Product_GetList(PCV_TruckerCargoTrailer, NumProducts); // Build a list of products defined for truckers with a cargo-trailer
				case VehicleTrailerOre: // An Ore-trailer is attached
					ProductList = Product_GetList(PCV_TruckerOreTrailer, NumProducts); // Build a list of products defined for truckers with an ore-trailer
				case VehicleTrailerFluids: // A fluids-trailer is attached
					ProductList = Product_GetList(PCV_TruckerFluidsTrailer, NumProducts); // Build a list of products defined for truckers with a fluids-trailer
			}
		}
	}

	// Store the selected LoadID in the player's account
	APlayerData[playerid][LoadID] = ProductList[listitem];
	ProductID = APlayerData[playerid][LoadID];

	// Build a list of start-locations for this product
	for (new i; i < 30; i++)
	{
	    // Get the location-id
	    LocID = ALoads[ProductID][FromLocations][i];
	    // Check if it a valid location-id (not 0)
	    if (LocID != 0)
			format(TotalStartLocList, 1000, "%s%s\n", TotalStartLocList, ALocations[LocID][LocationName]); // Add the location-name to the list
		else
		    break; // As soon as an invalid location-id has been found, stop adding entries to the location-list
	}

	// Ask the player to choose a start-location
	ShowPlayerDialog(playerid, DialogTruckerStartLoc, DIALOG_STYLE_LIST, TXT_TruckerDialogSelectStartLoc, TotalStartLocList, TXT_DialogButtonSelect, TXT_DialogButtonCancel); // Let the player choose a starting location

	return 1;
}



// Process the selected startlocation and create the endlocation-dialog
Dialog_TruckerSelectStartLoc(playerid, response, listitem)
{
    // Setup local variables
	new ProductID, LocID, TotalEndLocList[1000];

	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Get the LoadID that's stored in the player's account
	ProductID = APlayerData[playerid][LoadID];
	// Store the chosen start-location in the player's account
	APlayerData[playerid][JobLoc1] = ALoads[ProductID][FromLocations][listitem];

	// Build a list of end-locations for this product
	for (new i; i < 30; i++)
	{
	    // Get the location-id
	    LocID = ALoads[ProductID][ToLocations][i];
	    // Check if it a valid location-id (not 0)
	    if (LocID != 0)
			format(TotalEndLocList, 1000, "%s%s\n", TotalEndLocList, ALocations[LocID][LocationName]); // Add the location-name to the list
		else
		    break; // As soon as an invalid location-id has been found, stop adding entries to the location-list
	}

	// Ask the player to choose an end-location
	ShowPlayerDialog(playerid, DialogTruckerEndLoc, DIALOG_STYLE_LIST, TXT_TruckerDialogSelectEndLoc, TotalEndLocList, TXT_DialogButtonSelect, TXT_DialogButtonCancel); // Let the player choose a endlocation

	return 1;
}



// Process the selected endlocation and start the job
Dialog_TruckerSelectEndLoc(playerid, response, listitem)
{
    // Setup local variables
	new RouteText[128], loadName[50], startlocName[50], endlocName[50], LoadMsg[128], Float:x, Float:y, Float:z, ProductID;

	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Get the LoadID that's stored in the player's account
	ProductID = APlayerData[playerid][LoadID];
	// Store the chosen end-location in the player's account
	APlayerData[playerid][JobLoc2] = ALoads[ProductID][ToLocations][listitem];

    // Get the names for the load, startlocation and endlocation
	format(loadName, 50, "%s", ALoads[ProductID][LoadName]);
	format(startlocName, 50, "%s", ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
	format(endlocName, 50, "%s", ALocations[APlayerData[playerid][JobLoc2]][LocationName]);

	// Job has started
	APlayerData[playerid][JobStarted] = true;
	// Store the vehicleID (required to be able to check if the player left his vehicle)
	APlayerData[playerid][VehicleID] = GetPlayerVehicleID(playerid);
	// Store the trailerID (required to be able to check if the player lost his trailer)
	APlayerData[playerid][TrailerID] = GetVehicleTrailer(GetPlayerVehicleID(playerid));
	// Set jobstep to 1 (going to load the goods)
	APlayerData[playerid][JobStep] = 1;
	// Combine all data into a string for the TextDraw (the player can see this all the time) to describe the mission
	format(RouteText, 255, TXT_HaulingCargoFromToPickup, loadName, startlocName, endlocName);
	// Set the TextDraw so the player can see it
	TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
	// Grab the x, y, z positions for the first location
	x = ALocations[APlayerData[playerid][JobLoc1]][LocX];
	y = ALocations[APlayerData[playerid][JobLoc1]][LocY];
	z = ALocations[APlayerData[playerid][JobLoc1]][LocZ];
	// Create a checkpoint where the player should load the goods
	SetPlayerCheckpoint(playerid, x, y, z, 7);
	// Start a timer that ticks every second to see if the player is still inside his vehicle
	APlayerData[playerid][VehicleTimerTime] = Trucker_TimeToFailMission;
	APlayerData[playerid][VehicleTimer] = SetTimerEx("Trucker_VehicleTimer", 1000, true, "d" , playerid);
	// Inform the player that he must load his goods
	format(LoadMsg, 128, TXT_PickupCargoAt, loadName, startlocName);
	SendClientMessage(playerid, 0xFFFFFFFF, LoadMsg);

	return 1;
}



// Process the work dialog for licensed busdrivers (show the list of busroutes after the player selected to choose his own route)
Dialog_BusSelectJobMethod(playerid, response, listitem)
{
	// Setup local variables
	new BusLine, Description[100], TotalRouteList[500];

	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

    // Check if the player already started a job
	if (APlayerData[playerid][JobStarted] == false)
	{
		// Select what to do after the player chose "Choose your own busroute" or "Auto assigned busroute"
		switch (listitem)
		{
			case 0: // Let the player choose his own busroute
			{
				// Construct the list of busroutes
				for (new i; i < sizeof(ABusRoutes); i++)
				{
					// Get the data about the route
					BusLine = ABusRoutes[i][LineNumber];
					format(Description, 100, ABusRoutes[i][RouteDescription]);
					// Add the busline to the list
					format(TotalRouteList, 500, "%s%sLine %i (%s)", TotalRouteList, "\n", BusLine, Description);
				}

				// Let the player choose a busroute
 				ShowPlayerDialog(playerid, DialogBusSelectRoute, DIALOG_STYLE_LIST, TXT_SelectBusRoute, TotalRouteList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
			}

			case 1: BusDriver_StartJob(playerid, random(sizeof(ABusRoutes))); // Start a random job
		}
	}
	else // Send a message to let the player know he already has a job
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_BusdriverAlreadyDoingJob);

	return 1;
}

// Process the work dialog for licensed busdrivers (let the player start the job he selects from the busroute-list)
Dialog_BusSelectRoute(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// The selected listitem is automatically the busroute, so start the job based on the item selected in the busroute-list
	BusDriver_StartJob(playerid, listitem);

	return 1;
}



// Process the chosen quantity for courier job
Dialog_CourierSelectQuant(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Listitem 0 represent maximum 2 houses to deliver a package, listitem 1 is max 5 houses, item 2 is max 10 houses
	switch (listitem)
	{
		case 0: APlayerData[playerid][CourierMaxStep] = 2;
		case 1: APlayerData[playerid][CourierMaxStep] = 5;
		case 2: APlayerData[playerid][CourierMaxStep] = 10;
	}

	// Start the job
	Courier_BeginJob(playerid);

	return 1;
}



// Process the bike dialog
Dialog_Bike(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new Float:x, Float:y, Float:z, Float:rot, CarID, msg[120], vID, pName[24];
	new engine,lights,alarm,doors,bonnet,boot,objective;

	// Get the player's position and name
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, rot);
	GetPlayerName(playerid, pName, 24);

	// Spawn the motorcycle based on the selection in the list, and spawn it 5 units north of the player
	switch (listitem)
	{
		case 0: CarID = VehicleBike; // Bike
		case 1: CarID = VehicleBMX; // BMX
		case 2: CarID = VehicleMountainBike; // Mountain Bike
		case 3: CarID = VehicleFaggio; // Faggio
		case 4: CarID = VehiclePizzaBoy; // Pizzaboy
		case 5: CarID = VehicleBF400; // BF-400
		case 6: CarID = VehicleNRG500; // NRG-500
		case 7: CarID = VehiclePCJ600; // PCJ-600
		case 8: CarID = VehicleFCR900; // FCR-900
		case 9: CarID = VehicleFreeway; // Freeway
		case 10: CarID = VehicleWayfarer; // Wayfarer
		case 11: CarID = VehicleSanchez; // Sanchez
		case 12: CarID = VehicleQuad; // Quad
	}

	// Spawn the vehicle based on the selection in the list with a random color
	// Also set max-fuel and save the model for the vehicle
	vID = Vehicle_Create(CarID, x, y, z, rot, random(126), random(126), 600);
	// Put the player in the vehicle
	PutPlayerInVehicle(playerid, vID, 0);
	// Turn on the engine and lights
	GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vID, 1, 1, alarm, doors, bonnet, boot, objective);
	// Inform all players about it
	format(msg, 120, TXT_PlayerSpawnedVehicle, pName, vID, CarID, x, y + 5.0, z);
	SendClientMessageToAll(0xFFFFFFFF, msg);

	return 1;
}



// Process the car dialog
Dialog_Car(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response)
	{
		// Reset the FirstCar (so the list won't start at an unexpected location in the list, but back at the start of the list)
		APlayerData[playerid][DialogCarFirstCar] = 0;
		return 1; // Exit the function
	}

	// Process the selected listitem
	switch (listitem)
	{
		case 10: // Player chooses the empty line between the carlist and "Next...", so refresh the current list
		{
		    // Refresh the current list of cars and let the player choose one (show dialog)
		    CarList_Create(playerid);
			// Exit the function
			return 1;
		}
		case 11: // Player chooses "Next..."
		{
		    // Add 10 to the FirstCar, so the list will start further down the array (will show the next 10 cars)
		    APlayerData[playerid][DialogCarFirstCar] = APlayerData[playerid][DialogCarFirstCar] + 10;
		    // Create a new list of cars and show the dialog
		    CarList_Create(playerid);
		}
		default: // Player chooses a car
		{
		    // Setup local variables
	    	new Float:x, Float:y, Float:z, Float:rot, CarIndex, msg[128], vID, pName[24];
			new engine,lights,alarm,doors,bonnet,boot,objective;

			// FirstCar is the index of the first car in the list, so select the proper index when a car is chosen by the player
			CarIndex = APlayerData[playerid][DialogCarFirstCar] + listitem;

			// Get the player's position and name
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, rot);
			GetPlayerName(playerid, pName, 24);

			// Spawn the vehicle based on the selection in the list with a random color
			// Also set max-fuel and save the model for the vehicle
			vID = Vehicle_Create(ACars[CarIndex][CarModel], x, y, z + 2.0, rot, random(126), random(126), 600);
			// Put the player in the vehicle
			PutPlayerInVehicle(playerid, vID, 0);
			// Turn on the engine and lights
			GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vID, 1, 1, alarm, doors, bonnet, boot, objective);
			// Inform all players about it
			format(msg, 120, TXT_PlayerSpawnedVehicle, pName, vID, ACars[CarIndex][CarModel], x, y + 10.0, z + 2.0);
			SendClientMessageToAll(0xFFFFFFFF, msg);
			// Also, after spawning a vehicle, reset FirstCar (so next time, the list starts from the start)
			APlayerData[playerid][DialogCarFirstCar] = 0;
		}
	}

	return 1;
}



// Process the Plane dialog
Dialog_Plane(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response)
	{
		// Reset the FirstPlane (so the list won't start at an unexpected location in the list, but back at the start of the list)
		APlayerData[playerid][DialogPlaneFirstPlane] = 0;
		return 1; // Exit the function
	}

	// Process the selected listitem
	switch (listitem)
	{
		case 10: // Player chooses the empty line between the Planelist and "Next...", so refresh the current list
		{
		    // Refresh the current list of Planes and let the player choose one (show dialog)
		    PlaneList_Create(playerid);
			// Exit the function
			return 1;
		}
		case 11: // Player chooses "Next..."
		{
		    // Add 10 to the FirstPlane, so the list will start further down the array (will show the next 10 Planes)
		    APlayerData[playerid][DialogPlaneFirstPlane] = APlayerData[playerid][DialogPlaneFirstPlane] + 10;
		    // Create a new list of Planes and show the dialog
		    PlaneList_Create(playerid);
		}
		default: // Player chooses a Plane
		{
		    // Setup local variables
	    	new Float:x, Float:y, Float:z, Float:rot, PlaneIndex, msg[128], vID, pName[24];
			new engine,lights,alarm,doors,bonnet,boot,objective;

			// FirstPlane is the index of the first Plane in the list, so select the proper index when a Plane is chosen by the player
			PlaneIndex = APlayerData[playerid][DialogPlaneFirstPlane] + listitem;

			// Get the player's position and name
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, rot);
			GetPlayerName(playerid, pName, 24);

			// Spawn the vehicle based on the selection in the list with a random color
			// Also set max-fuel and save the model for the vehicle
			vID = Vehicle_Create(APlanes[PlaneIndex][PlaneModel], x, y, z + 5.0, rot, random(126), random(126), 600);
			// Put the player in the vehicle
			PutPlayerInVehicle(playerid, vID, 0);
			// Turn on the engine and lights
			GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vID, 1, 1, alarm, doors, bonnet, boot, objective);
			// Inform the player about it
			format(msg, 128, TXT_PlayerSpawnedVehicle, pName, vID, APlanes[PlaneIndex][PlaneModel], x, y + 10.0, z + 5.0);
			SendClientMessageToAll(0xFFFFFFFF, msg);
			// Also, after spawning a vehicle, reset FirstPlane (so next time, the list starts from the start)
			APlayerData[playerid][DialogPlaneFirstPlane] = 0;
		}
	}

	return 1;
}



// Process the Trailer dialog
Dialog_Trailer(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response)
	{
		// Reset the FirstTrailer (so the list won't start at an unexpected location in the list, but back at the start of the list)
		APlayerData[playerid][DialogTrailerFirstTrailer] = 0;
		return 1; // Exit the function
	}

	// Process the selected listitem
	switch (listitem)
	{
		case 10: // Player chooses the empty line between the Trailerlist and "Next...", so refresh the current list
		{
		    // Refresh the current list of Trailers and let the player choose one (show dialog)
		    TrailerList_Create(playerid);
			// Exit the function
			return 1;
		}
		case 11: // Player chooses "Next..."
		{
		    // Add 10 to the FirstTrailer, so the list will start further down the array (will show the next 10 Trailers)
		    APlayerData[playerid][DialogTrailerFirstTrailer] = APlayerData[playerid][DialogTrailerFirstTrailer] + 10;
		    // Create a new list of Trailers and show the dialog
		    TrailerList_Create(playerid);
		}
		default: // Player chooses a Trailer
		{
		    // Setup local variables
	    	new Float:x, Float:y, Float:z, TrailerIndex, msg[128], vID, pName[24];

			// FirstTrailer is the index of the first Trailer in the list, so select the proper index when a Trailer is chosen by the player
			TrailerIndex = APlayerData[playerid][DialogTrailerFirstTrailer] + listitem;

			// Get the player's position and name
			GetPlayerPos(playerid, x, y, z);
			GetPlayerName(playerid, pName, 24);

			// Spawn the vehicle based on the selection in the list with a random color, and spawn it 10 units north of the player
			// Also set max-fuel and save the model for the vehicle
			vID = Vehicle_Create(ATrailers[TrailerIndex][TrailerModel], x, y + 10.0, z + 5.0, 0.0, random(126), random(126), 600);
			// Inform the player about it
			format(msg, 128, TXT_PlayerSpawnedVehicle, pName, vID, ATrailers[TrailerIndex][TrailerModel], x, y + 10.0, z + 5.0);
			SendClientMessageToAll(0xFFFFFFFF, msg);
			// Also, after spawning a vehicle, reset FirstTrailer (so next time, the list starts from the start)
			APlayerData[playerid][DialogTrailerFirstTrailer] = 0;
		}
	}

	return 1;
}



// Process the chosen vehicleclass to show the actual vehicle-list of this vehicleclass
Dialog_RentProcessClass(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new CarList[1000], DialogTitle[128];

	// Set the player's chosen vehicle-class based on the listitem he chose (add 1 as the vehicleclass starts at 1)
	APlayerData[playerid][DialogRentVClass] = listitem + 1;

	// Add all vehicles of the same class to the list
	for (new i; i < sizeof(ABuyableVehicles); i++)
	{
		// Check if the vehicle in the list has the same class as requested
		if (ABuyableVehicles[i][VehicleClass] == APlayerData[playerid][DialogRentVClass])
		{
			// Add the carname to the list and it's price
			format(CarList, 1000, "%s%s%s ($%i)", CarList, "\n", ABuyableVehicles[i][CarName], ABuyableVehicles[i][Price] / 10); // Add the name of the next car to the list on the next line
		}
	}

	// Check if the list is empty
	if (strlen(CarList) == 0)
	{
		// Send the player a message that all vehicles have been disabled of the chosen class (no vehicles in the array of this class)
		SendClientMessage(playerid, 0xFFFFFFFF, TXT_BuyRentCarEmptyList);
		// Exit the function (don't ask to choose a vehicle)
		return 1;
	}

	// Set a title for the dialog based on the requested vehicleclass
	switch (APlayerData[playerid][DialogRentVClass])
	{
		case VClassBike: format(DialogTitle, 128, TXT_RentBike);
		case VClassBoat: format(DialogTitle, 128, TXT_RentBoat);
		case VClassConvertible: format(DialogTitle, 128, TXT_RentConvertible);
		case VClassHelicopter: format(DialogTitle, 128, TXT_RentHelicopter);
		case VClassIndustrial: format(DialogTitle, 128, TXT_RentIndustrial);
		case VClassLowRider: format(DialogTitle, 128, TXT_RentLowRider);
		case VClassOffRoad: format(DialogTitle, 128, TXT_RentOffRoad);
		case VClassPlane: format(DialogTitle, 128, TXT_RentPlane);
		case VClassPublic: format(DialogTitle, 128, TXT_RentPublicService);
		case VClassRCVehicle: format(DialogTitle, 128, TXT_RentRC);
		case VClassSaloons: format(DialogTitle, 128, TXT_RentSaloon);
		case VClassSportCar: format(DialogTitle, 128, TXT_RentSport);
		case VClassStationCar: format(DialogTitle, 128, TXT_RentStationWagon);
		case VClassTrailer: format(DialogTitle, 128, TXT_RentTrailer);
		case VClassUnique: format(DialogTitle, 128, TXT_RentUnique);
	}

	// Ask which car the player wants to have by showing the dialog
	ShowPlayerDialog(playerid, DialogRentCar, DIALOG_STYLE_LIST, DialogTitle, CarList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);

	return 1;
}



// This dialog gives the chosen vehicle to the player (bought or rented)
Dialog_RentCar(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new Counter, Name[24], Float:x, Float:y, Float:z, Msg[128];

	// Loop through the entire list of buyable vehicles
	for (new i; i < sizeof(ABuyableVehicles); i++)
	{
		// Check if the vehicle in the list has the same class as requested
		if (ABuyableVehicles[i][VehicleClass] == APlayerData[playerid][DialogRentVClass])
		{
		    // Check if this is the vehicle that the player chose
		    if (Counter == listitem)
			{
			    // Check if the player has enough money to afford renting this vehicle
			    if (APlayerData[playerid][PlayerMoney] >= (ABuyableVehicles[i][Price] / 10))
			    {
					// Check if the player already has a rented vehicle
					if (APlayerData[playerid][RentedVehicleID] != 0)
					{
						// Clear the data for the already rented vehicle
						AVehicleData[APlayerData[playerid][RentedVehicleID]][Fuel] = 0;
						AVehicleData[APlayerData[playerid][RentedVehicleID]][Owned] = false;
						AVehicleData[APlayerData[playerid][RentedVehicleID]][Owner] = 0;
						AVehicleData[APlayerData[playerid][RentedVehicleID]][PaintJob] = 0;
						for (new j; j < 14; j++)
						{
							AVehicleData[APlayerData[playerid][RentedVehicleID]][Components][j] = 0;
						}
						// Destroy the vehicle
						DestroyVehicle(APlayerData[playerid][RentedVehicleID]);
						// Send the player a message that his previously rented vehicle has been replaced by the new one
						SendClientMessage(playerid, 0xFFFFFFFF, TXT_AlreadyRentedVehicle);
					}

					// Create the vehicle and link it to the player's account
					GetPlayerPos(playerid, x, y, z);
				    APlayerData[playerid][RentedVehicleID] = CreateVehicle(ABuyableVehicles[i][CarModel], x, y, z, 0.0, -1, -1, 600);
					// Also set owndership data
					AVehicleData[APlayerData[playerid][RentedVehicleID]][Fuel] = MaxFuel;
					AVehicleData[APlayerData[playerid][RentedVehicleID]][Owned] = true;
					GetPlayerName(playerid, Name, sizeof(Name));
					format(AVehicleData[APlayerData[playerid][RentedVehicleID]][Owner], 24, Name);
					// Put the player in the vehicle
					PutPlayerInVehicle(playerid, APlayerData[playerid][RentedVehicleID], 0);
					// Turn on the engine
					new engine,lights,alarm,doors,bonnet,boot,objective;
					GetVehicleParamsEx(APlayerData[playerid][RentedVehicleID], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(APlayerData[playerid][RentedVehicleID], 1, lights, alarm, doors, bonnet, boot, objective);
					// Let the player pay for renting the vehicle
					APlayerData[playerid][PlayerMoney] = APlayerData[playerid][PlayerMoney] - (ABuyableVehicles[i][Price] / 10);
					// Let the player know he rented a vehicle
					format(Msg, 128, TXT_PlayerRentsVehicle, ABuyableVehicles[i][CarName], (ABuyableVehicles[i][Price] / 10));
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
				else // The player has not enough money to rent this vehicle
				    SendClientMessage(playerid, 0xFFFFFFFF, TXT_RentingTooExpensive);

				// Stop looking for the vehicle, as it's found and given to the player already
				return 1;
			}
		    else // The player chose another vehicle from the same class, keep looking for another one
		        Counter++;
		}
	}

	return 1;
}



// Process the weather dialog
Dialog_Weather(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new WeatherID;

	// Select the weather
	switch (listitem)
	{
		case 0: WeatherID = 0; // Normal
		case 1: WeatherID = 8; // Stormy
		case 2: WeatherID = 9; // Foggy
		case 3: WeatherID = 11; // Scorching hot
		case 4: WeatherID = 16; // Dull, cloudy, rainy
		case 5: WeatherID = 19; // Sandstorm
		case 6: WeatherID = 20; // Green Fog
		case 7: WeatherID = 33; // Dark, cloudy, brown
		case 8: WeatherID = 39; // Extremely bright
		case 9: WeatherID = 43; // Dark toxic clouds
		case 10: WeatherID = 44; // Black & white sky
	}

	// Set the weather
    SetWeather(WeatherID);
    // Inform the player about it
	SendClientMessage(playerid, 0xFFFFFFFF, TXT_ChangedWeather;

	return 1;
}

// Process the caroption dialog
Dialog_CarOption(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

    // Setup local variables
	new vehicleid, engine, lights, bool:alarm, bool:doors, bool:bonnet, bool:boot, bool:objective;

	// Get the player's vehicle
	vehicleid = GetPlayerVehicleID(playerid);

	// Get the current status of the vehicle
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	// Select the weather
	switch (listitem)
	{
		case 0: SetVehicleParamsEx(vehicleid, 1 - engine, lights, alarm, doors, bonnet, boot, objective);
		case 1: SetVehicleParamsEx(vehicleid, engine, 1 - lights, alarm, doors, bonnet, boot, objective);
		case 2:
		{
			if (alarm == true)
				SetVehicleParamsEx(vehicleid, engine, lights, false, doors, bonnet, boot, objective);
			else
				SetVehicleParamsEx(vehicleid, engine, lights, true, doors, bonnet, boot, objective);
		}
		case 3:
		{
			if (doors == true)
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, false, bonnet, boot, objective);
			else
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, true, bonnet, boot, objective);
		}
		case 4:
		{
			if (bonnet == true)
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, false, boot, objective);
			else
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, true, boot, objective);
		}
		case 5:
		{
			if (boot == true)
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, false, objective);
			else
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, true, objective);
		}
		case 6:
		{
			if (objective == true)
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, false);
			else
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, true);
		}
	}

	return 1;
}



// This function processes the convoy dialog
Dialog_SelectConvoy(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new Convoy;

	// The convoy-id is automatically the listitem
	Convoy = listitem;

	// Check the status of the selected convoy to determine what to do
	switch (AConvoys[Convoy][Status])
	{
	    case CONVOY_EMPTY: // Convoy isn't started yet, this is a free convoy
		{
			Convoy_Create(playerid, Convoy); // Try to create the convoy
		}
	    case CONVOY_OPEN: // Convoy has been created but still open for new members to join
		{
		    Convoy_Join(playerid, Convoy); // Try to join the convoy
		}
	    case CONVOY_FULL: // Convoy is full (10 members)
		{
			SendClientMessage(playerid, 0xFFFFFFFF, TXT_ConvoyFull);
		}
	    case CONVOY_CLOSED: // Convoy has started already (the leader already chose a job, causing the convoy to close)
		{
			SendClientMessage(playerid, 0xFFFFFFFF, TXT_ConvoyEnRoute);
		}
	}

	return 1;
}

// This function processes the housemenu dialog
Dialog_HouseMenu(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new UpgradeList[2000], HouseID, DialogTitle[200], Counter, UpgradePrice, Msg[128], CarSlot, VehicleClassList[1000], VehicleList[200];

	// Get the HouseID of the house where the player is
	HouseID = APlayerData[playerid][CurrentHouse];

	// Select an option based on the selection in the list
	switch(listitem)
	{
	    case 0: // Change house name
	    {
	        format(DialogTitle, 200, TXT_DialogOldHouseName, AHouseData[HouseID][HouseName]);
			ShowPlayerDialog(playerid, DialogHouseNameChange, DIALOG_STYLE_INPUT, DialogTitle, TXT_DialogEnterNewHouseName, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
	    }
	    case 1: // Upgrade the house
	    {
	        // Check if it's possible to upgrade further
			if (AHouseData[HouseID][HouseLevel] < AHouseData[HouseID][HouseMaxLevel])
			{
				// Add only the upgrades above the current house-level to the upgradelist
				for (new i = AHouseData[HouseID][HouseLevel] + 1; i <= AHouseData[HouseID][HouseMaxLevel]; i++)
				{
				    Counter++; // Add 1 to the counter each time an upgrade is added to the upgradelist
				    UpgradePrice = ((AHouseData[HouseID][HousePrice] * Counter) / 100) * HouseUpgradePercent;
				    // Add the upgrade-info in green if the player can afford it, and in red if he cannot afford it
					if (APlayerData[playerid][PlayerMoney] >= UpgradePrice)
						format(UpgradeList, 2000, "%s{00FF00}%s (level %i)\t\t$%i\n", UpgradeList, AHouseInteriors[i][InteriorName], i, UpgradePrice);
					else
						format(UpgradeList, 2000, "%s{FF0000}%s (level %i)\t\t$%i\n", UpgradeList, AHouseInteriors[i][InteriorName], i, UpgradePrice);
				}

		        // Show another dialog to let the player select which upgrade he wants for his house
				ShowPlayerDialog(playerid, DialogUpgradeHouse, DIALOG_STYLE_LIST, TXT_DialogSelectHouseUpgrade, UpgradeList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, TXT_HouseReachedMaxLevel);
	    }
		case 2: // Buy house-car
		{
		    // Find a free carslot
		    CarSlot = House_GetFreeCarSlot(HouseID);
		    // Check if the carslot is valid
		    if (CarSlot != -1)
		    {
			    // Let the player choose a vehicle-class
				format(VehicleClassList, 1000, "%s{00FF00}%s{FFFFFF}\n", VehicleClassList, "Bikes");
				format(VehicleClassList, 1000, "%s{40FF00}%s{FFFFFF}\n", VehicleClassList, "Boats");
				format(VehicleClassList, 1000, "%s{80FF00}%s{FFFFFF}\n", VehicleClassList, "Convertibles");
				format(VehicleClassList, 1000, "%s{B0FF00}%s{FFFFFF}\n", VehicleClassList, "Helicopters");
				format(VehicleClassList, 1000, "%s{FFFF00}%s{FFFFFF}\n", VehicleClassList, "Industrial vehicles");
				format(VehicleClassList, 1000, "%s{B0FF40}%s{FFFFFF}\n", VehicleClassList, "Low-riders");
				format(VehicleClassList, 1000, "%s{80FF80}%s{FFFFFF}\n", VehicleClassList, "Off-Road vehicles");
				format(VehicleClassList, 1000, "%s{40FFB0}%s{FFFFFF}\n", VehicleClassList, "Planes");
				format(VehicleClassList, 1000, "%s{00FFFF}%s{FFFFFF}\n", VehicleClassList, "Public Service vehicles");
				format(VehicleClassList, 1000, "%s{00B0FF}%s{FFFFFF}\n", VehicleClassList, "RC vehicles");
				format(VehicleClassList, 1000, "%s{0080FF}%s{FFFFFF}\n", VehicleClassList, "Saloon vehicles");
				format(VehicleClassList, 1000, "%s{0040FF}%s{FFFFFF}\n", VehicleClassList, "Sport vehicles");
				format(VehicleClassList, 1000, "%s{0000FF}%s{FFFFFF}\n", VehicleClassList, "Station wagons");
				format(VehicleClassList, 1000, "%s{4000FF}%s{FFFFFF}\n", VehicleClassList, "Trailers");
				format(VehicleClassList, 1000, "%s{8000FF}%s{FFFFFF}\n", VehicleClassList, "Unique vehicles");
				// Ask which vehicle class the player wants to see to buy a vehicle
				ShowPlayerDialog(playerid, DialogBuyCarClass, DIALOG_STYLE_LIST, TXT_DialogBuyCarSelectClass, VehicleClassList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
		    }
		    else
		        SendClientMessage(playerid, 0xFFFFFFFF, TXT_HouseHasMaxVehicles);
		}
		case 3: // Buy house-car insurance
		{
		    new MsgInsurance[128];
		    // Check if this house doesn't have insurance yet
		    if (AHouseData[HouseID][Insurance] == 0)
		    {
		        // Check if the player can afford the insurance
		        if (APlayerData[playerid][PlayerMoney] >= (AHouseData[HouseID][HousePrice] / 10))
		        {
				    // Construct the message for the dialog, this includes the price for the insurance
				    format(MsgInsurance, 128, TXT_DialogBuyInsurance, AHouseData[HouseID][HousePrice] / 10);
					// Ask the player if the wants to buy an insurance for this house's vehicles
					ShowPlayerDialog(playerid, DialogBuyInsurance, DIALOG_STYLE_MSGBOX, TXT_DialogTitleBuyInsurance, MsgInsurance, TXT_DialogButtonYes, TXT_DialogButtonNo);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, TXT_CannotAffordInsurance);
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, TXT_HouseAlreadyHasInsurance);
		}
		case 4: // Sell house-car
		{
		    new BuyableCarIndex, bool:HouseHasCars = false;

			// Check if the house has any cars assigned to it
			for (CarSlot = 0; CarSlot < 5; CarSlot++)
			    if (AHouseData[HouseID][VehicleIDs][CarSlot] != 0)
			        HouseHasCars = true;

			// Check if the house has any cars assigned to it
			if (HouseHasCars == true)
			{
				// Add all vehicles to the list
				for (CarSlot = 0; CarSlot < 5; CarSlot++)
				{
					if (AHouseData[HouseID][VehicleIDs][CarSlot] != 0)
					{
					    // Get the index where the first vehicle is found in the ABuyableVehicles array
					    BuyableCarIndex = VehicleBuyable_GetIndex(GetVehicleModel(AHouseData[HouseID][VehicleIDs][CarSlot]));
					    // Add the name of the vehicle to the list
					    format(VehicleList, 200, "%s{00FF00}%s: $%i{FFFFFF}\n", VehicleList, ABuyableVehicles[BuyableCarIndex][CarName], ABuyableVehicles[BuyableCarIndex][Price] / 2);
					}
					else
						format(VehicleList, 500, TXT_EmptyCarSlot, VehicleList);
				}

				// Ask which vehicle class the player wants to see to buy a vehicle
				ShowPlayerDialog(playerid, DialogSellCar, DIALOG_STYLE_LIST, TXT_SelectVehicleToSell, VehicleList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NoHouseVehicles);
		}
		case 5: // Sell house
		{
		    // Setup local variables
		    new bool:HouseHasCars = false;

			// Check if the house has any cars assigned to it
			for (CarSlot = 0; CarSlot < 5; CarSlot++)
			    if (AHouseData[HouseID][VehicleIDs][CarSlot] != 0)
			        HouseHasCars = true;

			// Check if all house-cars have been sold (all slots are empty)
			if (HouseHasCars == false)
			{
			    format(Msg, 128, TXT_SureSellHouse, House_CalcSellPrice(HouseID));
				ShowPlayerDialog(playerid, DialogSellHouse, DIALOG_STYLE_MSGBOX, TXT_AreYouSure, Msg, TXT_DialogButtonYes, TXT_DialogButtonNo);
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, TXT_CannotSellHouseWithCars);
		}
	    case 6: // Exit the house
	    {
			House_Exit(playerid, HouseID);
	    }
	}

	return 1;
}

// This function processes the house-upgrade menu
Dialog_UpgradeHouse(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Get the HouseID of the house where the player is
	new HouseID = APlayerData[playerid][CurrentHouse];
	// Calculate the new house-level based on the selection in the list (the first entry is 1 level higher than the current house-level)
	new hLevel = listitem + 1 + AHouseData[HouseID][HouseLevel];
	// Calculate the price for upgrading
	new Payment = ((AHouseData[HouseID][HousePrice] * (listitem + 1)) / 100) * HouseUpgradePercent;

	// Check if the player can afford it
	if (APlayerData[playerid][PlayerMoney] >= Payment)
	{
		// Upgrade the house
		AHouseData[HouseID][HouseLevel] = hLevel;
		// Set the worldid so other players cannot see him anymore
		SetPlayerVirtualWorld(playerid, 1000 + playerid);
		// Set the player inside the new interior of the house
		SetPlayerInterior(playerid, AHouseInteriors[hLevel][InteriorID]);
		// Set the position of the player at the spawn-location of the house's interior
		SetPlayerPos(playerid, AHouseInteriors[hLevel][IntX], AHouseInteriors[hLevel][IntY], AHouseInteriors[hLevel][IntZ]);

		// Let the player pay for the upgrade
		new Msg[128];
		RewardPlayer(playerid, -Payment, 0);
		format(Msg, 128, TXT_PlayerUpgradedHouse, AHouseData[HouseID][HouseLevel], Payment);
		SendClientMessage(playerid, 0xFFFFFFFF, Msg);

		// Also update the 3DText at the entrance of the house
		House_UpdateEntrance(APlayerData[playerid][CurrentHouse]);

		// Save the player-file (and his houses)
		PlayerFile_Save(playerid);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_CannotAffordUpgrade);

	return 1;
}



// Check which house the player chose, and port him to it
Dialog_GoHome(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new HouseIndex, HouseID;

	// The listitem directly indicates the house-index
	HouseIndex = listitem;
	HouseID = APlayerData[playerid][Houses][HouseIndex];

	// Check if this is a valid house (HouseID != 0)
	if (HouseID != 0)
	{
		// Get the coordinates of the house's entrance
		SetPlayerPos(playerid, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NoHouseInSlot);

	return 1;
}

// Let the player change the name of his house
Dialog_ChangeHouseName(playerid, response, inputtext[])
{
	// Just close the dialog if the player clicked "Cancel" or if the player didn't input any text
	if ((!response) || (strlen(inputtext) == 0)) return 1;

	// Change the name of the house
	format(AHouseData[APlayerData[playerid][CurrentHouse]][HouseName], 100, inputtext);
	// Also update the 3DText at the entrance of the house
	House_UpdateEntrance(APlayerData[playerid][CurrentHouse]);
	// Let the player know that the name of his house has been changed
	SendClientMessage(playerid, 0xFFFFFFFF, TXT_ChangedHouseName);

	// Save the player-file (and his houses)
	PlayerFile_Save(playerid);

	return 1;
}

// Choose a vehicle class from which to buy a vehicle
Dialog_BuyCarClass(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new CarList[1000], DialogTitle[128];

	// Set the player's chosen vehicle-class based on the listitem he chose (add 1 as the vehicleclass starts at 1)
	APlayerData[playerid][DialogBuyVClass] = listitem + 1;

	// Add all vehicles of the same class to the list
	for (new i; i < sizeof(ABuyableVehicles); i++)
	{
		// Check if the vehicle in the list has the same class as requested
		if (ABuyableVehicles[i][VehicleClass] == APlayerData[playerid][DialogBuyVClass])
		{
			// Add the carname to the list and it's price
			format(CarList, 500, "%s%s%s ($%i)", CarList, "\n", ABuyableVehicles[i][CarName], ABuyableVehicles[i][Price]); // Add the name of the next car to the list on the next line
		}
	}

	// Check if the list is empty
	if (strlen(CarList) == 0)
	{
		// Send the player a message that all vehicles have been disabled of the chosen class (no vehicles in the array of this class)
		SendClientMessage(playerid, 0xFFFFFFFF, TXT_BuyRentCarEmptyList);
		// Exit the function (don't ask to choose a vehicle)
		return 1;
	}

	// Set a title for the dialog based on the requested vehicleclass
	switch (APlayerData[playerid][DialogBuyVClass])
	{
		case VClassBike: format(DialogTitle, 128, TXT_BuyBike);
		case VClassBoat: format(DialogTitle, 128, TXT_BuyBoat);
		case VClassConvertible: format(DialogTitle, 128, TXT_BuyConvertible);
		case VClassHelicopter: format(DialogTitle, 128, TXT_BuyHelicopter);
		case VClassIndustrial: format(DialogTitle, 128, TXT_BuyIndustrial);
		case VClassLowRider: format(DialogTitle, 128, TXT_BuyLowRider);
		case VClassOffRoad: format(DialogTitle, 128, TXT_BuyOffRoad);
		case VClassPlane: format(DialogTitle, 128, TXT_BuyPlane);
		case VClassPublic: format(DialogTitle, 128, TXT_BuyPublicService);
		case VClassRCVehicle: format(DialogTitle, 128, TXT_BuyRC);
		case VClassSaloons: format(DialogTitle, 128, TXT_BuySaloon);
		case VClassSportCar: format(DialogTitle, 128, TXT_BuySport);
		case VClassStationCar: format(DialogTitle, 128, TXT_BuyStationWagon);
		case VClassTrailer: format(DialogTitle, 128, TXT_BuyTrailer);
		case VClassUnique: format(DialogTitle, 128, TXT_BuyUnique);
	}

	// Ask which car the player wants to have by showing the dialog
	ShowPlayerDialog(playerid, DialogBuyCar, DIALOG_STYLE_LIST, DialogTitle, CarList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);

	return 1;
}

// Buy a vehicle and assign it to the house
Dialog_BuyCar(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new Counter, Msg[128], cComponents[14];

	// Get the HouseID
	new HouseID = APlayerData[playerid][CurrentHouse];

	// Loop through the entire list of buyable vehicles
	for (new i; i < sizeof(ABuyableVehicles); i++)
	{
		// Check if the vehicle in the list has the same class as requested
		if (ABuyableVehicles[i][VehicleClass] == APlayerData[playerid][DialogBuyVClass])
		{
		    // Check if this is the vehicle that the player chose
		    if (Counter == listitem)
			{
			    // Check if the player has enough money to afford buying this vehicle
			    if (APlayerData[playerid][PlayerMoney] >= (ABuyableVehicles[i][Price]))
			    {
					// Add the vehicle to the house (this sets ownership and other data that's needed)
					House_AddVehicle(HouseID, ABuyableVehicles[i][CarModel], 0, cComponents, 0.0, 0.0, 0.0, 0.0, -1, -1);

					// Let the player pay for buying the vehicle
					APlayerData[playerid][PlayerMoney] = APlayerData[playerid][PlayerMoney] - ABuyableVehicles[i][Price];
					// Let the player know he bought a vehicle
					format(Msg, 128, TXT_PlayerBoughtVehicle, ABuyableVehicles[i][CarName], ABuyableVehicles[i][Price]);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerMustUseGetcarAndPark);

					// Exit the house
//					House_Exit(playerid, HouseID);

					// Save the player-file (and his houses)
					PlayerFile_Save(playerid);
				}
				else // The player has not enough money to buy this vehicle
				    SendClientMessage(playerid, 0xFFFFFFFF, TXT_CannotAffordVehicle);

				// Stop looking for the vehicle, as it's found and given to the player already
				return 1;
			}
		    else // The player chose another vehicle from the same class, keep looking for another one
		        Counter++;
		}
	}

	return 1;
}

// Buy insurance for the house's vehicles
Dialog_BuyInsurance(playerid, response)
{
	// Just close the dialog if the player clicked "No"
	if(!response) return 1;

	// Setup local variables
	new Msg[128];

	// Get the HouseID where the player is right now
	new HouseID = APlayerData[playerid][CurrentHouse];

	// Buy an insurance for this house's vehicles (insurance costs 10% of the house's baseprice)
	AHouseData[HouseID][Insurance] = 1;
	RewardPlayer(playerid, -(AHouseData[HouseID][HousePrice] / 10), 0);

	// Let the player know he has bought a vehicle-insurance for this house
	format(Msg, 128, TXT_PlayerBoughtInsurance, AHouseData[HouseID][HousePrice] / 10);
	SendClientMessage(playerid, 0xFFFFFFFF, Msg);

	// Save the player-file (and his houses)
	PlayerFile_Save(playerid);
	// Also save the sold house, otherwise the old ownership-data is still there
	HouseFile_Save(HouseID);

	return 1;
}

// Sell the house
Dialog_SellHouse(playerid, response)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Get the HouseID where the player is right now
	new HouseID = APlayerData[playerid][CurrentHouse];

	// Set the player in the normal world again
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	// Set the position of the player at the entrance of his house
	SetPlayerPos(playerid, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]);

	// Also clear the tracking-variable to track in which house the player is
	APlayerData[playerid][CurrentHouse] = 0;

	// Clear the owner of the house
	AHouseData[HouseID][Owned] = false;
	AHouseData[HouseID][Owner] = 0;
	// Clear the house-name and house-level
	AHouseData[HouseID][HouseName] = 0;
	AHouseData[HouseID][HouseLevel] = 1;

	// Refund the player 50% of the worth of the house
	RewardPlayer(playerid, House_CalcSellPrice(HouseID), 0);
	SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerSoldHouse);

	// Clear the house-id from the player
	for (new i; i < MAX_HOUSESPERPLAYER; i++)
	{
		// If the house-slot if found where the house was added to the player
		if (APlayerData[playerid][Houses][i] == HouseID)
		{
		    // Clear the house-id
		    APlayerData[playerid][Houses][i] = 0;
		    // Stop searching
		    break;
		}
	}

	// Update the 3DText near the house's entrance to show other players that it's for sale again
	House_UpdateEntrance(HouseID);

	// Save the player-file (and his houses)
	PlayerFile_Save(playerid);
	// Also save the sold house, otherwise the old ownership-data is still there
	HouseFile_Save(HouseID);

	return 1;
}



// Sell the house
Dialog_SellCar(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new HouseID = APlayerData[playerid][CurrentHouse];
	new vid = AHouseData[HouseID][VehicleIDs][listitem];

	// Check if there is a vehicle stored in this carslot
	if (vid != 0)
	{
		new BuyableCarIndex = VehicleBuyable_GetIndex(GetVehicleModel(vid));
		new Msg[128];

		// Destroy the vehicle and remove it from the house
		DestroyVehicle(vid);
		AHouseData[HouseID][VehicleIDs][listitem] = 0;
		// Also clear the data
		AVehicleData[vid][Owned] = false;
		AVehicleData[vid][Owner] = 0;
		AVehicleData[vid][Model] = 0;
		AVehicleData[vid][PaintJob] = 0;
		for (new i; i < 14; i++)
			AVehicleData[vid][Components][i] = 0;
		AVehicleData[vid][SpawnX] = 0.0;
		AVehicleData[vid][SpawnY] = 0.0;
		AVehicleData[vid][SpawnZ] = 0.0;
		AVehicleData[vid][SpawnRot] = 0.0;

		// Refund the player with 50% of the vehicle's buying price
		APlayerData[playerid][PlayerMoney] = APlayerData[playerid][PlayerMoney] + (ABuyableVehicles[BuyableCarIndex][Price] / 2);
		// Let the player know about it
		format(Msg, 128, TXT_PlayerSoldVehicle, ABuyableVehicles[BuyableCarIndex][CarName], ABuyableVehicles[BuyableCarIndex][Price] / 2);
		SendClientMessage(playerid, 0xFFFFFFFF, Msg);

		// Save the player-file (and his houses)
		PlayerFile_Save(playerid);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NoVehicleInSlot);

	return 1;
}

// This dialog processes the selected house from which to get a vehicle using /getcar
Dialog_GetCarSelectHouse(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Get the houseid based on the chosen listitem
	new HouseID = APlayerData[playerid][Houses][listitem];

	// Check if it was a valid house
	if (HouseID != 0)
	{
		// Setup local variables
	    new BuyableCarIndex, VehicleList[500], bool:HouseHasCars = false, CarSlot;

		// Store the HouseID, otherwise the next dialog won't be able to get a car from the chosen house
		APlayerData[playerid][DialogGetCarHouseID] = HouseID;

		// Check if the house has any cars assigned to it
		for (CarSlot = 0; CarSlot < 5; CarSlot++)
			if (AHouseData[HouseID][VehicleIDs][CarSlot] != 0)
			    HouseHasCars = true;

		// Check if the house has any cars assigned to it
		if (HouseHasCars == true)
		{
			// Add all vehicles to the list
			for (CarSlot = 0; CarSlot < 5; CarSlot++)
			{
				// Check if the carslot has a vehicle in it
				if (AHouseData[HouseID][VehicleIDs][CarSlot] != 0)
				{
				    // Get the index where the first vehicle is found in the ABuyableVehicles array
				    BuyableCarIndex = VehicleBuyable_GetIndex(GetVehicleModel(AHouseData[HouseID][VehicleIDs][CarSlot]));
				    // Add the name of the vehicle to the list
				    format(VehicleList, 500, "%s{00FF00}%s\n", VehicleList, ABuyableVehicles[BuyableCarIndex][CarName]);
				}
				else
					format(VehicleList, 500, TXT_EmptyCarSlot, VehicleList);
			}

			// Ask which vehicle the player wants to teleport to his location
			ShowPlayerDialog(playerid, DialogGetCarSelectCar, DIALOG_STYLE_LIST, TXT_SelectVehicleToGet, VehicleList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
		}
		else
		    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NoHouseVehicles);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NoHouseInSlot);

	return 1;
}

// This dialog processes the chosen car and spawns it at the player's location
Dialog_GetCarSelectCar(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Get the HouseID from which to get the car
	new HouseID = APlayerData[playerid][DialogGetCarHouseID];

	// Get the vehicleid from the chosen listitem
	new vid = AHouseData[HouseID][VehicleIDs][listitem];

	// Check if it was a valid vehicleid
	if (vid != 0)
	{
		// Setup local variables
		new Float:x, Float:y, Float:z, Float:Angle;
		// Get the player's position
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, Angle);
		// Port the vehicle to the player
		SetVehiclePos(vid, x, y, z);
		// Put the player inside the vehicle and rotate the vehicle to face where the player was facing
		PutPlayerInVehicle(playerid, vid, 0);
		SetVehicleZAngle(vid, Angle);
		// Turn on the engine and lights
		new engine,lights,alarm,doors,bonnet,boot,objective;
		GetVehicleParamsEx(vid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vid, 1, 1, alarm, doors, bonnet, boot, objective);
		SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerMustUsePark);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NoVehicleInSlot);

	return 1;
}



// This dialog processes the chosen business-type and creates the business
Dialog_CreateBusSelType(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

    // Setup some local variables
	new BusType, Float:x, Float:y, Float:z, Msg[128];
	// Get the player's position
	GetPlayerPos(playerid, x, y, z);

	// Get the business-type from the option the player chose
	BusType = listitem + 1;

	// Set some default data at the index of NextFreeBusinessID (NextFreeBusinessID will point to the next free business-index)
	ABusinessData[NextFreeBusinessID][BusinessX] = x;
	ABusinessData[NextFreeBusinessID][BusinessY] = y;
	ABusinessData[NextFreeBusinessID][BusinessZ] = z;
	ABusinessData[NextFreeBusinessID][BusinessType] = BusType;
	ABusinessData[NextFreeBusinessID][BusinessLevel] = 1;
	ABusinessData[NextFreeBusinessID][Owned] = false;

	// Add the pickup and 3DText at the location of the business-entrance (where the player is standing when he creates the business)
	Business_CreateEntrance(NextFreeBusinessID);

	// Save the business
	BusinessFile_Save(NextFreeBusinessID);

	// Inform the player that he created a new house
	format(Msg, 128, "{00FF00}You've succesfully created business {FF00FF}%i{00FF00}", NextFreeBusinessID);
	SendClientMessage(playerid, 0xFFFFFFFF, Msg);

	// Select the next free business-index where no business is created yet, so next time a new business is created, this variable
	// points to this free slot
	NextFreeBusinessID++;

	return 1;
}

// This function processes the businessmenu dialog
Dialog_BusinessMenu(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new BusID, BusType, Msg[128], DialogTitle[200], UpgradePrice;

	// Get the HouseID of the house where the player is
	BusID = APlayerData[playerid][CurrentBusiness];
	BusType = ABusinessData[BusID][BusinessType];

	// Select an option based on the selection in the list
	switch(listitem)
	{
	    case 0: // Change business name
	    {
	        format(DialogTitle, 200, TXT_DialogOldBusinessName, ABusinessData[BusID][BusinessName]);
			ShowPlayerDialog(playerid, DialogBusinessNameChange, DIALOG_STYLE_INPUT, DialogTitle, TXT_DialogEnterNewBusinessName, TXT_DialogButtonSelect, TXT_DialogButtonCancel);
	    }
	    case 1: // Upgrade the business
	    {
	        // Check if it's possible to upgrade further
			if (ABusinessData[BusID][BusinessLevel] < 5)
			{
			    // Get the upgrade-price
			    UpgradePrice = ABusinessInteriors[BusType][BusPrice];
			    // Check if the player can afford the upgrade
				if (APlayerData[playerid][PlayerMoney] >= UpgradePrice)
				{
				    // Give the current earnings of the business to the player and update the LastTransaction time
					Business_PayEarnings(playerid, BusID);
					// Upgrade the business 1 level
				    ABusinessData[BusID][BusinessLevel]++;
					// Let the player pay for the upgrade
					RewardPlayer(playerid, -UpgradePrice, 0);
					// Update the 3DText near the business's entrance to show what level the business is
					Business_UpdateEntrance(BusID);
					// Let the player know about it
					format(Msg, 128, "{00FF00}You have upgraded your business to level {FFFF00}%i", ABusinessData[BusID][BusinessLevel]);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
				else
					SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot afford the upgrade");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, TXT_BusinessReachedMaxLevel);
	    }
		case 2: // Retrieve business earnings
		{
		    // Give the current earnings of the business to the player and update the LastTransaction time
			Business_PayEarnings(playerid, BusID);
		}
		case 3: // Sell business
		{
		    format(Msg, 128, TXT_SureSellBusiness, (ABusinessInteriors[BusType][BusPrice] * ABusinessData[BusID][BusinessLevel]) / 2);
			ShowPlayerDialog(playerid, DialogSellBusiness, DIALOG_STYLE_MSGBOX, TXT_AreYouSure, Msg, TXT_DialogButtonYes, TXT_DialogButtonNo);
		}
	    case 4: // Exit the business
	    {
			Business_Exit(playerid, BusID);
	    }
	}

	return 1;
}

// This function processes the /gobus dialog
Dialog_GoBusiness(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new BusIndex, BusID;

	// The listitem directly indicates the business-index
	BusIndex = listitem;
	BusID = APlayerData[playerid][Business][BusIndex];

	// Check if this is a valid business (BusID != 0)
	if (BusID != 0)
	{
		// Get the coordinates of the business's entrance
		SetPlayerPos(playerid, ABusinessData[BusID][BusinessX], ABusinessData[BusID][BusinessY], ABusinessData[BusID][BusinessZ]);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NoBusinessInSlot);

	return 1;
}

// Let the player change the name of his business
Dialog_ChangeBusinessName(playerid, response, inputtext[])
{
	// Just close the dialog if the player clicked "Cancel" or if the player didn't input any text
	if ((!response) || (strlen(inputtext) == 0)) return 1;

	// Change the name of the business
	format(ABusinessData[APlayerData[playerid][CurrentBusiness]][BusinessName], 100, inputtext);
	// Also update the 3DText at the entrance of the business
	Business_UpdateEntrance(APlayerData[playerid][CurrentBusiness]);
	// Let the player know that the name of his business has been changed
	SendClientMessage(playerid, 0xFFFFFFFF, TXT_ChangedBusinessName);

	// Save the player-file (and his houses and businesses)
	PlayerFile_Save(playerid);

	return 1;
}

// Sell the business
Dialog_SellBusiness(playerid, response)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Get the BusinessID where the player is right now and the business-type
	new BusID = APlayerData[playerid][CurrentBusiness];
	new BusType = ABusinessData[BusID][BusinessType];

	// Set the player in the normal world again
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	// Set the position of the player at the entrance of his business
	SetPlayerPos(playerid, ABusinessData[BusID][BusinessX], ABusinessData[BusID][BusinessY], ABusinessData[BusID][BusinessZ]);

	// Also clear the tracking-variable to track in which business the player is
	APlayerData[playerid][CurrentBusiness] = 0;

	// Clear the owner of the business
	ABusinessData[BusID][Owned] = false;
	ABusinessData[BusID][Owner] = 0;
	// Clear the house-name and business-level
	ABusinessData[BusID][BusinessName] = 0;
	ABusinessData[BusID][BusinessLevel] = 1;

	// Refund the player 50% of the worth of the business
	RewardPlayer(playerid, (ABusinessInteriors[BusType][BusPrice] * ABusinessData[BusID][BusinessLevel]) / 2, 0);
	SendClientMessage(playerid, 0xFFFFFFFF, TXT_PlayerSoldBusiness);

	// Clear the house-id from the player
	for (new i; i < MAX_BUSINESSPERPLAYER; i++)
	{
		// If the business-slot if found where the business was added to the player
		if (APlayerData[playerid][Business][i] == BusID)
		{
		    // Clear the business-id
		    APlayerData[playerid][Business][i] = 0;
		    // Stop searching
		    break;
		}
	}

	// Update the 3DText near the business's entrance to show other players that it's for sale again
	Business_UpdateEntrance(BusID);

	// Save the player-file (and his houses and businesses)
	PlayerFile_Save(playerid);
	// Also save the sold business, otherwise the old ownership-data is still there
	BusinessFile_Save(BusID);

	return 1;
}

// Process the commands dialog
Dialog_PlayerCommands(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response)
	{
		// Reset the FirstCommand (so the list won't start at an unexpected location in the list, but back at the start of the list)
		APlayerData[playerid][DialogFirstItem] = 0;
		return 1; // Exit the function
	}

	// Process the selected listitem
	switch (listitem)
	{
		case 11: // Player chooses "Next..."
		{
		    // Add 5 to the FirstCommand, so the list will start further down the array (will show the next 5 commands)
		    APlayerData[playerid][DialogFirstItem] = APlayerData[playerid][DialogFirstItem] + 5;
		    // Create a new list of commands and show the dialog
		    CommandList_Create(playerid);
		}
	}

	return 1;
}

// Process the primary car color dialog
Dialog_PrimaryCarColor(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new vid = GetPlayerVehicleID(playerid);

	// Save the primary car-color and apply the colors
	AVehicleData[vid][Color1] = listitem;
	ChangeVehicleColor(GetPlayerVehicleID(playerid), AVehicleData[vid][Color1], AVehicleData[vid][Color2]);
	// If the primary color is black, remove the paintjob
	if (listitem == 0)
		AVehicleData[vid][PaintJob] = 0;

	// Let the player pay $150 for changing the color
	RewardPlayer(playerid, -150, 0);
	SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}You've changed the color of your vehicle for $150");

	return 1;
}

// Process the secundary car color dialog
Dialog_SedundaryCarColor(playerid, response, listitem)
{
	// Just close the dialog if the player clicked "Cancel"
	if(!response) return 1;

	// Setup local variables
	new vid = GetPlayerVehicleID(playerid);

	// Save the primary car-color and apply the colors
	AVehicleData[vid][Color2] = listitem;
	ChangeVehicleColor(GetPlayerVehicleID(playerid), AVehicleData[vid][Color1], AVehicleData[vid][Color2]);

	// Let the player pay $150 for changing the color
	RewardPlayer(playerid, -150, 0);
	SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}You've changed the color of your vehicle for $150");

	return 1;
}

