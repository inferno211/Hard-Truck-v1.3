/*

							CZECH PROPERTY SCRIPT

				Made by Vojtech "MaverickCZE" Dvorak in 2008
							All rights reserved (c)
							       Verze 1.1
							
  					For more info how to use this script
  				visit www.pawnobox.net or www.igrania.ic.cz
  				
  				            Have easy scripting :D !

*/

#if defined _CZproperty_included
	#endinput
#endif

#define _CZproperty_included
#pragma library CZproperty

#include <a_samp>

/*

						 [ NATIVE FOR PAWNO ]

native Jmeno(playerid);
native GetPlayerIDFromName(const name[]);
native PropertyMenuLoad();
native PropertyPickup();
native PlayerToPoint(Float:r, playerid, Float:x, Float:y, Float:z);
native AddProperty(Float:static_x,Float:static_y,Float:static_z, cost, payments, const property_name[], ownername[]);
native PropertyPaymentsUpdate(const message[]);
native GetPlayerPropertyIn(playerid);
native UnlockProperty(propertyid);
native GetPlayerPropertyID(playerid);
native OnPlayerSelectedPropertyMenu(playerid, row);

						 [ NATIVE FOR PAWNO ]

*/

#define PROPERTY_DEFAULT_OWNER "Mesto"   // Puvodni vlastnik vsech nemovitosti
#define MAX_PROPERTIES    50 			 // Maximalni pocet nemovitosti
#define MAX_PROPERTY_NAME 65 			 // Maximalni delka nazvu nemovitosti

new PropertyCount = 0;       			 // Aktualni pocet nemovitosti

enum PROPERTY_INFO
{
    prop_name[MAX_PROPERTY_NAME], // Jmeno nemovitosti
    prop_ownername[24],           // Jmeno vlastnika
	Float:prop_pos_x,             // Pozice nemovitosti X
	Float:prop_pos_y,             // Pozice nemovitosti Y
	Float:prop_pos_z,             // Pozice nemovitosti Z
	bool:prop_locked,             // Zamek nemovitosti
	prop_savedmoney,              // Ulozene penize v nemovitosti
	prop_payments,                // Vydelky nemovitosti
	prop_cost                     // Cena nemovitosti
}

new Property[MAX_PROPERTIES][PROPERTY_INFO]; // Definice promenne pro nemovitosti o velikosti MAX_PROPERTIES a informaci PROPERTY_INFO
new bool:PropertyMenu[MAX_PLAYERS];
new Menu:PropertyBuyMenu;                    // Definice menu

forward AddProperty(Float:static_x,Float:static_y,Float:static_z, cost, payments, const property_name[], ownername[]);
forward PlayerToPoint(Float:r, playerid, Float:x, Float:y, Float:z);
forward OnPlayerSelectedPropertyMenu(playerid, row);
forward GetPlayerPropertyIn(playerid);
forward UnlockProperty(propertyid);
forward PropertyPickup();

stock Jmeno(playerid)
{
	new p[MAX_PLAYER_NAME];
	if(IsPlayerConnected(playerid)) GetPlayerName(playerid, p, MAX_PLAYER_NAME);
	return p;
}

stock GetPlayerIDFromName(const name[])
{
	for(new p=0;p<200;p++)
	{
	if(IsPlayerConnected(p))
	{
		new jm[MAX_PLAYER_NAME];
		GetPlayerName(p, jm, MAX_PLAYER_NAME);
		if(strcmp(jm, name, true) == 0) return p;
	}
	}
	return -1;
}

public OnPlayerSelectedPropertyMenu(playerid, row)
{
	new Menu:Aktualni = GetPlayerMenu(playerid);

	if(Aktualni == PropertyBuyMenu)         // Kdyz je aktualni property menu
	{
	new property_in = GetPlayerPropertyIn(playerid);
	if(property_in != -1) 					 // Kdyz hrac je v nektere z nemovitosti
	{
  	{
		new string[17 + MAX_PROPERTY_NAME];
		format(string, 17 + MAX_PROPERTY_NAME, "[  BUSINESS  ]  %s",Property[property_in][prop_name]);
		SendClientMessage(playerid, 0xFF0000AA, string);
	}
	
	new ownerid = GetPlayerIDFromName(Property[property_in][prop_ownername]);
	
	switch(row)
	{
		case 0:
		{
		    new string[34 + MAX_PLAYER_NAME];
			format(string, 34 + MAX_PLAYER_NAME, "Vlastnikem teto nemovitosti je %s.",Property[property_in][prop_ownername]);
			SendClientMessage(playerid, 0xFFFFFFAA, string);
		}
		case 1:
		{
		    if(ownerid != playerid) // Kdyz neni hrac playerid vlastnikem budovy
			{
				if(GetPlayerMoney(playerid) >= Property[property_in][prop_cost])
				{
				    if(Property[property_in][prop_locked] == false) // Kdyz neni nemovitost zamcena
					{
					   	new string[150];
					   	format(string, 150, "Odkoupil jsi nemovitost %s od vlastnika: %s.",Property[property_in][prop_name],Property[property_in][prop_ownername]);
					    SendClientMessage(playerid, 0xFFFFFFAA, string);

				        Property[property_in][prop_savedmoney] = 0; // Vyresetovani ulozenych penez

				    	if(IsPlayerConnected(ownerid)) GivePlayerMoney(ownerid, Property[property_in][prop_cost]);
				    	GivePlayerMoney(playerid, 0 - Property[property_in][prop_cost]);
              
              			if(IsPlayerConnected(ownerid))
              			{
				    	   	format(string, 150, "Hrac %s(%d) ti odkoupil nemovitost %s.",Jmeno(playerid), playerid, Property[property_in][prop_name]);
				    	   	SendClientMessage(ownerid, 0xFF0000AA, string);

					       	format(string, 150, "Nemovitost byla odkoupena za %d$ a nevyzvednute penize byly zabaveny statem.",Property[property_in][prop_cost]);
					       	SendClientMessage(ownerid, 0xFFFFFFAA, string);
					    }
                 		format(Property[property_in][prop_ownername],MAX_PLAYER_NAME,Jmeno(playerid)); // Definovani noveho vlastnika
	  				} else {
		  				SendClientMessage(playerid, 0xFFFFFFAA, "Mafie ti non-verbalne vysvetlila, ze tato nemovitost neni na prodej.");
		                ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.000000, 0, 1, 1, 4, -1);
  					}
				} else {
				    new string[150];
	               	format(string, 150, "Nemas dostatek penez pro koupeni %s.Je zapotrebi nejmene %d$.",Property[property_in][prop_name],Property[property_in][prop_cost]);
				   	SendClientMessage(playerid, 0xFFFFFFAA, string);
				}
			}
			else SendClientMessage(playerid, 0xFFFFFFAA, "Toto je tvoje nemovitost.");
		}
		case 2:
		{
			if(ownerid == playerid)
			{
				new gener = random(1000),string[250];

				gener = floatround(Property[property_in][prop_cost] - (Property[property_in][prop_cost]/1.2) + gener);
				format(string, 250, "Prodal jsi nemovitost %s. Bylo ti vraceno %d$. (Mene nez nakupni cena, inflace je hajzl :D )",Property[property_in][prop_name],gener);
	    		SendClientMessage(playerid, 0xFFFFFFAA, string);

				GivePlayerMoney(playerid, gener);
				format(Property[property_in][prop_ownername],64,PROPERTY_DEFAULT_OWNER); // Ulozeni puvodniho vlastnika
		    } else {
		        new string[150];
           		format(string, 150, "Nejsi vlastnikem nemovitosti %s.",Property[property_in][prop_name]);
	    		SendClientMessage(playerid, 0xFFFFFFAA, string);
			}
		}
		case 3:
		{
		    new string[150];
		    format(string, 150, "Nemovitost %s za minuly mesic vydelala %d$.",Property[property_in][prop_name],Property[property_in][prop_payments]);
		    SendClientMessage(playerid, 0xFFFFFFAA, string);
		}
		case 4:
		{
		    if(playerid == ownerid)
			{
			    if(Property[property_in][prop_savedmoney] > 0)
				{
				    new string[256];
			    	new vyplaty = floatround(random(Property[property_in][prop_savedmoney]/7 + 100));
			    	format(string, 256, "Nemovitost %s ma v kase %d$, bylo strzeno %d$ na udrzbu a vyplaty zamestnancu. Penize ti byly vyplaceny.",Property[property_in][prop_name],Property[property_in][prop_savedmoney] - vyplaty, vyplaty);
			   		SendClientMessage(playerid, 0xFFFFFFAA, string);
		    		vyplaty = Property[property_in][prop_savedmoney] - vyplaty;
		    		GivePlayerMoney(playerid, vyplaty);
		    		Property[property_in][prop_savedmoney] = 0;
		    	} else SendClientMessage(playerid, 0xFFFFFFAA, "Neni co vybirat, nemovitost od tve posledni navstevy jeste nic nevydelala.");
		    } else {
		        new string[150];
	    		format(string, 150, "Nejsi vlastnikem nemovitosti %s.",Property[property_in][prop_name]);
	    		SendClientMessage(playerid, 0xFFFFFFAA, string);
           	}
		}
		case 5:
		{
		    if(playerid == ownerid)
			{
				if(GetPlayerMoney(playerid) > Property[property_in][prop_cost]/4) // 1/4 ceny nemovitosti za lock
				{
					if(Property[property_in][prop_locked] == false)
					{
					    new string[256];
				    	format(string, 256, "Nemovitost %s je nyni pod ochranou mafie, po dobu pul hodiny. Zaplatil jsi %d$.",Property[property_in][prop_name],floatround(Property[property_in][prop_cost] / 4));
				   		SendClientMessage(playerid, 0xFFFFFFAA, string);
				   		Property[property_in][prop_locked] = true;
				   		SetTimerEx("PropertyUnlock", 60000*30, false, "i",property_in);
				   		GivePlayerMoney(playerid, floatround(0 - Property[property_in][prop_cost] / 4));
					} else SendClientMessage(playerid, 0xFFFFFFAA, "Nemovitost uz je pod ochranou.");
		    	} else {
		    	    new string[150];
		    		format(string, 150, "Nemas na zaplaceni %d$ za mafianskou ochranu.",floatround(Property[property_in][prop_cost] / 4));
		    		SendClientMessage(playerid, 0xFFFFFFAA, string);
		    	}
		    } else {
		        new string[150];
		    	format(string, 150, "Nejsi vlastnikem nemovitosti %s.",Property[property_in][prop_name]);
		    	SendClientMessage(playerid, 0xFFFFFFAA, string);
           	}
		}
		default:
		{
		    if(playerid != ownerid)
			{
			    if(Property[property_in][prop_savedmoney] <= 0)
				{
					if(RobRandom(playerid))
					{
   						GivePlayerMoney(playerid, Property[property_in][prop_savedmoney]);
   				
   			    		new string[250];
						format(string, 250, "%s prepadl %s, odnesl si z kasy %d$.", Jmeno(playerid), Property[property_in][prop_name], Property[property_in][prop_savedmoney]);
						SendClientMessageToAll(0xFF0000AA, string);
				
						Property[property_in][prop_savedmoney] = 0;
					}
				}else SendClientMessage(playerid, 0xFFFFFFAA, "Nemovitost nema v kase ani haler.");
			}else SendClientMessage(playerid, 0xFFFFFFAA, "Nemuzes vykrast svoji nemovitost.");
		}

		}

	} else SendClientMessage(playerid, 0xFFFFFFAA, "Musis byt u nemovitosti.");
	}	
	
	TogglePlayerControllable(playerid, true);
	PropertyMenu[playerid] = false; // Menu uz nevidi
	return true;
}

RobRandom(playerid)
{
	if(IsPlayerConnected(playerid))
 	{
    	new status = random(13);

		switch(status)
		{
			case 0,1,2:
			{
			    new string[250];
				SetPlayerHealth(playerid, 0.0);
				format(string, 250, "%s byl pri pokusu o loupez zabit prodavacem.", Jmeno(playerid));
				SendClientMessageToAll(0xFF0000AA, string);
				return 0;
			}
			case 8,9,10,11:
			{
				new string[250],Float:hp;
				GetPlayerHealth(playerid, hp);
				SetPlayerHealth(playerid, hp - 50.0);
				if(hp - 50.0 <= 0.0) format(string, 250, "%s byl pri pokusu o loupez zabit prodavacem.", Jmeno(playerid));
				else format(string, 250, "%s byl pri pokusu o loupez poranen prodavacem.", Jmeno(playerid));
				SendClientMessageToAll(0xFF0000AA, string);
				return 0;
			}
		}
	}
	return 1;
}

stock PropertyMenuLoad() // Nacteni menu
{
	PropertyBuyMenu = CreateMenu("Nemovitost",1,20,120,150,40);
	if(IsValidMenu(PropertyBuyMenu))
	{
    	AddMenuItem(PropertyBuyMenu,0,"Vlastnik");
    	AddMenuItem(PropertyBuyMenu,0,"Koupit");
    	AddMenuItem(PropertyBuyMenu,0,"Prodat");
    	AddMenuItem(PropertyBuyMenu,0,"Vydelky");
    	AddMenuItem(PropertyBuyMenu,0,"Vyplatit");
    	AddMenuItem(PropertyBuyMenu,0,"Mafianska ochrana");
    	AddMenuItem(PropertyBuyMenu,0,"Vykrast");
    }
}

public PropertyPickup()
{
	for(new i=0;i<MAX_PLAYERS;i++)
	{
	if(IsPlayerConnected(i))
	{
 		for(new p=0;p<PropertyCount;p++)
  		{
  			if(PlayerToPoint(1.8,i,Property[p][prop_pos_x],Property[p][prop_pos_y],Property[p][prop_pos_z]))
			{	
				if(PropertyMenu[i] == false) {TogglePlayerControllable(i, false); ShowMenuForPlayer(PropertyBuyMenu, i); PropertyMenu[i] = true; }
				new string[250];
				format(string, 250,"~r~%s~n~Cena: ~w~%d$~n~~r~Majitel: ~w~%s",Property[p][prop_name],Property[p][prop_cost],Property[p][prop_ownername]);
                GameTextForPlayer(i,string,5000,1);
				continue;
			}
  		}
  	}
	}
}

public PlayerToPoint(Float:r, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
	{
		new Float:ox,Float:oy,Float:oz,Float:tx,Float:ty,Float:tz;
		GetPlayerPos(playerid,ox,oy,oz);
		tx = (ox -x);
		ty = (oy -y);
		tz = (oz -z);
		if(((tx<r)&&(tx>-r))&&((ty<r)&&(ty>-r))&&((tz<r)&&(tz>-r))) return 1;
	}
	return 0;
}
  	
public AddProperty(Float:static_x,Float:static_y,Float:static_z, cost, payments, const property_name[], ownername[])
{
	if(PropertyCount <= MAX_PROPERTIES)
	{
	    CreatePickup(1274, 1, static_x, static_y, static_z);
	    //-----------------------------------------
	    Property[PropertyCount][prop_pos_x] = static_x;
	    Property[PropertyCount][prop_pos_y] = static_y;
	    Property[PropertyCount][prop_pos_z] = static_z;
	    Property[PropertyCount][prop_cost]  = cost;
	    Property[PropertyCount][prop_payments] = payments;
	    format(Property[PropertyCount][prop_name], MAX_PROPERTY_NAME, "%s", property_name);
	    format(Property[PropertyCount][prop_ownername],24,"%s",ownername);
	    //-----------------------------------------
	    PropertyCount++;
	}else{
		print("  __  Kapacita AddProperty prekrocena, nemovitost nebyla vytvorena.  __  ");
	}
}

stock PropertyPaymentsUpdate(const message[])
{
	for(new p;p<PropertyCount;p++)
	{
    	Property[p][prop_savedmoney] = Property[p][prop_savedmoney] + Property[p][prop_payments];
	}

	if(strlen(message) > 0) SendClientMessageToAll(0xFF0000AA,message);
}
  		
public GetPlayerPropertyIn(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		for(new p;p<PropertyCount;p++) if(PlayerToPoint(1.8,playerid,Property[p][prop_pos_x],Property[p][prop_pos_y],Property[p][prop_pos_z])) return p;
	}
	return -1;
}

public UnlockProperty(propertyid)
{
    Property[propertyid][prop_locked] = false;
    new ownerid = GetPlayerIDFromName(Property[propertyid][prop_ownername]);
    if(IsPlayerConnected(ownerid))
	{
	    new string[150];
		format(string, 150, "Nemovitost %s nadale neni pod ochranou mafie.",Property[propertyid][prop_name]);
		SendClientMessage(ownerid, 0xFF0000AA, string);
	}
}

stock GetPlayerPropertyID(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		for(new p;p<PropertyCount;p++) if(GetPlayerIDFromName(Property[p][prop_ownername]) == playerid) return p;
	}
	return -1;
}



// 					All rights reserved (c) Vojtech "MaverickCZE" Dvorak 2008
