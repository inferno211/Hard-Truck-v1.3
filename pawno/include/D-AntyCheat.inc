/*
	Anty-Cheat by Destroyer
    * bronie:

    dDajBron(playerid,id,ammo) - dajemy komuœ broñ i amunicjê
    dCzyMaBron(playerid,id) - sprawdzamy czy gracz posiada podan¹ przez nas bron
    dWyswietlAmmo(playerid,id) - zwraca nam iloœæ amunicji u broni jaka podamy
    dSlotBron(playerid,id) - zwraca nam slot jaki zajmuje podane przez nas id broni
    dUsunBronieSlot(playerid,slot) - usuwa wszystkie bronie z podanego slotu
    dUsunBron(playerid,id) - usuwa podan¹ przez nas broñ
    dUsunBronie(playerid) - usuwa wszystkie bronie jakie posiada gracz

    * kasa:

    dDodajKase(playerid,kasa) - dodaje graczu podana ilosc kasy
    dCzyMaKase(playerid,kasa) - sprawdzamy czy grac posiada podana przez nas kwote
    dWyswietlKase(playerid) - zwraca nam kwote jaka posiada gracz
    dUstawKase(playerid,kasa) - ustawia graczu podana przez nas kwote
    dUsunKase(playerid) - zeruje graczu kase

    * hp:

    dDodajHP(playerid,Float:HP) - dodaje graczu podana przez nas ilosc hp
    dUstawHP(playerid,Float:HP) - ustawia hp na podane przez nas
    dCzyMaHP(playerid,Float:hp) - sprawdza czy gracz ma co najmniej tyle hp ile podalismy
    dWyswietlHP(playerid) = wyswietla stan hp

    * pancerz:

    dDodajArmor(playerid,Float:Armor) - dodaje graczu podana ilosc przez nas pancerza
    dUstawArmor(playerid,Float:Armor) - ustawia graczu podana przez nas ilosc pancerza
    dCzyMaArmor(playerid,Float:armor) - sprawdza czy gracz ma co najmniej tyle pancerza ile podalismy
    dWyswietlArmor(playerid) = wyswietla stan hp
*/

#include <a_samp>
#include <foreach>

#define KOLOR_ROZOWY 0xFF80FFFF
#define C_BIALY "{FFFFFF}"
#define C_CZERWONY "{FF0000}"

new dKasa[MAX_PLAYERS],
	Float:dHP[MAX_PLAYERS],
	Float:dArmor[MAX_PLAYERS],
	Timer,TimerPing,
	ACString[128],

	Float:ACHP,Float:ACArmor;

DestACOn()//uruchomienie anty cheata
{
    KillTimer(Timer);
	Timer=SetTimer("AntyCheatSystem",2000,true);
	TimerPing=SetTimer("AntyCheatPing",60000,true);
	return 1;
}

DestACOff()//wy³¹czenie anty cheata
{
	KillTimer(Timer);
	KillTimer(TimerPing);
	return 1;
}

forward AntyCheatPing();
public AntyCheatPing()
{
    foreach(Player,i)
	{
		if(GetPlayerPing(i)>=400)
		{
			format(ACString,sizeof(ACString),"AC: "C_BIALY"(%d) %s zosta³ wyrzucony, za: "C_CZERWONY"ping (%d)",i,ACNick(i),GetPlayerPing(i));
			SendClientMessageToAll(KOLOR_ROZOWY,ACString);
			format(ACString, sizeof(ACString),"~r~(%d)%s zostal zbanowany~n~~y~przez: (-1)AntyCheat~n~~w~Za: ping (%d)",i,ACNick(i),GetPlayerPing(i));
			NapisText(ACString);
			Kick(i);
			//SerwerInfo[sKick]++;
			
		}
	}
	return 1;
}

forward AntyCheatSystem();
public AntyCheatSystem()
{

	foreach(Player,i)
	{
 		GetPlayerHealth(i,ACHP); GetPlayerArmour(i,ACArmor);
 		//kasa
		if(GetPlayerMoney(i)!=dKasa[i])
		{
  			ResetPlayerMoney(i);
     		GivePlayerMoney(i,dKasa[i]);
    	}
		//hp
		if(ACHP!=dHP[i])
		{
			if(ACHP>dHP[i])
  			{
  				SetPlayerHealth(i,dHP[i]);
	   		}
	   		else
	   		{
				dHP[i]=ACHP;
		 	}
   		}
		//armor
		if(ACArmor!=dArmor[i])
		{
 			if(ACArmor>dArmor[i])
   			{
  				SetPlayerArmour(i,dArmor[i]);
	   		}
		   	else
		   	{
				dArmor[i]=ACArmor;
		 	}
   		}
		//jetpack
		if(GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK)
		{
			SetPlayerSpecialAction(i, SPECIAL_ACTION_NONE);
			format(ACString,sizeof(ACString),"AC: "C_BIALY"(%d) %s zosta³ wyrzucony, za: "C_CZERWONY"jetpack",i,ACNick(i));
			SendClientMessageToAll(KOLOR_ROZOWY,ACString);
			format(ACString, sizeof(ACString),"~r~(%d)%s zostal zbanowany~n~~y~przez: (-1)AntyCheat~n~~w~Za: jetpack",i,ACNick(i));
			NapisText(ACString);
			Kick(i);
			//SerwerInfo[sKick]++;
		}
		//bronie
	}//od petli
	return 1;
}

stock ACNick(playerid)
{
	new nick[MAX_PLAYER_NAME];
	GetPlayerName(playerid, nick, sizeof(nick));
	return nick;
}

stock ACGetPlayerSpeed(playerid)// km/h by destroyer
{
	new Float:x,Float:y,Float:z,Float:predkosc;
	if(IsPlayerInAnyVehicle(playerid)) GetVehicleVelocity(GetPlayerVehicleID(playerid),x,y,z); else GetPlayerVelocity(playerid,x,y,z);
	predkosc=floatsqroot((x*x)+(y*y)+(z*z))*198;
	return floatround(predkosc);
}

stock AntyCheatStart(playerid)
{
	dUstawKase(playerid,0);
	dUstawHP(playerid,100);
	dUstawArmor(playerid,0);
}

	//hp
stock dDodajHP(playerid,Float:HP)
{
	dHP[playerid]+=HP;
	SetPlayerHealth(playerid,dHP[playerid]);
	if(dHP[playerid]>100)
	{
		dHP[playerid]=100;
		SetPlayerHealth(playerid,100);
	}
	return 1;
}


stock dUstawHP(playerid,Float:HP)
{
	dHP[playerid]=HP;
	SetPlayerHealth(playerid,HP);
	/*if(dHP[playerid]>100)
	{
		dHP[playerid]=100;
		SetPlayerHealth(playerid,100);
	}*/
	return 1;
}

stock dUstawGod(playerid)
{
	SetPlayerHealth(playerid,10000);
	return 1;
}

stock dCzyMaHP(playerid,Float:hp)
{
	if(dHP[playerid]>=hp)
	{
	    return 1;
	}
	return 0;
}

stock Float:dWyswietlHP(playerid)
{
	return dHP[playerid];
}

	//armor

stock dDodajArmor(playerid,Float:Armor)
{
	dArmor[playerid]+=Armor;
	SetPlayerArmour(playerid,dArmor[playerid]);
	if(dArmor[playerid]>100)
	{
		dArmor[playerid]=100;
		SetPlayerArmour(playerid,100);
	}
	return 1;
}

stock dUstawArmor(playerid,Float:Armor)
{
	dArmor[playerid]=Armor;
	SetPlayerArmour(playerid,Armor);
	if(dArmor[playerid]>100)
	{
		dArmor[playerid]=100;
		SetPlayerArmour(playerid,100);
	}
	return 1;
}

stock dCzyMaArmor(playerid,Float:armor)
{
	if(dArmor[playerid]>=armor)
	{
	    return 1;
	}
	return 0;
}

stock Float:dWyswietlArmor(playerid)
{
	return dArmor[playerid];
}

	//kasa
stock dDodajKase(playerid,kasa)
{
	dKasa[playerid]+=kasa;
	GivePlayerMoney(playerid,kasa);
	return 1;
}

stock dCzyMaKase(playerid,kasa)
{
	if(dKasa[playerid]>=kasa)
	{
	    return 1;
	}
	return 0;
}

stock dWyswietlKase(playerid)
{
	return dKasa[playerid];
}

stock dUstawKase(playerid,kasa)
{
	dKasa[playerid]=kasa;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid,kasa);
	return 1;
}

stock dUsunKase(playerid)
{
	dKasa[playerid]=0;
	ResetPlayerMoney(playerid);
	return 1;
}
/*
	//anty cheat na bron
stock dDajBron(playerid,id,ammo)
{
	if((id<1||id>46)||id==19||id==20||id==21) return 1;
	if(ammo<1||ammo>999) return 1;
	new slot=dSlotBron(id);
	dUsunBronieSlot(playerid,slot);
	dBron[playerid][id]=true;
	dAmmo[playerid][id]=ammo;
	GivePlayerWeapon(playerid,id,ammo);
	return 1;
}

stock dCzyMaBron(playerid,id)
{
	if((id<1||id>46)||id==19||id==20||id==21) return 1;
	if(dBron[playerid][id]==true)
	{
		return 1;
	}
	return 0;
}

stock dWyswietlAmmo(playerid,id)
{
	if((id<1||id>46)||id==19||id==20||id==21) return 1;
	return dAmmo[playerid][id];
}

stock dSlotBron(id)
{
	if((id<1||id>46)||id==19||id==20||id==21) return 1;
	new slot;
    switch(id)
	{
		case 0, 1: slot = 0;
		case 2..9: slot = 1;
		case 22..24: slot = 2;
		case 25..27: slot = 3;
		case 28, 29, 32: slot = 4;
		case 30, 31: slot = 5;
		case 33, 34: slot = 6;
		case 35..38: slot = 7;
		case 16..19, 39: slot = 8;
		case 41..43: slot = 9;
		case 10..15: slot = 10;
		case 44..46: slot = 11;
		case 40: slot = 12;
	}
	return slot;
}

stock dUsunBronieSlot(playerid,slot)
{
	new bron,ammo;
	GetPlayerWeaponData(playerid,slot,bron,ammo);
	if(dBron[playerid][bron]==true)
	{
 		GivePlayerWeapon(playerid,bron,-ammo);
   		dBron[playerid][bron]=false;
		dAmmo[playerid][bron]=0;
	}
	return 1;
}

stock dUsunBron(playerid,id)
{
	if((id<1||id>46)||id==19||id==20||id==21) return 1;
	new bron,ammo,slot=dSlotBron(id);
	GetPlayerWeaponData(playerid,slot,bron,ammo);
	if(bron==id&&dBron[playerid][id]==true)
	{
 		GivePlayerWeapon(playerid,id,-ammo);
   		dBron[playerid][id]=false;
		dAmmo[playerid][id]=0;
	}
	return 1;
}

stock dUsunBronie(playerid)
{
	ResetPlayerWeapons(playerid);
	for(new p = 1; p <= 46; p++)
	{
	    dBron[playerid][p]=false;
		dAmmo[playerid][p]=0;
	}
	return 1;
}*/