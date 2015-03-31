#if defined _ACByDestroyerV2_included
	#endinput
#endif
#define _ACByDestroyerV2_included

#include <a_samp>
#pragma tabsize 0
#define KOLOR_ADMIN 0x80FF80FF
new GraczZespawnowany[MAX_PLAYERS];

new BronInfo[MAX_PLAYERS][47];

new Float:hp[MAX_PLAYERS];
new Float:armor[MAX_PLAYERS];
new kaska[MAX_PLAYERS];

forward Ac_OnGameModeInit();
public Ac_OnGameModeInit()//anty cheat
{
SetTimer("AntyCheatSystemByDestroyer", 1000, 1);
return 1;
}

forward Ac_OnPlayerConnect(playerid);
public Ac_OnPlayerConnect(playerid)
{
	kaska[playerid]=0;
	hp[playerid]=50;
	armor[playerid]=0;
	
	for(new i; i < 47; i++)
    BronInfo[playerid][i]=0;
	
return 1;
}

forward Ac_OnPlayerSpawn(playerid);
public Ac_OnPlayerSpawn(playerid)
{
GraczZespawnowany[playerid]=1;
return 1;
}

forward AntyCheatSystemByDestroyer();
public AntyCheatSystemByDestroyer(){

        for(new i = 0, p = GetMaxPlayers(); i < p; i++)
        {
			//anty money cheat :D by Destoyer
			if(GetPlayerMoney(i) > kaska[i])
		    {
		    if(IsPlayerConnected(i))
			{
			ResetPlayerMoney(i);
			GivePlayerMoney(i,kaska[i]);
			}
			}//koniec

			//anty armor i hp cheat by destroyer

			new Float:HP,Float:ARMOR;
			GetPlayerHealth(i,HP);
			GetPlayerArmour(i,ARMOR);

			if(HP>hp[i]){
			SetPlayerHealth(i,hp[i]);
			}
			if(ARMOR>armor[i]){
			SetPlayerArmour(i,armor[i]);
			}

			//anty bron chack by Destroyer
			if(GetPlayerWeapon(i) >=1 && GraczZespawnowany[i]==1)
			{
			new b=GetPlayerWeapon(i);
				switch(b)
				{

			case 1: if(BronInfo[i][1] < 1){
		 	}
			case 2: if(BronInfo[i][2] < 1){
		 	}
			case 3: if(BronInfo[i][3] < 1){
		 	}
			case 4: if(BronInfo[i][4] < 1){
			
		 	}
			case 5: if(BronInfo[i][5] < 1){
			
		 	}
			case 6: if(BronInfo[i][6] < 1){
			
		 	}
			case 7: if(BronInfo[i][7] < 1){
			
		 	}
			case 8: if(BronInfo[i][8] < 1){
			
		 	}
			case 9: if(BronInfo[i][9] < 1){
			
		 	}
			case 10: if(BronInfo[i][10] < 1){
			
		 	}
			case 11: if(BronInfo[i][11] < 1){
			
		 	}
			case 12: if(BronInfo[i][12] < 1){
			
		 	}
			case 13: if(BronInfo[i][13] < 1){
			
		 	}
			case 14: if(BronInfo[i][14] < 1){
			
		 	}
			case 15: if(BronInfo[i][15] < 1){
			
		 	}
			case 16: if(BronInfo[i][16] < 1){
			
		 	}
			case 17: if(BronInfo[i][17] < 1){
			
		 	}
			case 18: if(BronInfo[i][18] < 1){
			
		 	}
			case 19: if(BronInfo[i][19] < 1){
			
		 	}
			case 20: if(BronInfo[i][20] < 1){
			
		 	}
			case 21: if(BronInfo[i][21] < 1){
			
		 	}
			case 22: if(BronInfo[i][22] < 1){
			
		 	}
			case 23: if(BronInfo[i][23] < 1){
			
		 	}
			case 24: if(BronInfo[i][24] < 1){
			
		 	}
			case 25: if(BronInfo[i][25] < 1){
			
		 	}
			case 26: if(BronInfo[i][26] < 1){
			
		 	}
			case 27: if(BronInfo[i][27] < 1){
			
		 	}
			case 28: if(BronInfo[i][28] < 1){
			
		 	}
			case 29: if(BronInfo[i][29] < 1){
			
		 	}
			case 30: if(BronInfo[i][30] < 1){
			
		 	}
			case 31: if(BronInfo[i][31] < 1){
			
			}
			case 32: if(BronInfo[i][32] < 1){
			
		 	}
			case 33: if(BronInfo[i][33] < 1){
			
		 	}
			case 34: if(BronInfo[i][34] < 1){
			
		 	}
			case 35: if(BronInfo[i][35] < 1){
			
		 	}
			case 36: if(BronInfo[i][36] < 1){
			
		 	}
			case 37: if(BronInfo[i][37] < 1){
			
		 	}
			case 38: if(BronInfo[i][38] < 1){
			
		 	}
			case 39: if(BronInfo[i][39] < 1){
			
		 	}
			case 40: if(BronInfo[i][40] < 1){
			
	 		}
			case 41: if(BronInfo[i][41] < 1){
			
		 	}
			case 42: if(BronInfo[i][42] < 1){
			
		 	}
			case 43: if(BronInfo[i][43] < 1){
			
		 	}
			case 44: if(BronInfo[i][44] < 1){
			
		 	}
			case 45: if(BronInfo[i][45] < 1){
			
		 	}
			case 46: if(BronInfo[i][46] < 1){
		 	}
				}//switch
			}//koniec anty na bronie

		}

return 1;
}

forward DajBronGraczu(playerid,bron,ammo);
public DajBronGraczu(playerid,bron,ammo)
{
switch(bron)
{
case 0: { GivePlayerWeapon(playerid,bron,ammo); }
case 1: { BronInfo[playerid][1]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 2: { BronInfo[playerid][2]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 3: { BronInfo[playerid][3]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 4: { BronInfo[playerid][4]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 5: { BronInfo[playerid][5]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 6: { BronInfo[playerid][6]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 7: { BronInfo[playerid][7]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 8: { BronInfo[playerid][8]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 9: { BronInfo[playerid][9]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 10: { BronInfo[playerid][10]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 11: { BronInfo[playerid][11]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 12: { BronInfo[playerid][12]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 13: { BronInfo[playerid][13]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 14: { BronInfo[playerid][14]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 15: { BronInfo[playerid][15]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 16: { BronInfo[playerid][16]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 17: { BronInfo[playerid][17]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 18: { BronInfo[playerid][18]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 19: { BronInfo[playerid][19]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 20: { BronInfo[playerid][20]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 21: { BronInfo[playerid][21]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 22: { BronInfo[playerid][22]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 23: { BronInfo[playerid][23]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 24: { BronInfo[playerid][24]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 25: { BronInfo[playerid][25]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 26: { BronInfo[playerid][26]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 27: { BronInfo[playerid][27]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 28: { BronInfo[playerid][28]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 29: { BronInfo[playerid][29]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 30: { BronInfo[playerid][30]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 31: { BronInfo[playerid][31]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 32: { BronInfo[playerid][32]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 33: { BronInfo[playerid][33]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 34: { BronInfo[playerid][34]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 35: { BronInfo[playerid][35]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 36: { BronInfo[playerid][36]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 37: { BronInfo[playerid][37]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 38: { BronInfo[playerid][38]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 39: { BronInfo[playerid][39]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 40: { BronInfo[playerid][40]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 41: { BronInfo[playerid][41]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 42: { BronInfo[playerid][42]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 43: { BronInfo[playerid][43]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 44: { BronInfo[playerid][44]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 45: { BronInfo[playerid][45]=1; GivePlayerWeapon(playerid,bron,ammo); }
case 46: { BronInfo[playerid][46]=1; GivePlayerWeapon(playerid,bron,ammo); }
}
return 1;
}

forward UsunBronie(playerid);
public UsunBronie(playerid){
ResetPlayerWeapons(playerid);
for(new i; i < 47; i++)
BronInfo[playerid][i]=0;
return 1;
}

forward UstawHP(playerid,Float:HP);
public UstawHP(playerid,Float:HP){
hp[playerid]=HP;
SetPlayerHealth(playerid,Float:HP);
return 1;
}

forward UstawArmor(playerid,Float:ARMOR);
public UstawArmor(playerid,Float:ARMOR){
armor[playerid]=ARMOR;
SetPlayerArmour(playerid,Float:ARMOR);
return 1;
}

forward DajKase(playerid,pieniadze);
public DajKase(playerid,pieniadze){
kaska[playerid]+=pieniadze;
GivePlayerMoney(playerid,pieniadze);
return 1;
}
forward ResetujKase(playerid);
public ResetujKase(playerid){
kaska[playerid]=0;
ResetPlayerMoney(playerid);
return 1;
}