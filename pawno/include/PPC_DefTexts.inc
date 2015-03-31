// Debug messages
#define TXT_DebugInfo "Debug information"
#define TXT_HousesFixed "Houses that have been fixed: %i"
#define TXT_LastVehicleID "Last vehicle ID: %i"
#define TXT_LastObjectID "Last object ID: %i"
#define TXT_TotalHouses "Loaded %i houses"
#define TXT_TotalBusiness "Loaded %i businesses"
#define TXT_TotalSpeedCameras "Loaded %i speed-camera's"

// Define the message that's sent to all players when a player joins the server
#define TXT_PlayerJoinedServer "{0000FF}Player '{FFFF00}%s{0000FF}' (id: {FFFF00}%i{0000FF}) has joined the server"
#define TXT_PlayerLeftServer "{0000FF}Player '{FFFF00}%s{0000FF}' (id: {FFFF00}%i{0000FF}) has left the server"

// Banned texts (also kick messages)
#define TXT_StillBanned "{FF0000}You're still banned" // Define the text that the player sees when he's still banned when trying to login
#define TXT_BannedDuration "{FF0000}Remaining: Days: %i, Hours: %i, Minutes: %i, Seconds: %i" // Define the remaining ban-time text
#define TXT_KickSpeedHack "{FF0000}You've been kicked for using speed-hack and/or air braking"
#define TXT_KickJetPackHack "{FF0000}You've been kicked for using jetpack-hack"
#define TXT_KickHealthHack "{FF0000}You've been kicked for using health-hack"

// Dialog buttons
#define TXT_DialogButtonCancel "Cancel" // Define the text on the "Cancel"-button for dialogs
#define TXT_DialogButtonBuy "Buy" // Define the text on the "Buy"-button for dialogs
#define TXT_DialogButtonSpawn "Spawn"
#define TXT_DialogButtonSelect "Select"
#define TXT_DialogButtonYes "Yes"
#define TXT_DialogButtonNo "No"

// Dialog entries
#define TXT_DialogEntryNext "Next..."

// The register dialog
#define TXT_DialogRegisterTitle "Welcome" // Define the title-message on top of the register-dialog
#define TXT_DialogRegisterMsg "Please register by entering your password:" // Define the actual message in the register-dialog
#define TXT_DialogRegisterButton1 "Register" // Define the text on the "register" button for the register-dialog
#define TXT_AccountRegistered "{00FF00}You succesfully registered your account"
#define TXT_RegisterEnterValidPassword "Please enter a valid password to register:"
#define TXT_PlayerMustRegister "{FF0000}You must register in order to play, you've been kicked out!"

// The login dialog
#define TXT_DialogLoginTitle "Welcome" // Define the title-message on top of the login-dialog
#define TXT_DialogLoginMsg "Please login by entering your password:" // Define the actual message in the login-dialog
#define TXT_DialogLoginButton1 "Login" // Define the text on the "login" button for the login-dialog
#define TXT_LoggedIn "{00FF00}You logged in, welcome back"
#define TXT_WrongPassword "{FF0000}You've entered the wrong password, you've been kicked"
#define TXT_LoginEnterValidPassword "Please login by entering your password:"
#define TXT_PlayerMustLogin "{FF0000}You must login in order to play, you've been kicked out!"
#define TXT_FailedLoginProperly "{FF0000}You failed to login properly, you're kicked"

// The license dialog
#define TXT_DialogLicenseTitle "Select license:" // Define the title-message on top of the licenses-dialog
#define TXT_DialogLicenseList "Trucker's license ($50.000, 100 points)\r\nBusdriver license ($25.000, 50 points)" // Define the licenses and their price
#define TXT_PickupText "Buy licenses" // Defines the text that's shown above the pickup for buying licenses
#define TXT_TruckerLicenseBought "{00FF00}You have acquired your trucker's license"
#define TXT_TruckerLicenseNotEnoughMoney "{FF0000}You need $50.000 and 100 score-points to buy a trucker's license"
#define TXT_TruckerLicenseOwned "{FF0000}You already bought the license"
#define TXT_TruckerLicenseWrongClass "{FF0000}You must be a trucker to buy a trucker's license"
#define TXT_BusLicenseBought "{00FF00}You have acquired your busdriver's license"
#define TXT_BusLicenseNotEnoughMoney "{FF0000}You need $25.000 and 50 score-points to buy a busdriver's license"
#define TXT_BusLicenseOwned "{FF0000}You already bought the license"
#define TXT_BusLicenseWrongClass "{FF0000}You must be a busdriver to buy a busdriver's license"



// Dialog related for /car, /plane, ...
#define TXT_DialogCarTitle "Choose a car (page %i):"
#define TXT_DialogPlaneTitle "Choose a plane (page %i):"
#define TXT_DialogTrailerTitle "Choose a trailer (page %i):"
#define TXT_PlayerSpawnedVehicle "{00FF00}%s spawned vehicle-id %i (model-id = %i) at coords: x=%4.2f, y=%4.2f, z=%4.2f"
#define TXT_ChangedWeather "{00FF00}You've changed the weather")
#define TXT_DialogCommandTitle "List of commands (page %i):"

// Trucker related
#define TXT_PlayerCompletedTruckJob "{FFFFFF}Trucker {FF00FF}%s{FFFFFF} succesfully transported {0000FF}%s{FFFFFF}"
#define TXT_PlayerCompletedTruckJobInfo "from {00FF00}%s{FFFFFF} to {00FF00}%s{FFFFFF}"
#define TXT_TruckerBonusOverloaded "{00FF00}You also earned a bonus for being overloaded: $%i"
#define TXT_TruckerBonusMafiaLoad "{00FF00}You also earned a bonus for delivering a mafia-load: $%i"
#define TXT_TruckerBonusOwnVehicle "{00FF00}You also earned a bonus for using your own truck: $%i"
#define TXT_TruckerMustEnterVehicle "{FF0000}You must enter your vehicle or re-attach your trailer"
#define TXT_TruckerOverloaded "{FF0000}You have been overloaded! Avoid the police!"
#define TXT_TruckerMafiaInterested "~r~The mafia is interested in your load~w~"
#define TXT_TruckerDialogSelectLoad "Select load:"
#define TXT_TruckerDialogSelectStartLoc "Select loading point:"
#define TXT_TruckerDialogSelectEndLoc "Select unloading point:"
#define TXT_NeedVehicleToProceed "{FF0000}You need to be in your vehicle to proceed"
#define TXT_NeedTrailerToProceed "{FF0000}You need to have your trailer attached to proceed"
#define TXT_NeedOnFootToProceed "{FF0000}You need to be on foot to proceed"

// Busdriver related
#define TXT_PlayerCompletedBusLine "{FFFFFF}BusDriver {FF00FF}%s{FFFFFF} succesfully completed bus-line {0000FF}%i{FFFFFF}"
#define TXT_BusDriverMissionPassed "Mission passed" // Define the game-text that shows when the player passed a busdriver mission
#define TXT_BusDriverJobInfo "~w~Line ~y~%i~w~ (~g~%s~w~): ~b~%i~w~ on bus"
#define TXT_BusDriverBusStopInfo "~w~Line ~y~%i~w~ (~g~%s~w~): ~b~%i~w~ on bus, ~b~%i~w~ on busstop"
#define TXT_BusDriverReward "~g~You've earned $%i~w~"
#define TXT_BusDriverMustEnterBus "{FF0000}You must enter your bus"
#define TXT_SelectBusRoute "Select busroute:"
#define TXT_BusdriverAlreadyDoingJob "{FF0000}You're already doing a job"

// Mafia related
#define TXT_PlayerCompletedMafiaJob "{FFFFFF}Mafia {FF00FF}%s{FFFFFF} succesfully transported {0000FF}%s{FFFFFF}"
#define TXT_PlayerCompletedMafiaJobInfo "from {00FF00}%s{FFFFFF} to {00FF00}%s{FFFFFF}"
#define TXT_MafiaMustEnterVehicle "{FF0000}You must enter your vehicle"
#define TXT_MafiaDeliverStolenLoad "~w~Bring the ~b~stolen load~w~ to the ~r~mafia-hideout~w~"
#define TXT_MafiaDeliveredStolenLoad "{00FF00}You delivered a stolen mafia-load, you earned $5000"

// Police related
#define TXT_PoliceWarnPlayer "~r~This is the police! Stop at once!~w~"
#define TXT_PoliceFinedPlayerReward "{00FF00}You have fined %s and earned $%i"
#define TXT_PlayerGotFinedByPolice "{FF0000}You have been caught by %s and payed a fine of $%i"
#define TXT_PoliceFinedPlayer "{00FF00}Officer %s has fined %s"
#define TXT_PoliceJailedPlayerReward "{00FF00}You have jailed %s and earned $%i"
#define TXT_PlayerGotJailedByPolice "{FF0000}You have been jailed by %s for %i minutes"
#define TXT_PoliceJailedPlayer "{00FF00}Officer %s has jailed %s for %i minutes"

// Pilot related
#define TXT_PlayerCompletedPilotJob "{FFFFFF}Pilot {FF00FF}%s{FFFFFF} succesfully transported {0000FF}%s{FFFFFF}"
#define TXT_PlayerCompletedPilotJobInfo "from {00FF00}%s{FFFFFF} to {00FF00}%s{FFFFFF}"

// Courier related
#define TXT_CourierMustEnterVehicle "{FF0000}You must enter your vehicle"
#define TXT_PlayerCompletedCourierJob "{FFFFFF}Courier {FF00FF}%s{FFFFFF} succesfully delivered {0000FF}%i{FFFFFF} packages"
#define TXT_PackageDeliveredGameText "Package delivered"
#define TXT_PackageDeliveredMessage "{00FF00}Package delivered"

// Job related, for all classes
#define TXT_RewardJob "{00FF00}You finished the mission and earned $%i"
#define TXT_FailedMission "~w~You ~r~failed~w~ your mission. You lost ~y~$1000~w~ to cover expenses." // Define game-text when player fails a mission

// Class related
#define TXT_ClassTrucker "Truck driver" // Define the game-text that shows when the player is choosing classes (this one = trucker)
#define TXT_ClassBusDriver "Bus driver" // Define the game-text that shows when the player is choosing classes (this one = bus-driver)
#define TXT_ClassPilot "Pilot" // Define the game-text that shows when the player is choosing classes (this one = pilot)
#define TXT_ClassPolice "Police" // Define the game-text that shows when the player is choosing classes (this one = police)
#define TXT_ClassMafia "Mafia" // Define the game-text that shows when the player is choosing classes (this one = mafia)
#define TXT_ClassCourier "Courier" // Define the game-text that shows when the player is choosing classes (this one = courier)
#define TXT_ClassAssistance "Assistance" // Define the game-text that shows when the player is choosing classes (this one = assistance)

// No-job texts for all classes
#define Trucker_NoJobText "No job at the moment. Enter \"~y~/work~w~\" to start a job"
#define BusDriver_NoJobText "No job at the moment. Enter \"~y~/work~w~\" to start a job"
#define Pilot_NoJobText "No job at the moment. Enter \"~y~/work~w~\" to start a job"
#define Police_NoJobText "~r~'RMB'~w~ fines a player (on foot), ~r~'LCTRL'~w~ warns the player (in vehicle)"
#define Mafia_NoJobText "Hijack a ~r~marked~w~ vehicle or enter \"~y~/work~w~\" to start a job"
#define Courier_NoJobText "No job at the moment. Enter \"~y~/work~w~\" to start a job"
#define Assistance_NoJobText "~r~'RMB'~w~ repairs/refuels a vehicle (on foot), ~r~'LCTRL'~w~ fixes your own vehicle"

// Command related
#define TXT_PlayerRescued "{0000FF}You've been rescued. $200 has been deducted."

// Fuel related
#define TXT_Refuelling "~g~Refuelling..." // Define the game-text that shows when you're refuelling your vehicle
#define TXT_PickupRefuel "Honk the horn\nto refuel your vehicle"
#define TXT_RefuelledVehicle "{00FF00}You refuelled your vehicle for $%i"
#define TXT_CannotRefuelVehicle "{FF0000}You don't have enough cash to refuel your vehicle"

// Gametexts for loading/unloading
#define TXT_LoadingGoods "~r~Loading %s... ~w~Please Wait"
#define TXT_UnloadingGoods "~r~Unloading %s... ~w~Please Wait"
#define TXT_TruckerLoadingGoods "~r~Loading Your Truck... ~w~Please Wait"
#define TXT_TruckerUnloadingGoods "~r~Unloading Your Truck... ~w~Please Wait"
#define TXT_TransportingFromToPickup "~w~Transporting ~b~%s~w~ from ~r~%s~w~ to %s"
#define TXT_TransportingFromToDeliver "~w~Transporting ~b~%s~w~ from %s to ~r~%s~w~"
#define TXT_HaulingCargoFromToPickup "~w~Hauling ~b~%s~w~ from ~r~%s~w~ to %s"
#define TXT_HaulingCargoFromToDeliver "~w~Hauling ~b~%s~w~ from %s to ~r~%s~w~"
#define TXT_PickupCargoAt "{00FF00}Pickup the %s at %s"
#define TXT_DeliverCargoTo "{00FF00}Deliver the %s to %s"

// Cardealer related
#define TXT_PickupCarDealer "Use \"/rentcar\"\nto rent a car"
#define TXT_BuyRentCarEmptyList "{FF0000}This is an empty list, the administrator may have disabled all vehicles of this class"
#define TXT_RentBike "Rent a bike:"
#define TXT_RentBoat "Rent a boat:"
#define TXT_RentConvertible "Rent a convertible:"
#define TXT_RentHelicopter "Rent a helicopter:"
#define TXT_RentIndustrial "Rent an industrail vehicle:"
#define TXT_RentLowRider "Rent a low-rider:"
#define TXT_RentOffRoad "Rent an off-road vehicle:"
#define TXT_RentPlane "Rent a plane:"
#define TXT_RentPublicService "Rent a public service vehicle:"
#define TXT_RentRC "Rent a RC vehicle:"
#define TXT_RentSaloon "Rent a saloon vehicle:"
#define TXT_RentSport "Rent a sport vehicle:"
#define TXT_RentStationWagon "Rent a station wagon:"
#define TXT_RentTrailer "Rent a trailer:"
#define TXT_RentUnique "Rent a unique vehicle:"
#define TXT_AlreadyRentedVehicle "{FF0000}You already had a rented vehicle, but it has been replaced by the new one"
#define TXT_PlayerRentsVehicle "{00FF00}You have rented a {FFFF00}%s{00FF00} for ${FFFF00}%i{00FF00}"
#define TXT_RentingTooExpensive "{FF0000}You can't afford to rent this vehicle"
#define TXT_BuyBike "Buy a bike:"
#define TXT_BuyBoat "Buy a boat:"
#define TXT_BuyConvertible "Buy a convertible:"
#define TXT_BuyHelicopter "Buy a helicopter:"
#define TXT_BuyIndustrial "Buy an industrail vehicle:"
#define TXT_BuyLowRider "Buy a low-rider:"
#define TXT_BuyOffRoad "Buy an off-road vehicle:"
#define TXT_BuyPlane "Buy a plane:"
#define TXT_BuyPublicService "Buy a public service vehicle:"
#define TXT_BuyRC "Buy a RC vehicle:"
#define TXT_BuySaloon "Buy a saloon vehicle:"
#define TXT_BuySport "Buy a sport vehicle:"
#define TXT_BuyStationWagon "Buy a station wagon:"
#define TXT_BuyTrailer "Buy a trailer:"
#define TXT_BuyUnique "Buy a unique vehicle:"



// Jail related
#define TXT_JailTimer "~w~Jailed: ~r~%i~w~"

// Speedometer related
#define TXT_SpeedometerSpeed "~w~Speed: ~b~%i~w~ kph"
#define TXT_SpeedometerFuel "~w~Fuel: %s"
#define TXT_SpeedometerCannotUseVehicle "{FF0000}You cannot use this vehicle, it's owned by \"{FFFF00}%s{FF0000}\""
#define TXT_PlayerCaughtSpeeding "{FF0000}You've been caught by a speedtrap, slow down!"

// Toll-gate related
#define TXT_PlayerPaysToll "You paid $%i for the toll"

// Convoy related
#define TXT_PlayerStartsConvoy "Player {00FF00}%s{FFFFFF} wants to start a {00FF00}convoy{FFFFFF}, join him by entering \"/convoy\""
#define TXT_PlayerJoinedConvoy "Player {00FF00}%s{FFFFFF} has joined the convoy"
#define TXT_YouJoinedConvoy "{00FF00}You have joined the convoy"
#define TXT_WaitingLeaderJob "Waiting for the leader to start a job"
#define TXT_WaitingMembersToLoadCargo "Waiting for all members to load their cargo"
#define TXT_WaitingMembersToUnLoadCargo "Waiting for all members to unload their cargo"
#define TXT_ConvoyFull "{FF0000}This convoy is already full"
#define TXT_ConvoyEnRoute "This convoy is en-route to it's destination, you cannot join it"
#define TXT_LeaderCancelledConvoy "{FF0000}The leader cancelled the convoy"
#define TXT_MeetOtherConvoyMembers "{00FF00}Meet the other members of the convoy at the loading point"
#define TXT_ConvoyDistanceForLeader "{00FF00}Everybody needs to stay within 500m of you"
#define TXT_ConvoyDistanceForMember "{00FF00}Stay within 500m of the leader of the convoy"
#define TXT_MemberNeedsCargoTrailer "You need a cargo trailer"
#define TXT_MemberNeedsOreTrailer "You need an ore trailer"
#define TXT_MemberNeedsFluidsTrailer "You need a fluids trailer"
#define TXT_AllMembersSameTrailer "{00FF00}All members have the same trailer, convoy is ready to go"
#define TXT_AllMembersNotSameTrailer "{FF0000}Not all members have the same trailer, convoy cannot start yet"
#define TXT_AllMembersLoadedCargo "{00FF00}All members have loaded their cargo, convoy is ready to proceed to the unloading-point"
#define TXT_MemberKickedByDistance "{FF0000}You didn't stay close to the leader, you've been kicked from the convoy"
#define TXT_MemberFellBehind "Player {00FF00}%s{FFFFFF} fell behind and is kicked from the convoy"
#define TXT_FinishedConvoy "{00FF00}You finished the convoy and earned $%i"
#define TXT_LeaderInfoBar "Members: ~g~%i~w~, Furthest member: ~g~%s~w~, Distance: ~r~%3.1f~w~"
#define TXT_MemberInfoBar "Leader: ~r~%s~w~, distance: ~r~%3.1f~w~, members: ~r~%i~w~"
#define TXT_CannotJoinJobStarted "{FF0000}You already started a job, you cannot create or join a convoy"
#define TXT_ConvoyAllreadyJoined "{FF0000}You already joined a convoy"
#define TXT_ConvoyNeedsTruckerClass "{FF0000}You need to be a trucker to create or join a convoy"

// Timed messages
#define TXT_TimedRefuel "{808080}You want to refuel your vehicle? Park on a refuel-pickup and honk the horn"
#define TXT_TimedConvoy "{808080}You want to start a convoy? Enter \"/convoy\" to start or join one"
#define TXT_TimedGohome "{808080}You want to teleport to a house you own? Use \"/gohome\" to go home"
#define TXT_TimedRentCar "{808080}You want to rent a vehicle? Go visit Wang Cars in Doherty, San Fierro"
#define TXT_TimedLicense "{808080}You're tired of random trucker/busdriver missions? Visit the driving school in Doherty and buy a license"
#define TXT_TimedSpeedTraps "{808080}Beware of speedtraps (60kph in the city, 90kph on roads, 120kph on highways)"
#define TXT_TimedGoBusiness "{808080}You want to teleport to a business you own? Use \"/gobus\" to go to your business"

// House-related
#define TXT_DefaultHouseName "%s's house"
#define TXT_PlayerBoughtHouse "{33FF33}You've bought the house for ${FFCC33}%i"
#define TXT_PlayerOwnsMaxHouses "{FF0000}You already own the maximum amount of allowed houses per player"
#define TXT_ExitHouseReloadEnv "Waiting for the environment to load"
#define TXT_PickupHouseOwned "%s\nOwned by: %s\nHouse-level: %i\n/enter"
#define TXT_PickupHouseForSale "House available for\n$%i\nMax-level: %i\n/buyhouse"
#define TXT_DialogOldHouseName "Old house-name: %s"
#define TXT_DialogEnterNewHouseName "Give a new name to your house"
#define TXT_DialogSelectHouseUpgrade "Select upgrade:"
#define TXT_HouseReachedMaxLevel "{FF0000}Your house has reached the maximum level, you cannot upgrade it further"
#define TXT_DialogBuyCarSelectClass "Select vehicle class:"
#define TXT_HouseHasMaxVehicles "{FF0000}This house has the maximum amount of house-cars already"
#define TXT_AlreadyBoughtRecentVehicle "{FF0000}You already bought a vehicle recently, use \"/getcar\" and \"/park\" to park it before buying a new one"
#define TXT_EmptyCarSlot "%s{FFFFFF}Empty car-slot{FFFFFF}\n"
#define TXT_SelectVehicleToSell "Select vehicle to sell:"
#define TXT_SelectVehicleToGet "Select vehicle to port to your location:"
#define TXT_NoHouseVehicles "{FF0000}This house has no vehicles assigned to it"
#define TXT_SureSellHouse "Are you sure you want to sell your house for $%i?"
#define TXT_AreYouSure "Are you sure?"
#define TXT_CannotSellHouseWithCars "{FF0000}You can't sell a house which still has house-cars assigned to it"
#define TXT_PlayerUpgradedHouse "{00FF00}You've upgraded your house to level %i for $%i"
#define TXT_CannotAffordUpgrade "{FF0000}You cannot afford this upgrade"
#define TXT_NoHouseInSlot "{FF0000}You don't have a house in this house-slot"
#define TXT_ChangedHouseName "{00FF00}You've changed the name of your house"
#define TXT_PlayerBoughtVehicle "{00FF00}You have bought a {FFFF00}%s{00FF00} for ${FFFF00}%i{00FF00}"
#define TXT_PlayerMustUseGetcarAndPark "{00FF00}Now get outside and use \"{FFFF00}/getcar{00FF00}\" to spawn it, then use \"{FFFF00}/park{00FF00}\" to park it near your house"
#define TXT_PlayerMustUsePark "{00FF00}You've spawned your vehicle, now use \"{FFFF00}/park{00FF00}\" to park it near your house"
#define TXT_CannotAffordVehicle "{FF0000}You can't afford to buy this vehicle"
#define TXT_PlayerSoldHouse "{00FF00}You've sold your house"
#define TXT_PlayerSoldVehicle "{00FF00}You've sold your {FFFF00}%s{00FF00} for ${FFFF00}%i{00FF00}"
#define TXT_NoVehicleInSlot "{FF0000}No vehicle exists in this vehicle-slot"
#define TXT_DialogTitleBuyInsurance "Buy insurance?"
#define TXT_DialogBuyInsurance "Are you sure you want to buy an insurance for your house's vehicles for $%i?"
#define TXT_HouseAlreadyHasInsurance "{FF0000}This house already has an insurance for it's vehicles"
#define TXT_PlayerBoughtInsurance "{00FF00}You've bought a vehicle-insurance for all vehicles in this house for $%i"
#define TXT_CannotAffordInsurance "{FF0000}You cannot afford the vehicle-insurance"

// Business related
#define TXT_PickupBusinessOwned "%s\nOwned by: %s\nBusiness-level: %i\n/enter"
#define TXT_PickupBusinessForSale "%s\nAvailable for\n$%i\nEarnings: $%i\n/buybus"
#define TXT_DefaultBusinessName "%s's business"
#define TXT_PlayerBoughtBusiness "{33FF33}You've bought the business for ${FFCC33}%i"
#define TXT_PlayerOwnsMaxBusinesses "{FF0000}You already own the maximum amount of allowed businesses per player"
#define TXT_NoBusinessInSlot "{FF0000}You don't have a business in this business-slot"
#define TXT_DialogOldBusinessName "Old business-name: %s"
#define TXT_DialogEnterNewBusinessName "Give a new name to your business"
#define TXT_ChangedBusinessName "{00FF00}You've changed the name of your business"
#define TXT_BusinessReachedMaxLevel "{FF0000}Your business has reached the maximum level, you cannot upgrade it further"
#define TXT_SureSellBusiness "Are you sure you want to sell your business for $%i?"
#define TXT_PlayerSoldBusiness "{00FF00}You've sold your business"
