
#define KOLOR_JASNONIEBIESKI 0x33CCFFAA
#define ZIELONY 0x33AA33AA
#define COLOR_LIGHTYELLOW 0xFAEAA9FF
#define COLOR_LIGHTORANGE 0xF7A26FFF
#define COLOR_VIOLET 0x9955DEEE
#define COLOR_LIGHTRED 0xFF99AADD
#define COLOR_SEAGREEN 0x00EEADDF
#define COLOR_BROWN 0x8F4747FF
#define COLOR_TEAL 0x01FCFFC8
#define COLOR_KREM 0xFF8080FF
#define COLOR_GRAYWHITE 0xEEEEFFC4
#define COLOR_LIGHTNEUTRALBLUE 0xabcdef66
#define COLOR_GREENISHGOLD 0xDEAD4370
#define COLOR_LIGHTBLUEGREEN 0x0FFDD349
#define COLOR_NEUTRALBLUE 0xABCDEF01
#define COLOR_LIGHTCYAN 0xAAFFCC33
#define COLOR_LEMON 0xDDDD2357
#define COLOR_MEDIUMBLUE 0x63AFF00A
#define COLOR_NEUTRAL 0xABCDEF97
#define COLOR_BLACK 0x00000000
#define COLOR_NEUTRALGREEN 0x81CFAB00
#define COLOR_DARKGREEN 0x12900BBF
#define COLOR_LIGHTGREEN 0x24FF0AB9
#define COLOR_DARKBLUE 0x300FFAAB
#define COLOR_BLUEGREEN 0x46BBAA00
#define COLOR_PINK 0xFF66FFAA
#define COLOR_BLUE 0x0000BBAA
#define COLOR_LIGHTBLUE 0x33CCFFAA
#define COLOR_GRAD1 0xB4B5B7FF
#define COLOR_DARKRED 0x660000AA
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_GREEN 0x33AA33AA
#define COLOR_RED 0xAA3333AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_ADMIN 0xFF0000AA
#define COLOR_KOMENDA 0xC83322FF
#define COLOR_BLOOD 0xE60005FF


#define CP_BANK 	0
#define CP_PIRATE 	1
#define CP_AMMU     2
#define CP_DRAGON   3
#define CP_SEXSHOP  4
#define CP_BAR      5
#define CP_CALIGULA 6
#define CP_ZIP      7
#define CP_BINCO    8
#define CP_TATOO    9
#define CP_BOTIQUE  10
#define CP_STARFISH 11
#define CP_TUNELV   12
#define CP_HIGHROLLER   13
#define CP_VISAGE   14
#define CP_LOTNISKO 15
#define CP_ROYAL 	16

#define P_DRAGON    0
#define P_SEXSHOP   1
#define P_BAR       2
#define P_CALIGULA  3
#define P_ZIP       4
#define P_BINCO     5
#define P_TATOO     6
#define P_BOTIQUE   7
#define P_STARFISH  8
#define P_TUNELV    9
#define P_HIGHROLLER 10
#define P_VISAGE   11
#define P_LOTNISKO 12
#define P_ROYAL    13

#define P_OFFSET    3


#define MAX_GANGS 			32
#define MAX_GANG_MEMBERS     6
#define MAX_GANG_NAME       16
new gangMembers[MAX_GANGS][MAX_GANG_MEMBERS];
new gangNames[MAX_GANGS][MAX_GANG_NAME];
new gangInfo[MAX_GANGS][3]; 
new gangBank[MAX_GANGS];
new playerGang[MAX_PLAYERS];
new gangInvite[MAX_PLAYERS];

new playerColors[100] = {
0xFF8C13FF,0xC715FFFF,0x20B2AAFF,0xDC143CFF,0x6495EDFF,0xf0e68cFF,0x778899FF,0xFF1493FF,0xF4A460FF,0xEE82EEFF,0xFFD720FF,
0x8b4513FF,0x4949A0FF,0x148b8bFF,0x14ff7fFF,0x556b2fFF,0x0FD9FAFF,0x10DC29FF,0x534081FF,0x0495CDFF,0xEF6CE8FF,0xBD34DAFF,
0x247C1BFF,0x0C8E5DFF,0x635B03FF,0xCB7ED3FF,0x65ADEBFF,0x5C1ACCFF,0xF2F853FF,0x11F891FF,0x7B39AAFF,0x53EB10FF,0x54137DFF,
0x275222FF,0xF09F5BFF,0x3D0A4FFF,0x22F767FF,0xD63034FF,0x9A6980FF,0xDFB935FF,0x3793FAFF,0x90239DFF,0xE9AB2FFF,0xAF2FF3FF,
0x057F94FF,0xB98519FF,0x388EEAFF,0x028151FF,0xA55043FF,0x0DE018FF,0x93AB1CFF,0x95BAF0FF,0x369976FF,0x18F71FFF,0x4B8987FF,
0x491B9EFF,0x829DC7FF,0xBCE635FF,0xCEA6DFFF,0x20D4ADFF,0x2D74FDFF,0x3C1C0DFF,0x12D6D4FF,0x48C000FF,0x2A51E2FF,0xE3AC12FF,
0xFC42A8FF,0x2FC827FF,0x1A30BFFF,0xB740C2FF,0x42ACF5FF,0x2FD9DEFF,0xFAFB71FF,0x05D1CDFF,0xC471BDFF,0x94436EFF,0xC1F7ECFF,
0xCE79EEFF,0xBD1EF2FF,0x93B7E4FF,0x3214AAFF,0x184D3BFF,0xAE4B99FF,0x7E49D7FF,0x4C436EFF,0xFA24CCFF,0xCE76BEFF,0xA04E0AFF,
0x9F945CFF,0xDCDE3DFF,0x10C9C5FF,0x70524DFF,0x0BE472FF,0x8A2CD7FF,0x6152C2FF,0xCF72A9FF,0xE59338FF,0xEEDC2DFF,0xD8C762FF,
0x3FE65CFF
};

new Float:gRandomPlayerSpawns[23][3] = {
{1958.3783,1343.1572,15.3746},
{2199.6531,1393.3678,10.8203},
{2483.5977,1222.0825,10.8203},
{2637.2712,1129.2743,11.1797},
{2000.0106,1521.1111,17.0625},
{2024.8190,1917.9425,12.3386},
{2261.9048,2035.9547,10.8203},
{2262.0986,2398.6572,10.8203},
{2244.2566,2523.7280,10.8203},
{2335.3228,2786.4478,10.8203},
{2150.0186,2734.2297,11.1763},
{2158.0811,2797.5488,10.8203},
{1969.8301,2722.8564,10.8203},
{1652.0555,2709.4072,10.8265},
{1564.0052,2756.9463,10.8203},
{1271.5452,2554.0227,10.8203},
{1441.5894,2567.9099,10.8203},
{1480.6473,2213.5718,11.0234},
{1400.5906,2225.6960,11.0234},
{1598.8419,2221.5676,11.0625},
{1318.7759,1251.3580,10.8203},
{1558.0731,1007.8292,10.8125},
{1705.2347,1025.6808,10.8203}
};

new Float:gCopPlayerSpawns[3][3] = {
{2297.1064,2452.0115,10.8203},
{2297.0452,2468.6743,10.8203},
{2268.0566,2449.2874,3.5313}
};

#define MAX_POINTS 17

new Float:checkCoords[MAX_POINTS][4] = {

{-36.5483,-57.9948, -17.2655,-49.2967},     //BANK
{1894.6128,1445.3431, 2084.9739,1637.8186}, //PIRATE
{284.0546,-86.4384, 302.9315,-56.6674},     //AMMUNATION
{1925.1511,968.2358, 2019.0715,1067.4276},  //DRAGON
{-115.9544,-24.2706, -99.1631,-7.1391},     //SEXSHOP
{487.6558,-88.5900, 512.0635, -67.7503},    //BAR
{2216.7971,1638.0493, 2255.2097,1714.0806}, //CALIGULA
{144.9131,-96.0927, 177.4128,-70.7923},    	//ZIP
{201.4462,-112.4556, 218.5237,-95.1238},    //BINCO
{-204.7623,-44.0326, -200.2330,-39.8128},   //TATOO
{416.7485,-84.4242, 422.6890,-74.0611},     //BOTIQUE
{2100.6367,1841.2338, 2352.1677,2014.0052}, //STARFISH
{2346.8098,951.5180,2429.6694,1067.5883},   //TUNE LV
{1927.2758,1276.3640,2038.7133,1449.4250},  //HIGH ROLLER
{1998.0820,1842.4736,2080.0137,1999.0541},   //VISAGE
{1651.4408,1295.1288,1726.7802,1569.1279},   //LOTNISKO
{2078.3188,1428.0557,2184.0771,1526.7725}    //ROYAL
};

new Float:checkpoints[MAX_POINTS][3] = {
{-22.2549,-55.6575,1003.5469},   	//BANK
{2000.3132,1538.6012,13.5859},		//PIRATE
{291.0004,-84.5168,1001.5156},		//AMMUNATION
{1989.0619,1005.5241,994.4688},		//DRAGON
{-103.5525,-22.4661,1000.7188},		//SEXSHOP
{501.4927,-75.4323,998.7578},		//BAR
{2235.5408,1679.0402,1008.3594},	//CALIGULA
{161.1875,-79.9915,1001.8047},		//ZIP
{207.5640,-97.8188,1005.2578}, 		//BINCO
{-203.4864,-41.2045,1002.2734},		//TATOO
{418.5547,-80.1667,1001.8047},		//BOTIQUE
{2163.3354,1904.5193,10.8125},		//STARFISH
{2392.4858,1041.2852,10.8203},		//TUNE LV
{1934.2170,1345.3629,9.9688},		//HIGH ROLLER
{2019.3564,1916.3898,12.3413}, 		//VISAGE
{1677.2045,1447.4795,10.7822},  	//LOTNISKO
{2121.8872,1486.5500,10.8203}  		//ROYAL
};

new Float:gArena[9][3]= {
{171.2280,1880.8297,20.8902},
{224.4834,1931.5679,17.6406},
{269.8601,1884.0562,17.4770},
{278.9883,1824.1399,17.6406},
{211.2068,1810.4451,21.8672},
{210.1593,1838.9865,17.6406},
{135.0183,1834.0011,17.6406},
{107.2365,1875.1182,17.8730},
{126.0669,1906.3270,18.6876}
};

new Float:SpawnGrove[3][3]= {
{-1133.1749,1093.9858,1345.7988},
{-1130.5291,1057.7830,1346.4141},
{-1132.2559,1039.0487,1345.7391}
};

new Float:SpawnBallas[3][3]= {
{-974.4026,1024.8848,1345.0425},
{-974.0859,1061.0713,1345.6749},
{-973.3613,1077.0044,1344.9951}
};

new checkpointType[MAX_POINTS] = {
	CP_BANK,
	CP_PIRATE,
	CP_AMMU,
	CP_DRAGON,
	CP_SEXSHOP,
	CP_BAR,
	CP_CALIGULA,
	CP_ZIP,
	CP_BINCO,
	CP_TATOO,
	CP_BOTIQUE,
	CP_STARFISH,
	CP_TUNELV,
	CP_HIGHROLLER,
	CP_VISAGE,
	CP_LOTNISKO,
	CP_ROYAL
};

#define MAX_PROPERTIES 14

new propertyNames[MAX_PROPERTIES][32] = {
	"Kasyno Czterech Smok�w",
	"Sex Shop",
	"Bar Shithole",
	"Kasyno Caligula's",
	"Sklep Zip",
	"Sklep Binco",
	"Salon Tatua�u",
	"Botique",
	"Kasyno Star Fish",
	"Tuning w Las Venturas",
	"Kasyno High Roller",
	"Kasyno Visage",
	"Lotnisko Las Venturas",
	"Kasyno Royal"
};

new propertyValues[MAX_PROPERTIES] = {
	80000,
	25000,
	30000,
	100000,
	20000,
	15000,
	30000,
	23000,
	200000,
	70000,
	50000,
	60000,
	300000,
	75000
};

new propertyEarnings[MAX_PROPERTIES] = {
	8000,
	2500,
	3000,
	10000,
	2000,
	1500,
	3000,
	2300,
	20000,
	7000,
	5000,
	6000,
	30000,
	7500
};

new UzylKomendykamizelka[MAX_PLAYERS];
new UzylKomendywiesniak[MAX_PLAYERS];
new UzylKomendynapraw[MAX_PLAYERS];
new UzylKomendy100hp[MAX_PLAYERS];
new UzylKomendykill[MAX_PLAYERS];
new UzylKomendyodlicz[MAX_PLAYERS];
new SkinyGrove[3] = {105,106,107};
new SkinyBallas[3] = {102,103,104};
new iSpawnSet[MAX_PLAYERS];
new bank[MAX_PLAYERS];
new bounty[MAX_PLAYERS];
new playerCheckpoint[MAX_PLAYERS];
new Float:LocX = 0.0;
new Float:LocY = 0.0;
new Float:LocZ = 0.0;
new logged[MAX_PLAYERS];
new logintimeout[MAX_PLAYERS];
new killsinarow[MAX_PLAYERS];
new Zabitych[200];
new Zgonow[200];
new Samobojstw[200];
new gPlayerName[MAX_PLAYERS][MAX_PLAYER_NAME];

new tmp2[256];
new ping,bool:timerping=true;
new bool:AntyBronie=true;
new odlicz = 1;
new Float:boomX[MAX_PLAYERS];
new Float:boomY[MAX_PLAYERS];
new Float:boomZ[MAX_PLAYERS];
new KamizelkaSpawn[200];
new Moderator[MAX_PLAYERS];
new naarenie[MAX_PLAYERS];
new pozwacept[MAX_PLAYERS];
new niespodzianka[MAX_PLAYERS];
new nawojnie[MAX_PLAYERS];
new Float:Pos[200][3];
new Bomba[200];
new ktop[200];
new Float:PosF[200][4];
new Int[200];
new bool:UzylFLO[200]=false;
new Guns[200][2][13];
new PobierzKolor[700][2];
new Menu:bronie;
new Menu:gangi;
new Menu:pistolety;
new Menu:duze;
new Menu:rzucane;


forward MoneyGrubScoreUpdate();
forward PlayerLeaveGang(playerid);
forward getCheckpointType(playerID);
forward PayPlayerInArea(playerID, Float:x1, Float:y1, Float:x2, Float:y2, cash);
forward GetPlayerId(playername[]);
forward PirateShipScoreUpdate();
forward checkpointUpdate();
forward PropertyScoreUpdate();
forward SaveData();
forward StatGivePlayerMoney(playerid, amount);
forward LoginTimeout(playerid);