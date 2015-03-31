/*
 *            DUtils functions 1.10
 *       (c) Copyright 2006-2007 by DracoBlue
 *
 * @author    : Dupa
 * @date      : Dupska
 * @update    : Dupsko
 *
 * This file is provided as is (no warranties).
 *
 */

#define COLOR_VIOLET 0x8000FFFF
#define COLOR_BLACK 0x000000FF
#define COLOR_BROWN 0x8F4747FF
#define COLOR_PINK 0xFF66FFAA
#define COLOR_DARKGREEN 0x0D731FFF
#define COLOR_DARKBLUE 0x2010E0FF
#define COLOR_DARKBROWN 0x530000FF
#define COLOR_DARKVIOLET 0x400040FF
#define COLOR_DARKYELLOW 0x808000FF
#define COLOR_DARKPINK 0x400040FF
#define COLOR_KREM 0xFF8080FF
#define COLOR_LIGHTGREEN 0x00FF00FF
#define COLOR_LIGHTPINK 0xFF80FFFF
#define COLOR_SYSGREY 0xC6BEBDFF
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_GREEN 0x39FF09FF
#define COLOR_RED 0xFF282EFF
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_BLUE 0x0000BBAA
#define COLOR_LIGHTBLUE 0x33CCFFAA
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_ADMIN 0xFF0000AA
#define COLOR_SYSTEM 0xEFEFF7AA

#define STATYSTYKI "totalstat.ini"

forward MoneyGrubScoreUpdate();
forward SetPlayerRandomSpawn(playerid);
forward SetupPlayerForClassSelection(playerid);
forward GameModeExitFunc();
forward checkpointUpdate();
forward PropertyScoreUpdate();
forward isPlayerInArea(playerID, Float:data[4]);
forward getCheckpointType(playerID);
forward PirateShipScoreUpdate();
forward PayPlayerInArea(playerID, Float:x1, Float:y1, Float:x2, Float:y2, cash);
forward komendysek(playerid);
forward opodloz(playerid);
forward ojj(playerid);
forward ozw(playerid);
forward ozycie(playerid);
forward owitam(playerid);
forward onara(playerid);
forward onapraw(playerid);
forward onapraw(playerid);
forward okill(playerid);
forward oodlicz(playerid);
forward odetonuj(playerid);
forward SendPlayerFormattedText(playerid, const str[], define);
forward DisCountSpam(p);
forward IconUpdate();
forward AntyPing();
forward CountDown();
forward TowPlayerVehicle(playerid);
forward SendClientMessageToAdmins(color, const zmienna[]);
forward SendClientMessageToVips(color, const zmienna[]);
forward PlayerLeaveGang(playerid);
forward IsPlayerInAreawiez(playerid, Float:minx, Float:maxx, Float:miny, Float:maxy);
forward Reklama5();
forward Reklama4();
forward Reklama3();
forward Reklama1();
forward bronarena(playerid);
forward bronbazoka(playerid);
forward bronm4(playerid);
forward odstaw2(playerid);
forward FunkcjaRespawnu(playerid, vehicleid);
forward SprawdzanieArenWalki();
forward AntyCheat();
forward LoginTimeout(playerid);
forward ZapiszWszystkim();
forward OnPlayerPickUpPickup(playerid, pickupid);
forward autootwarcie();
forward dupsko(playerid);

stock PlayerName(playerid) {
	new name[255];
 	GetPlayerName(playerid, name, 255);
 	return name;
}
Player(playerid)
{
	new player[MAX_PLAYER_NAME];
	GetPlayerName(playerid, player, sizeof(player));
	return player;
}
Killer(killerid)
{
	new killer[MAX_PLAYER_NAME];
	GetPlayerName(killerid, killer, sizeof(killer));
	return killer;
}
GetVehicleWithinDistance( playerid, Float:x1, Float:y1, Float:z1, Float:dist, &vehic){
	for(new i = 1; i < MAX_VEHICLES; i++){
		if(GetVehicleModel(i) > 0){
			if(GetPlayerVehicleID(playerid) != i ){
				new Float:x, Float:y, Float:z;
				new Float:x2, Float:y2, Float:z2;
				GetVehiclePos(i, x, y, z);
				x2 = x1 - x; y2 = y1 - y; z2 = z1 - z;
				new Float:iDist = (x2*x2+y2*y2+z2*z2);
				if( iDist < dist){
					vehic = i;
				}
			}
		}
	}
}
stock ConnectedPlayers()
{
	new count;
	for(new x=0; x<MAX_PLAYERS; x++) {
		if(IsPlayerConnected(x)) {
			count++;
		}
	}
	return count;
}

#define CP_BANK         0
#define CP_PIRATE       1
#define CP_AMMU         2
#define CP_HELL      	3
#define CP_DRAGON       4
#define CP_CALIGULA     5
#define CP_SEXSHOP      6
#define CP_BAR          7
#define CP_ZIP         	8
#define CP_BINCO        9
#define CP_TATOO       10
#define CP_BOTIQUE     11
#define CP_STRIPCLUB   12
#define CP_WANGCARS    13
#define CP_AIRSTRIP    14
#define CP_EMERALD     15
#define CP_VISAGE      16
#define CP_SPREADRANCH 17
#define CP_STARFISH    18
#define CP_ROPA        19
#define CP_PARAFIA     20
#define CP_ROCKHOTEL   21
#define CP_METALSHOP   22
#define CP_STACJALV    23
#define CP_LOTNISKO    24
#define CP_BAZA        25
#define CP_HATA        26
#define CP_BAZA11      27
#define CP_BAZA12      28
#define CP_BAZA13      29
#define CP_BARW        30

#define P_DRAGON        0
#define P_CALIGULA      1
#define P_SEXSHOP       2
#define P_BAR           3
#define P_ZIP           4
#define P_BINCO         5
#define P_TATOO         6
#define P_BOTIQUE       7
#define P_STRIPCLUB     8
#define P_WANGCARS      9
#define P_AIRSTRIP     10
#define P_EMERALD      11
#define P_VISAGE       12
#define P_SPREADRANCH  13
#define P_STARFISH     14
#define P_ROPA        15
#define P_PARAFIA     16
#define P_ROCKHOTEL   17
#define P_METALSHOP   18
#define P_STACJALV    19
#define P_LOTNISKO    20

#define P_OFFSET    4

#define MAX_POINTS 31
//-----Koordy markerów
new Float:checkCoords[MAX_POINTS][4] = {
	{-36.5483,-57.9948, -17.2655,-49.2967},
	{1894.6128,1445.3431, 2084.9739,1637.8186},
	{284.0546,-86.4384, 302.9315,-56.6674},
	{-2549.7979,-1660.4034,-2339.2673,-1589.3324},
	{1925.1511,968.2358, 2019.0715,1067.4276},
	{2216.7971,1638.0493, 2255.2097,1714.0806},
	{-115.9544,-24.2706, -99.1631,-7.1391},
	{487.6558,-88.5900, 512.0635, -67.7503},
	{144.9131,-96.0927, 177.4128,-70.7923},
	{201.4462,-112.4556, 218.5237,-95.1238},
	{-204.7623,-44.0326, -200.2330,-39.8128},
	{416.7485,-84.4242, 422.6890,-74.0611},
	{1201.1422,-16.6343,1223.4420,12.6656},
	{-1996.0801,253.4684,-1942.0564,310.0717},
	{413.4203,2534.9907,421.4078,2542.7031},
	{2099.1985,2328.5200,2179.1382,2405.8721},
	{1998.3783,1875.9679,2066.3425,1957.0034},
	{1205.7026,-41.1453,1216.8755,-23.9896},
	{2107.4619,1852.0098,2203.6267,1983.9738},
	{537.7953,1449.0892,709.7960,1626.7419},
	{2417.7458,871.6465,2572.0159,986.4371},
	{2556.8198,2254.7537,2693.4243,2395.4614},
	{2488.3906,2288.1797,2543.4998,2391.4841},
	{1367.5404,2582.1882,1513.3503,2705.8162},
	{1552.8221,1364.1782,1753.0825,1519.3199},
	{1929.4453,2398.7639,1953.5980,2425.9380},//////////////
	{1916.5334,2426.8167,1924.9418,2437.7795},/////////////////////
	{1853.5430,1779.5178,1896.7898,1823.2184},
	{1949.7457,1748.9823,1988.0371,1778.0660},
	{1963.0989,1734.7319,2002.9460,1747.4436},
	{2139.9211,973.5457,2209.1145,1080.7388}
};
//-----Markery
new Float:checkpoints[MAX_POINTS][3] = {
	{-22.2549,-55.6575,1003.5469},
	{2000.3132,1538.6012,13.5859},
	{291.0004,-84.5168,1001.5156},
	{-2432.6628,-1620.0771,526.8676},
	{1989.0619,1005.5241,994.4688},
	{2235.5408,1679.0402,1008.3594},
	{-103.5525,-22.4661,1000.7188},
	{501.4927,-75.4323,998.7578},
	{161.1875,-79.9915,1001.8047},
	{207.5640,-97.8188,1005.2578},
	{-203.4864,-41.2045,1002.2734},
	{418.5547,-80.1667,1001.8047},
	{1212.3918,-10.9459,1000.9219},
	{-1957.5327,300.2131,35.4688},
	{418.1210,2536.8762,10.0000},
	{2127.5940,2370.4255,10.8203},
	{2022.5179,1916.6848,12.3397},
	{1208.5027,-32.6044,1000.9531},
	{2165.1523,1901.3459,10.8203},
	{614.8133,1549.6451,4.9361},
	{2485.6890,918.8550,10.8203},
	{2632.3352,2347.1904,10.6719},
	{2518.8796,2334.2656,10.8203},
	{1436.3792,2652.0818,11.3926},
	{1684.1711,1448.4459,10.7709},
	{1939.8365,2411.3420,10.8323},///////////////////
	{1923.9683,2434.2322,12.3858},////////////////////
	{1874.8990,1805.1327,12.7437},
	{1966.3617,1758.0869,12.7437},
	{1971.8042,1743.7091,12.7437},
	{2182.6675,1015.3694,10.9203}
};
//-----Nazwy markerów
new checkpointType[MAX_POINTS] = {
	CP_BANK,
	CP_PIRATE,
	CP_AMMU,
	CP_HELL,
	CP_DRAGON,
	CP_CALIGULA,
	CP_SEXSHOP,
	CP_BAR,
	CP_ZIP,
	CP_BINCO,
	CP_TATOO,
	CP_BOTIQUE,
	CP_STRIPCLUB,
	CP_WANGCARS,
	CP_AIRSTRIP,
	CP_EMERALD,
	CP_VISAGE,
	CP_SPREADRANCH,
	CP_STARFISH,
	CP_ROPA,
	CP_PARAFIA,
	CP_ROCKHOTEL,
	CP_METALSHOP,
	CP_STACJALV,
	CP_LOTNISKO,
	CP_BAZA,
	CP_HATA,
	CP_BAZA11,
	CP_BAZA12,
	CP_BAZA13,
	CP_BARW
};

#define MAX_PROPERTIES	21
//-----Nazwy Posiad³oœci
new propertyNames[MAX_PROPERTIES][32] = {
	"Four Dragons",
	"Caligula",
	"Sex Shop",
	"Shithole Bar",
	"Zip Shop",
	"Binco Shop",
	"Tatoo Parlor",
	"Botique",
	"Strip Club",
	"Wang Cars",
	"Verdant Meadows Air Strip",
	"Emerald Isle",
	"The Visage",
	"The Big Spread Ranch",
	"StarFish",
	"Z³o¿a Ropy",
	"Parafia 'Belzebub'",
	"Rock Hotel",
	"Metal Shop",
	"Stacja Kolejowa LV",
	"Lotnisko LV"
};
//-----Cena posiad³oœci
new propertyValues[MAX_PROPERTIES] = {
	300000,//smoki
	400000,//caligula
	15000,//sexshop
	100000,//sitholebar
	70000,//zipshop
	70000,//bincoshop
	10000,//tatoo
	20000,//bontique
	30000,//stripclub
	40000,//wang cars
	25000,//verdant
	700000,//isle
	700000,//visage
	25000,//spreadranch
	100000,//starfish
	2000000,//Ropa
	30000,//parafia
	1000000,//Rockhotel
	300000,//metalshop
	70000,//stacjalv
	700000//lotnisko
};
//-----Dochody posiad³oœci
new propertyEarnings[MAX_PROPERTIES] = {
	7000,//smoki
	8000,//caligula
	700,//sexshop
	900,//sitholebar
	900,//zipshop
	500,//bincoshop
	700,//tatoo
	950,//bontique
	1000,//stripclub
	1200,//wang cars
	2000,//verdant
	10000,//isle
	10000,//visage
	2000,//spreadranch
	7000,//starfish
	100000,//Ropa
	200,//parafia
 	50000,//Rock Hotel
 	1000,//metalshop
 	800,//stacjalv
 	10000//lotnisko
};

new propertyOwner[MAX_PROPERTIES] = {999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999};

new CashScoreOld;
new iSpawnSet[MAX_PLAYERS];
new bank[MAX_PLAYERS];
new bounty[MAX_PLAYERS];
new playerCheckpoint[MAX_PLAYERS];
new giveplayerid;
new vip[MAX_PLAYERS];
new Float:boomX[MAX_PLAYERS];
new Float:boomY[MAX_PLAYERS];
new Float:boomZ[MAX_PLAYERS];
new komendy[MAX_PLAYERS];
new njj[MAX_PLAYERS];
new nzw[MAX_PLAYERS];
new nzycie[MAX_PLAYERS];
new nwitam[MAX_PLAYERS];
new nnara[MAX_PLAYERS];
new nnapraw[MAX_PLAYERS];
new nkill[MAX_PLAYERS];
new npodloz[MAX_PLAYERS];
new playermuted[MAX_PLAYERS];
new Mutedpm[MAX_PLAYERS];
new logmuted[MAX_PLAYERS];
new Arena[MAX_PLAYERS];
new Bazoka[MAX_PLAYERS];
new M4[MAX_PLAYERS];
//new Float:Ang;
new Float:LocX;
new Float:LocY;
new Float:LocZ;
new JailStatus[MAX_PLAYERS];
new podlozyl[MAX_PLAYERS];
new Float:aa2,Float: b2,Float: c2;
new IP[MAX_PLAYERS][20];
new eye2 = 0;
new ping[MAX_PLAYERS];
new zalogowany[MAX_PLAYERS];
new zlehaslo[MAX_PLAYERS];
new logintimeout[MAX_PLAYERS];
new wylogowany[MAX_PLAYERS];
new Ping;
new dom;
new brama;
new hata2;
new bramadrag;
new dragizielone[MAX_PLAYERS];
new dragiczerwone[MAX_PLAYERS];
new draginiebieskie[MAX_PLAYERS];
new pz1;
new pz2;
new pz3;
new pz4;
new pz5;
new pz6;
new pz7;
new pz8;
new pz9;
new pz10;
new pn1;
new pn2;
new pn3;
new pn4;
new pn5;
new pn6;
new pn7;
new pc1;
new pc2;
new pc3;
new pc4;
new pc5;
new czolg;
GetPlayerNick(playerid){
    new Name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, Name, sizeof(Name));
	return Name;
}



#define ADMIN_SPEC_TYPE_NONE 0
#define ADMIN_SPEC_TYPE_PLAYER 1
#define ADMIN_SPEC_TYPE_VEHICLE 2
#define dcmd(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define PlColor[%1] ColorsAlpha77[PlIdCo[%1]]

#define PocketMoney 10000
#define INACTIVE_PLAYER_ID 255
#define GIVECASH_DELAY 5000
#define MAX_ICONS 60