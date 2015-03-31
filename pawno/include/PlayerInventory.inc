// 	PlayerInventory.inc
// 	Pawn Library Include for San Andreas: Multiplayer Modification
// 	
// 	Copyright (c) João Pedro Lourenço Lopes (Zriptarusk)
// 	Dini and the Dini mark are copyright (c) DracoBlue (http://dracoblue.com)
// 	
// 	> Terms of Use
// 	By using this library along with your gamemode or filterscript, you agree to
// 	give credit to its original creator (hereby known as 'João', 'Zriptarusk').
// 	
// 	You also agree not to share it with anyone without giving credits to its original
// 	creator and DracoBlue, the creator of the Dini Engine.
// 	
// 	Feel free to change this file as you want, as long as you follow the terms.
//
//  By ignoring the Terms of Use included in this file, you are violating
//	the copyright law, giving the original author of this library the right to
//  report you to your local law enforcemant.



#if defined _PLAYER_INVENTORY_INCLUDED
	#endinput
#endif

#define _PLAYER_INVENTORY_INCLUDED
#define PLAYER_INVENTORY_VERSION "Player Inventory - Version 0.2b"
#pragma library PlayerInventory

#include <a_samp>
#include <Dini>


/* natives
native VerifyInventoryMenuRowSelected(playerid, rowid); // Place this at OnPlayerSelectedMenuRow
native InitializeInventories(); // Place this at OnGameModeInit
native RemoveItemFromPlayerInventory(playerid, itemid, quantity);
native ResetPlayerInventory(playerid); // Place this at OnPlayerDisconnect
native AddItemToPlayerInventory(playerid, itemid, quantity, itemdescription[] = "")
native ShowInventoryToPlayer(playerid); // Shows the inventory menu to the player
native DestroyPlayerInventoryMenu(playerid); // Call this on OnPlayerMenuExit
native GetItemQuantity(playerid, itemid);	// Returns -1 if the item doesn't exist!
native PlayerHasItemInInventory(playerid, itemid); // Returns 0 if he hasn't or 1 if he has
-- VERSION 0.2b
native SetPlayerItemQuantity(playerid, itemid, quantity); // Returns 0 if the item is not found, or 1 if it is found
native SavePlayerInventoryToFile(playerid); // Saves the player inventory to ..Player Inventories/player.ini
native LoadPlayerInventoryFromFile(playerid); // Loads the player inventory from ..Player Inventories/player.ini
*/

// Public Functions Forwarding
forward OnPlayerInventoryItemSelected(playerid, itemid);

enum pitemenum{
	i_itemid,
	menurowid,
	quantity,
	description[30]
};

new gPlayerInventory[MAX_PLAYERS][10][pitemenum];
new Menu:gInventoryMenu[MAX_PLAYERS];

stock InitializeInventories(){
	for(new i; i < MAX_PLAYERS; i++)
	{
		for(new j; j < 10; j++)
		{
			gPlayerInventory[i][j][i_itemid] = -1;
			gPlayerInventory[i][j][menurowid] = -1;
			gPlayerInventory[i][j][quantity] = 0;
			format(gPlayerInventory[i][j][description], 30, "- Empty -");
		}
	}
	return 1;
}

stock SavePlayerInventoryToFile(playerid){
	if(!IsPlayerConnected(playerid)) return 0;
	
	
	new __playerName[256];
	GetPlayerName(playerid, __playerName, 256);
	
	new i_path[256];
	format(i_path, 256, "Player Inventories/%s.ini", __playerName);
	
	if(!dini_Exists(i_path)) dini_Create(i_path);
	
	new inventorydinikey[256], inventoryitemline[256];
	for(new j; j < 10; j++){
		format(inventorydinikey, 256, "inventory_item_%d", j);
		format(inventoryitemline, 256, "%d;%d;%s", gPlayerInventory[playerid][j][i_itemid], gPlayerInventory[playerid][j][quantity], gPlayerInventory[playerid][j][description]);
		dini_Set(i_path, inventorydinikey, inventoryitemline);
	}
	return 1;
}

stock LoadPlayerInventoryFromFile(playerid){
	if(!IsPlayerConnected(playerid)) return 0;
	
	new __playerName[256];
	GetPlayerName(playerid, __playerName, 256);
	
	new i_path[256];
	format(i_path, 256, "Player Inventories/%s.ini", __playerName);
	
	if(!dini_Exists(i_path)) return 0;
	
	
	// Formatting the player inventory, to avoid bugs
	ResetPlayerInventory(playerid);
	new inventorydinikey[256], inventoryitemline[256];
	new tmp[256], idx;
	for(new j; j < 10; j++)
	{
		format(inventorydinikey, 256, "inventory_item_%d", j);
		inventoryitemline = dini_Get(i_path, inventorydinikey);
		
		idx = 0;
		tmp = delim_strtok(inventoryitemline, ';', idx);
		new __itemid = strval(tmp);
		
		tmp = delim_strtok(inventoryitemline, ';', idx);
		new __quantity = strval(tmp);
		
		// Setting the stuff in the array
		gPlayerInventory[playerid][j][i_itemid] = __itemid;
		gPlayerInventory[playerid][j][quantity] = __quantity;
		format(gPlayerInventory[playerid][j][description], 30, "%s", delim_strtok(inventoryitemline, ';', idx));
		
	}
	return 1;
}

stock RemoveItemFromPlayerInventory(playerid, _itemid, _quantity){
	if(!IsPlayerConnected(playerid)) return 0;
	if(_itemid == -1) return 0;
	
	// Finding the specified item
	for(new j; j < 10; j++)
	{
		if(gPlayerInventory[playerid][j][i_itemid] == _itemid)
		{
			gPlayerInventory[playerid][j][quantity] -= _quantity;
			
			// Did we completely removed it?
			if(gPlayerInventory[playerid][j][quantity] <= 0){
				gPlayerInventory[playerid][j][i_itemid] = -1;
				gPlayerInventory[playerid][j][menurowid] = -1;
				format(gPlayerInventory[playerid][j][description], 30, "- Empty -");
				gPlayerInventory[playerid][j][quantity] = 0;
			}
		}
	}
	return 0;
}

stock ResetPlayerInventory(playerid){
	for(new j; j < 10; j++){
		gPlayerInventory[playerid][j][quantity] = 0;
		gPlayerInventory[playerid][j][i_itemid] = -1;
		gPlayerInventory[playerid][j][menurowid] = -1;
		format(gPlayerInventory[playerid][j][description], 30, "- Empty -");
	}
	return 1;
}

stock AddItemToPlayerInventory(playerid, _itemid, _quantity, itemdescription[] = ""){
	if(!IsPlayerConnected(playerid)) return 0;
	if(_itemid == -1) return 0;
	if(strlen(itemdescription) >= 30) return 0;

	// Finding an opened spot
	for(new j; j < 10; j++){
		
		if(gPlayerInventory[playerid][j][i_itemid] == _itemid){
			gPlayerInventory[playerid][j][quantity] += _quantity;
			return 1;
		}
		
		if(gPlayerInventory[playerid][j][i_itemid] == -1){
			gPlayerInventory[playerid][j][i_itemid] = _itemid;
			gPlayerInventory[playerid][j][quantity] = _quantity;
			format(gPlayerInventory[playerid][j][description], 30, "%s", itemdescription);
			return 1;
		}
	}
	return 0;
}



stock DestroyPlayerInventoryMenu(playerid){
	DestroyMenu(gInventoryMenu[playerid]);
	TogglePlayerControllable(playerid, 1);	
	return 1;
}

stock ShowInventoryToPlayer(playerid){
	if(!IsPlayerConnected(playerid)) return 0;
	
	gInventoryMenu[playerid] = CreateMenu("Inventory", 2, 250, 100, 200, 200);
	new tmp[20];
	for(new j; j < 10; j++)
	{
		// Empty Item?
		if(gPlayerInventory[playerid][j][i_itemid] == -1){
			DisableMenuRow(gInventoryMenu[playerid], AddMenuItem(gInventoryMenu[playerid], 0, gPlayerInventory[playerid][j][description]));
			DisableMenuRow(gInventoryMenu[playerid], AddMenuItem(gInventoryMenu[playerid], 1, "    "));
			continue;
		}
		
		// Item?
		gPlayerInventory[playerid][j][menurowid] = AddMenuItem(gInventoryMenu[playerid], 0, gPlayerInventory[playerid][j][description]);
		format(tmp, 5, "x%d", gPlayerInventory[playerid][j][quantity]);
		AddMenuItem(gInventoryMenu[playerid], 1, tmp);
	}
	
	TogglePlayerControllable(playerid, 0);	
	ShowMenuForPlayer(gInventoryMenu[playerid], playerid);
	return 1;
}

stock GetItemQuantity(playerid, _itemid){
	for(new j; j < 10; j++)
	{
		if(gPlayerInventory[playerid][j][i_itemid] == _itemid)
			return gPlayerInventory[playerid][j][quantity];
		
	}
	return -1;
}

stock PlayerHasItemInInventory(playerid, _itemid){
	for(new j; j < 10; j++)
	{
		if(gPlayerInventory[playerid][j][i_itemid] == _itemid) return 1;
	}
	return 0;
}

stock SetPlayerItemQuantity(playerid, _itemid, _quantity) {
	for(new j; j < 10; j++){
		if(gPlayerInventory[playerid][j][i_itemid] == _itemid) {
			gPlayerInventory[playerid][j][quantity] = _quantity;
			return 1;
		}
	}
	return 0;
}

stock VerifyInventoryMenuRowSelected(playerid, rowid){
	for(new j; j < 10; j++)
	{
		if(gPlayerInventory[playerid][j][menurowid] == rowid){
			OnPlayerInventoryItemSelected(playerid, gPlayerInventory[playerid][j][i_itemid]);
			TogglePlayerControllable(playerid, 1);
			DestroyPlayerInventoryMenu(playerid);
			return 1;
		}
	}
	return 0;
}


// --------------------------------------------------------------------------------
stock delim_strtok(str[], delim, &idx){
	new result[256];
	new ridx;
	
	while(idx < strlen(str) && str[idx] != delim){
		result[ridx] = str[idx];
		ridx++;
		idx++;
	}
	idx++;
	return result;
}

