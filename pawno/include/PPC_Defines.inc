//************************************************************************************************************************************
// Keep the values and assignments below this line to what they are
//************************************************************************************************************************************

// Define path to player's account-files
#define PlayerFile "ServerData/Players/%s.ini"
#define HouseFile "ServerData/Houses/House%i.ini"
#define CameraFile "ServerData/Cameras/Camera%i.ini"
#define BusinessFile "ServerData/Business/Business%i.ini"
#define LocationFile "ServerData/Missions/Locations/Location%i.ini"
#define LoadFile "ServerData/Missions/Loads/Load%i.ini"



// Define vehicles
#define VehicleFlatbed			455 // Truck: Flatbed
#define VehicleDFT30			578 // Truck: DFT-30
#define VehicleCementTruck		524 // Truck: Cementtruck
#define VehicleLineRunner		403 // Truck: LineRunner
#define VehicleTanker			514 // Truck: Tanker
#define VehicleRoadTrain		515 // Truck: RoadTrain
#define VehicleTrailerCargo		435 // Trailer: cargo
#define VehicleTrailerOre		450 // Trailer: Ore
#define VehicleTrailerFluids	584 // Trailer: Fluids

#define VehicleCoach			437 // Bus

#define VehicleShamal           519 // Plane: Shamal
#define VehicleNevada           553 // Plane: Nevada
#define VehicleMaverick         487 // Helicopter: Maverick

#define VehiclePoliceLSPD       596 // Police Car Los Santos Police Department
#define VehiclePoliceSFPD       597 // Police Car San Fierro Police Department
#define VehiclePoliceLVPD       598 // Police Car Las Venturas Police Department
#define VehicleHPV1000          523 // Police motorcycle
#define VehiclePoliceRanger     599 // Police Ranger

#define VehicleSandKing			495 // Mafia-van: Sandking
#define VehicleMoonbeam         418 // Mafia-van: Moonbeam

#define VehicleBike             509 // Bike: Bike
#define VehicleBMX              481 // Bike: BMX
#define VehicleMountainBike     510 // Bike: Mountain Bike
#define VehicleFaggio           462 // Bike: Faggio
#define VehiclePizzaBoy         448 // Bike: Pizzaboy
#define VehicleBF400            581 // Bike: BF-400
#define VehicleNRG500           522 // Bike: NRG-500
#define VehiclePCJ600           461 // Bike: PCJ-600
#define VehicleFCR900           521 // Bike: FCR-900
#define VehicleFreeway          463 // Bike: Freeway
#define VehicleWayfarer         586 // Bike: Wayfarer
#define VehicleSanchez          468 // Bike: Sanchez
#define VehicleQuad             471 // Bike: Quad

#define VehicleRhino            432 // Tank: Rhino
#define VehiclePatriot          470 // Jeep: Patriot

#define VehicleTowTruck         525 // Towtruck
#define VehicleBurrito          482 // Van: Burrito
#define VehicleFaggio           462 // Bike: Faggio



// Define player-class AND vehicle statements to use for missions (PCV = PlayerClass and Vehicle)
#define PCV_TruckerOreTrailer			1
#define PCV_TruckerFluidsTrailer     	2
#define PCV_TruckerCargoTrailer      	3
#define PCV_TruckerCementTruck       	4
#define PCV_TruckerNoTrailer         	5
#define PCV_PilotPlane               	6
#define PCV_PilotHelicopter          	7
#define PCV_MafiaVan                 	8



// Define classes
#define ClassTruckDriver 1
#define ClassBusDriver 2
#define ClassPilot 3
#define ClassPolice 4
#define ClassMafia 5
#define ClassCourier 6
#define ClassAssistance 7



// Defines for truckers
#define Trucker_TimeToFailMission 60
// Defines for busdrivers
#define BusDriver_TimeToFailMission 60
// Defines for mafia
#define Mafia_TimeToFailMission 60
// Defines for all classes
#define Job_TimeToFailMission   60



// Define class-colors
#define ColorClassTruckDriver		0xFF8000FF
#define ColorClassBusDriver			0x80FFFFFF
#define ColorClassPilot             0x00FF80FF
#define ColorClassPolice			0x0000FFFF
#define ColorClassMafia				0x8000FFFF
#define ColorClassCourier           0x0080FFFF
#define ColorClassAssistance        0x80FF00FF



// Define Dialogs
#define DialogRegister      		1
#define DialogLogin         		2
#define DialogStats                 3
#define DialogStatsOtherPlayer      4

#define DialogRescue                11
#define DialogBuyLicenses           12

#define DialogTruckerJobMethod      21
#define DialogTruckerSelectLoad     22
#define DialogTruckerStartLoc       23
#define DialogTruckerEndLoc         24

#define DialogBusJobMethod          31
#define DialogBusSelectRoute        32

#define DialogCourierSelectQuant    41

#define DialogBike                  94

#define DialogCar                   101
#define DialogPlane                 102
#define DialogTrailer               103
#define DialogRentCarClass       	104
#define DialogRentCar	        	105

#define DialogWeather               201
#define DialogCarOption             202

#define DialogSelectConvoy          401
#define DialogConvoyMembers         402

#define DialogPlayerCommands        501
#define DialogPrimaryCarColor       502
#define DialogSedundaryCarColor     503

#define DialogHouseMenu             601
#define DialogUpgradeHouse          602
#define DialogGoHome                603
#define DialogHouseNameChange       604
#define DialogSellHouse             605
#define DialogBuyCarClass           606
#define DialogBuyCar                607
#define DialogSellCar               608
#define DialogBuyInsurance          609
#define DialogGetCarSelectHouse     610
#define DialogGetCarSelectCar       611

#define DialogCreateBusSelType      701
#define DialogBusinessMenu          702
#define DialogGoBusiness            703
#define DialogBusinessNameChange    704
#define DialogSellBusiness          705

#define DialogNoResponse            25000



// Define the maximum amount of convoys at the same time
#define MAX_CONVOYS					5
#define CONVOY_MAX_MEMBERS          10
#define CONVOY_EMPTY                0
#define CONVOY_OPEN                 1
#define CONVOY_FULL         	    2
#define CONVOY_CLOSED               3



// Define messagecolors
#define ColorRed 0xFF0000FF
#define ColorGreen 0x00FF00FF
#define ColorBlue 0x0000FFFF

// Define Virtual Worlds
#define WORLD_JAIL 10254

// Define options for admins
#define AutoKickAfterWarn           1 // Define if the player gets kicked after a certain amount of warnings
#define AutoKickWarnings            3 // Define the amount of warnings before a player is kicked automatically



// Define spectate modes
#define ADMIN_SPEC_TYPE_NONE 0
#define ADMIN_SPEC_TYPE_PLAYER 1
#define ADMIN_SPEC_TYPE_VEHICLE 2



// These variables are only used during the GameModeInit, they are used for debugging purposes
// A variable to hold the ID of every vehicle (used to record the last ID of a vehicle, for debugging)
new LastVehicleID;
// A variable to hold the ID of every object (used to record the last ID of an object, for debugging)
new LastObjectID;
// A variable to hold the total amount of houses that are loaded
new TotalHouses;
// A variable that holds the last speedcam-id
new TotalCameras;
// A variable to hold the last BusinessID that was loaded (let it point to the first business-index of the ABusiness array first, business 0 is ignored)
new NextFreeBusinessID = 1;



// This variable holds the number of the last TimedMessage that was sent to all players
new LastTimedMessage;
// This array holds all timed messages that will be sent every few minutes
new ATimedMessages[][128] =
{
	{TXT_TimedRefuel},
	{TXT_TimedConvoy},
	{TXT_TimedGohome},
	{TXT_TimedRentCar},
	{TXT_TimedLicense},
	{TXT_TimedSpeedTraps},
	{TXT_TimedGoBusiness}
//	{"{808080}Message"}
//	{"{808080}Message"}
//	{"{808080}Message"}
//	{"{808080}Message"}
//	{"{808080}Message"}
//	{"{808080}Message"}
};



// Holds the admin-levelnames
new AdminLevelName[6][24] =
{
	{"Player"}, // Admin-level 0
	{"Moderator"}, // Admin-level 1
	{"Helper-admin"}, // Admin-level 2
	{"Admin"}, // Admin-level 3
	{"Head-admin"}, // Admin-level 4
	{"Owner-admin"} // Admin-level 5
};



// Holds the reference to the pickup that can reward you with a trucker/busdriver license
new Pickup_License;



// Setup a custom type that holds the data of pickups
enum TPickupData
{
	Float:pux,
	Float:puy,
	Float:puz,
	PickupID
}
// Holds the data for pickups for refuelling (maximum 50 refuel-pickups)
new ARefuelPickups[50][TPickupData];
// Holds the data for pickups for 3 cardealers
new ACarDealerPickups[3][TPickupData];



// Setup a custom type that holds all data about toll-boots
enum TTollGate
{
	GateID, // Holds the object-id of the gate
	TollPrice, // Holds the price for passing the gate
	GateStatus, // Holds the status of the gate (open = 1, closed = 0)
	Float:OpenX, // Holds the coordinates when the gate is opened
	Float:OpenY, // Holds the coordinates when the gate is opened
	Float:OpenZ, // Holds the coordinates when the gate is opened
	Float:CloseX, // Holds the coordinates when the gate is closed
	Float:CloseY, // Holds the coordinates when the gate is closed
	Float:CloseZ // Holds the coordinates when the gate is closed
}
new ATollGates[MAX_TOLLGATES][TTollGate];



// Setup a custom type that holds all data about spikestrips
enum TSpikeStrip
{
	SpikeTime, // This holds the time left when the spikestrip automatically disappears
	SpikeTimer, // This holds the reference to the timer for spikestrips
	SpikeObject, // This holds the ObjectID of the spikestrip object
	Float:SpikeX, // This holds the X coordinates of the spikestrip
	Float:SpikeY, // This holds the Y coordinates of the spikestrip
	Float:SpikeZ // This holds the Z coordinates of the spikestrip
}
new ASpikeStrips[MAX_SPIKESTRIPS][TSpikeStrip];



// Setup a custom type that holds all data about a speedcamera
enum TSpeedCamera
{
	Float:CamX, // Holds the X-coordinate of the camera
	Float:CamY, // Holds the Y-coordinate of the camera
	Float:CamZ, // Holds the Z-coordinate of the camera
	Float:CamAngle, // Holds the Angle of the camera
	CamSpeed // Holds the maximum speed allowed to pass this camera without being caught
}
new ACameras[100][TSpeedCamera];



// Setup a custom type to hold all data about a convoy
enum TConvoyData
{
	Members[10], // This array holds the playerid's of all members (at index 0, the leader is stored), so a convoy can hold 1 leader and 9 members
	LoadID, // Holds the ID of the load
	Location1, // Holds the location-id of the start-location
	Location2, // Holds the location-id of the end-location
	Status, // Holds the status of the convoy (1 = open, 2 = full, 3 = closed, 0 = empty)
	ConvoyStep, // Holds the jobstep for the entire convoy
	TrailerModel, // Holds the trailer-model required by the convoy
	bool:LeaderInformedTrailers, // Is used to inform the leader ONCE if all members failed to have the same trailer
	Text:ConvoyTextLeader, // This is the textdraw for the leader of the convoy
	Text:ConvoyTextMember, // This is the textdraw for all members of the convoy
	ConvoyTimer // This convoy-timer checks everything for the whole convoy
}
// Setup an array which holds all data for every convoy
new AConvoys[MAX_CONVOYS][TConvoyData];



// Setup a custom type to hold all data about a vehicle
enum TVehicleData
{
	bool:MafiaLoad, // Holds True if the vehicle (or trailer) is carrying a mafia-wanted load
	Fuel, // Holds the amount of fuel for this vehicle
	BelongsToHouse, // Holds the HouseID to which this vehicle belongs
	bool:StaticVehicle, // Holds true if this is a static vehicle
	bool:Owned, // Holds true if the vehicle is owned by somebody
	Owner[24], // Holds the name of the owned of the vehicle
	Model, // Holds the vehicle-model of this vehicle
	PaintJob, // Holds the ID of the paintjob applied to the vehicle
	Components[14], // Holds all Component-ID's for all components on the vehicle
	Color1, // Holds the primary color for this vehicle
	Color2, // Holds the secundairy color for this vehicle
	Float:SpawnX, // Holds the X-coordinate of the parking spot for this vehicle
	Float:SpawnY, // Holds the Y-coordinate of the parking spot for this vehicle
	Float:SpawnZ, // Holds the Z-coordinate of the parking spot for this vehicle
	Float:SpawnRot // Holds the rotation of the parking spot for this vehicle
}
// Setup an array which holds all data for every vehicleid, max 2000 vehicles (server limit)
new AVehicleData[2000][TVehicleData];



// Setup a custom type that holds all data for businesses
enum TBusinessData
{
	PickupID, // Holds the pickup-id that is linked to this business
	Text3D:DoorText, // Holds the reference to the 3DText above the business's pickup
	MapIconID, // Holds the ID of the mapicon for the business

	BusinessName[100], // Holds the name of the business (this will be displayed above the pickup near the business when it's owned)
	Float:BusinessX, // Holds the X-coordinate of the pickup for the Business
	Float:BusinessY, // Holds the Y-coordinate of the pickup for the Business
	Float:BusinessZ, // Holds the Z-coordinate of the pickup for the Business
	BusinessType, // Holds the type of business (well stacked pizza, burger shot, ...), this defines which icon and interior to use
	BusinessLevel, // Holds the level of upgrades the business has
	LastTransaction, // Holds the amount of minutes when the last transaction took place (buying the business or retrieving the money by the owner)
	bool:Owned, // Holds true if the Business is owned by somebody
	Owner[24] // Holds the name of the owner of the Business
}
// Holds the data for all houses
new ABusinessData[MAX_BUSINESS][TBusinessData];
// This variable holds the business-time (this value is increased every minute and is used to calculate the amount of money a business
// has generated after the last transaction of the business)
new BusinessTransactionTime;



// Setup a custom type that holds all data for houses
enum THouseData
{
	PickupID, // Holds the pickup-id that is linked to this house
	Text3D:DoorText, // Holds the reference to the 3DText above the house's pickup
	MapIconID, // Holds the ID of the mapicon for the house

	HouseName[100], // Holds the name of the house (this will be displayed above the pickup near the house when it's owned)
	Insurance, // Holds "1" if the house has an insurance for the vehicles belonging to this house
	Float:HouseX, // Holds the X-coordinate of the pickup for the house
	Float:HouseY, // Holds the Y-coordinate of the pickup for the house
	Float:HouseZ, // Holds the Z-coordinate of the pickup for the house
	HouseLevel, // Holds the level of upgrades the house has (also defines how many vehicles can currently be added to the house)
	HouseMaxLevel, // Holds the maximum level this house can be upgraded to
	HousePrice, // Holds the price for buying the house, the same price applies when upgrading a house per level
	bool:Owned, // Holds true if the house is owned by somebody
	Owner[24], // Holds the name of the owner of the house
	VehicleIDs[5] // Holds the vehicle-id's of the vehicles linked to this house
}
// Holds the data for all houses
new AHouseData[MAX_HOUSES][THouseData];



// Setup a custom type that holds all data about a house-interior (selected when entering a house, based on the house-level)
enum THouseInterior
{
	InteriorName[50], // Holds the name of the interior
	InteriorID, // Holds the interior-id
	Float:IntX, // Holds the X-coordinate of the spawn-location where you enter the house
	Float:IntY, // Holds the Y-coordinate of the spawn-location where you enter the house
	Float:IntZ // Holds the Z-coordinate of the spawn-location where you enter the house
}
// Holds the data for all interiors for houses
new AHouseInteriors[][THouseInterior] =
{
	{"Dummy", 				0, 		0.0, 		0.0, 		0.0}, // Dummy interior (Level 0), as the house-level starts at 1
	{"Small motel room", 	10, 	2262.83, 	-1137.71, 	1050.63}, // Level 1
	{"Small house", 		2, 		2467.36, 	-1698.38, 	1013.51}, // Level 2
	{"Small house 2", 		1, 		223.00, 	1289.26, 	1082.20}, // Level 3
	{"Medium house", 		10, 	2260.76, 	-1210.45, 	1049.02}, // Level 4
	{"Medium house 2",		8, 		2365.42, 	-1131.85, 	1050.88}, // Level 5
	{"Duplex house",		12, 	2324.33, 	-1144.79, 	1050.71}, // Level 6
	{"Big house", 			15, 	295.14, 	1474.47, 	1080.52}, // Level 7
	{"Big duplex house", 	3, 		235.50, 	1189.17, 	1080.34}, // Level 8
	{"Huge house", 			7, 		225.63, 	1022.48, 	1084.07}, // Level 9
	{"Mansion", 			5, 		1299.14, 	-794.77, 	1084.00} // Level 10
};



// Setup a custom type that holds all data about a business
enum TBusinessType
{
	InteriorName[50], // Holds the name of the interior
	InteriorID, // Holds the interior-id
	Float:IntX, // Holds the X-coordinate of the spawn-location where you enter the business
	Float:IntY, // Holds the Y-coordinate of the spawn-location where you enter the business
	Float:IntZ, // Holds the Z-coordinate of the spawn-location where you enter the business
	BusPrice, // Holds the price for the business
	BusEarnings, // Holds the earnings for this type of business
	IconID // Holds the icon-id which represents the business
}
// Holds the data for all interiors for businesses
new ABusinessInteriors[][TBusinessType] =
{
	{"Dummy", 				0, 		0.0, 		0.0, 		0.0,		0,			0,		0}, // Dummy business (Type 0)
	{"24/7 (Small)", 		6, 		-26.75, 	-55.75, 	1003.6,		500000,		50,		52}, // Type 1 (earnings per day: $1200)
	{"24/7 (Medium)", 		18, 	-31.0, 		-89.5, 		1003.6,		750000,		75,		52}, // Type 2 (earnings per day: $1800)
	{"Bar", 				11, 	502.25, 	-69.75, 	998.8,		350000,		35,		49}, // Type 3 (earnings per day: $840)
	{"Barber (Small)", 		2, 		411.5, 		-21.25, 	1001.8,		300000,		30,		7}, // Type 4 (earnings per day: $720)
	{"Barber (Medium)",		3, 		418.75, 	-82.5, 		1001.8,		350000,		35,		7}, // Type 5 (earnings per day: $840)
	{"Betting shop", 		3, 		833.25, 	7.0, 		1004.2,		1500000,	150,	52}, // Type 6 (earnings per day: $3600)
	{"Burger Shot", 		10, 	363.5, 		-74.5, 		1001.5,		750000,		75,		10}, // Type 7 (earnings per day: $1800)
	{"Casino (4 Dragons)", 	10, 	2017.25, 	1017.75, 	996.9,		2500000,	250,	44}, // Type 8 (earnings per day: $6000)
	{"Casino (Caligula's)", 1, 		2234.0, 	1710.75, 	1011.3,		2500000,	250,	25}, // Type 9 (earnings per day: $6000)
	{"Casino (Small)", 		12, 	1133.0, 	-9.5,	 	1000.7,		2000000,	200,	43}, // Type 10 (earnings per day: $4800)
	{"Clothing (Binco)", 	15, 	207.75, 	-109.0, 	1005.2,		850000,		85,		45}, // Type 11 (earnings per day: $2040)
	{"Clothing (Pro)", 		3, 		207.0, 		-138.75, 	1003.5,		850000,		85,		45}, // Type 12 (earnings per day: $2040)
	{"Clothing (Urban)", 	1, 		203.75, 	-48.5, 		1001.8,		850000,		85,		45}, // Type 13 (earnings per day: $2040)
	{"Clothing (Victim)", 	5, 		226.25, 	-7.5, 		1002.3,		850000,		85,		45}, // Type 14 (earnings per day: $2040)
	{"Clothing (ZIP)",		18, 	161.5, 		-92.25, 	1001.8,		850000,		85,		45}, // Type 15 (earnings per day: $2040)
	{"Cluckin' Bell",		9,		365.75, 	-10.75,  	1001.9,		750000,		75,		14}, // Type 16 (earnings per day: $1800)
	{"Disco (Small)", 		17, 	492.75,		-22.0, 		1000.7,		1000000,	100,	48}, // Type 17 (earnings per day: $2400)
	{"Disco (Large)", 		3, 		-2642.0, 	1406.5, 	906.5,		1200000,	120,	48}, // Type 18 (earnings per day: $2880)
	{"Gym (LS)", 			5, 		772.0, 		-3.0, 		1000.8,		500000,		50,		54}, // Type 19 (earnings per day: $1200)
	{"Gym (SF)", 			6, 		774.25, 	-49.0, 		1000.6,		500000,		50,		54}, // Type 20 (earnings per day: $1200)
	{"Gym (LV)", 			7, 		774.25, 	-74.0, 		1000.7,		500000,		50,		54}, // Type 21 (earnings per day: $1200)
	{"Motel", 				15, 	2216.25, 	-1150.5, 	1025.8,		1000000,	100,	37}, // Type 22 (earnings per day: $2400)
	{"RC shop", 			6, 		-2238.75, 	131.0, 		1035.5,		600000,		60,		46}, // Type 23 (earnings per day: $1440)
	{"Sex-shop", 			3, 		-100.25, 	-22.75, 	1000.8,		800000,		80,		38}, // Type 24 (earnings per day: $1920)
	{"Slaughterhouse", 		1, 		933.75, 	2151.0, 	1011.1,		500000,		50,		50}, // Type 25 (earnings per day: $1200)
	{"Stadium (Bloodbowl)", 15, 	-1394.25, 	987.5, 		1024.0,		1750000,	175,	33}, // Type 26 (earnings per day: $4200)
	{"Stadium (Kickstart)", 14, 	-1410.75, 	1591.25, 	1052.6,		1750000,	175,	33}, // Type 27 (earnings per day: $4200)
	{"Stadium (8-Track)", 	7, 		-1396.0, 	-208.25, 	1051.2,		1750000,	175,	33}, // Type 28 (earnings per day: $4200)
	{"Stadium (Dirt Bike)", 4, 		-1425.0, 	-664.5, 	1059.9,		1750000,	175,	33}, // Type 29 (earnings per day: $4200)
	{"Stripclub (Small)", 	3, 		1212.75, 	-30.0, 		1001.0,		750000,		75,		48}, // Type 30 (earnings per day: $1800)
	{"Stripclub (Large)", 	2, 		1204.75, 	-12.5, 		1001.0,		900000,		90,		48}, // Type 31 (earnings per day: $2160)
	{"Tattoo LS", 			16, 	-203.0, 	-24.25, 	1002.3,		500000,		50,		39}, // Type 32 (earnings per day: $1200)
	{"Well Stacked Pizza", 	5,	 	372.25, 	-131.50, 	1001.5,		650000,		65,		29} // Type 33 (earnings per day: $1560)
};



// Setup all the fields required for the player data (Speedometer TextDraw, current job, ...)
enum TPlayerData
{
	PlayerPassword[50], // Holds the password of the player's account
	PlayerLevel, // The admin-level of the player
	PlayerJailed, // Holds jail-time left for this player
	PlayerJailedTimer, // Holds the reference to the jail-timer
	PlayerFrozen, // Holds the time this player is frozen
	PlayerFrozenTimer, // Holds the reference to the frozen-timer
	Warnings, // Holds the number of warnings for this player
	Bans, // Holds the number of bans for this player
	BanTime, // Holds the time where the player is unbanned automatically (when the ban is over)
	bool:LoggedIn, // Holds true if the player has properly logged in
	bool:Muted, // Holds "true" if the player is muted

	TruckerLicense, // Holds "1" if the player has acquired his truckers-license
	BusLicense, // Holds "1" if the player has acquired his busdriver license
	PlayerMoney, // Holds the money of this player
	PlayerScore, // Holds the score of this player

	Houses[MAX_HOUSESPERPLAYER], // Holds the HouseID's of the houses that the player owns (index of the AHouseData array)
    CurrentHouse, // Holds the HouseID to track in which house the player currently is (used when accessing the housemenu)
	Business[MAX_BUSINESSPERPLAYER], // Holds the BusinessID's of the business that the player owns
	CurrentBusiness, // Holds the BusinessID to track in which business the player currently is (used when accessing the businessmenu)

	PlayerClass, //Holds the Class that the player chose (1 = truckdriver, 2 = taxidriver, ... -> see DEFINES)

	bool:PlayerEjected, // This variable is used to warn a player once when trying to drive a vehicle owned by someone else
	SpectateID, // Holds the ID of the other player which this player is spectating
	SpectateVehicle, // If the target player is inside a vehicle, store it here
	SpectateType, // Holds the type of spectating (none, player or vehicle)

	StatsTruckerJobs, // Holds the number of succesfully completed trucker-missions
	StatsConvoyJobs, // Holds the number of completed trucking-routes when in a convoy
	StatsBusDriverJobs, // Holds the number of completed busroutes
	StatsPilotJobs, // Holds the number of completed pilot-missions
	StatsMafiaJobs, // Holds the number of completed mafia-missions
	StatsMafiaStolen, // Holds the number of succesfully deliveries of stolen mafialoads
	StatsPoliceFined, // Holds the number of fined players for police
	StatsPoliceJailed, // Holds the number of jailed players for police
	StatsCourierJobs, // Holds the number of completed courier-jobs
	StatsAssistance, // Holds the number of player-vehicles that this player has repaired/refuelled
	Float:StatsMetersDriven, // Holds the total kilometers that the player has driven already

	Text:SpeedometerText, // The TextDraw of the speedometer for this player
	Text:FuelGauge, // The textdraw of the fuel-gauge for this player
	SpeedometerTimer, // Holds the reference to the speedometer timer for this player
	PlayerSpeed, // Holds the speed of the player
	PlayerCaughtSpeeding, // This holds a value to prevent being caught multiple times by the same speedcamera

	Timer_PoliceCanJailMe, // This holds a reference to the timer which is started when the player got warned by a police player
	Value_PoliceCanJailMe, // This holds the remaining time for the Timer_PoliceCanJailPlayer timer
	bool:PoliceCanJailMe, // This holds "true" when the player was warned by a police player but didn't stop before the timer ran out
	bool:PoliceWarnedMe, // This holds "true" is the player got caught by a police player and got at least one warning

	bool:AssistanceNeeded, // Holds "true" is the player called for assistance

	bool:JobStarted, // States that the player has started a job or not
	Text:MissionText, // Displays the mission info at the bottom of the screen
	JobID, // Mission ID of the job (in the appropriate array, based on the PlayerClass), not used by truckers
	JobStep, // Current step of the job (for trucker: 1 = going to load, 2 = delivering goods to destination)
	Passengers, // Holds the number of passengers (used for busdriver, taxi classes)
	PlayerCheckTimer, // A special timer used by certain classes (police, mafia) to check players every second if they're wanted/carrying mafialoads
	LoadingTimer, // The timer used for loading and unloading during jobs
	VehicleTimer, // The timer used to check if the player exited his vehicle or lost his trailer for more than 60 seconds
	VehicleTimerTime, // Holds the remaining seconds for the vehicletimer
	VehicleID, // Holds the ID of the vehicle that the player is driving during his job
	TrailerID, // Holds the ID of the trailer that the player has attached during his job (is 0 if no trailer attached)
	LoadID, // Holds the ID of the load
	JobLoc1, // Holds the LocationID where to pickup the load (used in trucking missions)
	JobLoc2, // Holds the LocationID where to deliver the load (used in trucking missions)
	bool:Overloaded, // Holds True if the player's vehicle is overloaded (wanted level increases by 2)
	bool:MafiaLoad, // Holds True is the player's load is wanted by the mafia
	bool:MafiaLoadHijacked, // Holds true if the mafia-player has hijacked a mafia-load
	bool:InConvoy, // Holds true if the player has joined a convoy already
	ConvoyID, // Holds the ID of the convoy where this player is a member
	CourierHouses[11], // This holds up to 10 HouseID's for use during Courier-missions
	CourierMaxStep, // Thos holds the max number of houses to deliver packages to

	DialogFirstItem, // Holds the first array-index where a split dialog must start
	DialogCarFirstCar, // Holds the first array-index where the carlist should start when the player asks to choose a car to spawn ("/car")
	DialogPlaneFirstPlane, // Holds the first array-index where the planelist should start when the player asks to choose a plane to spawn ("/plane")
	DialogTrailerFirstTrailer, // Holds the first array-index where the trailerlist should start when the player asks to choose a trailer to spawn ("/trailer")
	DialogRentVClass, // Holds the ID of the chosen vehicle class to process when renting a vehicle
	DialogRentCarIndex, // Holds the index in the ABuyableVehicles array which vehicle the player chose to rent
	DialogBuyVClass, // Holds the ID of the chose vehicle class to process when buying a vehicle
	DialogBuyCarIndex, // Holds the index in the ABuyableVehicles array which vehicle the player chose to buy

	DialogGetCarHouseID, // Holds the HouseID from which to get a vehicle when using /getcar

	RentedVehicleID // Holds the vehicle-id of the rented vehicle (if any)
}

// Create an array to hold the playerdata for every player
new APlayerData[MAX_PLAYERS][TPlayerData];



// Setup all the fields for a spawnlocation
enum TSpawnLocation
{
	Float:SpawnX,
	Float:SpawnY,
	Float:SpawnZ,
	Float:SpawnAngle
}
// Setup spawnlocations for each class (when selecting "Spawn" at class-selection, a random spawnlocation is selected)
new ASpawnLocationsTrucker[][TSpawnLocation] =
{
	{-525.0, -502.0, 26.0, 0.0},
	{-74.7, -1137.5, 4.5, 0.0},
	{1457.0, 975.5, 11.0, 0.0},
	{-2136.0, -247.5, 36.5, 270.0},
	{1766.5, -2040.7, 14.0, 270.0},
	{-546.0, 2594.0, 54.0, 270.0},
	{332.0, 900.0, 25.0, 205.0},
	{-1575.0, -2724.0, 49.0, 146.0}
};
new ASpawnLocationsBusDriver[][TSpawnLocation] =
{
	{1809.0, -1905.0, 13.6, 90.0}, // Los Santos busdepot
	{-1983.0, 110.0, 27.7, 180.0}, // San Fierro busdepot
	{1060.0, 1260.0, 11.0, 270.0} // Las Venturas busdepot
};
new ASpawnLocationsPilot[][TSpawnLocation] =
{
	{2010.0, -2345.0, 13.6, 90.0}, // Los Santos airport
	{-1211.0, -105.0, 14.2, 135.0}, // San Fierro airport
	{1630.0, 1615.0, 10.9, 90.0} // Las Venturas airport
};
new ASpawnLocationsPolice[][TSpawnLocation] =
{
	{1568.5, -1693.5, 6.0, 180.0}, // Los Santos police station
	{-1590.0, 716.25, -5.0, 270.0}, // San Fierro police station
	{2275.0, 2460.0, 10.9, 90.0} // Las Venturas police station
};
new ASpawnLocationsMafia[][TSpawnLocation] =
{
	{2822.5, 898.5, 10.8, 0.0} // Mafia hideout
};
new ASpawnLocationsCourier[][TSpawnLocation] =
{
	{798.0, -618.75, 16.4, 0.0}, // Los Santos
	{-1849.25, -135.0, 12.0, 90.0}, // San Fierro
	{1050.5, 1931.0, 10.9, 270.0} // Las Venturas
};
new ASpawnLocationsAssistance[][TSpawnLocation] =
{
	{211.25, 24.75, 2.6, 270.0}
};



// Setup an array that holds all prices for vehicle-components
new AVehicleModPrices[] =
{
	400, // ID 1000, Spoiler Pro								Certain Transfender cars
	550, // ID 1001, Spoiler Win								Certain Transfender cars
	200, // ID 1002, Spoiler Drag								Certain Transfender cars
	250, // ID 1003, Spoiler Alpha								Certain Transfender cars
	100, // ID 1004, Hood Champ Scoop							Certain Transfender cars
	150, // ID 1005, Hood Fury Scoop							Certain Transfender cars
	80, // ID 1006, Roof Roof Scoop								Certain Transfender cars
	500, // ID 1007, Sideskirt Right Sideskirt					Certain Transfender cars
	500, // ID 1008, Nitro 5 times								Most cars, Most planes and Most Helicopters
	200, // ID 1009, Nitro 2 times								Most cars, Most planes and Most Helicopters
	1000, // ID 1010, Nitro 10 times                 			Most cars, Most planes and Most Helicopters
	220, // ID 1011, Hood Race Scoop                			Certain Transfender cars
	250, // ID 1012, Hood Worx Scoop                			Certain Transfender cars
	100, // ID 1013, Lamps Round Fog                			Certain Transfender cars
	400, // ID 1014, Spoiler Champ                  			Certain Transfender cars
	500, // ID 1015, Spoiler Race                   			Certain Transfender cars
	200, // ID 1016, Spoiler Worx                   			Certain Transfender cars
	500, // ID 1017, Sideskirt Left Sideskirt       			Certain Transfender cars
	350, // ID 1018, Exhaust Upswept                			Most cars
	300, // ID 1019, Exhaust Twin                   			Most cars
	250, // ID 1020, Exhaust Large                  			Most cars
	200, // ID 1021, Exhaust Medium								Most cars
	150, // ID 1022, Exhaust Small								Most cars
	350, // ID 1023, Spoiler Fury                   			Certain Transfender cars
	50, // ID 1024, Lamps Square Fog							Certain Transfender cars
	1000, // ID 1025, Wheels Offroad							Certain Transfender cars
	480, // ID 1026, Sideskirt Right Alien Sideskirt			Sultan
	480, // ID 1027, Sideskirt Left Alien Sideskirt				Sultan
	770, // ID 1028, Exhaust Alien                      		Sultan
	680, // ID 1029, Exhaust X-Flow								Sultan
	370, // ID 1030, Sideskirt Left X-Flow Sideskirt    		Sultan
	370, // ID 1031, Sideskirt Right X-Flow Sideskirt   		Sultan
	170, // ID 1032, Roof Alien Roof Vent						Sultan
	120, // ID 1033, Roof X-Flow Roof Vent              		Sultan
	790, // ID 1034, Exhaust Alien								Elegy
	150, // ID 1035, Roof X-Flow Roof Vent						Elegy
	500, // ID 1036, SideSkirt Right Alien Sideskirt    		Elegy
	690, // ID 1037, Exhaust X-Flow								Elegy
	190, // ID 1038, Roof Alien Roof Vent						Elegy
	390, // ID 1039, SideSkirt Right X-Flow Sideskirt   		Elegy
	500, // ID 1040, SideSkirt Left Alien Sideskirt				Elegy
	390, // ID 1041, SideSkirt Right X-Flow Sideskirt   		Elegy
	1000, // ID 1042, SideSkirt Right Chrome Sideskirt			Broadway
	500, // ID 1043, Exhaust Slamin                     		Broadway
	500, // ID 1044, Exhaust Chrome								Broadway
	510, // ID 1045, Exhaust X-Flow								Flash
	710, // ID 1046, Exhaust Alien								Flash
	670, // ID 1047, SideSkirt Right Alien Sideskirt    		Flash
	530, // ID 1048, SideSkirt Right X-Flow Sideskirt			Flash
	810, // ID 1049, Spoiler Alien								Flash
	620, // ID 1050, Spoiler X-Flow                     		Flash
	670, // ID 1051, SideSkirt Left Alien Sideskirt     		Flash
	530, // ID 1052, SideSkirt Left X-Flow Sideskirt			Flash
	130, // ID 1053, Roof X-Flow								Flash
	210, // ID 1054, Roof Alien									Flash
	230, // ID 1055, Roof Alien									Stratum
	520, // ID 1056, Sideskirt Right Alien Sideskirt			Stratum
	430, // ID 1057, Sideskirt Right X-Flow Sideskirt			Stratum
	620, // ID 1058, Spoiler Alien								Stratum
	720, // ID 1059, Exhaust X-Flow								Stratum
	530, // ID 1060, Spoiler X-Flow								Stratum
	180, // ID 1061, Roof X-Flow								Stratum
	520, // ID 1062, Sideskirt Left Alien Sideskirt				Stratum
	430, // ID 1063, Sideskirt Left X-Flow Sideskirt			Stratum
	830, // ID 1064, Exhaust Alien								Stratum
	850, // ID 1065, Exhaust Alien								Jester
	750, // ID 1066, Exhaust X-Flow								Jester
	250, // ID 1067, Roof Alien									Jester
	200, // ID 1068, Roof X-Flow								Jester
	550, // ID 1069, Sideskirt Right Alien Sideskirt			Jester
	450, // ID 1070, Sideskirt Right X-Flow Sideskirt			Jester
	550, // ID 1071, Sideskirt Left Alien Sideskirt				Jester
	450, // ID 1072, Sideskirt Left X-Flow Sideskirt			Jester
	1100, // ID 1073, Wheels Shadow								Most cars
	1030, // ID 1074, Wheels Mega								Most cars
	980, // ID 1075, Wheels Rimshine							Most cars
	1560, // ID 1076, Wheels Wires								Most cars
	1620, // ID 1077, Wheels Classic							Most cars
	1200, // ID 1078, Wheels Twist								Most cars
	1030, // ID 1079, Wheels Cutter								Most cars
	900, // ID 1080, Wheels Switch								Most cars
	1230, // ID 1081, Wheels Grove								Most cars
	820, // ID 1082, Wheels Import								Most cars
	1560, // ID 1083, Wheels Dollar								Most cars
	1350, // ID 1084, Wheels Trance								Most cars
	770, // ID 1085, Wheels Atomic								Most cars
	100, // ID 1086, Stereo Stereo								Most cars
	1500, // ID 1087, Hydraulics Hydraulics						Most cars
	150, // ID 1088, Roof Alien									Uranus
	650, // ID 1089, Exhaust X-Flow								Uranus
	450, // ID 1090, Sideskirt Right Alien Sideskirt			Uranus
	100, // ID 1091, Roof X-Flow								Uranus
	750, // ID 1092, Exhaust Alien								Uranus
	350, // ID 1093, Sideskirt Right X-Flow Sideskirt			Uranus
	450, // ID 1094, Sideskirt Left Alien Sideskirt				Uranus
	350, // ID 1095, Sideskirt Right X-Flow Sideskirt			Uranus
	1000, // ID 1096, Wheels Ahab								Most cars
	620, // ID 1097, Wheels Virtual								Most cars
	1140, // ID 1098, Wheels Access								Most cars
	1000, // ID 1099, Sideskirt Left Chrome Sideskirt			Broadway
	940, // ID 1100, Bullbar Chrome Grill						Remington
	780, // ID 1101, Sideskirt Left `Chrome Flames` Sideskirt	Remington
	830, // ID 1102, Sideskirt Left `Chrome Strip` Sideskirt	Savanna
	3250, // ID 1103, Roof Convertible							Blade
	1610, // ID 1104, Exhaust Chrome							Blade
	1540, // ID 1105, Exhaust Slamin							Blade
	780, // ID 1106, Sideskirt Right `Chrome Arches`			Remington
	780, // ID 1107, Sideskirt Left `Chrome Strip` Sideskirt	Blade
	780, // ID 1108, Sideskirt Right `Chrome Strip` Sideskirt	Blade
	1610, // ID 1109, Rear Bullbars Chrome						Slamvan
	1540, // ID 1110, Rear Bullbars Slamin						Slamvan
	55, // ID 1111, Front Sign? Little Sign?					Slamvan         ???
	55, // ID 1112, Front Sign? Little Sign?					Slamvan         ???
	3340, // ID 1113, Exhaust Chrome							Slamvan
	3250, // ID 1114, Exhaust Slamin							Slamvan
	2130, // ID 1115, Front Bullbars Chrome						Slamvan
	2050, // ID 1116, Front Bullbars Slamin						Slamvan
	2040, // ID 1117, Front Bumper Chrome						Slamvan
	780, // ID 1118, Sideskirt Right `Chrome Trim` Sideskirt	Slamvan
	940, // ID 1119, Sideskirt Right `Wheelcovers` Sideskirt	Slamvan
	780, // ID 1120, Sideskirt Left `Chrome Trim` Sideskirt		Slamvan
	940, // ID 1121, Sideskirt Left `Wheelcovers` Sideskirt		Slamvan
	780, // ID 1122, Sideskirt Right `Chrome Flames` Sideskirt	Remington
	860, // ID 1123, Bullbars Bullbar Chrome Bars				Remington
	780, // ID 1124, Sideskirt Left `Chrome Arches` Sideskirt	Remington
	1120, // ID 1125, Bullbars Bullbar Chrome Lights			Remington
	3340, // ID 1126, Exhaust Chrome Exhaust					Remington
	3250, // ID 1127, Exhaust Slamin Exhaust					Remington
	3340, // ID 1128, Roof Vinyl Hardtop						Blade
	1650, // ID 1129, Exhaust Chrome							Savanna
	3380, // ID 1130, Roof Hardtop								Savanna
	3290, // ID 1131, Roof Softtop								Savanna
	1590, // ID 1132, Exhaust Slamin							Savanna
	830, // ID 1133, Sideskirt Right `Chrome Strip` Sideskirt	Savanna
	800, // ID 1134, SideSkirt Right `Chrome Strip` Sideskirt	Tornado
	1500, // ID 1135, Exhaust Slamin							Tornado
	1000, // ID 1136, Exhaust Chrome							Tornado
	800, // ID 1137, Sideskirt Left `Chrome Strip` Sideskirt	Tornado
	580, // ID 1138, Spoiler Alien								Sultan
	470, // ID 1139, Spoiler X-Flow								Sultan
	870, // ID 1140, Rear Bumper X-Flow							Sultan
	980, // ID 1141, Rear Bumper Alien							Sultan
	150, // ID 1142, Vents Left Oval Vents						Certain Transfender Cars
	150, // ID 1143, Vents Right Oval Vents						Certain Transfender Cars
	100, // ID 1144, Vents Left Square Vents					Certain Transfender Cars
	100, // ID 1145, Vents Right Square Vents					Certain Transfender Cars
	490, // ID 1146, Spoiler X-Flow								Elegy
	600, // ID 1147, Spoiler Alien								Elegy
	890, // ID 1148, Rear Bumper X-Flow							Elegy
	1000, // ID 1149, Rear Bumper Alien							Elegy
	1090, // ID 1150, Rear Bumper Alien							Flash
	840, // ID 1151, Rear Bumper X-Flow							Flash
	910, // ID 1152, Front Bumper X-Flow						Flash
	1200, // ID 1153, Front Bumper Alien						Flash
	1030, // ID 1154, Rear Bumper Alien							Stratum
	1030, // ID 1155, Front Bumper Alien						Stratum
	920, // ID 1156, Rear Bumper X-Flow							Stratum
	930, // ID 1157, Front Bumper X-Flow						Stratum
	550, // ID 1158, Spoiler X-Flow								Jester
	1050, // ID 1159, Rear Bumper Alien							Jester
	1050, // ID 1160, Front Bumper Alien						Jester
	950, // ID 1161, Rear Bumper X-Flow							Jester
	650, // ID 1162, Spoiler Alien								Jester
	450, // ID 1163, Spoiler X-Flow								Uranus
	550, // ID 1164, Spoiler Alien								Uranus
	850, // ID 1165, Front Bumper X-Flow						Uranus
	950, // ID 1166, Front Bumper Alien							Uranus
	850, // ID 1167, Rear Bumper X-Flow							Uranus
	950, // ID 1168, Rear Bumper Alien							Uranus
	970, // ID 1169, Front Bumper Alien							Sultan
	880, // ID 1170, Front Bumper X-Flow						Sultan
	990, // ID 1171, Front Bumper Alien							Elegy
	900, // ID 1172, Front Bumper X-Flow						Elegy
	950, // ID 1173, Front Bumper X-Flow						Jester
	1000, // ID 1174, Front Bumper Chrome						Broadway
	900, // ID 1175, Front Bumper Slamin						Broadway
	1000, // ID 1176, Rear Bumper Chrome						Broadway
	900, // ID 1177, Rear Bumper Slamin							Broadway
	2050, // ID 1178, Rear Bumper Slamin						Remington
	2150, // ID 1179, Front Bumper Chrome						Remington
	2130, // ID 1180, Rear Bumper Chrome						Remington
	2050, // ID 1181, Front Bumper Slamin						Blade
	2130, // ID 1182, Front Bumper Chrome						Blade
	2040, // ID 1183, Rear Bumper Slamin						Blade
	2150, // ID 1184, Rear Bumper Chrome						Blade
	2040, // ID 1185, Front Bumper Slamin						Remington
	2095, // ID 1186, Rear Bumper Slamin						Savanna
	2175, // ID 1187, Rear Bumper Chrome						Savanna
	2080, // ID 1188, Front Bumper Slamin						Savanna
	2200, // ID 1189, Front Bumper Chrome						Savanna
	1200, // ID 1190, Front Bumper Slamin						Tornado
	1040, // ID 1191, Front Bumper Chrome						Tornado
	940, // ID 1192, Rear Bumper Chrome							Tornado
	1100, // ID 1193 Rear Bumper Slamin							Tornado
};

enum TCommands
{
	CommandLevel, // Holds the admin-level required to execute this command
	CommandStructure[128], // Holds the command-structure
	CommandDescription[128] // Holds the description of the comment
}
new ACommands[][TCommands] =
{
	{0, "/admins",                                   					"Displays all online admins"},
	{0, "/assist",                                   					"Call for assistance to repair/refuel your vehicle"},
	{0, "/busmenu",                                   					"Displays the menu for controlling your business"},
	{0, "/buybus",                                   					"Buy a business (you must be in range of a business)"},
	{0, "/buyhouse",                                   					"Buy a house (you must be in range of a house"},
	{0, "/cmds",                                   						"Displays all the commands"},
	{0, "/color1",														"Changes the primary color of your vehicle"},
	{0, "/color2",														"Changes the secundary color of your vehicle"},
	{0, "/convoy",                                   					"Lets you start or join a convoy"},
	{0, "/convoycancel",                                   				"Cancels the convoy you're in"},
	{0, "/convoykick <OtherPlayerID>",									"Kicks a member from the convoy"},
	{0, "/convoyleave",                                   				"You leave the convoy"},
	{0, "/convoymembers",                                   			"Displays all convoy members"},
	{0, "/detach",                                   					"Detaches your trailer"},
	{0, "/enter",                                   					"Enter your business or house"},
	{0, "/flip",                                   						"Flips your vehicle back onto it's wheels"},
	{0, "/getcar",                                   					"Teleports a house-car to your location"},
	{0, "/givecash <OtherPlayer> <Money>",                              "Give money to another player"},
	{0, "/gobus",                                   					"Teleport to a business you own"},
	{0, "/gohome",                                   					"Teleport to a house you own"},
	{0, "/housemenu",                                   				"Displays the menu for controlling your house"},
	{0, "/kill",                                   						"Kill yourself"},
	{0, "/me <action>",													"Just a silly command to repeat your text"},
	{0, "/paint <paintjobid (0-2)>",                                   	"Apply a paintjob to a vehicle you own"},
	{0, "/park",                                   						"Park your vehicle where it's standing now"},
	{0, "/pm <otherplayerid> <message>",                        		"Send a private message to another player"},
	{0, "/reclass",                                   					"Choose another class"},
	{0, "/rentcar",                                   					"Rent a car from a cardealer"},
	{0, "/rescue",                                   					"Teleports you to a location where your class starts"},
	{0, "/say",                                   						"Say something to players that have same class as you"},
	{0, "/spike",                                   					"Creates a spikestrip (can only be used by cops)"},
	{0, "/stats",                                   					"Displays statistics about yourself"},
	{0, "/stopwork",                                   					"Ends the current job"},
	{0, "/work",														"Starts a job"},
	{1, "/bike",                                   						"Spawns a bike of your choice"},
	{1, "/car",                                   						"Spawns a car of your choice"},
	{1, "/endspec",                                   					"Stop spectating a player"},
	{1, "/engine <EngineStatus (0/1)>",                                 "Toggle engine-status on or off"},
	{1, "/freeze <OtherPlayer> <Duration> <Reason>",                    "Freeze a player for a certain time in seconds"},
	{1, "/fuel",                                   						"Refuels your vehicle for free"},
	{1, "/get <OtherPlayer>",                                   		"Teleports another player to your location"},
	{1, "/jail <PlayerToJail> <JailTime> <Reason>",                     "Jails another player for a certain time in seconds"},
	{1, "/kick <PlayerToKick> <Reason>",                                "Kick a player"},
	{1, "/mute <OtherPlayer> <Reason>",                                 "Mute a player"},
	{1, "/mutes",                                   					"Display muted players"},
	{1, "/nos",                                   						"Adds nitro to your vehicle"},
	{1, "/plane",                                   					"Spawns a plane of your choice"},
	{1, "/port <OtherPlayer>",                                   		"Teleport yourself to another player"},
	{1, "/portloc <x> <y> <z>",                                   		"Teleport yourself to the given coordinates"},
	{1, "/portvehicle <CarID>",                                   		"Teleport yourself to a vehicle"},
	{1, "/repair",                                   					"Repairs your vehicle for free"},
	{1, "/respawn <Vehicle-id>",                                   		"Forces a vehicle to respawn"},
	{1, "/asay",                                   						"Say something to other admin players"},
	{1, "/spec <OtherPlayer>",                                   		"Spectate a player"},
	{1, "/trailer",                                   					"Spawns a trailer of your choice"},
	{1, "/unmute <OtherPlayer>",                                   		"Un-mutes a player"},
	{1, "/warn <PlayerToWarn> <Reason>",                                "Warn a player, up to three times"},
	{2, "/eject <OtherPlayer>",                                   		"Ejects a player from his vehicle"},
	{2, "/wanted <PlayerID> <Stars>",                                   "Set a player's wanted level"},
	{3, "/ban <PlayerToBan> <Days> <Hours> <Reason>",                   "Ban a player for a certain time"},
	{3, "/caroption",                                   				"Changes some options for your vehicle"},
	{3, "/cleanupcars",                                   				"Removes all spawned vehicles from the map"},
	{3, "/fly",                                   						"Equips yourself with a jetpack"},
	{3, "/healall",                                   					"Heals all the players"},
	{3, "/loc",                                   						"Display your current location"},
	{3, "/plate <NumberPlate>",                                   		"Changes the plate on your vehicle"},
	{3, "/repairall",                                   				"Repair all vehicles for free"},
	{3, "/unban <PlayerToUnban>",                                   	"Unban a player"},
	{4, "/cash <amount>",                                   			"Give cash to yourself"},
	{4, "/score <amount>",                                   			"Give scorepoints to yourself"},
	{4, "/weather",                                   					"Changes the weather"},
	{5, "/clamp <vehicleid> <reason>",                                  "Delete a player-owned vehicle"},
	{5, "/createbusiness",                                   			"Create a business at your location"},
	{5, "/createcamera <max_speed>",                                   	"Create s speedcamera at your location"},
	{5, "/createhouse <price> <maxlevel (1-10)>",               		"Create a new house"},
	{5, "/delhouse",                                   					"Delete a house"},
	{5, "/delobject <ObjectID>",                                   		"Deletes an object"},
	{5, "/delvehicle <VehicleID>",                                   	"Deletes a vehicle"},
	{5, "/object <ObjectModel> <x> <y> <z> <Angle>",                    "Create an object"},
	{5, "/pickup <PickupModel> <x> <y> <z> <PickupType>",               "Create a pickup"},
	{5, "/restart",                                   					"Restarts the server in 2 minutes"},
	{5, "/saveloc <ID> <LocationName>",                                 "Saves your location to a file"},
	{5, "/setlevel <OtherPlayer> <AdminLevel>",                         "Changes a player's admin-level"},
	{5, "/vehicle <VehicleModel> <x> <y> <z> <Angle> <SpawnDelay>",     "Create a vehicle"}
};

new AVehicleColors[][10] =
{
	{"{000000}"},	{"{f5f5f5}"},	{"{2a77a1}"},	{"{840510}"},	{"{253739}"}, // Colors 0, 1, 2, 3, 4
	{"{87446f}"},	{"{d68f11}"},	{"{4c75b7}"},	{"{bdbdc5}"},	{"{5e7072}"}, // Colors 5, 6, 7, 8, 9

	{"{46597a}"},	{"{66697a}"},	{"{5e7e8d}"},	{"{58595b}"},	{"{d6dbd5}"}, // Colors 10, 11, 12, 13, 14
	{"{9ca1a4}"},	{"{34603f}"},	{"{740e1b}"},	{"{7c0a2b}"},	{"{a09d94}"}, // Colors 15, 16, 17, 18, 19

	{"{3b4e79}"},	{"{732e40}"},	{"{691e3c}"},	{"{96918d}"},	{"{515459}"}, // Colors 20, 21, 22, 23, 24
	{"{3f3e46}"},	{"{a5a9a8}"},	{"{645c5a}"},	{"{3c4969}"},	{"{969591}"}, // Colors 25, 26, 27, 28, 29

	{"{431f21}"},	{"{5f272a}"},	{"{8494ab}"},	{"{757a7d}"},	{"{646464}"}, // Colors 30, 31, 32, 33, 34
	{"{5b5853}"},	{"{252527}"},	{"{2e3a36}"},	{"{93a398}"},	{"{6d7a8a}"}, // Colors 35, 36, 37, 38, 39

	{"{28201e}"},	{"{6f6860}"},	{"{7c1c28}"},	{"{600a15}"},	{"{193828}"}, // Colors 40, 41, 42, 43, 44
	{"{5c1b1f}"},	{"{9c9872}"},	{"{7a7561}"},	{"{989586}"},	{"{acb0b1}"}, // Colors 45, 46, 47, 48, 49

	{"{848a88}"},	{"{305045}"},	{"{4e6368}"},	{"{162248}"},	{"{282f4c}"}, // Colors 50, 51, 52, 53, 54
	{"{7e6257}"},	{"{9fa4aa}"},	{"{9c8d70}"},	{"{6e1821}"},	{"{4e6881}"}, // Colors 55, 56, 57, 58, 59

	{"{9c9d98}"},	{"{907347}"},	{"{661d26}"},	{"{949c9f}"},	{"{a3a8a4}"}, // Colors 60, 61, 62, 63, 64
	{"{8f8c47}"},	{"{331a1d}"},	{"{697a8a}"},	{"{aaad8e}"},	{"{ac988f}"}, // Colors 65, 66, 67, 68, 69

	{"{86202e}"},	{"{708298}"},	{"{585953}"},	{"{9aa68e}"},	{"{601a1a}"}, // Colors 70, 71, 72, 73, 74
	{"{21212d}"},	{"{a4a097}"},	{"{ab9d83}"},	{"{78222b}"},	{"{0e326e}"}, // Colors 75, 76, 77, 78, 79

	{"{722a40}"},	{"{7a715f}"},	{"{741c28}"},	{"{1d2f31}"},	{"{4e322f}"}, // Colors 80, 81, 82, 83, 84
	{"{7d1b44}"},	{"{2f5b20}"},	{"{395a83}"},	{"{6c2837}"},	{"{a7a28f}"}, // Colors 85, 86, 87, 88, 89

	{"{b0b2b1}"},	{"{364155}"},	{"{6d6d6f}"},	{"{0f6a89}"},	{"{204b6d}"}, // Colors 90, 91, 92, 93, 94
	{"{2c3d57}"},	{"{9a9e9d}"},	{"{6d8494}"},	{"{4d5c5f}"},	{"{ac9b7f}"}, // Colors 95, 96, 97, 98, 99

	{"{416c8f}"},	{"{20253b}"},	{"{ac9277}"},	{"{124574}"},	{"{96816c}"}, // Colors 100, 101, 102, 103, 104
	{"{64686b}"},	{"{115083}"},	{"{a19984}"},	{"{385694}"},	{"{525661}"}, // Colors 105, 106, 107, 108, 109

	{"{7e6956}"},	{"{8d919a}"},	{"{596d86}"},	{"{483433}"},	{"{456250}"}, // Colors 110, 111, 112, 113, 114
	{"{730a28}"},	{"{223556}"},	{"{630d1a}"},	{"{a3adc6}"},	{"{6a5854}"}, // Colors 115, 116, 117, 118, 119

	{"{9b8a80}"},	{"{620b1c}"},	{"{5c5d5f}"},	{"{634428}"},	{"{741827}"}, // Colors 120, 121, 122, 123, 124
	{"{1c376e}"},	{"{ed6aae}"}                                                  // Colors 125, 126
};

