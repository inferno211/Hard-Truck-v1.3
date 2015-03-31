	//include
	#include <a_samp>//podstawowa biblioteka sampa
	#include <streamer>//streamer wszystkiego by incognito :)
	#include <zcmd>//komendy zcmd
	#include <O-Files>//szybkie zapisywanie i wczytywanie danych, autor: double-o-seven
	#include <foreach>//szybkie petelki
	#include <sscanf>//komendy ;)
	#include <tune>
	#include <a_http>
	#include <D-AntyCheat>
	new blokadacmd = 1;
	forward ResetCount(playerid);
	forward ResetCommandCount(playerid);
	#define SpamLimit (3000)

    new pojazdznaleziony;
	new pojazdkonkursowy;

//definy

    #define DATA "30 grudnia 2011"
	#define NICK "[HTC]Inferno"
	#define WERSJAMAPY "1.4"

	#define Sloty 50//sloty serwa
	#define WERSJA "HardTruck 1.3"//wersja mapy
	#define MAPNAME "Hard Truck map"//nazwa w zak≥adce 'map'
	#define URL "www.Hard-Truck.pl"//nazwa w zak≥adce 'url'
	#define ROZMIAR_TEKSTU 128//d≥ugoúÊ tekstu... (kolorowanie)
	#define SZYBKOSC_SPADANIA 30 //czas w jakim bedzie spadac/podnosic o 2 punkty zmecznie. ( w sekundach )
	#define WHOMADETHIS "Stworzone przez {FF0000}In{FFEF00}fer{1A00FF}no"

	//ogÛlne definy do systemÛw
	#define LIMIT_SAMOCHODOW 3000
	#define LIMIT_LADUNKOW 100
	#define LIMIT_TEXTOW 100
	#define ILOSC_STACJI 20
	#define LIMIT_DOMOW 100

	#define ILOSC_WOZOW 100
	#define WOZY_FILE "Truck/Wozy/%d.ini"

	#define SERWER_STAT "Truck/Statystyki.ini"

	new sprawdzil[MAX_PLAYERS];
	new infernodom;
	new otwarty;
	new Text:godzina;
	new hourt, minutet, secondst;

	#define MAX_FOTORADAR 300
	#define FOTORADARY_FILE "Truck/Fotoradary/%d.ini"

	new Fotoradar[MAX_FOTORADAR];
	new Text3D: FotoradarText[MAX_FOTORADAR];
	enum FotoradarEnum
	{
	    fAktywny,
		Float: fX,
		Float: fY,
		Float: fZ,
		Float: fAng
	}
	new FotoInfo[MAX_FOTORADAR][FotoradarEnum];

	#define LA 100
	#define AUTOMATY_FILE "Truck/Automaty/%d.ini"

	new ilemadacscore[Sloty];
	new cmakogut[LIMIT_SAMOCHODOW],
	    kogut[LIMIT_SAMOCHODOW],
	    kogut2[LIMIT_SAMOCHODOW];

	new IdWozu[Sloty];
	new TworzenieWozu;
    enum privcar
	{
		cAktywny,
		cWlasciciel[64],
		cModel,
		Float: cX,
		Float: cY,
		Float: cZ,
		Float: cRX,
		cColor1,
		cColor2,
		cRespawn,
		cLock
	}
	new PrivateCar[ILOSC_WOZOW][privcar];
	new KupneWozy[ILOSC_WOZOW];

	new Text3D:Tag[Sloty];

	enum AutomatEnum
	{
		aAktywny,
		Float: aX,
		Float: aY,
		Float: aZ,
		Float: aAng
	}

	new podnosnik;
	new TworzyDomek[Sloty];
	new dikonka[LIMIT_DOMOW];

	new AutomatInfo[LA][AutomatEnum];

	new Automat[LA];

	new DB:KASA,
		DBResult:DBResult,
		query[128];

    new Text3D: dtexty[LIMIT_DOMOW];

	new pojazdpd[40];
	new pojazdpolicji[37];
	new pojazdlot[66];
	new pojazdyST[25];
	new pojazdyET[30];
	new ricowoz[30];

	new zaladowano = 0;

	new rekord;
	new teraz = 0;

	enum servInfo
	{
		sKomendy,
		sWiadomosci,
		sRestartow,
		sBan,
		sKick,
		sWarn
	};

	new SerwerInfo[servInfo];


	#define GUI_EMAIL 80
	#define GUI_OB 81

    new
		bool:PowerEnabled[MAX_PLAYERS],
		GroundExplosionTimer[MAX_PLAYERS] = { -1, ... },
		PlayerAnimLib[MAX_PLAYERS][32],
		PlayerAnimName[MAX_PLAYERS][32]
	;

	new bool:swords[Sloty];

	new AFK[Sloty];
    new PozwolenieMiecze[Sloty];
    new NaDysce[Sloty];
	new PrivCar[Sloty];
	new Pierwszy[Sloty];
	//new TimDajWoz[Sloty];
	new PrivNaczepa[Sloty];

	#pragma tabsize 0

	new juzplacil[Sloty];
	new Text:ViaTollTD[Sloty];
	new Zaplacil[Sloty];

	#define TUNE_PRICE 2000
    #define KLAN "Truck/Klan.ini"

	#define UpperToLower(%1) for ( new ToLowerChar; ToLowerChar < strlen( %1 ); ToLowerChar ++ ) if ( %1[ ToLowerChar ]> 64 && %1[ ToLowerChar ] < 91 ) %1[ ToLowerChar ] += 32

	//kolory textow
    #define KOLOR_NIEWIDZIALNY 0xFFFFFF00
	#define KOLOR_BIALY 0xFFFFFFFF
	#define KOLOR_CZARNY 0x000000FF
	#define KOLOR_ZOLTY 0xFFFF00FF
	#define KOLOR_POMARANCZOWY 0xFF8040FF
	#define KOLOR_CZERWONY 0xFF2F2FFF
	#define KOLOR_ROZOWY 0xFF80FFFF
	#define KOLOR_NIEBIESKI 0x2B95FFFF
	#define KOLOR_BRAZOWY 0x9D4F4FFF
	#define KOLOR_ZIELONY 0x00FF40FF
	#define KOLOR_TURKUSOWY 0x00FFFFFF
	#define KOLOR_SZARY 0xC0C0C0FF
	#define KOLOR_FILOETOWY 0x800040FF
	#define KOLOR_BEZOWY 0xFFFFA6FF
	#define KOLOR_BORDOWY 0x800000FF

	//kolory do zmieniania w czacie,textcie 3d
	#define C_BIALY "{FFFFFF}"
	#define C_CZARNY "{000000}"
	#define C_ZOLTY "{FFFF00}"
	#define C_POMARANCZOWY "{FF7F50}"
	#define C_CZERWONY "{FF0000}"
	#define C_ROZOWY "{FF1493}"
	#define C_NIEBIESKI "{4169E1}"
	#define C_BRAZOWY "{A0522D}"
	#define C_ZIELONY "{ADFF2F}"
	#define C_TURKUSOWY "{00FFFF}"
	#define C_SZARY "{C0C0C0}"
	#define C_FILOETOWY "{BA55D3}"
	#define C_BEZOWY "{FFDEAD}"
	#define C_BORDOWY "{B22222}"

	#define SPAWN 999999999999//czas respawnu pojazdÛw

	#define LIMIT_MISJI 5
	
	
//newy

	//pojazdy
	new nazwypojazdow[212][32]=
	{
		"Landstalker","Bravura","Buffalo","Linerunner","Pereniel","Sentinel","Dumper","Firetruck","Trashmaster","Stretch","Manana",
		"Infernus","Voodoo","Pony","Mule","Cheetah","Ambulance","Leviathan","Moonbeam","Esperanto","Taxi","Washington","Bobcat",
		"Mr Whoopee","BF Injection","Hunter","Premier","Enforcer","Securicar","Banshee","Predator","Bus","Rhino","Barracks",
		"Hotknife","Trailer","Previon","Coach","Cabbie","Stallion","Rumpo","RC Bandit","Romero","Packer","Monster","Admiral",
		"Squalo","Seasparrow","Pizzaboy","Tram","Trailer","Turismo","Speeder","Reefer","Tropic","Flatbed","Yankee","Caddy",
		"Solair","Berkley's RC Van","Skimmer","PCJ-600","Faggio","Harley","RC Baron","RC Raider","Glendale","Oceanic",
		"Sanchez","Sparrow","Patriot","Quad","Coastguard","Dinghy","Hermes","Sabre","Rustler","ZR3 50","Walton","Regina",
		"Comet","BMX","Burrito","Camper","Marquis","Baggage","Dozer","Maverick","News Chopper","Rancher","FBI Rancher",
		"Virgo","Greenwood","Jetmax","Hotring","Sandking","Blista Compact","Police Maverick","Boxville","Benson","Mesa",
		"RC Goblin","Hotring Racer","Hotring Racer","Bloodring Banger","Rancher","Super GT","Elegant","Journey","Bike",
		"Mountain Bike","Beagle","Cropdust","Stunt","Tanker","RoadTrain","Nebula","Majestic","Buccaneer","Shamal","Hydra",
		"FCR-900","NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona","FBI Truck","Willard","Forklift","Traktor",
		"Combine","Feltzer","Remington","Slamvan","Blade","Freight","Streak","Vortex","Vincent","Bullet","Clover","Sadler",
		"Firetruck","Hustler","Intruder","Primo","Cargobob","Tampa","Sunrise","Merit","Utility","Nevada","Yosemite","Windsor",
		"Monster","Monster","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RC Tiger","Flash","Tahoma","Savanna",
		"Bandito","Freight","Trailer","Kart","Mower","Duneride","Sweeper","Broadway","Tornado","AT-400","DFT-30","Huntley",
		"Stafford","BF-400","Newsvan","Tug","Trailer","Emperor","Wayfarer","Euros","Hotdog","Club","Trailer","Trailer",
		"Andromeda","Dodo","RC Cam","Launch","LS Police-Car","SF Police-Car","LV Police-Car","Police Rancher","Picador","SWAT Van",
		"Alpha","Phoenix","Glendale","Sadler","Luggage Trailer","Luggage Trailer","Stair Trailer","Boxville","Farm Plow","Utility Trailer"
	};
	new vPaliwo[LIMIT_SAMOCHODOW],
		vPaliwoMax[LIMIT_SAMOCHODOW],
		vLadownosc[LIMIT_SAMOCHODOW],vLadownoscMax[LIMIT_SAMOCHODOW],
		vCB[LIMIT_SAMOCHODOW],
		Text:Licznik[Sloty],
		Float:vPojazdZycie[MAX_VEHICLES];

    //ladunek
    enum ladunek
	{
		lAktywny,
		lTowar[64],//nazwa towaru
		Float:lTowarKoszt,//ile kasy dostajemy za 1 kg ladunku
		lZaladunek[64],//nazwa miejsca z ktorego bierzemy towar
		Float:lPosX,Float:lPosY,Float:lPosZ,
		lDostarczenie[64],//nazwa miejsca do ktorego dostarczamy towar
		Float:lPos2X,Float:lPos2Y,Float:lPos2Z,
	};
	new LadunekInfo[LIMIT_LADUNKOW][ladunek],
		bool:LadunekTworzenie=true,
		LadunekID[Sloty],LadunekPkt[Sloty];

	//texty3d
    enum txt
	{
		tAktywny,
		tNapis[64],
		Float:tPosX,Float:tPosY,Float:tPosZ,
	};
	new TextInfo[LIMIT_TEXTOW][txt],
        Text3D:TextNapis[LIMIT_TEXTOW],
		bool:TextTworzenie=true,
		TextID[Sloty],TextPkt[Sloty];


	//stacje paliw
	enum sInfo
	{
		Float:sCena,
		Float:sPosX,Float:sPosY,Float:sPosZ,Float:sOdleglosc,
	}
	new StacjaInfo[ILOSC_STACJI][sInfo];

	 //system domÛw
	enum dInfo
	{
		dAktywny,
		Float:dWejscieX,Float:dWejscieY,Float:dWejscieZ,dWejscieInt,dWejscieVir,
		Float:dWyjscieX,Float:dWyjscieY,Float:dWyjscieZ,dWyjscieInt,
		dWlasciciel[64],
		dOpis[64],
		dKupiony,
		dKoszt,
		dZamkniety,
	};

	new DomInfo[LIMIT_DOMOW][dInfo],
	    DomPickup[LIMIT_DOMOW],
		bool:DomTworzenie=true,
		DomID[Sloty],DomPkt[Sloty];

    new cp1,
		cp2,
		cp3,
		cp4,
		cp5,
		cp6,
		cp7;

	new zdawanie = 0,
		zdaje[Sloty],
		typPrawka[Sloty],
		wozekprawo;

	//reszta
    enum pInfo
	{
	    //zapisywalne do pliku
		pHaslo[64],
		pKonto,
		pAdmin,
		pPremium,
		pJail,
		pWyciszony,
		pWarny,
		pPoziom,
		pDostarczenia,
		pScigany,
		pMandat,
		pKasa,
		pBank,
		pFrakcja,
		pLider,
		pDom,
		pWizyty,
		pMisja,
		pToll,
        pEmail[64],
		pDJ,

		pPrawkoB, //Osobowe
		pPrawkoCE, //Tiry
		pPrawkoA1, //Vany

		pPunkty,

		pNazwaMisji[64],
		pIDMisji,
		pDostarczen,
		//niezapisywalne
		LoadingTimer,
		UseLoadTimer,
		DischargingTimer,
		Float: LoadX,
		Float: LoadY,
		Float: LoadZ
	};
	new PlayerInfo[Sloty][pInfo];

	new Text:Naczepa[Sloty],
		bool:Zalogowany[Sloty],
		bool:Regulamin[Sloty],
		TankowanePaliwo[Sloty],
		bool:BlokadaPW[Sloty],
		bool:Lista[Sloty],
		Text:Napis,
	    NapisUzywany=0,
	    NapisTimer,
     	NaprawTimer[Sloty],
	    MandatPD[Sloty],
	    bool:Podglad=false,
		bool:Spec[Sloty],
		MuteTimer[Sloty];
		//misje
	new	bool:Misja[Sloty],
		MisjaID[Sloty],
		MisjaPojazd[Sloty],
		MisjaStopien[Sloty],
		bool:Przeladowany[Sloty],
		OstatniaMisja[Sloty];
		//kierunkowskazy
	new bool:Kierunkowskaz[Sloty],
		Text3D:Kierunek[Sloty];
		//blokady
	new Blokady=0,
		Blokadka[15];
		//kolczatki
	new	Kolczatki=0,
		bool:Kolczatka[5],
		KolczatkaObiekt[5],
		Float:KolPosX[5],Float:KolPosY[5],Float:KolPosZ[5];

    new dstring[200],
		Godzina;

	//NEWY DO TIMER”W

	//do licznika
	new lPojazd,
		Float:lPojazdHP,
		lText[7],
		engine,lights,alarm,doors,bonnet,boot,objective;

	new PaliwoLicznik=0;
	//
	new mstr[20];//ma≥y string

	#define DIALOG_PD_OPEN      		5001
	#define DIALOG_PD_CLOSE     		5002
	#define GUI_TARYFIKATOR     		5003
	#define NEON                		5004
	#define RADIO_POLECANE      		5005
	#define GUI_POJAZD          		5006
	#define DIALOG_SALON 				5007
	#define DIALOG_SALON_DOSTAWCZE  	5008
	#define DIALOG_SALON_TRUCKI 		5009
	#define DIALOG_SALON_NACZEPA		5010
	#define GUI_VIATOLL 				5011
	#define GUI_VIATOLL1                5013
	#define GUI_VIATOLL2 				5017
	#define LOAD_DIALOG         		5018
	#define CARGOS_DIALOG       		5019
	#define WEIGHT_DIALOG       		5020
	#define WEIGHT2_DIALOG      		5021
	#define DISCHARGE_DIALOG    		5022
	#define MIECZE              		5023
	#define PANEL_DJ            		5024
	#define GUI_NIEKUPIONE 				5025
	#define GUI_MENUCAR         		5026
	#define GUI_MENUCAR_RESPAWNTIME 	5027
	#define GUI_BRAK                    5028
	#define GUI_ZLECENIE                5029
	#define GUI_ANULUJ                  5030
	#define ZDAWANIE_PYTANIE            5031
	#define PYTANIE1                    5032
	#define PYTANIE2                    5033
	#define PYTANIE3                    5034
	#define PYTANIE4                    5035
	#define PYTANIE5                    5036
	#define KATEGORIA                   5037
	#define TARYFIK                     5038
	#define PANEL_DJ_URL                5039
	#define PANEL_DJ_CH                 5040
	#define GUI_ZLECENIE_LOT            5041
	#define GUI_ZLECENIE_ST             5042
	#define U2BDIAG						6958

	new PlayerU2B[MAX_PLAYERS];
	new PlayerU2BLink[MAX_PLAYERS][32];
	new U2BRadius[MAX_PLAYERS][16];
	forward U2BInfo(playerid, response_code, data[]);

	#define B 1
	#define CE 2
	#define A1 3

	new Text:box[Sloty];
	new Text:typr[Sloty];
	new Text:stacja[Sloty];
	new Text:volumemax[Sloty];
	new Text:TarBox[Sloty];
	new Text:Taryfa[Sloty];
	new Text:Nal[Sloty];


	new TarTim[Sloty];
	new Naleznosc[Sloty];
	#define function%0(%1) forward%0(%1); public%0(%1)

	new VNaprawTimer[Sloty];
	//vip
    new forma[80];
    new PVeh[Sloty];

#define MAX_ZONE_NAME 28

new Text:Zones[MAX_PLAYERS];

new Text:ReklamaTD;
new Text:NapisFirma[Sloty];
new Text:FirmaNazwa[Sloty];
new Text:FirmaMisja[Sloty];
new Text:FirmaDost[Sloty];
new Text:FirmaPoziom[Sloty];

new Text:zycie[Sloty];
new Text:armour[Sloty];
new Text:score[Sloty];

new ViaTollTextDraw[MAX_PLAYERS];


forward Zones_Update();

enum SAZONE_MAIN { //Betamaster
		SAZONE_NAME[28],
		Float:SAZONE_AREA[4]
};

static const gSAZones[][SAZONE_MAIN] =
{
	{"Piatkowo (PTKWO)",	                { 2718.181,  2296.066, -1152.865, -1729.235}},
	{"Lawica",                      		{ 1708.783,  1193.343,  1871.665,  1156.073}},
	{"13 Dzielnica",                      	{-1730.301, -2143.608,  353.4189, -198.8761}},
	{"Slawkow",                      		{ 175.1681, -397.0478,  1296.244,  957.5858}},
	{"Choroszcz",                      		{ 1004.297,  291.9469,  1179.465,  700.6725}},
	{"West Theif",                          { 2269.447,  1839.726, -1117.335, -1468.684}}
};

//podstawowe callbaki samp

main()//funkcja wyswietlajaca wiadomosc poczatkowa
{
	printf(" \n\n\n%s\nby Inferno\n\n\n ",WERSJA);
}

//system za≥adnkowy
/*#define MAX_POINTS 49

enum CP_MAIN
{
	Float:coordX,
	Float:coordY,
	Float:coordZ,
	Float:Size,
	Float:Distance
};

new Float:gCheckpoints[MAX_POINTS][CP_MAIN] =
{
	{1693.1924,1639.1239,10.5577, 3.0, 20.0},
	{2821.7622,2605.9915,10.8203, 3.0, 20.0},
	{978.4063, 2097.9084,10.8203, 3.0, 20.0},
	{621.4365,871.6871,-42.9609, 3.0, 20.0},
	{-2039.7074,-2384.6646,30.6250, 3.0, 20.0},
	{-2171.6145,-210.7355,35.3203, 3.0, 20.0},
	{-1693.0688,26.4203,3.5547, 3.0, 20.0},
	{-2433.1855,2298.9460,4.9844, 3.0, 20.0},
	{2761.1680,-2391.8877,13.3599, 3.0, 20.0},
	{2073.3105,-2234.3032,13.2740, 3.0, 20.0},
	{2187.2546,-2263.6301,13.1984, 3.0, 20.0},
	{873.5506,-1256.3068,14.7350, 3.0, 20.0},
	{-1044.9138,-644.4881,31.7349, 3.0, 20.0},
	{-1046.9347,-1156.9359,127.6371, 3.0, 20.0},
	{-1264.0833,-402.4480,14.1600, 3.0, 20.0},
	{-2078.4800,213.0442,35.3230, 3.0, 20.0},
	{-2517.9575,-612.3046,132.5794, 3.0, 20.0},
	{-2354.1445,-1637.0999,483.7025, 3.0, 20.0},
	{-1300.3336,2506.8269,87.1869, 3.0, 20.0},
	{-520.8759,2593.0227,53.6498, 3.0, 20.0},
	{268.8903,1410.6411,10.6376, 3.0, 20.0},
	{2468.7148,1934.8610,10.0187, 3.0, 20.0},
	{2707.6196,855.4386,10.3197, 3.0, 20.0},
	{-479.5117,-55.4943,60.3753, 3.0, 20.0},
	{2183.0000,-1981.9198,13.5515, 3.0, 20.0},
	{-755.5800,-156.5414,66.6758, 3.0, 20.0},
	{640.6879,1218.4763,11.4448, 3.0, 20.0},
	{-373.4811,1559.4572,75.2923, 3.0, 20.0},
	{2525.5620,2816.9324,10.4800, 3.0, 20.0},
	{1701.8314,1040.4697,10.8203, 3.0, 20.0},
	{-1877.2723,-1680.3555,21.7500, 3.0, 20.0},
	{1253.4032,-1265.6023,13.3666, 3.0, 20.0},
	{1683.9310,2319.8955,10.8203, 3.0, 20.0},
	{1082.6799,1888.2157,10.8203, 3.0, 20.0},
	{-2461.7603,786.0463,35.1719, 3.0, 20.0},
	{-1834.2552,1422.9844,7.1875, 3.0, 20.0},
	{2347.4297,2754.3359,10.8203, 3.0, 20.0},
	{106.4272,-165.5344,2.0364, 3.0, 20.0},
	{313.3841,-240.9951,1.5781, 3.0, 20.0},
	{1336.2332,286.5710,19.5615, 3.0, 20.0},
	{844.8580,-594.7557,18.1477, 3.0, 20.0},
	{2913.7258300781, 2554.4924316406, 10.8203125, 3.0, 20.0},
	{1901.1040039063, 118.00833892822, 35.511837005615, 3.0, 20.0},
	{-1515.4927978516, 2191.4108886719, 50.81783676147, 3.0, 20.0},
	{2789.00000000,1200.90002441,10.80000019, 3.0, 20.0},
	{2767.50000000,1199.59960938,10.80000019, 3.0, 20.0},
	{2810.10009766,1200.59997559,10.80000019, 3.0, 20.0},
	{2684.50000000,2602.69995117,10.50000000, 3.0, 20.0},
	{2683.89941406,2584.50000000,10.50000000, 3.0, 20.0}
};

//new cCheckpoints[MAX_POINTS];
*/
enum vInfo
{
	bool: vCargo,
	vTypeCargo,
	vTimeCargo,
	TimeCargo,
	vWeight,
	Float: LoadX,
	Float: LoadY,
	Float: LoadZ,
	Float: DischargeX,
	Float: DischargeY,
	Float: DischargeZ
};

new VehicleInfo[LIMIT_SAMOCHODOW][vInfo];

public OnGameModeInit()
{
	KASA = db_open("Kasa.db");
	db_free_result(db_query(KASA, "CREATE TABLE IF NOT EXISTS `Gracze` (`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,`login` VARCHAR(32) NOT NULL,`Kasa` INT(5) NOT NULL DEFAULT 0);"));

	SendRconCommand("loadfs obiekty");

//podstawowe ustw.
    new str[30];
	format(str,sizeof(str),"%s",WERSJA);
    SetGameModeText(str);//zmienia nazwe gamemode
    format(str,sizeof(str),"mapname %s",MAPNAME);
    SendRconCommand(str);//zmienia nazwe mapname
	format(str,sizeof(str),"weburl %s",URL);
	SendRconCommand(str);//zmienia weburl


    otwarty = 0;
	podnosnik = CreateObject(980, 1045.3994140625, 1310.8994140625, 9.8999996185303, 90, 0, 90);
	SetTimer("Zones_Update", 500, 1);
	
    cp1 = CreateDynamicRaceCP(0, 1145.659179, 1251.472412, 10.820312, 1135.073974, 1261.957763, 10.820312, 5, -1, -1, -1, 100.0);
	cp2 = CreateDynamicRaceCP(0, 1135.073974, 1261.957763, 10.820312, 1146.599243, 1274.050537, 10.820312, 5, -1, -1, -1, 100.0);
	cp3 = CreateDynamicRaceCP(0, 1146.599243, 1274.050537, 10.820312, 1134.179077, 1284.447509, 10.820312, 5, -1, -1, -1, 100.0);
	cp4 = CreateDynamicRaceCP(0, 1134.179077, 1284.447509, 10.820312, 1148.381958, 1296.700439, 10.820312, 5, -1, -1, -1, 100.0);
	cp5 = CreateDynamicRaceCP(0, 1148.381958, 1296.700439, 10.820312, 1137.237060, 1305.038696, 10.820312, 5, -1, -1, -1, 100.0);
	cp6 = CreateDynamicRaceCP(0, 1137.237060, 1305.038696, 10.820312, 1140.645019, 1320.234008, 10.820312, 5, -1, -1, -1, 100.0);
	cp7 = CreateDynamicRaceCP(1, 1140.645019, 1320.234008, 10.820312, 1140.645019, 1320.234008, 10.820312, 5, -1, -1, -1, 100.0);

	
	infernodom = CreateObject(980, 1245.38, -767.19, 93.78,   0.00, 0.00, 179.74);
	
	CreateDynamicObject(987, 1239.18, -767.34, 91.27,   0.00, 0.00, 271.83);
	CreateDynamicObject(987, 1263.02, -766.91, 90.93,   0.00, 0.00, 179.99);
	CreateDynamicObject(987, 1262.84, -778.81, 90.93,   0.00, 0.00, 89.78);
	CreateDynamicObject(987, 1303.70, -813.59, 83.12,   0.00, 0.00, 90.46);
	CreateDynamicObject(987, 1303.68, -804.60, 83.12,   0.00, 0.00, 90.46);
	CreateDynamicObject(987, 1283.05, -833.68, 82.13,   0.00, 0.00, 0.00);
	CreateDynamicObject(987, 1294.81, -833.69, 82.13,   0.00, 0.00, 90.65);
	CreateDynamicObject(987, 1271.11, -833.67, 82.13,   0.00, 0.00, 0.00);
	CreateDynamicObject(987, 1268.09, -833.65, 82.13,   0.00, 0.00, 0.00);
	CreateDynamicObject(987, 1268.65, -821.58, 82.13,   0.00, 0.00, 270.00);
	CreateObject(4514, 423.25, 611.88, 19.63,   -1.48, 0.00, 35.02);

    for(new i=0; i<MAX_PLAYERS; i++)
	{
	   	Zones[i] = TextDrawCreate(441.000000, 383.000000, "_");
		TextDrawBackgroundColor(Zones[i], 255);
		TextDrawFont(Zones[i], 1);
		TextDrawLetterSize(Zones[i], 0.430000, 1.000000);
		TextDrawColor(Zones[i], -1);
		TextDrawSetOutline(Zones[i], 1);
		TextDrawSetProportional(Zones[i], 1);
		TextDrawUseBox(Zones[i], 1);
		TextDrawBoxColor(Zones[i], 96);
		TextDrawTextSize(Zones[i], 636.000000, 0.000000);
	}

	Godzina=6;
	SetWorldTime(Godzina);//ustawia godzine
	AllowInteriorWeapons(true);//bronie w budynkach
	DisableInteriorEnterExits();//usuwa teleporty do interiorow
	EnableStuntBonusForAll(false);//nie dodaje kasy za stunt
	ShowPlayerMarkers(true);//wyswietla graczy na mapie
	ShowNameTags(true);//wyswietla nick
	SetNameTagDrawDistance(25);//odlegosc widzenia nicku

//timery
    DestACOn();//uruchamia mojego anty cheata
    SetTimer("LicznikTimer",500,true);
    SetTimer("PaliwoMinus",20000,true);
    SetTimer("CoMinute",60000,true);//co minute
    SetTimer("ZmienCzas",60000*5,true);//co 5 minut
    SetTimer("Reklama",60000*6,true);//co 6 minut

//skiny
	//trukerzy
	AddPlayerClass(0, 	-189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//0
	AddPlayerClass(7, 	-189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//1
	AddPlayerClass(30, 	-189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//2
	AddPlayerClass(67, 	-189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//3
	AddPlayerClass(101, -189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//4
	AddPlayerClass(217, -189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//5
	AddPlayerClass(299, -189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//6
	AddPlayerClass(272, -189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//7
	//laski
	AddPlayerClass(233, -189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//8
	AddPlayerClass(93, 	-189.6111,	-307.9127,	2.4297,	315.3905, 0, 0, 0, 0, 0, 0);//9
	//policja
	AddPlayerClass(280, -127.77,	1040.24,	19.52,	315.3905, 0, 0, 0, 0, 0, 0);//10
	AddPlayerClass(282, -127.77,	1040.24,	19.52,	315.3905, 0, 0, 0, 0, 0, 0);//11
	AddPlayerClass(283, -127.77,	1040.24,	19.52,	315.3905, 0, 0, 0, 0, 0, 0);//12
	AddPlayerClass(265, -127.77,	1040.24,	19.52,	315.3905, 0, 0, 0, 0, 0, 0);//13
	AddPlayerClass(266, -127.77,	1040.24,	19.52,	315.3905, 0, 0, 0, 0, 0, 0);//14
	AddPlayerClass(284, -127.77,	1040.24,	19.52,	315.3905, 0, 0, 0, 0, 0, 0);//15
	//pomoc drogowa
	AddPlayerClass(27, 	1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//16
	AddPlayerClass(16, 	1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//17
	AddPlayerClass(8, 	1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//18
	AddPlayerClass(56, 	1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//19
	//pomoc drogowa
	AddPlayerClass(61, 	1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//20
	AddPlayerClass(171, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//21
	AddPlayerClass(172, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//22
	//speed trans
	AddPlayerClass(126, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//23
	AddPlayerClass(128, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//24
	//speed trans
	AddPlayerClass(3, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//25
	AddPlayerClass(20, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//26
	//taxi
	AddPlayerClass(86, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//27
	AddPlayerClass(93, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//28
	//rico
	AddPlayerClass(233, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//29
	AddPlayerClass(294, 1427.79,	672.37,		10.46,	315.3905, 0, 0, 0, 0, 0, 0);//30



//ikony
 	//miejsca z tirami
	CreateDynamicMapIcon(2326.9631,2785.5002,10.8203,51,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(1636.6249,1038.6071,10.8203,51,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(252.8059,1354.8419,10.7075,51,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-49.9214,-277.7625,5.4297,51,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-501.8290,-518.0654,25.5234,51,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-1710.3651,403.0952,7.4190,51,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-79.4036,-1135.6272,1.0781,51,1,-1,-1,-1,300.0);
	//ikony pcn
	CreateDynamicMapIcon(-1328.6442,2677.4944,49.7787,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-737.3889,2742.2444,46.8992,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-1475.6040,1863.6361,32.3494,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(70.2113,1218.4081,18.5282,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(611.5366,1694.5262,6.7086,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(1596.3970,2197.1189,10.5371,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(2199.8953,2477.1919,10.5369,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(2640.4731,1104.9952,10.5366,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(2115.5632,923.1831,10.5362,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(1380.8798,456.7491,19.6220,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(652.3244,-569.8619,16.0465,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(1003.0161,-939.9588,41.8959,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(1944.4365,-1773.8070,13.1072,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-89.2281,-1164.0281,2.0001,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-1606.3033,-2713.9014,48.2523,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-2244.0728,-2560.5244,31.6372,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-2029.6616,157.3720,28.5526,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-2414.1677,976.4759,45.0135,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(2150.0823,2748.0471,10.8203,55,1,-1,-1,-1,300.0);
	CreateDynamicMapIcon(-1674.9819,413.9892,7.1797,55,1,-1,-1,-1,300.0);

	//textdrawy
	for(new p = 0; p < Sloty; p++)
	{

	    ViaTollTD[p] = TextDrawCreate(310.000000, 348.000000, "-");
		TextDrawBackgroundColor(ViaTollTD[p], 255);
		TextDrawFont(ViaTollTD[p], 1);
		TextDrawLetterSize(ViaTollTD[p], 0.970000, 3.900000);
		TextDrawColor(ViaTollTD[p], -1);
		TextDrawSetOutline(ViaTollTD[p], 0);
		TextDrawSetProportional(ViaTollTD[p], 1);
		TextDrawSetShadow(ViaTollTD[p], 1);


		Licznik[p] = TextDrawCreate(536.000000,399.000000," ");
		TextDrawUseBox(Licznik[p],1);
		TextDrawBoxColor(Licznik[p],0x00000066);
		TextDrawTextSize(Licznik[p],636.000000,0.000000);
		TextDrawAlignment(Licznik[p],0);
		TextDrawFont(Licznik[p],1);
		TextDrawLetterSize(Licznik[p],0.199999,1.000000);
		TextDrawColor(Licznik[p],0xffffffff);
		TextDrawSetOutline(Licznik[p],1);
		TextDrawSetProportional(Licznik[p],1);
		TextDrawSetShadow(Licznik[p],1);
/*
		NapisLadunek[p] = TextDrawCreate(183.000000, 419.000000, " ");
		TextDrawBackgroundColor(NapisLadunek[p], 255);
		TextDrawFont(NapisLadunek[p], 1);
		TextDrawLetterSize(NapisLadunek[p], 0.200000, 1.000000);
		TextDrawColor(NapisLadunek[p], -1);
		TextDrawSetOutline(NapisLadunek[p], 1);
		TextDrawSetProportional(NapisLadunek[p], 1);

		NapisLevel[p] = TextDrawCreate(179.000000, 408.000000, " ");
		TextDrawBackgroundColor(NapisLevel[p], 255);
		TextDrawFont(NapisLevel[p], 3);
		TextDrawLetterSize(NapisLevel[p], 0.439999, 1.000000);
		TextDrawColor(NapisLevel[p], -1);
		TextDrawSetOutline(NapisLevel[p], 1);
		TextDrawSetProportional(NapisLevel[p], 1);
*/

		//firma
		NapisFirma[p] = TextDrawCreate(441.000000, 399.000000, "~y~Firma                                                                                                                        ");
		TextDrawBackgroundColor(NapisFirma[p], 255);
		TextDrawFont(NapisFirma[p], 1);
		TextDrawLetterSize(NapisFirma[p], 0.289999, 0.799998);
		TextDrawColor(NapisFirma[p], -1);
		TextDrawSetOutline(NapisFirma[p], 1);
		TextDrawSetProportional(NapisFirma[p], 1);
		TextDrawUseBox(NapisFirma[p], 1);
		TextDrawBoxColor(NapisFirma[p], 101);
		TextDrawTextSize(NapisFirma[p], 528.000000, 0.000000);

		FirmaNazwa[p] = TextDrawCreate(442.000000, 407.000000, "Nazwa: ~r~Brak");
		TextDrawBackgroundColor(FirmaNazwa[p], 255);
		TextDrawFont(FirmaNazwa[p], 1);
		TextDrawLetterSize(FirmaNazwa[p], 0.230000, 0.899999);
		TextDrawColor(FirmaNazwa[p], -1);
		TextDrawSetOutline(FirmaNazwa[p], 1);
		TextDrawSetProportional(FirmaNazwa[p], 1);

		FirmaMisja[p] = TextDrawCreate(441.000000, 416.000000, "Misja: ~r~Brak");
		TextDrawBackgroundColor(FirmaMisja[p], 255);
		TextDrawFont(FirmaMisja[p], 1);
		TextDrawLetterSize(FirmaMisja[p], 0.219999, 1.000000);
		TextDrawColor(FirmaMisja[p], -1);
		TextDrawSetOutline(FirmaMisja[p], 1);
		TextDrawSetProportional(FirmaMisja[p], 1);

		FirmaDost[p] = TextDrawCreate(442.000000, 426.000000, "Dostarczen: ~r~0/0");
		TextDrawBackgroundColor(FirmaDost[p], 255);
		TextDrawFont(FirmaDost[p], 1);
		TextDrawLetterSize(FirmaDost[p], 0.189999, 1.000000);
		TextDrawColor(FirmaDost[p], -1);
		TextDrawSetOutline(FirmaDost[p], 1);
		TextDrawSetProportional(FirmaDost[p], 1);

		FirmaPoziom[p] = TextDrawCreate(442.000000, 435.000000, "Poziom: ~g~0");
		TextDrawBackgroundColor(FirmaPoziom[p], 255);
		TextDrawFont(FirmaPoziom[p], 1);
		TextDrawLetterSize(FirmaPoziom[p], 0.209998, 0.899999);
		TextDrawColor(FirmaPoziom[p], -1);
		TextDrawSetOutline(FirmaPoziom[p], 1);
		TextDrawSetProportional(FirmaPoziom[p], 1);


  		Naczepa[p] = TextDrawCreate(4.000000, 435.000000, "~y~Towar: ~g~Telewizory ~y~Waga: ~g~39t");
		TextDrawBackgroundColor(Naczepa[p], 255);
		TextDrawFont(Naczepa[p], 3);
		TextDrawLetterSize(Naczepa[p], 0.420000, 1.100000);
		TextDrawColor(Naczepa[p], -1);
		TextDrawSetOutline(Naczepa[p], 1);
		TextDrawSetProportional(Naczepa[p], 1);
	}

	Napis = TextDrawCreate(38.000000,309.000000," ");
	TextDrawAlignment(Napis,0);
	TextDrawBackgroundColor(Napis,0x000000ff);
	TextDrawFont(Napis,1);
	TextDrawLetterSize(Napis,0.199999,1.000000);
	TextDrawColor(Napis,0xffffffff);
	TextDrawSetOutline(Napis,1);
	TextDrawSetProportional(Napis,1);
	TextDrawSetShadow(Napis,1);

	for(new n = 0; n < Sloty; n++)
	{
	box[n] = TextDrawCreate(378.000000, 1.000000, "                                                            ");
	TextDrawBackgroundColor(box[n], 255);
	TextDrawFont(box[n], 1);
	TextDrawLetterSize(box[n], 0.500000, 1.000000);
	TextDrawColor(box[n], -1);
	TextDrawSetOutline(box[n], 0);
	TextDrawSetProportional(box[n], 1);
	TextDrawSetShadow(box[n], 1);
	TextDrawUseBox(box[n], 1);
	TextDrawBoxColor(box[n], 85);
	TextDrawTextSize(box[n], 491.000000, 0.000000);

	typr[n] = TextDrawCreate(377.000000, 1.000000, "~b~typ: ~w~brak");
	TextDrawBackgroundColor(typr[n], 255);
	TextDrawFont(typr[n], 1);
	TextDrawLetterSize(typr[n], 0.330000, 1.000000);
	TextDrawColor(typr[n], -1);
	TextDrawSetOutline(typr[n], 0);
	TextDrawSetProportional(typr[n], 1);
	TextDrawSetShadow(typr[n], 1);

	stacja[n] = TextDrawCreate(377.000000, 10.000000, "~b~stacja: ~w~brak");
	TextDrawBackgroundColor(stacja[n], 255);
	TextDrawFont(stacja[n], 1);
	TextDrawLetterSize(stacja[n], 0.310000, 1.100000);
	TextDrawColor(stacja[n], -1);
	TextDrawSetOutline(stacja[n], 0);
	TextDrawSetProportional(stacja[n], 1);
	TextDrawSetShadow(stacja[n], 1);

	volumemax[n] = TextDrawCreate(377.000000, 20.000000, "~y~volume: ~w~40%");
	TextDrawBackgroundColor(volumemax[n], 255);
	TextDrawFont(volumemax[n], 1);
	TextDrawLetterSize(volumemax[n], 0.290000, 1.000000);
	TextDrawColor(volumemax[n], -1);
	TextDrawSetOutline(volumemax[n], 0);
	TextDrawSetProportional(volumemax[n], 1);
	TextDrawSetShadow(volumemax[n], 1);

	TarBox[n] = TextDrawCreate(37.000000, 290.000000, "                                                  ");
	TextDrawBackgroundColor(TarBox[n], 255);
	TextDrawFont(TarBox[n], 1);
	TextDrawLetterSize(TarBox[n], 0.500000, 1.000000);
	TextDrawColor(TarBox[n], -1);
	TextDrawSetOutline(TarBox[n], 0);
	TextDrawSetProportional(TarBox[n], 1);
	TextDrawSetShadow(TarBox[n], 1);
	TextDrawUseBox(TarBox[n], 1);
	TextDrawBoxColor(TarBox[n], 102);
	TextDrawTextSize(TarBox[n], 135.000000, 0.000000);

	Taryfa[n] = TextDrawCreate(38.000000, 290.000000, "~y~taryfa: ~w~brak");
	TextDrawBackgroundColor(Taryfa[n], 255);
	TextDrawFont(Taryfa[n], 1);
	TextDrawLetterSize(Taryfa[n], 0.320000, 1.300000);
	TextDrawColor(Taryfa[n], -1);
	TextDrawSetOutline(Taryfa[n], 1);
	TextDrawSetProportional(Taryfa[n], 1);

	Nal[n] = TextDrawCreate(38.000000, 304.000000, "~y~naleznosc: ~w~0$");
	TextDrawBackgroundColor(Nal[n], 255);
	TextDrawFont(Nal[n], 1);
	TextDrawLetterSize(Nal[n], 0.320000, 1.300000);
	TextDrawColor(Nal[n], -1);
	TextDrawSetOutline(Nal[n], 1);
	TextDrawSetProportional(Nal[n], 1);
	
	}

	ReklamaTD = TextDrawCreate(464.000000, 1.000000, "~r~www.~b~H~r~ard-~b~T~r~ruck.pl");
	TextDrawBackgroundColor(ReklamaTD, 255);
	TextDrawFont(ReklamaTD, 1);
	TextDrawLetterSize(ReklamaTD, 0.539999, 2.099999);
	TextDrawColor(ReklamaTD, -1);
	TextDrawSetOutline(ReklamaTD, 0);
	TextDrawSetProportional(ReklamaTD, 1);
	TextDrawSetShadow(ReklamaTD, 1);
	
	godzina = TextDrawCreate(545.000000, 20.000000, "24~g~:~w~00~g~:~w~00");
	TextDrawBackgroundColor(godzina, 255);
	TextDrawFont(godzina, 1);
	TextDrawLetterSize(godzina, 0.400000, 2.700000);
	TextDrawColor(godzina, -1);
	TextDrawSetOutline(godzina, 1);
	TextDrawSetProportional(godzina, 1);

    CreateWozy();

//petla na pojazdy
	for(new nr = 1; nr < LIMIT_SAMOCHODOW; nr++)
	{
		SetVehicleParamsEx(nr,false,false,false,false,false,false,false);
		if(nr>54) vCB[nr]=19;
		UstalPaliwo(nr);
		UstalLadownosc(nr);
		vPojazdZycie[nr]=1000.0;
		VehicleInfo[nr][vCargo] = false;
		VehicleInfo[nr][vTypeCargo] = -1;
		cmakogut[nr] = 0;
	}

//wczytuje wszystkie dane
	WczytajStacje();
	//WczytajLadunki();
	WczytajTexty();
	WczytajDomy();
	WczytajWozy();
	LadujFotoradary();
	SendRconCommand("loadfs obiekty");

	if(!DOF_FileExists(SERWER_STAT))
	{
	    SerwerInfo[sKomendy] = 0;
	    SerwerInfo[sWiadomosci] = 0;
	    SerwerInfo[sRestartow] = 0;
	    SerwerInfo[sBan] = 0;
	    SerwerInfo[sKick] = 0;
	    SerwerInfo[sWarn] = 0;
	    DOF_CreateFile(SERWER_STAT);
		DOF_SetInt(SERWER_STAT, "Komendy", SerwerInfo[sKomendy]);
	    DOF_SetInt(SERWER_STAT, "Wiadomosci", SerwerInfo[sWiadomosci]);
	    DOF_SetInt(SERWER_STAT, "Restartow", SerwerInfo[sRestartow]);
	    DOF_SetInt(SERWER_STAT, "Ban", SerwerInfo[sBan]);
	    DOF_SetInt(SERWER_STAT, "Kick", SerwerInfo[sKick]);
	    DOF_SetInt(SERWER_STAT, "Warn", SerwerInfo[sWarn]);
	    DOF_SaveFile();
	}
	else
	{
	    SerwerInfo[sKomendy] = DOF_GetInt(SERWER_STAT, "Komendy");
	    SerwerInfo[sWiadomosci] = DOF_GetInt(SERWER_STAT, "Wiadomosci");
	    SerwerInfo[sRestartow] = DOF_GetInt(SERWER_STAT, "Restartow");
	    SerwerInfo[sBan] = DOF_GetInt(SERWER_STAT, "Ban");
	    SerwerInfo[sKick] = DOF_GetInt(SERWER_STAT, "Kick");
	    SerwerInfo[sWarn] = DOF_GetInt(SERWER_STAT, "Warn");

	}

	if(!DOF_FileExists(KLAN))
	{
	    DOF_CreateFile(KLAN);
	}

	rekord = DOF_GetInt("Truck/Statystyki.ini", "Rekord");

	return 1;
}

public OnGameModeExit()
{
	DOF_SetInt("Truck/Statystyki.ini", "Rekord", rekord);
    SerwerInfo[sRestartow]++;

    DestroyAllDynamicObjects();
    for(new i=0; i<MAX_PLAYERS; i++){
    TextDrawHideForPlayer(i, Zones[i]);}

    DOF_SetInt(SERWER_STAT, "Komendy", SerwerInfo[sKomendy]);
    DOF_SetInt(SERWER_STAT, "Wiadomosci", SerwerInfo[sWiadomosci]);
    DOF_SetInt(SERWER_STAT, "Restartow", SerwerInfo[sRestartow]);
    DOF_SetInt(SERWER_STAT, "Ban", SerwerInfo[sBan]);
    DOF_SetInt(SERWER_STAT, "Kick", SerwerInfo[sKick]);
    DOF_SetInt(SERWER_STAT, "Warn", SerwerInfo[sWarn]);
    DOF_Exit();
   	for(new nr = 1; nr < LIMIT_SAMOCHODOW; nr++)
	{
		DestroyVehicle(nr);
	}
	for(new nr = 0; nr < ILOSC_WOZOW; nr++)
	{
	    DestroyVehicle(KupneWozy[nr]);
	}
	SendRconCommand("unloadfs obiekty");
	DestACOff();
	return 1;
}

//timery

forward ZmienCzas();
public ZmienCzas()
{
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_BEZOWY"Zapraszamy na "C_ZIELONY"www.Hard-Truck.pl"C_BEZOWY"!");
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_BEZOWY"Nie wiesz co robiÊ na serwerze? Pisz "C_ZIELONY"/info"C_BEZOWY"!");
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_BEZOWY"Posiadamy system Vip'a! Pisz "C_ZIELONY"/vip"C_BEZOWY" by uzyskaÊ wiÍcej informacji!");
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_BEZOWY"Spis nowoúci na serwerze znajdziesz pod "C_ZIELONY"/news"C_BEZOWY"!");
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_BEZOWY"Wszystkie dane serwera zosta≥y zapisane!");
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_BEZOWY"Na serwerze jest system zleceÒ dostÍpny pod "C_ZIELONY"/zlecenie"C_BEZOWY"!");
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_BEZOWY"Serwerowy "C_NIEBIESKI"TeamSpeak3"C_BEZOWY" juø jest! IP: "C_ZIELONY"ts8.net-speak.pl:6320"C_BEZOWY"!");
    SendClientMessageToAll(KOLOR_BIALY, ""C_CZERWONY"*** "C_ZIELONY"Plebiscyt 2011 juø trwa na "C_ZOLTY"www.Hard-Truck.pl/plebiscyt.html"C_ZIELONY"!");
	foreach(Player, i)
	    ZapiszKonto(i);

	Godzina++;
	if(Godzina>24)
	{
	     Godzina=1;
	}
	SetWorldTime(Godzina);
	format(mstr,sizeof(mstr),"~r~%d:00",Godzina);
	GameTextForAll(mstr,5000,1);
	return 1;
}

forward CoMinute();
public CoMinute()
{
	foreach(Player,i)
	{
	    if(Zalogowany[i]==true)
	    {
	        dDodajHP(i,-2);
	        if(dWyswietlHP(i)<20)
	        {
	            SendClientMessage(i, KOLOR_ZIELONY, "TwÛj stan HP jest bardzo niski! Jedz do automatu i zregeneruj je. Automat jest na kaødym spawnie i LV-Lot.");
			}
	        if(PlayerInfo[i][pJail]>=1)
	        {
	            PlayerInfo[i][pJail]--;
	            if(PlayerInfo[i][pJail]<1)
	            {
	                PlayerInfo[i][pJail]=0;
   					SetPlayerWorldBounds(i, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
   					CallLocalFunction("OnPlayerSpawn", "i",i);
	            }
				else
				{
	            	format(mstr, sizeof(mstr), "~w~jail: ~r~%d min",PlayerInfo[i][pJail]);
	            	GInfo(i,mstr,1);
				}
	        }
	        ZapiszKonto(i);
        }//jesli gracz jest zalogowany
	}
	return 1;
}

forward OdZmecz(playerid);
public OdZmecz(playerid)
{
    TogglePlayerControllable(playerid,1);
    GInfo(playerid, "~g~Obudziles sie...", 3);
    return 1;
}

forward PaliwoMinus();
public PaliwoMinus()
{
	PaliwoLicznik++;
	for(new nr = 1; nr < LIMIT_SAMOCHODOW; nr++)
	{
		GetVehicleParamsEx(nr,engine,lights,alarm,doors,bonnet,boot,objective);
		if(engine&&vPaliwo[nr]>=1)
    	{
    	    if(PaliwoLicznik==1)
    	    {
				if(GetVehicleModel(nr)==403||GetVehicleModel(nr)==514||GetVehicleModel(nr)==515)//ciÍøarowe
				{
     				vPaliwo[nr]--;
     			}
			}
			else if(PaliwoLicznik==2)
			{
			    vPaliwo[nr]--;
			}
        }
	}
	if(PaliwoLicznik >= 2) PaliwoLicznik=0;
	return 1;
}

forward LicznikTimer();
public LicznikTimer()
{
	foreach(Player,i)
	{
	    if(GetPlayerState(i)==PLAYER_STATE_DRIVER)
		{
		    lPojazd=GetPlayerVehicleID(i);
		    GetVehicleParamsEx(lPojazd,engine,lights,alarm,doors,bonnet,boot,objective);
		    if(engine)
		    {
			    GetVehicleHealth(lPojazd,lPojazdHP);
			    lPojazdHP = floatsub(lPojazdHP, 250.0);
				if(doors) lText="~r~Tak"; else lText="~g~Nie";

	   			format(dstring, sizeof(dstring), "~y~%s~n~~w~Predkosc: ~r~%d km/h~n~~w~Paliwo: ~r~ %d/%d l~n~~w~HP: ~r~%.0f %%~n~~w~Zamkniety: %s",GetVehicleName(lPojazd),GetPlayerSpeed(i),vPaliwo[lPojazd],vPaliwoMax[lPojazd],(lPojazdHP/750)*100,lText);
				TextDrawSetString(Licznik[i], dstring);

				if(vPaliwo[lPojazd]<1)
				{
	        		SetVehicleParamsEx(lPojazd,false,lights,alarm,doors,bonnet,boot,objective);
	        		TextDrawHideForPlayer(i,Licznik[i]);
		    		GInfo(i,"~r~brak paliwa!",3);
				}
			}//koniec engine
		}//status kierowcy
	}//petla
	
	gettime(hourt, minutet, secondst);
	format(dstring, sizeof(dstring),"%02d~g~:~w~%02d~g~:~w~%02d", hourt, minutet, secondst);
	TextDrawSetString(godzina, dstring);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    dUstawHP(playerid,100);
	SetPlayerPos(playerid, -189.6111,-307.9127,2.4297);
	SetPlayerFacingAngle(playerid,315.3905);
	SetPlayerCameraPos(playerid, -186.8163,-305.0795,1.9599);
	SetPlayerCameraLookAt(playerid, -189.6111,-307.9127,2.4297);
	if(classid <= 9) GInfo(playerid,"~n~~n~~n~~y~trucker",3);
	if((classid >= 10) && (classid <= 15)) GInfo(playerid,"~n~~n~~n~~b~Policja",3);
	if((classid >= 16) && (classid <= 19)) GInfo(playerid,"~n~~n~~n~~r~Pomoc Drogowa",3);
	if((classid >= 20) && (classid <= 22)) GInfo(playerid,"~n~~n~~n~~w~Firma Lotnicza",3);
	if((classid >= 23) && (classid <= 24)) GInfo(playerid,"~n~~n~~n~~r~Speed Trans",3);
	if((classid >= 25) && (classid <= 26)) GInfo(playerid,"~n~~n~~n~~r~Euro Trans",3);
	if((classid >= 27) && (classid <= 28)) GInfo(playerid,"~n~~n~~n~~r~Taxi",3);
	if((classid >= 29) && (classid <= 30)) GInfo(playerid,"~n~~n~~n~~r~Rico Trans",3);
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	new s=GetPlayerSkin(playerid);
	if((s==280||s==282||s==283||s==265||s==266||s==284)&&PlayerInfo[playerid][pFrakcja]!=1)
	{
		return GInfo(playerid,"~r~nie jestes w policji!",3), 0;
	}
	if((s==27||s==16||s==8||s==56)&&PlayerInfo[playerid][pFrakcja]!=2)
	{
		return GInfo(playerid,"~r~nie jestes w Pomocy Drogowej!",3), 0;
	}
	if((s==61||s==171||s==172)&&PlayerInfo[playerid][pFrakcja]!=3)
	{
		return GInfo(playerid,"~r~nie jestes w Firmie Lotniczej!",3), 0;
	}
	if((s==126||s==128)&&PlayerInfo[playerid][pFrakcja]!=10)
	{
		return GInfo(playerid,"~r~nie jestes w Firmie Speed Trans!",3), 0;
	}
	if((s==3||s==20)&&PlayerInfo[playerid][pFrakcja]!=11)
	{
		return GInfo(playerid,"~r~nie jestes w Firmie Euro Trans!",3), 0;
	}
	if((s==86||s==93)&&PlayerInfo[playerid][pFrakcja]!=4)
	{
		return GInfo(playerid,"~y~nie jestes w Taxi!",3), 0;
	}
	if((s==233||s==294)&&PlayerInfo[playerid][pFrakcja]!=12)
	{
		return GInfo(playerid,"~y~nie jestes w Rico Trans!",3), 0;
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
/*
    if(strfind(PlayerName(playerid),"[HTC]",true)!=1)
	{
		if(!DOF_IsSet(KLAN,PlayerName(playerid)))
 	    {
 	    	format(dstring, sizeof(dstring),"~r~(%d)%s zostal wyrzucony~n~~y~przez: (-1)BOT~n~~w~Za: posiadanie w nicku [HTC]",playerid,Nick(playerid));
		    NapisText(dstring);
		    SendClientMessage(playerid, KOLOR_BEZOWY, ""C_BEZOWY"W twoim nicku znajduje siÍ tag klanu "C_BEZOWY"HTC"C_BEZOWY", a nie jesteú wpisany na liste cz≥onkÛw !");
		    SendClientMessage(playerid, KOLOR_BEZOWY, ""C_CZERWONY"Jeøeli uwaøasz øe to b≥πd skontaktuj sie z "C_ZOLTY"[HTC]Pneumaticer"C_CZERWONY" i wyjaúnij tÍ sprawÍ.");
		    dKick(playerid);
		}
	}
*/
	teraz++;
	if(teraz > rekord)
	{
		rekord = teraz;
		DOF_SetInt("Truck/Statystyki.ini", "Rekord", rekord);
	}
    TextDrawHideForPlayer(playerid, Zones[playerid]);
    SetPlayerColor(playerid,KOLOR_CZARNY);
    SetTimerEx("Text",1000,false,"i",playerid);
	Zalogowany[playerid]=false;
	Regulamin[playerid]=true;
	BlokadaPW[playerid]=false;
	Lista[playerid]=true;
	Kierunkowskaz[playerid]=false;
	MandatPD[playerid]=999;
	Spec[playerid]=false;
	Misja[playerid]=false;
	MisjaID[playerid]=999;
	MisjaStopien[playerid]=0;
	MisjaPojazd[playerid]=0;
	Przeladowany[playerid]=false;
	OstatniaMisja[playerid]=999;
	LadunekPkt[playerid]=0;
	LadunekID[playerid]=999;
	DomID[playerid]=9999;
	DomPkt[playerid]=0;
	TextPkt[playerid]=0;
	TextID[playerid]=999;
	Pierwszy[playerid]=0;
	SetPVarInt(playerid, "PunktyToll", 0);
	PozwolenieMiecze[playerid]=0;
	AFK[playerid]=0;

	DeletePVar(playerid,"etap");
	DeletePVar(playerid,"Towar");
	DeletePVar(playerid,"Zaladunek");
	DeletePVar(playerid,"ZaladunekX");
	DeletePVar(playerid,"ZaladunekY");
	DeletePVar(playerid,"ZaladunekZ");
	DeletePVar(playerid,"Zaladunek");
	DeletePVar(playerid,"WyladunekX");
	DeletePVar(playerid,"WyladunekY");
	DeletePVar(playerid,"WyladunekZ");
	DeletePVar(playerid,"Kasa");
	DeletePVar(playerid,"Score");

	PlayerInfo[playerid][pKonto]=0;
	PlayerInfo[playerid][pAdmin]=0;
	PlayerInfo[playerid][pPremium]=0;
	PlayerInfo[playerid][pJail]=0;
	PlayerInfo[playerid][pWyciszony]=0;
	PlayerInfo[playerid][pWarny]=0;
	PlayerInfo[playerid][pPoziom]=0;
	PlayerInfo[playerid][pDostarczenia]=0;
	PlayerInfo[playerid][pScigany]=0;
	PlayerInfo[playerid][pMandat]=0;
	PlayerInfo[playerid][pKasa]=0;
	PlayerInfo[playerid][pBank]=0;
	PlayerInfo[playerid][pFrakcja]=0;
	PlayerInfo[playerid][pLider]=0;
	PlayerInfo[playerid][pDom]=9999;
	PlayerInfo[playerid][pWizyty]=1;
	PlayerInfo[playerid][pMisja]=0;
	PlayerInfo[playerid][pDJ]=0;
	sprawdzil[playerid] = 0;

	PlayerInfo[playerid][pPrawkoB]=0;
	PlayerInfo[playerid][pPrawkoCE]=0;
	PlayerInfo[playerid][pPrawkoA1]=0;

 	TogglePlayerSpectating(playerid, true);
 	new str[45],nick[MAX_PLAYER_NAME];
	GetPlayerName(playerid, nick, sizeof(nick));
	UpperToLower(nick);
	format(str, sizeof(str), "Truck/Konta/%s.ini",nick);
	if(DOF_FileExists(str))
 	{
		ShowPlayerDialog(playerid,2,DIALOG_STYLE_PASSWORD,""C_ZOLTY"Hard-Truck: "C_BIALY"Logowanie",""C_BIALY"Witaj!\nTen login jest zarejestrowany!\nW celu zalogowania siÍ wpisz "C_ZOLTY"has≥o"C_BIALY":","Zaloguj","Wyjdü");
 	}
 	else
 	{
      	ShowPlayerDialog(playerid,3,DIALOG_STYLE_PASSWORD,""C_ZOLTY"Hard-Truck: "C_BIALY"Rejestracja",""C_BIALY"Witaj!\nAby zagraÊ na tym serwerze musisz siÍ zarejestrowaÊ!\nW celu zarejestrowania siÍ wpisz "C_ZOLTY"has≥o do konta"C_BIALY":","Rejestruj","Wyjdü");
 	}
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	teraz--;
    PowerEnabled[playerid] = false;
    ZapiszKonto(playerid);
	TextDrawHideForPlayer(playerid,Licznik[playerid]);
 	TextDrawHideForPlayer(playerid, Zones[playerid]);
  	TextDrawHideForPlayer(playerid, armour[playerid]);
   	TextDrawHideForPlayer(playerid, zycie[playerid]);
   	TextDrawHideForPlayer(playerid, score[playerid]);

   	if(zdaje[playerid] == 1)
   	{
		zdawanie = 0;
		zdaje[playerid] = 0;
		typPrawka[playerid] = 0;
	}
  	if(Zalogowany[playerid]==true)
  	{
	  	switch(reason)
	  	{
	  		case 0: format(dstring, sizeof(dstring), "%s [%d] "C_SZARY"dosta≥ crasha!",Nick(playerid),playerid);
			case 1: format(dstring, sizeof(dstring), "%s [%d] "C_SZARY"wyszed≥ z gry!",Nick(playerid),playerid);
			case 2: format(dstring, sizeof(dstring), "%s [%d] "C_SZARY"zosta≥ wyrzucony/zbanowany!",Nick(playerid),playerid);
		}
		SendClientMessageToAll(KOLOR_BEZOWY,dstring);
	}
	if(ToAdminLevel(playerid, 1))
	{
	    Delete3DTextLabel(Tag[playerid]);
	}
	Zalogowany[playerid]=false;
	TarOff(playerid);
	TarZer(playerid);
	DestroyVehicle(PrivCar[playerid]);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if (zaladowano == 0)
	{
	    zaladowano = 1;
	    //WczytajLadunki();
		WczytajStacje();
		WczytajTexty();
		WczytajDomy();
		WczytajAutomaty();
		WczytajWozy();
		LadujFotoradary();
	}
	TextDrawShowForAll(godzina);

    if (PowerEnabled[playerid]) SetPlayerHealth(playerid, 0x107FFF);
	TextDrawShowForAll(ReklamaTD);
	UsowaneBudynki(playerid);

	if(!Zalogowany[playerid])
	{
        Info(playerid,""C_CZERWONY"Nie zalogowa≥eú siÍ!");
        Kick(playerid);
        return 1;
	}
	if(ToPD(playerid)) SetPlayerColor(playerid,KOLOR_NIEWIDZIALNY);
	else if(ToPOMOC(playerid)) SetPlayerColor(playerid,KOLOR_POMARANCZOWY);
	else if(ToLOT(playerid)) SetPlayerColor(playerid,KOLOR_ZOLTY);
	else if(ToST(playerid)) SetPlayerColor(playerid,KOLOR_CZERWONY);
	else if(ToET(playerid)) SetPlayerColor(playerid,KOLOR_ZIELONY);
	else if(ToTAXI(playerid)) SetPlayerColor(playerid,KOLOR_ROZOWY);
	else if(ToRICO(playerid)) SetPlayerColor(playerid,KOLOR_SZARY);
	else SetPlayerColor(playerid,KOLOR_NIEBIESKI);

	GivePlayerWeapon(playerid, 0, 0);
	dUstawHP(playerid,100);
	dUstawArmor(playerid,0);
	SetPlayerInterior(playerid,0);
	SetPlayerVirtualWorld(playerid,0);
	if(pojazdznaleziony == 1)
	{
		new sa[1000];
	 	strcat(sa,""C_NIEBIESKI"Administrator Inferno zgubi≥ swojego QUADa! \n");
	 	strcat(sa,""C_NIEBIESKI"Prosimy o pomoc w odnalezieniu go.\n");
	 	strcat(sa,""C_NIEBIESKI"Ostatni raz widzieliúmy go w pobliøu Los Santos\n");
	 	strcat(sa,""C_NIEBIESKI"\n");
	 	strcat(sa,""C_ZOLTY"Podpowiedz:\n");
	 	strcat(sa,""C_ZIELONY"Ale draka na lotnisku !!!\n");
		strcat(sa,""C_ZIELONY"mysz w plecaku siÍ schowa≥a\n");
		strcat(sa,""C_ZIELONY"bez paszportu i bez wizy\n");
		strcat(sa,""C_ZIELONY"do Tunezji lecieÊ chcia≥a\n");
		strcat(sa,""C_ZOLTY"\tAutor: renia èrÛd≥o: www.kobieta.pl\n");
        strcat(sa,""C_NIEBIESKI"\n");
	 	strcat(sa,""C_NIEBIESKI"Jeøeli go znajdziesz podejdz do niego i wpisz "C_ZIELONY"/znalazlem"C_NIEBIESKI".\n");
	 	strcat(sa,"\n");
	 	strcat(sa,""C_NIEBIESKI"\t\tWiÍc powodzenia!");
	  	ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,""C_CZERWONY"UWAGA Konkurs! "C_BIALY"["C_ZIELONY"TRWA"C_BIALY"]", sa, "Ok", "");
	}
	if(pojazdznaleziony == 0)
	{
		new sa[1000];
	 	strcat(sa,""C_NIEBIESKI"Konkurs na zagubionego Quada zakoÒczony! \n");
	 	strcat(sa,""C_NIEBIESKI"Znalazcy z ca≥ego serca gratulujemy.\n");
	 	strcat(sa,""C_NIEBIESKI"\n");
	 	strcat(sa,""C_NIEBIESKI"\n");
		strcat(sa,""C_NIEBIESKI"Juø nied≥ugo kolejne konkursy/eventy.\n");
		strcat(sa,""C_NIEBIESKI"\n");
		strcat(sa,""C_NIEBIESKI"Przypominamy o Sylwester 2012 z HT, ktÛry odbÍdzie siÍ\n");
		strcat(sa,""C_NIEBIESKI"31 grudnia o godzinie 20.30!\n");
		strcat(sa,""C_NIEBIESKI"Wszystkich serdecznie zapraszamy\n");
		strcat(sa,""C_NIEBIESKI"\n");
		strcat(sa,""C_ZOLTY"Pozdrawiamy\n");
		strcat(sa,""C_CZERWONY"Administracja\n");
	  	ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,""C_CZERWONY"UWAGA Konkurs! "C_BIALY"["C_CZERWONY"ZAKONCZONY"C_BIALY"]", sa, "Ok", "");
	}
	format(forma,sizeof forma,"Truck/VIP/%s.ini",PlayerName(playerid));
	if(DOF_FileExists(forma))
	{
		if(DOF_GetInt(forma,"VipCzas") < gettime())
		{
			DOF_SetInt(forma,"Vip",0);
			DOF_RemoveFile(forma);
		}else if(GetPVarInt(playerid,"pokazywalo")==0)
		{
			PokazCzas(playerid);
			DOF_SetInt(forma,"Vip",1);
			SetPVarInt(playerid,"pokazywalo",1);
		}
	}

	if(PlayerInfo[playerid][pJail]>=1)
	{
	    Info(playerid,""C_CZERWONY"Nie odsiedzia≥eú do koÒca na≥oøonej na Ciebie kary!");
		SetPlayerPos(playerid,264.9535,77.5068,1001.0391);
  		SetPlayerInterior(playerid,6);
    	SetPlayerVirtualWorld(playerid,playerid);
	    SetPlayerWorldBounds(playerid,268.5071,261.3936,81.6285,71.8745);
	    return 1;
	}
    new s=GetPlayerSkin(playerid);
    if(s==56)
    {
        SetPlayerAttachedObject(playerid,5,18638,2,0.16,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000);
	}
	
	if(s==280||s==282||s==283||s==265||s==266||s==284)//policja
	{
	    dUstawArmor(playerid,100);
		SetPlayerPos(playerid, 2861.291, 2251.2512, 11.7341);
	}
	else if(s==27||s==16||s==8||s==56)//pomoc drogowa
	{
	    SetPlayerPos(playerid,1073.329223, 1794.847778, 11.093982);
	}
	else if(s==61||s==171||s==172)//Lotnicza
	{
	    SetPlayerPos(playerid,1318.836181, 1249.819702, 10.820312);
	}
	else if(s==126||s==128)//speed trans
	{
	    SetPlayerPos(playerid,16.109012, 1480.746093, 13.084131);
	}
	else if(s==3||s==20)//euro truck
	{
	    SetPlayerPos(playerid,-2129.463867, -776.389282, 31.976549);
	}
	else if(s==86||s==93)//taxi
	{
	    SetPlayerPos(playerid,252.8059,1354.8419,10.7075);
	}
	else if(s==233||s==294)//rico
	{
	    SetPlayerPos(playerid,-1150.447753, -1060.930664, 129.218750);
	}
	else
	{
	    new los=random(7);
		switch(los)
		{
		    case 0:
			{
			    if(PlayerInfo[playerid][pDom]!=9999)
				{
				    new nr=PlayerInfo[playerid][pDom];
				    SetPlayerPos(playerid, DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				    return 1;
				}
				else if(PlayerInfo[playerid][pDom]==9999)
				{
					SetPlayerPos(playerid,2326.9631,2785.5002,10.8203);//lv
				}
			}
		    case 1:
			{
			    if(PlayerInfo[playerid][pDom]!=9999)
				{
				    new nr=PlayerInfo[playerid][pDom];
				    SetPlayerPos(playerid, DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				    return 1;
				}
				else if(PlayerInfo[playerid][pDom]==9999)
				{
					SetPlayerPos(playerid,1636.6249,1038.6071,10.8203);//lv
				}
			}
		    case 2:
			{
			    if(PlayerInfo[playerid][pDom]!=9999)
				{
				    new nr=PlayerInfo[playerid][pDom];
				    SetPlayerPos(playerid, DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				    return 1;
				}
				else if(PlayerInfo[playerid][pDom]==9999)
				{
					SetPlayerPos(playerid,252.8059,1354.8419,10.7075);//pustynia
				}
			}
		    case 3:
			{
			    if(PlayerInfo[playerid][pDom]!=9999)
				{
				    new nr=PlayerInfo[playerid][pDom];
				    SetPlayerPos(playerid, DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				    return 1;
				}
				else if(PlayerInfo[playerid][pDom]==9999)
				{
					SetPlayerPos(playerid,-49.9214,-277.7625,5.4297);//wioska
				}
			}
		    case 4:
			{
                if(PlayerInfo[playerid][pDom]!=9999)
				{
				    new nr=PlayerInfo[playerid][pDom];
				    SetPlayerPos(playerid, DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				    return 1;
				}
				else if(PlayerInfo[playerid][pDom]==9999)
				{
					SetPlayerPos(playerid,-501.8290,-518.0654,25.5234);//kolo sf
				}
			}
		    case 5:
			{
			    if(PlayerInfo[playerid][pDom]!=9999)
				{
				    new nr=PlayerInfo[playerid][pDom];
				    SetPlayerPos(playerid, DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				    return 1;
				}
				else if(PlayerInfo[playerid][pDom]==9999)
				{
					SetPlayerPos(playerid,-1710.3651,403.0952,7.4190);//sf
				}
			}
		    case 6:
			{
			    if(PlayerInfo[playerid][pDom]!=9999)
				{
				    new nr=PlayerInfo[playerid][pDom];
				    SetPlayerPos(playerid, DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				    return 1;
				}
				else if(PlayerInfo[playerid][pDom]==9999)
				{
					SetPlayerPos(playerid,-79.4036,-1135.6272,1.0781);//ls
				}
			}
		}
	}
	return 1;
}
/*

forward DajWoz(playerid);
public DajWoz(playerid)
{
	if(Pierwszy[playerid]==1)
	{

		Info(playerid, "Oto twÛj pierwszy pojazd w tej grze.\n Zbieraj pieniadze i kupuj coraz lepsze\n\n\n\n\n"C_CZERWONY"Wpisz "C_NIEBIESKI"/spomoc "C_CZERWONY"by uzyskaÊ pomoc co do systemu prywatnych pojazdow.");
 		new Float: X, Float: Y, Float: Z, Float:Ang;
		GetPlayerPos(playerid, X, Y, Z);
		GetPlayerFacingAngle(playerid,Ang);
		PrivCar[playerid] = CreateVehicle(414, X, Y , Z, Ang, 0,1, SPAWN);
		PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
		LinkVehicleToInterior(PrivCar[playerid], GetPlayerInterior(playerid));
 		ZapiszKonto(playerid);
 		KillTimer(TimDajWoz[playerid]);

		SetVehicleParamsEx(TimDajWoz[playerid],false,false,false,false,false,false,false);
		UstalPaliwo(TimDajWoz[playerid]);
		UstalLadownosc(TimDajWoz[playerid]);
		vPojazdZycie[TimDajWoz[playerid]]=1000.0;
		return 1;
	}
	if(Pierwszy[playerid]==0)
	{
		new file[45],nick[MAX_PLAYER_NAME];
		GetPlayerName(playerid,nick,sizeof(nick));
		UpperToLower(nick);
 		format(file,sizeof(file),"Truck/Konta/%s.ini",nick);
 		Info(playerid, "Zostales wsadzony do swojego wozu\n\n\n\n\n"C_CZERWONY"Wpisz "C_NIEBIESKI"/spomoc "C_CZERWONY"by uzyskaÊ pomoc co do systemu prywatnych pojazdow.");
 		KillTimer(TimDajWoz[playerid]);
   		PlayerInfo[playerid][pAuto]=DOF_GetInt(file,"Auto");
   		PlayerInfo[playerid][pAuto2]=DOF_GetInt(file,"Auto2");
   		PlayerInfo[playerid][pAuto3]=DOF_GetInt(file,"Auto3");
   		PlayerInfo[playerid][pAuto4]=DOF_GetInt(file,"Auto4");
   		PlayerInfo[playerid][pAuto5]=DOF_GetInt(file,"Auto5");
        PrivCar[playerid] = CreateVehicle(PlayerInfo[playerid][pAuto],PlayerInfo[playerid][pAuto2],PlayerInfo[playerid][pAuto3],PlayerInfo[playerid][pAuto4],PlayerInfo[playerid][pAuto5], -1, -1, SPAWN);
        PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
        KillTimer(TimDajWoz[playerid]);

		SetVehicleParamsEx(TimDajWoz[playerid],false,false,false,false,false,false,false);
		UstalPaliwo(TimDajWoz[playerid]);
		UstalLadownosc(TimDajWoz[playerid]);
		vPojazdZycie[TimDajWoz[playerid]]=1000.0;
   		return 1;
	}
	return 1;
}

*/


public OnPlayerDeath(playerid, killerid, reason)
{
	if(killerid == INVALID_PLAYER_ID)
	{
        SendDeathMessage(INVALID_PLAYER_ID,playerid,reason);
	}
	else
    {
   		SendDeathMessage(killerid, playerid, reason);
    }
    if(GetPVarInt(playerid, "etap") > 0)
    {
	   	SetPVarInt(playerid, "etap", 0);
		SetPVarString(playerid, "Towar", "Brak");
		SetPVarString(playerid, "Zaladunek", "Brak");
		SetPVarFloat(playerid, "ZaladunekX", 0.0000);
		SetPVarFloat(playerid, "ZaladunekY", 0.0000);
		SetPVarFloat(playerid, "ZaladunekZ", 0.0000);
		SetPVarString(playerid, "Zaladunek", "Brak");
		SetPVarFloat(playerid, "WyladunekX", 0.0000);
		SetPVarFloat(playerid, "WyladunekY", 0.0000);
		SetPVarFloat(playerid, "WyladunekZ", 0.0000);
		SetPVarInt(playerid, "Kasa", 0);
		ilemadacscore[playerid] = 0;
		DisablePlayerCheckpoint(playerid);
		dDodajKase(playerid, -400);
		GInfo(playerid, "~y~Zginales...~r~Straciles przewozony towar oraz 400$!", 3);
	}
	new s=GetPlayerSkin(playerid);
	if(s==56)
    {
        RemovePlayerAttachedObject(playerid, 5);
	}
 	return 1;
}

public OnVehicleSpawn(vehicleid)
{
    SetVehicleParamsEx(vehicleid,false,false,false,false,false,false,false);
    vPojazdZycie[vehicleid]=1000.0;
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	
	foreach(Player, i)
	{
		if(vehicleid == wozekprawo)
		{
		    if(zdaje[i] == 1)
		    {
	    		DestroyVehicle(wozekprawo);
	    		zdaje[i] = 0;
	    		typPrawka[i] = 0;
	    		zdawanie = 0;
                ShowPlayerDialog(i, 0, DIALOG_STYLE_MSGBOX, "Wyniki!", "Niestety, nie zda≥eú!\nNie uda≥o Ci siÍ zdaÊ na prawo jazdy.\nTwÛj pojazd zosta≥ zniszczony\n\nSprÛbuj ponownie...\nPowodzenia", "Ok", "");
                SendClientMessageToAll(KOLOR_CZERWONY, ""C_CZERWONY"Zdawanie na prawo jazdy: "C_ZIELONY"wolne");
			}
		}
	}
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new Float:HP;
	GetVehicleHealth(vehicleid,HP);
	if(floatround(vPojazdZycie[vehicleid]-HP)>=100)
	{
	    TogglePlayerControllable(playerid,0);
     	GameTextForPlayer(playerid,"~r~masz wypadek!~n~straciles przytomnosc...",10000,3);
      	SetTimerEx("Unfreeze",10000,false,"iS",playerid,"~w~ockneles sie");
	}
	vPojazdZycie[vehicleid]=HP;
    return 1;
}

public OnPlayerText(playerid, text[])
{
	new TCount, KMessage[128];
	TCount = GetPVarInt(playerid, "TextSpamCount");
	TCount++;
	SetPVarInt(playerid, "TextSpamCount", TCount);
	if(TCount == 2) {
	    SendClientMessage(playerid, KOLOR_ROZOWY, "AC: "C_BIALY"PrzestaÒ spamiÊ bo dostaniesz kicka!");
	}
	else if(TCount == 3) {
	    GetPlayerName(playerid, KMessage, sizeof(KMessage));
	    format(KMessage,sizeof(KMessage),"AC: "C_BIALY"(%d) %s zosta≥ wyrzucony, za: "C_CZERWONY"SPAM na chacie",playerid, KMessage);
		SendClientMessageToAll(KOLOR_ROZOWY, KMessage);
		format(dstring, sizeof(dstring),"~r~(%d)%s zostal wyrzucony~n~~y~przez: (-1)AntyCheat~n~~w~Za: Spam na Chacie",playerid,KMessage);
 		NapisText(dstring);
	    print(KMessage);
	    Kick(playerid);
	}
	SetTimerEx("ResetCount", SpamLimit, false, "i", playerid);
	
	if(anty(text) && !IsPlayerAdmin(playerid))
	{
		format(KMessage,sizeof(KMessage),"AC: "C_BIALY"(%d) %s zosta≥ wyrzucony, za: "C_CZERWONY"reklama",playerid, Nick(playerid));
		SendClientMessageToAll(KOLOR_ROZOWY, KMessage);
		format(dstring, sizeof(dstring),"~r~(%d)%s zostal wyrzucony~n~~y~przez: (-1)AntyCheat~n~~w~Za: reklama",playerid, Nick(playerid));
 		NapisText(dstring);
		Kick(playerid);
		return 0;
	}
	
	new Float: Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
    if(PlayerInfo[playerid][pJail]>=1)
	{
	    Info(playerid,""C_CZERWONY"Jesteú w wiÍzieniu, nie moøesz nic pisaÊ!");
		return 0;
	}
	else if(PlayerInfo[playerid][pWyciszony]>=1)
	{
	    Info(playerid,""C_CZERWONY"Jesteú wyciszony!");
		return 0;
	}
	else if(Bluzg(text))
	{
	    format(dstring,sizeof(dstring),"AC: "C_BIALY"(%d) %s zosta≥ wyciszony (3 min), za: "C_CZERWONY"wulgaryzmy",playerid,Nick(playerid));
		SendClientMessageToAll(KOLOR_ROZOWY,dstring);
	    KillTimer(MuteTimer[playerid]);
		MuteTimer[playerid]=SetTimerEx("Odcisz",60000*3,false,"i",playerid);
		PlayerInfo[playerid][pWyciszony]=5;
		ZapiszKonto(playerid);
		return 0;
	}
	UpperToLower(text);
	if(PlayerInfo[playerid][pAdmin]==1)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_ZIELONY"MOD"C_BIALY"]: %s",playerid,Nick(playerid),text);
		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pAdmin]==2)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_NIEBIESKI"Admin"C_BIALY"]: %s",playerid,Nick(playerid),text);
		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pAdmin]==3)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_CZERWONY"HeadAdmin"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(IsVip(playerid))
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_ZOLTY"VIP"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pDJ] == 1)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_TURKUSOWY"DJ"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pLider] == 1)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_BIALY"Szef Policji"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pLider] == 2)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_POMARANCZOWY"Szef PD"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pLider] == 3)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_ZOLTY"Szef FL"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pLider] == 10)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_CZERWONY"Szef ST"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else if(PlayerInfo[playerid][pLider] == 11)
	{
	    format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"["C_ZIELONY"Szef ET"C_BIALY"]: %s",playerid,Nick(playerid),text);
  		SendClientMessageToAll(KOLOR_NIEBIESKI,Koloruj(dstring));
  		SerwerInfo[sWiadomosci]++;
	    return 0;
	}
	else
	{
		format(dstring,sizeof(dstring),"[%d] %s: "C_BIALY"%s",playerid,Nick(playerid),text);
		SendClientMessageToAll(KOLOR_POMARANCZOWY,Koloruj(dstring));
		SerwerInfo[sWiadomosci]++;
	}
	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if(ToRadiowoz(vehicleid) && !ToPD(playerid) && !ispassenger)
	{
 		new Float:Pos[3];
		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
 		SetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
 		Info(playerid,""C_CZERWONY"Nie moøesz wsiπúÊ do tego pojazdu!");
	    return 1;
	}
	if(ToPojazdPD(vehicleid) && !ToPOMOC(playerid) && !ispassenger)
	{
	    new Float:Pos[3];
		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    SetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    Info(playerid,""C_CZERWONY"Nie moøesz wsiπúÊ do tego pojazdu!");
	    return 1;
	}
	if(ToPojazdLot(vehicleid) && !ToLOT(playerid) && !ispassenger)
	{
	    new Float:Pos[3];
		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    SetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    Info(playerid,""C_CZERWONY"Nie moøesz wsiπúÊ do tego pojazdu!");
	    return 1;
	}
	if(ToPojazdyST(vehicleid) && !ToST(playerid) && !ispassenger)
	{
	    new Float:Pos[3];
		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    SetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    Info(playerid,""C_CZERWONY"Nie moøesz wsiπúÊ do tego pojazdu!");
	    return 1;
	}
	if(ToPojazdyET(vehicleid) && !ToET(playerid) && !ispassenger)
	{
	    new Float:Pos[3];
		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    SetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    Info(playerid,""C_CZERWONY"Nie moøesz wsiπúÊ do tego pojazdu!");
	    return 1;
	}
	if(ToPojazdyRICO(vehicleid) && !ToRICO(playerid) && !ispassenger)
	{
	    new Float:Pos[3];
		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    SetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    Info(playerid,""C_CZERWONY"Nie moøesz wsiπúÊ do tego pojazdu!");
	    return 1;
	}
	return 1;
}

//sprawdza czy to pojazd PD
stock ToPojazdPD(id)
{
	for(new w = 0; w < 40; w++)
	{
 		if(id==pojazdpd[w])
 		{
 			return 1;
 		}
	}
	return 0;
}

//sprawdza czy to radiowoz
stock ToRadiowoz(id)
{
	for(new w = 0; w < 37; w++)
	{
 		if(id==pojazdpolicji[w])
 		{
 			return 1;
 		}
	}
	return 0;
}

stock ToPojazdLot(id)
{
	for(new w = 0; w < 67; w++)
	{
 		if(id==pojazdlot[w])
 		{
 			return 1;
 		}
	}
	return 0;
}

stock ToPojazdyST(id)
{
	for(new w = 0; w < 67; w++)
	{
 		if(id==pojazdyST[w])
 		{
 			return 1;
 		}
	}
	return 0;
}

stock ToPojazdyET(id)
{
	for(new w = 0; w < 67; w++)
	{
 		if(id==pojazdyET[w])
 		{
 			return 1;
 		}
	}
	return 0;
}

stock ToPojazdyRICO(id)
{
	for(new w = 0; w < 67; w++)
	{
 		if(id==ricowoz[w])
 		{
 			return 1;
 		}
	}
	return 0;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	if(doors)
	{
		SetVehicleParamsEx(vehicleid,engine,lights,alarm,false,bonnet,boot,objective);
	}
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
	{
	    new carid = GetPlayerVehicleID(playerid);
	    SendClientMessage(playerid,KOLOR_BIALY,"Panel zarzπdzania pojazdem, wpisz: "C_ZIELONY"(/p)ojazd");
	    SendClientMessage(playerid,KOLOR_CZERWONY,"PamiÍtaj by mieÊ zdane prawa jazdy na dane wozy! Prawko zdasz pod"C_ZIELONY" /prawko");

		if(pojazdkonkursowy == GetPlayerVehicleID(playerid))
		{
		    RemovePlayerFromVehicle(playerid);
		    return 1;
		}

        GetVehicleParamsEx(carid,engine,lights,alarm,doors,bonnet,boot,objective);
		if(engine)
		{
		    TextDrawShowForPlayer(playerid,Licznik[playerid]);
		    TextDrawShowForPlayer(playerid, Zones[playerid]);
			PokazFirmaTD(playerid);
		    return 1;
		}
		
		for(new nr = 0; nr < ILOSC_WOZOW; nr++)
		{
		    if(carid == KupneWozy[nr])
		    {
				if(strcmp(PrivateCar[nr][cWlasciciel], Nick(playerid)))
				{
					if(PrivateCar[nr][cLock]==1)
					{
						format(dstring, sizeof(dstring), ""C_BEZOWY"W≥aúciciel: "C_ZIELONY"%s\n"C_BEZOWY"ZamkniÍty: "C_CZERWONY"TAK", PrivateCar[nr][cWlasciciel]);
						ShowPlayerDialog(playerid, GUI_NIEKUPIONE, DIALOG_STYLE_MSGBOX, "Warning! - Prywatny pojazd.", dstring, "Ok", "");
						RemovePlayerFromVehicle(playerid);
					}
					if(PrivateCar[nr][cLock]==0)
					{
						format(dstring, sizeof(dstring), ""C_BEZOWY"W≥aúciciel: "C_ZIELONY"%s\n"C_BEZOWY"ZamkniÍty: "C_ZIELONY"NIE", PrivateCar[nr][cWlasciciel]);
						ShowPlayerDialog(playerid, GUI_NIEKUPIONE, DIALOG_STYLE_MSGBOX, "Warning! - Prywatny pojazd.", dstring, "Ok", "");
					}
				}
				else if(!strcmp(PrivateCar[nr][cWlasciciel], Nick(playerid)))
				{
					SendClientMessage(playerid, KOLOR_ZIELONY, ""C_ZIELONY"Witaj w swoim pojeüdzie! Aby nim zarzπdzaÊ wpisz "C_POMARANCZOWY"/cmenu"C_ZIELONY".");
				}
			}
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT)
	{
		TextDrawHideForPlayer(playerid,Licznik[playerid]);
		TextDrawHideForPlayer(playerid, Zones[playerid]);
		UkryjFirmaTD(playerid);
	    return 1;
	}

	return 1;
}
/*
public OnPlayerEnterCheckpoint(playerid)
{
	if(Misja[playerid]==true)
	{
	    DisablePlayerCheckpoint(playerid);
		if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
		{
		    Misja[playerid]=false;
		    dDodajKase(playerid,-2000);
		    Info(playerid,""C_ZOLTY"Nie masz pojazdu, misja anulowana!\n"C_CZERWONY"Grzywna: 2000$");
		    return 1;
		}

		new id=MisjaID[playerid],v=GetPlayerVehicleID(playerid);
	    if(MisjaStopien[playerid]==0 && DoInRange(10.0, playerid, LadunekInfo[id][lPosX],LadunekInfo[id][lPosY],LadunekInfo[id][lPosZ]))//dopiero ≥aduje
	    {
			if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)//ciÍøarowe
			{
                if(GetVehicleTrailer(v)!=MisjaPojazd[playerid])
			    {
			        Info(playerid,""C_CZERWONY"Nie masz naczepy, ktÛrπ przyjπ≥eú zlecenie!\nMisja anulowana!\nGrzywna: 1000$");
    				dDodajKase(playerid,-1000);
    				AnulujMisje(playerid);
		        	return 1;
			    }
				MisjaStopien[playerid]=1;
				SetPlayerCheckpoint(playerid,LadunekInfo[id][lPos2X],LadunekInfo[id][lPos2Y],LadunekInfo[id][lPos2Z],5);
                TogglePlayerControllable(playerid,0);
                GameTextForPlayer(playerid,"~r~trwa ladowanie...",10000,3);
                SetTimerEx("Unfreeze",10000,false,"iS",playerid,"~r~zaladowany");
			    if(Przeladowany[playerid]==true)
				{
			 		SendClientMessage(playerid,KOLOR_CZERWONY,"Prze≥adowa≥eú towar, uwaøaj na kontrole!");
			 		format(dstring, sizeof(dstring), "~g~%s ~r~(150 %%) ~w~z ~r~%s ~w~do ~y~%s",LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
				    LadunekNapis(playerid,dstring);
				}
				else
				{
					SendClientMessage(playerid,KOLOR_ZOLTY,"Towar za≥adowany pomyúlnie!");
					format(dstring, sizeof(dstring), "~g~%s ~g~(100 %%) ~w~z ~r~%s ~w~do ~y~%s",LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
				    LadunekNapis(playerid,dstring);
				}
		    }
		    else
		    {
		        if(v!=MisjaPojazd[playerid])
		        {
		            Info(playerid,""C_CZERWONY"Nie masz pojazdu, ktÛrym przyjπ≥eú zlecenie!\nMisja anulowana!\nGrzywna: 1000$");
    				dDodajKase(playerid,-1000);
    				AnulujMisje(playerid);
		        	return 1;
		        }
		        MisjaStopien[playerid]=1;
				SetPlayerCheckpoint(playerid,LadunekInfo[id][lPos2X],LadunekInfo[id][lPos2Y],LadunekInfo[id][lPos2Z],5);
                TogglePlayerControllable(playerid,0);
                GameTextForPlayer(playerid,"~r~trwa ladowanie...",10000,3);
                SetTimerEx("Unfreeze",10000,false,"iS",playerid,"~r~Zaladowany");
			    if(Przeladowany[playerid]==true)
				{
			 		SendClientMessage(playerid,KOLOR_CZERWONY,"Prze≥adowa≥eú towar, uwaøaj na kontrole!");
			 		format(dstring, sizeof(dstring), "~g~%s ~r~(150 %%) ~w~z ~r~%s ~w~do ~y~%s",LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
				    LadunekNapis(playerid,dstring);
				}
				else
				{
					SendClientMessage(playerid,KOLOR_ZOLTY,"Towar za≥adowany pomyúlnie!");
					format(dstring, sizeof(dstring), "~g~%s ~g~(100 %%) ~w~z ~r~%s ~w~do ~y~%s",LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
				    LadunekNapis(playerid,dstring);
				}
		    }
	        return 1;
	    }

	    if(MisjaStopien[playerid]==1 && DoInRange(10.0, playerid, LadunekInfo[id][lPos2X],LadunekInfo[id][lPos2Y],LadunekInfo[id][lPos2Z]))//roz≥adunek
	    {
	        if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)//ciÍøarowe
			{
                if(GetVehicleTrailer(v)!=MisjaPojazd[playerid])
			    {
			        Info(playerid,""C_CZERWONY"Nie masz naczepy, ktÛrπ przyjπ≥eú zlecenie!\nMisja anulowana!\nGrzywna: 1000$");
    				dDodajKase(playerid,-1000);
    				AnulujMisje(playerid);
		        	return 1;
				}
				new wyplata,naczepa=MisjaPojazd[playerid];
				if(Przeladowany[playerid]==true) wyplata=floatround(LadunekInfo[id][lTowarKoszt]*vLadownoscMax[naczepa]); else wyplata=floatround(LadunekInfo[id][lTowarKoszt]*vLadownosc[naczepa]);
    			PlayerInfo[playerid][pDostarczenia]++;
				dDodajKase(playerid,wyplata);
				dDodajKase(playerid,4000);
				format(dstring, sizeof(dstring), ""C_ZIELONY"Zarobi≥eú: %d$\n"C_ZOLTY"Dostarczy≥eú: %s z %s do %s.",wyplata,LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
				Info(playerid,dstring);
				PlayerInfo[playerid][pMisja]=0;
				ZapiszKonto(playerid);
				ZmienRange(playerid);
				format(dstring, sizeof(dstring),"[%d]%s dostarczy≥ "C_CZERWONY"%s "C_TURKUSOWY"z "C_CZERWONY"%s "C_TURKUSOWY" do "C_CZERWONY"%s.",playerid,Nick(playerid),LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
  				SendClientMessageToAll(KOLOR_TURKUSOWY,dstring);
				TogglePlayerControllable(playerid,0);
                GameTextForPlayer(playerid,"~r~trwa rozladunek...",10000,3);
                SetTimerEx("Unfreeze",10000,false,"iS",playerid,"~r~rozladowany");
				Misja[playerid]=false;
				MisjaID[playerid]=999;
				MisjaStopien[playerid]=0;
				MisjaPojazd[playerid]=0;
                LadunekNapis(playerid,"~y~/zlecenie ~w~aby rozpoczac misje... ~y~/pomoc ~w~spis pomocnych komend");
			}
			else
			{
			    if(v!=MisjaPojazd[playerid])
		        {
		            Info(playerid,""C_CZERWONY"Nie masz pojazdu, ktÛrym przyjπ≥eú zlecenie!\nMisja anulowana!\nGrzywna: 1000$");
    				dDodajKase(playerid,-1000);
    				AnulujMisje(playerid);
		        	return 1;
		        }
          		new wyplata;
				if(Przeladowany[playerid]==true) wyplata=floatround(LadunekInfo[id][lTowarKoszt]*vLadownoscMax[v]); else wyplata=floatround(LadunekInfo[id][lTowarKoszt]*vLadownosc[v]);
    			PlayerInfo[playerid][pDostarczenia]++;
				dDodajKase(playerid,wyplata);
				dDodajKase(playerid,2000);
				format(dstring, sizeof(dstring), ""C_ZIELONY"Zarobi≥eú: %d$\n"C_ZOLTY"Dostarczy≥eú: %s z %s do %s.",wyplata,LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
				Info(playerid,dstring);
				PlayerInfo[playerid][pMisja]=0;
				ZapiszKonto(playerid);
				ZmienRange(playerid);

				format(dstring, sizeof(dstring),"[%d]%s dostarczy≥ "C_CZERWONY"%s "C_TURKUSOWY"z "C_CZERWONY"%s "C_TURKUSOWY" do "C_CZERWONY"%s.",playerid,Nick(playerid),LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
  				SendClientMessageToAll(KOLOR_TURKUSOWY,dstring);
				TogglePlayerControllable(playerid,0);
                GameTextForPlayer(playerid,"~r~trwa rozladunek...",10000,3);
                SetTimerEx("Unfreeze",10000,false,"iS",playerid,"~r~rozladowany");
				Misja[playerid]=false;
				MisjaID[playerid]=999;
				MisjaStopien[playerid]=0;
				MisjaPojazd[playerid]=0;
				LadunekNapis(playerid,"~y~/zlecenie ~w~aby rozpoczac misje... ~y~/pomoc ~w~spis pomocnych komend");
			}
	        return 1;
	    }
	}
	return 1;
}
*/
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (PowerEnabled[playerid]) ActivateMotion(playerid, newkeys);

    if(newkeys==KEY_LOOK_RIGHT&&GetPlayerState(playerid)==PLAYER_STATE_DRIVER&&Kierunkowskaz[playerid]==false)
	{
		new v=GetPlayerVehicleID(playerid);
	    Kierunkowskaz[playerid]=true;
	    format(dstring, sizeof(dstring), ""C_ZIELONY"%s "C_ZOLTY"skrÍca w "C_CZERWONY"prawo [>>]",Nick(playerid));
		Kierunek[playerid]=Create3DTextLabel(dstring,KOLOR_BIALY,0.0,0.0,0.0,15.0,-1,0);
		Attach3DTextLabelToVehicle(Text3D:Kierunek[playerid],v,0.0,0.0,0.1);
		SetTimerEx("KierunekPrawo",1000,0,"iii",playerid,v,0);
	    return 1;
	}

	if(newkeys==KEY_LOOK_LEFT&&GetPlayerState(playerid)==PLAYER_STATE_DRIVER&&Kierunkowskaz[playerid]==false)
	{
	    new v=GetPlayerVehicleID(playerid);
	    Kierunkowskaz[playerid]=true;
	    format(dstring, sizeof(dstring), ""C_ZIELONY"%s "C_ZOLTY"skrÍca w "C_CZERWONY"lewo [<<]",Nick(playerid));
		Kierunek[playerid]=Create3DTextLabel(dstring,KOLOR_BIALY,0.0,0.0,0.0,15.0,-1,0);
		Attach3DTextLabelToVehicle(Text3D:Kierunek[playerid],v,0.0,0.0,0.1);
		SetTimerEx("KierunekLewo",1000,0,"iii",playerid,v,0);
		return 1;
	}

 	if((newkeys==KEY_SPRINT)&&(GetPlayerState(playerid)==PLAYER_STATE_ONFOOT))
	{
		new vir=GetPlayerVirtualWorld(playerid);
		for(new p = 0; p < LIMIT_DOMOW; p++)
		{
			//domy
			if(DoInRange(1.2,playerid,DomInfo[p][dWejscieX],DomInfo[p][dWejscieY],DomInfo[p][dWejscieZ])&&DomInfo[p][dAktywny]==1&&vir==DomInfo[p][dWejscieVir])
			{
			    if(DomInfo[p][dZamkniety]==1){ GInfo(playerid,"~r~drzwi zamkniete",1); return 1; }
			    SetPlayerPos(playerid,DomInfo[p][dWyjscieX],DomInfo[p][dWyjscieY],DomInfo[p][dWyjscieZ]);
			    SetPlayerInterior(playerid,DomInfo[p][dWyjscieInt]);
			    SetPlayerVirtualWorld(playerid,p);
				break;
			}
			if(DoInRange(1.2,playerid,DomInfo[p][dWyjscieX],DomInfo[p][dWyjscieY],DomInfo[p][dWyjscieZ])&&DomInfo[p][dAktywny]==1&&vir==p)
			{
			    if(DomInfo[p][dZamkniety]==1){ GInfo(playerid,"~r~drzwi zamkniete",1); return 1; }
			    SetPlayerPos(playerid,DomInfo[p][dWejscieX],DomInfo[p][dWejscieY],DomInfo[p][dWejscieZ]);
			    SetPlayerInterior(playerid,DomInfo[p][dWejscieInt]);
			    SetPlayerVirtualWorld(playerid,DomInfo[p][dWejscieVir]);
				break;
			}
		}
	}

	if(newkeys & KEY_ACTION)
	{
 		if((ToPOMOC(playerid)) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new vehicleid, model;
			vehicleid = GetPlayerVehicleID(playerid);
			model = GetVehicleModel(vehicleid);

			if((model == 403 || model == 514 || model == 515) && IsTrailerAttachedToVehicle(vehicleid)) //ciÍøarÛwki
			{
				new vehicle = GetVehicleTrailer(vehicleid), Float:vPos[4];

				DetachTrailerFromVehicle(vehicleid);
				GetVehiclePos(vehicle, vPos[0], vPos[1], vPos[2]);
				GetVehicleZAngle(vehicle, vPos[3]);

				vPos[0] -= 3 * floatsin(-vPos[3], degrees);
				vPos[1] -= 3 * floatcos(-vPos[3], degrees);

				SetVehiclePos(vehicle, vPos[0], vPos[1], vPos[2]);
			}
			else if(model == 525) //Tow Truck
			{
				if(IsTrailerAttachedToVehicle(vehicleid))
				{
					DetachTrailerFromVehicle(vehicleid);
				}
				else
				{
					new Float:pPos[3], Float:vPos[3];
					GetVehiclePos(vehicleid, pPos[0], pPos[1], pPos[2]);

					for(new vehicle = 1; vehicle < MAX_VEHICLES; vehicle++)
					{
						GetVehiclePos(vehicle, vPos[0], vPos[1], vPos[2]);

						if(!IsTruckTrailer(vehicle) && floatabs(pPos[0] - vPos[0]) < 7.0 && floatabs(pPos[1] - vPos[1]) < 7.0 && floatabs(pPos[2] - vPos[2]) < 7.0 && vehicleid != vehicle)
						{
							AttachTrailerToVehicle(vehicle, vehicleid);
							break;
						}
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(Zalogowany[playerid]==true)
	{
	    if(DoInRange(100, playerid, 210.856903, -1841.830932, 4.860312))
	    {
	        NaDysce[playerid]=1;
		}
		else if(!DoInRange(100, playerid, 210.856903, -1841.830932, 4.860312))
		{
		    NaDysce[playerid]=0;
		}

		SetPlayerScore(playerid,PlayerInfo[playerid][pDostarczenia]);

		new upanels, udoors, ulights, utires;
		GetVehicleDamageStatus(GetPlayerVehicleID(playerid), upanels, udoors, ulights, utires);
		if(Kolczatka[0]&&IsPlayerInRangeOfPoint(playerid, 5.0, KolPosX[0], KolPosY[0], KolPosZ[0])&&IsPlayerInAnyVehicle(playerid))
		{
			UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), upanels, udoors, ulights, 999);
		}
		if(Kolczatka[1]&&IsPlayerInRangeOfPoint(playerid, 5.0, KolPosX[1], KolPosY[1], KolPosZ[1])&&IsPlayerInAnyVehicle(playerid))
		{
			UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), upanels, udoors, ulights, 999);
		}
		if(Kolczatka[2]&&IsPlayerInRangeOfPoint(playerid, 5.0, KolPosX[2], KolPosY[2], KolPosZ[2])&&IsPlayerInAnyVehicle(playerid))
		{
			UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), upanels, udoors, ulights, 999);
		}
		if(Kolczatka[3]&&IsPlayerInRangeOfPoint(playerid, 5.0, KolPosX[3], KolPosY[3], KolPosZ[3])&&IsPlayerInAnyVehicle(playerid))
		{
			UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), upanels, udoors, ulights, 999);
		}
		if(Kolczatka[4]&&IsPlayerInRangeOfPoint(playerid, 5.0, KolPosX[4], KolPosY[4], KolPosZ[4])&&IsPlayerInAnyVehicle(playerid))
		{
			UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), upanels, udoors, ulights, 999);
		}
		Toll(playerid, 1646.69995117, 224.10000610, 29.39999962);
		Toll(playerid, 1635.19995117, 226.50000000, 29.39999962);
		Toll(playerid, 1828.80004883, 279.50000000, 21.70000076);
		Toll(playerid, 1830.80004883, 259.89999390, 21.70000076);
		Toll(playerid, 1634.50000000, -1092.90002441, 58.79999924);
		Toll(playerid, 1651.50000000, -1095.40002441, 58.79999924);
		Toll(playerid, 1952.30004883, -1516.09997559, 2.29999995);
		Toll(playerid, 1952.40002441, -1499.80004883, 2.29999995);
		Toll(playerid, 1668.69995117, -2001.09997559, 22.50000000);
		Toll(playerid, 1653.69995117, -1997.69995117, 22.60000038);
		Toll(playerid, 2709.10009766, 1142.09997559, 5.69999981);
		Toll(playerid, 2726.60009766, 1142.09997559, 5.69999981);
		Toll(playerid, 1768.00000000, 2476.89990234, 5.80000019);
		Toll(playerid, 1765.50000000, 2494.69995117, 5.80000019);
		Toll(playerid, 1530.00000000, 852.20001221, 5.80000019);
		Toll(playerid, 1529.90002441, 834.40002441, 5.80000019);
		Toll(playerid, 648.29998779, 676.40002441, 5.90000010);
		Toll(playerid, 647.20001221, 657.79998779, 5.90000010);
		Toll(playerid, -901.70001221, 912.29998779, 18.10000038);
		Toll(playerid, -840.59960938, 922.69921875, 24.70000076);
		Toll(playerid, -1897.40002441, -224.10000610, 37.20000076);
		Toll(playerid, -1911.00000000, -224.19999695, 37.20000076);
		Toll(playerid, -1188.80004883, -1852.40002441, 66.90000153);
		if(sprawdzil[playerid] == 0 && !ToPD(playerid))
		{
			for(new nr = 0; nr < MAX_FOTORADAR; nr++)
			{
				if(DoInRange(10, playerid, FotoInfo[nr][fX], FotoInfo[nr][fY], FotoInfo[nr][fZ]))
				{
					new predkoscgracza = GetPlayerSpeed(playerid);
					if(predkoscgracza > 130)
					{
						if(!ToPD(playerid))
						{
							new kwota = (predkoscgracza-130)*10;
							dDodajKase(playerid, -kwota);
							SendClientMessage(playerid, KOLOR_CZERWONY, ""C_CZERWONY"Fotoradar Warning: "C_BEZOWY"twoja predkosc byla wyzsza niz maksymalna dopuszczalna!");
							format(dstring,sizeof(dstring),""C_BEZOWY"Wynosila ona "C_ZIELONY"%d"C_BEZOWY" a dopuszczalne jest "C_ZIELONY"130km/h."C_BEZOWY" Zaplaciles %d$.", predkoscgracza, kwota);
							SendClientMessage(playerid, KOLOR_CZERWONY, dstring);
							sprawdzil[playerid] = 1;
							SetTimerEx("FotoradarSprawdzil", 3000, false, "d", playerid);
						}
					}
				}
			}
		}
	}
	return 1;
}

forward FotoradarSprawdzil(playerid);
public FotoradarSprawdzil(playerid)
{
    sprawdzil[playerid] = 0;
    return 1;
}

CMD:dfot(playerid, params[])
{
	if(PlayerInfo[playerid][pLider] != 1)
	    return 1;
	new id;
	if(sscanf(params, "d", id))
	    return SendClientMessage(playerid, KOLOR_CZERWONY, "Uzyj: /ufot <ID>");

	if(FotoInfo[id][fAktywny] == 0)
	    return SendClientMessage(playerid, KOLOR_CZERWONY, "Nie ma takiego fotoradaru!");

    new file[25];
	format(file,sizeof(file),FOTORADARY_FILE,id);
	DestroyDynamicObject(Fotoradar[id]);
	DestroyDynamic3DTextLabel(FotoradarText[id]);
	FotoInfo[id][fX]=0.0000;
	FotoInfo[id][fY]=0.0000;
	FotoInfo[id][fZ]=0.0000;
	FotoInfo[id][fAng]=0.0000;
	FotoInfo[id][fAktywny] = 0;
	DOF_RemoveFile(file);
	format(dstring,sizeof(dstring),"Usunoles fotoradar o ID: %d", id);
 	SendClientMessage(playerid, KOLOR_CZERWONY, dstring);
	return 1;
}


CMD:cfot(playerid, params[])
{
    if(PlayerInfo[playerid][pLider] != 1)
	    return 1;
	    
	new TworzenieFotoradaru = 1;
	for(new nr = 0; nr < MAX_FOTORADAR; nr++)
	{
		if(TworzenieFotoradaru == 1)
		{
			new file[25];
			format(file,sizeof(file),FOTORADARY_FILE,nr);
			if(!DOF_FileExists(file))
			{
				TworzenieFotoradaru = 0;
				new Float: Pos[4];
				GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
				GetPlayerFacingAngle(playerid, Pos[3]);
				FotoInfo[nr][fX]=Pos[0];
				FotoInfo[nr][fY]=Pos[1];
				FotoInfo[nr][fZ]=Pos[2];
				FotoInfo[nr][fAng]=Pos[3]+180;
				FotoInfo[nr][fAktywny] = 1;
				Fotoradar[nr] = CreateDynamicObject(18880, Pos[0], Pos[1], Pos[2]-3, 0.0000, 0.0000, Pos[3]+180);
				format(dstring,sizeof(dstring),""C_CZERWONY"UWAGA FOTORADAR\n"C_ZIELONY"Ograniczenie predkosci: "C_CZERWONY"130km/h\n\n"C_ZIELONY"ID: "C_CZERWONY"%d", nr);
				FotoradarText[nr] = CreateDynamic3DTextLabel(dstring,0x00FF40FF,FotoInfo[nr][fX], FotoInfo[nr][fY], FotoInfo[nr][fZ],5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,5.0);
				ZapiszFotoradar(nr);
				format(dstring,sizeof(dstring),"Utworzyles fotoradar o ID: %d", nr);
				SendClientMessage(playerid, KOLOR_ZIELONY, dstring);
				SetPlayerPos(playerid, Pos[0]+1, Pos[1]+1, Pos[2]);
			}
		}
	}
    return 1;
}

forward ZapiszFotoradar(nr);
public ZapiszFotoradar(nr)
{
	new file[25];
	format(file,sizeof(file),FOTORADARY_FILE,nr);
	if(!DOF_FileExists(file))
	{
	    DOF_CreateFile(file);
	}
	DOF_SetFloat(file,"X", FotoInfo[nr][fX]);
	DOF_SetFloat(file,"Y", FotoInfo[nr][fY]);
	DOF_SetFloat(file,"Z", FotoInfo[nr][fZ]);
	DOF_SetFloat(file,"Ang", FotoInfo[nr][fAng]);
	DOF_SaveFile();
	return 1;
}

//g≥Ûwne moje funkcje


stock Bluzg(text[])
{
	if(strfind(text[0],"huj",false)!=-1||
	strfind(text[0],"chuj",false)!=-1||
	strfind(text[0],"kurwa",false)!=-1||
	strfind(text[0],"suka",false)!=-1||
	strfind(text[0],"szmata",false)!=-1||
	strfind(text[0],"dziwka",false)!=-1||
	strfind(text[0],"jebaÊ",false)!=-1||
	strfind(text[0],"jebac",false)!=-1||
	strfind(text[0],"spierdalaj",false)!=-1||
	strfind(text[0],"pierdoliÊ",false)!=-1||
	strfind(text[0],"pierdolic",false)!=-1||
	strfind(text[0],"jeb",false)!=-1||
	strfind(text[0],"ssij",false)!=-1||
	strfind(text[0],"suki",false)!=-1||
	strfind(text[0],"skurwysyn",false)!=-1||
	strfind(text[0],"pizda",false)!=-1||
	strfind(text[0],"kurwy",false)!=-1)
	{
	    return 1;
	}
    return 0;
}

stock ColouredText(text[])//zmienianie kolorÛw
{
    enum
        colorEnum
        {
            colorName[16],
            colorID[7]
        }
    ;
    new
        colorInfo[][colorEnum] =
        {
            { "BLUE",           "1B1BE0" },
            { "PINK",           "E81CC9" },
            { "YELLOW",         "DBED15" },
            { "LIGHTGREEN",     "8CED15" },
            { "LIGHTBLUE",      "15D4ED" },
            { "RED",            "FF0000" },
            { "GREY",           "BABABA" },
            { "WHITE",          "FFFFFF" },
            { "ORANGE",         "DB881A" },
            { "GREEN",          "37DB45" },
            { "PURPLE",         "7340DB" }
        },
        string[(128 + 32)],
        tempString[16],
        pos = -1,
        x
    ;
    strmid(string, text, 0, 128, sizeof(string));

    for( ; x != sizeof(colorInfo); ++x)
    {
        format(tempString, sizeof(tempString), "#%s", colorInfo[x][colorName]);

        while((pos = strfind(string, tempString, true, (pos + 1))) != -1)
        {
            new
                tempLen = strlen(tempString),
                tempVar,
                i = pos
            ;
            format(tempString, sizeof(tempString), "{%s}", colorInfo[x][colorID]);

            if(tempLen < 8)
            {
                for(new j; j != (8 - tempLen); ++j)
                {
                    strins(string, " ", pos);
                }
            }
            for( ; ((string[i] != 0) && (tempVar != 8)) ; ++i, ++tempVar)
            {
                string[i] = tempString[tempVar];
            }
            if(tempLen > 8)
            {
                strdel(string, i, (i + (tempLen - 8)));
            }
            x = -1;
        }
    }
    return string;
}

forward KierunekPrawo(playerid,vehicleid,numer);
public KierunekPrawo(playerid,vehicleid,numer)
{
	if(numer>=7)
	{
	    Delete3DTextLabel(Text3D:Kierunek[playerid]);
	    Kierunkowskaz[playerid]=false;
	 	return 1;
	}
	new string[128];
	numer++;
	if(numer==1||numer==3||numer==5) Delete3DTextLabel(Text3D:Kierunek[playerid]);
	if(numer==2||numer==4||numer==6)
	{
	    format(string, sizeof(string), ""C_ZIELONY"%s "C_ZOLTY"skrÍca w "C_CZERWONY"prawo [>>]",Nick(playerid));
	    Kierunek[playerid]=Create3DTextLabel(string,KOLOR_BIALY,0.0,0.0,0.0,25.0,-1,0);
		Attach3DTextLabelToVehicle(Text3D:Kierunek[playerid],vehicleid,0.0,0.0,0.1);
	}
	SetTimerEx("KierunekPrawo",1000,0,"iii",playerid,vehicleid,numer);
	return 1;
}

forward KierunekLewo(playerid,vehicleid,numer);
public KierunekLewo(playerid,vehicleid,numer)
{
	if(numer>=7)
	{
	    Delete3DTextLabel(Text3D:Kierunek[playerid]);
	    Kierunkowskaz[playerid]=false;
	 	return 1;
	}
	new string[128];
	numer++;
	if(numer==1||numer==3||numer==5) Delete3DTextLabel(Text3D:Kierunek[playerid]);
	if(numer==2||numer==4||numer==6)
	{
	    format(string, sizeof(string), ""C_ZIELONY"%s "C_ZOLTY"skrÍca w "C_CZERWONY"lewo [<<]",Nick(playerid));
	    Kierunek[playerid]=Create3DTextLabel(string,KOLOR_BIALY,0.0,0.0,0.0,25.0,-1,0);
		Attach3DTextLabelToVehicle(Text3D:Kierunek[playerid],vehicleid,0.0,0.0,0.1);
	}
	SetTimerEx("KierunekLewo",1000,0,"iii",playerid,vehicleid,numer);
	return 1;
}

forward SpecSystem(playerid,gracz);//specowanie
public SpecSystem(playerid,gracz)
{
	if(IsPlayerConnected(gracz)&&IsPlayerConnected(playerid)&&Spec[playerid]==true)
 	{
 		if(IsPlayerInAnyVehicle(gracz)) PlayerSpectateVehicle(playerid,GetPlayerVehicleID(gracz)); else PlayerSpectatePlayer(playerid,gracz);
  		SetPlayerInterior(playerid,GetPlayerInterior(gracz));
   		SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(gracz));
    	SetTimerEx("SpecSystem",1000,false,"ii",playerid,gracz);
    	format(dstring, sizeof(dstring),"~r~Spec~n~~g~id: %d",gracz);
    	GameTextForPlayer(playerid,dstring,3000,1);
    	return 1;
	}
	else
	{
 		TogglePlayerSpectating(playerid,false);
	}
 	return 1;
}

forward Unfreeze(playerid,text[]);//odmraza
public Unfreeze(playerid,text[])
{
    TogglePlayerControllable(playerid,1);
    GameTextForPlayer(playerid,text,7000,3);
	return 1;
}

forward NapisText(text[]);//wyswietla napis
public NapisText(text[])
{
	if(NapisUzywany==1)
	{
		TextDrawHideForAll(Napis);
		KillTimer(NapisTimer);
	}
	NapisUzywany=1;
	TextDrawSetString(Napis,text);
	TextDrawShowForAll(Napis);
 	NapisTimer=SetTimer("NapisWylacz",20000,false);
	return 1;
}

forward NapisWylacz();//wylacza
public NapisWylacz()
{
    NapisUzywany=0;
    TextDrawHideForAll(Napis);
    KillTimer(NapisTimer);
    return 1;
}

forward RegulaminOff(playerid);//zalicza regulamin
public RegulaminOff(playerid)
{
    Regulamin[playerid]=false;
    return 1;
}

forward Text(playerid);//text powitalny przy polaczeniu
public Text(playerid)
{
    CzyscCzat(playerid,20);
    SendCompileInfo(playerid);
	SendClientMessage(playerid,KOLOR_ZOLTY,"*** "C_POMARANCZOWY"Hard-Truck "C_ZOLTY"");
	SendClientMessage(playerid,KOLOR_ZOLTY,"Witaj na serwerze! Zapoznaj siÍ z komendami: "C_ZIELONY"/pomoc");
	return 1;
}

forward SilnikUruchom(playerid);//odpala silnik
public SilnikUruchom(playerid)
{
    if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER) return 1;
    new v,Float:HP;
    v=GetPlayerVehicleID(playerid);
    GetVehicleHealth(v,HP);
    GetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,boot,objective);

    if(HP>700)
    {
    	GInfo(playerid,"~w~silnik ~g~uruchomiony",3);
    	SetVehicleParamsEx(v,true,lights,alarm,doors,bonnet,boot,objective);
	    TextDrawShowForPlayer(playerid,Licznik[playerid]);
	    PokazFirmaTD(playerid);
	    TextDrawShowForPlayer(playerid, Zones[playerid]);
    	return 1;
	}
	else
	{
	    new los = random(4);
	    if(los!=3)
	    {
	        GInfo(playerid,"~w~silnik ~g~uruchomiony",3);
    		SetVehicleParamsEx(v,true,lights,alarm,doors,bonnet,boot,objective);
		    TextDrawShowForPlayer(playerid,Licznik[playerid]);
		    PokazFirmaTD(playerid);
		    TextDrawShowForPlayer(playerid, Zones[playerid]);
    		return 1;
	    }
	    else
	    {
	        GInfo(playerid,"~w~silnik ~r~nieuruchomiony",3);
	    }
	}
    return 1;
}

stock LosujMisje(playerid)//losuje misje
{
	new los=random(LIMIT_LADUNKOW);
	if(LadunekInfo[los][lAktywny]==1&&OstatniaMisja[playerid]!=los)
	{
		MisjaID[playerid]=los;
  		return MisjaID[playerid];
	}
	return 999;
}
/*
stock AnulujMisje(playerid)//anuluje misje
{
	if(Misja[playerid]==true)
	{
	    Misja[playerid]=false;
	    MisjaStopien[playerid]=0;
	    PlayerInfo[playerid][pMisja]=0;
	    LadunekNapis(playerid,"~y~/zlecenie ~w~aby rozpoczac misje... ~y~/pomoc ~w~spis pomocnych komend");
	    ZapiszKonto(playerid);
	    DisablePlayerCheckpoint(playerid);
	}
}

stock ZmienRange(playerid)//zmienia range
{
	if(PlayerInfo[playerid][pDostarczenia]>=10) PlayerInfo[playerid][pPoziom]=1;//m≥okos
	if(PlayerInfo[playerid][pDostarczenia]>=30) PlayerInfo[playerid][pPoziom]=2;//amator
	if(PlayerInfo[playerid][pDostarczenia]>=60) PlayerInfo[playerid][pPoziom]=3;//poczatkujacy trucker
	if(PlayerInfo[playerid][pDostarczenia]>=100) PlayerInfo[playerid][pPoziom]=4;//trucker
	if(PlayerInfo[playerid][pDostarczenia]>=300) PlayerInfo[playerid][pPoziom]=5;//doúwiadczony trucker
	if(PlayerInfo[playerid][pDostarczenia]>=500) PlayerInfo[playerid][pPoziom]=6;//úwietny transporter
	if(PlayerInfo[playerid][pDostarczenia]>=1000) PlayerInfo[playerid][pPoziom]=7;//perfekcyjny transporter
	if(PlayerInfo[playerid][pDostarczenia]>=1500) PlayerInfo[playerid][pPoziom]=8;//w≥adca ciÍøarÛwki
	if(PlayerInfo[playerid][pDostarczenia]>=2500) PlayerInfo[playerid][pPoziom]=9;//doskona≥y trucker
	if(PlayerInfo[playerid][pDostarczenia]>=4500) PlayerInfo[playerid][pPoziom]=10;//krÛl szos
	return 1;
}
*/
stock Nick(playerid)//zwraca nick
{
	new nick[MAX_PLAYER_NAME];
	GetPlayerName(playerid, nick, sizeof(nick));
	return nick;
}

strrest(string[], idx)//do pisania
{
    new ret[80];
    strmid(ret, string, idx, strlen(string));
    return ret;
}

//nazwa bryki
stock GetVehicleName(vehicleid)
{
	new tmp = GetVehicleModel(vehicleid) - 400;
	return nazwypojazdow[tmp];
}


stock ToPD(playerid)//sprawdza czy to policjant
{
    new s=GetPlayerSkin(playerid);
	if((s==280||s==282||s==283||s==265||s==266||s==284)&&PlayerInfo[playerid][pFrakcja]==1)
	{
		return 1;
	}
	return 0;
}

stock ToPOMOC(playerid)//sprawdza czy to Pomoc Drogowa
{
    new s=GetPlayerSkin(playerid);
	if((s==27||s==16||s==8||s==56)&&PlayerInfo[playerid][pFrakcja]==2)
	{
		return 1;
	}
	return 0;
}

stock ToLOT(playerid)//sprawdza czy to Firma Lotnicza
{
    new s=GetPlayerSkin(playerid);
	if((s==61||s==171||s==172)&&PlayerInfo[playerid][pFrakcja]==3)
	{
		return 1;
	}
	return 0;
}

stock ToST(playerid)//sprawdza czy to SpeedTrans
{
    new s=GetPlayerSkin(playerid);
	if((s==126||s==128)&&PlayerInfo[playerid][pFrakcja]==10)
	{
		return 1;
	}
	return 0;
}
stock ToET(playerid)//sprawdza czy to Euro Trans
{
    new s=GetPlayerSkin(playerid);
	if((s==3||s==29)&&PlayerInfo[playerid][pFrakcja]==11)
	{
		return 1;
	}
	return 0;
}
stock ToTAXI(playerid)//sprawdza czy to Euro Trans
{
    new s=GetPlayerSkin(playerid);
	if((s==86||s==93)&&PlayerInfo[playerid][pFrakcja]==4)
	{
		return 1;
	}
	return 0;
}
stock ToRICO(playerid)//sprawdza czy to Euro Trans
{
    new s=GetPlayerSkin(playerid);
	if((s==233||s==294)&&PlayerInfo[playerid][pFrakcja]==12)
	{
		return 1;
	}
	return 0;
}

stock GetPlayerSpeed(playerid)// km/h by destroyer
{
	new Float:x,Float:y,Float:z,Float:predkosc;
	if(IsPlayerInAnyVehicle(playerid)) GetVehicleVelocity(GetPlayerVehicleID(playerid),x,y,z); else GetPlayerVelocity(playerid,x,y,z);
	predkosc=floatsqroot((x*x)+(y*y)+(z*z))*198;
	return floatround(predkosc);
}

//czyszczenie czatu
stock CzyscCzat(playerid, linie)
{
	if(IsPlayerConnected(playerid))
	{
		for(new i=0; i<linie; i++)
		{
			SendClientMessage(playerid, KOLOR_BIALY, " ");
		}
	}
	return 1;
}

//wyswietlanie info
stock GInfo(playerid,text[],typ)
{
	GameTextForPlayer(playerid,text,10000,typ);
	return 1;
}

stock Info(playerid,text[])
{
	ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,""C_POMARANCZOWY"Hard-Truck",text,"Zatwierdü","");
	return 1;
}

//sprawdza lvl adma
stock ToAdminLevel(playerid,level)
{
	if(IsPlayerConnected(playerid)&&PlayerInfo[playerid][pAdmin]>=level)
	{
 		return true;
	}
	return false;
}

//wywalanie i zapis przed tym
stock dKick(playerid)
{
	ZapiszKonto(playerid);
	Kick(playerid);
	return 1;
}

stock dBan(playerid)
{
	ZapiszKonto(playerid);
	Ban(playerid);
	return 1;
}

stock dBanEx(playerid,text[])
{
	ZapiszKonto(playerid);
	BanEx(playerid,text);
	return 1;
}
//

stock DoInRange(Float: radi, playerid, Float:x, Float:y, Float:z)//sprawdza odleglosc od miejsca
{
	if(IsPlayerInRangeOfPoint(playerid, radi, x, y, z)) return 1;
	return 0;
}

stock NaStacjiPaliw(playerid)//sprawdza czy wogÛle jestesmy na stacji paliw
{
    if(IsPlayerConnected(playerid))
	{
		if(DoInRange(16.0, playerid, -1328.6442,2677.4944,49.7787)||
		DoInRange(8.0, playerid, -737.3889,2742.2444,46.8992)||
		DoInRange(12.0, playerid, -1475.6040,1863.6361,32.3494)||
		DoInRange(10.0, playerid, 70.2113,1218.4081,18.5282)||
		DoInRange(25.0, playerid, 611.5366,1694.5262,6.7086)||
		DoInRange(16.0, playerid, 1596.3970,2197.1189,10.5371)||
		DoInRange(16.0, playerid, 2199.8953,2477.1919,10.5369)||
		DoInRange(16.0, playerid, 2640.4731,1104.9952,10.5366)||
		DoInRange(16.0, playerid, 2115.5632,923.1831,10.5362)||
		DoInRange(10.0, playerid,1380.8798,456.7491,19.6220)||
		DoInRange(12.0, playerid,652.3244,-569.8619,16.0465)||
		DoInRange(12.0, playerid,1003.0161,-939.9588,41.8959)||
		DoInRange(12.0, playerid,1944.4365,-1773.8070,13.1072)||
		DoInRange(12.0, playerid,-89.2281,-1164.0281,2.0001)||
		DoInRange(14.0, playerid,-1606.3033,-2713.9014,48.2523)||
		DoInRange(8.0, playerid,-2244.0728,-2560.5244,31.6372)||
		DoInRange(10.0, playerid,-2029.6616,157.3720,28.5526)||
		DoInRange(16.0, playerid,-2414.1677,976.4759,45.0135)||
		DoInRange(16.0, playerid,-1674.9819,413.9892,7.1797)||
		DoInRange(16.0, playerid,2150.0823,2748.0471,10.8203)||
		DoInRange(10.0, playerid,-571.8826,576.1145,17.0437)||
		DoInRange(10.0, playerid,576.9487,1088.5782,28.4437)||
		DoInRange(6.0, playerid,-1208.7374,-1003.2311,127.8290))
		{
			return 1;
		}
 	}
	return 0;
}

stock StacjaPaliw(playerid)//sprawdza nam stacje paliw na jakiej jestesmy i zwraca jej id
{
    for(new nr = 0; nr < ILOSC_STACJI; nr++)
	{
	    if(DoInRange(StacjaInfo[nr][sOdleglosc], playerid, StacjaInfo[nr][sPosX],StacjaInfo[nr][sPosY],StacjaInfo[nr][sPosZ]))
	    {
	        return nr;
	    }
	}
	return 99;
}

//wczytywanie i zapisywanie wszystkiego

forward WczytajStacje();
public WczytajStacje()
{
	//stacja 0
    CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.35 $ / 1 litr",KOLOR_POMARANCZOWY,-1328.6442,2677.4944,49.7787,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[0][sCena]=1.35;
	StacjaInfo[0][sPosX]=-1328.6442; StacjaInfo[0][sPosY]=2677.4944; StacjaInfo[0][sPosZ]=49.7787;
	StacjaInfo[0][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.29 $ / 1 litr",KOLOR_POMARANCZOWY,-737.3889,2742.2444,46.8992,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[1][sCena]=1.29;
	StacjaInfo[1][sPosX]=-737.3889; StacjaInfo[1][sPosY]=2742.2444; StacjaInfo[1][sPosZ]=46.8992;
	StacjaInfo[1][sOdleglosc]=8.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.31 $ / 1 litr",KOLOR_POMARANCZOWY,-1475.6040,1863.6361,32.3494,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[2][sCena]=1.31;
	StacjaInfo[2][sPosX]=-1475.6040; StacjaInfo[2][sPosY]=1863.6361; StacjaInfo[2][sPosZ]=32.3494;
	StacjaInfo[2][sOdleglosc]=12.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.1 $ / 1 litr",KOLOR_POMARANCZOWY,70.2113,1218.4081,18.5282,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[3][sCena]=1.1;
	StacjaInfo[3][sPosX]=70.2113; StacjaInfo[3][sPosY]=1218.4081; StacjaInfo[3][sPosZ]=18.5282;
	StacjaInfo[3][sOdleglosc]=10.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.29 $ / 1 litr",KOLOR_POMARANCZOWY,611.5366,1694.5262,6.7086,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[4][sCena]=1.29;
	StacjaInfo[4][sPosX]=611.5366; StacjaInfo[4][sPosY]=1694.5262; StacjaInfo[4][sPosZ]=6.7086;
	StacjaInfo[4][sOdleglosc]=25.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.49 $ / 1 litr",KOLOR_POMARANCZOWY,1596.3970,2197.1189,10.5371,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[5][sCena]=1.49;
	StacjaInfo[5][sPosX]=1596.3970; StacjaInfo[5][sPosY]=2197.1189; StacjaInfo[5][sPosZ]=10.5371;
	StacjaInfo[5][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.32 $ / 1 litr",KOLOR_POMARANCZOWY,2199.8953,2477.1919,10.5369,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[6][sCena]=1.32;
	StacjaInfo[6][sPosX]=2199.8953; StacjaInfo[6][sPosY]=2477.1919; StacjaInfo[6][sPosZ]=10.5369;
	StacjaInfo[6][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"0.98 $ / 1 litr",KOLOR_POMARANCZOWY,2640.4731,1104.9952,10.5366,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[7][sCena]=0.98;
	StacjaInfo[7][sPosX]=2640.4731; StacjaInfo[7][sPosY]=1104.9952; StacjaInfo[7][sPosZ]=10.5366;
	StacjaInfo[7][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.25 $ / 1 litr",KOLOR_POMARANCZOWY,2115.5632,923.1831,10.5362,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[8][sCena]=1.25;
	StacjaInfo[8][sPosX]=2115.5632; StacjaInfo[8][sPosY]=923.1831; StacjaInfo[8][sPosZ]=10.5362;
	StacjaInfo[8][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.56 $ / 1 litr",KOLOR_POMARANCZOWY,1380.8798,456.7491,19.6220,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[9][sCena]=1.56;
	StacjaInfo[9][sPosX]=1380.8798; StacjaInfo[9][sPosY]=456.7491; StacjaInfo[9][sPosZ]=19.6220;
	StacjaInfo[9][sOdleglosc]=10.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.42 $ / 1 litr",KOLOR_POMARANCZOWY,652.3244,-569.8619,16.0465,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[10][sCena]=1.42;
	StacjaInfo[10][sPosX]=652.3244; StacjaInfo[10][sPosY]=-569.8619; StacjaInfo[10][sPosZ]=16.0465;
	StacjaInfo[10][sOdleglosc]=12.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.1 $ / 1 litr",KOLOR_POMARANCZOWY,1003.0161,-939.9588,41.8959,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[11][sCena]=1.1;
	StacjaInfo[11][sPosX]=1003.0161; StacjaInfo[11][sPosY]=-939.9588; StacjaInfo[11][sPosZ]=41.8959;
	StacjaInfo[11][sOdleglosc]=12.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"0.87 $ / 1 litr",KOLOR_POMARANCZOWY,1944.4365,-1773.8070,13.1072,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[12][sCena]=0.87;
	StacjaInfo[12][sPosX]=1944.4365; StacjaInfo[12][sPosY]=-1773.8070; StacjaInfo[12][sPosZ]=13.1072;
	StacjaInfo[12][sOdleglosc]=12.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.26 $ / 1 litr",KOLOR_POMARANCZOWY,-89.2281,-1164.0281,2.0001,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[13][sCena]=1.26;
	StacjaInfo[13][sPosX]=-89.2281; StacjaInfo[13][sPosY]=-1164.0281; StacjaInfo[13][sPosZ]=2.0001;
	StacjaInfo[13][sOdleglosc]=12.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.21 $ / 1 litr",KOLOR_POMARANCZOWY,-1606.3033,-2713.9014,48.2523,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[14][sCena]=1.21;
	StacjaInfo[14][sPosX]=-1606.3033; StacjaInfo[14][sPosY]=-2713.9014; StacjaInfo[14][sPosZ]=48.2523;
	StacjaInfo[14][sOdleglosc]=14.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.16 $ / 1 litr",KOLOR_POMARANCZOWY,-2244.0728,-2560.5244,31.6372,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[15][sCena]=1.16;
	StacjaInfo[15][sPosX]=-2244.0728; StacjaInfo[15][sPosY]=-2560.5244; StacjaInfo[15][sPosZ]=31.6372;
	StacjaInfo[15][sOdleglosc]=8.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.36 $ / 1 litr",KOLOR_POMARANCZOWY,-2029.6616,157.3720,28.5526,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[16][sCena]=1.36;
	StacjaInfo[16][sPosX]=-2029.6616; StacjaInfo[16][sPosY]=157.3720; StacjaInfo[16][sPosZ]=28.5526;
	StacjaInfo[16][sOdleglosc]=10.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.24 $ / 1 litr",KOLOR_POMARANCZOWY,-2414.1677,976.4759,45.0135,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[17][sCena]=1.24;
	StacjaInfo[17][sPosX]=-2414.1677; StacjaInfo[17][sPosY]=976.4759; StacjaInfo[17][sPosZ]=45.0135;
	StacjaInfo[17][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.11 $ / 1 litr",KOLOR_POMARANCZOWY,-1674.9819,413.9892,7.1797,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[18][sCena]=1.11;
	StacjaInfo[18][sPosX]=-1674.9819; StacjaInfo[18][sPosY]=413.9892; StacjaInfo[18][sPosZ]=7.1797;
	StacjaInfo[18][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.19 $ / 1 litr",KOLOR_POMARANCZOWY,2150.0823,2748.0471,10.8203,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[19][sCena]=1.19;
	StacjaInfo[19][sPosX]=2150.0823; StacjaInfo[19][sPosY]=2748.0471; StacjaInfo[19][sPosZ]=10.8203;
	StacjaInfo[19][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.19 $ / 1 litr",KOLOR_POMARANCZOWY,2150.0823,2748.0471,10.8203,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[19][sCena]=1.19;
	StacjaInfo[19][sPosX]=-571.8826; StacjaInfo[19][sPosY]=576.1145; StacjaInfo[19][sPosZ]=17.0437;
	StacjaInfo[19][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.19 $ / 1 litr",KOLOR_POMARANCZOWY,2150.0823,2748.0471,10.8203,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[19][sCena]=1.19;
	StacjaInfo[19][sPosX]=576.9487; StacjaInfo[19][sPosY]=1088.5782; StacjaInfo[19][sPosZ]=28.4437;
	StacjaInfo[19][sOdleglosc]=16.0;
	//kolejna
	CreateDynamic3DTextLabel("Stacja benzynowa\n"C_ZOLTY"/tankuj\n"C_ZIELONY"1.19 $ / 1 litr",KOLOR_POMARANCZOWY,2150.0823,2748.0471,10.8203,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,25.0);
	StacjaInfo[19][sCena]=1.59;
	StacjaInfo[19][sPosX]=-1208.737426; StacjaInfo[19][sPosY]=-1003.231140; StacjaInfo[19][sPosZ]=127.829093;
	StacjaInfo[19][sOdleglosc]=6.0;
	return 1;
}

forward WczytajDomy();
public WczytajDomy()
{
	new file[25];
    for(new nr = 0; nr < LIMIT_DOMOW; nr++)
	{
		format(file,sizeof(file),"Truck/Domy/%d.ini",nr);
		if(DOF_FileExists(file))
	 	{
		 	DomInfo[nr][dAktywny]=DOF_GetInt(file,"Aktywny");
		 	DomInfo[nr][dWejscieX]=DOF_GetFloat(file,"WejscieX");
		 	DomInfo[nr][dWejscieY]=DOF_GetFloat(file,"WejscieY");
		 	DomInfo[nr][dWejscieZ]=DOF_GetFloat(file,"WejscieZ");
		 	DomInfo[nr][dWejscieInt]=DOF_GetInt(file,"WejscieInt");
		 	DomInfo[nr][dWejscieVir]=DOF_GetInt(file,"WejscieVir");
		 	DomInfo[nr][dWyjscieX]=DOF_GetFloat(file,"WyjscieX");
		 	DomInfo[nr][dWyjscieY]=DOF_GetFloat(file,"WyjscieY");
		 	DomInfo[nr][dWyjscieZ]=DOF_GetFloat(file,"WyjscieZ");
		 	DomInfo[nr][dWyjscieInt]=DOF_GetInt(file,"WyjscieInt");
		 	DomInfo[nr][dWlasciciel]=DOF_GetString(file,"Wlasciciel");
		 	DomInfo[nr][dOpis]=DOF_GetString(file,"Opis");
		 	DomInfo[nr][dKupiony]=DOF_GetInt(file,"Kupiony");
		 	DomInfo[nr][dKoszt]=DOF_GetInt(file,"Koszt");
		 	DomInfo[nr][dZamkniety]=DOF_GetInt(file,"Zamkniety");

		 	if(DomInfo[nr][dKupiony]==0 && DomInfo[nr][dAktywny]==1)
		 	{
		 		DomPickup[nr]=CreateDynamicPickup(1273,1,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ],DomInfo[nr][dWejscieVir],DomInfo[nr][dWejscieInt],-1,45.0);
                format(dstring, sizeof(dstring),""C_ZIELONY"ID domu: "C_ZOLTY"%d\n"C_ZIELONY"W≥aúciciel: "C_ZOLTY"brak\n"C_ZIELONY"Opis: "C_ZOLTY"brak\n"C_ZIELONY"Koszt: "C_ZOLTY"%d", nr, DomInfo[nr][dKoszt]);
				dtexty[nr] = CreateDynamic3DTextLabel(dstring, KOLOR_ZOLTY, DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);
				dikonka[nr] = CreateDynamicMapIcon(DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 32, 0, -1, -1, -1, 100.0);

		 	}
	  		else if(DomInfo[nr][dKupiony]==1 && DomInfo[nr][dAktywny]==1)
    		{
		 		DomPickup[nr]=CreateDynamicPickup(1239,1,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ],DomInfo[nr][dWejscieVir],DomInfo[nr][dWejscieInt],-1,45.0);
				format(dstring, sizeof(dstring),""C_ZIELONY"ID domu: "C_ZOLTY"%d\n"C_ZIELONY"W≥aúciciel: "C_ZOLTY"%s\n"C_ZIELONY"Opis: "C_ZOLTY"%s\n"C_ZIELONY"Koszt: "C_ZOLTY"%d", nr, DomInfo[nr][dWlasciciel], DomInfo[nr][dOpis], DomInfo[nr][dKoszt]);
				dtexty[nr] = CreateDynamic3DTextLabel(dstring, KOLOR_ZOLTY, DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);
				dikonka[nr] = CreateDynamicMapIcon(DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 31, 0, -1, -1, -1, 100.0);
			}
			printf("Zaladowano dom o ID: %d", nr);
		}
		else
		{
			DomInfo[nr][dAktywny]=0;
		}
	}
	print("\nWczytano domy!\n");
	return 1;
}

forward ZapiszDom(nr);
public ZapiszDom(nr)
{
    if(nr<0||nr>LIMIT_DOMOW) return 1;
	new file[25];
	format(file,sizeof(file),"Truck/Domy/%d.ini",nr);
	if(DOF_FileExists(file))
	{
		DOF_SetInt(file,"Aktywny",DomInfo[nr][dAktywny]);
		DOF_SetFloat(file,"WejscieX",DomInfo[nr][dWejscieX]);
		DOF_SetFloat(file,"WejscieY",DomInfo[nr][dWejscieY]);
		DOF_SetFloat(file,"WejscieZ",DomInfo[nr][dWejscieZ]);
        DOF_SetInt(file,"WejscieInt",DomInfo[nr][dWejscieInt]);
        DOF_SetInt(file,"WejscieVir",DomInfo[nr][dWejscieVir]);
        DOF_SetFloat(file,"WyjscieX",DomInfo[nr][dWyjscieX]);
		DOF_SetFloat(file,"WyjscieY",DomInfo[nr][dWyjscieY]);
		DOF_SetFloat(file,"WyjscieZ",DomInfo[nr][dWyjscieZ]);
        DOF_SetInt(file,"WyjscieInt",DomInfo[nr][dWyjscieInt]);
        DOF_SetString(file,"Wlasciciel",DomInfo[nr][dWlasciciel]);
        DOF_SetString(file,"Opis",DomInfo[nr][dOpis]);
        DOF_SetInt(file,"Kupiony",DomInfo[nr][dKupiony]);
        DOF_SetInt(file,"Koszt",DomInfo[nr][dKoszt]);
        DOF_SetInt(file,"Zamkniety",DomInfo[nr][dZamkniety]);
		DOF_SaveFile();
	}
	else
	{
	    DOF_CreateFile(file);
		DOF_SetInt(file,"Aktywny",DomInfo[nr][dAktywny]);
		DOF_SetFloat(file,"WejscieX",DomInfo[nr][dWejscieX]);
		DOF_SetFloat(file,"WejscieY",DomInfo[nr][dWejscieY]);
		DOF_SetFloat(file,"WejscieZ",DomInfo[nr][dWejscieZ]);
        DOF_SetInt(file,"WejscieInt",DomInfo[nr][dWejscieInt]);
        DOF_SetInt(file,"WejscieVir",DomInfo[nr][dWejscieVir]);
        DOF_SetFloat(file,"WyjscieX",DomInfo[nr][dWyjscieX]);
		DOF_SetFloat(file,"WyjscieY",DomInfo[nr][dWyjscieY]);
		DOF_SetFloat(file,"WyjscieZ",DomInfo[nr][dWyjscieZ]);
        DOF_SetInt(file,"WyjscieInt",DomInfo[nr][dWyjscieInt]);
        DOF_SetString(file,"Wlasciciel",DomInfo[nr][dWlasciciel]);
        DOF_SetString(file,"Opis",DomInfo[nr][dOpis]);
        DOF_SetInt(file,"Kupiony",DomInfo[nr][dKupiony]);
        DOF_SetInt(file,"Koszt",DomInfo[nr][dKoszt]);
        DOF_SetInt(file,"Zamkniety",DomInfo[nr][dZamkniety]);
		DOF_SaveFile();
	}
	return 1;
}

forward WczytajLadunki();
public WczytajLadunki()
{
	new file[25];
    for(new nr = 0; nr < LIMIT_LADUNKOW; nr++)
	{
		format(file,sizeof(file),"Truck/Ladunki/%d.ini",nr);
		if(DOF_FileExists(file))
	 	{
		 	LadunekInfo[nr][lAktywny]=DOF_GetInt(file,"Aktywny");
		 	LadunekInfo[nr][lTowar]=DOF_GetString(file,"Towar");
		 	LadunekInfo[nr][lTowarKoszt]=DOF_GetFloat(file,"TowarKoszt");
		 	LadunekInfo[nr][lZaladunek]=DOF_GetString(file,"Zaladunek");
		 	LadunekInfo[nr][lPosX]=DOF_GetInt(file,"PosX");
		 	LadunekInfo[nr][lPosY]=DOF_GetInt(file,"PosY");
		 	LadunekInfo[nr][lPosZ]=DOF_GetInt(file,"PosZ");
		 	LadunekInfo[nr][lDostarczenie]=DOF_GetString(file,"Dostarczenie");
		 	LadunekInfo[nr][lPos2X]=DOF_GetInt(file,"Pos2X");
		 	LadunekInfo[nr][lPos2Y]=DOF_GetInt(file,"Pos2Y");
		 	LadunekInfo[nr][lPos2Z]=DOF_GetInt(file,"Pos2Z");
		 	if(LadunekInfo[nr][lAktywny]==1)
		 	{
		 	    printf("Ladunek [%d] %s wczytano!",nr,LadunekInfo[nr][lTowar]);
		 	}
		}
		else
		{
			LadunekInfo[nr][lAktywny]=0;
		}
	}
	print("\nWczytano ladunki!\n");
	return 1;
}

forward ZapiszLadunek(nr);
public ZapiszLadunek(nr)
{
    if(nr<0||nr>LIMIT_LADUNKOW) return 1;
	new file[25];
	format(file,sizeof(file),"Truck/Ladunki/%d.ini",nr);
	if(DOF_FileExists(file))
	{
		DOF_SetInt(file,"Aktywny",LadunekInfo[nr][lAktywny]);
		DOF_SetString(file,"Towar",LadunekInfo[nr][lTowar]);
		DOF_SetFloat(file,"TowarKoszt",LadunekInfo[nr][lTowarKoszt]);
		DOF_SetString(file,"Zaladunek",LadunekInfo[nr][lZaladunek]);
		DOF_SetFloat(file,"PosX",LadunekInfo[nr][lPosX]);
		DOF_SetFloat(file,"PosY",LadunekInfo[nr][lPosY]);
		DOF_SetFloat(file,"PosZ",LadunekInfo[nr][lPosZ]);
		DOF_SetString(file,"Dostarczenie",LadunekInfo[nr][lDostarczenie]);
		DOF_SetFloat(file,"Pos2X",LadunekInfo[nr][lPos2X]);
		DOF_SetFloat(file,"Pos2Y",LadunekInfo[nr][lPos2Y]);
		DOF_SetFloat(file,"Pos2Z",LadunekInfo[nr][lPos2Z]);
		DOF_SaveFile();
	}
	else
	{
	    DOF_CreateFile(file);
		DOF_SetInt(file,"Aktywny",LadunekInfo[nr][lAktywny]);
		DOF_SetString(file,"Towar",LadunekInfo[nr][lTowar]);
		DOF_SetFloat(file,"TowarKoszt",LadunekInfo[nr][lTowarKoszt]);
		DOF_SetString(file,"Zaladunek",LadunekInfo[nr][lZaladunek]);
		DOF_SetFloat(file,"PosX",LadunekInfo[nr][lPosX]);
		DOF_SetFloat(file,"PosY",LadunekInfo[nr][lPosY]);
		DOF_SetFloat(file,"PosZ",LadunekInfo[nr][lPosZ]);
		DOF_SetString(file,"Dostarczenie",LadunekInfo[nr][lDostarczenie]);
		DOF_SetFloat(file,"Pos2X",LadunekInfo[nr][lPos2X]);
		DOF_SetFloat(file,"Pos2Y",LadunekInfo[nr][lPos2Y]);
		DOF_SetFloat(file,"Pos2Z",LadunekInfo[nr][lPos2Z]);
		DOF_SaveFile();
	}
	return 1;
}

forward WczytajTexty();
public WczytajTexty()
{
	new file[25];
    for(new nr = 0; nr < LIMIT_TEXTOW; nr++)
	{
		format(file,sizeof(file),"Truck/Texty/%d.ini",nr);
		if(DOF_FileExists(file))
	 	{
		 	TextInfo[nr][tAktywny]=DOF_GetInt(file,"Aktywny");
		 	TextInfo[nr][tNapis]=DOF_GetString(file,"Napis");
		 	TextInfo[nr][tPosX]=DOF_GetFloat(file,"PosX");
		 	TextInfo[nr][tPosY]=DOF_GetFloat(file,"PosY");
		 	TextInfo[nr][tPosZ]=DOF_GetFloat(file,"PosZ");
		 	if(TextInfo[nr][tAktywny]==1)
		 	{
		 	    printf("Text3d id: [%d] wczytano!",nr);
		 	    TextNapis[nr]=CreateDynamic3DTextLabel(ColouredText(TextInfo[nr][tNapis]),KOLOR_BIALY,TextInfo[nr][tPosX],TextInfo[nr][tPosY],TextInfo[nr][tPosZ],40.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,-1,-1,-1,-1,40.0);
		 	}
		}
		else
		{
			TextInfo[nr][tAktywny]=0;
		}
	}
	print("\nWczytano texty3d!\n");
	return 1;
}

forward ZapiszText(nr);
public ZapiszText(nr)
{
    if(nr<0||nr>LIMIT_TEXTOW) return 1;
	new file[25];
	format(file,sizeof(file),"Truck/Texty/%d.ini",nr);
	if(DOF_FileExists(file))
	{
		DOF_SetInt(file,"Aktywny",TextInfo[nr][tAktywny]);
        DOF_SetString(file,"Napis",TextInfo[nr][tNapis]);
        DOF_SetFloat(file,"PosX",TextInfo[nr][tPosX]);
        DOF_SetFloat(file,"PosY",TextInfo[nr][tPosY]);
        DOF_SetFloat(file,"PosZ",TextInfo[nr][tPosZ]);
		DOF_SaveFile();
	}
	else
	{
	    DOF_CreateFile(file);
		DOF_SetInt(file,"Aktywny",TextInfo[nr][tAktywny]);
        DOF_SetString(file,"Napis",TextInfo[nr][tNapis]);
        DOF_SetFloat(file,"PosX",TextInfo[nr][tPosX]);
        DOF_SetFloat(file,"PosY",TextInfo[nr][tPosY]);
        DOF_SetFloat(file,"PosZ",TextInfo[nr][tPosZ]);
		DOF_SaveFile();
	}
	return 1;
}

//logowanie
forward GraczSieLoguje(playerid,haslo[]);
public GraczSieLoguje(playerid,haslo[])
{
	if(IsPlayerConnected(playerid)&&Zalogowany[playerid]==false)
	{
		new file[45],nick[MAX_PLAYER_NAME];
		GetPlayerName(playerid,nick,sizeof(nick));
		UpperToLower(nick);
 		format(file,sizeof(file),"Truck/Konta/%s.ini",nick);
	 	PlayerInfo[playerid][pHaslo]=DOF_GetString(file,"Haslo");//wczytujemy has≥o
		if(strcmp(PlayerInfo[playerid][pHaslo],haslo,true))//jeøeli has≥o nie pasuje kick
		{
		    ShowPlayerDialog(playerid,2,DIALOG_STYLE_PASSWORD,""C_ZOLTY"Hard-Truck: "C_BIALY"Logowanie",""C_BIALY"Witaj!\nTen login jest zarejestrowany!\nW celu zalogowania siÍ wpisz "C_ZOLTY"has≥o"C_BIALY":\n\n"C_CZERWONY"Podales niewlasciwe haslo. Sprobuj ponownie","Zaloguj","Wyjdü");
			return 0;
		}//jesli sie powiedzie to wczytujemy reszte
		PlayerInfo[playerid][pKonto]=DOF_GetInt(file,"Konto");
		PlayerInfo[playerid][pAdmin]=DOF_GetInt(file,"Admin");
		PlayerInfo[playerid][pPremium]=DOF_GetInt(file,"Premium");
		PlayerInfo[playerid][pJail]=DOF_GetInt(file,"Jail");
		PlayerInfo[playerid][pWyciszony]=DOF_GetInt(file,"Wyciszony");
		PlayerInfo[playerid][pWarny]=DOF_GetInt(file,"Warny");
		PlayerInfo[playerid][pDostarczenia]=DOF_GetInt(file,"Dostarczenia");
		PlayerInfo[playerid][pScigany]=DOF_GetInt(file,"Scigany");
		PlayerInfo[playerid][pMandat]=DOF_GetInt(file,"Mandat");
		PlayerInfo[playerid][pKasa]=DOF_GetInt(file,"Kasa");
		PlayerInfo[playerid][pBank]=DOF_GetInt(file,"Bank");
		PlayerInfo[playerid][pFrakcja]=DOF_GetInt(file,"Frakcja");
		PlayerInfo[playerid][pLider]=DOF_GetInt(file,"Lider");
		PlayerInfo[playerid][pDom]=DOF_GetInt(file,"Dom");
		PlayerInfo[playerid][pWizyty]=DOF_GetInt(file,"Wizyty");
		PlayerInfo[playerid][pMisja]=DOF_GetInt(file,"Misja");
		PlayerInfo[playerid][pToll]=DOF_GetInt(file,"ViaToll");
		PlayerInfo[playerid][pPrawkoB]=DOF_GetInt(file,"PrawkoB");
		PlayerInfo[playerid][pPrawkoCE]=DOF_GetInt(file,"PrawkoCE");
		PlayerInfo[playerid][pPrawkoA1]=DOF_GetInt(file,"PrawkoA1");
		PlayerInfo[playerid][pPunkty]=DOF_GetInt(file,"PunktyKarne");
		SetPVarInt(playerid, "PunktyToll", PlayerInfo[playerid][pToll]);
		PlayerInfo[playerid][pIDMisji]=DOF_GetInt(file, "IDMisji");
		PlayerInfo[playerid][pDostarczen]=DOF_GetInt(file, "Dostarczen");
		PlayerInfo[playerid][pEmail] = DOF_GetString(file,"Email");
		PlayerInfo[playerid][pDJ] = DOF_GetInt(file,"DJ");

		//PlayerInfo[playerid][pAuto]=DOF_GetInt(file,"Auto"); //id auta
		//PlayerInfo[playerid][pAuto2]=DOF_GetInt(file,"Auto2"); // X
		//PlayerInfo[playerid][pAuto3]=DOF_GetInt(file,"Auto3"); // Y
		//PlayerInfo[playerid][pAuto4]=DOF_GetInt(file,"Auto4"); // Z
		//PlayerInfo[playerid][pAuto5]=DOF_GetInt(file,"Auto5"); // A
		if(PlayerInfo[playerid][pKonto]==2)//
		{
			Info(playerid,""C_CZERWONY"To konto jest zablokowane!");
			dKick(playerid);
			return 0;
		}
		dUstawKase(playerid,PlayerInfo[playerid][pKasa]);
		if(PlayerInfo[playerid][pMisja]==1)
		{
		    Info(playerid,""C_ZOLTY"Wyszed≥eú z serwera nie ukoÒczywszy zlecenia.\n"C_CZERWONY"Zostajesz ukarany: 1000$");
			dDodajKase(playerid,-1000);
			PlayerInfo[playerid][pMisja]=0;
		}
		if(PlayerInfo[playerid][pWyciszony]>=1)
		{
			KillTimer(MuteTimer[playerid]);
			MuteTimer[playerid]=SetTimerEx("Odcisz",60000*PlayerInfo[playerid][pWyciszony],false,"i",playerid);
		}
	 	TogglePlayerSpectating(playerid, false);
		PlayerInfo[playerid][pWizyty]++;
		SendClientMessage(playerid,KOLOR_ZOLTY,"Zalogowa≥eú siÍ poprawnie! Wybierz postaÊ i graj!");
		Zalogowany[playerid]=true;
		format(dstring, sizeof(dstring), "%s [%d] "C_BIALY"do≥πczy≥ do gry!",Nick(playerid),playerid);
		SendClientMessageToAll(KOLOR_BEZOWY,dstring);

		return 1;
	}
	return 0;
}

//rejestrowanie
forward GraczSieRejestruje(playerid, haslo[]);
public GraczSieRejestruje(playerid, haslo[])
{
    if(IsPlayerConnected(playerid)&&Zalogowany[playerid]==false)
	{
		new file[45],nick[MAX_PLAYER_NAME];
		GetPlayerName(playerid,nick,sizeof(nick));
		UpperToLower(nick);
	 	format(file,sizeof(file),"Truck/Konta/%s.ini",nick);
	 	DOF_CreateFile(file);
	 	strmid(PlayerInfo[playerid][pHaslo], haslo, 0, strlen(haslo), 64);
	 	DOF_SetString(file,"Haslo",PlayerInfo[playerid][pHaslo]);
		DOF_SetInt(file,"Konto",PlayerInfo[playerid][pKonto]);
		DOF_SetInt(file,"Admin",PlayerInfo[playerid][pAdmin]);
		DOF_SetInt(file,"Premium",PlayerInfo[playerid][pPremium]);
		DOF_SetInt(file,"Jail",PlayerInfo[playerid][pJail]);
		DOF_SetInt(file,"Wyciszony",PlayerInfo[playerid][pWyciszony]);
		DOF_SetInt(file,"Warny",PlayerInfo[playerid][pWarny]);
		DOF_SetInt(file,"Dostarczenia",PlayerInfo[playerid][pDostarczenia]);
		DOF_SetInt(file,"Scigany",PlayerInfo[playerid][pScigany]);
		DOF_SetInt(file,"Mandat",PlayerInfo[playerid][pMandat]);
		DOF_SetInt(file,"Kasa",PlayerInfo[playerid][pKasa]);
		DOF_SetInt(file,"Bank",PlayerInfo[playerid][pBank]);
		DOF_SetInt(file,"Frakcja",PlayerInfo[playerid][pFrakcja]);
		DOF_SetInt(file,"Lider",PlayerInfo[playerid][pLider]);
		DOF_SetInt(file,"Dom",PlayerInfo[playerid][pDom]);
		DOF_SetInt(file,"Wizyty",PlayerInfo[playerid][pWizyty]);
		DOF_SetInt(file,"Misja",PlayerInfo[playerid][pMisja]);
	    DOF_SetInt(file,"ViaToll",GetPVarInt(playerid, "PunktyToll"));
	    DOF_SetInt(file,"IDMisji", PlayerInfo[playerid][pIDMisji]);
	    DOF_SetInt(file,"Dostarczen", PlayerInfo[playerid][pDostarczen]);

		DOF_SetInt(file,"PrawkoB", PlayerInfo[playerid][pPrawkoB]);
		DOF_SetInt(file,"PrawkoCE", PlayerInfo[playerid][pPrawkoCE]);
		DOF_SetInt(file,"PrawkoA1", PlayerInfo[playerid][pPrawkoA1]);

		DOF_SetInt(file,"PunktyKarne", PlayerInfo[playerid][pPunkty]);

	    DOF_SetString(file,"Email",PlayerInfo[playerid][pEmail]);
	    DOF_SetInt(file, "DJ", PlayerInfo[playerid][pDJ]);

 		DOF_SaveFile();
 		TogglePlayerSpectating(playerid, false);
 		Zalogowany[playerid]=true;
 		SendClientMessage(playerid,KOLOR_ZOLTY,"Konto utworzone poprawnie! Wybierz postaÊ i graj!");
   		dUstawKase(playerid,2500);
	    format(dstring, sizeof(dstring), "%s [%d] "C_BIALY"do≥πczy≥ do gry!",Nick(playerid),playerid);
		SendClientMessageToAll(KOLOR_BEZOWY,dstring);
		ShowPlayerDialog(playerid, GUI_EMAIL, DIALOG_STYLE_INPUT, "Email", "Podaj swÛj email byúmy mogli siÍ szybko z tobπ skontaktowaÊ lub byú,\nmÛg≥ odzyskaÊ utracone has≥o. Gdy zapomnisz has≥a bπdü niewiadomo co\nsiÍ z nim stanie odzyskanie bÍdzie moøliwe tylko na email!\n\n"C_CZERWONY"Poniøej podaj swÛj email:", "Zapisz", "");
		Pierwszy[playerid]=1;
	}
	return 1;
}

//zapisywanie
forward ZapiszKonto(playerid);
public ZapiszKonto(playerid)
{
	if(IsPlayerConnected(playerid)&&Zalogowany[playerid]==true)
	{
		new file[45],nick[MAX_PLAYER_NAME];
		GetPlayerName(playerid,nick,sizeof(nick));
		UpperToLower(nick);
		format(file,sizeof(file),"Truck/Konta/%s.ini",nick);
		PlayerInfo[playerid][pKasa]=dWyswietlKase(playerid);
		PlayerInfo[playerid][pDostarczen]=GetPlayerScore(playerid);
		DOF_SetString(file,"Haslo",PlayerInfo[playerid][pHaslo]);
		DOF_SetInt(file,"Konto",PlayerInfo[playerid][pKonto]);
		DOF_SetInt(file,"Admin",PlayerInfo[playerid][pAdmin]);
		DOF_SetInt(file,"Premium",PlayerInfo[playerid][pPremium]);
		DOF_SetInt(file,"Jail",PlayerInfo[playerid][pJail]);
		DOF_SetInt(file,"Wyciszony",PlayerInfo[playerid][pWyciszony]);
		DOF_SetInt(file,"Warny",PlayerInfo[playerid][pWarny]);
		DOF_SetInt(file,"Dostarczenia",PlayerInfo[playerid][pDostarczenia]);
		DOF_SetInt(file,"Scigany",PlayerInfo[playerid][pScigany]);
		DOF_SetInt(file,"Mandat",PlayerInfo[playerid][pMandat]);
		DOF_SetInt(file,"Kasa",PlayerInfo[playerid][pKasa]);
		DOF_SetInt(file,"Bank",PlayerInfo[playerid][pBank]);
		DOF_SetInt(file,"Frakcja",PlayerInfo[playerid][pFrakcja]);
		DOF_SetInt(file,"Lider",PlayerInfo[playerid][pLider]);
		DOF_SetInt(file,"Dom",PlayerInfo[playerid][pDom]);
		DOF_SetInt(file,"Wizyty",PlayerInfo[playerid][pWizyty]);
		DOF_SetInt(file,"Misja",PlayerInfo[playerid][pMisja]);

		DOF_SetInt(file,"PrawkoB", PlayerInfo[playerid][pPrawkoB]);
		DOF_SetInt(file,"PrawkoCE", PlayerInfo[playerid][pPrawkoCE]);
		DOF_SetInt(file,"PrawkoA1", PlayerInfo[playerid][pPrawkoA1]);

		DOF_SetInt(file,"PunktyKarne", PlayerInfo[playerid][pPunkty]);

	    DOF_SetInt(file,"ViaToll",GetPVarInt(playerid, "PunktyToll"));

  		DOF_SetInt(file,"IDMisji", PlayerInfo[playerid][pIDMisji]);
	    DOF_SetInt(file,"Dostarczen", PlayerInfo[playerid][pDostarczen]);

        DOF_SetString(file,"Email",PlayerInfo[playerid][pEmail]);
        DOF_SetInt(file, "DJ", PlayerInfo[playerid][pDJ]);

        DajKase(playerid, PlayerInfo[playerid][pKasa]);

		DOF_SaveFile();
 	}
	return 1;
}
/*
forward
public SaveCar(playerid)
{
    new file[45],nick[MAX_PLAYER_NAME];
	GetPlayerName(playerid,nick,sizeof(nick));
	UpperToLower(nick);
	format(file,sizeof(file),"Truck/Konta/%s.ini",nick);
	new Float: X, Float: Y, Float: Z, Float: Ang;
	GetVehiclePos(PrivCar[playerid], X, Y, Z);
	GetVehicleZAngle(PrivCar[playerid], Ang);
	PlayerInfo[playerid][pAuto2] = X;
	PlayerInfo[playerid][pAuto3] = Y;
	PlayerInfo[playerid][pAuto4] = Z;
	PlayerInfo[playerid][pAuto5] = Ang;
	PlayerInfo[playerid][pAuto] = GetVehicleModel(PrivCar[playerid]);
    DOF_SetInt(file,"Auto",PlayerInfo[playerid][pAuto]);
	DOF_SetFloat(file,"Auto2",PlayerInfo[playerid][pAuto2]);
	DOF_SetFloat(file,"Auto3",PlayerInfo[playerid][pAuto3]);
	DOF_SetFloat(file,"Auto4",PlayerInfo[playerid][pAuto4]);
	DOF_SetFloat(file,"Auto5",PlayerInfo[playerid][pAuto5]);

    DOF_SaveFile();

	return 1;
}
*/
//publice od streamera

public OnDynamicObjectMoved(objectid)//gdy dynamiczny obiekt siÍ porusza
{
	return 1;
}
public OnPlayerPickUpDynamicPickup(playerid, pickupid)//gdy gracz podnosi dynamiczny pickup
{
    for(new p = 0; p < 100; p++)
	{
		if(pickupid==DomPickup[p]&&DomInfo[p][dAktywny]==1)
 		{
 		    if(DomInfo[p][dKupiony] == 1)
			{
				format(dstring, sizeof(dstring), "~g~Dom kupiony przez~n~~w~%s~n~~r~Zamek: ~w~%d",DomInfo[p][dWlasciciel],DomInfo[p][dKupiony]);
				GInfo(playerid,dstring,3);
				return 1;
			}
			else
			{
				format(dstring, sizeof(dstring), "~g~Dom na sprzedaz~n~~w~%s~n~~y~cena: %d$~n~~p~/kupdom",DomInfo[p][dOpis],DomInfo[p][dKoszt]);
				GInfo(playerid,dstring,3);
				return 1;
			}
		}
	}
	return 1;
}
public OnPlayerLeaveDynamicCP(playerid, checkpointid)//jak gracz opusci dynamiczny checkpoint
{
	return 1;
}
public OnPlayerEnterDynamicRaceCP(playerid, checkpointid)
{
	if(zdaje[playerid] == 1)
	{
		if(checkpointid == cp1)
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
			    TogglePlayerDynamicRaceCP(playerid, cp1, 0);
			    TogglePlayerDynamicRaceCP(playerid, cp2, 1);
			}
		}
		else if(checkpointid == cp2)
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
			    TogglePlayerDynamicRaceCP(playerid, cp2, 0);
			    TogglePlayerDynamicRaceCP(playerid, cp3, 1);
			}
		}
		else if(checkpointid == cp3)
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
			    TogglePlayerDynamicRaceCP(playerid, cp3, 0);
			    TogglePlayerDynamicRaceCP(playerid, cp4, 1);
			}
		}
		else if(checkpointid == cp4)
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
			    TogglePlayerDynamicRaceCP(playerid, cp4, 0);
			    TogglePlayerDynamicRaceCP(playerid, cp5, 1);
			}
		}
		else if(checkpointid == cp5)
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
			    TogglePlayerDynamicRaceCP(playerid, cp5, 0);
			    TogglePlayerDynamicRaceCP(playerid, cp6, 1);
			}
		}
		else if(checkpointid == cp6)
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
			    TogglePlayerDynamicRaceCP(playerid, cp6, 0);
			    TogglePlayerDynamicRaceCP(playerid, cp7, 1);
			}
		}
		else if(checkpointid == cp7)
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
				new Float: carHP;
				GetVehicleHealth(wozekprawo,carHP);
				if(carHP >= 495)
				{
				    if(typPrawka[playerid] == B)
				    {
				        PlayerInfo[playerid][pPrawkoB] = 1;
				        ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Wyniki!", "GratulujÍ, zda≥eú!\nUda≥o Ci siÍ zdaÊ na prawo jazdy.\nTwÛj stan HP pojazdu by≥ wystarczajπcy by zdaÊ.\n\nOd teraz moøesz legalnie jeüdziÊ Samochodami Osobowymi.", "Ok", "");
                        ZapiszKonto(playerid);
                        TogglePlayerDynamicRaceCP(playerid, cp7, 0);
					    zdawanie = 0;
						zdaje[playerid] = 0;
						typPrawka[playerid] = 0;
						DestroyVehicle(wozekprawo);
						SpawnPlayer(playerid);
						SendClientMessageToAll(KOLOR_CZERWONY, ""C_CZERWONY"Zdawanie na prawo jazdy: "C_ZIELONY"wolne");
				    }
				    else if(typPrawka[playerid] == CE)
				    {
				        PlayerInfo[playerid][pPrawkoCE] = 1;
				        ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Wyniki!", "GratulujÍ, zda≥eú!\nUda≥o Ci siÍ zdaÊ na prawo jazdy.\nTwÛj stan HP pojazdu by≥ wystarczajπcy by zdaÊ.\n\nOd teraz moøesz legalnie jeüdziÊ Tirami z naczepami.", "Ok", "");
                        ZapiszKonto(playerid);
                        TogglePlayerDynamicRaceCP(playerid, cp7, 0);
					    zdawanie = 0;
						zdaje[playerid] = 0;
						typPrawka[playerid] = 0;
						DestroyVehicle(wozekprawo);
						SpawnPlayer(playerid);
						SendClientMessageToAll(KOLOR_CZERWONY, ""C_CZERWONY"Zdawanie na prawo jazdy: "C_ZIELONY"wolne");
				    }
				    else if(typPrawka[playerid] == A1)
				    {
				        PlayerInfo[playerid][pPrawkoA1] = 1;
				        ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Wyniki!", "GratulujÍ, zda≥eú!\nUda≥o Ci siÍ zdaÊ na prawo jazdy.\nTwÛj stan HP pojazdu by≥ wystarczajπcy by zdaÊ.\n\nOd teraz moøesz legalnie jeüdziÊ Vanami.", "Ok", "");
                        ZapiszKonto(playerid);
                        TogglePlayerDynamicRaceCP(playerid, cp7, 0);
					    zdawanie = 0;
						zdaje[playerid] = 0;
						typPrawka[playerid] = 0;
						DestroyVehicle(wozekprawo);
						SpawnPlayer(playerid);
						SendClientMessageToAll(KOLOR_CZERWONY, ""C_CZERWONY"Zdawanie na prawo jazdy: "C_ZIELONY"wolne");
				    }
				}
				else if(carHP <= 494)
				{
				    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Wyniki!", "Niestety, nie zda≥eú!\nNie uda≥o Ci siÍ zdaÊ na prawo jazdy.\nTwÛj stan HP pojazdu by≥ wystarczajπcy by zdaÊ.\n\nSprÛbuj ponownie...\nPowodzenia", "Ok", "");
                    TogglePlayerDynamicRaceCP(playerid, cp7, 0);
				    zdawanie = 0;
					zdaje[playerid] = 0;
					typPrawka[playerid] = 0;
					DestroyVehicle(wozekprawo);
					SpawnPlayer(playerid);
					SendClientMessageToAll(KOLOR_CZERWONY, ""C_CZERWONY"Zdawanie na prawo jazdy: "C_ZIELONY"wolne");
				}
			}
		}
	}
	return 1;
}
public OnPlayerLeaveDynamicRaceCP(playerid, checkpointid)//jak gracz opusci dynamiczny checkpoint wyscigowy
{
	return 1;
}
public OnPlayerEnterDynamicArea(playerid, areaid)//jak gracz wchodzi w dynamiczna strefe
{
	return 1;
}
public OnPlayerLeaveDynamicArea(playerid, areaid)//jak gracz opuszcza
{
	return 1;
}

//publice od zcmd I WSZYSTKIE KOMENDY

public OnPlayerCommandReceived(playerid, cmdtext[])
{
	if(Zalogowany[playerid]==false)
	{
		Info(playerid,""C_CZERWONY"Nie zalogowa≥eú siÍ!");
		return 0;
	}
	if(PlayerInfo[playerid][pJail]>=1)
	{
	    Info(playerid,""C_CZERWONY"Jesteú w wiÍzieniu, nie moøesz uøywaÊ komend!");
		return 0;
	}
	if(zdaje[playerid]>=1)
	{
	    SendClientMessage(playerid, KOLOR_CZERWONY, "Zdajesz na prawo jazdy, nie moøesz uøywaÊ komend!");
	}
	new TCount, KMessage[128];
	TCount = GetPVarInt(playerid, "CommandSpamCount");
	TCount++;
	SetPVarInt(playerid, "CommandSpamCount", TCount);
	if(TCount == 2) {
	    SendClientMessage(playerid, KOLOR_ROZOWY, "AC: "C_BIALY"PrzestaÒ spamiÊ bo dostaniesz kicka!");
	}
	else if(TCount == 3) {
	    GetPlayerName(playerid, KMessage, sizeof(KMessage));
	    format(KMessage,sizeof(KMessage),"AC: "C_BIALY"(%d) %s zosta≥ wyrzucony, za: "C_CZERWONY"SPAM komendami",playerid, KMessage);
		SendClientMessageToAll(KOLOR_ROZOWY, KMessage);
		format(dstring, sizeof(dstring),"~r~(%d)%s zostal wyrzucony~n~~y~przez: (-1)AntyCheat~n~~w~Za: Spam Komendami",playerid,KMessage);
 		NapisText(dstring);
	    print(KMessage);
	    Kick(playerid);
	}

	SetTimerEx("ResetCommandCount", SpamLimit, false, "i", playerid);
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	if(!success)
	{
		format(dstring, sizeof(dstring),"*** "C_BEZOWY"komenda "C_ZIELONY"%s "C_BEZOWY"nie jest poprawna. Spis komend pod "C_ZIELONY"/pomoc"C_BEZOWY".", cmdtext);
		SendClientMessage(playerid, KOLOR_CZERWONY, dstring);
	}
	else
	{
	    printf("[CMD]%s: %s", Nick(playerid), cmdtext);
	    SerwerInfo[sKomendy]++;
	}
	return 1;
}
	COMMAND:cmd(playerid,cmdtext[])
	{
	  return cmd_pomoc(playerid,cmdtext);
	}
	COMMAND:koemndy(playerid,cmdtext[])
	{
	  return cmd_pomoc(playerid,cmdtext);
	}
	CMD:pomoc(playerid, cmdtext[])
	{
	    new s[1600];
	    strcat(s,""C_ZOLTY"Komendy serwera:\n\n");
		strcat(s,""C_ZIELONY"/regulamin"C_BEZOWY" - regulamin serwera\n");
		strcat(s,""C_ZIELONY"/info"C_BEZOWY" - odpowiedz na pytanie 'o co tu chodzi?'\n");
		strcat(s,""C_ZIELONY"/konto"C_BEZOWY" - zarzπdzanie kontem\n");
		strcat(s,""C_ZIELONY"/autorzy"C_BEZOWY" - twÛrcy mapy, obiektÛw\n");
		strcat(s,""C_ZIELONY"/raport"C_BEZOWY" - informacja o cheaterze\n");
		strcat(s,""C_ZIELONY"/admini"C_BEZOWY" - lista adminÛw na serwerze\n");
		strcat(s,""C_ZIELONY"(/p)ojazd"C_BEZOWY" - zarzπdzanie pojazd\n");
        strcat(s,""C_ZIELONY"/cb"C_BEZOWY" - piszesz na CB-Radiu\n");
        strcat(s,""C_ZIELONY"/pm"C_BEZOWY" - wysy≥asz prywatnπ wiadomoúÊ do gracza\n");
        strcat(s,""C_ZIELONY"/respawn"C_BEZOWY" - respawnujesz siÍ\n");
        strcat(s,""C_ZIELONY"/odczep"C_BEZOWY" - odczepiasz naczepÍ\n");
        strcat(s,""C_ZIELONY"/lider"C_BEZOWY" - zatrudniasz kogoú w swojej frakcji\n");
        strcat(s,""C_ZIELONY"/frakcja"C_BEZOWY" - komendy frakcyjne\n");
        strcat(s,""C_ZIELONY"/skin"C_BEZOWY" - zmieniasz skina\n");
        strcat(s,""C_ZIELONY"/flip"C_BEZOWY" - stawiasz pojazd na nogi\n");
        strcat(s,""C_ZIELONY"/rachunek"C_BEZOWY" - sp≥acasz zaleg≥y mandat\n");
        strcat(s,""C_ZIELONY"/dajkase"C_BEZOWY" - dajesz komuú pieniπdze z swojego konta\n");
        strcat(s,""C_ZIELONY"/anim"C_BEZOWY" - lista animacji z serwera\n");
        strcat(s,""C_ZIELONY"/konto"C_BEZOWY" - zarzπdzanie kontem\n");
        strcat(s,""C_ZIELONY"/limity"C_BEZOWY" - ograniczenia na serwerze\n");
        strcat(s,""C_ZIELONY"/taryfikator"C_BEZOWY" - czyli ile za co zap≥acisz\n");
        strcat(s,""C_ZIELONY"/colors"C_BEZOWY" - lista kolorÛw do kolorowego pisania na chacie\n");
        strcat(s,""C_ZIELONY"/zw"C_BEZOWY" - mÛwisz øe zaraz wracasz\n");
        strcat(s,""C_ZIELONY"/jj"C_BEZOWY" - mÛwisz øe juø jesteú\n\n");
        strcat(s,""C_ZOLTY"Komendy zwiπzane z domem:\n\n");
        strcat(s,""C_ZIELONY"/kupdom"C_BEZOWY" - kupujesz dom\n");
        strcat(s,""C_ZIELONY"/sprzedajdom"C_BEZOWY" - sprzedajesz dom\n");
        strcat(s,""C_ZIELONY"/zamek"C_BEZOWY" - zamykasz dom\n");
        strcat(s,""C_ZIELONY"/wolaj"C_BEZOWY" - krzyczysz na caly serwer\n");
        ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend gracza", s, "Ok", "");
		return 1;
	}

	CMD:anim(playerid, cmdtext[])
	{
		Info(playerid,""C_ZOLTY"- /gleba - /raczkuj - /kryj - /rece - /machaj - /odskocz - /tupnij - /fuckyou - /sikaj\n- /poddajsie - /tam - /odejdz - /bacznosc - /salutuj - /taxi - /zmeczony\n- /tancz - /szafka - /mysl - /ranny - /spij - /bar - /jedz - /pij - /lez - /silownia\n- /wymiotuj - /turlaj - /tak - /nie - /siema - /opieraj - /yeah - /kibic - /caluj\n- /podnies - /poloz - /ratuj - /daj - /smiech - /dawaj - /stop - /krzeslo - /lawka\n/astop lub PPM - wy≥πczenie");
		return 1;
	}

	CMD:anims(playerid, cmdtext[])
	{
		Info(playerid,""C_ZOLTY"- /gleba - /raczkuj - /kryj - /rece - /machaj - /odskocz - /tupnij - /fuckyou - /sikaj\n- /poddajsie - /tam - /odejdz - /bacznosc - /salutuj - /taxi - /zmeczony\n- /tancz - /szafka - /mysl - /ranny - /spij - /bar - /jedz - /pij - /lez - /silownia\n- /wymiotuj - /turlaj - /tak - /nie - /siema - /opieraj - /yeah - /kibic - /caluj\n- /podnies - /poloz - /ratuj - /daj - /smiech - /dawaj - /stop - /krzeslo - /lawka\n/astop lub PPM - wy≥πczenie");
		return 1;
	}

	CMD:astop(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,"Nie moøesz uøywaÊ tej komendy bÍdπc w pojeüdzie!");
	        return 1;
	    }
		ClearAnimations(playerid);
		Info(playerid,""C_ZOLTY"Usune≥eú animacjÍ!");
	    return 1;
	}

	CMD:zamek(playerid, cmdtext[])
	{
		if(PlayerInfo[playerid][pDom]==9999)
		{
		    Info(playerid,""C_CZERWONY"Nie masz domu!");
		    return 1;
		}
	    new nr=PlayerInfo[playerid][pDom];
	    if(DoInRange(5.0, playerid,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ])||DoInRange(5.0, playerid,DomInfo[nr][dWyjscieX],DomInfo[nr][dWyjscieY],DomInfo[nr][dWyjscieZ]))
  		{
  		    if(DomInfo[nr][dZamkniety]==1)
  		    {
  		        Info(playerid,""C_ZOLTY"Drzwi otwarte!");
  		        DomInfo[nr][dZamkniety]=0;
				ZapiszDom(nr);
  		    }
  		    else
  		    {
  		        Info(playerid,""C_ZOLTY"Drzwi zamkniete!");
  		        DomInfo[nr][dZamkniety]=1;
  		        ZapiszDom(nr);
  		    }
  		}
  		else
  		{
  		    Info(playerid,""C_CZERWONY"Nie jesteú przy drzwiach swojego domu!");
  		}
		return 1;
	}

	CMD:sprzedajdom(playerid, cmdtext[])
	{
		if(PlayerInfo[playerid][pDom]==9999)
		{
		    Info(playerid,""C_CZERWONY"Nie masz øadnego domu!");
		    return 1;
		}
		new nr=PlayerInfo[playerid][pDom];
		if((DoInRange(5.0, playerid,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]))&&DomInfo[nr][dAktywny]==1)
  		{
		    PlayerInfo[playerid][pDom]=9999;
		    dDodajKase(playerid,(DomInfo[nr][dKoszt]/4)*3);
		    ZapiszKonto(playerid);
		    DomInfo[nr][dKupiony]=0;
		    DomInfo[nr][dZamkniety]=1;
			ZapiszDom(nr);
			DestroyDynamicPickup(DomPickup[nr]);
			DomPickup[nr]=CreateDynamicPickup(1273,1,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ],DomInfo[nr][dWejscieVir],DomInfo[nr][dWejscieInt],-1,45.0);
			format(dstring, sizeof(dstring),""C_ZIELONY"ID domu: "C_ZOLTY"%d\n"C_ZIELONY"W≥aúciciel: "C_ZOLTY"brak\n"C_ZIELONY"Opis: "C_ZOLTY"brak\n"C_ZIELONY"Koszt: "C_ZOLTY"%d", nr, DomInfo[nr][dWlasciciel], DomInfo[nr][dOpis], DomInfo[nr][dKoszt]);
			UpdateDynamic3DTextLabelText(dtexty[nr], KOLOR_ZIELONY, dstring);
			format(dstring, sizeof(dstring),""C_ZOLTY"Sprzeda≥eú dom (%s) za %d$",DomInfo[nr][dOpis],(DomInfo[nr][dKoszt]/4)*3);
			Info(playerid,dstring);
			DestroyDynamicMapIcon(dikonka[nr]);
			dikonka[nr] = CreateDynamicMapIcon(DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 31, 0, -1, -1, -1, 100.0);
    	}
	   	else
	    {
     		Info(playerid,""C_CZERWONY"Nie jesteú przed w≥asnym domem!");
	    }
		return 1;
	}

	CMD:kupdom(playerid, cmdtext[])
	{
		if(PlayerInfo[playerid][pDom]!=9999)
		{
		    Info(playerid,""C_CZERWONY"Masz juø dom!");
		    return 1;
		}
		for(new nr = 0; nr < LIMIT_DOMOW; nr++)
		{
		    if((DoInRange(5.0, playerid,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]))&&DomInfo[nr][dAktywny]==1)
		    {
		        if(DomInfo[nr][dKupiony]==1)
		        {
		            Info(playerid,""C_CZERWONY"Ktoú juø kupi≥ ten dom!");
		    		return 1;
		        }
		        if(!dCzyMaKase(playerid,DomInfo[nr][dKoszt]))
			    {
			        Info(playerid,""C_CZERWONY"Nie staÊ ciebie na zakup tego domu!");
					return 1;
				}
				dDodajKase(playerid,-DomInfo[nr][dKoszt]);
				PlayerInfo[playerid][pDom]=nr;
				ZapiszKonto(playerid);
				new nick[MAX_PLAYER_NAME];
				GetPlayerName(playerid, nick, sizeof(nick));
				strmid(DomInfo[nr][dWlasciciel], nick, 0, strlen(nick), 64);
				DomInfo[nr][dKupiony]=1;
				ZapiszDom(nr);
				DestroyDynamicPickup(DomPickup[nr]);
				DomPickup[nr]=CreateDynamicPickup(1239,1,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ],DomInfo[nr][dWejscieVir],DomInfo[nr][dWejscieInt],-1,45.0);
				format(dstring, sizeof(dstring),""C_ZIELONY"ID domu: "C_ZOLTY"%d\n"C_ZIELONY"W≥aúciciel: "C_ZOLTY"%s\n"C_ZIELONY"Opis: "C_ZOLTY"%s\n"C_ZIELONY"Koszt: "C_ZOLTY"%d", nr, DomInfo[nr][dWlasciciel], DomInfo[nr][dOpis], DomInfo[nr][dKoszt]);
				UpdateDynamic3DTextLabelText(dtexty[nr], KOLOR_ZIELONY, dstring);
				format(dstring, sizeof(dstring),""C_ZOLTY"Kupi≥eú dom (%s) za %d$",DomInfo[nr][dOpis],DomInfo[nr][dKoszt]);
 				Info(playerid,dstring);
 				DestroyDynamicMapIcon(dikonka[nr]);
 				dikonka[nr] = CreateDynamicMapIcon(DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 32, 0, -1, -1, -1, 100.0);
				return 1;
		    }
		}
		Info(playerid,""C_CZERWONY"Nie jesteú przed øadnym domem!");
		return 1;
	}

	CMD:dom(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,3)) return 1;
		new tmp[64],idx,text[80];
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /dom (nr)\n1 - tworzenie nowego domu\n2 - edycja domu\n3 - lista istniejπcych domÛw\n4 - usuÒ dom");
	 		return 1;
	 	}
	 	new numer = strval(tmp);
		if(numer==1)
		{
		    if(DomTworzenie==false&&DomPkt[playerid]==0)
			{
				Info(playerid,"Ten panel aktualnie jest uøywany przez kogoú innego!\nMusisz poczekaÊ!");
				return 1;
			}
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /dom 1 (nr)\n1 - miejsce wejúcia\n2 - miejsce wyjúcia (interior)\n3 - opis\n4 - koszt\n5 - zapisz i dodaj\n99 - anuluj");
		 		return 1;
		 	}
		 	new punkt = strval(tmp);
		 	switch(punkt)
		 	{
		 	    case 1:
		 	    {
		 	        if(DomPkt[playerid]!=0)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
     				for(new nr = 0; nr < LIMIT_DOMOW; nr++)
					{
						if(DomInfo[nr][dAktywny]==0)
				 		{
				 			DomID[playerid]=nr;
							DomTworzenie=false;
							DomPkt[playerid]=1;
							GetPlayerPos(playerid,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
							DomInfo[nr][dWejscieInt]=GetPlayerInterior(playerid);
							DomInfo[nr][dWejscieVir]=GetPlayerVirtualWorld(playerid);
							Info(playerid,"Pozycja wejúcia ustalona!");
							return 1;
						}
					}
					return 1;
		 	    }//koniec przypadku
		 	    case 2:
		 	    {
		 	        if(DomPkt[playerid]!=1)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			new nr=DomID[playerid];
		            GetPlayerPos(playerid,DomInfo[nr][dWyjscieX],DomInfo[nr][dWyjscieY],DomInfo[nr][dWyjscieZ]);
					DomInfo[nr][dWyjscieInt]=GetPlayerInterior(playerid);
					DomPkt[playerid]=2;
					Info(playerid,"Pozycja wyjúcia (interior) ustalona!");
				 	return 1;
				}//koniec przypadku
				case 3:
		 	    {
		 	        if(DomPkt[playerid]!=2)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /dom 1 3 (opis domu)");
				 		return 1;
				 	}
				 	if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
				 	new nr=DomID[playerid];
				 	DomPkt[playerid]=3;
				 	strmid(DomInfo[nr][dOpis], text, 0, strlen(text), 64);
				 	Info(playerid,"Opis domu ustalony!");
				 	return 1;
				}//koniec przypadku
				case 4:
		 	    {
		 	        if(DomPkt[playerid]!=3)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			tmp = strtok(cmdtext, idx);
					if(isnull(tmp))
					{
						Info(playerid,"Uøyj: /dom 1 4 (cena)");
				 		return 1;
				 	}
				 	new kwota=strval(tmp);
				 	if(kwota<5000||kwota>1000000)
				 	{
				 	    Info(playerid,"Od 5000$ do 1000000$");
				 	    return 1;
				 	}
				 	new nr=DomID[playerid];
				 	DomPkt[playerid]=4;
                    DomInfo[nr][dKoszt]=kwota;
                    Info(playerid,"Koszt domu ustalony!");
				 	return 1;
				}//koniec przypadku
				case 5:
		 	    {
		 	        if(DomPkt[playerid]!=4)
			 		{
				 		Info(playerid,"Nie wykona≥eú jeszcze wszystkich punktÛw!");
				 		return 1;
		 			}
		 			new nr=DomID[playerid];
		 			DomInfo[nr][dAktywny]=1;
		 			DomInfo[nr][dKupiony]=0;
		 			DomInfo[nr][dZamkniety]=1;
		 			ZapiszDom(nr);
		 			DomPickup[nr]=CreateDynamicPickup(1273,2,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ],DomInfo[nr][dWejscieVir],DomInfo[nr][dWejscieInt],-1,45.0);
		 			DomID[playerid]=9999;
					DomPkt[playerid]=0;
					DomTworzenie=true;
		 			format(dstring, sizeof(dstring),"Poprawnie doda≥eú dom o ID: %d",nr);
		 			Info(playerid,dstring);
		 			SetPlayerPos(playerid,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
		 			SetPlayerInterior(playerid,DomInfo[nr][dWejscieInt]);
		 			SetPlayerVirtualWorld(playerid,DomInfo[nr][dWejscieVir]);
		 	        return 1;
		 	    }//koniec przypadku
		 	    case 99:
		 	    {
		 	        if(DomPkt[playerid]==0)
			 		{
				 		Info(playerid,"Nie moøesz anulowaÊ pracy, poniewaø jej nie zacze≥eú!");
				 		return 1;
		 			}
		 			DomID[playerid]=9999;
					DomPkt[playerid]=0;
					DomTworzenie=true;
					Info(playerid,"Praca anulowana!");
		 	        return 1;
		 	    }//koniec przypadku
			}
			return 1;
		}
		else if(numer==2)
		{
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /dom 2 (id domu) (nr)\n1 - miejsce wejúcia\n2 - miejsce wyjúcia (interior)\n3 - opis\n4 - koszt");
		 		return 1;
		 	}
		 	new nr = strval(tmp);
		 	tmp = strtok(cmdtext, idx);
		 	new punkt = strval(tmp);
		 	if(DomInfo[nr][dAktywny]==0)
 			{
 			    Info(playerid,"Nie poprawne id domu!");
 			    return 1;
 			}
		 	switch(punkt)
		 	{
		 	    case 1:
				{
					GetPlayerPos(playerid,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
					DomInfo[nr][dWejscieInt]=GetPlayerInterior(playerid);
					DomInfo[nr][dWejscieVir]=GetPlayerVirtualWorld(playerid);
					DestroyDynamicPickup(DomPickup[nr]);
					DomPickup[nr]=CreateDynamicPickup(1273,2,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ],DomInfo[nr][dWejscieVir],DomInfo[nr][dWejscieInt],-1,45.0);
					Info(playerid,"Pozycja wejúcia zmieniona!");
					ZapiszDom(nr);
					return 1;
		 	    }//koniec przypadku
		 	    case 2:
		 	    {
		            GetPlayerPos(playerid,DomInfo[nr][dWyjscieX],DomInfo[nr][dWyjscieY],DomInfo[nr][dWyjscieZ]);
					DomInfo[nr][dWyjscieInt]=GetPlayerInterior(playerid);
					Info(playerid,"Pozycja wyjúcia (interior) zmieniona!");
					ZapiszDom(nr);
				 	return 1;
				}//koniec przypadku
				case 3:
		 	    {
		 			text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /dom 2 (id) 3 (opis domu)");
				 		return 1;
				 	}
				 	if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
				 	strmid(DomInfo[nr][dOpis], text, 0, strlen(text), 64);
				 	Info(playerid,"Opis domu ustalony!");
				 	ZapiszDom(nr);
				 	return 1;
				}//koniec przypadku
				case 4:
		 	    {
		 			tmp = strtok(cmdtext, idx);
					if(isnull(tmp))
					{
						Info(playerid,"Uøyj: /dom 2 (id) 4 (cena)");
				 		return 1;
				 	}
				 	new kwota=strval(tmp);
				 	if(kwota<5000||kwota>1000000)
				 	{
				 	    Info(playerid,"Od 5000$ do 1000000$");
				 	    return 1;
				 	}
                    DomInfo[nr][dKoszt]=kwota;
                    Info(playerid,"Koszt domu zmieniony!");
                    ZapiszDom(nr);
				 	return 1;
				}//koniec przypadku
			}
			return 1;
		}
		else if(numer==3)
		{
		    SendClientMessage(playerid,KOLOR_ZOLTY,"Istniejπce domy:");
		    for(new nr = 0; nr < LIMIT_DOMOW; nr++)
			{
				if(DomInfo[nr][dAktywny]==1)
	 			{
		    		format(dstring, sizeof(dstring),"Dom [%d], opis: %s",nr,DomInfo[nr][dOpis]);
		    		SendClientMessage(playerid,KOLOR_BIALY,dstring);
				}
			}
			return 1;
		}
		else if(numer==4)
		{
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /dom 4 (id)");
	 			return 1;
		 	}
		 	new nr=strval(tmp);
		 	if(DomInfo[nr][dAktywny]==0)
 			{
 			    Info(playerid,"Taki dom nie istnieje!");
 			    return 1;
 			}
 			DestroyDynamicPickup(DomPickup[nr]);
 			DomInfo[nr][dAktywny]=0;
 			ZapiszDom(nr);
 			Info(playerid,"Dom zosta≥ usuniÍty!");
			return 1;
		}
		return 1;
	}

	CMD:rsp(playerid, cmdtext[])
	{
		if(ToAdminLevel(playerid,1))
		{
			new bool:Uzywany[LIMIT_SAMOCHODOW]=false,v;
	        foreach(Player,i)
			{
			    if(IsPlayerInAnyVehicle(i))
			    {
					v=GetPlayerVehicleID(i);
			        Uzywany[v]=true;
			        if(IsTrailerAttachedToVehicle(v)) Uzywany[GetVehicleTrailer(v)]=true;
			    }
			}
			for(new nr = 1; nr < LIMIT_SAMOCHODOW; nr++)
			{
				if(Uzywany[nr]==false)
				{
					SetVehicleToRespawn(nr);
					SetVehicleParamsEx(nr,false,false,false,false,false,false,false);
					vPojazdZycie[nr]=1000.0;
				}
			}
	        format(dstring, sizeof(dstring),"~r~(%d)%s ~w~zrespawnowal wszystkie nieuzywane pojazdy!",playerid,Nick(playerid));
	  		NapisText(dstring);
		}
		return 1;
	}

	CMD:rspall(playerid, cmdtext[])
	{
		if(ToAdminLevel(playerid,2))
		{
			for(new nr = 1; nr < LIMIT_SAMOCHODOW; nr++)
			{
				SetVehicleToRespawn(nr);
				SetVehicleParamsEx(nr,false,false,false,false,false,false,false);
				vPojazdZycie[nr]=1000.0;
			}
	        format(dstring, sizeof(dstring),"~r~(%d)%s ~w~zrespawnowal wszystkie pojazdy!",playerid,Nick(playerid));
	  		NapisText(dstring);
		}
		return 1;
	}

	CMD:tankujall(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,2)) return 1;
		for(new nr = 1; nr < LIMIT_SAMOCHODOW; nr++)
		{
			vPaliwo[nr]=vPaliwoMax[nr];
		}
        format(dstring, sizeof(dstring),"~r~(%d)%s ~w~zatankowal wszystkie pojazdy!",playerid,Nick(playerid));
  		NapisText(dstring);
		return 1;
	}
	
	CMD:tankujcar(playerid, params[])
	{
	    if(ToPOMOC(playerid) || ToAdminLevel(playerid, 3))
	    {
	    	if(IsPlayerInAnyVehicle(playerid))
	    	{
	    	    new carid = GetPlayerVehicleID(playerid);
	    		vPaliwo[carid]=vPaliwoMax[carid];
	    		SendClientMessage(playerid, KOLOR_ZIELONY, "Zatankowa≥eú pojazd...");
			}
			else
			{
			    SendClientMessage(playerid, KOLOR_CZERWONY, "Musisz siedzieÊ w pojeüdzie!");
			}
		}
		else
		{
            SendClientMessage(playerid, KOLOR_CZERWONY, "Nie pracujesz w PD!");
		}
		return 1;
	}
	
	COMMAND:cmds(playerid,params[])
	{
	  return cmd_frakcja(playerid,params);
	}

	CMD:frakcja(playerid, params[])
	{
		new s[1000];
		if(ToPD(playerid))
		{
		    strcat(s,""C_ZIELONY"(/kol)czatka"C_BEZOWY" - stawiasz kolczatke\n");
		    strcat(s,""C_ZIELONY"/zbierz"C_BEZOWY" - zabierasz kolczatki\n");
		    strcat(s,""C_ZIELONY"(/m)andat"C_BEZOWY" - wystawiasz mandat\n");
		    strcat(s,""C_ZIELONY"/areszt"C_BEZOWY" - aresztujesz gracza\n");
		    strcat(s,""C_ZIELONY"(/s)uszarka"C_BEZOWY" - mierzysz prÍdkoúÊ graczy w pewnym promieniu\n");
		    strcat(s,""C_ZIELONY"(/r)adio"C_BEZOWY" - radio policyjne\n");
		    strcat(s,""C_ZIELONY"/taryfikator"C_BEZOWY" - sprawdzasz kary na serwerze\n");
		    strcat(s,""C_ZIELONY"/bronie"C_BEZOWY" - zestaw broni\n");
		    strcat(s,""C_ZIELONY"/stoj"C_BEZOWY" - komunikat by dany gracz sie zatrzymal\n");
		    strcat(s,""C_ZIELONY"/unareszt"C_BEZOWY" - wypuszczasz gracza z wiÍzienia\n");
		    strcat(s,""C_ZIELONY"/konfiskuj"C_BEZOWY" - konfiskujesz towar");
		    ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend Policjanta", s, "Ok", "");
		}
		else if(ToPOMOC(playerid))
		{
		    strcat(s,""C_ZIELONY"/blokada"C_BEZOWY" - stawiasz blokadÍ na drodze\n");
		    strcat(s,""C_ZIELONY"/napraw"C_BEZOWY" - naprawiasz pojazd\n");
		    strcat(s,""C_ZIELONY"/pobierz"C_BEZOWY" - bierzesz naleønoúÊ\n");
		    strcat(s,""C_ZIELONY"/kogut"C_BEZOWY" - stawiasz kogut\n");
		    ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend pracownika pomocy drogowej", s, "Ok", "");
		}
		else if(ToLOT(playerid))
		{
		    strcat(s,""C_ZIELONY"/zlecenie"C_BEZOWY" - bierzesz zlecenie\n");
		    ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend pracownika Firmy Lotniczej", s, "Ok", "");
		}
		else if(ToST(playerid) || ToET(playerid))
		{
		    strcat(s,""C_ZIELONY"/zlecenie"C_BEZOWY" - bierzesz zlecenie\n");
		    ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend pracownika Firmy", s, "Ok", "");
		}
		return 1;
	}

	COMMAND:radio(playerid,cmdtext[])
	{
	  return cmd_r(playerid,cmdtext);
	}

	CMD:taryfikator(playerid, cmdtext[])
	{
        new s[3000];
		strcat(s,"ß1.PrÍdkoúÊ.\n");
		strcat(s,"Przekroczenie dopuszczalnej prÍdkoúci o 10km/h ñ 100$ + 2 punkty karne\n");
		strcat(s,"*za kaøde kolejne 10km/h- 100$\n");
		strcat(s,"(do kaødego przekroczenia prÍdkoúci sπ przyznawane 2 punkty karne niewaøne o ile by≥a\n");
		strcat(s,"przekroczona prÍdkoúÊ)\n");
		strcat(s,"\n");
		strcat(s,"(np.: dopuszczalna prÍdkoúÊ- 100km/h ñ ktoú jedzie 150km/h przekroczy≥ o 50km/h wiÍc 250 $ itd.)\n");
		strcat(s,"\n");
		strcat(s,"ß2.Wykroczenia.\n");
		strcat(s,"1.Niestosowanie siÍ do sygnalizacji úwietlnej: 100-250$.+ 2 punkty karne\n");
		strcat(s,"2.Jazda pod prπd: 100-300$ + 3 punkty karne\n");
		strcat(s,"3.Jazda na skrÛty: 100-300$ + 3 punkty karne\n");
		strcat(s,"4.Zawracanie na autostradzie lub na jakiejkolwiek drodze z zakazem zawracania: 100-400$ + 3 punkty karne\n");
		strcat(s,"5.Zniszczenie mienia: 300-600$ + 4 punkty karne\n");
		strcat(s,"6.Ucieczka przed kontrolπ: 500-700$ + 2 minuty aresztu.+ 5 punkty karne\n");
		strcat(s,"7.Utrudnianie pracy Policji lub innym s≥uøbπ: 500$ + 3 minuty aresztu.+ 5 punkty karne\n");
		strcat(s,"8.Stwarzanie zagroøenia: 500$-1500$ + 2 minuty aresztu.+ 3 punkty karne\n");
		strcat(s,"9.Jazda bez oúwietlenia/uszkodzone auto: 200-400$ + przymusowa naprawa.+ 2 punkty karne\n");
		strcat(s,"10.Jazda z prÍdkoúciπ utrudniajπcπ ruch: 200-300$ + 3 punkty karne\n");
		strcat(s,"11.Ucieczka z miejsca wypadku: podliczenie wszystkich wykroczeÒ x2 . + 5 punktÛw karnych\n");
		strcat(s,"12.Spowodowanie wypadku: 500$ + 2 punkty karne/ze skutkiem úmiertelnym: +2 minuty + 5 punkty karne\n");
		strcat(s,"13.Jazda po autostradzie pojazdem niedostosowanym: 300-500$ + konfiskacja pojazdu.+ 4 punkty karne\n");
		strcat(s,"14.Wymuszanie pierwszeÒstwa:200$+ 3 punkty karne\n");
		strcat(s,"15.Uøywanie podtlenku azotu (NOS/NITRO): 1000$ + konf. Poj. + 5 punktÛw karnych\n");
		strcat(s,"16.BÛjka/udzia≥ w niej: 400$ + 3 punkty karne\n");
		strcat(s,"17.W≥amanie: 1000$ + 4 punkty karne\n");
		strcat(s,"18.PrÛba kradzieøy: 3 minuty aresztu ( moøna na odleg≥oúÊ)+ 4 punkty karne\n");
		strcat(s,"19.£apÛwka: 1000$ + 5 punktÛw karnych\n");
		strcat(s,"20.Nielegalne posiadanie broni: 1500$ +2 minuty aresztu. + 5 punktÛw karnych\n");
		strcat(s,"21.WspÛ≥udzia≥: po≥owa kary sprawcy. + 2 punkty karne\n");
		strcat(s,"22. Nie op≥acanie urzπdzenia viatoll grozi mandatem w wysokoúci 600$ i 1 punkt karny\n");
		strcat(s,"23.Podmiot ktÛry nie posiada prawa jazdy zostaje ukarany mandatem karnym w wysokoúci 1500$ + 3 minuty wiÍzienia.\n");
		ShowPlayerDialog(playerid,TARYFIK,DIALOG_STYLE_MSGBOX,"Taryfikator", s, "Dalej", "Ok");
        return 1;
 	}

	CMD:r(playerid, cmdtext[])
	{
	    if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        if(PlayerInfo[playerid][pWyciszony]>=1)
		{
		    Info(playerid,""C_CZERWONY"Jesteú wyciszony!");
			return 1;
		}
	    new text[80],idx;
		text=strrest(cmdtext,idx);
		if(isnull(text))
		{
			Info(playerid,"Uøyj: (/r)adio (tekst)");
			return 1;
		}
		UpperToLower(text);
		foreach(Player,i)
		{
  			if(ToPD(i))
	    	{
    			format(dstring,sizeof(dstring),"(PD-Radio)[%d]%s: "C_BIALY"%s",playerid,Nick(playerid),text);
	 			SendClientMessage(i,KOLOR_ZOLTY,dstring);
			}
		}
		return 1;
	}

	CMD:dajkase(playerid, cmdtext[])
	{
	    if(blokadacmd==1)
	        return Info(playerid, "Komenda zablokowana przez Inferno\nPowÛd: Zakaz przekazywania kasy przed zmianπ mapki");
        new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /dajkase (id) (kwota)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new kwota = strval(tmp);
	 	if(kwota<1||kwota>dKasa[playerid])
	 	{
	 	    Info(playerid,""C_CZERWONY"Nie poprawna kwota!");
	 	    return 1;
	 	}
		if(IsPlayerConnected(playa)&&playa!=playerid)
	 	{
	 	    dDodajKase(playa,kwota);
	 	    dDodajKase(playerid,-kwota);
	 	    format(dstring,sizeof(dstring),""C_ZOLTY"Gracz [%d]%s da≥ tobie %d$",playerid,Nick(playerid),kwota);
			Info(playa,dstring);
			format(dstring,sizeof(dstring),""C_ZOLTY"Da≥eú %d$ graczowi [%d]%s",kwota,playa,Nick(playa));
			Info(playerid,dstring);
	 	    return 1;
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Nie poprawne id!");
		}
		return 1;
	}
/*
	CMD:pobierz(playerid, cmdtext[])
	{
	    if(!ToPOMOC(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie pracujesz w Pomocy Drogowej!");
            return 1;
        }
        new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /pobierz (id) (kwota)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new kwota = strval(tmp);
		if(IsPlayerConnected(playa)&&playa!=playerid)
	 	{
	 	    dDodajKase(playerid,kwota);
	 	    dDodajKase(playa,-kwota);
	 	    format(dstring,sizeof(dstring),""C_CZERWONY"Op≥ata za us≥ugi pomocy drogowej:\n\n"C_POMARANCZOWY"Nick mechanika:"C_BIALY"[%d]%s\n"C_POMARANCZOWY"Pobrana naleznosc:"C_BIALY" %d$",playerid,Nick(playerid),kwota);
			Info(playa,dstring);
			format(dstring,sizeof(dstring),""C_CZERWONY"Op≥ata za us≥ugi pomocy drogowej:\n\n"C_POMARANCZOWY"Pobrana naleznosc:"C_BIALY"%d$\n"C_POMARANCZOWY"Graczowi: "C_BIALY"[%d]%s",kwota,playa,Nick(playa));
			Info(playerid,dstring);
	 	    return 1;
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Nie poprawne id!");
		}
		return 1;
	}

	CMD:sprawdz(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /sprawdz (id)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(IsPlayerConnected(playa)&&playa!=playerid)
	 	{
	 	    if(!OdlegloscGracze(20.0,playerid,playa))
		 	{
		 	    GInfo(playerid,"~r~gracz jest za daleko od ciebie",3);
		 	    return 1;
		 	}
		 	if(GetPlayerState(playa)!=PLAYER_STATE_DRIVER)
		 	{
                GInfo(playerid,"~r~gracz nie jest kierowca zadnego pojazdu",3);
		 	    return 1;
		 	}
			if(Misja[playa]==false||MisjaStopien[playa]==0)
			{
			    format(dstring,sizeof(dstring),"Pojazd %s,kierowca: [%d]%s, towar (brak).",GetVehicleName(GetPlayerVehicleID(playa)),playa,Nick(playa));
 				SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
 				format(dstring,sizeof(dstring),"Policjant [%d]%s skontrolowa≥ ciebie, ale nie wieziesz towaru!",playerid,Nick(playerid));
 				SendClientMessage(playa,KOLOR_NIEBIESKI,dstring);
		 	    return 1;
			}

			format(dstring,sizeof(dstring),"Policjant [%d]%s kontroluje ≥adunek,ktÛry wieziesz!",playerid,Nick(playerid));
			SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);

			if(Przeladowany[playa]==true)
			{
				format(dstring,sizeof(dstring),"Pojazd %s,kierowca: [%d]%s, towar(%s): "C_CZERWONY"prze≥adowany!",GetVehicleName(GetPlayerVehicleID(playa)),playa,Nick(playa),LadunekInfo[MisjaID[playa]][lTowar]);
 				SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
 				format(dstring,sizeof(dstring),"Policjant [%d]%s skontrolowa≥ twÛj pojazd i wykry≥, øe jesteú: "C_CZERWONY"prze≥adowany!",playerid,Nick(playerid));
 				SendClientMessage(playa,KOLOR_NIEBIESKI,dstring);
			}
			else
			{
			    format(dstring,sizeof(dstring),"Pojazd %s,kierowca: [%d]%s, towar(%s): "C_ZIELONY"nie prze≥adowany!",GetVehicleName(GetPlayerVehicleID(playa)),playa,Nick(playa),LadunekInfo[MisjaID[playa]][lTowar]);
 				SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
 				format(dstring,sizeof(dstring),"Policjant [%d]%s skontrolowa≥ twÛj pojazd i wykry≥, øe jesteú: "C_ZIELONY"nie prze≥adowany!",playerid,Nick(playerid));
 				SendClientMessage(playa,KOLOR_NIEBIESKI,dstring);
			}
			return 1;
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Nie poprawne id!");
		}
		return 1;
	}
*/
	COMMAND:s(playerid,cmdtext[])
	{
	  return cmd_suszarka(playerid,cmdtext);
	}

	CMD:suszarka(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        if(GetPlayerInterior(playerid)!=0)
        {
        	Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ tej komendy w interiorze!");
            return 1;
        }
        new Float:Pos[3];
        GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
        SendClientMessage(playerid,KOLOR_BIALY,"Pojazdy namierzone suszarkπ:");
        foreach(Player,i)
		{
		    if(GetPlayerState(i)==PLAYER_STATE_DRIVER&&GetPlayerSpeed(i)>5&&DoInRange(90.0, i,Pos[0],Pos[1],Pos[2])&&i!=playerid)
		    {
		        new w=GetPlayerSpeed(i);
		        format(dstring,sizeof(dstring),"Policjant [%d]%s namierzy≥ twÛj pojazd 'suszarkπ',wskaza≥o: "C_ZOLTY"%d km/h",playerid,Nick(playerid),w);
		 		SendClientMessage(i,KOLOR_NIEBIESKI,dstring);
		 		format(dstring,sizeof(dstring),"Pojazd %s,kierowca: [%d]%s, prÍdkoúÊ: "C_ZOLTY"%d km/h",GetVehicleName(GetPlayerVehicleID(i)),i,Nick(i),w);
		 		SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
		    }
		}
		return 1;
	}

    CMD:bronie(playerid, cmdtext[])
	{
		if(PlayerInfo[playerid][pFrakcja]==0)
		{
		    Info(playerid,""C_CZERWONY"Nie pracujesz w Policji!");
		    return 1;
		}
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze!\nKomenda /skin s≥uøy do zmiany skinu.");
            return 1;
        }
        GivePlayerWeapon(playerid,31,200);
        GivePlayerWeapon(playerid,29,200);
        GivePlayerWeapon(playerid,3,200);
        GivePlayerWeapon(playerid,22,200);
        GivePlayerWeapon(playerid,25,200);
		Info(playerid,""C_ZIELONY"Dostales bronie");
        return 1;
	}

	CMD:areszt2(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /areszt (id)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(IsPlayerConnected(playa)&&playa!=playerid)
	 	{
	 	    if(!OdlegloscGracze(15.0,playerid,playa))
		 	{
		 	    GInfo(playerid,"~r~gracz jest za daleko od ciebie",3);
		 	    return 1;
		 	}
			/*if(Misja[playa]==true)
			{
			    Info(playa,""C_ZOLTY"Misja przerwana, otrzyma≥eú grzywnÍ w wysokoúci: "C_CZERWONY"1000$");
				dDodajKase(playa,-1000);
				AnulujMisje(playa);
			}*/
		 	new kara=PlayerInfo[playa][pScigany]*2;
		 	SetPlayerPos(playa,264.9535,77.5068,1001.0391);
		    SetPlayerInterior(playa,6);
		    SetPlayerVirtualWorld(playa,playa);
		    SetPlayerWorldBounds(playa,268.5071,261.3936,81.6285,71.8745);
		    dUstawHP(playa,100);
            format(dstring,sizeof(dstring),"Policjant [%d]%s aresztowa≥ ciebie na %d minut/y.",playerid,Nick(playerid),kara);
		 	SendClientMessage(playa,KOLOR_NIEBIESKI,dstring);
		 	format(dstring,sizeof(dstring),"Aresztowa≥eú [%d]%s na %d minut/y. Zarobi≥eú: %d$",playa,Nick(playa),kara,PlayerInfo[playa][pMandat]);
		 	SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
		 	format(dstring,sizeof(dstring),"Policjant [%d]%s "C_ZOLTY"aresztowa≥ "C_NIEBIESKI"[%d]%s na "C_ZOLTY"%d minut/y.",playerid,Nick(playerid),playa,Nick(playa),kara);
		 	SendClientMessageToAll(KOLOR_BIALY,dstring);
		 	PlayerInfo[playa][pJail]=kara;
			PlayerInfo[playa][pScigany]=0;
			SetPlayerWantedLevel(playa,0);
			dDodajKase(playa,-PlayerInfo[playa][pMandat]);
			dDodajKase(playerid,PlayerInfo[playa][pMandat]);
			PlayerInfo[playa][pMandat]=0;
			PlayerInfo[playa][pScigany]=0;
		 	SetPlayerWantedLevel(playa,0);
		 	ZapiszKonto(playa);
	 	    return 1;
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Nie poprawne id!");
		}
		return 1;
	}
	
	CMD:unareszt(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            SendClientMessage(playerid, KOLOR_CZERWONY, "Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        new id;
		if(sscanf(cmdtext,"d",id))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /areszt <id> <czas w minutach>");
	 	if(IsPlayerConnected(id) && id != playerid)
	 	{
	 	    if(PlayerInfo[id][pJail] > 0)
	 	    {
				PlayerInfo[id][pJail]=0;
				SetPlayerWorldBounds(id, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
				CallLocalFunction("OnPlayerSpawn", "i",id);
				format(dstring,sizeof(dstring),"Policjant [%d]%s wypuúci≥ ciebie z wiÍzienia.",playerid,Nick(playerid));
			 	SendClientMessage(id,KOLOR_NIEBIESKI,dstring);
			 	format(dstring,sizeof(dstring),"Wypuúci≥eú [%d]%s z wiÍzienia.",id,Nick(id));
			 	SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
			 	format(dstring,sizeof(dstring),"Policjant [%d]%s "C_ZOLTY"wypuúci≥ "C_NIEBIESKI"[%d]%s "C_ZOLTY".",playerid,Nick(playerid),id,Nick(id));
			 	SendClientMessageToAll(KOLOR_BIALY,dstring);
			}
			else
			{
				SendClientMessage(playerid, KOLOR_CZERWONY, "Ten gracz nie jest w wiÍzieniu!");
			}
		}
		else
		{
			SendClientMessage(playerid, KOLOR_CZERWONY, "Nie moøesz wypuúciÊ sam siebie!");
		}
		return 1;
	}

	CMD:areszt(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            SendClientMessage(playerid, KOLOR_CZERWONY, "Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        new id,karagracz;
		if(sscanf(cmdtext,"dd",id,karagracz))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /areszt <id> <czas w minutach>");
	 	if(IsPlayerConnected(id) && id != playerid)
	 	{
	 	    if(karagracz > 0)
	 	    {
		 	    if(!OdlegloscGracze(15.0,playerid,id))
			 	{
			 	    GInfo(playerid,"~r~gracz jest za daleko od ciebie",3);
			 	    return 1;
			 	}

			 	SetPlayerPos(id,264.9535,77.5068,1001.0391);
			    SetPlayerInterior(id,6);
			    SetPlayerVirtualWorld(id,id);
			    SetPlayerWorldBounds(id,268.5071,261.3936,81.6285,71.8745);
			    dUstawHP(id,100);
	            format(dstring,sizeof(dstring),"Policjant [%d]%s aresztowa≥ ciebie na %d minut/y.",playerid,Nick(playerid),karagracz);
			 	SendClientMessage(id,KOLOR_NIEBIESKI,dstring);
			 	format(dstring,sizeof(dstring),"Aresztowa≥eú [%d]%s na %d minut/y.",id,Nick(id),karagracz);
			 	SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
			 	format(dstring,sizeof(dstring),"Policjant [%d]%s "C_ZOLTY"aresztowa≥ "C_NIEBIESKI"[%d]%s na "C_ZOLTY"%d minut/y.",playerid,Nick(playerid),id,Nick(id),karagracz);
			 	SendClientMessageToAll(KOLOR_BIALY,dstring);
			 	PlayerInfo[id][pJail]=karagracz;
			 	ZapiszKonto(id);
		 	    return 1;
			}
			else
			{
			    SendClientMessage(playerid, KOLOR_CZERWONY, "Czas musi byÊ wiÍkszy niø 1 minuta");
			}
		}
		else
		{
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Nie poprawne id!");
		}
		return 1;
	}
/*
	CMD:scigani(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        SendClientMessage(playerid,KOLOR_BIALY," ");
        SendClientMessage(playerid,KOLOR_BIALY,"* Poszukiwane osoby:");
		foreach(Player,i)
		{
		    if(PlayerInfo[i][pScigany]>=1)
		    {
		        format(dstring,sizeof(dstring),"[%d] %s - poziom: "C_ZOLTY"%d/6",playerid,Nick(playerid),PlayerInfo[i][pScigany]);
		 		SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
		    }
		}
		return 1;
	}

	CMD:scigany(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /scigany (id) (wartoúÊ 0-6)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new kara = strval(tmp);
	 	if(kara<0||kara>6)
		{
		    Info(playerid,""C_CZERWONY"Poziom poszukiwaÒ od 0 do 6!");
		    return 1;
		}
	 	if(IsPlayerConnected(playa)&&playa!=playerid)
	 	{
		 	if(PlayerInfo[playa][pScigany]==0)
	 	    {
	 	        Info(playerid,""C_CZERWONY"Ten gracz nie jest poszukiwany!");
	 	        return 1;
	 	    }
		 	PlayerInfo[playa][pScigany]=kara;
		 	SetPlayerWantedLevel(playa,PlayerInfo[playa][pScigany]);
		 	ZapiszKonto(playa);
		 	format(dstring,sizeof(dstring),"Policjant [%d]%s ustawi≥ tobie poziom poszukiwaÒ na: "C_ZOLTY"%d/6",playerid,Nick(playerid),kara);
		 	SendClientMessage(playa,KOLOR_NIEBIESKI,dstring);
		 	format(dstring,sizeof(dstring),"Ustawi≥eú [%d]%s poziom poszukiwaÒ na "C_ZOLTY"%d/6",playa,Nick(playa),kara);
		 	SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
	 	}
	 	else
	 	{
	 	    Info(playerid,""C_CZERWONY"Nie poprawne id!");
	 	}
		return 1;
	}

	CMD:rachunek(playerid, cmdtext[])
	{
	    if(PlayerInfo[playerid][pMandat]<1)
	    {
	        Info(playerid,""C_CZERWONY"Nie masz øadnych zaleg≥ych mandatÛw!");
            return 1;
	    }
	    if(PlayerInfo[playerid][pScigany]>=1)
	    {
	        Info(playerid,""C_CZERWONY"Teraz juø za pÛüno na sp≥atÍ d≥ugÛw\nPoddaj siÍ policji!");
            return 1;
	    }
	    if(!dCzyMaKase(playerid,PlayerInfo[playerid][pMandat]))
	    {
	        Info(playerid,""C_CZERWONY"Nie staÊ ciebie na zap≥acenie mandatu!");
			return 1;
		}
	    new pd=MandatPD[playerid];
	    if(IsPlayerConnected(pd)&&ToPD(pd))
	    {
	 		format(dstring,sizeof(dstring),"Zap≥aci≥eú mandat [%d]%s w wysokoúci: "C_ZOLTY"%d$",pd,Nick(pd),PlayerInfo[playerid][pMandat]);
            Info(playerid,dstring);
            format(dstring,sizeof(dstring),"[%d]%s zap≥aci≥ tobie mandat: "C_ZOLTY"(%d$)",playerid,Nick(playerid),PlayerInfo[playerid][pMandat]);
            Info(pd,dstring);
            dDodajKase(playerid,-PlayerInfo[playerid][pMandat]);
            dDodajKase(pd,PlayerInfo[playerid][pMandat]);
            PlayerInfo[playerid][pMandat]=0;
            ZapiszKonto(playerid);
            MandatPD[playerid]=999;
		}
		else
		{
            format(dstring,sizeof(dstring),"Zap≥aci≥eú mandat w wysokoúci: "C_ZOLTY"%d$",PlayerInfo[playerid][pMandat]);
            Info(playerid,dstring);
            dDodajKase(playerid,-PlayerInfo[playerid][pMandat]);
            PlayerInfo[playerid][pMandat]=0;
            ZapiszKonto(playerid);
            MandatPD[playerid]=999;
		}
	    return 1;
	}
 */
	COMMAND:m(playerid,cmdtext[])
	{
	  return cmd_mandat(playerid,cmdtext);
	}

	CMD:mandat(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: (/m)andat (id) (wartoúÊ)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new kara = strval(tmp);
	 	if(kara<100||kara>50000)
		{
		    Info(playerid,""C_CZERWONY"Mandat od 100$ do 50000$!");
		    return 1;
		}
	 	if(IsPlayerConnected(playa)&&playa!=playerid)
	 	{
	 	    if(!OdlegloscGracze(20.0,playerid,playa))
		 	{
		 	    GInfo(playerid,"~r~gracz jest za daleko od ciebie",3);
		 	    return 1;
		 	}
		 	format(dstring,sizeof(dstring),"Policjant [%d]%s wystawi≥ tobie mandat (%d$)!",playerid,Nick(playerid),kara);
		 	SendClientMessage(playa,KOLOR_NIEBIESKI,dstring);
		 	format(dstring,sizeof(dstring),"Wystawi≥eú [%d]%s mandat na kwotÍ %d$.",playa,Nick(playa),kara);
		 	SendClientMessage(playerid,KOLOR_NIEBIESKI,dstring);
		 	dDodajKase(playa, -kara);
		 	ZapiszKonto(playa);
	 	}
	 	else
	 	{
	 	    Info(playerid,""C_CZERWONY"Nie poprawne id!");
	 	}
		return 1;
	}

	stock OdlegloscGracze(Float:odleglosc, playerid, gracz)
	{
		if(IsPlayerConnected(playerid)&&IsPlayerConnected(gracz))
		{
			new Float:Pos[3];
			GetPlayerPos(gracz,Pos[0],Pos[1],Pos[2]);
			if(IsPlayerInRangeOfPoint(playerid, odleglosc, Pos[0],Pos[1],Pos[2]))
			{
			    return 1;
			}
		}
		return 0;
	}

	CMD:skin(playerid, cmdtext[])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
		    Info(playerid,""C_CZERWONY"Nie moøesz byÊ w pojeüdzie!");
		    return 1;
		}
		if(!dCzyMaKase(playerid,1))
	    {
	        Info(playerid,""C_CZERWONY"Nie masz pieniÍdzy!");
			return 1;
		}
        ForceClassSelection(playerid);
    	dUstawHP(playerid,0);
	    return 1;
	}

	CMD:zbierz(playerid, cmdtext[])
	{
 		if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        if(Kolczatki==0)
		{
  			Info(playerid,""C_CZERWONY"Øadna kolczatka nie jest postawiona!");
	    	return 1;
		}
		Kolczatki=0;
		for(new c=0;c<5;c++)
		{
			DestroyObject(KolczatkaObiekt[c]);
			Kolczatka[c]=false;
		}
		Info(playerid,""C_ZOLTY"Kolczatki usuniÍte!");
		return 1;
	}

	COMMAND:kol(playerid,cmdtext[])
	{
	  return cmd_kolczatka(playerid,cmdtext);
	}

	CMD:kolczatka(playerid, cmdtext[])
	{
        if(!ToPD(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        if(IsPlayerInAnyVehicle(playerid))
 		{
			Info(playerid,""C_CZERWONY"Nie moøesz po≥oøyÊ blokady bÍdπc w pojeüdzie!");
   			return 1;
   		}
   		if(Kolczatki>=5)
   		{
   		    Info(playerid,""C_CZERWONY"Nie moøna po≥oøyÊ wiÍkszej iloúci kolczatek! Uøyj cmd: /zbierz");
   			return 1;
   		}
   		new Float:pos[4],n=Kolczatki;
   		Kolczatki++;
		GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
		GetPlayerFacingAngle(playerid,pos[3]);
		switch(n)
		{
		    case 0:
		    {
		        Kolczatka[0]=true;
				KolczatkaObiekt[0]=CreateObject(2892,pos[0],pos[1],pos[2]-1,0,0,pos[3]+90);
				KolPosX[0]=pos[0]; KolPosY[0]=pos[1]; KolPosZ[0]=pos[2];
				Info(playerid,""C_ZOLTY"Rozstawi≥eú kolczatkÍ numer 1!");
				return 1;
		    }
		    case 1:
		    {
      			Kolczatka[1]=true;
			 	KolczatkaObiekt[1]=CreateObject(2892,pos[0],pos[1],pos[2]-1,0,0,pos[3]+90);
			 	KolPosX[1]=pos[0]; KolPosY[1]=pos[1]; KolPosZ[1]=pos[2];
			 	Info(playerid,""C_ZOLTY"Rozstawi≥eú kolczatkÍ numer 2!");
			 	return 1;
		    }
		    case 2:
		    {
		    	Kolczatka[2]=true;
			 	KolczatkaObiekt[2]=CreateObject(2892,pos[0],pos[1],pos[2]-1,0,0,pos[3]+90);
			 	KolPosX[2]=pos[0]; KolPosY[2]=pos[1]; KolPosZ[2]=pos[2];
			 	Info(playerid,""C_ZOLTY"Rozstawi≥eú kolczatkÍ numer 3!");
			 	return 1;
		    }
		    case 3:
		    {
		        Kolczatka[3]=true;
			 	KolczatkaObiekt[3]=CreateObject(2892,pos[0],pos[1],pos[2]-1,0,0,pos[3]+90);
			 	KolPosX[3]=pos[0]; KolPosY[3]=pos[1]; KolPosZ[3]=pos[2];
			 	Info(playerid,""C_ZOLTY"Rozstawi≥eú kolczatkÍ numer 4!");
			 	return 1;
		    }
		    case 4:
		    {
		    	Kolczatka[4]=true;
			 	KolczatkaObiekt[4]=CreateObject(2892,pos[0],pos[1],pos[2]-1,0,0,pos[3]+90);
			 	KolPosX[4]=pos[0]; KolPosY[4]=pos[1]; KolPosZ[4]=pos[2];
			 	Info(playerid,""C_ZOLTY"Rozstawi≥eú kolczatkÍ numer 5!");
			 	return 1;
		    }
		}
   		return 1;
	}

	CMD:blokada(playerid, cmdtext[])
	{
        if(!ToPOMOC(playerid))
        {
            Info(playerid,""C_CZERWONY"Nie jesteú w mundurze lub nie pracujesz w policji!");
            return 1;
        }
        if(IsPlayerInAnyVehicle(playerid))
 		{
			Info(playerid,""C_CZERWONY"Nie moøesz po≥oøyÊ kolczatki bÍdπc w pojeüdzie!");
   			return 1;
   		}
        new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /blokada (numer)\n1 - 6 (rÛøne blokadki)\n7 - usuwasz wszystkie blokady");
			return 1;
 		}
	 	new id = strval(tmp);
		if(id<1||id>7) return 1;
		new n=Blokady,Float:Pos[4];
		Blokady++;
  		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
    	GetPlayerFacingAngle(playerid,Pos[3]);
        switch(id)
        {
            case 1:
			{
			    if(Blokady>=14)
			    {
				    Info(playerid,""C_CZERWONY"Maskymalna iloúÊ blokadek, usuÒ je za pomocπ komendy /blokada 7");
				    return 1;
			    }
				Blokadka[n]=CreateObject(979,Pos[0]+1.0, Pos[1]+1.0, Pos[2]-0.3, 0.0, 0.0000, Pos[3]); Info(playerid,""C_ZOLTY"Blokada postawiona!");
			}
            case 2:
			{
			    if(Blokady>=14)
			    {
				    Info(playerid,""C_CZERWONY"Maskymalna iloúÊ blokadek, usuÒ je za pomocπ komendy /usun-blokady");
				    return 1;
			    }
		 		Blokadka[n]=CreateObject(1228,Pos[0]+1.0, Pos[1]+1.0, Pos[2]-0.4, 0.0, 0.0000, Pos[3]); Info(playerid,""C_ZOLTY"Blokada postawiona!");
			}
            case 3:
			{
			    if(Blokady>=14)
			    {
				    Info(playerid,""C_CZERWONY"Maskymalna iloúÊ blokadek, usuÒ je za pomocπ komendy /usun-blokady");
				    return 1;
			    }
		 		Blokadka[n]=CreateObject(1237,Pos[0]+1.0, Pos[1]+1.0, Pos[2]-0.8, 0.0, 0.0000, Pos[3]); Info(playerid,""C_ZOLTY"Blokada postawiona!");
			}
            case 4:
			{
			    if(Blokady>=14)
			    {
				    Info(playerid,""C_CZERWONY"Maskymalna iloúÊ blokadek, usuÒ je za pomocπ komendy /usun-blokady");
				    return 1;
			    }
		 		Blokadka[n]=CreateObject(1427,Pos[0]+1.0, Pos[1]+1.0, Pos[2]-0.4, 0.0, 0.0000, Pos[3]); Info(playerid,""C_ZOLTY"Blokada postawiona!");
			}
            case 5:
			{
			    if(Blokady>=14)
			    {
				    Info(playerid,""C_CZERWONY"Maskymalna iloúÊ blokadek, usuÒ je za pomocπ komendy /usun-blokady");
				    return 1;
			    }
				Blokadka[n]=CreateObject(1424,Pos[0]+1.0, Pos[1]+1.0, Pos[2]-0.5, 0.0, 0.0000, Pos[3]); Info(playerid,""C_ZOLTY"Blokada postawiona!");
			}
            case 6:
			{
			    if(Blokady>=14)
			    {
				    Info(playerid,""C_CZERWONY"Maskymalna iloúÊ blokadek, usuÒ je za pomocπ komendy /usun-blokady");
				    return 1;
			    }
		 		Blokadka[n]=CreateObject(1459,Pos[0]+1.0, Pos[1]+1.0, Pos[2]-0.5, 0.0, 0.0000, Pos[3]); Info(playerid,""C_ZOLTY"Blokada postawiona!");
			}
            case 7:
            {
				if(Blokady==0)
				{
                    Info(playerid,""C_CZERWONY"Øadna blokada nie jest postawiona!");
				    return 1;
				}
                Info(playerid,""C_ZOLTY"Blokady usuniÍte!");
			    Blokady=0;
				for(new c=0;c<15;c++)
				{
					DestroyObject(Blokadka[c]);
				}
				return 1;
            }
        }
	    return 1;
	}

	CMD:flip(playerid, cmdtext[])
	{
	    if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
	    {
	        Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ øadnego pojazdu!");
            return 1;
	    }
	    if(!dCzyMaKase(playerid,50))
	    {
	        Info(playerid,""C_CZERWONY"Nie staÊ ciebie na us≥ugÍ mechanika! (50$)");
			return 1;
		}
		dDodajKase(playerid,-50);
	    new Float:Pos[4],v=GetPlayerVehicleID(playerid);
	    GetVehiclePos(v,Pos[0],Pos[1],Pos[2]);
     	GetVehicleZAngle(v,Pos[3]);
		SetVehiclePos(v,Pos[0],Pos[1],Pos[2]);
		SetVehicleZAngle(v,Pos[3]);
		Info(playerid,""C_ZOLTY"ObrÛci≥eú pojazd na cztery ko≥a za 50$!");
	    return 1;
	}

	CMD:napraw(playerid, cmdtext[])
	{
	    if(!ToPOMOC(playerid))
	    {
	        Info(playerid,"Nie pracujesz w PD!");
	        return 1;
		}
	    if(!IsPlayerInAnyVehicle(playerid))
	    {
    		Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ øadnego pojazdu!");
            return 1;
	    }
	    if(GetPlayerSpeed(playerid)>1)
	    {
	    	Info(playerid,""C_CZERWONY"Musisz siÍ zatrzymaÊ, aby uøyÊ tej komendy!");
            return 1;
	    }
	    new Float:HP;
	    GetVehicleHealth(GetPlayerVehicleID(playerid),HP);
	    if(HP>=999.0)
	    {
	    	Info(playerid,""C_CZERWONY"Ten pojazd jest w perfekcyjnym stanie!");
            return 1;
	    }
		new Float:Pos[3];
		GetVehiclePos(GetPlayerVehicleID(playerid),Pos[0],Pos[1],Pos[2]);
		KillTimer(NaprawTimer[playerid]);
		NaprawTimer[playerid]=SetTimerEx("NaprawPojazd",1000,false,"iifff",playerid,GetPlayerVehicleID(playerid),Pos[0],Pos[1],Pos[2]);
  		return 1;
	}

	forward PaliwoPojazd(playerid,vehicleid,Float:PosX,Float:PosY,Float:PosZ);
	public PaliwoPojazd(playerid,vehicleid,Float:PosX,Float:PosY,Float:PosZ)
	{
	    if(!IsPlayerInVehicle(playerid,vehicleid))
	    {
	        GInfo(playerid,"~r~przegapiles mechanika~n~nie jestes w odpowiednim pojezdzie!",3);
	        return 1;
	    }
	    if(GetPlayerSpeed(playerid)>1)
	    {
	    	GInfo(playerid,"~r~przegapiles mechanika~n~nie stales w miejscu!",3);
            return 1;
	    }
	    if(!DoInRange(7.0, playerid,PosX,PosY,PosZ))
		{
            GInfo(playerid,"~r~przegapiles mechanika~n~nie stales odpowiednim w miejscu!",3);
			return 1;
		}
	    new v=GetPlayerVehicleID(playerid),potrzebne=vPaliwoMax[v]-vPaliwo[v];
		if(potrzebne<20)
		{
			Info(playerid, ""C_CZERWONY"TwÛj pojazd ma jeszcze paliwo!");
			return 1;
		}
	    if(!dCzyMaKase(playerid,350))
	    {
			Info(playerid,""C_CZERWONY"Nie staÊ ciebie na us≥ugÍ mechanika!(350$)!");
			return 1;
		}
		dDodajKase(playerid,-350);
        vPaliwo[v]+=20;
		Info(playerid,""C_ZOLTY"Pojazd dotankowany!\nZap≥aci≥eú:350$ za 20 litrÛw");
	    return 1;
	}

	forward NaprawPojazd(playerid,vehicleid,Float:PosX,Float:PosY,Float:PosZ);
	public NaprawPojazd(playerid,vehicleid,Float:PosX,Float:PosY,Float:PosZ)
	{
	    new Float:HP,koszt;
	    GetVehicleHealth(vehicleid,HP);
  		koszt=floatround((1000.0-HP)*3.1);
		RepairVehicle(vehicleid);
		SetVehicleHealth(vehicleid,1000.0);
		format(dstring,sizeof(dstring),""C_ZOLTY"Pojazd naprawiony!\nDoZap≥aty: %d$",koszt);
		Info(playerid,dstring);
	    return 1;
	}

	forward VNaprawPojazd(playerid,vehicleid,Float:PosX,Float:PosY,Float:PosZ);
	public VNaprawPojazd(playerid,vehicleid,Float:PosX,Float:PosY,Float:PosZ)
	{
	    new Float:HP;
	    GetVehicleHealth(vehicleid,HP);
		RepairVehicle(vehicleid);
		SetVehicleHealth(vehicleid,1000.0);
		format(dstring,sizeof(dstring),""C_ZOLTY"Pojazd naprawiony!");
		Info(playerid,dstring);
		dDodajKase(playerid,-500);
	    return 1;
	}

	CMD:lider(playerid, cmdtext[])
	{
		if(PlayerInfo[playerid][pLider]==0)
		{
		    Info(playerid,""C_CZERWONY"Nie jesteú liderem!");
		    return 1;
		}
		new tmp[64],idx,f=PlayerInfo[playerid][pLider];
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /lider (nr)\n1 - zatrudnij\n2 - wyrzuÊ");
			return 1;
 		}
	 	new id = strval(tmp);
		if(id==1)
		{
		    tmp = strtok(cmdtext, idx);
		    if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /lider 1 (id)");
				return 1;
	 		}
		    new playa = strval(tmp);
		    if(IsPlayerConnected(playa)&&playerid!=playa)
		    {
		        if(Misja[playa])
		        {
		            Info(playerid,""C_CZERWONY"Ten gracz aktualnie wykonuje zlecenie!");
		            return 1;
		        }
		        PlayerInfo[playa][pFrakcja]=f;
		        ZapiszKonto(playa);
			    format(dstring, sizeof(dstring),""C_ZOLTY"%s zatrudni≥ ciebie do frakcji: %d\nAby zmieniÊ skin uøyj /skin",Nick(playerid),f);
			    Info(playa,dstring);
			    format(dstring, sizeof(dstring),""C_ZOLTY"Zatrudni≥eú %s do twojej frakcji",Nick(playa));
			    Info(playerid,dstring);
		        return 1;
		    }
		    else
		    {
				Info(playerid,""C_CZERWONY"Nie poprawne id gracza!");
		    }
		    return 1;
		}
		else if(id==2)
		{
		    tmp = strtok(cmdtext, idx);
		    if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /lider 2 (id)");
				return 1;
	 		}
		    new playa = strval(tmp);
		    if(IsPlayerConnected(playa)&&playerid!=playa)
		    {
		        if(PlayerInfo[playa][pFrakcja]!=PlayerInfo[playerid][pFrakcja])
		        {
		            Info(playerid,"Ten gracz nie pracuje w twojej frakcji!");
		            return 1;
		        }
		        PlayerInfo[playa][pFrakcja]=0;
		        ZapiszKonto(playa);
			    format(dstring, sizeof(dstring),""C_ZOLTY"%s zwolni≥ ciebie.",Nick(playerid));
			    Info(playa,dstring);
			    format(dstring, sizeof(dstring),""C_ZOLTY"Zwolni≥eú %s z twojej frakcji.",Nick(playa));
			    Info(playerid,dstring);
		        return 1;
		    }
		    else
		    {
				Info(playerid,""C_CZERWONY"Nie poprawne id gracza!");
		    }
		    return 1;
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Nie poprawny numer!");
		}
		return 1;
	}

	CMD:dajlider(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,3)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /dajlider (ID) (frakcja)\n1 - Policja\n2 - Pomoc Drogowa\n3 - Firma Lotnicza\n\nFirmy\n10 - Speed Trans (Sirvon)\n\n0 - zabierasz lidera");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new level = strval(tmp);
	 	if(level<0||level>20){ Info(playerid,"Poziom od 0 do 20!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    PlayerInfo[playa][pLider]=level;
		    PlayerInfo[playa][pFrakcja]=level;
		    ZapiszKonto(playa);
		    format(dstring, sizeof(dstring),"%s da≥ tobie lidera frakcji: %d",Nick(playerid),level);
		    Info(playa,dstring);
		    format(dstring, sizeof(dstring),"Da≥eú %s lidera frakcji: %d",Nick(playa),level);
		    Info(playerid,dstring);
		    return 1;
		}
		return 1;
	}

	CMD:dajadmin(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,3)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /dajadmin (ID) (poziom)\n1 - Junior Admin\n2 - Admin\n3 - Head Admin\n\n0 - zabierasz admina");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new level = strval(tmp);
	 	if(level<0||level>3){ Info(playerid,"Poziom od 0 do 3!"); return 1; }
	 	if(playa==playerid){ Info(playerid,"Nie moøesz wyrzuciÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    PlayerInfo[playa][pAdmin]=level;
		    ZapiszKonto(playa);
		    format(dstring, sizeof(dstring),"%s ustawi≥ tobie poziom admina na: %d\n\nListÍ komend admina znajdziesz pod "C_ZIELONY"/apomoc",Nick(playerid),level);
		    Info(playa,dstring);
		    format(dstring, sizeof(dstring),"Ustawi≥eú %s poziom admina na: %d",Nick(playa),level);
		    Info(playerid,dstring);
		    return 1;
		}
		return 1;
	}

	CMD:sprawdzip(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,2)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /sprawdzip (ID)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz sprawdziÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz sprawdziÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
	     	new plrIP[16];
    		GetPlayerIp(playa, plrIP, sizeof(plrIP));
            format(dstring, sizeof(dstring),"Gracz: [%d]%s, ip: %s",playa,Nick(playa),plrIP);
		    SendClientMessage(playerid,KOLOR_ROZOWY,dstring);
            return 1;
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

    CMD:spec(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /spec (ID)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz specowaÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz specowaÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
		    Spec[playerid]=true;
		    TogglePlayerSpectating(playerid,true);
            SetTimerEx("SpecSystem",1000,false,"ii",playerid,playa);
            return 1;
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	CMD:specoff(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
        if(Spec[playerid]==true)
        {
            Spec[playerid]=false;
            TogglePlayerSpectating(playerid,false);
        }
        else
        {
   			Info(playerid,"Nie jesteú na specu!");
        }
		return 1;
	}

	CMD:odczep(playerid, cmdtext[])
	{
	    new v=GetPlayerVehicleID(playerid);
		if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)//ciÍøarowe
		{
		    if(!GetVehicleTrailer(v))
		    {
		        Info(playerid,""C_CZERWONY"Nie masz podczepionej naczepy!");
	        	return 1;
		    }
		    DetachTrailerFromVehicle(v);
		    Info(playerid,""C_ZOLTY"Odczepi≥eú naczepÍ");
		    return 1;
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ ciÍøarÛwki!");
		}
	    return 1;
	}

	CMD:respawn(playerid, cmdtext[])
	{
		if(Misja[playerid]==true)
		{
		    Info(playerid,""C_CZERWONY"Podczas misji nie moøna uøyÊ tej komendy!");
		    return 1;
		}
		if(IsPlayerInAnyVehicle(playerid))
		{
		    Info(playerid,""C_CZERWONY"Nie moøesz byÊ w pojeüdzie!");
		    return 1;
		}
		if(!dCzyMaKase(playerid,500))
	    {
			Info(playerid,""C_CZERWONY"Nie masz tyle pieniÍdzy! (500$)");
			return 1;
		}
		dDodajKase(playerid,-500);
		GInfo(playerid,"~g~zespawnowany",1);
		CallLocalFunction("OnPlayerSpawn", "i",playerid);
		return 1;
	}
/*
	CMD:przeladowany(playerid, cmdtext[])
	{
		if(Misja[playerid]==true)
		{
		    Info(playerid,""C_CZERWONY"Gdy przyje≥eú juø zlecenie nie moøesz uøyÊ tej komendy!");
		    return 1;
		}
		if(Przeladowany[playerid]==true)
		{
		    Info(playerid,""C_ZIELONY"Od tego momentu towar,ktÛry za≥adujesz nie bÍdzie prze≥adowany!");
		    Przeladowany[playerid]=false;
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Od tego momentu towar,ktÛry za≥adujesz bÍdzie prze≥adowany!");
		    Przeladowany[playerid]=true;
		}
		return 1;
	}

	CMD:anuluj(playerid, cmdtext[])
	{
	    if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        Info(playerid,""C_CZERWONY"Komenda chwilowo wy≥πczona");
	        return 1;
		}
		if(Misja[playerid]==true)
		{
		    ShowPlayerDialog(playerid,11,DIALOG_STYLE_MSGBOX,""C_POMARANCZOWY"Anulowanie misji",""C_ZOLTY"Anulowanie misji wiπøe siÍ z grzywnπ wynoszπcπ: "C_CZERWONY"1000$\n"C_ZOLTY"Czy na pewno chcesz anulowaÊ misjÍ?","Tak","Nie");
		}
		else
		{
		    Info(playerid,""C_CZERWONY"Nie wykonujesz øadnej misji!");
		}
		return 1;
	}

	CMD:zlecenie(playerid, cmdtext[])
	{
	    if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        Info(playerid,""C_CZERWONY"Komenda chwilowo wy≥πczona");
	        return 1;
		}
	    if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
	    {
	        Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ øadnego pojazdu!");
	        return 1;
	    }
	    if(ToPD(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Bedπc policjantem na s≥uøbie nie moøesz przyjmowaÊ zleceÒ\nZmieÒ postaÊ za pomocπ komendy /skin!");
	        return 1;
	    }
	    if(Misja[playerid]==true)
	    {
	        Info(playerid,""C_CZERWONY"Aktualnie wykonujesz juø misjÍ!");
	        return 1;
	    }
	    new v=GetPlayerVehicleID(playerid),id;
		if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)//ciÍøarowe
		{
		    if(GetVehicleTrailer(v)==0)
		    {
		        Info(playerid,""C_CZERWONY"Nie masz podczepionej naczepy!");
	        	return 1;
		    }
		    new naczepa=GetVehicleModel(GetVehicleTrailer(v));
		    if(naczepa==435||naczepa==450||naczepa==591||naczepa==584)
		    {
				id=LosujMisje(playerid);
				if(id!=999)
				{
				    PlayerInfo[playerid][pMisja]=1;
				    ZapiszKonto(playerid);
				    Misja[playerid]=true;
				    MisjaID[playerid]=id;
					MisjaStopien[playerid]=0;
					MisjaPojazd[playerid]=GetVehicleTrailer(v);
					OstatniaMisja[playerid]=id;
				    format(dstring, sizeof(dstring), "~g~%s ~w~z ~y~%s ~w~do ~y~%s",LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
				    LadunekNapis(playerid,dstring);
				    Info(playerid,""C_ZIELONY"Zlecenie przyjetÍ!\nJedü na miejsce za≥adunku!\n"C_CZERWONY"Towar musisz za≥adowaÊ do tej naczepy, nie zgub jej!");
				    SetPlayerCheckpoint(playerid,LadunekInfo[id][lPosX],LadunekInfo[id][lPosY],LadunekInfo[id][lPosZ],5);
					return 1;
				}
				else
				{
				    Info(playerid,""C_CZERWONY"Losowanie misji nie powiod≥o siÍ, wpisz ponownie komendÍ!");
				}
				return 1;
		    }
		    else
		    {
		        Info(playerid,""C_CZERWONY"Masz nie odpowiedniπ naczepÍ!");
		    }
		    return 1;
		}
		else if(ToBus(v))
		{
		    id=LosujMisje(playerid);
			if(id!=999)
			{
			    PlayerInfo[playerid][pMisja]=1;
			    ZapiszKonto(playerid);
   				Misja[playerid]=true;
			    MisjaID[playerid]=id;
				MisjaStopien[playerid]=0;
				MisjaPojazd[playerid]=v;
				OstatniaMisja[playerid]=id;
    			format(dstring, sizeof(dstring), "~g~%s ~w~z ~y~%s ~w~do ~y~%s",LadunekInfo[id][lTowar],LadunekInfo[id][lZaladunek],LadunekInfo[id][lDostarczenie]);
    			LadunekNapis(playerid,dstring);
			    Info(playerid,""C_ZIELONY"Zlecenie przyjetÍ!\nJedü na miejsce za≥adunku!\n"C_CZERWONY"Towar musisz za≥adowaÊ do tego pojazdu, nie zmieniaj go!");
			    SetPlayerCheckpoint(playerid,LadunekInfo[id][lPosX],LadunekInfo[id][lPosY],LadunekInfo[id][lPosZ],5);
				return 1;
			}
			else
			{
   				Info(playerid,""C_CZERWONY"Losowanie misji nie powiod≥o siÍ, wpisz ponownie komendÍ!");
			}
			return 1;
		}
		else
		{
			Info(playerid,""C_CZERWONY"Ten pojazd nie moøe przewoziÊ towarÛw!");
		}
		return 1;
	}
*/
	CMD:text(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,3)) return 1;
		new tmp[64],idx,text[80];
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /text (nr)\n1 - tworzenie nowego textu\n2 - edycja textu\n3 - lista istniejacych textow\n4 - usun text");
	 		return 1;
	 	}
	 	new numer = strval(tmp);
		if(numer==1)
		{
		    if(TextTworzenie==false&&TextPkt[playerid]==0)
			{
				Info(playerid,"Ten panel aktualnie jest uøywany przez kogoú innego!\nMusisz poczekaÊ!");
				return 1;
			}
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /text 1 (nr)\n1 - treúÊ textu\n2 - pozycja textu\n3 - zapisz i dodaj\n99 - anuluj");
		 		return 1;
		 	}
		 	new punkt = strval(tmp);
		 	switch(punkt)
		 	{
		 	    case 1:
		 	    {
		 	        if(TextPkt[playerid]!=0)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 	        text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /text 1 1 (treúÊ textu)");
						return 1;
					}
					if(strlen(text)<3||strlen(text)>64)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 64 liter!");
						return 1;
					}
					for(new nr = 0; nr < LIMIT_TEXTOW; nr++)
					{
						if(TextInfo[nr][tAktywny]==0)
				 		{
				 			TextID[playerid]=nr;
							TextTworzenie=false;
							TextPkt[playerid]=1;
							strmid(TextInfo[nr][tNapis], text, 0, strlen(text), 64);
							Info(playerid,"TreúÊ textu3d ustalona!");
							return 1;
						}
					}
					return 1;
		 	    }//koniec przypadku
		 	    case 2:
		 	    {
		 	        if(TextPkt[playerid]!=1)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
	                new nr=TextID[playerid];
				 	TextPkt[playerid]=2;
				 	GetPlayerPos(playerid,TextInfo[nr][tPosX],TextInfo[nr][tPosY],TextInfo[nr][tPosZ]);
				 	Info(playerid,"Pozycja textu pobrana!");
					return 1;
		 	    }//koniec przypadku
		 	    case 3:
		 	    {
		 	        if(TextPkt[playerid]!=2)
			 		{
				 		Info(playerid,"Nie wykona≥eú jeszcze wszystkich punktÛw!");
				 		return 1;
		 			}
		 			new nr=TextID[playerid];
		 			TextInfo[nr][tAktywny]=1;
		 			TextNapis[nr]=CreateDynamic3DTextLabel(ColouredText(TextInfo[nr][tNapis]),KOLOR_BIALY,TextInfo[nr][tPosX],TextInfo[nr][tPosY],TextInfo[nr][tPosZ],40.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,-1,-1,-1,-1,40.0);
		 			ZapiszText(nr);
		 			TextID[playerid]=9999;
					TextPkt[playerid]=0;
					TextTworzenie=true;
		 			format(dstring, sizeof(dstring),"Poprawnie doda≥eú text3d o ID: %d",nr);
		 			Info(playerid,dstring);
		 	        return 1;
		 	    }//koniec przypadku
		 	    case 99:
		 	    {
		 	        if(TextPkt[playerid]==0)
			 		{
				 		Info(playerid,"Nie moøesz anulowaÊ pracy, poniewaø jej nie zacze≥eú!");
				 		return 1;
		 			}
		 			TextID[playerid]=9999;
					TextPkt[playerid]=0;
					TextTworzenie=true;
					Info(playerid,"Praca anulowana!");
		 	        return 1;
		 	    }//koniec przypadku
			}//switch
		}//punkt
		else if(numer==2)
		{
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /text 2 (ID) (nr)\n1 - treúÊ textu\n2 - pozycja textu");
		 		return 1;
		 	}
		 	new nr = strval(tmp);
		 	tmp = strtok(cmdtext, idx);
		 	new punkt = strval(tmp);
		 	if(TextInfo[nr][tAktywny]==0)
	 		{
	 		    Info(playerid,"Nie poprawne id textu3d!");
	 		    return 1;
			}
		 	switch(punkt)
		 	{
		 	    case 1:
		 	    {
		 	        text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /text 2 (id) 1 (treúÊ textu)");
						return 1;
					}
					if(strlen(text)<3||strlen(text)>64)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 64 liter!");
						return 1;
					}
					strmid(TextInfo[nr][tNapis], text, 0, strlen(text), 64);
					DestroyDynamic3DTextLabel(TextNapis[nr]);
					TextNapis[nr]=CreateDynamic3DTextLabel(ColouredText(TextInfo[nr][tNapis]),KOLOR_BIALY,TextInfo[nr][tPosX],TextInfo[nr][tPosY],TextInfo[nr][tPosZ],30.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,-1,-1,-1,-1,30.0);
					Info(playerid,"TreúÊ textu3d zmieniona!");
					ZapiszText(nr);
					return 1;
		 	    }//koniec przypadku
		 	    case 2:
		 	    {
				 	GetPlayerPos(playerid,TextInfo[nr][tPosX],TextInfo[nr][tPosY],TextInfo[nr][tPosZ]);
				 	Info(playerid,"Pozycja textu zmieniona!");
				 	DestroyDynamic3DTextLabel(TextNapis[nr]);
					TextNapis[nr]=CreateDynamic3DTextLabel(TextInfo[nr][tNapis],KOLOR_BIALY,TextInfo[nr][tPosX],TextInfo[nr][tPosY],TextInfo[nr][tPosZ],30.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,-1,-1,-1,-1,30.0);
					ZapiszText(nr);
					return 1;
		 	    }//koniec przypadku
			}//switch
			return 1;
		}//punkt
		else if(numer==3)
		{
		    SendClientMessage(playerid,KOLOR_ZOLTY,"Istniejπce texty 3d:");
		    for(new nr = 0; nr < LIMIT_TEXTOW; nr++)
			{
				if(TextInfo[nr][tAktywny]==1)
				{
				    format(dstring, sizeof(dstring),"Text 3d ID: %d TreúÊ: %s",nr,TextInfo[nr][tNapis]);
		    		SendClientMessage(playerid,KOLOR_BIALY,dstring);
				}
			}
		    return 1;
		}
	 	else if(numer==4)
		{
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /text 4 (ID)");
		 		return 1;
		 	}
		 	new nr = strval(tmp);
		 	if(TextInfo[nr][tAktywny]==0)
	 		{
	 		    Info(playerid,"Nie poprawne id textu3d!");
	 		    return 1;
			}
            DestroyDynamic3DTextLabel(TextNapis[nr]);
            TextInfo[nr][tAktywny]=0;
            ZapiszText(nr);
            Info(playerid,"Text usuniÍty!");
			return 1;
		}
		return 1;
	}//komenda


	CMD:ladunek(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,3)) return 1;
		new tmp[64],idx,text[80];
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /ladunek (nr)\n1 - tworzenie nowego ≥adunku\n2 - edycja ≥adunku\n3 - lista istniejπcych ≥adunkÛw\n4 - usuÒ ≥adunek");
	 		return 1;
	 	}
	 	new numer = strval(tmp);
		if(numer==1)
		{
		    if(LadunekTworzenie==false&&LadunekPkt[playerid]==0)
			{
				Info(playerid,"Ten panel aktualnie jest uøywany przez kogoú innego!\nMusisz poczekaÊ!");
				return 1;
			}
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /≥adunek 1 (nr)\n1 - nazwa towaru\n2 - cena za 1 kg. towaru\n3 - Miejsce za≥adunku\n4 - pozycja za≥adunku\n5 - miejsce roz≥adunku\n6 - pozycja roz≥adunku\n7 - zapisz i dodaj ≥adunek\n99 - anuluj");
		 		return 1;
		 	}
		 	new punkt = strval(tmp);
		 	switch(punkt)
		 	{
		 	    case 1:
		 	    {
		 	        if(LadunekPkt[playerid]!=0)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 	        text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /ladunek 1 1 (nazwa towaru)");
						return 1;
					}
					if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
					for(new nr = 0; nr < LIMIT_LADUNKOW; nr++)
					{
						if(LadunekInfo[nr][lAktywny]==0)
				 		{
				 			LadunekID[playerid]=nr;
							LadunekTworzenie=false;
							LadunekPkt[playerid]=1;
							strmid(LadunekInfo[nr][lTowar], text, 0, strlen(text), 64);
							Info(playerid,"Nazwa towaru ustalona! Przejdü do kolejnego punktu!");
							return 1;
						}
					}
					return 1;
		 	    }//koniec przypadku
		 	    case 2:
		 	    {
		 	        if(LadunekPkt[playerid]!=1)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			tmp = strtok(cmdtext, idx);
					if(isnull(tmp))
					{
						Info(playerid,"Uøyj: /ladunek 1 2 (kwota za 1 kg)");
				 		return 1;
				 	}
				 	new Float:kwota=floatstr(tmp);
				 	if(kwota<0.5||kwota>5.0)
				 	{
				 	    Info(playerid,"Od 0.5$ do 5.0$");
				 	    return 1;
				 	}
				 	new nr=LadunekID[playerid];
				 	LadunekPkt[playerid]=2;
				 	LadunekInfo[nr][lTowarKoszt]=kwota;
				 	Info(playerid,"Kwota za kg towaru ustalona!");
				 	return 1;
				}//koniec przypadku
				case 3:
		 	    {
		 	        if(LadunekPkt[playerid]!=2)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /ladunek 1 3 (nazwa miejsca za≥adunku)");
				 		return 1;
				 	}
				 	if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
				 	new nr=LadunekID[playerid];
				 	LadunekPkt[playerid]=3;
				 	strmid(LadunekInfo[nr][lZaladunek], text, 0, strlen(text), 64);
				 	Info(playerid,"Nazwa miejsca za≥adunku ustalona!");
				 	return 1;
				}//koniec przypadku
				case 4:
		 	    {
		 	        if(LadunekPkt[playerid]!=3)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			if(GetPlayerInterior(playerid)!=0)
		 			{
		 			    Info(playerid,"Nie moøe byÊ to w interiorze!");
		 			    return 1;
		 			}
				 	new nr=LadunekID[playerid];
				 	LadunekPkt[playerid]=4;
				 	GetPlayerPos(playerid,LadunekInfo[nr][lPosX],LadunekInfo[nr][lPosY],LadunekInfo[nr][lPosZ]);
				 	Info(playerid,"Pozycja miejsca za≥adunku pobrana!");
				 	return 1;
				}//koniec przypadku
				case 5:
		 	    {
		 	        if(LadunekPkt[playerid]!=4)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /ladunek 1 5 (nazwa miejsca roz≥adunku)");
				 		return 1;
				 	}
				 	if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
				 	new nr=LadunekID[playerid];
				 	LadunekPkt[playerid]=5;
				 	strmid(LadunekInfo[nr][lDostarczenie], text, 0, strlen(text), 64);
				 	Info(playerid,"Nazwa miejsca roz≥adunku ustalona!");
				 	return 1;
				}//koniec przypadku
				case 6:
		 	    {
		 	        if(LadunekPkt[playerid]!=5)
			 		{
				 		Info(playerid,"Ta opcja zosta≥a juø wykonana lub nie robisz punktÛw w odpowiedniej kolejnoúci!");
				 		return 1;
		 			}
		 			if(GetPlayerInterior(playerid)!=0)
		 			{
		 			    Info(playerid,"Nie moøe byÊ to w interiorze!");
		 			    return 1;
		 			}
				 	new nr=LadunekID[playerid];
				 	LadunekPkt[playerid]=6;
				 	GetPlayerPos(playerid,LadunekInfo[nr][lPos2X],LadunekInfo[nr][lPos2Y],LadunekInfo[nr][lPos2Z]);
				 	Info(playerid,"Pozycja miejsca roz≥adunku pobrana!");
				 	return 1;
				}//koniec przypadku
				case 7:
		 	    {
		 	        if(LadunekPkt[playerid]!=6)
			 		{
				 		Info(playerid,"Nie wykona≥eú jeszcze wszystkich punktÛw!");
				 		return 1;
		 			}
		 			new nr=LadunekID[playerid];
		 			LadunekInfo[nr][lAktywny]=1;
		 			ZapiszLadunek(nr);
		 			LadunekID[playerid]=9999;
					LadunekPkt[playerid]=0;
					LadunekTworzenie=true;
		 			format(dstring, sizeof(dstring),"Poprawnie doda≥eú ofertÍ transportowπ o ID: %d",nr);
		 			Info(playerid,dstring);
		 	        return 1;
		 	    }//koniec przypadku
		 	    case 99:
		 	    {
		 	        if(LadunekPkt[playerid]==0)
			 		{
				 		Info(playerid,"Nie moøesz anulowaÊ pracy, poniewaø jej nie zacze≥eú!");
				 		return 1;
		 			}
		 			LadunekID[playerid]=9999;
					LadunekPkt[playerid]=0;
					LadunekTworzenie=true;
					Info(playerid,"Praca anulowana!");
		 	        return 1;
		 	    }//koniec przypadku
			}
			return 1;
		}
		else if(numer==2)
		{
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /≥adunek 2 (id ≥adunku) (nr)\n1 - nazwa towaru\n2 - cena za 1 kg. towaru\n3 - Miejsce za≥adunku\n4 - pozycja za≥adunku\n5 - miejsce roz≥adunku\n6 - pozycja roz≥adunku");
		 		return 1;
		 	}
		 	new nr = strval(tmp);
		 	tmp = strtok(cmdtext, idx);
		 	new punkt = strval(tmp);
		 	if(LadunekInfo[nr][lAktywny]==0)
 			{
 			    Info(playerid,"Nie poprawne id ≥adunku!");
 			    return 1;
 			}
		 	switch(punkt)
		 	{
		 	    case 1:
				{
		 	        text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /ladunek 2 (id) 1 (nazwa towaru)");
						return 1;
					}
					if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
					strmid(LadunekInfo[nr][lTowar], text, 0, strlen(text), 64);
					Info(playerid,"Nazwa towaru zmieniona!");
					ZapiszLadunek(nr);
					return 1;
		 	    }//koniec przypadku
		 	    case 2:
		 	    {
		 			tmp = strtok(cmdtext, idx);
					if(isnull(tmp))
					{
						Info(playerid,"Uøyj: /ladunek 2 (id) 2 (kwota za 1 kg)");
				 		return 1;
				 	}
				 	new Float:kwota=floatstr(tmp);
				 	if(kwota<0.5||kwota>5.0)
				 	{
				 	    Info(playerid,"Od 0.5$ do 5.0$");
				 	    return 1;
				 	}
				 	LadunekInfo[nr][lTowarKoszt]=kwota;
				 	Info(playerid,"Kwota za kg towaru zmieniona!");
				 	ZapiszLadunek(nr);
				 	return 1;
				}//koniec przypadku
				case 3:
		 	    {
		 			text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /ladunek 2 (id) 3 (nazwa miejsca za≥adunku)");
				 		return 1;
				 	}
				 	if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
				 	strmid(LadunekInfo[nr][lZaladunek], text, 0, strlen(text), 64);
				 	Info(playerid,"Nazwa miejsca za≥adunku zmieniona!");
				 	ZapiszLadunek(nr);
				 	return 1;
				}//koniec przypadku
				case 4:
		 	    {
		 			if(GetPlayerInterior(playerid)!=0)
		 			{
		 			    Info(playerid,"Nie moøe byÊ to w interiorze!");
		 			    return 1;
		 			}
				 	GetPlayerPos(playerid,LadunekInfo[nr][lPosX],LadunekInfo[nr][lPosY],LadunekInfo[nr][lPosZ]);
				 	Info(playerid,"Pozycja miejsca za≥adunku zmieniona!");
				 	ZapiszLadunek(nr);
				 	return 1;
				}//koniec przypadku
				case 5:
		 	    {
		 			text=strrest(cmdtext,idx);
					if(isnull(text))
					{
						Info(playerid,"Uøyj: /ladunek 2 (id) 5 (nazwa miejsca roz≥adunku)");
				 		return 1;
				 	}
				 	if(strlen(text)<3||strlen(text)>30)
					{
                        Info(playerid,"Nie poprawna d≥ugoúÊ nazwy!\nOd 3 do 30 liter!");
						return 1;
					}
				 	strmid(LadunekInfo[nr][lDostarczenie], text, 0, strlen(text), 64);
				 	Info(playerid,"Nazwa miejsca roz≥adunku zmieniona!");
				 	ZapiszLadunek(nr);
				 	return 1;
				}//koniec przypadku
				case 6:
		 	    {
		 			if(GetPlayerInterior(playerid)!=0)
		 			{
		 			    Info(playerid,"Nie moøe byÊ to w interiorze!");
		 			    return 1;
		 			}
				 	GetPlayerPos(playerid,LadunekInfo[nr][lPos2X],LadunekInfo[nr][lPos2Y],LadunekInfo[nr][lPos2Z]);
				 	Info(playerid,"Pozycja miejsca roz≥adunku zmieniona!");
				 	ZapiszLadunek(nr);
				 	return 1;
				}//koniec przypadku
			}
			return 1;
		}
		else if(numer==3)
		{
		    SendClientMessage(playerid,KOLOR_ZOLTY,"Istniejπce oferty transportowe:");
		    for(new nr = 0; nr < LIMIT_LADUNKOW; nr++)
			{
				if(LadunekInfo[nr][lAktywny]==1)
	 			{
		    		format(dstring, sizeof(dstring),"£adunek [%d]: %s z %s do %s za %f/kg",nr,LadunekInfo[nr][lTowar],LadunekInfo[nr][lZaladunek],LadunekInfo[nr][lDostarczenie],LadunekInfo[nr][lTowarKoszt]);
		    		SendClientMessage(playerid,KOLOR_BIALY,dstring);
				}
			}
			return 1;
		}
		else if(numer==4)
		{
			tmp = strtok(cmdtext, idx);
			if(isnull(tmp))
			{
				Info(playerid,"Uøyj: /ladunek 4 (id)");
	 			return 1;
		 	}
		 	new nr=strval(tmp);
		 	if(LadunekInfo[nr][lAktywny]==0)
 			{
 			    Info(playerid,"Taka oferta transportowa nie istnieje!");
 			    return 1;
 			}
 			LadunekInfo[nr][lAktywny]=0;
 			ZapiszLadunek(nr);
 			Info(playerid,"Oferta transportowa usuniÍta");
			return 1;
		}
		return 1;
	}

	CMD:wycisz(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /wycisz (ID) (czas) (powÛd)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new czas = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz wsadziÊ sam siebie!"); return 1; }
	 	if(czas<2||czas>=20){ Info(playerid,"Od 2 do 20 minut!"); return 1; }
		if(IsPlayerConnected(playa)&&Zalogowany[playa]==true)
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz ukaraÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /wycisz (ID) (czas) (powÛd)");
				return 1;
			}
			KillTimer(MuteTimer[playa]);
			MuteTimer[playa]=SetTimerEx("Odcisz",60000*czas,false,"i",playa);
			PlayerInfo[playa][pWyciszony]=czas;
			ZapiszKonto(playa);
		    format(dstring, sizeof(dstring),"Zosta≥eú wyciszony przez %s(%d) na %d minut\nPowÛd: %s",Nick(playerid),playerid,PlayerInfo[playa][pJail],text);
		    Info(playa,dstring);
		    GInfo(playa,"~r~wyciszony",1);
		    format(dstring, sizeof(dstring),"~r~(%d)%s zostal wyciszony na %d min~n~~y~przez: (%d)%s~n~~w~Za: %s",playa,Nick(playa),czas,playerid,Nick(playerid),text);
		    NapisText(dstring);
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	forward Odcisz(playerid);
	public Odcisz(playerid)
	{
	    if(PlayerInfo[playerid][pWyciszony]>=1)
	    {
		    PlayerInfo[playerid][pWyciszony]=0;
			GInfo(playerid,"~w~odciszony",1);
		}
	    return 1;
	}

	CMD:aj(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /aj (ID) (czas) (powÛd)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	tmp = strtok(cmdtext, idx);
	 	new czas = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz wsadziÊ sam siebie!"); return 1; }
	 	if(czas<3||czas>=180){ Info(playerid,"Od 3 do 180 minut!"); return 1; }
		if(IsPlayerConnected(playa)&&Zalogowany[playa]==true)
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz ukaraÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /aj (ID) (czas) (powÛd)");
				return 1;
			}
			SetPlayerPos(playa,264.9535,77.5068,1001.0391);
		    SetPlayerInterior(playa,6);
		    SetPlayerVirtualWorld(playa,playa);
		    SetPlayerWorldBounds(playa,268.5071,261.3936,81.6285,71.8745);
		    dUstawHP(playa,100);
			PlayerInfo[playa][pJail]=czas;
			ZapiszKonto(playa);
		    format(dstring, sizeof(dstring),"Zosta≥eú uwiÍziony w admin jailu przez %s(%d) na %d minut\nPowÛd: %s",Nick(playerid),playerid,PlayerInfo[playa][pJail],text);
		    Info(playa,dstring);
		    GInfo(playa,"~r~admin jail",1);
		    format(dstring, sizeof(dstring),"~r~(%d)%s zostal uwieziony na %d min~n~~y~przez: (%d)%s~n~~w~Za: %s",playa,Nick(playa),czas,playerid,Nick(playerid),text);
		    NapisText(dstring);
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	CMD:ban(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /ban (ID) (powÛd)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz zbanowaÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz zbanowaÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /ban (ID) (powÛd)");
				return 1;
			}
		    format(dstring, sizeof(dstring),"Zosta≥eú zbanowany przez %s(%d) za: %s",Nick(playerid),playerid,text);
		    Info(playa,dstring);
		    format(dstring, sizeof(dstring),"~r~(%d)%s zostal zbanowany~n~~y~przez: (%d)%s~n~~w~Za: %s",playa,Nick(playa),playerid,Nick(playerid),text);
	    	NapisText(dstring);
	    	format(dstring, sizeof(dstring),"%s zostal zbanowany przez: %s Za: %s",Nick(playa),Nick(playerid),text);
	    	print(dstring);
		    dBanEx(playa,text);
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	CMD:blok(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /blok (ID) (powÛd)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz zablokowaÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa)&&Zalogowany[playa]==true)
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz zablokowaÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /blok (ID) (powÛd)");
				return 1;
			}
		    format(dstring, sizeof(dstring),"Zosta≥eú zablokowany przez %s(%d) za: %s",Nick(playerid),playerid,text);
		    Info(playa,dstring);
		    format(dstring, sizeof(dstring),"~r~Konto (%d)%s zostalo zablokowane~n~~y~przez: (%d)%s~n~~w~Za: %s",playa,Nick(playa),playerid,Nick(playerid),text);
	    	NapisText(dstring);
		    PlayerInfo[playa][pKonto]=2;
		    dKick(playa);
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	CMD:warn(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /warn (ID) (powÛd)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz zwarnowaÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa)&&Zalogowany[playa]==true)
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz zwarnowaÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /warn (ID) (powÛd)");
				return 1;
			}
			PlayerInfo[playa][pWarny]++;
            SerwerInfo[sWarn]++;
			if(PlayerInfo[playa][pWarny]>=4)
			{
			    format(dstring, sizeof(dstring),"Otrzyma≥eú warna(4/4) i jednoczeúnie bana od %s(%d)\nPowÛd: %s",Nick(playerid),playerid,text);
			    Info(playa,dstring);
			    format(dstring, sizeof(dstring),"~r~(%d)%s zostal zbanowany (4/4 warny)~n~~y~przez: (%d)%s~n~~w~Za: %s",playa,Nick(playa),playerid,Nick(playerid),text);
		    	NapisText(dstring);
			    dBanEx(playa,"Otrzymanie 4 warnÛw");
			    SerwerInfo[sBan]++;
		    }
			else
			{
			    format(dstring, sizeof(dstring),"Otrzyma≥eú warna(%d/4) od %s(%d)\nPowÛd: %s",PlayerInfo[playa][pWarny],Nick(playerid),playerid,text);
			    Info(playa,dstring);
			    format(dstring, sizeof(dstring),"~r~(%d)%s zostal ostrzezony (%d/4)~n~~y~przez: (%d)%s~n~~w~Za: %s",playa,Nick(playa),PlayerInfo[playa][pWarny],playerid,Nick(playerid),text);
		    	NapisText(dstring);
			    dKick(playa);
			}
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	CMD:kick(playerid, cmdtext[])
	{
	    if(!ToAdminLevel(playerid,1)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /kick (ID) (powÛd)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz wrzuciÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    if(PlayerInfo[playa][pAdmin]>PlayerInfo[playerid][pAdmin])
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz wyrzuciÊ admina z wiÍkszπ rangπ od twojej!");
				return 1;
		    }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /kick (ID) (powÛd)");
				return 1;
			}
		    format(dstring, sizeof(dstring),"Zosta≥eú wyrzucony przez %s(%d) za: %s",Nick(playerid),playerid,text);
		    Info(playa,dstring);
		    format(dstring, sizeof(dstring),"~r~(%d)%s zostal wyrzucony~n~~y~przez: (%d)%s~n~~w~Za: %s",playa,Nick(playa),playerid,Nick(playerid),text);
		    NapisText(dstring);
		    dKick(playa);
            SerwerInfo[sKick]++;
		    format(dstring, sizeof(dstring),"%s zostal wykopany przez przez: %s Za: %s",Nick(playa),Nick(playerid),text);
	    	print(dstring);
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	CMD:podglad(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,1)) return 1;
		if(Podglad==true)
		{
		    Podglad=false;
		    Info(playerid,"Podglπd CB radia i pw wy≥πczony!");
		}
		else
		{
		    Podglad=true;
		    Info(playerid,"Podglπd CB radia i pw w≥πczony!");
		}
		return 1;
	}

	CMD:lista(playerid, cmdtext[])
	{
		if(!ToAdminLevel(playerid,1)) return 1;
		if(Lista[playerid]==true)
		{
		    Lista[playerid]=false;
		    Info(playerid,"Teraz nie bÍdziesz wyúwietlany na liúcie adminÛw!");
		}
		else
		{
		    Lista[playerid]=true;
		    Info(playerid,"Teraz bÍdziesz wyúwietlany na liúcie adminÛw!");
		}
		return 1;
	}

	CMD:tankuj(playerid, cmdtext[])
	{
	    if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
		{
		    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
		    return 1;
		}
    	if(!NaStacjiPaliw(playerid))
		{
			Info(playerid, ""C_CZERWONY"Nie jesteú na stacji benzynowej!");
			return 1;
		}
		new v=GetPlayerVehicleID(playerid),potrzebne=vPaliwoMax[v]-vPaliwo[v];
		if(potrzebne<1)
		{
			Info(playerid, ""C_CZERWONY"TwÛj pojazd nie potrzebuje paliwa!");
			return 1;
		}
		new id;
		id=StacjaPaliw(playerid);
		if(id==99)
		{
		    Info(playerid, ""C_CZERWONY"Nie jesteú na stacji benzynowej!");
			return 1;
		}
		format(dstring, sizeof(dstring), ""C_ZOLTY"Witaj na stacji benzynowej!\n"C_ZIELONY"Do pe≥nego baku brakuje Tobie: %d litr/Ûw.\n1 litr kosztuje %.02f$\n"C_ZOLTY"Ile litrÛw chcesz zatankowaÊ?",potrzebne,StacjaInfo[id][sCena]);
		ShowPlayerDialog(playerid,5,DIALOG_STYLE_INPUT,""C_POMARANCZOWY"Tankowanie",dstring,"Tankuj","Zamknij");
		return 1;
	}

    CMD:pojazd(playerid, cmdtext[])
	{
		if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
		{
		    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
		    return 1;
		}
		ShowPlayerDialog(playerid,4,DIALOG_STYLE_LIST,""C_ZOLTY"Zarzπdzanie pojazdem",""C_ZIELONY"W≥πcz"C_BIALY" / "C_CZERWONY"Wy≥πcz "C_ZOLTY"silnik\n"C_ZIELONY"W≥πcz"C_BIALY" / "C_CZERWONY"Wy≥πcz "C_ZOLTY"lampy\n"C_ZIELONY"OtwÛrz"C_BIALY" / "C_CZERWONY"Zamknij "C_ZOLTY"maskÍ\n"C_ZIELONY"OtwÛrz"C_BIALY" / "C_CZERWONY"Zamknij "C_ZOLTY"bagaønik\n"C_ZIELONY"OtwÛrz"C_BIALY"  / "C_CZERWONY"Zamknij "C_ZOLTY"drzwi\n"C_ZOLTY"CB-Radio","Wybierz","Zamknij");
		return 1;
	}

	COMMAND:p(playerid,cmdtext[])
	{
	  return cmd_pojazd(playerid,cmdtext);
	}

	CMD:cb(playerid, cmdtext[])
	{
	    if(PlayerInfo[playerid][pWyciszony]>=1)
		{
		    Info(playerid,""C_CZERWONY"Jesteú wyciszony!");
			return 1;
		}
		if(!IsPlayerInAnyVehicle(playerid))
		{
		    Info(playerid,""C_CZERWONY"Nie jesteú w øadnym pojeüdzie!");
		    return 1;
		}
		if(ToRadiowoz(GetPlayerVehicleID(playerid)))
		{
			Info(playerid,""C_CZERWONY"Ten pojazd nie ma CB-Radia!");
		    return 1;
		}
		new kanal=vCB[GetPlayerVehicleID(playerid)];
		if(kanal==0)
		{
		    Info(playerid,""C_CZERWONY"CB-Radio w tym pojeüdzie jest wy≥πczone, musisz je najpierw uruchomiÊ!");
		    return 1;
		}
		new text[80],idx;
		text=strrest(cmdtext,idx);
		if(isnull(text))
		{
			Info(playerid, "Uøyj: /cb (tekst)");
			return 1;
		}
		if(Bluzg(text))
		{
		    format(dstring,sizeof(dstring),"AC: "C_BIALY"(%d) %s zosta≥ wyciszony (5 min), za: "C_CZERWONY"wulgaryzmy",playerid,Nick(playerid));
			SendClientMessageToAll(KOLOR_ROZOWY,dstring);
		    KillTimer(MuteTimer[playerid]);
			MuteTimer[playerid]=SetTimerEx("Odcisz",60000*5,false,"i",playerid);
			PlayerInfo[playerid][pWyciszony]=5;
			ZapiszKonto(playerid);
			return 1;
		}
		UpperToLower(text);
		new Float:Pos[3];
		GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
		foreach(Player,i)
		{
		    if(IsPlayerInAnyVehicle(i)&&vCB[GetPlayerVehicleID(i)]==kanal)
		    {
				format(dstring, sizeof(dstring), "[CB:"C_ZIELONY"%d"C_ZOLTY"]: "C_TURKUSOWY"%s",kanal,text);
				SendClientMessage(i,KOLOR_ZOLTY,dstring);
			}
			if(Podglad==true&&PlayerInfo[i][pAdmin]>=1)
			{
			    format(dstring, sizeof(dstring), "[CB:%d][ID:%d]%s: "C_TURKUSOWY"%s",kanal,playerid,Nick(playerid),text);
				SendClientMessage(i,KOLOR_ROZOWY,dstring);
			}
		}
		return 1;
	}

	CMD:konto(playerid, cmdtext[])
	{
        ShowPlayerDialog(playerid,9,DIALOG_STYLE_LIST,""C_POMARANCZOWY"Zarzπdzanie kontem",""C_ZOLTY"Statystyki\n"C_ZOLTY"ZmieÒ has≥o\n"C_ZOLTY"Blokada PW","Wybierz","Zamknij");
	    return 1;
	}

	COMMAND:pm(playerid,cmdtext[])
	{
	  return cmd_w(playerid,cmdtext);
	}

	CMD:w(playerid, cmdtext[])
	{
	    if(PlayerInfo[playerid][pWyciszony]>=1)
		{
		    Info(playerid,""C_CZERWONY"Jesteú wyciszony!");
			return 1;
		}
	    new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /pm (id) (tekst)");
			return 1;
 		}
	 	new playa = strval(tmp);
		if(IsPlayerConnected(playa)&&Zalogowany[playa]==true)
		{
 			if(playa==playerid){ Info(playerid,""C_CZERWONY"Nie moøesz pisaÊ sam do siebie!"); return 1; }
		 	if(BlokadaPW[playa]==true){ Info(playerid,""C_CZERWONY"Ten gracz zablokowa≥ prywatne wiadomoúci!"); return 1; }
		 	if(BlokadaPW[playerid]==true){ Info(playerid,""C_CZERWONY"Zablokowa≥eú prywatne wiadomoúci!"); return 1; }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /pm (id) (tekst)");
				return 1;
			}
			if(Bluzg(text))
			{
			    format(dstring,sizeof(dstring),"AC: "C_BIALY"(%d) %s zosta≥ wyciszony (5 min), za: "C_CZERWONY"wulgaryzmy",playerid,Nick(playerid));
				SendClientMessageToAll(KOLOR_ROZOWY,dstring);
			    KillTimer(MuteTimer[playerid]);
				MuteTimer[playerid]=SetTimerEx("Odcisz",60000*5,false,"i",playerid);
				PlayerInfo[playerid][pWyciszony]=5;
				ZapiszKonto(playerid);
				return 1;
			}
			UpperToLower(text);
			format(dstring, sizeof(dstring), "[PM]>>"C_ZIELONY"[%d]%s: "C_BEZOWY"%s",playa,Nick(playa),text);
			SendClientMessage(playerid,KOLOR_BEZOWY, dstring);
			format(dstring, sizeof(dstring), "[PM]<<"C_ZIELONY"[%d]%s: "C_BEZOWY"%s",playerid,Nick(playerid),text);
			SendClientMessage(playa,KOLOR_BEZOWY, dstring);
			format(dstring, sizeof(dstring), "[PM] %s do %s - Wiadomosc: %s", Nick(playerid), Nick(playa), text);
			print(dstring);
			if(Podglad==true)
			{
				foreach(Player,i)
				{
				    if(PlayerInfo[i][pAdmin]>=1)
				    {
			    		format(dstring, sizeof(dstring), "[PW] [%d]%s do [%d][%s]: "C_BEZOWY"%s",playerid,Nick(playerid),playa,Nick(playa),text);
						SendClientMessage(i,KOLOR_ROZOWY, dstring);
					}
				}
			}
		}
		else
		{
			Info(playerid,"Poda≥eú nie poprawne ID!");
		}
		return 1;
	}

	CMD:regulamin(playerid, cmdtext[])
	{
	    new s[300],ss[300],str[600];
	    format(s, sizeof(s), ""C_ZOLTY"1. Jest to polski serwer, wiÍc uøywamy wy≥πcznie polskiego jÍzyka.\n2. Zabrania siÍ jakichkolwiek bluzgÛw, zachowaj kulturÍ osobistπ.\n3. Zabrania siÍ zak≥Ûcania pozosta≥ym osobom gry.\n4. Zabrania siÍ spamowania lub pisania bez takiej potrzeby.");
	    format(ss, sizeof(ss), ""C_ZOLTY"5. Zabrania siÍ wykorzystywania cheatÛw lub jakichkolwiek b≥ÍdÛw skryptu.\n6. Gdy jesteú úwiadkiem przewinieÒ, Twoim obowiπzkiem jest poinformowanie o tym administracji.\n7. Za z≥amanie regulaminu moøna otrzymaÊ kare, w najgorszym wypadku bana.");
 	   	format(str, sizeof(str), "%s\n%s",s,ss);
 	    Info(playerid,str);
		return 1;
	}

	CMD:autorzy(playerid, cmdtext[])
	{
		Info(playerid,""C_POMARANCZOWY"Hard-Truck\n"C_ZOLTY"Mape stworzy≥: "C_CZERWONY"Inferno (GG: 34773974)\n"C_ZOLTY"Obiekty stworzyli: "C_CZERWONY"ZiomeQ, Reggaenerator, PogromcaPL i NolLajf\n "C_ZIELONY"DziÍkujemy za uwagÍ :-)\nMi≥ej gry!");
		return 1;
	}

	CMD:raport(playerid, cmdtext[])
	{
	    if(PlayerInfo[playerid][pWyciszony]>=1)
		{
		    Info(playerid,""C_CZERWONY"Jesteú wyciszony!");
			return 1;
		}
		new text[80],idx;
		text=strrest(cmdtext,idx);
		if(isnull(text))
		{
			Info(playerid, "Uøyj: /raport (tekst)");
			return 1;
		}
		Info(playerid,""C_ZOLTY"Raport wys≥any!");
		UpperToLower(text);
		foreach(Player,i)
		{
		    if(PlayerInfo[i][pAdmin]>=1)
		    {
				format(dstring, sizeof(dstring), ""C_CZERWONY"[Raport:"C_ZIELONY"[%d]%s"C_CZERWONY"]: %s",playerid,Nick(playerid),text);
				SendClientMessage(i,KOLOR_CZERWONY,dstring);
			}
		}
		return 1;
	}

	CMD:premium(playerid, cmdtext[])
	{
		if(PlayerInfo[playerid][pPremium]<1)
		{
		    Info(playerid,""C_CZERWONY"Nie posiadasz konta premium!\n"C_ZOLTY"Informacje na temat konta premium moøna znaleüÊ na stronie: "C_ZIELONY"www.Hard-Truck.pl");
		    return 1;
		}
		return 1;
	}

	CMD:admini(playerid, cmdtext[])
	{
		new admini=0;
		SendClientMessage(playerid,KOLOR_CZERWONY,"Administracja online:");
		foreach(Player,i)
		{
		    if(PlayerInfo[i][pAdmin]==1&&Lista[i]==true)
		    {
		        admini++;
				format(dstring, sizeof(dstring), "Junior Admin: "C_BIALY"[%d] %s",i,Nick(i));
				SendClientMessage(playerid,KOLOR_BEZOWY,dstring);
			}
			else if(PlayerInfo[i][pAdmin]==2&&Lista[i]==true)
		    {
		        admini++;
				format(dstring, sizeof(dstring), "Administrator: "C_BIALY"[%d] %s",i,Nick(i));
				SendClientMessage(playerid,KOLOR_ZOLTY,dstring);
			}
			else if(PlayerInfo[i][pAdmin]==3&&Lista[i]==true)
		    {
		        admini++;
				format(dstring, sizeof(dstring), "Head Administrator: "C_BIALY"[%d] %s",i,Nick(i));
				SendClientMessage(playerid,KOLOR_CZERWONY,dstring);
			}
		}
		if(admini==0){ SendClientMessage(playerid,KOLOR_ZOLTY,"* Brak administratorÛw online!"); }
		return 1;
	}

	CMD:dawaj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"POLICE","CopTraf_Come",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:stop(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"POLICE","CopTraf_Stop",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:smiech(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"RAPPING","Laugh_01",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:daj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
		}
	    ApplyAnimation(playerid,"DEALER","shop_pay",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:ratuj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"MEDIC","CPR",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:poloz(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"CARRY","putdwn",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:podnies(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"CARRY","liftup",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:caluj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /caluj (nr)\nOd 1 do 2");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"KISSING","Grlfrd_Kiss_02",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"KISSING","Playa_Kiss_01",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:kibic(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /kibic (nr)\nOd 1 do 2");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"ON_LOOKERS","shout_02",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"STRIP","PUN_HOLLER",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:yeah(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /yeah (nr)\nOd 1 do 2");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"CASINO","manwind",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"CASINO","Slot_win_out",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:opieraj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"GANGS","leanIDLE",4.1,0,0,0,1,0);
	    return 1;
	}

	CMD:siema(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /siema (nr)\nOd 1 do 3");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"GANGS","hndshkaa",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"GANGS","hndshkba",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"GANGS","hndshkfa",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:nie(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"FOOD","EAT_Vomit_SK",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:tak(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"GANGS","DEALER_DEAL",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:turlaj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"MD_CHASE","MD_HANG_Lnd_Roll",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:wymiotuj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"FOOD","EAT_Vomit_P",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:silownia(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /silownia (nr)\n1 (k≥adziesz siÍ na maszynie do ÊwiczeÒ)\n2 (bierzesz sztangÍ w gÛrÍ)\n3 (bierzesz sztangÍ w dÛ≥)\n4 (schodzisz z maszyny do ÊwiczeÒ)");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"benchpress","gym_bp_geton",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"benchpress","gym_bp_up_A",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"benchpress","gym_bp_down",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
        else if(pkt==4)
	 	{
	 	    ApplyAnimation(playerid,"benchpress","gym_bp_getoff",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:lez(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /lez (nr)\nOd 1 do 3");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"BEACH","bather",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"BEACH","ParkSit_W_loop",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"BEACH","SitnWait_loop_W",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:pij(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"BAR","dnk_stndF_loop",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:jedz(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:bar(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /bar (nr)\n1 (bierzesz napÛj z lady)\n2 (s≥uchasz zamÛwienia)\n3 (wyciπgasz coú spod lady)\n4 (podajesz coú)\n5 (nalewasz coú z maszyny)\n6 (sk≥adasz zamÛwienie)\n7 (opierasz siÍ przy ladzie[1])\n8 (opierasz siÍ przy ladzie[2])");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"BAR","Barcustom_get",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"BAR","Barcustom_order",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"BAR","Barserve_bottle",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==4)
	 	{
	 	    ApplyAnimation(playerid,"BAR","Barserve_give",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==5)
	 	{
	 	    ApplyAnimation(playerid,"BAR","Barserve_glass",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==6)
	 	{
	 	    ApplyAnimation(playerid,"BAR","Barserve_order",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==7)
	 	{
	 	    ApplyAnimation(playerid,"BAR","Barserve_in",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==8)
	 	{
	 	    ApplyAnimation(playerid,"BAR","BARman_idle",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:spij(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"CRACK","crckidle2",4.1,0,0,0,1,0);
	    return 1;
	}

	CMD:ranny(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /ranny (nr)\nOd 1 do 2");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"CRACK","crckidle1",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"SWAT","gnstwall_injurd",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:mysl(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"COP_AMBIENT","Coplook_think",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:szafka(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /szafka (nr)\n1 (otwierasz szafke)\n2 (znajdujesz dokument w szafce)\n3 (zamykasz szafke)");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_in",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_nod",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_out",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:tancz(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /tancz (nr)\nOd 1 do 4");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    SendClientMessage(playerid,KOLOR_ZOLTY,"Klawisz 'enter' zatrzyma animacjÍ");
	 	    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    SendClientMessage(playerid,KOLOR_ZOLTY,"Klawisz 'enter' zatrzyma animacjÍ");
	 	    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    SendClientMessage(playerid,KOLOR_ZOLTY,"Klawisz 'enter' zatrzyma animacjÍ");
	 	    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
	 	    return 1;
	 	}
	 	else if(pkt==4)
	 	{
	 	    SendClientMessage(playerid,KOLOR_ZOLTY,"Klawisz 'enter' zatrzyma animacjÍ");
	 	    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:lawka(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /lawka (nr)\n1 (siadasz na ≥awce)\n2 (wstajesz z ≥awki)");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"Attractors","Stepsit_in",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"Attractors","Stepsit_out",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:krzeslo(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /krzeslo (nr)\n1 (siadasz na krzes≥o)\n2 (wstajesz z krzes≥a)\n3 (siadasz przy stoliku - prawa)\n4 (siadasz przy stoliku - lewa)\n5 (wstajesz od stolika - lewa)\n6 (wstajesz od stolika - prawa)\n7 (wyskakujesz z krzes≥a)");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"PED","SEAT_down",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"PED","SEAT_up",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"FOOD","FF_Sit_In_L",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==4)
	 	{
	 	    ApplyAnimation(playerid,"FOOD","FF_Sit_In_R",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==5)
	 	{
	 	    ApplyAnimation(playerid,"FOOD","FF_Sit_Out_L_180",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==6)
	 	{
	 	    ApplyAnimation(playerid,"FOOD","FF_Sit_Out_R_180",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==7)
	 	{
	 	    ApplyAnimation(playerid,"CRIB","PED_Console_Win",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:zmeczony(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","IDLE_tired",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:salutuj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"ON_LOOKERS","panic_in",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:taxi(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","IDLE_taxi",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:bacznosc(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","Idlestance_fat",4.1,0,0,0,1,0);
	    return 1;
	}

	CMD:odejdz(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","handscower",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:tam(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"ON_LOOKERS","point_loop",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:poddajsie(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","handsup",4.1,0,0,0,1,0);
	    return 1;
	}

	CMD:fuckyou(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","fucku",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:sikaj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    SetPlayerSpecialAction(playerid, 68);
	    return 1;
	}

	CMD:tupnij(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","FALL_land",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:odskocz(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","EV_step",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:machaj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /machaj (nr)\n1 (machasz[1])\n2 (machasz[2])\n3 (machasz kucajπc)");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"PED","endchat_03",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"KISSING","gfwave2",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"CAMERA","camcrch_cmon",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:rece(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /rece (nr)\n1 (wystawiasz rÍce do przodu)\n2 (trzymasz rÍkÍ na biodrze)\n3 (zak≥adasz rÍce)\n4 (myjesz rÍce)\n5 (rozstawiasz szeroko rÍce)\n6 (stajesz na rÍkach)");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"PED","DRIVE_BOAT",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"PED","woman_idlestance",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"COP_AMBIENT","Coplook_in",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==4)
	 	{
	 	    ApplyAnimation(playerid,"INT_HOUSE","wash_up",4.1,0,0,0,0,0);
	 	    return 1;
	 	}
	 	else if(pkt==5)
	 	{
	 	    ApplyAnimation(playerid,"BSKTBALL","BBALL_def_loop",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==6)
	 	{
	 	    ApplyAnimation(playerid,"DAM_JUMP","DAM_Dive_Loop",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	CMD:kryj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","cower",4.1,0,0,0,1,0);
	    return 1;
	}

	CMD:raczkuj(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
	    ApplyAnimation(playerid,"PED","CAR_crawloutRHS",4.1,0,0,0,0,0);
	    return 1;
	}

	CMD:gleba(playerid, cmdtext[])
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        Info(playerid,""C_CZERWONY"Nie moøesz uøywaÊ animacji bÍdπc w pojeüdzie!");
	        return 1;
	    }
		new tmp[64],idx;
	    tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /gleba (nr)\n1 (wywalasz siÍ na ziemie)\n2 (k≥adziesz siÍ na plecach)\n3 (k≥adziesz siÍ twarzπ do ziemi)\n4 (padasz na plecy)\n5 (padasz na twarz)\n6 (padasz na ziemie trzymajπc siÍ za brzuch)\n7 (leøysz naÊpany[1])\n8 (leøysz naÊpany[2])\n9 (leøysz naÊpany[3])\n10 (leøysz naÊpany[4])");
			return 1;
	 	}
	 	new pkt=strval(tmp);
	 	if(pkt==1)
	 	{
	 	    ApplyAnimation(playerid,"PED","BIKE_fall_off",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==2)
	 	{
	 	    ApplyAnimation(playerid,"PED","FLOOR_hit",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==3)
	 	{
	 	    ApplyAnimation(playerid,"PED","FLOOR_hit_f",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==4)
	 	{
	 	    ApplyAnimation(playerid,"PED","KO_shot_face",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==5)
	 	{
	 	    ApplyAnimation(playerid,"PED","KO_shot_front",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==6)
	 	{
	 	    ApplyAnimation(playerid,"PED","KO_shot_stom",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==7)
	 	{
	 	    ApplyAnimation(playerid,"CRACK","crckdeth1",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==8)
	 	{
	 	    ApplyAnimation(playerid,"CRACK","crckdeth2",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==9)
	 	{
	 	    ApplyAnimation(playerid,"CRACK","crckdeth3",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else if(pkt==10)
	 	{
	 	    ApplyAnimation(playerid,"CRACK","crckdeth4",4.1,0,0,0,1,0);
	 	    return 1;
	 	}
	 	else
	 	{
	 	    Info(playerid,"Nie poprawny numer!");
	 	}
	 	return 1;
	}

	forward UstalLadownosc(v);
	public UstalLadownosc(v)
	{
		new m=GetVehicleModel(v);
	    if(m==435)//wieksza przyczepka
	    {
	        vLadownosc[v]=1200;
		    vLadownoscMax[v]=1800;
		    return 1;
	    }
	    else if(m==591)//ta mniejsza troche
	    {
	        vLadownosc[v]=1000;
		    vLadownoscMax[v]=1500;
		    return 1;
	    }
	    else if(m==413||m==482||m==440)//busy
	    {
	        vLadownosc[v]=200;
		    vLadownoscMax[v]=400;
		    return 1;
	    }
	    else if(m==414||m==456||m==499)//te wieksze troche busy
	    {
	        vLadownosc[v]=500;
		    vLadownoscMax[v]=750;
		    return 1;
	    }
	    else if(m==498||m==609)//te duze busy
	    {
	        vLadownosc[v]=700;
		    vLadownoscMax[v]=1050;
		    return 1;
	    }
	    else
	    {
	        vLadownosc[v]=0;
		    vLadownoscMax[v]=0;
	    }
		return 1;
	}

	forward UstalPaliwo(v);
	public UstalPaliwo(v)
	{
		if(ToRower(v)||ToPrzyczepa(v)||ToRC(v))
		{
		    vPaliwo[v]=0;
		    vPaliwoMax[v]=0;
		    return 1;
		}
		if(ToAutobus(v))
		{
		    vPaliwo[v]=500;
		    vPaliwoMax[v]=500;
		    return 1;
		}
		if(ToBus(v))
		{
		    vPaliwo[v]=80;
		    vPaliwoMax[v]=80;
		    return 1;
		}
		if(ToCiezarowka(v))
		{
		    vPaliwo[v]=350;
		    vPaliwoMax[v]=350;
		    return 1;
		}
		if(ToHelikopter(v))
		{
		    vPaliwo[v]=300;
		    vPaliwoMax[v]=300;
		    return 1;
		}
		if(ToSamolot(v))
		{
		    vPaliwo[v]=500;
		    vPaliwoMax[v]=500;
		    return 1;
		}
		if(ToLodz(v))
		{
		    vPaliwo[v]=150;
		    vPaliwoMax[v]=150;
		    return 1;
		}
		if(ToMotor(v))
		{
		    vPaliwo[v]=10;
		    vPaliwoMax[v]=10;
		    return 1;
		}
		if(ToOsobowy(v))
		{
		    vPaliwo[v]=50;
		    vPaliwoMax[v]=50;
		    return 1;
		}
		return 1;
	}

	forward ToOsobowy(id);
	public ToOsobowy(id)
	{
		new m=GetVehicleModel(id);
		if(!ToAutobus(m)
		&&!ToBus(m)
		&&!ToCiezarowka(m)
		&&!ToHelikopter(m)
		&&!ToSamolot(m)
		&&!ToLodz(m)
		&&!ToMotor(m)
		&&!ToRC(m)
		&&!ToPrzyczepa(m)
		&&!ToRower(m))
		{
			return 1;
		}
		return 0;
	}

	forward ToRower(id);
	public ToRower(id)
	{
		new m=GetVehicleModel(id);
		if(m==481//bmx
		||m==509//bike
		||m==510)//mountain bike
		{
			return 1;
		}
		return 0;
	}

	forward ToPrzyczepa(id);
	public ToPrzyczepa(id)
	{
		new m=GetVehicleModel(id);
		if(m==435//
		||m==450//
		||m==569//
		||m==570//
		||m==584//
		||m==590//
		||m==591//
		||m==606//
		||m==607//
		||m==608//
		||m==610//
		||m==611)//
		{
			return 1;
		}
		return 0;
	}

	forward ToRC(id);
	public ToRC(id)
	{
		new m=GetVehicleModel(id);
		if(m==441//rcbandit
		||m==594//rccam
		||m==564//rctiger
		||m==465//rcrider
		||m==501//rcgobiln
		||m==464)//rcbarron
		{
			return 1;
		}
		return 0;
	}

	forward ToMotor(id);
	public ToMotor(id)
	{
		new m=GetVehicleModel(id);
		if(m==448//pizzaboy
		||m==461//pcj600
		||m==462//faggio
		||m==463//freeway
		||m==468//sanchez
		||m==521//fcr900
		||m==522//nrg500
		||m==523//copbike
		||m==581//bf400
		||m==586)//wayfarer
		{
			return 1;
		}
		return 0;
	}

	forward ToLodz(id);
	public ToLodz(id)
	{
		new m=GetVehicleModel(id);
		if(m==430//predator
		||m==446//squalo
		||m==452//speeder
		||m==453//refeer
		||m==454//tropic
		||m==472//coast guard
		||m==473//dinghy
		||m==484//marquis
		||m==493//jetmax
		||m==595)//launch
		{
			return 1;
		}
		return 0;
	}

	forward ToSamolot(id);
	public ToSamolot(id)
	{
		new m=GetVehicleModel(id);
		if(m==460//skimmer
		||m==476//rustler
		||m==511//beagle
		||m==512//cropdust
		||m==513//stuntplane
		||m==519//shmal
		||m==520//hydra
		||m==553//nevada
		||m==577//at400
		||m==592//andromeda
		||m==593)//dodo
		{
			return 1;
		}
		return 0;
	}

	forward ToHelikopter(id);
	public ToHelikopter(id)
	{
		new m=GetVehicleModel(id);
		if(m==417//leviathan
		||m==425//hunter
		||m==447//seasparrow
		||m==469//sparrow
		||m==487//maverick
		||m==488//san news maverick
		||m==497//police maverick
		||m==548//cargojob
		||m==563)//raindanc
		{
			return 1;
		}
		return 0;
	}

	forward ToCiezarowka(id);
	public ToCiezarowka(id)
	{
		new m=GetVehicleModel(id);
		if(m==403//linerunner
		||m==406//dumper
	    ||m==408//trash
	    ||m==433//baraccks
	    ||m==443//packer
	    ||m==455//flatbed
	    ||m==486//dozer
	    ||m==514//petro
	    ||m==515//roadtrain
	    ||m==524//cement truck
	    ||m==531//traktor
	    ||m==532//kombajn
	    ||m==573//duneride
	    ||m==578//ctf30
	    ||m==407//firetruck
	    ||m==544//firela
	    ||m==432//czolg rhino
	    ||m==601)//swatvan
		{
			return 1;
		}
		return 0;
	}

	forward ToAutobus(id);
	public ToAutobus(id)
	{
		new m=GetVehicleModel(id);
		if(m==431//bus
		||m==437)//coach
		{
			return 1;
		}
		return 0;
	}

	forward ToBus(id);
	public ToBus(id)
	{
		new m=GetVehicleModel(id);
		if(m==413//pony
		||m==414//mule
		||m==418//moonbeam
		||m==440//rumpo
		||m==456//yankee
		||m==482//burrito
		||m==483//camper
		||m==498//boxville
		||m==499//benson
		||m==508//yourney
		||m==559//topfun
		||m==416//ambulans
		||m==423//mr. whoopie
		||m==427//enforcer
		||m==428//securica
		||m==582//news van
		||m==588//hotdog
		||m==609)//boxburg
		{
			return 1;
		}
		return 0;
	}

	public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
	{

		if(dialogid == U2BDIAG && response)
		{
			switch(listitem)
			{
	  			case 0:
				{
				    PlayerU2B[playerid] = 1;
				    ShowPlayerDialog(playerid,U2BDIAG+1,DIALOG_STYLE_INPUT,WHOMADETHIS,"Podaj link jaki chcesz odtworzyÊ:","OdtwÛrz","Anuluj");
	   				return 1;
				}
				case 1:
				{
				    PlayerU2B[playerid] = 2;
				    ShowPlayerDialog(playerid,U2BDIAG+1,DIALOG_STYLE_INPUT,WHOMADETHIS,"Podaj link jaki chcesz komuú odtworzyÊ:","OdtwÛrz","Anuluj");
	   				return 1;
				}
				case 2:
				{
				    PlayerU2B[playerid] = 3;
				    ShowPlayerDialog(playerid,U2BDIAG+1,DIALOG_STYLE_INPUT,WHOMADETHIS,"Podaj link jaki chcesz odtworzyÊ w danej odleg≥oúci:","OdtwÛrz","Anuluj");
	   				return 1;
				}
				case 3:
				{
				    PlayerU2B[playerid] = 4;
				    ShowPlayerDialog(playerid,U2BDIAG+1,DIALOG_STYLE_INPUT,WHOMADETHIS,"Podaj link jaki chcesz wszytskim odtworzyÊ:","OdtwÛrz","Anuluj");
	   				return 1;
				}
			}
		}
		if(dialogid == U2BDIAG+1 && response)
		{
		    if(strlen(inputtext))
		    {
		        new result[128], videostr[128];
				strmid(result,inputtext,31,44,strlen(inputtext));
		        format(videostr,sizeof(videostr),"www.youtube-mp3.org/api/itemInfo/?video_id=%s",result);
		        strmid(PlayerU2BLink[playerid], result, 0, 32);
			    if (PlayerU2B[playerid] == 1)
			    {
			        PlayerU2B[playerid] = 11;
	        		HTTP(playerid,HTTP_GET,videostr,"","U2BInfo");
				}
				else if (PlayerU2B[playerid] == 2)
			    {
	                PlayerU2B[playerid] = 22;
					ShowPlayerDialog(playerid,U2BDIAG+2,DIALOG_STYLE_INPUT,WHOMADETHIS,"Wpisz ID gracza jakiemu chcesz odtwarzaÊ:","Play","Cancel");
					new string[128];
					format(string, sizeof(string), "%s", PlayerU2BLink[playerid]);
				}
		        else if (PlayerU2B[playerid] == 3)
			    {
			        PlayerU2B[playerid] = 33;
	    			ShowPlayerDialog(playerid,U2BDIAG+3,DIALOG_STYLE_INPUT,WHOMADETHIS,"Wpisz odleg≥oúÊ w metrach w jakiej bÍdzie odtwarzana nutka:","Play","Cancel");
				}
		        else if (PlayerU2B[playerid] == 4)
			    {
			        PlayerU2B[playerid] = 44;
	    			HTTP(playerid,HTTP_GET,videostr,"","U2BInfo");
				}
			}
			return 1;

		}
		if(dialogid == U2BDIAG+2 && response)
		{
	 		new gpid = strval(inputtext);
			new videostr[128];
			format(videostr,sizeof(videostr),"www.youtube-mp3.org/api/itemInfo/?video_id=%s",PlayerU2BLink[playerid]);
			HTTP(gpid,HTTP_GET,videostr,"","U2BInfo");
			return 1;

		}
		if(dialogid == U2BDIAG+3 && response)
		{
		    strmid(U2BRadius[playerid], inputtext, 0, 32);
		    new videostr[128];
	 		PlayerU2B[playerid] = 333;
			format(videostr,sizeof(videostr),"www.youtube-mp3.org/api/itemInfo/?video_id=%s",PlayerU2BLink[playerid]);
			HTTP(playerid,HTTP_GET,videostr,"","U2BInfo");
			return 1;

		}
		if(dialogid == GUI_MENUCAR)
		{
		    if(response)
		    {
		    	switch(listitem)
				{
					case 0:
					{
					    for(new nr = 0; nr < ILOSC_WOZOW; nr++)
						{
						    if(IsPlayerInVehicle(playerid, KupneWozy[nr]))
						    {
						        new Float: Pos[4];
						        GetVehiclePos(KupneWozy[nr], Pos[0], Pos[1], Pos[2]);
						        GetVehicleZAngle(KupneWozy[nr], Pos[3]);
	    			 	    	PrivateCar[nr][cX] = Pos[0];
				 	    		PrivateCar[nr][cY] = Pos[1];
				 	    		PrivateCar[nr][cZ] = Pos[2];
				 	    		PrivateCar[nr][cRX] = Pos[3];
				 	    		DestroyVehicle(KupneWozy[nr]);
	                            KupneWozy[nr] = AddStaticVehicleEx(PrivateCar[nr][cModel],PrivateCar[nr][cX],PrivateCar[nr][cY],PrivateCar[nr][cZ],PrivateCar[nr][cRX],PrivateCar[nr][cColor1],PrivateCar[nr][cColor2],PrivateCar[nr][cRespawn]);
				 	    		ZapiszWoz(nr);
				 	    		format(dstring, sizeof(dstring), ""C_BEZOWY"Ustawi≥eú spawn pojazdu na "C_BEZOWY"X: "C_ZIELONY"%f, "C_BEZOWY"Y: "C_ZIELONY"%f, "C_BEZOWY"Z: "C_ZIELONY"%f, "C_BEZOWY"RotX: "C_ZIELONY"%f", Pos[0], Pos[1], Pos[2], Pos[3]);
				 	    		SendClientMessage(playerid, KOLOR_BIALY, dstring);
							}
						}
					}
					case 1:
					{
					    for(new nr = 0; nr < ILOSC_WOZOW; nr++)
						{
						    if(IsPlayerInVehicle(playerid, KupneWozy[nr]))
						    {
						        SetVehicleToRespawn(KupneWozy[nr]);
								SendClientMessage(playerid, KOLOR_ZIELONY, "Zrespawnowano...");
							}
						}
					}
					case 2:
					{
						for(new nr = 0; nr < ILOSC_WOZOW; nr++)
						{
						    if(IsPlayerInVehicle(playerid, KupneWozy[nr]))
						    {
			                    if(PrivateCar[nr][cLock] == 1)
			                    {
			                        PrivateCar[nr][cLock]=0;
			                        SendClientMessage(playerid, KOLOR_ZIELONY, ""C_BEZOWY"Pojazd "C_ZIELONY"Otwarty");
			                        ZapiszWoz(nr);
								}
								else if(PrivateCar[nr][cLock] == 0)
								{
								    PrivateCar[nr][cLock]=1;
								    SendClientMessage(playerid, KOLOR_ZIELONY, ""C_BEZOWY"Pojazd "C_CZERWONY"ZamkniÍty");
								    ZapiszWoz(nr);
								}
							}
						}
					}
				}
			}
		}
	    if(dialogid == TARYFIK)
	    {
	        if(response)
	        {
	            new s[1000];
	        	strcat(s,"ß3.PrzestÍpstwa.\n");
				strcat(s,"\n");
				strcat(s,"1.Przemyt narkotykÛw: 500$-3000$ + 2 minuty wiezienia + 4 punkty karne(dotyczy takøe osÛb ktÛre roz≥adujπ\n");
				strcat(s,"podczas poúcigu.)\n");
				strcat(s,"2.Obraza funkcjonariusza:500$ + 2 minuty + 4 punkty karne\n");
				strcat(s,"3.Atak na funkcjonariusza policji/gracza : 500-1000$ + 5 punktÛw karnych\n");
				strcat(s,"4.ZabÛjstwo:1000-3000$ + 4 minuty + 5 punktÛw karnych\n");
				strcat(s,"5.Ucieczka z wiÍzienia/reconnect podczas aresztu:10.000$ (odstÍpuje siÍ od kary jeúli dana osoba mia≥a Ñcrashî)\n");
				strcat(s,"\n");
				strcat(s,"*za kaødπ odmowÍ przyjÍcia mandatu(5 min. aresztu + 3 punkty karne)\n");
				strcat(s,"**jeúli dany osobnik bÍdzie arogancko wykonywa≥ wykroczenia oraz przestÍpstwa oraz robi≥ wszystko co nie jest\n");
				strcat(s,"na rÍkÍ funkcjonariusza zostaje obnaøony karπ KICK\n");
				strcat(s,"\n");
				strcat(s,"ß3.Ograniczenia\n");
				strcat(s,"\n");
				strcat(s,"Roboty Drogowe - 30 km/h\n");
				strcat(s,"Teren Zabudowany - 50 km/h\n");
				strcat(s,"Teren Niezabudowany - 90 km/h\n");
				strcat(s,"Autostrada - 130 km/h\n");
				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Taryfikator", s, "Ok", "");
			}
		}
		if(dialogid == ZDAWANIE_PYTANIE)
		{
		    if(response)
		    {
		        if(zdawanie == 0)
		        {
			        SetPlayerPos(playerid, 1168.71, 1365.66, 10.82);
			        zdawanie = 1;
			        zdaje[playerid] = 1;
			        ShowPlayerDialog(playerid, PYTANIE1, DIALOG_STYLE_LIST, "Pytanie 1:\n\nKtÛrym pasem porusza siÍ na serwerze?", "a) Prawym\nb) Lewym\nc) Zaleøy od promili", "Wybierz", "Anuluj");
			        SendClientMessageToAll(KOLOR_CZERWONY, ""C_CZERWONY"Zdawanie na prawo jazdy: "C_ZIELONY"zajÍte");
				}
				else
				{
				    SendClientMessage(playerid, KOLOR_CZERWONY, "Juø ktoú zdaje na prawo jazdy. Poczekaj aø zwolni siÍ miejsce.");
				}
			}
			else
			{
				zdawanie = 0;
	   			zdaje[playerid] = 0;
	   			typPrawka[playerid] = 0;
	   			SpawnPlayer(playerid);
			}
		}
		if(dialogid == PYTANIE1)
		{
		    if(response)
		    {
		        switch(listitem)
				{
					case 0:
					{
					    ShowPlayerDialog(playerid, PYTANIE2, DIALOG_STYLE_LIST, "Pytanie 2:\n\nIle moøna maksymalnie jechac na autostradzie?", "a) 140km/h\nb) 130km/h\nc) Ile fabryka da≥a", "Wybierz", "Anuluj");
					}
					case 1:
					{
					    SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz...");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
					case 2:
					{
					    SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
				}
			}
			else
			{
				zdawanie = 0;
	   			zdaje[playerid] = 0;
	   			typPrawka[playerid] = 0;
	   			SpawnPlayer(playerid);
			}
		}
		if(dialogid == PYTANIE2)
		{
		    if(response)
		    {
		        switch(listitem)
				{
					case 0:
					{
	    				SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
					case 1:
					{
					    ShowPlayerDialog(playerid, PYTANIE3, DIALOG_STYLE_LIST, "Pytanie 3:\n\nCo robimy w sytuacji wypadku?", "a) Pierdole to, jade dalej.\nb) Dzwonie po policjÍ i uciekam bo moøe na mnie zgoniπ.\nc) DzwoniÍ po policjÍ i udzielam pierwszej pomocy", "Wybierz", "Anuluj");
					}
					case 2:
					{
					    SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
				}
			}
			else
			{
				zdawanie = 0;
	   			zdaje[playerid] = 0;
	   			typPrawka[playerid] = 0;
	   			SpawnPlayer(playerid);
			}
		}
		if(dialogid == PYTANIE3)
		{
		    if(response)
		    {
		        switch(listitem)
				{
					case 0:
					{
	    				SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
					case 1:
					{
					    SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
					case 2:
					{
					    ShowPlayerDialog(playerid, PYTANIE4, DIALOG_STYLE_LIST, "Pytanie 4:\n\nW razie braku policji na serwerze w przypadku wypadku wykonujemy:", "a) Zakopujemy cia≥o a samochÛd topiny w pobliskim jeziorze.\nb) Wzywamy Pomoc Drogowπ.\nc) Zatrzymujemy siÍ, úpiewamy anielski orszak i jedziemy dalej.", "Wybierz", "Anuluj");
					}
				}
			}
			else
			{
				zdawanie = 0;
	   			zdaje[playerid] = 0;
	   			typPrawka[playerid] = 0;
	   			SpawnPlayer(playerid);
			}
		}
		if(dialogid == PYTANIE4)
		{
		    if(response)
		    {
		        switch(listitem)
				{
					case 0:
					{
	    				SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
					case 1:
					{
						ShowPlayerDialog(playerid, PYTANIE5, DIALOG_STYLE_LIST, "Pytanie 5:\n\nCo robimy gdy widzimy pojadz uprzywilejowany:", "a) Pojeba≥o go? Co tak gloúno?.\nb) Stajemy na úrodku i udajemy úlepego.\nc) UstÍpujemy mu miejsca.", "Wybierz", "Anuluj");
					}
					case 2:
					{
						SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
				}
			}
			else
			{
				zdawanie = 0;
	   			zdaje[playerid] = 0;
	   			typPrawka[playerid] = 0;
	   			SpawnPlayer(playerid);
			}
		}
		if(dialogid == PYTANIE5)
		{
		    if(response)
		    {
		        switch(listitem)
				{
					case 0:
					{
	    				SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
					case 1:
					{
						SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥a odpowiedz... A moøe bana?");
					    zdawanie = 0;
					    zdaje[playerid] = 0;
					    SpawnPlayer(playerid);
					}
					case 2:
					{
						ShowPlayerDialog(playerid, KATEGORIA, DIALOG_STYLE_LIST, "Na jakπ kategoriÍ chcesz zdawaÊ?", "B - osobowe\nC+E - tiry\nC1 - vany", "Wybierz", "Anuluj");
					}
				}
			}
			else
			{
				zdawanie = 0;
	   			zdaje[playerid] = 0;
	   			typPrawka[playerid] = 0;
	   			SpawnPlayer(playerid);
			}
		}
		if(dialogid == KATEGORIA)
		{
		    if(response)
		    {
		        switch(listitem)
				{
					case 0:
					{
					    if(PlayerInfo[playerid][pPrawkoB] == 0)
					    {
							TogglePlayerDynamicRaceCP(playerid, cp1, 0);
							TogglePlayerDynamicRaceCP(playerid, cp2, 0);
							TogglePlayerDynamicRaceCP(playerid, cp3, 0);
							TogglePlayerDynamicRaceCP(playerid, cp4, 0);
							TogglePlayerDynamicRaceCP(playerid, cp5, 0);
							TogglePlayerDynamicRaceCP(playerid, cp6, 0);
							TogglePlayerDynamicRaceCP(playerid, cp7, 0);
						    zdaje[playerid] = 1;
		    				typPrawka[playerid] = B;
		    				DestroyVehicle(wozekprawo);
							wozekprawo = CreateVehicle(542, 1140.7935, 1233.2156, 11.3311, 0.0000, -1, -1, 100);
							SetVehicleHealth(wozekprawo, 495.0);
							SetVehicleParamsEx(wozekprawo,false,false,false,false,false,false,false);
							vPojazdZycie[wozekprawo]=495.0;
							PutPlayerInVehicle(playerid, wozekprawo, 0);
		     				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Egzamin Praktyczny", "Wybra≥eú zdawanie na kategoriÍ B.\n\nPrzejedü przez wszystkie Checkpointy bez uszkodzenia wozu !!\nJeøeli HP pojazdu spadnie conajmniej o 1 nie zdasz.\n\nPowodzenia!", "Go!", "");
		                    TogglePlayerDynamicRaceCP(playerid, cp1, 1);
						}
						else
						{
						    SendClientMessage(playerid, KOLOR_CZERWONY, "Juø masz prawo jazdy tej kategori!");
						}
					}
					case 1:
					{
					    if(PlayerInfo[playerid][pPrawkoCE] == 0)
					    {
							TogglePlayerDynamicRaceCP(playerid, cp1, 0);
							TogglePlayerDynamicRaceCP(playerid, cp2, 0);
							TogglePlayerDynamicRaceCP(playerid, cp3, 0);
							TogglePlayerDynamicRaceCP(playerid, cp4, 0);
							TogglePlayerDynamicRaceCP(playerid, cp5, 0);
							TogglePlayerDynamicRaceCP(playerid, cp6, 0);
							TogglePlayerDynamicRaceCP(playerid, cp7, 0);
						    zdaje[playerid] = 1;
							typPrawka[playerid] = CE;
							DestroyVehicle(wozekprawo);
							wozekprawo = CreateVehicle(514, 1140.7935, 1233.2156, 11.3311, 0.0000, -1, -1, 100);
							SetVehicleHealth(wozekprawo, 495.0);
							SetVehicleParamsEx(wozekprawo,false,false,false,false,false,false,false);
							vPojazdZycie[wozekprawo]=495.0;
							PutPlayerInVehicle(playerid, wozekprawo, 0);
		     				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Egzamin Praktyczny", "Wybra≥eú zdawanie na kategoriÍ C+E.\n\nPrzejedü przez wszystkie Checkpointy bez uszkodzenia wozu !!\nJeøeli HP pojazdu spadnie conajmniej o 1 nie zdasz.\n\nPowodzenia!", "Go!", "");
		                    TogglePlayerDynamicRaceCP(playerid, cp1, 1);
						}
					}
					case 2:
					{
					    if(PlayerInfo[playerid][pPrawkoA1] == 0)
					    {
						    TogglePlayerDynamicRaceCP(playerid, cp1, 0);
							TogglePlayerDynamicRaceCP(playerid, cp2, 0);
							TogglePlayerDynamicRaceCP(playerid, cp3, 0);
							TogglePlayerDynamicRaceCP(playerid, cp4, 0);
							TogglePlayerDynamicRaceCP(playerid, cp5, 0);
							TogglePlayerDynamicRaceCP(playerid, cp6, 0);
							TogglePlayerDynamicRaceCP(playerid, cp7, 0);
						    zdaje[playerid] = 1;
							typPrawka[playerid] = A1;
							DestroyVehicle(wozekprawo);
							wozekprawo = CreateVehicle(482, 1140.7935, 1233.2156, 11.3311, 0.0000, -1, -1, 100);
							SetVehicleHealth(wozekprawo, 495.0);
							SetVehicleParamsEx(wozekprawo,false,false,false,false,false,false,false);
							vPojazdZycie[wozekprawo]=495.0;
							PutPlayerInVehicle(playerid, wozekprawo, 0);
		     				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Egzamin Praktyczny", "Wybra≥eú zdawanie na kategoriÍ A1.\n\nPrzejedü przez wszystkie Checkpointy bez uszkodzenia wozu !!\nJeøeli HP pojazdu spadnie conajmniej o 1 nie zdasz.\n\nPowodzenia!", "Go!", "");
		                    TogglePlayerDynamicRaceCP(playerid, cp1, 1);
						}
					}
				}
			}
			else
			{
				zdawanie = 0;
	   			zdaje[playerid] = 0;
	   			typPrawka[playerid] = 0;
	   			SpawnPlayer(playerid);
	   			SendClientMessageToAll(KOLOR_CZERWONY, ""C_CZERWONY"Zdawanie na prawo jazdy: "C_ZIELONY"wolne");
			}
		}
	    if(dialogid == GUI_ZLECENIE)
		{
			if(response)
			{
			    switch(listitem)
			    {
			        case 0:
			            Zaladunek(playerid, "Zboze", "Farma (PC)", 1949.58581542, 155.01045227, 36.89312744, "Doki (SF)", -1547.97253417, 123.41166687, 3.55468750, 540, 1);
					case 1:
			            Zaladunek(playerid, "Dokumenty", "Biurowiec (SF)", -1978.01647949, 432.21426391, 25.52413940, "Bank (PC)", 2299.74267578, -16.02529144, 26.48437500, 650, 1);
					case 2:
			            Zaladunek(playerid, "Lampy", "Fabryka (LS)", 1769.59655761, -2032.04895019, 13.50045204, "Doki (SF)", -1547.97253417, 123.41166687, 3.55468750, 450, 1);
					case 3:
			            Zaladunek(playerid, "Ubrania", "Fabryka (LV)", 2844.83007812, 994.04730224, 10.75000000, "Doki (LS)", 2786.70556640, -2417.35815429, 13.63392734, 660, 1);
					case 4:
			            Zaladunek(playerid, "Zabawki", "Hurtownia (LS)", 2477.51879882, -1525.91687011, 23.99086189, "Centrum Handlowe (LV)", 2825.12182617, 2604.18334960, 10.82031250, 430, 1);
					case 5:
			            Zaladunek(playerid, "Kabury", "Fabryka (LV)", 1425.94555664, 1045.76538085, 10.82031250, "Komenda Policji (D)", 613.17028808, -589.53033447, 17.23301315, 350, 1);
					case 6:
			            Zaladunek(playerid, "Wojskowe mundury", "Lotnisko (LS)", 2083.56469726, -2385.54077148, 13.54687500, "Area69 (Pustynia)", 135.31710815, 1949.65930175, 19.38471031, 890, 1);
					case 7:
			            Zaladunek(playerid, "Amunicja", "Baza Wojskowa (LV)", 2491.04028320, 2772.71728515, 10.79721641, "Area69 (Pustynia)", 135.44364929, 1948.60070800, 19.37591934, 830, 1);
					case 8:
			            Zaladunek(playerid, "Bronie", "Ammu-Nation (AP)", -2116.91601562, -2469.71728515, 30.62500000, "Baza Wojskowa (LV)", 2489.77954101, 2772.05029296, 10.79136657, 670, 1);
	                case 9:
			            Zaladunek(playerid, "Amfetamina", "Farma Whetstone (SF)", -1445.79028320, -1537.55371093, 101.75781250, "Doki (LS)", 2792.76123046, -2456.56933593, 13.63244915, 1500, 2);
					case 10:
					    Zaladunek(playerid, "Marihuana", "Farma (PC)", 1949.58581542, 155.01045227, 36.89312744, "Doki (SF)", -1547.97253417, 123.41166687, 3.55468750, 1550, 2);
					case 11:
			            Zaladunek(playerid, "Porcelana", "Doki (SF)", -1546.48730468, 124.79665374, 3.55468750, "Hurtownia (RC)", 318.22738647, -34.84130859, 1.57812500, 690, 1);
					case 12:
			            Zaladunek(playerid, "Artykuly Spozywcze", "Hurtownia (B)", -2450.29760742, 2302.67773437, 4.97872781, "Sklep (EQ)", -1518.13586425, 2572.16259765, 55.83593750, 670, 1);
	                case 13:
			            Zaladunek(playerid, "Cukier", "Port Bayside (SF)", -2247.23291015, 2371.20776367, 4.99713945, "The Brown Starfish (LS)", 369.75573730, -2041.23242187, 7.67187500, 950, 1);
					case 14:
					    Zaladunek(playerid, "Paliwo", "Gasso (D)", 666.18408203, -546.52062988, 16.33593750, "Stacja Benzynowa (EQ)", -1271.56640625, 2731.08691406, 50.06250000, 780, 1);
	                case 15:
			            Zaladunek(playerid, "Komputery", "Pro Computers (LS)", 1132.00000000, -1672.00000000, 13.00000000, "Bilbioteka (PC)", 2254.00000000, -84.00000000, 26.00000000, 800, 1);
					case 16:
					    Zaladunek(playerid, "Piasek", "Kopalnia (LV)", 597.97473144, 869.46307373, -42.96093750, "Plac budowy (LS)", 1255.19604492, -1258.97167968, 13.17149257, 750, 1);
					case 17:
			            Zaladunek(playerid, "Kurtki", "Binco (LS)", 2280.70361328, -1680.24768066, 14.52397346, "Binco (SF)", -2381.08691406, 911.27746582, 45.29687500, 590, 1);
	                case 18:
			            Zaladunek(playerid, "Drukarki", "Pro Computers (LS)", 1132.00000000, -1672.00000000, 13.00000000, "Centrum Konferencyjne (LS)", 1198.24206542, -1733.65673828, 13.57336044, 750, 1);
					case 19:
					    Zaladunek(playerid, "Odpady", "Burger Shot (LS)", 787.86322021, -1635.77478027, 13.38281250, "Wysypisko smieci (LS)", 2179.51464843, -1990.78271484, 13.54687500, 780, 1);
	                case 20:
			            Zaladunek(playerid, "Kamery", "Pro Computers (LS)", 1132.00000000, -1672.00000000, 13.00000000, "Interglobal Television (LS)", 737.20202636, -1337.69006347, 13.53339004, 880, 1);
					case 21:
					    Zaladunek(playerid, "Papier", "Binco (SF)", -2381.08691406, 911.27746582, 45.29687500, "Bank (PC)", 2299.74267578, -16.02529144, 26.48437500, 760, 1);
				}
			}
		}
		if(dialogid == GUI_ZLECENIE_LOT)
		{
			if(response)
			{
			    switch(listitem)
			    {
			        case 0:
			        	Zaladunek(playerid, "ØywnoúÊ", "Lotnisko (LS)", 1588.5, -2546.1000976563, 12.300000190735, "Lotnisko (LV)", 1433.0999755859, 1369.5999755859, 9.8000001907349, 1540, 3);
					case 1:
			        	Zaladunek(playerid, "Ludzie", "Lotnisko (LV)", 1433.0999755859, 1369.5999755859, 9.8000001907349, "Lotnisko (SF)", -1525, -122.09999847412, 12.39999961853, 1650, 3);
					case 2:
			        	Zaladunek(playerid, "Artyku≥y Gospodarstwa Domowego", "Lotnisko (LS)", 1588.5, -2546.1000976563, 12.300000190735, "Lotnisko (LV)", 1433.0999755859, 1369.5999755859, 9.8000001907349, 1450, 3);
					case 3:
			        	Zaladunek(playerid, "Ubrania", "Lotnisko (SF)", -1525, -122.09999847412, 12.39999961853, "Lotnisko (opuszczone)", 358.79998779297, 2539.6999511719, 15.5, 1660, 3);
                    case 4:
			        	Zaladunek(playerid, "Zabawki", "Lotnisko (opuszczone)", 358.79998779297, 2539.6999511719, 15.5, "Lotnisko (LV)", 1433.0999755859, 1369.5999755859, 9.8000001907349, 1430, 3);
				}
			}
		}
		if(dialogid == GUI_ZLECENIE_ST)
		{
		    if(response)
			{
			    switch(listitem)
			    {
			        case 0:
						Zaladunek(playerid, "czesci budowlane", "brak", -2073.39990234,202.19999695,35.20000076,"brak", 2758.30004883,-2395.19995117,13.19999981, 2540, 1);
					case 1:
						Zaladunek(playerid, "czesci do kombajna", "brak", -104.40000153,-76.40000153,2.70000005,"brak", -1693.19995117,36.59999847,3.20000005, 2673, 1);
					case 2:
						Zaladunek(playerid, "czesci do koparek", "brak", -2272.80004883,2392.39990234,4.50000000,"brak", 584.90002441,895.79998779,-44.50000000, 2717, 1);
					case 3:
						Zaladunek(playerid, "marihuana", "brak", 2810.30004883,918.50000000,10.30000019,"brak", 558.29998779,859.90002441,-43.40000153, 3952, 1);
					case 4:
						Zaladunek(playerid, "amfetamina", "brak", 2485.50000000,931.50000000,10.39999962,"brak", 2405.39990234,92.80000305,26.10000038, 3893, 1);
					case 5:
						Zaladunek(playerid, "paliwo do koparek", "brak", 271.20001221,1410.50000000,10.10000038,"brak", 579.50000000,891.70001221,-44.00000000, 2751, 1);
					case 6:
						Zaladunek(playerid, "prezerwatywy", "brak", 693.79998779,1942.50000000,5.09999990,"brak", -1740.09997559,157.50000000,3.20000005, 2873, 1);
					case 7:
						Zaladunek(playerid, "ropa", "brak", 270.29998779,1405.09997559,10.10000038,"brak", -1730.09997559,131.80000305,3.20000005, 2538, 1);
					case 8:
						Zaladunek(playerid, "samochody wyscigowe", "brak", 1078.50000000,1740.50000000,10.39999962,"brak", -2261.10009766,2322.00000000,4.40000010, 1430, 1);
					case 9:
						Zaladunek(playerid, "trumny", "brak", -2260.19995117,2331.60009766,4.40000010,"brak", 2240.89990234,-1310.90002441,23.60000038, 2673, 1);
				}
			}
		}
		if(dialogid == GUI_ANULUJ)
		{
			if(response == 1)
			{
	 			DisablePlayerCheckpoint(playerid);
		    	SetPVarInt(playerid, "etap", 0);
			}
			else
			{
				SCM(playerid, -1, "Nie posiadasz øadnego towaru");
			}
		}

			if(dialogid == GUI_OB)
			{
				if(response)
				{
					switch(listitem)
					{
						case 0:
						{
						    if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
							{
								RemovePlayerAttachedObject(playerid, 0);
							}
							else
							{
						    	SetPlayerAttachedObject(playerid, 0, 19079, 1, 0.297670, -0.057706, 0.147036, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000 );
							}
						}
						case 1:
						{
						    if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
							{
								RemovePlayerAttachedObject(playerid, 1);
							}
							else
							{
			    				SetPlayerAttachedObject(playerid, 1, 356, 1, -0.221766, -0.148428, 0.091785, 0.000000, 36.229553, 0.000000, 1.000000, 1.000000, 1.000000 ); // m4 - m4
							}
						}
						case 2:
						{
							if(IsPlayerAttachedObjectSlotUsed(playerid, 2))
							{
								RemovePlayerAttachedObject(playerid, 2);
							}
							else
							{
			    				SetPlayerAttachedObject(playerid, 2, 19086, 13, 0.331070, 0.013773, -0.028330, 358.113372, 283.851989, 271.677886, 1.000000, 1.000000, 1.000000 ); // ChainsawDildo1 - dildo
							}
						}
						case 3:
						{
							if(IsPlayerAttachedObjectSlotUsed(playerid, 3))
							{
								RemovePlayerAttachedObject(playerid, 3);
							}
							else
							{
			    				SetPlayerAttachedObject(playerid, 3, 19065, 15, -0.025, -0.04, 0.23, 0, 0, 270, 2, 2, 2 ); // ChainsawDildo1 - dildo
							}
						}
						case 4:
						{
							if(IsPlayerAttachedObjectSlotUsed(playerid, 4))
							{
								RemovePlayerAttachedObject(playerid, 4);
							}
							else
							{
			    				SetPlayerAttachedObject(playerid, 4, 19065, 2, 0.120000, 0.040000, -0.003500, 0, 100, 100, 1.4, 1.4, 1.4);
							}
						}
					}
				}
			}
		if(dialogid == PANEL_DJ)
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/1.mp3");
						}
					}
					case 1:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/2.mp3");
						}
					}
					case 2:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/3.mp3");
						}
					}
					case 3:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/4.mp3");
						}
					}
					case 4:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/5.mp3");
						}
					}
					case 5:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/6.mp3");
						}
					}
					case 6:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/7.mp3");
						}
					}
					case 7:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/8.mp3");
						}
					}
					case 8:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/9.mp3");
						}
					}
					case 9:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/10.mp3");
						}
					}
					case 10:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/11.mp3");
						}
					}
					case 11:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/12.mp3");
						}
					}
					case 12:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/13.mp3");
						}
					}
					case 13:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/14.mp3");
						}
					}
					case 14:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/pack.mp3");
						}
					}
					case 15:
					{
						new s[600];
						strcat(s,"1. Ania Szarmach - Coraz blizej swieta\n");
						strcat(s,"2. Celine Dion - So This Is Christmas\n");
						strcat(s,"3. Cliff Richards - Christmas time\n");
						strcat(s,"4. Dance House - Santa Claus Is Coming To Town\n");
						strcat(s,"5. De su - Kto Wie\n");
						strcat(s,"6. Mariah Carey - All I Want For Christmas\n");
						strcat(s,"7. Shakin Stevens - Merry Christmas Everyone\n");
						strcat(s,"8. Wham - Last Christmas");
						ShowPlayerDialog(playerid,PANEL_DJ_CH,DIALOG_STYLE_LIST, "Panel DJ'a - åwiÍta", s, "Play", "Anuluj");
					}
					case 16:
					{
     					ShowPlayerDialog(playerid, PANEL_DJ_URL, DIALOG_STYLE_INPUT, "Panel DJ'a - Adres URL", "Wpisz adres url nutki jakπ chcesz puúciÊ.\n\n"C_CZERWONY"UWAGA\n"C_CZERWONY"Link musi pochodziÊ z hostingu www.william.ugu.pl", "Play", "Anuluj");
					}
					case 17:
					{
						foreach(Player, i)
						{
								StopAudioStreamForPlayer(i);
						}
					}
				}
			}
		}

		if(dialogid == PANEL_DJ_CH)
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/1.mp3");
						}
					}
					case 1:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/2.mp3");
						}
					}
					case 2:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/3.mp3");
						}
					}
					case 3:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/4.mp3");
						}
					}
					case 4:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/5.mp3");
						}
					}
					case 5:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/6.mp3");
						}
					}
					case 6:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/7.mp3");
						}
					}
					case 7:
					{
						foreach(Player, i)
						{
						    StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i, "http://www.william.ugu.pl/swieta/8.mp3");
						}
					}
				}
			}
		}


		if(dialogid == PANEL_DJ_URL)
		{
		    if(response)
		    {
		        foreach(Player, i)
		        {
		            StopAudioStreamForPlayer(i);
		            PlayAudioStreamForPlayer(i, inputtext);
				}
			}
		}

	    if(dialogid == GUI_EMAIL)
	    {
	        if(response || !response)
	        {
	            strmid(PlayerInfo[playerid][pEmail], inputtext, 0, strlen(inputtext), 64);
				format(dstring, sizeof(dstring), ""C_BEZOWY"TwÛj email zosta≥ zapisany! Podany email to: "C_ZIELONY"%s", PlayerInfo[playerid][pEmail]);
				SendClientMessage(playerid, KOLOR_CZERWONY, dstring);
			}
		}

			if(dialogid == GUI_VIATOLL)
			{
			    if(response)
				{
			 		switch(listitem)
			        {
			            case 0:
			           	{
			           	    new string[128];
			           	    format(string, sizeof(string), "TwÛj stan konta ViaToll: %d", GetPVarInt(playerid, "PunktyToll"));
			                ShowPlayerDialog(playerid,GUI_VIATOLL2,DIALOG_STYLE_MSGBOX,"ViaTol - Stan Kπpta", string, "Ok", "");
			           	}
			           	case 1:
			           	{
			           	    ShowPlayerDialog(playerid,GUI_VIATOLL1,DIALOG_STYLE_LIST,"ViaToll - Kup ViaToll\n\nWybierz kwotÍ do≥adowania konta ViaToll\n\t1 punkt ViaToll = 1$","50\tza 50$\n80\tza 80$\n100\tza 100$\n120\tza 120$\n150\tza 140$","Kup","Wyjdü");
			           	}
					}
				}
			}
		    if(dialogid == GUI_VIATOLL1)
			{
			    if(response)
				{
			 		switch(listitem)
			        {
			            case 0:
			           	{
			           	    if(dWyswietlKase(playerid) >= 50)
			           	    {
			           	    	new punkciki = GetPVarInt(playerid, "PunktyToll");
			           	    	SetPVarInt(playerid, "PunktyToll", punkciki+50);
								new string[128];
			           	    	format(string, sizeof(string), ""C_BIALY"Kupi≥eú "C_ZIELONY"50"C_BIALY" punktÛw ViaToll. TwÛj stan konta wynosi: "C_ZIELONY"%d", GetPVarInt(playerid, "PunktyToll"));
			           	    	SendClientMessage(playerid, 0xFFFFFF, string);
			           	    	dDodajKase(playerid, -50);
							}
							else
							{
							    SendClientMessage(playerid, 0xFFFFFF, ""C_CZERWONY"ViaToll warning: "C_BIALY"Nie staÊ ciÍ na kupno "C_ZIELONY"50"C_BIALY" punktÛw ViaToll");
							}
			           	}
			           	case 1:
			           	{
			           	    if(dWyswietlKase(playerid) >= 80)
			           	    {
				           	    new punkciki = GetPVarInt(playerid, "PunktyToll");
				           	    SetPVarInt(playerid, "PunktyToll", punkciki+80);
				           	    new string[128];
				           	    format(string, sizeof(string), ""C_BIALY"Kupi≥eú "C_ZIELONY"80"C_BIALY" punktÛw ViaToll. TwÛj stan konta wynosi: "C_ZIELONY"%d", GetPVarInt(playerid, "PunktyToll"));
				           	    SendClientMessage(playerid, 0xFFFFFF, string);
				           	    dDodajKase(playerid, -80);
			           	    }
							else
							{
							    SendClientMessage(playerid, 0xFFFFFF, ""C_CZERWONY"ViaToll warning: "C_BIALY"Nie staÊ ciÍ na kupno "C_ZIELONY"50"C_BIALY" punktÛw ViaToll");
							}
			           	}
			           	case 2:
			           	{
			           	    if(dWyswietlKase(playerid) >= 100)
			           	    {
				           	    new punkciki = GetPVarInt(playerid, "PunktyToll");
				           	    SetPVarInt(playerid, "PunktyToll", punkciki+100);
				           	    new string[128];
				           	    format(string, sizeof(string), ""C_BIALY"Kupi≥eú "C_ZIELONY"100"C_BIALY" punktÛw ViaToll. TwÛj stan konta wynosi: "C_ZIELONY"%d", GetPVarInt(playerid, "PunktyToll"));
				           	    SendClientMessage(playerid, 0xFFFFFF, string);
				           	    dDodajKase(playerid, -100);
			           	    }
							else
							{
							    SendClientMessage(playerid, KOLOR_BIALY, ""C_CZERWONY"ViaToll warning: "C_BIALY"Nie staÊ ciÍ na kupno "C_ZIELONY"50"C_BIALY" punktÛw ViaToll");
							}
			           	}
			           	case 3:
			           	{
			           	    if(dWyswietlKase(playerid) >= 120)
			           	    {
				           	    new punkciki = GetPVarInt(playerid, "PunktyToll");
				           	    SetPVarInt(playerid, "PunktyToll", punkciki+120);
				           	    new string[128];
				           	    format(string, sizeof(string), ""C_BIALY"Kupi≥eú "C_ZIELONY"120"C_BIALY" punktÛw ViaToll. TwÛj stan konta wynosi: "C_ZIELONY"%d", GetPVarInt(playerid, "PunktyToll"));
				           	    SendClientMessage(playerid, KOLOR_BIALY, string);
				           	    dDodajKase(playerid, -120);
			           	    }
							else
							{
							    SendClientMessage(playerid, KOLOR_BIALY, ""C_CZERWONY"ViaToll warning: "C_BIALY"Nie staÊ ciÍ na kupno "C_ZIELONY"50"C_BIALY" punktÛw ViaToll");
							}
			           	}
			           	case 4:
			           	{
			           	    if(dWyswietlKase(playerid) >= 140)
			           	    {
				           	    new punkciki = GetPVarInt(playerid, "PunktyToll");
				           	    SetPVarInt(playerid, "PunktyToll", punkciki+150);
				           	    new string[128];
				           	    format(string, sizeof(string), ""C_BIALY"Kupi≥eú "C_ZIELONY"150"C_BIALY" punktÛw ViaToll. TwÛj stan konta wynosi: "C_ZIELONY"%d", GetPVarInt(playerid, "PunktyToll"));
				           	    SendClientMessage(playerid, KOLOR_BIALY, string);
				           	    dDodajKase(playerid, -140);
			           	    }
							else
							{
							    SendClientMessage(playerid, KOLOR_BIALY, ""C_CZERWONY"ViaToll warning: "C_BIALY"Nie staÊ ciÍ na kupno "C_ZIELONY"50"C_BIALY" punktÛw ViaToll");
							}
			           	}
					}
				}
			}
			if(dialogid == 1)
			{
				if(!response)
				{
					Info(playerid,""C_CZERWONY"Zostajesz wyrzucony poniewaø nie akceptowa≥eú regulaminu!");
					Kick(playerid);
					return 1;
				}
				else
				{
					if(Regulamin[playerid]==true)
					{
						new s[300],ss[300],sss[600];
						format(s, sizeof(s), ""C_ZOLTY"1. Jest to polski serwer, wiÍc uøywamy wy≥πcznie polskiego jÍzyka.\n2. Zabrania siÍ jakichkolwiek bluzgÛw, zachowaj kulturÍ osobistπ.\n3. Zabrania siÍ zak≥Ûcania pozosta≥ym osobom gry.\n4. Zabrania siÍ spamowania lub pisania bez takiej potrzeby.");
						format(ss, sizeof(ss), ""C_ZOLTY"5. Zabrania siÍ wykorzystywania cheatÛw lub jakichkolwiek b≥ÍdÛw skryptu.\n6. Gdy jesteú úwiadkiem przewinieÒ, Twoim obowiπzkiem jest poinformowanie o tym administracji.\n7. Za z≥amanie regulaminu moøna otrzymaÊ kare, w najgorszym wypadku bana.\n"C_ZIELONY"Czy akceptujesz regulamin?");
						format(sss, sizeof(sss), "%s\n%s",s,ss);
						ShowPlayerDialog(playerid,1,DIALOG_STYLE_MSGBOX,""C_CZERWONY"Regulamin Serwera",sss,"Tak","Nie");
						GInfo(playerid,"~r~czytaj...",1);
						return 1;
					}
					ShowPlayerDialog(playerid,3,DIALOG_STYLE_INPUT,""C_ZOLTY"Hard-Truck: "C_BIALY"Rejestracja",""C_BIALY"Witaj!\nAby zagraÊ na tym serwerze musisz siÍ zarejestrowaÊ!\nW celu zarejestrowania siÍ wpisz "C_ZOLTY"has≥o do konta"C_BIALY":","Rejestruj","Wyjdü");
				}
				return 1;
			}

	    	else if(dialogid == 2)
	   		{
	       		if(!response) return Kick(playerid);
       			if(isnull(inputtext))
		   		{
				   ShowPlayerDialog(playerid,2,DIALOG_STYLE_PASSWORD,""C_ZOLTY"Hard-Truc: "C_BIALY"Logowanie",""C_BIALY"Ten login jest zarejestrowany!\nW celu zalogowania siÍ wpisz "C_ZOLTY"has≥o"C_BIALY":","Zaloguj","Wyjdü");
				   return 1;
		   		}
       			GraczSieLoguje(playerid,inputtext);
       			return 1;
	    	}
	    //
			else if(dialogid == 3)
	   		{
	       		if(!response) return Kick(playerid);
	       		if(isnull(inputtext))
		   	{
			   	ShowPlayerDialog(playerid,3,DIALOG_STYLE_PASSWORD,""C_ZOLTY"Hard-Truck: "C_BIALY"Rejestracja",""C_BIALY"Aby zagraÊ na tym serwerze musisz siÍ zarejestrowaÊ!\nW celu zarejestrowania siÍ wpisz "C_ZOLTY"has≥o do konta"C_BIALY":","Rejestruj","Wyjdü");
			   	return 1;
		   	}
	       	if(strlen(inputtext)<5||strlen(inputtext)>15)
		   	{
			   	ShowPlayerDialog(playerid,3,DIALOG_STYLE_PASSWORD,""C_ZOLTY"Hard-Truck: "C_BIALY"Rejestracja",""C_BIALY"Od 5 do 15 liter!\nAby zagraÊ na tym serwerze musisz siÍ zarejestrowaÊ!\nW celu zarejestrowania siÍ wpisz "C_ZOLTY"has≥o do konta"C_BIALY":","Rejestruj","Wyjdü");
			   	return 1;
		   	}
	       	GraczSieRejestruje(playerid,inputtext);
	       	return 1;
	    }
	    //
		else if(dialogid == 4)
	   	{
			if(!response) return 1;
			new v;
			switch(listitem)
			{
			    case 0:
			    {
			        if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
					{
					    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
					    return 1;
					}
			        v=GetPlayerVehicleID(playerid);
	 				GetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,boot,objective);
	 				if(engine)
	 				{
	 				    TextDrawHideForPlayer(playerid,Licznik[playerid]);
	 				    UkryjFirmaTD(playerid);
	 				    TextDrawHideForPlayer(playerid, Zones[playerid]);
	 				    GInfo(playerid,"~w~silnik ~r~wylaczony",3);
	 				    SetVehicleParamsEx(v,false,lights,alarm,doors,bonnet,boot,objective);
	 				}
	 				else
	 				{
	 				    if(vPaliwo[v]<=1)
	 				    {
	 				        Info(playerid,""C_CZERWONY"Ten pojazd nie ma paliwa!");
	 				        return 1;
	 				    }
	 				    SetTimerEx("SilnikUruchom",3000,false,"i",playerid);
	 				    GInfo(playerid,"~w~uruchamianie silnika",3);
	 				}
	 				return 1;
			    }
			    case 1:
			    {
			        if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
					{
					    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
					    return 1;
					}
			        v=GetPlayerVehicleID(playerid);
	 				GetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,boot,objective);
	 				if(lights)
	 				{
	 				    GInfo(playerid,"~w~lampy ~r~wylaczone",3);
	 				    SetVehicleParamsEx(v,engine,false,alarm,doors,bonnet,boot,objective);
						if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)
						{
						    if(GetVehicleTrailer(v)!=0)
						    {
						        SetVehicleParamsEx(GetVehicleTrailer(v),engine,false,alarm,doors,bonnet,boot,objective);
						    }
						}
	 				}
	 				else
	 				{
	 				    GInfo(playerid,"~w~lampy ~g~wlaczone",3);
	 				    SetVehicleParamsEx(v,engine,true,alarm,doors,bonnet,boot,objective);
	 				    if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)
						{
						    if(GetVehicleTrailer(v)!=0)
						    {
						        SetVehicleParamsEx(GetVehicleTrailer(v),engine,true,alarm,doors,bonnet,boot,objective);
						    }
						}
	 				}
	 				return 1;
			    }
			    case 2:
			    {
			        if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
					{
					    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
					    return 1;
					}
			        v=GetPlayerVehicleID(playerid);
	 				GetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,boot,objective);
	 				if(bonnet)
	 				{
	 				    GInfo(playerid,"~w~maska ~r~zamknieta",3);
	 				    SetVehicleParamsEx(v,engine,lights,alarm,doors,false,boot,objective);
	 				}
	 				else
	 				{
	 				    GInfo(playerid,"~w~maska ~g~otwarta",3);
	 				    SetVehicleParamsEx(v,engine,lights,alarm,doors,true,boot,objective);
	 				}
	 				return 1;
			    }
			    case 3:
			    {
			        if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
					{
					    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
					    return 1;
					}
			        v=GetPlayerVehicleID(playerid);
	 				GetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,boot,objective);
	 				if(boot)
	 				{
	 				    GInfo(playerid,"~w~bagaznik ~r~zamkniety",3);
	 				    SetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,false,objective);
	 				}
	 				else
	 				{
	 				    GInfo(playerid,"~w~bagaznik ~g~otwarty",3);
	 				    SetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,true,objective);
	 				}
	 				return 1;
			    }
			    case 4:
			    {
			        if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
					{
					    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
					    return 1;
					}
			        v=GetPlayerVehicleID(playerid);
	 				GetVehicleParamsEx(v,engine,lights,alarm,doors,bonnet,boot,objective);
	 				if(doors)
	 				{
	 				    GInfo(playerid,"~w~drzwi ~g~otwarte",3);
	 				    SetVehicleParamsEx(v,engine,lights,alarm,false,bonnet,boot,objective);
	 				}
	 				else
	 				{
	 				    GInfo(playerid,"~w~drzwi ~r~zamkniete",3);
	 				    SetVehicleParamsEx(v,engine,lights,alarm,true,bonnet,boot,objective);
	 				}
	 				return 1;
			    }
			    case 5:
			    {
			        if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
					{
					    Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ pojazdu!");
					    return 1;
					}
					if(ToRadiowoz(GetPlayerVehicleID(playerid)))
					{
						Info(playerid,""C_CZERWONY"Ten pojazd nie ma CB-Radia!");
					    return 1;
					}
					ShowPlayerDialog(playerid,7,DIALOG_STYLE_LIST,""C_ZOLTY"CB-Radio",""C_ZIELONY"W≥πcz"C_BIALY" / "C_CZERWONY"Wy≥πcz "C_ZOLTY"CB-Radio\n"C_ZOLTY"ZmieÒ kana≥\n"C_ZOLTY"Sprawdü kana≥\n"C_ZOLTY"Informacja","Wybierz","Zamknij");
	 				return 1;
			    }
			}
			return 1;
	    }
	    else if(dialogid == 5)
	   	{
			if(!response) return 1;
	        new v=GetPlayerVehicleID(playerid),potrzebne=vPaliwoMax[v]-vPaliwo[v];
	        if(isnull(inputtext))
		   	{
				format(dstring, sizeof(dstring), ""C_ZOLTY"Witaj na stacji benzynowej!\n"C_ZIELONY"Do pe≥nego baku brakuje Tobie: %d litr/Ûw.\n1 litr kosztuje 1.2$\n"C_ZOLTY"Ile litrÛw chcesz zatankowaÊ?",potrzebne);
				ShowPlayerDialog(playerid,5,DIALOG_STYLE_INPUT,""C_POMARANCZOWY"Tankowanie",dstring,"Tankuj","Zamknij");
				return 1;
			}
			new id=StacjaPaliw(playerid);
			new paliwo=strval(inputtext),cena=floatround(paliwo*StacjaInfo[id][sCena]);
			if(paliwo<1||paliwo>potrzebne)
			{
			    Info(playerid,""C_CZERWONY"Nie poprawna wartoúÊ paliwa!");
			    return 1;
			}
			TankowanePaliwo[playerid]=paliwo;
			format(dstring, sizeof(dstring), ""C_ZOLTY"Czy chcesz zatankowaÊ "C_ZIELONY"%d "C_ZOLTY"litr/Ûw za "C_ZIELONY"%d$ "C_ZOLTY"?",paliwo,cena);
			ShowPlayerDialog(playerid,6,DIALOG_STYLE_MSGBOX,""C_POMARANCZOWY"Tankowanie",dstring,"Tak","Nie");
	   	    return 1;
	   	}
	   	else if(dialogid == 6)
	   	{
			if(!response) return 1;
			new v=GetPlayerVehicleID(playerid),paliwo=TankowanePaliwo[playerid],cena,id;
			id=StacjaPaliw(playerid);
			cena=floatround(paliwo*StacjaInfo[id][sCena]);
			if(!dCzyMaKase(playerid,cena))
	  		{
	    		Info(playerid,""C_CZERWONY"Nie masz tyle pieniÍdzy!");
			    return 1;
			}
			dDodajKase(playerid,-cena);
	        vPaliwo[v]+=paliwo;
			format(dstring, sizeof(dstring), ""C_ZOLTY"Zatankowa≥eú "C_ZIELONY"%d "C_ZOLTY"litr/Ûw za "C_ZIELONY" %d$\n"C_ZOLTY"Poziom twojego baku wynosi: "C_ZIELONY"%d"C_ZOLTY"/"C_ZIELONY"%d "C_ZOLTY"l",paliwo,cena,vPaliwo[v],vPaliwoMax[v]);
			Info(playerid,dstring);
	   	    return 1;
	   	}
		else if(dialogid == 7)
	   	{
			if(!response) return 1;
			new v=GetPlayerVehicleID(playerid);
	  		switch(listitem)
			{
			    case 0:
			    {
			        if(vCB[v]==0)
			        {
			            vCB[v]=19;
			            Info(playerid,""C_ZOLTY"CB-Radio "C_ZIELONY"w≥πczone!\n"C_ZOLTY"Kana≥ domyúlnie ustawiony na: "C_ZIELONY"19");
			            return 1;
			        }
			        else
			        {
			            vCB[v]=0;
			            Info(playerid,""C_ZOLTY"CB-Radio "C_CZERWONY"wy≥πczone!");
			            return 1;
			        }
			    }
			    case 1:
			    {
	    			format(dstring, sizeof(dstring), ""C_ZOLTY"Obecny kana≥ CB jest ustawiony na: "C_ZIELONY"%d\n"C_ZOLTY"ZmieÒ kana≥ na (19-100):",vCB[v]);
	     			ShowPlayerDialog(playerid,8,DIALOG_STYLE_INPUT,""C_POMARANCZOWY"CB-Radio",dstring,"ZmieÒ","");
	     			return 1;
	     		}
	     		case 2:
	     		{
	     			format(dstring, sizeof(dstring), ""C_ZOLTY"Obecny kana≥ jest ustawiony na: "C_ZIELONY"%d",vCB[v]);
					Info(playerid,dstring);
					return 1;
	     		}
	     		case 3:
	     		{
					Info(playerid,""C_ZOLTY"CB-Radio ma zasiÍg na 3 kilometry.");
					return 1;
	     		}
			}
	   	    return 1;
	   	}
	   	else if(dialogid == 8)
	   	{
			if(!response) return 1;
			new kanal=strval(inputtext),v=GetPlayerVehicleID(playerid);
			if(kanal<19||kanal>100)
			{
				Info(playerid,""C_CZERWONY"Nie poprawny kana≥!");
			    return 1;
			}
	        vCB[v]=kanal;
			format(dstring, sizeof(dstring), ""C_ZOLTY"Zmieni≥eú kana≥ na: "C_ZIELONY"%d",kanal);
			Info(playerid,dstring);
	   	    return 1;
	   	}
	   	else if(dialogid == 9)
	   	{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					new str[500];
					format(str, sizeof(str), ""C_ZOLTY"Wizyty na serwerze: "C_ZIELONY"%d\n"C_ZOLTY"Ping: "C_ZIELONY"%d\n"C_ZOLTY"Score: "C_ZIELONY"%d\n"C_ZOLTY"GotÛwka: "C_ZIELONY"%d$\n"C_ZOLTY"Bank: "C_ZIELONY"%d$\n"C_ZOLTY"Ostrzeøenia: "C_ZIELONY"%d/4\n"C_ZOLTY"Prawo jazdy kategori B: "C_ZIELONY"%d\n"C_ZOLTY"Prawo jazdy kategori C+E: "C_ZIELONY"%d\n"C_ZOLTY"Prawo jazdy kategori A1: "C_ZIELONY"%d\n"C_ZOLTY"Punkty karne: "C_ZIELONY"%d\n",
					PlayerInfo[playerid][pWizyty],
					GetPlayerPing(playerid),
					PlayerInfo[playerid][pDostarczenia],
					dWyswietlKase(playerid),
					PlayerInfo[playerid][pBank],
					PlayerInfo[playerid][pWarny],
					PlayerInfo[playerid][pPrawkoB],
					PlayerInfo[playerid][pPrawkoCE],
					PlayerInfo[playerid][pPrawkoA1],
					PlayerInfo[playerid][pPunkty]);
					Info(playerid,str);
				    return 1;
				}
				case 1:
				{
	                format(dstring, sizeof(dstring), ""C_ZOLTY"Obecno has≥o: "C_CZERWONY"%s\n"C_ZOLTY"Podaj nowe has≥o:",PlayerInfo[playerid][pHaslo]);
	     			ShowPlayerDialog(playerid,10,DIALOG_STYLE_PASSWORD,""C_POMARANCZOWY"Has≥o",dstring,"ZmieÒ","Zamknij");
				    return 1;
				}
				case 2:
				{
					if(BlokadaPW[playerid]==true)
					{
					    BlokadaPW[playerid]=false;
					    Info(playerid,""C_ZOLTY"Blokada PW "C_ZIELONY"wy≥πczona");
					}
					else
					{
					    BlokadaPW[playerid]=true;
					    Info(playerid,""C_ZOLTY"Blokada PW "C_CZERWONY"w≥πczona");
					}
				    return 1;
				}
			}
			return 1;
		}
		else if(dialogid == 10)
	   	{
			if(!response) return 1;
			if(strlen(inputtext)<5||strlen(inputtext)>15)
			{
				Info(playerid,""C_CZERWONY"Nie poprawna d≥ugoúÊ has≥a!");
			    return 1;
			}
	        strmid(PlayerInfo[playerid][pHaslo], inputtext, 0, strlen(inputtext), 64);
			format(dstring, sizeof(dstring), ""C_ZOLTY"Zmieni≥eú has≥o na: "C_CZERWONY"%s",inputtext);
			Info(playerid,dstring);
			ZapiszKonto(playerid);
	   	    return 1;
	   	}
/*
	   	else if(dialogid == 11)
	   	{
			if(!response) return 1;
			Info(playerid,""C_ZOLTY"Anulowa≥eú misjÍ i otrzyma≥eú grzywnÍ w wysokoúci: "C_CZERWONY"1000$");
			dDodajKase(playerid,-1000);
			AnulujMisje(playerid);
			return 1;
		}
*/
		if(dialogid == GUI_TARYFIKATOR)
	 	{
			if(response)
			{
				switch(listitem)
				{
					case 0: TarOn(playerid);
					case 1: TarOff(playerid);
					case 2: TarZer(playerid);
					case 3: {}
					case 4: Info(playerid, "Juz w krotce");
				}
			}
		}

		if(dialogid == NEON)
		{
			if(response)
			{
			    if(listitem == 0)
			    {
			        SetPVarInt(playerid, "neon", 1);
	            	SetPVarInt(playerid, "blue", CreateObject(18648,0,0,0,0,0,0));
	            	SetPVarInt(playerid, "blue1", CreateObject(18648,0,0,0,0,0,0));
	            	AttachObjectToVehicle(GetPVarInt(playerid, "blue"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            	AttachObjectToVehicle(GetPVarInt(playerid, "blue1"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            	GameTextForPlayer(playerid, "~b~Niebieski~w~ neon zostal zamatowany",3500,5);
				}
				if(listitem == 1)
				{
	   				SetPVarInt(playerid, "neon", 1);
	       			SetPVarInt(playerid, "green", CreateObject(18649,0,0,0,0,0,0));
	       			SetPVarInt(playerid, "green1", CreateObject(18649,0,0,0,0,0,0));
	       			AttachObjectToVehicle(GetPVarInt(playerid, "green"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	          		AttachObjectToVehicle(GetPVarInt(playerid, "green1"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	          		GameTextForPlayer(playerid, "~g~Zielony~w~ neon zostal zamatowany",3500,5);
				}
				if(listitem == 2)
				{
				    SetPVarInt(playerid, "neon", 1);
	       			SetPVarInt(playerid, "yellow", CreateObject(18650,0,0,0,0,0,0));
	          		SetPVarInt(playerid, "yellow1", CreateObject(18650,0,0,0,0,0,0));
	            	AttachObjectToVehicle(GetPVarInt(playerid, "yellow"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	             	AttachObjectToVehicle(GetPVarInt(playerid, "yellow1"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "~y~Zolty~w~ neon zostal zamatowany",3500,5);
				}
				if(listitem == 3)
				{
	   				SetPVarInt(playerid, "neon", 1);
	   				SetPVarInt(playerid, "white", CreateObject(18652,0,0,0,0,0,0));
	   				SetPVarInt(playerid, "white1", CreateObject(18652,0,0,0,0,0,0));
	       			AttachObjectToVehicle(GetPVarInt(playerid, "white"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	          		AttachObjectToVehicle(GetPVarInt(playerid, "white1"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	                GameTextForPlayer(playerid, "~w~Bialy~w~ neon zostal zamatowany",3500,5);
				}
				if(listitem == 4)
				{
	   				SetPVarInt(playerid, "neon", 1);
	     			SetPVarInt(playerid, "pink", CreateObject(18651,0,0,0,0,0,0));
	        		SetPVarInt(playerid, "pink1", CreateObject(18651,0,0,0,0,0,0));
	          		AttachObjectToVehicle(GetPVarInt(playerid, "pink"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            	AttachObjectToVehicle(GetPVarInt(playerid, "pink1"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "~p~Rozwoy~w~ neon zostal zamatowany",3500,5);
				}
				if(listitem == 5)
				{
		   			DestroyObject(GetPVarInt(playerid, "blue"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "blue1"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "green"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "green1"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "yellow"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "yellow1"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "white"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "white1"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "pink"));
		            DeletePVar(playerid, "neon");
		            DestroyObject(GetPVarInt(playerid, "pink1"));
		            DeletePVar(playerid, "neon");
		            GameTextForPlayer(playerid, "~g~Neony zosta≥y usuniÍte",3500,5);
	            }
			}
	 	}

		if(dialogid == GUI_POJAZD) //0, bo taka jest wartoúÊ w drugim argumencie funkcji ShowPlayerDialog
		{
			if(response == 1) //Sprawdzamy, czy zosta≥ naciúniÍty lewy przycisk
			{
				if(dWyswietlKase(playerid) < 100000)
				{
					Info(playerid, ""C_CZERWONY"nie stac cie na kupno samochodu");
				}
				else
				{
			    	dDodajKase(playerid,-100000);
					Info(playerid, ""C_CZERWONY"Kupiles pojazd, pamietaj ze jezeli wysiadziesz to stracisz mozliwosc prowadzenia go");
				}
			}
			else //Jeúli nie...
			{
				new Float:Pos[3];
				GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
		    	SetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
		    	Info(playerid,""C_CZERWONY"Anulowales kupno pojazdu!");
			}
		}
	    if(dialogid == DIALOG_SALON)
		{
			if(response)
			{
			    if(listitem == 0)
			    {
	                ShowPlayerDialog(playerid, DIALOG_SALON_DOSTAWCZE, DIALOG_STYLE_LIST, "Salon Samochodowy - dostawcze",""C_NIEBIESKI"Mule(0$)\n"C_NIEBIESKI"Benson(5000$)\n"C_NIEBIESKI"Yankee(5500$)\n"C_NIEBIESKI"Berkley's RC Van(6000$)\n"C_NIEBIESKI"Pony(8000$)\n"C_NIEBIESKI"Rumpo(10000$)\n"C_NIEBIESKI"burrito(15000$)", "Kup", "Anuluj");
				}
				if(listitem == 1)
				{
				    ShowPlayerDialog(playerid, DIALOG_SALON_TRUCKI, DIALOG_STYLE_LIST, "Salon Samochodowy - trucki",""C_NIEBIESKI"Tanker(50000$)\n"C_NIEBIESKI"Linerunner(80000$)\n"C_NIEBIESKI"Roadtrain(100000$)", "Kup", "Anuluj");
				}
				if(listitem == 2)
				{
				    ShowPlayerDialog(playerid, 5010, DIALOG_STYLE_LIST, "Salon Samochodowy - naczepy",""C_NIEBIESKI"Article Trailer (0$)\n"C_NIEBIESKI"Article Trailer 2(0$)\n"C_NIEBIESKI"Article Trailer 3(0$)\n"C_NIEBIESKI"Petrol Trailer(0$)", "Kup", "Anuluj");
				}
			}
		    return 1;
		}



		if(dialogid == DIALOG_SALON_DOSTAWCZE)
		{
		    if(response)
			{
			    switch(listitem)
			    {
			        case 0:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(414, X, Y, Z, Ang, -1, -1, SPAWN);
						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,0);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Mule\n"C_NIEBIESKI"Cena: "C_ZOLTY"0$");
					}
					case 1:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(499, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-5000);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Benson\n"C_NIEBIESKI"Cena: "C_ZOLTY"5000$");
					}
					case 2:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(456, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-5500);
	                    Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Yankee\n"C_NIEBIESKI"Cena: "C_ZOLTY"5500$");
					}
					case 3:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(459, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-6000);
	                    Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Berkley's RC Van\n"C_NIEBIESKI"Cena: "C_ZOLTY"6000$");
					}
					case 4:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(413, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-8000);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Pony\n"C_NIEBIESKI"Cena: "C_ZOLTY"8000$");
					}
					case 5:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(440, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-10000);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Rumpo\n"C_NIEBIESKI"Cena: "C_ZOLTY"10000$");
					}
					case 6:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(482, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-15000);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Burrito\n"C_NIEBIESKI"Cena: "C_ZOLTY"15000$");
					}
				}
			}
			return 1;
		}

		if(dialogid == DIALOG_SALON_TRUCKI)
		{
		    if(response)
			{
			    switch(listitem)
			    {
			        case 0:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(514, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-50000);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Tanker\n"C_NIEBIESKI"Cena: "C_ZOLTY"50000$");
					}
					case 1:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(403, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-80000);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Linerunner\n"C_NIEBIESKI"Cena: "C_ZOLTY"80000$");
					}
					case 2:
			        {
			            new Float: X, Float: Y, Float: Z, Float: Ang;
						GetVehiclePos(PrivCar[playerid], X, Y, Z);
						GetVehicleZAngle(PrivCar[playerid], Ang);
						DestroyVehicle(PrivCar[playerid]);
						PrivCar[playerid] = CreateVehicle(514, X, Y, Z, Ang, -1, -1, SPAWN);

						PutPlayerInVehicle(playerid, PrivCar[playerid], 0);
						dDodajKase(playerid,-100000);
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Roadtrain\n"C_NIEBIESKI"Cena: "C_ZOLTY"100000$");
					}
				}
			}
			return 1;
		}

		if(dialogid == 5010)
		{
		    if(response)
			{
			    switch(listitem)
			    {
			        case 0:
			        {
	        			new Float: X, Float: Y, Float: Z, Float:Ang;
						DestroyVehicle(PrivNaczepa[playerid]);
						GetPlayerPos(playerid, X, Y, Z);
						GetPlayerFacingAngle(playerid,Ang);
						PrivNaczepa[playerid] = CreateVehicle(591, X, Y , Z, Ang, -1, -1, SPAWN);
						PutPlayerInVehicle(playerid, PrivNaczepa[playerid], 0);
						LinkVehicleToInterior(PrivNaczepa[playerid], GetPlayerInterior(playerid));
	                    Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Article Trailer\n"C_NIEBIESKI"Cena: "C_ZOLTY"0$");
					}
					case 1:
			        {
	        			new Float: X, Float: Y, Float: Z, Float:Ang;
						DestroyVehicle(PrivNaczepa[playerid]);
						GetPlayerPos(playerid, X, Y, Z);
						GetPlayerFacingAngle(playerid,Ang);
						PrivNaczepa[playerid] = CreateVehicle(450, X, Y , Z, Ang, -1, -1, SPAWN);
						PutPlayerInVehicle(playerid, PrivNaczepa[playerid], 0);
						LinkVehicleToInterior(PrivNaczepa[playerid], GetPlayerInterior(playerid));
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Article Trailer 2\n"C_NIEBIESKI"Cena: "C_ZOLTY"0$");
					}
					case 2:
			        {
	        			new Float: X, Float: Y, Float: Z, Float:Ang;
						DestroyVehicle(PrivNaczepa[playerid]);
						GetPlayerPos(playerid, X, Y, Z);
						GetPlayerFacingAngle(playerid,Ang);
						PrivNaczepa[playerid] = CreateVehicle(591, X, Y , Z, Ang, -1, -1, SPAWN);
						PutPlayerInVehicle(playerid, PrivNaczepa[playerid], 0);
						LinkVehicleToInterior(PrivNaczepa[playerid], GetPlayerInterior(playerid));
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Article Trailer 3\n"C_NIEBIESKI"Cena: "C_ZOLTY"0$");
					}
					case 3:
			        {
	        			new Float: X, Float: Y, Float: Z, Float:Ang;
						DestroyVehicle(PrivNaczepa[playerid]);
						GetPlayerPos(playerid, X, Y, Z);
						GetPlayerFacingAngle(playerid,Ang);
						PrivNaczepa[playerid] = CreateVehicle(584, X, Y , Z, Ang, -1, -1, SPAWN);
						PutPlayerInVehicle(playerid, PrivNaczepa[playerid], 0);
						LinkVehicleToInterior(PrivNaczepa[playerid], GetPlayerInterior(playerid));
						Info(playerid, ""C_ZIELONY"Informacja o kupionym pojezdzie\n\n"C_NIEBIESKI"Nazwa: "C_ZOLTY"Petrol Trailer\n"C_NIEBIESKI"Cena: "C_ZOLTY"0$");
					}
				}
			}
			return 1;
		}
		return 1;
	}

IsTruckTrailer(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 435, 450, 591, 584, 611:
		{
			return 1;
		}
	}
	return 0;
}

CMD:tar(playerid, cmdtext[])
{
	ShowPlayerDialog(playerid, GUI_TARYFIKATOR, DIALOG_STYLE_LIST, "Taryfikator Taxi", ""C_ZIELONY"Wlacz\n"C_CZERWONY"Wylacz\n"C_ZOLTY"Zeruj\n=========================================\n"C_ZIELONY"Taryfa", "Wybierz", "Anuluj");
	return 1;
}

forward TarOn(playerid);
public TarOn(playerid)
{
	TarTim[playerid] = SetTimerEx("TarPlus",5000,1,"d",playerid);
	return 1;
}

forward TarOff(playerid);
public TarOff(playerid)
{
	KillTimer(TarTim[playerid]);
}

forward TarZer(playerid);
public TarZer(playerid)
{
	new string[60];
	format(string, sizeof string,"~y~Naleznosc: ~w~%d$", (Naleznosc[playerid]=0));
 	TextDrawSetString(Nal[playerid],string);
}

function TarPlus(playerid)
{
	new string[60];
	format(string, sizeof string,"~y~Naleznosc: ~w~%d$", (Naleznosc[playerid]+=2));
 	TextDrawSetString(Nal[playerid],string);
}



	CMD:stoj(playerid, cmdtext[])
	{
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj /stoj <id gracza>");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Probujesz zatrzymac sam siebie ??!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    GInfo(playa,"~r~Policja San Andreas~n~~y~Prosze sie zatrzymac i zjechac na pobocze !!",1);
		}
		else
		{
   			SendClientMessage(playerid, KOLOR_CZERWONY, "Niepoprawne id gracza");
		}
		return 1;
	}

	/*
	CMD:att(playerid, cmdtext[])
	{
		SetPlayerAttachedObject( playerid, 0, 3528, 1, 0.000000, 0.811655, -0.425397, 93.877960, 358.891479, 355.196624, 1.000000, 1.000000, 1.000000 ); // vgsEdragon - smokmotor
  		return 1;
	}
	*/

	forward Reklama(playerid);
	public Reklama(playerid)
	{
	    SendClientMessageToAll(KOLOR_CZERWONY, "==================== Reklama ====================");
	    SendClientMessageToAll(KOLOR_ZIELONY,  "Zapraszamy na forum: www.Hard-Truck.pl");
	    SendClientMessageToAll(KOLOR_CZERWONY, "=================================================");
	    return 1;
	}

	stock Koloruj(textx[])
	{
    	enum colorEnum
    	{
    		colorName[16],
     		colorID[9],
    	};
    	new colorInfo[][colorEnum] = {
    	{ "BLUE",           "{0049FF}" },
    	{ "PINK",           "{E81CC9}" },
    	{ "YELLOW",         "{DBED15}" },
    	{ "LIGHTGREEN",     "{8CED15}" },
    	{ "LIGHTBLUE",      "{15D4ED}" },
    	{ "RED",            "{FF0000}" },
    	{ "GREY",           "{BABABA}" },
    	{ "WHITE",          "{FFFFFF}" },
    	{ "ORANGE",         "{DB881A}" },
    	{ "GREEN",          "{37DB45}" },
    	{ "BROWN",          "{153510}" },
    	{ "BLACK",          "{000000}" },
    	{ "DARKGREEN",      "{6EF83C}" },
    	{ "DARKBLUE",       "{1B1BE0}" },
    	{ "CYAN",           "{00FFEE}" },
    	{ "LIME",           "{B7FF00}" },
    	{ "PURPLE",         "{7340DB}" }
    	};
    	new stringKOLORUJ[16+2];
		new znacznik,text[ROZMIAR_TEKSTU+32];

		strmid(text,textx,0,ROZMIAR_TEKSTU,sizeof(text));
		for(new x=0; x<sizeof(colorInfo); x++)
		{
	    	format(stringKOLORUJ,sizeof(stringKOLORUJ),"[%s]",colorInfo[x][colorName]);
  			znacznik = strfind(text, stringKOLORUJ, true);
			if(znacznik > -1)
			{
				strdel(text, znacznik, znacznik + strlen(stringKOLORUJ));
				strins(text, colorInfo[x][colorID], znacznik,sizeof(colorInfo));
			}
		}
		return text;
	}

	CMD:vip(playerid,params[])
	{
		if(!IsVip(playerid)) return Info(playerid, ""C_NIEBIESKI"Aby zakupic "C_ZOLTY"VIP'a "C_NIEBIESKI" wyslij sms wedlug podanego nizej wzoru\n\nNa tydzien - sms "C_CZERWONY"SH5.1060 "C_NIEBIESKI"pod nr "C_CZERWONY"75550\n"C_NIEBIESKI"Na miesiac - sms "C_CZERWONY"SH9.1060 "C_NIEBIESKI"pod nr "C_CZERWONY"79550\n\n"C_ZIELONY"Nastepnie zglos sie pod numer GG: 34773974 lub na forum do Inferno");
		PokazCzas(playerid);
		return 1;
	}
	COMMAND:givevip(playerid,cmdtext[])
	{
	  return cmd_dajvip(playerid,cmdtext);
	}
	COMMAND:setvip(playerid,cmdtext[])
	{
	  return cmd_dajvip(playerid,cmdtext);
	}

	CMD:dajvip(playerid,params[])
	{
		new userid, Days, Hours, timeVip, Msg[128];

		if (!ToAdminLevel(playerid, 3)) return 0;
		if (sscanf(params, "ddd", userid, Days, Hours)) return SendClientMessage(playerid, 0xFF0000AA, "Uzyj: /dajvip [ID gracza] [Dni] [Godziny]"),1;
		if (IsPlayerConnected(userid))
		{
  			format(forma,sizeof forma,"Truck/VIP/%s.ini",PlayerName(userid));
			DOF_CreateFile(forma);
			timeVip = (Days * 86400) + (Hours * 3600) + gettime();
			DOF_SetInt(forma,"VipCzas",timeVip);


			format(Msg, 128, "Dosta≥eú VIP'a na %i Dni i %i Godzin ! Komendy: /vpomoc", Days, Hours);
			SendClientMessage(playerid, KOLOR_BIALY, Msg);
			DOF_SetInt(forma,"Vip",1);
			DOF_SaveFile();
		}
		return 1;
	}

	stock PokazCzas(playerid)
	{
		new CzasPrem, Days, Hours, Minutes;
		format(forma,sizeof forma,"Truck/VIP/%s.ini",PlayerName(playerid));
		CzasPrem = DOF_GetInt(forma,"VipCzas") - gettime();


		if (CzasPrem >= 86400)
		{
			Days = CzasPrem / 86400;
			CzasPrem = CzasPrem - (Days * 86400);
		}
		if (CzasPrem >= 3600)
		{
			Hours = CzasPrem / 3600;
			CzasPrem = CzasPrem - (Hours * 3600);
		}
		if (CzasPrem >= 60)
		{
			Minutes = CzasPrem / 60;
			CzasPrem = CzasPrem - (Minutes * 60);
		}

		new ff[128];
		format(ff,sizeof ff,"Konto VIP aktywne przez: %i Dni, %i Godzin, %i Minut",Days,Hours,Minutes);
		SendClientMessage(playerid,-1,ff);
	}

	stock IsVip(playerid)
	{
		format(forma,sizeof forma,"Truck/VIP/%s.ini",PlayerName(playerid));
		if(DOF_FileExists(forma) && DOF_GetInt(forma,"Vip") == 1) return 1;
		return 0;
	}

	stock PlayerName(playerid)
	{
		new name[24];
		GetPlayerName(playerid,name,sizeof name);
		return name;
	}

	CMD:vpomoc(playerid, params[])
	{
     	SendClientMessage(playerid, KOLOR_ZOLTY, "=============== "C_CZERWONY"KOMENDY VIPA"C_ZOLTY" ===============");
	    SendClientMessage(playerid, KOLOR_NIEBIESKI, "/vip - sprawdzasz waønoúÊ vipa.");
	    SendClientMessage(playerid, KOLOR_NIEBIESKI, "/vnrg - przywo≥ujesz prywatne nrg.");
	    SendClientMessage(playerid, KOLOR_NIEBIESKI, "/vnrgd - usÛwa stworzone nrg.");
	    SendClientMessage(playerid, KOLOR_NIEBIESKI, "/vsay <tekst> - (/vann <tekst>) og≥oszenie VIP'a.");
	    SendClientMessage(playerid, KOLOR_NIEBIESKI, "/vnapraw - naprawiasz pojazd za 500$.");
	    SendClientMessage(playerid, KOLOR_NIEBIESKI, "/vneon - neony do poziomy.");
	    SendClientMessage(playerid, KOLOR_NIEBIESKI, "/vkick - kickujesz gracza.");
	    SendClientMessage(playerid, KOLOR_ZOLTY, "============================================");
	    return 1;
	}

	CMD:vnrg(playerid, params[])
	{
	    if(!IsVip(playerid))
	    {
	        Info(playerid, ""C_CZERWONY"Komenda tylko dla VIP'a");
	        return 1;
		}
		new Float: X, Float: Y, Float: Z, Float:Ang;
		if(PVeh[playerid] > 0)
		{
			if(GetPlayerVehicleID(playerid) ==  PVeh[playerid])
			{
				Info(playerid, ""C_CZERWONY"Jestes juz w swoim nrg");
				return 1;
			}

			if(IsPlayerInAnyVehicle(playerid))
			{
				Info(playerid, ""C_CZERWONY"Jestes juz w pojezdzie");
				return 1;
			}

			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid,Ang);
			PutPlayerInVehicle(playerid, PVeh[playerid], 0);
			SetVehiclePos(PVeh[playerid], X, Y, Z);
			SetVehicleZAngle(PVeh[playerid],Ang);
			SetVehicleHealth(PVeh[playerid],  1000.0);
			LinkVehicleToInterior(PVeh[playerid], GetPlayerInterior(playerid));
			SendClientMessage(playerid,KOLOR_ZIELONY, "Hard Truck: Prywatne NRG-500 przywo≥ane!");
		}
		else
		{
			if(IsPlayerInAnyVehicle(playerid))
				RemovePlayerFromVehicle(playerid);

			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid,Ang);
			PVeh[playerid] = CreateVehicle(522, X, Y , Z, Ang, 0,1, 5000000);
			PutPlayerInVehicle(playerid, PVeh[playerid], 0);
			LinkVehicleToInterior(PVeh[playerid], GetPlayerInterior(playerid));
			SendClientMessage(playerid,KOLOR_ZIELONY, "Hard Truck: Stworzy≥eú prywatne NRG-500, aby je ponownie przywo≥aÊ wpisz /nrg!");
			SetVehicleParamsForPlayer(PVeh[playerid], playerid, 0, 0);
			for(new i=0; i <= MAX_PLAYERS; i++)
				if (IsPlayerConnected(i) && i != playerid)
					SetVehicleParamsForPlayer(PVeh[playerid], i, 0, 1);
		}
		return 1;
	}

	CMD:vnrgd(playerid, params[])
	{
	    if(!IsVip(playerid))
	    {
	        Info(playerid, ""C_CZERWONY"Komenda tylko dla VIP'a");
	        return 1;
		}
		DestroyVehicle(PVeh[playerid]);
		SendClientMessage(playerid, KOLOR_ZIELONY, "UsuniÍto prywatne nrg.");
		return 1;
	}

	COMMAND:ann(playerid,params[])
	{
		return cmd_say(playerid,params);
	}

	CMD:say(playerid, params[])
	{
		if(!ToAdminLevel(playerid,2))
		{
	    	Info(playerid, ""C_CZERWONY"Komenda dostÍpna tylko dla administratora poziom 2.");
	    	return 1;
		}

		new TextOgl[255];
		if(!sscanf(params, "s[255]", TextOgl))
		{
			Info(playerid, ""C_CZERWONY"Wpisz: /say [tekst]");
			return 1;
		}

		format(dstring, sizeof(dstring),"~r~(%d)%s ~w~%s",playerid,Nick(playerid),TextOgl);
		NapisText(dstring);
		return 1;
	}

	COMMAND:vann(playerid,params[])
	{
		return cmd_vsay(playerid,params);
	}

	CMD:vsay(playerid, params[])
	{
		if(!IsVip(playerid))
		{
	    	Info(playerid, ""C_CZERWONY"Komenda dostÍpna tylko dla VIP'a.");
	    	return 1;
		}

		new TextOgl[255];
		if(!sscanf(params, "s[255]", TextOgl))
		{
			Info(playerid, ""C_CZERWONY"Wpisz: /vsay [tekst]");
			return 1;
		}

		format(dstring, sizeof(dstring),"~r~(%d)%s ~w~%s",playerid,Nick(playerid),TextOgl);
		NapisText(dstring);
		return 1;
	}

	CMD:colors(playerid, params[])
	{
		Info(playerid, "{0049FF}[BLUE]\n{E81CC9}[PINK]\n{DBED15}[YELLOW]\n{8CED15}[LIGHTGREEN]\n{15D4ED}[LIGHTBLUE]\n{FF0000}[RED]\n{BABABA}[GREY]\n{FFFFFF}[WHITE]\n{DB881A}[ORANGE]\n{37DB45}[GREEN]\n{153510}[BROWN]\n{000000}[BLACK]\n{6EF83C}[DARKGREEN]\n{1B1BE0}[DARKBLUE]\n{00FFEE}[CYAN]\n{B7FF00}[LIME]\n{7340DB}[PURPLE]");
		return 1;
	}

	CMD:vnapraw(playerid, cmdtext[])
	{
	    if(!IsVip(playerid))
	    {
	        Info(playerid,"Komenda tylko dla vipa!");
	        return 1;
		}
	    if(GetPlayerState(playerid)!=PLAYER_STATE_DRIVER)
	    {
	        Info(playerid,""C_CZERWONY"Nie jesteú kierowcπ øadnego pojazdu!");
            return 1;
	    }
	    if(GetPlayerSpeed(playerid)>1)
	    {
	    	Info(playerid,""C_CZERWONY"Musisz siÍ zatrzymaÊ, aby uøyÊ tej komendy!");
            return 1;
	    }
	    new Float:HP;
	    GetVehicleHealth(GetPlayerVehicleID(playerid),HP);
	    if(HP>=999.0)
	    {
	    	Info(playerid,""C_CZERWONY"Ten pojazd jest w perfekcyjnym stanie!");
            return 1;
	    }
		new Float:Pos[3];
		GetVehiclePos(GetPlayerVehicleID(playerid),Pos[0],Pos[1],Pos[2]);
		KillTimer(VNaprawTimer[playerid]);
		VNaprawTimer[playerid]=SetTimerEx("VNaprawPojazd",1000,false,"iifff",playerid,GetPlayerVehicleID(playerid),Pos[0],Pos[1],Pos[2]);
  		return 1;
	}

	CMD:vkick(playerid, cmdtext[])
	{
	    if(!IsVip(playerid)) return 1;
		new tmp[64],idx;
		tmp = strtok(cmdtext, idx);
		if(isnull(tmp))
		{
			Info(playerid,"Uøyj: /vkick (ID) (powÛd)");
			return 1;
 		}
	 	new playa = strval(tmp);
	 	if(playa==playerid){ Info(playerid,"Nie moøesz wrzuciÊ sam siebie!"); return 1; }
		if(IsPlayerConnected(playa))
		{
		    if(ToAdminLevel(playerid,1))
		    {
				Info(playerid,""C_CZERWONY"Nie moøesz wyrzuciÊ admina!");
				return 1;
		    }
			new text[80];
			text=strrest(cmdtext,idx);
			if(isnull(text))
			{
				Info(playerid,"Uøyj: /vkick (ID) (powÛd)");
				return 1;
			}
		    format(dstring, sizeof(dstring),"Zosta≥eú wyrzucony przez %s(%d) za: %s",Nick(playerid),playerid,text);
		    Info(playa,dstring);
		    format(dstring, sizeof(dstring),"~r~(%d)%s zostal wyrzucony~n~~y~przez VIPA: (%d)%s~n~~w~Za: %s",playa,Nick(playa),playerid,Nick(playerid),text);
		    NapisText(dstring);
		    dKick(playa);
		}
		else
		{
			Info(playerid,"Nie poprawne id gracza!");
		}
		return 1;
	}

	public Zones_Update()
	{
		new string[30];
		foreach(Player, u)
		{
			for(new i = 0; i != sizeof(gSAZones); i++ )
	 		{
	 		    if(IsPlayerInArea(u, gSAZones[i][SAZONE_AREA][0], gSAZones[i][SAZONE_AREA][2], gSAZones[i][SAZONE_AREA][1], gSAZones[i][SAZONE_AREA][3]))
				{
					format(string,sizeof(string),"~r~GPS: ~b~%s", gSAZones[i][SAZONE_NAME]);
					TextDrawSetString(Zones[u], string);
				}
				else
				{
					TextDrawSetString(Zones[u], "~r~GPS: ~b~Laczenie...");
				}
			}
		}
		return 1;
	}

	IsPlayerInArea(playerid, Float:minx, Float:maxx, Float:miny, Float:maxy)
	{
	    new Float:x, Float:y, Float:z;
	    GetPlayerPos(playerid, x, y, z);
	    if (x > minx && x < maxx && y > miny && y < maxy) return 1;
	    return 0;
	}

	stock IsPlayerInZone(playerid, zone[]) //Credits to Cueball, Betamaster, Mabako, and Simon (for finetuning).
	{
		new TmpZone[MAX_ZONE_NAME];
		GetPlayer3DZone(playerid, TmpZone, sizeof(TmpZone));
		for(new i = 0; i != sizeof(gSAZones); i++)
		{
			if(strfind(TmpZone, zone, true) != -1)
			return 1;
		}
		return 0;
	}

	stock GetPlayer2DZone(playerid, zone[], len) //Credits to Cueball, Betamaster, Mabako, and Simon (for finetuning).
	{
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
	 	for(new i = 0; i != sizeof(gSAZones); i++ )
	 	{
			if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
			{
			    return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
			}
		}
		return 0;
	}

	stock GetPlayer3DZone(playerid, zone[], len) //Credits to Cueball, Betamaster, Mabako, and Simon (for finetuning).
	{
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
 		for(new i = 0; i != sizeof(gSAZones); i++ )
 		{
			if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4] && z >= gSAZones[i][SAZONE_AREA][2] && z <= gSAZones[i][SAZONE_AREA][5])
			{
			    return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
			}
		}
		return 0;
	}

//===================================         TUNE         ===================================

	CMD:tune(playerid, cmdtext[])
	{
	    if (!ToAdminLevel(playerid, 2))
	        return 1;
	    if(!DoInRange(10.0, playerid,1619.8413085938,1555.2446289063,9.8090887069702))
	    {
	        Info(playerid, "Nie jestes w tuningu");
		}
		if(!IsPlayerInAnyVehicle(playerid))
		{
	    	Info(playerid, "Nie jesteú w pojeüdzie.");
	    	return 1;
		}

		if(GetPlayerVehicleSeat(playerid) != 0)
		{
	    	Info(playerid, "Musisz byÊ na miejscu kierowcy.");
	    	return 1;
		}

		if(dWyswietlKase(playerid) < TUNE_PRICE)
		{
	    	Info(playerid, "Tuning kosztuje 2000$. Nie masz tyle kasy!");
	    	return 1;
		}

		if(DoInRange(10.0, playerid,1619.8413085938,1555.2446289063,9.8090887069702))
	    {
			dDodajKase(playerid,-TUNE_PRICE);
			Info(playerid, "Stuningowa≥eú pojazd.");
			TunePlayerVehicle(playerid);
		}

		return 1;
	}

	CMD:givecash(playerid, params[])
	{
    	new player,
        	ilosc,
			Msg[128];
    	if (!ToAdminLevel(playerid, 3))
        	return SendClientMessage(playerid, 0xFF0000FF, "Nie jesteú administratorem poziom 3!");

    	if(sscanf(params, "dd", player, ilosc))
        	return SendClientMessage(playerid, 0xFF0000FF, "/givecash (id) (ilosc)");

     	if(!IsPlayerConnected(player))
        	return SendClientMessage(playerid, 0xFF0000FF, "Ten gracz nie jest pod≥πczony!");
    	dDodajKase(player,ilosc);
    	format(Msg, 128, ""C_CZERWONY"Dosta≥eú "C_ZIELONY"%d$ "C_CZERWONY"od admin "C_BIALY"("C_CZERWONY"%d"C_BIALY")"C_CZERWONY"%s", ilosc,player,Nick(player));
		Info(player, Msg);
		format(Msg, 128, ""C_CZERWONY"Da≥eú "C_ZIELONY"%d$ "C_CZERWONY"graczowi "C_BIALY"("C_CZERWONY"%d"C_BIALY")"C_CZERWONY"%s", ilosc,playerid,Nick(playerid));
		Info(playerid, Msg);
    	return 1;
	}

	CMD:v(playerid, params[])
	{
    	new vehid;
    	if (!ToAdminLevel(playerid, 3))
        	return SendClientMessage(playerid, 0xFF0000FF, "Nie jesteú administratorem poziom 3!");

    	if(sscanf(params, "d", vehid))
        	return SendClientMessage(playerid, 0xFF0000FF, "/v (id pojazdu)");

    	new Float: X, Float: Y, Float: Z, Float:Ang;
		GetPlayerPos(playerid, X, Y, Z);
		GetPlayerFacingAngle(playerid,Ang);
		CreateVehicle(vehid, X+1, Y+1 , Z, Ang, 0,1, SPAWN);
    	SendClientMessage(playerid, KOLOR_ZIELONY, "Stworzy≥eú pojazd, aby usunπÊ go wpisz /vd");
    	return 1;
	}

	CMD:givehp(playerid, params[])
	{
    	new player,
        	ilosc,
			Msg[128];
    	if (!ToAdminLevel(playerid, 2))
        	return SendClientMessage(playerid, 0xFF0000FF, "Nie jesteú administratorem poziom 2!");

    	if(sscanf(params, "dd", player, ilosc))
        	return SendClientMessage(playerid, 0xFF0000FF, "/givehp (id) (ilosc hp)");

     	if(!IsPlayerConnected(player))
        	return SendClientMessage(playerid, 0xFF0000FF, "Ten gracz nie jest pod≥πczony!");

    	dDodajHP(player,ilosc);
    	format(Msg, 128, "Admin (%d)%s da≥ Ci %d HP",playerid,Nick(playerid), ilosc);
		SendClientMessage(player, KOLOR_ZIELONY, Msg);
    	return 1;
	}

	CMD:heal(playerid, params[])
	{
    	new player,
			Msg[128];
    	if (!ToAdminLevel(playerid, 2))
        	return SendClientMessage(playerid, 0xFF0000FF, "Nie jesteú administratorem poziom 2!");

    	if(sscanf(params, "d", player))
        	return SendClientMessage(playerid, 0xFF0000FF, "/heal (id)");

     	if(!IsPlayerConnected(player))
        	return SendClientMessage(playerid, 0xFF0000FF, "Ten gracz nie jest pod≥πczony!");

    	dUstawHP(player,100);
    	format(Msg, 128, "Admin (%d)%s uzdrowi≥ CiÍ",playerid,Nick(playerid));
		SendClientMessage(player, KOLOR_ZIELONY, Msg);
    	return 1;
	}

	CMD:armour(playerid, params[])
	{
    	new player,
			Msg[128];
    	if (!ToAdminLevel(playerid, 2))
        	return SendClientMessage(playerid, 0xFF0000FF, "Nie jesteú administratorem poziom 2!");

    	if(sscanf(params, "d", player))
        	return SendClientMessage(playerid, 0xFF0000FF, "/armour (id)");

     	if(!IsPlayerConnected(player))
        	return SendClientMessage(playerid, 0xFF0000FF, "Ten gracz nie jest pod≥πczony!");

    	dUstawArmor(player,100);
    	format(Msg, 128, "Admin (%d)%s uzdrowi≥ CiÍ",playerid,Nick(playerid));
		SendClientMessage(player, KOLOR_ZIELONY, Msg);
    	return 1;
	}

	CMD:disarm(playerid, params[])
	{
    	new player,
			Msg[128];
    	if (!ToAdminLevel(playerid, 1))
        	return SendClientMessage(playerid, 0xFF0000FF, "Nie jesteú administratorem poziom 1!");

    	if(sscanf(params, "d", player))
        	return SendClientMessage(playerid, 0xFF0000FF, "/disarm (id)");

     	if(!IsPlayerConnected(player))
        	return SendClientMessage(playerid, 0xFF0000FF, "Ten gracz nie jest pod≥πczony!");
        GivePlayerWeapon(playerid, 0, 0);
    	format(Msg, 128, "Admin (%d)%s zabra≥ Ci wszystkie bronie",playerid,Nick(playerid));
		SendClientMessage(player, KOLOR_ZIELONY, Msg);
    	return 1;
	}

	CMD:givegun(playerid, params[])
	{
    	new player,
        	bron,
        	ammo,
			Msg[128];
    	if (!ToAdminLevel(playerid, 2))
        	return SendClientMessage(playerid, 0xFF0000FF, "Nie jesteú administratorem poziom 3!");

    	if(sscanf(params, "ddd", player, bron, ammo))
        	return SendClientMessage(playerid, 0xFF0000FF, "/givegun (id) (id broni) (ammo)");

     	if(!IsPlayerConnected(player))
        	return SendClientMessage(playerid, 0xFF0000FF, "Ten gracz nie jest pod≥πczony!");

    	GivePlayerWeapon(player,bron,ammo);
    	format(Msg, 128, "Admin (%d)%s da≥ Ci bron o id %d z %d ammo",playerid,Nick(playerid), bron, ammo);
		SendClientMessage(player, KOLOR_ZIELONY, Msg);
    	return 1;
	}

	forward PokazFirmaTD(id);
	public PokazFirmaTD(id)
	{
		TextDrawShowForPlayer(id, NapisFirma[id]);
		TextDrawShowForPlayer(id, FirmaNazwa[id]);
		TextDrawShowForPlayer(id, FirmaMisja[id]);
		TextDrawShowForPlayer(id, FirmaDost[id]);
		TextDrawShowForPlayer(id, FirmaPoziom[id]);
		return 1;
	}

	forward UkryjFirmaTD(id);
	public UkryjFirmaTD(id)
	{
		TextDrawHideForPlayer(id, NapisFirma[id]);
		TextDrawHideForPlayer(id, FirmaNazwa[id]);
		TextDrawHideForPlayer(id, FirmaMisja[id]);
		TextDrawHideForPlayer(id, FirmaDost[id]);
		TextDrawHideForPlayer(id, FirmaPoziom[id]);
		return 1;
	}

	stock Toll(playerid, Float:x, Float:y, Float:z)
	{
		if(IsPlayerInRangeOfPoint(playerid, 10, x, y, z))
		{
		    if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER)
		    {
		        if(!ToPD(playerid))
		        {
				    if(GetPVarInt(playerid, "PunktyToll") >= 60)
				    {
				        if(juzplacil[playerid]==0)
				        {
				            new punkciki = GetPVarInt(playerid, "PunktyToll");
			           	    SetPVarInt(playerid, "PunktyToll", punkciki-10);


				            new string[128];
				    		format(string, sizeof(string),""C_CZERWONY"ViaToll: "C_BIALY"Zap≥aci≥eú "C_ZIELONY"10 "C_BIALY"punktÛw ViaToll. TwÛj stan konta wynosi: "C_ZIELONY"%d", GetPVarInt(playerid, "PunktyToll"));
				    		SendClientMessage(playerid, KOLOR_BIALY, string);
				    		Zaplacil[playerid] = SetTimerEx("ZaplacilTim", 3000, 0, "d", playerid);
				    		juzplacil[playerid] = 1;
				    		TextDrawSetString(ViaTollTD[playerid], "~g~v");
				    		TextDrawShowForPlayer(playerid, ViaTollTD[playerid]);
						}
					}
				    else if(GetPVarInt(playerid, "PunktyToll") >= 10)
				    {
				        if(juzplacil[playerid]==0)
				        {
				            new punkciki = GetPVarInt(playerid, "PunktyToll");
			           	    SetPVarInt(playerid, "PunktyToll", punkciki-10);


				            new string[128];
				    		format(string, sizeof(string),""C_CZERWONY"ViaToll: "C_BIALY"Zap≥aci≥eú "C_ZIELONY"10 "C_BIALY"punktÛw ViaToll. TwÛj stan konta wynosi: "C_ZIELONY"%d", GetPVarInt(playerid, "PunktyToll"));
				    		SendClientMessage(playerid, 0xFFFFFF, string);
				    		Zaplacil[playerid] = SetTimerEx("ZaplacilTim", 3000, 0, "d", playerid);
				    		juzplacil[playerid] = 1;
				    		TextDrawSetString(ViaTollTD[playerid], "~y~!");
				    		TextDrawShowForPlayer(playerid, ViaTollTD[playerid]);
						}
					}
					else if(GetPVarInt(playerid, "PunktyToll") <= 9)
				    {
				        if(juzplacil[playerid]==0)
				        {
				            new string[128];
				    		format(string, sizeof(string),""C_CZERWONY"ViaToll warning: "C_BIALY"Gracz ("C_ZIELONY"%d"C_BIALY") "C_ZIELONY"%s "C_BIALY"nie zap≥aci≥ za przejazd", playerid, Nick(playerid));
				    		SendClientMessageToPOLICJA(0xFFFFFF, string);
				    		SendClientMessage(playerid, 0xFFFFFF, ""C_CZERWONY"ViaToll warning: "C_BIALY"Nie posiadasz wystarczajπcej iloúci punktÛw "C_ZIELONY"ViaToll"C_BIALY" by zap≥aciÊ za przejazd. Policja zosta≥a zawiadomiona!.");

				    		Zaplacil[playerid] = SetTimerEx("ZaplacilTim", 3000, 0, "d", playerid);
				    		juzplacil[playerid] = 1;
				    		TextDrawSetString(ViaTollTD[playerid], "~r~x");
				    		TextDrawShowForPlayer(playerid, ViaTollTD[playerid]);
						}
					}
				}
			}
		}
		return 0;
	}

 	CMD:toll(playerid, params[])
	{
		ShowPlayerDialog(playerid,GUI_VIATOLL,DIALOG_STYLE_LIST,"ViaTol - menu","Stan Konta\nKup ViaToll","Kup","Wyjdü");
		return 1;
	}

	forward HideViaTollTD(playerid);
	public HideViaTollTD(playerid)
	{
		KillTimer(ViaTollTextDraw[playerid]);
		TextDrawHideForPlayer(playerid, ViaTollTD[playerid]);
		return 1;
	}

	forward ZaplacilTim(playerid);
	public ZaplacilTim(playerid)
	{
		KillTimer(Zaplacil[playerid]);
		juzplacil[playerid] = 0;
		TextDrawHideForPlayer(playerid, ViaTollTD[playerid]);
		return 1;
	}

	stock SendClientMessageToPOLICJA(color, message[])
	{
		foreach (Player, a)
		{
			if(ToPD(a))
        	{
				SendClientMessage(a, color, message);
			}
		}
		return 1;
	}

 	CMD:tpto(playerid, params[])
	{
    	new player;

   		if(!ToAdminLevel(playerid, 2))
		    return Info(playerid, ""C_CZERWONY"Komenda tylko dla Admina");

    	if(sscanf(params, "d", player))
        	return SendClientMessage(playerid, 0xFF0000FF, "/tp (id)");
		new Float: X, Float: Y, Float: Z;
		GetPlayerPos(player, X, Y, Z);
		SetPlayerPos(playerid, X, Y, Z);
		SendClientMessage(playerid, KOLOR_ZIELONY, "Teleportowano...");
		return 1;
	}

 	CMD:tphere(playerid, params[])
	{
    	new player;

   		if(!ToAdminLevel(playerid, 2))
		    return Info(playerid, ""C_CZERWONY"Komenda tylko dla Admina");

    	if(sscanf(params, "d", player))
        	return SendClientMessage(playerid, 0xFF0000FF, "/tp (id)");
		new Float: X, Float: Y, Float: Z;
		GetPlayerPos(playerid, X, Y, Z);
		SetPlayerPos(player, X, Y, Z);
		SendClientMessage(playerid, KOLOR_ZIELONY, "Teleportowano...");
		return 1;
	}

	CMD:swieta(playerid, params[])
	{
	    new player,
	        liczba;

		if(!ToAdminLevel(playerid, 3))
		    return Info(playerid, ""C_CZERWONY"Komenda tylko dla Head Admina");

		else if(sscanf(params, "dd", player, liczba))
		    return Info(playerid, "Uøyj: /swieta <id gracza> <typ>\n\nTypy:\n\t1. Skin\n\t2. Truck\n\t3. Naczepa\n\t4. DeskaSnowboardowa\n\t5. Skuter");

		else if(IsPlayerConnected(player))
		{
			if(liczba > 0)
			{
				if(liczba == 1)
				{
				    SetPlayerSkin(player, 85);
				    SendClientMessage(playerid, KOLOR_ZIELONY, "Zmieni≥eú skin");
				}
				else if(liczba == 2)
				{
					new Float: X, Float: Y, Float: Z;
					GetPlayerPos(player, X, Y, Z);
					CreateVehicle(515, X, Y, Z, 0, 0, 0, SPAWN);
					SendClientMessage(playerid, KOLOR_ZIELONY, "Stworzy≥eú wÛz");
				}
				else if(liczba == 3)
				{
					new Float: X, Float: Y, Float: Z;
					GetPlayerPos(player, X, Y, Z);
					CreateVehicle(435, X, Y, Z, 0, 0, 0, SPAWN);
					SendClientMessage(playerid, KOLOR_ZIELONY, "Stworzy≥eú naczepe");
				}
				else if(liczba == 4)
				{
					new Float: X, Float: Y, Float: Z;
					GetPlayerPos(player, X, Y, Z);
					CreateVehicle(448, X, Y, Z, 0, 0, 0, SPAWN);
					SendClientMessage(playerid, KOLOR_ZIELONY, "Stworzy≥eú deskesnowboardowa");
				}
				else if(liczba == 5)
				{
					new Float: X, Float: Y, Float: Z;
					GetPlayerPos(player, X, Y, Z);
					CreateVehicle(471, X, Y, Z, 0, 0, 0, SPAWN);
					SendClientMessage(playerid, KOLOR_ZIELONY, "Stworzy≥eú Skuter");
				}
				else
				{
				    SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥y typ!");
				}
			}
			else
			{
			    SendClientMessage(playerid, KOLOR_CZERWONY, "Typ nie moøe byÊ niøszy od 0!");
			}
		}
		else
		{
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥e ID Gracza!");
		}
		return 1;
	}

	stock GivePlayerScore(playerid, scores)
	{
		SetPlayerScore(playerid, GetPlayerScore(playerid)+scores);
		return 1;
	}

	stock GetDistanceBetweenPoints(Float: x1, Float: y1, Float: z1, Float: x2, Float: y2, Float: z2)
	{
		new Float:dis;
		dis = floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
		return floatround(dis);
	}

	forward UsowaneBudynki(playerid);
	public UsowaneBudynki(playerid)
	{
	    //budowa mostu SF-LV
		RemoveBuildingForPlayer(playerid, 9686, -2681.4922, 1595.0078, 109.4375, 0.25);
		RemoveBuildingForPlayer(playerid, 9687, -2681.4922, 1684.4609, 120.4531, 0.25);
		RemoveBuildingForPlayer(playerid, 9688, -2681.5000, 1764.8438, 113.1172, 0.25);
		RemoveBuildingForPlayer(playerid, 9689, -2681.4922, 1684.4609, 120.4531, 0.25);
		RemoveBuildingForPlayer(playerid, 9690, -2681.4922, 1595.0078, 109.4375, 0.25);
		RemoveBuildingForPlayer(playerid, 9691, -2681.4922, 1847.9375, 120.0859, 0.25);
		RemoveBuildingForPlayer(playerid, 9693, -2681.4922, 1847.9375, 120.0859, 0.25);
		RemoveBuildingForPlayer(playerid, 9838, -2681.4922, 1595.0078, 109.4375, 0.25);
		RemoveBuildingForPlayer(playerid, 1290, -2681.5859, 1609.8828, 70.0938, 0.25);
		RemoveBuildingForPlayer(playerid, 1290, -2681.5859, 1860.7500, 72.1719, 0.25);
		RemoveBuildingForPlayer(playerid, 1290, -2681.5859, 1798.0313, 73.3281, 0.25);
		RemoveBuildingForPlayer(playerid, 1290, -2681.5859, 1923.4688, 69.8828, 0.25);
		RemoveBuildingForPlayer(playerid, 1290, -2681.5859, 1735.3125, 73.3438, 0.25);
		RemoveBuildingForPlayer(playerid, 1290, -2681.5859, 1672.6016, 72.3047, 0.25);

		//Area 59
		RemoveBuildingForPlayer(playerid, 3366, 276.6563, 2023.7578, 16.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 3366, 276.6563, 1989.5469, 16.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 3366, 276.6563, 1955.7656, 16.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 3267, 188.2422, 2081.6484, 22.4453, 0.25);
		RemoveBuildingForPlayer(playerid, 3277, 188.2422, 2081.6484, 22.4063, 0.25);
		RemoveBuildingForPlayer(playerid, 16294, 15.1797, 1719.3906, 21.6172, 0.25);
		RemoveBuildingForPlayer(playerid, 3267, 15.6172, 1719.1641, 22.4141, 0.25);
		RemoveBuildingForPlayer(playerid, 3277, 15.6016, 1719.1719, 22.3750, 0.25);
		RemoveBuildingForPlayer(playerid, 3267, 237.6953, 1696.8750, 22.4141, 0.25);
		RemoveBuildingForPlayer(playerid, 3277, 237.6797, 1696.8828, 22.3750, 0.25);
		RemoveBuildingForPlayer(playerid, 16293, 238.0703, 1697.5547, 21.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 16093, 211.6484, 1810.1563, 20.7344, 0.25);
		RemoveBuildingForPlayer(playerid, 16638, 211.7266, 1809.1875, 18.9844, 0.25);
		RemoveBuildingForPlayer(playerid, 3279, 262.0938, 1807.6719, 16.8203, 0.25);
		RemoveBuildingForPlayer(playerid, 1411, 347.1953, 1799.2656, 18.7578, 0.25);
		RemoveBuildingForPlayer(playerid, 1411, 342.9375, 1796.2891, 18.7578, 0.25);
		RemoveBuildingForPlayer(playerid, 16670, 330.7891, 1813.2188, 17.8281, 0.25);
		RemoveBuildingForPlayer(playerid, 3279, 113.3828, 1814.4531, 16.8203, 0.25);
		RemoveBuildingForPlayer(playerid, 3279, 165.9531, 1849.9922, 16.8203, 0.25);
		RemoveBuildingForPlayer(playerid, 1697, 220.3828, 1835.3438, 23.2344, 0.25);
		RemoveBuildingForPlayer(playerid, 1697, 228.7969, 1835.3438, 23.2344, 0.25);
		RemoveBuildingForPlayer(playerid, 1697, 236.9922, 1835.3438, 23.2344, 0.25);
		RemoveBuildingForPlayer(playerid, 16095, 279.1328, 1829.7813, 16.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 3280, 245.3750, 1862.3672, 20.1328, 0.25);
		RemoveBuildingForPlayer(playerid, 3280, 246.6172, 1863.3750, 20.1328, 0.25);
		RemoveBuildingForPlayer(playerid, 16094, 191.1406, 1870.0391, 21.4766, 0.25);
		RemoveBuildingForPlayer(playerid, 3279, 103.8906, 1901.1016, 16.8203, 0.25);
		RemoveBuildingForPlayer(playerid, 16096, 120.5078, 1934.0313, 19.8281, 0.25);
		RemoveBuildingForPlayer(playerid, 3279, 161.9063, 1933.0938, 16.8203, 0.25);
		RemoveBuildingForPlayer(playerid, 16671, 193.9531, 2051.7969, 20.1797, 0.25);
		RemoveBuildingForPlayer(playerid, 3279, 233.4297, 1934.8438, 16.8203, 0.25);
		RemoveBuildingForPlayer(playerid, 3279, 267.0625, 1895.2969, 16.8203, 0.25);
		RemoveBuildingForPlayer(playerid, 3268, 276.6563, 2023.7578, 16.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 3268, 276.6563, 1989.5469, 16.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 3268, 276.6563, 1955.7656, 16.6328, 0.25);
		RemoveBuildingForPlayer(playerid, 3267, 354.4297, 2028.4922, 22.4141, 0.25);
		RemoveBuildingForPlayer(playerid, 3277, 354.4141, 2028.5000, 22.3750, 0.25);
		RemoveBuildingForPlayer(playerid, 16668, 357.9375, 2049.4219, 16.8438, 0.25);
		RemoveBuildingForPlayer(playerid, 16669, 380.2578, 1914.9609, 17.4297, 0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 10822, -1336.8000,892.7999,57.9000,0.25);
		RemoveBuildingForPlayer(playerid, 3332, 583.0859, 368.8750, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 3332, 537.1953, 434.4063, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 3332, 445.4219, 565.4688, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 3332, 491.3125, 499.9375, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 16431, 475.1250, 537.4375, 17.5859, 0.25);
        RemoveBuildingForPlayer(playerid, 3331, 445.4219, 565.4688, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 16357, 475.1250, 537.4375, 17.5859, 0.25);
        RemoveBuildingForPlayer(playerid, 3331, 491.3125, 499.9375, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 3331, 537.1953, 434.4063, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 3331, 583.0859, 368.8750, 24.5547, 0.25);
        RemoveBuildingForPlayer(playerid, 4514, 440.0469, 587.4453, 19.7344, 0.25);
		
		
		//moja chata
		RemoveBuildingForPlayer(playerid, 13744, 1272.5938, -803.1094, 86.3594, 0.25);
		return 1;
	}

	CMD:zlecenie(playerid, params[])
	{
		if(!ToPD(playerid) && !ToPOMOC(playerid) && !ToLOT(playerid))
		{
		    new v=GetPlayerVehicleID(playerid);
		    if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)//ciÍøarowe
			{
		    	if(GetVehicleTrailer(v)==0)
		    	{
		        	Info(playerid,""C_CZERWONY"Nie masz podczepionej naczepy!");
	        		return 1;
		    	}
		    	new naczepa=GetVehicleModel(GetVehicleTrailer(v));
		    	if(naczepa==435||naczepa==450||naczepa==591||naczepa==584)
		    	{
					if(GetPVarInt(playerid, "etap") == 0)
					{
						new s[2600];
						strcat(s,""C_ZIELONY"Zboze"C_BEZOWY" - 540$\n");
						strcat(s,""C_ZIELONY"Dokumenty"C_BEZOWY" - 650$\n");
						strcat(s,""C_ZIELONY"Lampy"C_BEZOWY" - 450$\n");
						strcat(s,""C_ZIELONY"Ubrania"C_BEZOWY" - 660$\n");
						strcat(s,""C_ZIELONY"Zabawki"C_BEZOWY" - 430$\n");
						strcat(s,""C_ZIELONY"Kabury"C_BEZOWY" - 350$\n");
						strcat(s,""C_ZIELONY"Wojskowe mundury"C_BEZOWY" - 890$\n");
						strcat(s,""C_ZIELONY"Amunicja"C_BEZOWY" - 830$\n");
						strcat(s,""C_ZIELONY"Bronie"C_BEZOWY" - 670$\n");
						strcat(s,""C_ZIELONY"Amfetamina"C_BEZOWY" - 1 500$\n");
						strcat(s,""C_ZIELONY"Marihuana"C_BEZOWY" - 1 550$\n");
						strcat(s,""C_ZIELONY"Porcelana"C_BEZOWY" - 690$\n");
						strcat(s,""C_ZIELONY"Artyku≥y spoøywcze"C_BEZOWY" - 670$\n");
						strcat(s,""C_ZIELONY"Cukier"C_BEZOWY" - 950$\n");
						strcat(s,""C_ZIELONY"Paliwo"C_BEZOWY" - 780$\n");
						strcat(s,""C_ZIELONY"Komputery"C_BEZOWY" - 800$\n");
						strcat(s,""C_ZIELONY"Piasek"C_BEZOWY" - 750$\n");
						strcat(s,""C_ZIELONY"Kurtki"C_BEZOWY" - 590$\n");
						strcat(s,""C_ZIELONY"Drukarki"C_BEZOWY" - 750$\n");
						strcat(s,""C_ZIELONY"Odpady"C_BEZOWY" - 780$\n");
						strcat(s,""C_ZIELONY"Kamery"C_BEZOWY" - 880$\n");
						strcat(s,""C_ZIELONY"Papier"C_BEZOWY" - 760$\n");
						ShowPlayerDialog(playerid, GUI_ZLECENIE, DIALOG_STYLE_LIST, "Wybierz towar jaki chcesz za≥adowaÊ", s, "Za≥aduj", "Anuluj");
					}
					else
					{
						ShowPlayerDialog(playerid, GUI_ANULUJ, DIALOG_STYLE_MSGBOX, "Anulowanie misji", "Czy na pewno chcesz anulowac aktualnπ misjÍ ??", "Tak", "Nie");
					}
				}
				else
				{
				    SCM(playerid, KOLOR_CZERWONY, "Zla naczepa");
				}
			}
			else if(ToBus(v))
			{
			    if(GetPVarInt(playerid, "etap") == 0)
				{
					new s[2600];
					strcat(s,""C_ZIELONY"Zboze"C_BEZOWY" - 540$\n");
					strcat(s,""C_ZIELONY"Dokumenty"C_BEZOWY" - 650$\n");
					strcat(s,""C_ZIELONY"Lampy"C_BEZOWY" - 450$\n");
					strcat(s,""C_ZIELONY"Ubrania"C_BEZOWY" - 660$\n");
					strcat(s,""C_ZIELONY"Zabawki"C_BEZOWY" - 430$\n");
					strcat(s,""C_ZIELONY"Kabury"C_BEZOWY" - 350$\n");
					strcat(s,""C_ZIELONY"Wojskowe mundury"C_BEZOWY" - 890$\n");
					strcat(s,""C_ZIELONY"Amunicja"C_BEZOWY" - 830$\n");
					strcat(s,""C_ZIELONY"Bronie"C_BEZOWY" - 670$\n");
					strcat(s,""C_ZIELONY"Amfetamina"C_BEZOWY" - 1 500$\n");
					strcat(s,""C_ZIELONY"Marichuana"C_BEZOWY" - 1 550$\n");
					strcat(s,""C_ZIELONY"Porcelana"C_BEZOWY" - 690$\n");
					strcat(s,""C_ZIELONY"Artyku≥y spoøywcze"C_BEZOWY" - 670$\n");
					strcat(s,""C_ZIELONY"Cukier"C_BEZOWY" - 950$\n");
					strcat(s,""C_ZIELONY"Paliwo"C_BEZOWY" - 780$\n");
					strcat(s,""C_ZIELONY"Komputery"C_BEZOWY" - 800$\n");
					strcat(s,""C_ZIELONY"Piasek"C_BEZOWY" - 750$\n");
					strcat(s,""C_ZIELONY"Kurtki"C_BEZOWY" - 590$\n");
					strcat(s,""C_ZIELONY"Drukarki"C_BEZOWY" - 750$\n");
					strcat(s,""C_ZIELONY"Odpady"C_BEZOWY" - 780$\n");
					strcat(s,""C_ZIELONY"Kamery"C_BEZOWY" - 880$\n");
					strcat(s,""C_ZIELONY"Papier"C_BEZOWY" - 760$\n");
					ShowPlayerDialog(playerid, GUI_ZLECENIE, DIALOG_STYLE_LIST, "Wybierz towar jaki chcesz za≥adowaÊ", s, "Za≥aduj", "Anuluj");
				}
				else
				{
					ShowPlayerDialog(playerid, GUI_ANULUJ, DIALOG_STYLE_MSGBOX, "Anulowanie misji", "Czy na pewno chcesz anulowac aktualnπ misjÍ ??", "Tak", "Nie");
				}
			}
		}
		else if(ToET(playerid) || ToST(playerid) || ToRICO(playerid))
		{
		    if(GetPVarInt(playerid, "etap") == 0)
			{
   				new s[1000];
				strcat(s,""C_ZIELONY"czesci budowlane"C_BEZOWY" - 2540$\n");
				strcat(s,""C_ZIELONY"czesci do kombajna"C_BEZOWY" - 2673$\n");
				strcat(s,""C_ZIELONY"czesci do koparek"C_BEZOWY" - 2717$\n");
				strcat(s,""C_ZIELONY"marihuana"C_BEZOWY" - 3952$\n");
				strcat(s,""C_ZIELONY"amfetamina"C_BEZOWY" - 3893$\n");
				strcat(s,""C_ZIELONY"paliwo do koparek"C_BEZOWY" - 2751$\n");
				strcat(s,""C_ZIELONY"prezerwatywy"C_BEZOWY" - 2873$\n");
				strcat(s,""C_ZIELONY"ropa"C_BEZOWY" - 2538$\n");
				strcat(s,""C_ZIELONY"samochody wyscigowe"C_BEZOWY" - 1430$\n");
				strcat(s,""C_ZIELONY"trumny"C_BEZOWY" - 2673$\n");
				ShowPlayerDialog(playerid, GUI_ZLECENIE_ST, DIALOG_STYLE_LIST, "Wybierz towar jaki chcesz za≥adowaÊ", s, "Za≥aduj", "Anuluj");
			}
			else
			{
				ShowPlayerDialog(playerid, GUI_ANULUJ, DIALOG_STYLE_MSGBOX, "Anulowanie misji", "Czy na pewno chcesz anulowac aktualnπ misjÍ ??", "Tak", "Nie");
			}
		}
		else if(ToLOT(playerid))
		{
		    if(GetPVarInt(playerid, "etap") == 0)
			{
			    new v=GetPlayerVehicleID(playerid);
		    	if(GetVehicleModel(v)==593||GetVehicleModel(v)==519||GetVehicleModel(v)==553||GetVehicleModel(v)==563||GetVehicleModel(v)==488||GetVehicleModel(v)==511)//ciÍøarowe
				{
				    new s[500];
					strcat(s,""C_ZIELONY"ØywnoúÊ"C_BEZOWY" - 1540$\n");
					strcat(s,""C_ZIELONY"Ludzie"C_BEZOWY" - 1650$\n");
					strcat(s,""C_ZIELONY"Artyku≥y Gospodarstwa Domowego"C_BEZOWY" - 1450$\n");
					strcat(s,""C_ZIELONY"Ubrania"C_BEZOWY" - 1660$\n");
					strcat(s,""C_ZIELONY"Zabawki"C_BEZOWY" - 1430$\n");
					ShowPlayerDialog(playerid, GUI_ZLECENIE_LOT, DIALOG_STYLE_LIST, "Wybierz towar jaki chcesz za≥adowaÊ", s, "Za≥aduj", "Anuluj");
				}
				else
				{
				    SendClientMessage(playerid, KOLOR_CZERWONY, "Musisz byÊ w pojeüdzie zdolnym do rozwozenia towarÛw!");
				}
			}
			else
			{
				ShowPlayerDialog(playerid, GUI_ANULUJ, DIALOG_STYLE_MSGBOX, "Anulowanie misji", "Czy na pewno chcesz anulowac aktualnπ misjÍ ??", "Tak", "Nie");
			}
		}
		else if(ToPD(playerid) && ToPOMOC(playerid))
		{
		    SendClientMessage(playerid, -1, ""C_CZERWONY"Nie moøesz rozwoziÊ towarÛw pracujπc w tej frakcji");
		}
		return 1;
	}

    /*
	IsNumeric(const numericstring[])
	{
		for (new i = 0, j = strlen(numericstring); i < j; i++)
		{
			if (numericstring[i] > '9' || numericstring[i] < '0') return 0;
		}
		return 1;
	}


	if(strfind(PlayerName(playerid),"[34T]",true)!=1)
	{
	//jest
	}else{
	//brak
	}
	*/

	CMD:info(playerid, params[])
	{
		new info[1500];
		strcat(info,"{FFFFFF}Witaj! {8000FF}Jest to serwer poúwiÍcony ciÍøarÛwkom,\n");
		strcat(info,"{FFFFFF}Praca kierowcy jest {FFFF00}bardzo odpowiedzialnym zawodem{FFFFFF}, ktÛry mogπ wykonywaÊ tylko najlepsi,\n");
		strcat(info,"{FFFFFF}Aby zaczπÊ pracowaÊ musisz zapoznaÊ siÍ z {379BFF}/pomoc{FFFFFF} i {379BFF}/taryfikator{FFFFFF}, pozwoli Ci to na bezb≥Ídne wykonywanie swojej pracy,\n");
		strcat(info,"{FFFFFF}Jeúli zapozna≥eú siÍ z powyøszymi komendami {FCB103}weü busa lub zestaw (Truck + Naczepa) z bazy truckerÛw{FFFFFF} i jedü na najbliøszy za≥adunek,\n");
		strcat(info,"{FFFFFF}Wybierz towar jaki chcia≥ byú za≥adowaÊ i jedz na jakieú miejsce roz≥adunku,\n");
		strcat(info,"{FFFFFF}Po dostarczeniu towaru otrzymasz {DBFA05}wyp≥atÍ w postaci pieniÍdzy i punktÛw score{FFFFFF},\n");
		strcat(info,"{FFFFFF}Punkty Score przydadzπ siÍ w naborze do firm i frakcji,\n");
		strcat(info,"{FFFFFF}Jeúli nadal nie wiesz o co chodzi - zapytaj siÍ innych graczy o pomoc\n");
		strcat(info,"{FFFFFF}Mi≥ej trasy na serwerze {DBFA05}Hard Truck{FFFFFF}. ({FD6102}www.Hard-Truck.pl{FFFFFF})");
		ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "{FFFFFF}Informacje", info, "OK", "");
		return 1;
	}

	CMD:brawa(playerid, params[])
	{
		new player,
	        liczba;

		if(!ToAdminLevel(playerid, 1))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Komenda dla Admina poziom 1");

		if(sscanf(params, "dd", player, liczba))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, ""C_BEZOWY"Uøyj: "C_ZIELONY"/brawa <id gracza> <typ> "C_ZOLTY"|| "C_BEZOWY"Typ to cyfry od "C_ZIELONY"1"C_BEZOWY"-"C_ZIELONY"10");

		if(!IsPlayerConnected(player))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Gracz o takim ID nie jest pod≥πczony !!");

		if(liczba == 1)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-29.mp3");
		}
		if(liczba == 2)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-28.mp3");
		}
		if(liczba == 3)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-27.mp3");
		}
		if(liczba == 4)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-26.mp3");
		}
		if(liczba == 5)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-25.mp3");
		}
		if(liczba == 6)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-6.mp3");
		}
		if(liczba == 7)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-7.mp3");
		}
		if(liczba == 8)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-8.mp3");
		}
		if(liczba == 9)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-9.mp3");
		}
		if(liczba == 10)
		{
			StopAudioStreamForPlayer(player);
			PlayAudioStreamForPlayer(player, "http://www.pacdv.com/sounds/applause-sounds/app-10.mp3");
		}
		if((liczba == 0) || (liczba > 10))
		{
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Z≥e ID aplausu");
		}
		return 1;
	}

	stock ActivateMotion(playerid, player_keys)
	{
        new
                Float:X, Float:Y, Float:Z,
                Float:VX, Float:VY, Float:VZ,
                Float:pAng
        ;


        dUstawHP(playerid, 1000000);
        GetPlayerCameraFrontVector(playerid, VX, VY, VZ);
        GetAnimationName(GetPlayerAnimationIndex(playerid), PlayerAnimLib[playerid], 32, PlayerAnimName[playerid], 32);

        if(strlen(PlayerAnimLib[playerid]) && !strcmp(PlayerAnimLib[playerid], "ped", true, 3))
        {
            if (player_keys & KEY_SPRINT)
            {
            	GetPlayerFacingAngle(playerid, pAng);
            	GetPlayerVelocity(playerid, X, Y, Z);
            	SetPlayerVelocity(playerid, floatsin(-pAng, degrees) * 1.6, floatcos(pAng, degrees) * 1.6 , (Z*2)+0.03);
            } else

            if (player_keys & KEY_JUMP)
                {
                    if(strlen(PlayerAnimName[playerid])
                        && !strcmp(PlayerAnimName[playerid], "IDLE_", true, 5)
                        || !strcmp(PlayerAnimName[playerid], "GETUP_", true, 6)
                        || !strcmp(PlayerAnimName[playerid], "WALK_", true, 5)
                        || !strcmp(PlayerAnimName[playerid], "FALL_", true, 5)
                        || !strcmp(PlayerAnimName[playerid], "FACTALK", true, 7)
                        || !strcmp(PlayerAnimName[playerid], "JUMP_", true, 5)
                        || !strcmp(PlayerAnimName[playerid], "FALL_", true, 5)
                        || !strcmp(PlayerAnimName[playerid], "RUN_", true, 4))
                        dUstawHP(playerid, 1000000);

                        {
                            SetPlayerVelocity(playerid, 0, 0, 5);

                            GetPlayerPos(playerid, X, Y, Z);
                            AngleXYInFrontOfPlayer(playerid, X, Y, -2.7, 30);
                            CreateExplosion(X, Y, Z, 4, 10);
                            CreateExplosion(X, Y, Z, 2, 2);

                            GetPlayerPos(playerid, X, Y, Z);
                            AngleXYInFrontOfPlayer(playerid, X, Y, -2.7, -30);
                            CreateExplosion(X, Y, Z, 4, 10);
                            CreateExplosion(X, Y, Z, 2, 2);
                        }
                } else

                if (player_keys & KEY_FIRE)
                {
                        if (strlen(PlayerAnimName[playerid])
                        && !strcmp(PlayerAnimName[playerid], "JUMP_", true, 5)
                        || !strcmp(PlayerAnimName[playerid], "FACTALK", true, 7)
                        || !strcmp(PlayerAnimName[playerid], "FALL_", true, 5))
                        dUstawHP(playerid, 1000000);

                        {
                            new
                                Float:yAng,
                                        Float:X1, Float:Y1, Float:Z1,
                                        Float:X2, Float:Y2, Float:Z2
                                ;
                                GetPlayerPos(playerid, X1, Y1, Z1);
                                GetPlayerCameraPos(playerid, X2, Y2, Z2);
                                #pragma unused Z1
                                #pragma unused Z2
                                yAng = (atan2(Y2-Y1, X2-X1))-270;

                                ClearAnimations(playerid);
                                SetPlayerFacingAngle(playerid, yAng);
                                SetPlayerVelocity(playerid, VX, VY, VZ+0.5);
                        }
                } else

                if (player_keys & KEY_CROUCH)
                {
                        SetPlayerVelocity(playerid, 0, 0, -50);
                        KillTimer(GroundExplosionTimer[playerid]);
            		GroundExplosionTimer[playerid] = SetTimerEx("Gexplode", 250, false, "d", playerid);
            		dUstawHP(playerid, 100000);
                }
        	}
        	return true;
		}

		forward Gexplode(playerid);
		public Gexplode(playerid)
		{
		    new Float:X, Float:Y, Float:Z;
		    GetPlayerPos(playerid, X, Y, Z);
		    CreateExplosion(X, Y, Z, 4, 10);
			CreateExplosion(X, Y, Z, 2, 2);
			dUstawHP(playerid, 100000);
			return true;
		}

		CMD:supermen(playerid, params[])
		{
		    if(!ToAdminLevel(playerid, 3))
		        return SendClientMessage(playerid, KOLOR_CZERWONY, "Komenda tylko dla administratora poziom 2");

			if (PowerEnabled[playerid])
		 	{
			    dUstawHP(playerid, 100);
			    SendClientMessage(playerid, 0x00FFFFFF, "*** Super moce zosta≥y wy≥πczone... ***");
				PowerEnabled[playerid] = false;
			} else {
			    SendClientMessage(playerid, 0x00FFFFFF, "*** Aktywowano super moce! ***");
			    SendClientMessage(playerid, 0xFFFFFFFF, "- Uøyj Sprint do szybkiego biegu.");
			    SendClientMessage(playerid, 0xFFFFFFFF, "- Uøyj Skok do super skoku.");
			    SendClientMessage(playerid, 0xFFFFFFFF, "- Uøyj LPM do latania.");
			    dUstawHP(playerid, 1000000);
				PowerEnabled[playerid] = true;
			}
		    return true;
		}

		stock AngleXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance, Float:Angle = 0.0)
		{                                               //by Y_Less (a little change by pleomax)

		    new Float:a;

		    GetPlayerPos(playerid, x, y, a);
		    GetPlayerFacingAngle(playerid, a);

		    if (GetPlayerVehicleID(playerid)) {
		        GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
		    }

		    x += (distance * floatsin(-(a+Angle), degrees));
		    y += (distance * floatcos(-(a+Angle), degrees));
		}

	CMD:savepos(playerid, params[])
	{
	    new tekst[64];
	    if(sscanf(params, "s", tekst))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /savepos <nazwa pozycji>");

	    new Float: X, Float: Y, Float: Z;
	    GetPlayerPos(playerid, X, Y, Z);
		format(dstring, sizeof(dstring),""C_BEZOWY"Pozycja "C_ZIELONY"'%f, %f, %f'"C_BEZOWY" zosta≥a zapisana w logach serwera pod nazwπ %s!", X, Y, Z, tekst);
		SendClientMessage(playerid, KOLOR_ZIELONY, dstring);
		printf("[SavePos]%s - %f, %f, %f. Nazwa: %s", Nick(playerid), X, Y, Z, tekst);
		return 1;
	}

	CMD:pogoda(playerid, params[])
	{
	    new liczba;
	    if(!ToAdminLevel(playerid, 2))
            return SendClientMessage(playerid, KOLOR_CZERWONY, "Tylko dla Admina");

        if(sscanf(params, "d", liczba))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /pogoda <ID>");


	    SetWeather(liczba);
        format(dstring, sizeof(dstring),""C_BEZOWY"Pogoda zmieniona na: "C_ZIELONY"%d", liczba);
        SendClientMessage(playerid, KOLOR_ZIELONY, dstring);

        format(dstring, sizeof(dstring),""C_BEZOWY"Admin "C_ZIELONY"%s"C_BEZOWY"["C_ZIELONY"%d"C_BEZOWY"] "C_BEZOWY"zmieni≥ pogodÍ na "C_ZIELONY"%d"C_BEZOWY".", Nick(playerid), playerid, liczba);
        SendClientMessage(playerid, KOLOR_ZIELONY, dstring);
	    return 1;
	}

	CMD:pozwol(playerid, params[])
	{
	    new idgracza, taknie;
	    if(!ToAdminLevel(playerid, 2))
            return SendClientMessage(playerid, KOLOR_CZERWONY, "Tylko dla Admina");

        if(sscanf(params, "dd", idgracza, taknie))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /pozwol <ID gracza> <1=pozwolenie, 0=brak>");

		if(taknie == 1)
		{
	        format(dstring, sizeof(dstring),"Admin %s(%d) da≥ Ci pozwolenie na miecze úwietlne. Uøyj /miecze.", Nick(playerid), playerid);
	        SendClientMessage(idgracza, KOLOR_ZIELONY, dstring);
	        PozwolenieMiecze[idgracza] = 1;
	        format(dstring, sizeof(dstring),"Da≥eú pozwolenie graczowi %s(%d).", Nick(idgracza), idgracza);
	        SendClientMessage(idgracza, KOLOR_ZIELONY, dstring);
		}
		if(taknie == 0)
		{
		    format(dstring, sizeof(dstring),"Admin %s(%d) zabra≥ Ci pozwolenie na miecze úwietlne.", Nick(playerid), playerid);
	        SendClientMessage(idgracza, KOLOR_ZIELONY, dstring);
	        PozwolenieMiecze[idgracza] = 0;
	        format(dstring, sizeof(dstring),"Zabra≥eú pozwolenie graczowi %s(%d).", Nick(idgracza), idgracza);
	        SendClientMessage(idgracza, KOLOR_ZIELONY, dstring);
		}
		if(taknie != 0 && taknie != 1)
		{
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /pozwol <ID gracza> <1=pozwolenie, 0=brak>");
		}
		return 1;
	}

	CMD:miecz(playerid, params[])
	{
		if(ToAdminLevel(playerid, 1))
		{
			if(swords[playerid] == false)
			{
				ShowPlayerDialog(playerid, MIECZE, DIALOG_STYLE_LIST, "Miecze úwietlne", "Zielony\nZolty\nNiebieski\nCzerwony\nBialy\nRozowy", "Wez", "Wyjdz");
			}
			else
			{
				RemovePlayerAttachedObject(playerid,0);
				swords[playerid] = false;
			}
		}
		return 1;
	}
	CMD:noc(playerid, params[])
	{
 		if(!ToAdminLevel(playerid, 1))
            return SendClientMessage(playerid, KOLOR_CZERWONY, "Komenda Moda");

	    SetWorldTime(1);
	    return 1;
	}

	CMD:dzien(playerid, params[])
	{
 		if(!ToAdminLevel(playerid, 1))
            return SendClientMessage(playerid, KOLOR_CZERWONY, "Komenda Moda");

	    SetWorldTime(12);
	    return 1;
	}

	CMD:impra(playerid, params[])
	{
	    SetPlayerPos(playerid, 257.110321, -1841.223144, 3.439889);
	    GameTextForPlayer(playerid,"~b~Witaj na imprezie!",1000,3);
	    format(dstring,sizeof(dstring),"{0088FF}CzeúÊ {FF0000}%s{0088FF}!\nWitaj na {15FF00}Imprezie{0088FF} z okazji otwarcia serwera.\n\n{0088FF}Mi≥ej zabawy",Nick(playerid));
		ShowPlayerDialog(playerid,9944,DIALOG_STYLE_MSGBOX,"{FFFF00}Impreza!",dstring,"Ok","");
	    return 1;
	}

	CMD:dj(playerid, params[])
	{
	    if(PlayerInfo[playerid][pDJ] != 1)
	        return SendClientMessage(playerid, KOLOR_CZERWONY, "Nie jesteú DJ'em");

	    new s[1000];
	    strcat(s,""C_ZIELONY"1. "C_BEZOWY"Onar - Kilka ostatnich krokÛw\n");
		strcat(s,""C_ZIELONY"2. "C_BEZOWY"Peja - Kto ma renomÍ na blokach\n");
		strcat(s,""C_ZIELONY"3. "C_BEZOWY"Flo Rida - Club cant handle me\n");
		strcat(s,""C_ZIELONY"4. "C_BEZOWY"Alexandra Stan - Mr.Saxo Beat\n");
		strcat(s,""C_ZIELONY"5. "C_BEZOWY"Cascada - Pyromania\n");
		strcat(s,""C_ZIELONY"6. "C_BEZOWY"Analogia - Bujaka\n");
		strcat(s,""C_ZIELONY"7. "C_BEZOWY"grubson - biba\n");
		strcat(s,""C_ZIELONY"8. "C_BEZOWY"Jennifer Lopez - On The Floor\n");
		strcat(s,""C_ZIELONY"9. "C_BEZOWY"Kesha - Tik Tok\n");
		strcat(s,""C_ZIELONY"10. "C_BEZOWY"Kobra - Gin & Tonic\n");
		strcat(s,""C_ZIELONY"11. "C_BEZOWY"Tomasz Niecik - Cztery Osiemnastki\n");
		strcat(s,""C_ZIELONY"12. "C_BEZOWY"Tomasz Niecik - StÛwa\n");
		strcat(s,""C_ZIELONY"13. "C_BEZOWY"nie znam\n");
		strcat(s,""C_ZIELONY"14. "C_BEZOWY"Jan B≥achowicz - KSW17\n");
		strcat(s,""C_ZIELONY"15. "C_BEZOWY"HD FunPack\n");
		strcat(s,""C_ZOLTY"Swiπteczne\n");
		strcat(s,""C_NIEBIESKI"Adres url\n");
		strcat(s,""C_CZERWONY"STOP");
		ShowPlayerDialog(playerid,PANEL_DJ,DIALOG_STYLE_LIST, "Panel DJ'a", s, "Play", "Anuluj");
		return 1;
	}

	CMD:obiekty(playerid, params[])
	{
	    ShowPlayerDialog(playerid,GUI_OB,DIALOG_STYLE_LIST, "Menu Przyczepianych ObiektÛw", "Papuga\nM4\nPi≥a Dildo\nCzapka\nOdczep", "Wybierz", "Anuluj");
	    return 1;
	}

	CMD:rspcar(playerid, params[])
	{
	    if(!ToAdminLevel(playerid, 2))
	        return 1;

		new idwozu = GetPlayerVehicleID(playerid);
        SetVehicleToRespawn(idwozu);
		SetVehicleParamsEx(idwozu,false,false,false,false,false,false,false);
		vPojazdZycie[idwozu]=1000.0;
		SendClientMessage(playerid, KOLOR_ZIELONY, "Pojazd zrespawnowany");
		return 1;
	}

	CMD:news(playerid, params[])
	{
	    new s[1000];
	    strcat(s,""C_POMARANCZOWY"Data\t\t"C_NIEBIESKI"NowoúÊ\n\n");
	    strcat(s,""C_POMARANCZOWY"15 grudnia 2011\t"C_NIEBIESKI"Wprowadzenie systemu øycia i automatÛw\n");
	    strcat(s,""C_POMARANCZOWY"16 grudnia 2011\t"C_NIEBIESKI"Zmiana systemu komend ("C_ZIELONY"/zlecenie"C_NIEBIESKI")\n");

        ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Nowoúci na serwerze", s, "Ok", "");
	    return 1;
	}
	CMD:apomoc(playerid, params[])
	{
		new s[2000];
	    if(PlayerInfo[playerid][pAdmin]==0)
	    {
	    	ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"B≥πd", "Nie posiadasz Admina", "Ok", "");
	    }
		if(PlayerInfo[playerid][pAdmin]==1)
		{
			strcat(s,""C_ZIELONY"/lista - "C_BEZOWY"ukrywasz siÍ na liúcie adminÛw\n");
			strcat(s,""C_ZIELONY"/podglad - "C_BEZOWY"podglπdasz cb radia i pm graczy\n");
			strcat(s,""C_ZIELONY"/kick - "C_BEZOWY"wyrzucasz gracza\n");
			strcat(s,""C_ZIELONY"/warn - "C_BEZOWY"dajesz graczowi warna (4x warn = ban)\n");
			strcat(s,""C_ZIELONY"/blok - "C_BEZOWY"blokujesz graczowi konto\n");
			strcat(s,""C_ZIELONY"/ban - "C_BEZOWY"banujesz gracza na adres IP\n");
			strcat(s,""C_ZIELONY"/disarm - "C_BEZOWY"rozbrajasz gracza\n");
			strcat(s,""C_ZIELONY"/rsp - "C_BEZOWY"respawnujesz wszystkie nie uøywane pojazdy\n");
			ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend Moderatora", s, "Ok", "");
		}
		if(PlayerInfo[playerid][pAdmin]==2)
		{
			strcat(s,""C_ZIELONY"/lista - "C_BEZOWY"ukrywasz siÍ na liúcie adminÛw\n");
			strcat(s,""C_ZIELONY"/podglad - "C_BEZOWY"podglπdasz cb radia i pm graczy\n");
			strcat(s,""C_ZIELONY"/kick - "C_BEZOWY"wyrzucasz gracza\n");
			strcat(s,""C_ZIELONY"/warn - "C_BEZOWY"dajesz graczowi warna (4x warn = ban)\n");
			strcat(s,""C_ZIELONY"/blok - "C_BEZOWY"blokujesz graczowi konto\n");
			strcat(s,""C_ZIELONY"/ban - "C_BEZOWY"banujesz gracza na adres IP\n");
			strcat(s,""C_ZIELONY"/disarm - "C_BEZOWY"rozbrajasz gracza\n");
		    strcat(s,""C_ZIELONY"/aj - "C_BEZOWY"wrzucasz admina niøszego poziomem do Admin Jaila\n");
		    strcat(s,""C_ZIELONY"/spec - "C_BEZOWY"podglπdasz gracza\n");
		    strcat(s,""C_ZIELONY"/specoff - "C_BEZOWY"koÒczysz podglπdanie gracza\n");
		    strcat(s,""C_ZIELONY"/rsp - "C_BEZOWY"respawnujesz wszystkie nie uøywane pojazdy\n");
		    strcat(s,""C_ZIELONY"/rspall - "C_BEZOWY"respawnujesz wszystkie pojazdy\n");
		    strcat(s,""C_ZIELONY"/rspcar - "C_BEZOWY"respawnujesz pojazd w ktÛrym aktualnie siedzisz\n");
		    strcat(s,""C_ZIELONY"/wycisz - "C_BEZOWY"uciszasz gracza\n");
		    strcat(s,""C_ZIELONY"/sprawdzip - "C_BEZOWY"sprawdzasz ip graczy\n");
		    strcat(s,""C_ZIELONY"/givehp - "C_BEZOWY"ustawiasz komus dana liczbe HP\n");
		    strcat(s,""C_ZIELONY"/heal - "C_BEZOWY"leczysz gracza\n");
		    strcat(s,""C_ZIELONY"/armour - "C_BEZOWY"dajesz komuú kamizelkÍ\n");
		    strcat(s,""C_ZIELONY"/tune - "C_BEZOWY"tuningujesz wÛz\n");
		    strcat(s,""C_ZIELONY"/brawa - "C_BEZOWY"bijesz komuú brawa\n");
		    strcat(s,""C_ZIELONY"/givegun - "C_BEZOWY"dajesz komuú broÒ\n");
		    strcat(s,""C_ZIELONY"/pozwol - "C_BEZOWY"dajesz komuú pozwolenie na miecze úwietlne ;)\n");
		    strcat(s,""C_ZIELONY"/pogoda - "C_BEZOWY"zmieniasz pogode\n");
		    strcat(s,""C_ZIELONY"/tpto - "C_BEZOWY"teleportujesz siÍ do gracza\n");
		    strcat(s,""C_ZIELONY"/tphere - "C_BEZOWY"teleportujesz gracza do siebie\n");
		    ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend Admina", s, "Ok", "");
		}
		if(PlayerInfo[playerid][pAdmin]==3)
		{
			strcat(s,""C_ZIELONY"/lista - "C_BEZOWY"ukrywasz siÍ na liúcie adminÛw\n");
			strcat(s,""C_ZIELONY"/podglad - "C_BEZOWY"podglπdasz cb radia i pm graczy\n");
			strcat(s,""C_ZIELONY"/kick - "C_BEZOWY"wyrzucasz gracza\n");
			strcat(s,""C_ZIELONY"/warn - "C_BEZOWY"dajesz graczowi warna (4x warn = ban)\n");
			strcat(s,""C_ZIELONY"/blok - "C_BEZOWY"blokujesz graczowi konto\n");
			strcat(s,""C_ZIELONY"/ban - "C_BEZOWY"banujesz gracza na adres IP\n");
			strcat(s,""C_ZIELONY"/disarm - "C_BEZOWY"rozbrajasz gracza\n");
		    strcat(s,""C_ZIELONY"/aj - "C_BEZOWY"wrzucasz admina niøszego poziomem do Admin Jaila\n");
		    strcat(s,""C_ZIELONY"/spec - "C_BEZOWY"podglπdasz gracza\n");
		    strcat(s,""C_ZIELONY"/specoff - "C_BEZOWY"koÒczysz podglπdanie gracza\n");
		    strcat(s,""C_ZIELONY"/rsp - "C_BEZOWY"respawnujesz wszystkie nie uøywane pojazdy\n");
		    strcat(s,""C_ZIELONY"/rspall - "C_BEZOWY"respawnujesz wszystkie pojazdy\n");
		    strcat(s,""C_ZIELONY"/rspcar - "C_BEZOWY"respawnujesz pojazd w ktÛrym aktualnie siedzisz\n");
		    strcat(s,""C_ZIELONY"/wycisz - "C_BEZOWY"uciszasz gracza\n");
		    strcat(s,""C_ZIELONY"/sprawdzip - "C_BEZOWY"sprawdzasz ip graczy\n");
		    strcat(s,""C_ZIELONY"/givehp - "C_BEZOWY"ustawiasz komus dana liczbe HP\n");
		    strcat(s,""C_ZIELONY"/heal - "C_BEZOWY"leczysz gracza\n");
		    strcat(s,""C_ZIELONY"/armour - "C_BEZOWY"dajesz komuú kamizelkÍ\n");
		    strcat(s,""C_ZIELONY"/tune - "C_BEZOWY"tuningujesz wÛz\n");
		    strcat(s,""C_ZIELONY"/brawa - "C_BEZOWY"bijesz komuú brawa\n");
		    strcat(s,""C_ZIELONY"/givegun - "C_BEZOWY"dajesz komuú broÒ\n");
		    strcat(s,""C_ZIELONY"/text - "C_BEZOWY"tworzysz dynamiczny 3d text\n");
		    strcat(s,""C_ZIELONY"/dajadmin - "C_BEZOWY"dajesz admina (1-Moderator, 2-Admin, 3-HeadAdmin)\n");
		    strcat(s,""C_ZIELONY"/dajlider - "C_BEZOWY"dajesz komuú lidera frakcji\n");
		    strcat(s,""C_ZIELONY"/v - "C_BEZOWY"spawnujesz pojazd\n");
		    strcat(s,""C_ZIELONY"/vd - "C_BEZOWY"niszczysz wÛz w ktÛrym siedzisz\n");
		    strcat(s,""C_ZIELONY"/givecash - "C_BEZOWY"dajezsz komuú kasÍ\n");
		    strcat(s,""C_ZIELONY"/supermen - "C_BEZOWY"cheaty HeadAdmina\n");
		    strcat(s,""C_ZIELONY"/pozwol - "C_BEZOWY"dajesz komuú pozwolenie na miecze úwietlne ;)\n");
		    strcat(s,""C_ZIELONY"/pogoda - "C_BEZOWY"zmieniasz pogode\n");
		    strcat(s,""C_ZIELONY"/rebuildc - "C_BEZOWY"niszczysz wszystkie wozy i tworzysz je na nowo w ich spawnie\n");
		    strcat(s,""C_ZIELONY"/rebuildo - "C_BEZOWY"niszczysz wszystkie obiekty i tworzysz je na nowo w ich spawnie\n");
            strcat(s,""C_ZIELONY"/swieta - "C_BEZOWY"dodatki zwiπzane z Hard-Truck modem\n");
		    strcat(s,""C_ZIELONY"/tpto - "C_BEZOWY"teleportujesz siÍ do gracza\n");
		    strcat(s,""C_ZIELONY"/tphere - "C_BEZOWY"teleportujesz gracza do siebie\n");
		    strcat(s,""C_ZIELONY"/tphereall - "C_BEZOWY"teleportujesz wszystkich graczy do siebie\n");
		    strcat(s,""C_ZIELONY"/tptoall - "C_BEZOWY"teleporyjesz wszystkich graczy do danego gracza\n");
		    ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"Spis komend HeadAdmina", s, "Ok", "");
		}
		return 1;
	}

	forward CreateWozy();
	public CreateWozy()
	{
		//ciÍøarowki i busy
		CreateVehicle(414,2311.0071,2763.9890,10.9140,90.2121,28,1,SPAWN); // bus
		CreateVehicle(499,2295.8572,2748.2329,10.8130,271.4996,109,32,SPAWN); // bus
		CreateVehicle(609,2295.3965,2754.5676,10.8857,270.5961,36,36,SPAWN); // bus
		CreateVehicle(609,2347.0491,2754.1199,10.8871,269.8410,36,36,SPAWN); // bus
		CreateVehicle(414,2347.8394,2770.8708,10.9135,269.2453,43,1,SPAWN); // bus
		CreateVehicle(456,2347.8459,2779.8958,10.9939,269.6905,91,63,SPAWN); // bus
		CreateVehicle(499,2400.3853,2754.8801,10.8088,180.5168,112,32,SPAWN); // bus
		CreateVehicle(456,2259.7896,2763.6418,10.9942,90.3634,102,65,SPAWN); // bus
		CreateVehicle(609,2260.7993,2747.9197,10.8869,89.3076,36,36,SPAWN); // bus
		CreateVehicle(482,2311.6440,2770.2808,10.9420,90.1025,48,48,SPAWN); // bus
		CreateVehicle(482,2368.1650,2754.0090,10.9329,182.0930,52,52,SPAWN); // bus
		CreateVehicle(403,2317.8159,2804.8123,11.4265,180.4881,30,1,SPAWN); // tir
		CreateVehicle(514,2337.5222,2805.1755,11.4103,179.4931,25,1,SPAWN); // tir
		CreateVehicle(514,2342.9092,2805.0005,11.8441,180.7084,24,77,SPAWN); // tir
		CreateVehicle(514,2347.7495,2804.9570,11.8459,180.0310,63,78,SPAWN); // tir
		CreateVehicle(591,2307.6084,2815.1992,10.9447,180.3318,71,71,SPAWN); // przyczepka
		CreateVehicle(591,2312.1775,2815.2847,10.9332,179.9018,64,64,SPAWN); // przyczepka
		CreateVehicle(591,2303.6321,2815.1543,10.9406,180.0920,85,85,SPAWN); // przyczepka
		CreateVehicle(591,2299.9846,2814.9185,10.9340,180.6121,10,10,SPAWN); // przyczepka
		CreateVehicle(456,1665.2975,1028.1313,10.9941,180.1994,105,72,SPAWN); // tir
		CreateVehicle(499,1668.2421,999.9714,10.8125,0.7830,10,32,SPAWN); // bus
		CreateVehicle(609,1677.8937,1038.9404,10.8894,0.2504,36,36,SPAWN); // bus
		CreateVehicle(414,1655.1812,1039.5575,10.9140,180.1107,67,1,SPAWN); // bus
		CreateVehicle(482,1658.4481,1039.5607,10.9435,180.1298,41,41,SPAWN); // bus
		CreateVehicle(482,1677.6862,988.4897,10.9369,180.8095,62,62,SPAWN); // bus
		CreateVehicle(514,1635.6238,984.7650,11.4158,269.2711,28,1,SPAWN); // tir
		CreateVehicle(514,1635.7374,980.0479,11.4123,268.9646,36,1,SPAWN); // tir
		CreateVehicle(403,1634.6945,958.8669,11.3781,270.2846,25,1,SPAWN); // tir
		CreateVehicle(403,1634.8462,963.1311,11.4175,267.4902,28,1,SPAWN); // tir
		CreateVehicle(514,1631.0264,1056.5179,11.8412,270.2427,54,77,SPAWN); // tor
		CreateVehicle(514,1631.1403,1051.6240,11.8455,270.5518,42,76,SPAWN); // tir
		CreateVehicle(591,1668.0574,1084.7648,10.9439,179.3968,48,48,SPAWN); // przyczepka
		CreateVehicle(591,1673.1671,1084.9673,10.9447,180.0114,52,52,SPAWN); // przyczepka
		CreateVehicle(591,1663.3488,1084.5458,10.9368,179.6583,64,64,SPAWN); // przyczepka
		CreateVehicle(591,1701.4664,1045.0643,10.9451,90.0509,71,71,SPAWN); // przyczepka
		CreateVehicle(591,1701.5645,1039.9934,10.9408,92.6422,10,10,SPAWN); // przyczepka
		CreateVehicle(591,1701.6602,1034.9216,10.9362,91.0510,85,85,SPAWN); // przyczepka
		CreateVehicle(514,280.9649,1339.0770,11.5953,90.3783,11,76,SPAWN); // tir
		CreateVehicle(514,281.1323,1344.1147,11.6088,89.6267,39,78,SPAWN); // tir
		CreateVehicle(403,281.1361,1348.8962,11.1930,89.4511,113,1,SPAWN); // tir
		CreateVehicle(403,281.2014,1352.9846,11.1931,90.0113,101,1,SPAWN); // tir
		CreateVehicle(591,281.0659,1359.0925,10.7061,90.0978,62,62,SPAWN); // przyczepka
		CreateVehicle(591,281.2307,1363.4637,10.7072,89.6200,41,41,SPAWN); // przyczepka
		CreateVehicle(591,281.2249,1368.0638,10.7111,89.8796,48,48,SPAWN); // przyczepka
		CreateVehicle(591,281.6437,1372.7913,10.7061,89.1569,52,52,SPAWN); // przyczepka
		CreateVehicle(456,281.7934,1378.2223,10.7591,88.9489,110,93,SPAWN); // bus
		CreateVehicle(414,281.2166,1382.9561,10.6797,90.5572,72,1,SPAWN); // bus
		CreateVehicle(499,281.1668,1387.2590,10.5768,91.2498,30,44,SPAWN); // bus
		CreateVehicle(482,281.8506,1391.4460,10.7046,94.2692,71,71,SPAWN); // bus
		CreateVehicle(482,281.5196,1395.7723,10.7028,90.8613,64,64,SPAWN); // bus
		CreateVehicle(499,-60.4430,-307.3835,5.4215,269.0612,32,52,SPAWN); // bus
		CreateVehicle(414,-61.5061,-318.0318,5.5235,90.8284,9,1,SPAWN); // bus
		CreateVehicle(609,-30.6578,-279.9072,5.4936,90.8196,36,36,SPAWN); // bus
		CreateVehicle(482,-30.2935,-293.8136,5.5443,269.7084,85,85,SPAWN); // bus
		CreateVehicle(514,-2.2432,-304.7859,6.0134,89.3857,54,1,SPAWN); // tir
		CreateVehicle(514,-2.3283,-308.8102,6.0138,90.9112,40,1,SPAWN); // tir
		CreateVehicle(514,-1.8840,-313.6975,6.4484,90.6338,13,76,SPAWN); // tir
		CreateVehicle(514,-1.8206,-318.5291,6.4498,91.8417,24,77,SPAWN); // tir
		CreateVehicle(403,-2.1220,-323.1804,6.0360,90.0182,37,1,SPAWN); // tir
		CreateVehicle(403,-1.9556,-327.3929,6.0353,89.8897,36,1,SPAWN); // tir
		CreateVehicle(591,-1.9019,-333.0806,5.5484,89.1492,10,10,SPAWN); // przyczepka
		CreateVehicle(591,-2.4786,-336.4034,5.5548,90.1768,10,10,SPAWN); // przyczepka
		CreateVehicle(591,-2.9942,-339.7986,5.5504,89.6660,10,10,SPAWN); // przyczepka
		CreateVehicle(591,-3.1092,-343.4930,5.5493,90.4812,10,10,SPAWN); // przyczepka
		CreateVehicle(591,-3.4045,-346.8654,5.5421,89.5194,10,10,SPAWN); // przyczepka
		CreateVehicle(591,-3.4633,-350.5401,5.5456,89.1490,10,10,SPAWN); // przyczepka
		CreateVehicle(514,-475.3481,-487.7929,26.1025,179.8293,113,1,SPAWN); // tir
		CreateVehicle(514,-480.1838,-487.8595,26.1111,179.7600,75,1,SPAWN); // tir
		CreateVehicle(414,-520.2507,-502.4152,24.9474,359.3402,95,1,SPAWN); // bus
		CreateVehicle(403,-485.2526,-487.6130,26.1240,179.0935,30,1,SPAWN); // tir
		CreateVehicle(403,-490.3285,-487.6574,26.1248,179.6279,28,1,SPAWN); // tir
		CreateVehicle(591,-481.5328,-539.3635,25.6475,89.1427,62,62,SPAWN); // przyczepka
		CreateVehicle(591,-481.3817,-535.1353,25.6458,90.2982,41,41,SPAWN); // przyczepka
		CreateVehicle(591,-481.4117,-529.9183,25.6423,88.8686,48,48,SPAWN); // przyczepka
		CreateVehicle(591,-471.9379,-524.3510,25.6412,89.3235,52,52,SPAWN); // przyczepka
		CreateVehicle(499,-514.8950,-471.8510,25.5150,357.2408,84,66,SPAWN); // bus
		CreateVehicle(482,-529.7975,-498.9450,25.2568,0.3225,64,64,SPAWN); // przyczepka
		CreateVehicle(482,-557.5793,-497.9398,25.3433,359.2647,71,71,SPAWN); // przyczepka
		CreateVehicle(514,-548.0521,-499.2165,26.5318,1.1971,63,78,SPAWN); // tir
		CreateVehicle(514,-542.2838,-499.1769,26.5412,359.5015,42,76,SPAWN); // tir
		CreateVehicle(482,-1716.5682,394.2632,7.3023,227.1302,85,85,SPAWN); // bus
		CreateVehicle(414,-1714.4014,396.7476,7.2734,225.8878,24,1,SPAWN); // bus
		CreateVehicle(456,-1699.2637,412.0785,7.3541,223.0623,121,93,SPAWN); // bus
		CreateVehicle(403,-1674.1497,436.8432,7.7857,224.8543,25,1,SPAWN); // tir
		CreateVehicle(514,-1670.7048,440.2315,7.7730,226.1244,10,1,SPAWN); // tir
		CreateVehicle(514,-1667.4596,444.1543,8.2065,224.7720,54,77,SPAWN); // tir
		CreateVehicle(591,-1663.1475,446.9085,7.2996,222.8381,10,10,SPAWN); // przyczepka
		CreateVehicle(591,-1660.0369,450.3135,7.3042,223.8612,62,62,SPAWN); // przyczepka
		CreateVehicle(591,-1656.8699,453.6613,7.3047,226.9082,41,41,SPAWN); // przyczepka
		CreateVehicle(403,-55.4870,-1133.0015,1.6841,67.9868,101,1,SPAWN); // tir
		CreateVehicle(514,-57.6327,-1137.7991,1.6608,67.4059,25,1,SPAWN); // tir
		CreateVehicle(514,-59.1611,-1142.9742,2.0982,66.5671,39,78,SPAWN); // tir
		CreateVehicle(591,-44.4431,-1137.0759,1.1960,70.4657,48,48,SPAWN); // przyczepka
		CreateVehicle(591,-44.8744,-1142.7460,1.2009,70.4315,48,48,SPAWN); // przyczepka
		CreateVehicle(591,-46.1187,-1148.4441,1.1939,68.3204,48,48,SPAWN); // przyczepka
		CreateVehicle(482,73.48412323,2033.74169922,17.89062500,182.00000000,3,3,SPAWN); //Burrito
		CreateVehicle(482,81.99251556,2034.01013184,17.89062500,184.00000000,3,3,SPAWN); //Burrito
		CreateVehicle(482,69.18588257,2033.53698730,17.89729691,182.00000000,3,3,SPAWN); //Burrito
		CreateVehicle(482,77.88835144,2033.82409668,17.89062500,182.00000000,3,3,SPAWN); //Burrito
		CreateVehicle(403,86.19795990,1971.99658203,18.34062576,96.00000000,3,3,SPAWN); //Linerunner
		CreateVehicle(403,85.67610168,1976.90478516,18.34062576,98.00000000,3,3,SPAWN); //Linerunner
		CreateVehicle(403,86.62659454,1966.82275391,18.48818970,96.00000000,3,3,SPAWN); //Linerunner
		CreateVehicle(403,87.58654785,1961.03540039,18.34062576,96.00000000,3,3,SPAWN); //Linerunner
		CreateVehicle(440,-3.35381913,2021.69433594,17.85331345,270.00000000,3,3,SPAWN); //Rumpo
		CreateVehicle(440,-3.50095749,2026.73974609,17.85331345,270.00000000,3,3,SPAWN); //Rumpo
		CreateVehicle(440,-3.35884547,2032.19714355,17.85331345,270.00000000,3,3,SPAWN); //Rumpo
		CreateVehicle(440,-3.49862218,2016.57971191,17.85331345,270.00000000,3,3,SPAWN); //Rumpo
		CreateVehicle(514,83.16514587,2007.28906250,18.96788025,96.00000000,3,3,SPAWN); //Roadtrain
		CreateVehicle(514,84.31657410,1991.90795898,18.79434586,96.00000000,3,3,SPAWN); //Roadtrain
		CreateVehicle(514,84.03717804,1996.78039551,19.02338409,96.00000000,3,3,SPAWN); //Roadtrain
		CreateVehicle(514,83.55990601,2001.98291016,18.84866333,96.00000000,3,3,SPAWN); //Roadtrain
		CreateVehicle(591,48.73873901,1946.50610352,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,43.85627747,1946.50524902,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,38.81546021,1946.10925293,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,53.59922028,1946.06860352,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,33.97669983,1946.15063477,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,28.79563904,1945.91796875,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,23.87169075,1945.79321289,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,19.21839523,1946.12329102,18.29480743,0.00000000,3,3,SPAWN); //Trailer 1
		CreateVehicle(591,993.73010254,2407.76538086,11.47449589,0.00000000,86,1,SPAWN); //Trailer 3
		CreateVehicle(591,988.40051270,2407.92626953,11.47449589,0.00000000,86,1,SPAWN); //Trailer 3
		CreateVehicle(591,981.89581299,2407.91723633,11.47449589,0.00000000,86,1,SPAWN); //Trailer 3
		CreateVehicle(591,975.89056396,2407.88989258,11.47449589,0.00000000,86,1,SPAWN); //Trailer 3
		CreateVehicle(591,970.84167480,2408.35058594,11.47449589,0.00000000,86,1,SPAWN); //Trailer 1
		CreateVehicle(591,965.35260010,2408.32617188,11.47449589,0.00000000,86,1,SPAWN); //Trailer 1
		CreateVehicle(591,959.35986328,2408.03320312,11.47449589,0.00000000,86,1,SPAWN); //Trailer 1
		CreateVehicle(591,953.10485840,2407.97778320,11.47449589,0.00000000,86,1,SPAWN); //Trailer 1
		CreateVehicle(450,946.60137939,2408.35205078,11.47449589,0.00000000,86,1,SPAWN); //Trailer 2
		CreateVehicle(450,940.85058594,2408.36279297,11.47449589,0.00000000,86,1,SPAWN); //Trailer 2
		CreateVehicle(450,935.10058594,2408.37353516,11.47449589,0.00000000,86,1,SPAWN); //Trailer 2
		CreateVehicle(450,929.35058594,2408.38427734,11.47449589,0.00000000,86,1,SPAWN); //Trailer 2
		CreateVehicle(403,984.68225098,2489.86401367,11.52031231,181.48999023,86,1,SPAWN); //Linerunner
		CreateVehicle(403,979.18432617,2490.03515625,11.52031231,181.48864746,86,1,SPAWN); //Linerunner
		CreateVehicle(403,973.43640137,2490.21484375,11.52031231,181.48864746,86,1,SPAWN); //Linerunner
		CreateVehicle(403,967.68835449,2490.39453125,11.52031231,181.48864746,86,1,SPAWN); //Linerunner
		CreateVehicle(514,962.12670898,2489.25732422,11.51998711,179.41497803,86,1,SPAWN); //Tanker
		CreateVehicle(514,955.86145020,2489.32714844,11.51998711,179.41223145,86,1,SPAWN); //Tanker
		CreateVehicle(514,949.81756592,2489.51464844,11.51998711,179.41223145,86,1,SPAWN); //Tanker
		CreateVehicle(514,943.89093018,2489.48144531,11.51998711,179.41223145,86,1,SPAWN); //Tanker
		CreateVehicle(514,938.47253418,2489.90380859,11.97403336,177.42999268,86,86,SPAWN); //Roadtrain
		CreateVehicle(514,931.70336914,2490.47534180,11.97403336,177.42919922,86,86,SPAWN); //Roadtrain
		CreateVehicle(514,925.45465088,2490.30981445,11.97403336,181.39916992,86,86,SPAWN); //Roadtrain
		CreateVehicle(514,919.45556641,2490.15136719,11.97403336,181.39526367,86,86,SPAWN); //Roadtrain
		//wozy frakcyjne
		pojazdpd[0] = AddStaticVehicle(552,1025.90002441,1733.69995117,10.60000038,305.99670410,6,6); //Utility
		pojazdpd[1] = AddStaticVehicle(552,1025.39941406,1741.29980469,10.60000038,303.99719238,6,6); //Utility
		pojazdpd[2] = AddStaticVehicle(552,1025.00000000,1748.90002441,10.60000038,302.00000000,6,6); //Utility
		pojazdpd[3] = AddStaticVehicle(552,1025.69995117,1757.09997559,10.60000038,300.00000000,6,6); //Utility
		pojazdpd[4] = AddStaticVehicle(552,1025.19995117,1765.19995117,10.60000038,304.00000000,6,6); //Utility
		pojazdpd[5] = AddStaticVehicle(552,1025.00000000,1773.40002441,10.60000038,306.00000000,6,6); //Utility
		pojazdpd[6] = AddStaticVehicle(552,1024.90002441,1781.30004883,10.60000038,310.00000000,6,6); //Utility
		pojazdpd[7] = AddStaticVehicle(552,1024.90002441,1789.09997559,10.60000038,310.00000000,6,6); //Utility
		pojazdpd[8] = AddStaticVehicle(525,1075.19995117,1787.09997559,10.50000000,90.00000000,6,6); //Tow Truck
		pojazdpd[9] = AddStaticVehicle(525,1075.09997559,1780.59997559,10.80000019,90.00000000,6,6); //Tow Truck
		pojazdpd[10] = AddStaticVehicle(525,1075.00000000,1773.19921875,10.60000038,87.99499512,6,6); //Tow Truck
		pojazdpd[11] = AddStaticVehicle(525,1074.90002441,1766.30004883,10.80000019,88.00000000,6,6); //Tow Truck
		pojazdpd[12] = AddStaticVehicle(525,1074.40002441,1759.69995117,10.80000019,88.00000000,6,6); //Tow Truck
		pojazdpd[13] = AddStaticVehicle(525,1074.19995117,1753.00000000,10.80000019,88.00000000,6,6); //Tow Truck
		pojazdpd[14] = AddStaticVehicle(525,1074.30004883,1746.00000000,10.80000019,88.00000000,6,6); //Tow Truck
		pojazdpd[15] = AddStaticVehicle(525,1074.50000000,1739.30004883,10.80000019,89.50000000,6,6); //Tow Truck
		pojazdpd[16] = AddStaticVehicle(525,1074.40002441,1731.69995117,10.80000019,89.75000000,6,6); //Tow Truck
		pojazdpd[17] = AddStaticVehicle(583,1049.59997559,1777.80004883,10.19999981,0.00000000,6,6); //Tug
		pojazdpd[18] = AddStaticVehicle(583,1049.59997559,1771.90002441,10.19999981,0.00000000,6,6); //Tug
		pojazdpd[19] = AddStaticVehicle(583,1049.69995117,1766.00000000,10.10000038,0.00000000,6,6); //Tug
		pojazdpd[20] = AddStaticVehicle(583,1049.69995117,1759.90002441,10.19999981,0.00000000,6,6); //Tug
		pojazdpd[21] = AddStaticVehicle(583,1049.69995117,1754.50000000,10.19999981,0.00000000,6,6); //Tug
		pojazdpd[22] = AddStaticVehicle(583,1049.80004883,1747.50000000,10.30000019,0.00000000,6,6); //Tug
		pojazdpd[23] = AddStaticVehicle(583,1049.80004883,1741.09997559,10.19999981,0.00000000,6,6); //Tug
		pojazdpd[24] = AddStaticVehicle(583,1049.80004883,1734.90002441,10.19999981,0.00000000,6,6); //Tug
		pojazdpd[25] = AddStaticVehicle(583,1049.80004883,1729.40002441,10.30000019,0.00000000,6,6); //Tug
		pojazdpd[26] = AddStaticVehicle(552,1055.30004883,1775.30004883,10.60000038,0.00000000,6,6); //Utility
		pojazdpd[27] = AddStaticVehicle(525,1055.40002441,1765.40002441,10.80000019,0.00000000,6,6); //Tow Truck
		pojazdpd[28] = AddStaticVehicle(552,1055.50000000,1755.69995117,10.60000038,0.00000000,6,6); //Utility
		pojazdpd[29] = AddStaticVehicle(525,1055.50000000,1746.30004883,10.80000019,0.00000000,6,6); //Tow Truck
		pojazdpd[30] = AddStaticVehicle(552,1055.59997559,1737.50000000,10.60000038,0.00000000,6,6); //Utility
		pojazdpd[31] = AddStaticVehicle(524,1040.59997559,1732.50000000,11.89999962,0.00000000,6,6); //Cement Truck
		pojazdpd[32] = AddStaticVehicle(524,1062.40002441,1733.30004883,11.89999962,0.00000000,6,6); //Cement Truck
		pojazdpd[33] = AddStaticVehicle(530,1055.69995117,1730.90002441,10.60000038,0.00000000,6,6); //Forklift
		pojazdpd[34] = AddStaticVehicle(530,1040.19995117,1797.00000000,10.60000038,202.00000000,6,6); //Forklift
		pojazdpd[35] = AddStaticVehicle(530,1042.69995117,1797.30004883,10.60000038,208.00000000,6,6); //Forklift
		pojazdpd[36] = AddStaticVehicle(530,1045.09997559,1797.69995117,10.60000038,208.00000000,6,6); //Forklift
		pojazdlot[0] = AddStaticVehicle(407,1442.00000000,1550.19995117,11.19999981,0.00000000,3,3); //Firetruck
		pojazdlot[1] = AddStaticVehicle(485,1432.40002441,1520.00000000,10.50000000,322.00000000,-1,-1); //Baggage
		pojazdlot[2] = AddStaticVehicle(485,1428.30004883,1520.00000000,10.50000000,321.99829102,-1,-1); //Baggage
		pojazdlot[3] = AddStaticVehicle(485,1424.59997559,1520.19995117,10.50000000,321.99829102,-1,-1); //Baggage
		pojazdlot[4] = AddStaticVehicle(485,1420.90002441,1520.40002441,10.50000000,321.99829102,-1,-1); //Baggage
		pojazdlot[5] = AddStaticVehicle(485,1416.69995117,1520.59997559,10.50000000,321.99829102,-1,-1); //Baggage
		pojazdlot[6] = AddStaticVehicle(583,1328.59997559,1278.69995117,11.10000038,359.99633789,1,1); //Tug
		pojazdlot[7] = AddStaticVehicle(606,1415.09997559,1506.19995117,10.89999962,180.00000000,-1,-1); //Luggage Trailer A
		pojazdlot[8] = AddStaticVehicle(606,1417.50000000,1506.09997559,10.89999962,180.00000000,-1,-1); //Luggage Trailer A
		pojazdlot[9] = AddStaticVehicle(607,1429.59997559,1506.09997559,10.89999962,180.00000000,-1,-1); //Luggage Trailer B
		pojazdlot[10] = AddStaticVehicle(607,1432.80004883,1506.00000000,10.89999962,180.00000000,-1,-1); //Luggage Trailer B
		pojazdlot[11] = AddStaticVehicle(608,1422.80004883,1506.30004883,11.39999962,180.00000000,1,1); //Stair Trailer
		pojazdlot[12] = AddStaticVehicle(608,1425.30004883,1506.19995117,11.39999962,180.00000000,-1,-1); //Stair Trailer
		pojazdlot[13] = AddStaticVehicle(511,1288.40002441,1324.30004883,12.30000019,270.00000000,1,1); //Beagle
		pojazdlot[14] = AddStaticVehicle(511,1289.09997559,1361.50000000,12.30000019,270.00000000,1,1); //Beagle
		pojazdlot[15] = AddStaticVehicle(593,1287.50000000,1390.00000000,11.39999962,270.00000000,1,1); //Dodo
		pojazdlot[16] = AddStaticVehicle(593,1287.50000000,1422.80004883,11.39999962,270.00000000,1,1); //Dodo
		pojazdlot[17] = AddStaticVehicle(593,1288.19995117,1447.50000000,11.39999962,270.00000000,1,1); //Dodo
		pojazdlot[18] = AddStaticVehicle(593,1287.90002441,1481.50000000,11.39999962,270.00000000,1,1); //Dodo
		pojazdlot[19] = AddStaticVehicle(519,1543.50000000,1509.50000000,11.89999962,90.00000000,-1,-1); //Shamal
		pojazdlot[20] = AddStaticVehicle(519,1544.00000000,1487.69995117,11.89999962,90.00000000,-1,-1); //Shamal
		pojazdlot[21] = AddStaticVehicle(519,1543.90002441,1466.59997559,11.89999962,90.00000000,-1,-1); //Shamal
		pojazdlot[22] = AddStaticVehicle(519,1544.30004883,1445.50000000,11.89999962,90.00000000,-1,-1); //Shamal
		pojazdlot[23] = AddStaticVehicle(519,1544.69995117,1424.09997559,11.89999962,90.00000000,-1,-1); //Shamal
		pojazdlot[24] = AddStaticVehicle(519,1544.69995117,1402.09997559,11.89999962,90.00000000,-1,-1); //Shamal
		pojazdlot[25] = AddStaticVehicle(519,1545.19995117,1380.30004883,11.89999962,90.00000000,-1,-1); //Shamal
		pojazdlot[26] = AddStaticVehicle(511,1333.09997559,1565.19995117,12.30000019,270.00000000,1,1); //Beagle
		pojazdlot[27] = AddStaticVehicle(511,1332.59997559,1588.00000000,12.30000019,270.00000000,1,1); //Beagle
		pojazdlot[28] = AddStaticVehicle(511,1333.19995117,1612.00000000,12.30000019,270.00000000,1,1); //Beagle
		pojazdlot[29] = AddStaticVehicle(511,1334.09997559,1683.40002441,12.30000019,270.00000000,1,1); //Beagle
		pojazdlot[30] = AddStaticVehicle(511,1335.40002441,1784.00000000,12.30000019,270.00000000,1,1); //Beagle
		pojazdlot[31] = AddStaticVehicle(553,1533.69995117,1839.69995117,13.10000038,124.00000000,1,1); //Nevada
		pojazdlot[32] = AddStaticVehicle(553,1534.09997559,1803.59997559,13.10000038,123.99719238,1,1); //Nevada
		pojazdlot[33] = AddStaticVehicle(553,1535.80004883,1763.00000000,13.10000038,123.99719238,1,1); //Nevada
		pojazdlot[34] = AddStaticVehicle(553,1537.30004883,1728.40002441,13.10000038,123.99719238,1,1); //Nevada
		pojazdlot[35] = AddStaticVehicle(553,1538.80004883,1692.50000000,13.10000038,123.99719238,1,1); //Nevada
		pojazdlot[36] = AddStaticVehicle(553,1538.69995117,1657.19995117,13.10000038,123.99719238,1,1); //Nevada
		pojazdlot[37] = AddStaticVehicle(593,1350.59997559,1851.59997559,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[38] = AddStaticVehicle(593,1365.80004883,1852.00000000,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[39] = AddStaticVehicle(593,1379.50000000,1852.30004883,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[40] = AddStaticVehicle(593,1393.69995117,1852.59997559,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[41] = AddStaticVehicle(593,1408.40002441,1852.90002441,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[42] = AddStaticVehicle(593,1423.19995117,1853.19995117,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[43] = AddStaticVehicle(593,1437.50000000,1853.50000000,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[44] = AddStaticVehicle(593,1452.09997559,1853.80004883,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[45] = AddStaticVehicle(593,1466.69995117,1854.09997559,11.39999962,180.00000000,1,1); //Dodo
		pojazdlot[46] = AddStaticVehicle(583,1325.50000000,1278.69995117,11.10000038,359.99450684,1,1); //Tug
		pojazdlot[47] = AddStaticVehicle(583,1322.30004883,1278.69995117,11.10000038,359.99450684,1,1); //Tug
		pojazdlot[48] = AddStaticVehicle(583,1319.00000000,1278.69995117,11.10000038,359.99450684,1,1); //Tug
		pojazdlot[49] = AddStaticVehicle(583,1316.00000000,1278.69995117,11.10000038,359.99450684,1,1); //Tug
		pojazdlot[50] = AddStaticVehicle(583,1312.50000000,1278.69995117,11.10000038,359.99450684,1,1); //Tug
		pojazdlot[51] = AddStaticVehicle(583,1309.30004883,1278.69995117,11.10000038,359.99450684,1,1); //Tug
		pojazdlot[52] = AddStaticVehicle(583,1306.00000000,1278.69995117,11.10000038,359.99450684,1,1); //Tug
		pojazdlot[53] = AddStaticVehicle(553,1571.40002441,1202.90002441,13.00000000,0.00000000,1,1); //Nevada
		pojazdlot[54] = AddStaticVehicle(553,1602.00000000,1202.90002441,13.00000000,0.00000000,1,1); //Nevada
		pojazdlot[55] = AddStaticVehicle(487,1443.80004883,1427.09997559,11.10000038,0.00000000,1,1); //Maverick
		pojazdlot[56] = AddStaticVehicle(487,1428.80004883,1427.00000000,11.10000038,0.00000000,1,1); //Maverick
		pojazdlot[57] = AddStaticVehicle(487,1428.90002441,1411.19995117,11.10000038,0.00000000,1,1); //Maverick
		pojazdlot[58] = AddStaticVehicle(487,1442.80004883,1411.30004883,11.10000038,0.00000000,1,1); //Maverick
		pojazdlot[59] = AddStaticVehicle(417,1381.30004883,1228.00000000,11.10000038,0.00000000,-1,-1); //Leviathan
		pojazdlot[60] = AddStaticVehicle(417,1401.19995117,1227.59997559,11.30000019,0.00000000,-1,-1); //Leviathan
		pojazdlot[61] = AddStaticVehicle(417,1422.50000000,1226.80004883,11.10000038,0.00000000,-1,-1); //Leviathan
		pojazdyST[0] = AddStaticVehicle(515,-33.70000076,1536.59997559,13.89999962,231.99829102,3,-1); //Roadtrain
		pojazdyST[1] = AddStaticVehicle(515,61.29999924,1527.40002441,13.89999962,89.99182129,3,-1); //Roadtrain
		pojazdyST[2] = AddStaticVehicle(515,-28.50000000,1548.50000000,13.89999962,237.99133301,3,-1); //Roadtrain
		pojazdyST[3] = AddStaticVehicle(515,-25.19921875,1554.69921875,13.89999962,237.99133301,3,-1); //Roadtrain
		pojazdyST[4] = AddStaticVehicle(435,-7.19921875,1568.09960938,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[5] = AddStaticVehicle(435,-1.50000000,1568.40002441,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[6] = AddStaticVehicle(435,4.19999981,1568.69995117,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[7] = AddStaticVehicle(435,10.00000000,1568.80004883,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[8] = AddStaticVehicle(435,16.00000000,1568.50000000,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[9] = AddStaticVehicle(435,21.60000038,1569.50000000,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[10] = AddStaticVehicle(435,27.60000038,1569.69995117,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[11] = AddStaticVehicle(435,34.09999847,1569.40002441,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[12] = AddStaticVehicle(435,-13.10000038,1567.40002441,13.39999962,180.00000000,-1,-1); //Trailer 1
		pojazdyST[13] = AddStaticVehicle(515,59.00000000,1550.40002441,13.89999962,93.99487305,3,-1); //Roadtrain
		pojazdyST[14] = AddStaticVehicle(515,61.29999924,1542.40002441,13.89999962,91.99987793,3,-1); //Roadtrain
		pojazdyST[15] = AddStaticVehicle(515,61.59999847,1535.30004883,13.89999962,89.99536133,3,-1); //Roadtrain
		pojazdyST[16] = AddStaticVehicle(515,-30.20000076,1541.50000000,13.89999962,231.99829102,3,-1); //Roadtrain
		pojazdyST[17] = AddStaticVehicle(482,61.29999924,1515.00000000,13.00000000,68.00000000,3,-1); //Burrito
		pojazdyST[18] = AddStaticVehicle(482,59.90000153,1512.00000000,13.00000000,67.99487305,3,-1); //Burrito
		pojazdyST[19] = AddStaticVehicle(482,51.40000153,1497.50000000,13.00000000,37.99487305,3,-1); //Burrito
		pojazdyST[20] = AddStaticVehicle(482,47.79999924,1494.00000000,13.00000000,37.99487305,3,-1); //Burrito
		pojazdyST[21] = AddStaticVehicle(482,43.70000076,1490.69995117,13.00000000,33.99487305,3,-1); //Burrito
		pojazdyST[22] = AddStaticVehicle(482,39.09999847,1487.09997559,13.00000000,31.99487305,3,-1); //Burrito
		pojazdyST[23] = AddStaticVehicle(482,34.70000076,1485.00000000,13.00000000,31.99218750,3,-1); //Burrito
		pojazdyST[24] = AddStaticVehicle(515,-21.39999962,1561.19995117,13.89999962,237.99133301,3,-1); //Roadtrain
		pojazdpolicji[0] = CreateVehicle(598, 2889.3022, 2249.9968, 10.7341, 179, 1, 0, 120000); //LVPD
		pojazdpolicji[1] = CreateVehicle(598, 2884.4282, 2250.0396, 10.7341, 179, 1, 0, 120000); //LVPD
		pojazdpolicji[2] = CreateVehicle(598, 2879.3354, 2250.0303, 10.7341, 179, 1, 0, 120000); //LVPD
		pojazdpolicji[3] = CreateVehicle(598, 2870.6108, 2250.1995, 10.7341, 179, 1, 0, 120000); //LVPD
		pojazdpolicji[4] = CreateVehicle(598, 2864.8987, 2250.2576, 10.7341, 179, 1, 0, 120000); //LVPD
		pojazdpolicji[5] = CreateVehicle(598, 2860.291, 2250.2512, 10.7341, 179, 1, 0, 120000); //LVPD
		pojazdpolicji[6] = CreateVehicle(599, 2860.2393, 2167.5469, 10.7341, 360, 1, 0, 120000); //Police Ranger
		pojazdpolicji[7] = CreateVehicle(599, 2865.585, 2167.6709, 10.7341, 360, 1, 0, 120000); //Police Ranger
		pojazdpolicji[8] = CreateVehicle(599, 2871.3254, 2167.6853, 10.7341, 360, 1, 0, 120000); //Police Ranger
		pojazdpolicji[9] = CreateVehicle(490, 2880.0225, 2168.2202, 10.7341, 360, 1, 0, 120000); //FBI Rancher
		pojazdpolicji[10] = CreateVehicle(490, 2884.2751, 2168.2043, 10.7341, 360, 1, 0, 120000); //FBI Rancher
		pojazdpolicji[11] = CreateVehicle(490, 2888.9231, 2168.175, 10.7341, 360, 1, 0, 120000); //FBI Rancher
		pojazdpolicji[12] = CreateVehicle(497, 2919.2808, 2237.4773, 35.084, 89, 1, 0, 120000); //Police Maverick
		pojazdpolicji[13] = CreateVehicle(469, 2920.5603, 2188.699, 35.084, 89, 1, 0, 120000); //Sparrow
		pojazdyET[0] = AddStaticVehicle(482,-2149.00000000,-760.59960938,32.29999924,270.49987793,86,86); //Burrito
		pojazdyET[1] = AddStaticVehicle(482,-2148.89941406,-763.69921875,32.32999802,269.74731445,86,86); //Burrito
		pojazdyET[2] = AddStaticVehicle(515,-2123.69921875,-757.89941406,33.20000076,0.00000000,86,86); //Roadtrain
		pojazdyET[3] = AddStaticVehicle(435,-2123.50000000,-771.00000000,32.70000076,0.00000000,86,86); //Trailer 1
		pojazdyET[4] = AddStaticVehicle(514,-2123.50000000,-782.50000000,32.70000076,0.00000000,86,86); //Tanker
		pojazdyET[5] = AddStaticVehicle(450,-2123.30004883,-795.40002441,32.70000076,0.00000000,86,86); //Trailer 2
		pojazdyET[6] = AddStaticVehicle(514,-2133.00000000,-818.29998779,32.70000076,0.00000000,86,86); //Tanker
		pojazdyET[7] = AddStaticVehicle(515,-2149.19995117,-818.20001221,33.20000076,0.00000000,86,86); //Roadtrain
		pojazdyET[8] = AddStaticVehicle(450,-2132.89990234,-830.50000000,32.70000076,0.00000000,86,86); //Trailer 2
		pojazdyET[9] = AddStaticVehicle(435,-2149.10009766,-830.09997559,32.70000076,0.00000000,86,86); //Trailer 1
		pojazdyET[10] = AddStaticVehicle(482,-2148.89990234,-766.79998779,32.29999924,270.00000000,86,86); //Burrito
		pojazdyET[11] = AddStaticVehicle(482,-2148.89990234,-769.90002441,32.29999924,270.00000000,86,86); //Burrito
		pojazdyET[12] = AddStaticVehicle(482,-2148.89990234,-773.20001221,32.29999924,270.00000000,86,86); //Burrito
		pojazdyET[13] = AddStaticVehicle(514,-2149.39990234,-793.59997559,32.70000076,0.00000000,86,86); //Tanker
		pojazdyET[14] = AddStaticVehicle(515,-2133.50000000,-782.09997559,33.20000076,0.00000000,86,86); //Roadtrain
		pojazdyET[15] = AddStaticVehicle(591,-2149.39990234,-805.50000000,32.70000076,0.00000000,86,86); //Trailer 3
		pojazdyET[16] = AddStaticVehicle(435,-2133.30004883,-794.20001221,32.70000076,0.00000000,86,86); //Trailer 1
		pojazdyET[17] = AddStaticVehicle(413,-2133.50000000,-760.50000000,32.20000076,90.00000000,86,86); //Pony
		pojazdyET[18] = AddStaticVehicle(413,-2133.50000000,-763.40002441,32.20000076,90.50000000,86,86); //Pony
		pojazdyET[19] = AddStaticVehicle(459,-2133.19995117,-766.50000000,32.20000076,90.00000000,86,86); //Berkley's RC Van
		pojazdyET[20] = AddStaticVehicle(459,-2133.19995117,-769.90002441,32.20000076,90.25000000,86,86); //Berkley's RC Van
		ricowoz[0] = AddStaticVehicleEx(482,-1033.50000000,-1019.69921875,129.50000000,67.99987793,86,86,SPAWN); //Burrito
		ricowoz[1] = AddStaticVehicleEx(482,-1035.89941406,-1025.69921875,129.50000000,67.99987793,86,1,SPAWN); //Burrito
		ricowoz[2] = AddStaticVehicleEx(482,-1038.59960938,-1032.19921875,129.50000000,67.99987793,86,1,SPAWN); //Burrito
		ricowoz[3] = AddStaticVehicleEx(482,-1041.69921875,-1039.59960938,129.50000000,67.99987793,86,1,SPAWN); //Burrito
		ricowoz[4] = AddStaticVehicleEx(482,-1044.89941406,-1047.19921875,129.50000000,67.99987793,86,1,SPAWN); //Burrito
		ricowoz[5] = AddStaticVehicleEx(515,-1050.69921875,-939.19921875,130.39999390,139.99877930,86,86,SPAWN); //Roadtrain
		ricowoz[6] = AddStaticVehicleEx(515,-1188.90002441,-959.59997559,130.39999390,221.99523926,86,86,SPAWN); //Roadtrain
		ricowoz[7] = AddStaticVehicleEx(515,-1031.19921875,-940.29980469,130.39999390,139.99877930,86,86,SPAWN); //Roadtrain
		ricowoz[8] = AddStaticVehicleEx(515,-1018.29980469,-940.39941406,130.39999390,139.99877930,86,86,SPAWN); //Roadtrain
		ricowoz[9] = AddStaticVehicleEx(435,-1014.50000000,-978.59997559,129.89999390,34.00000000,1,1,SPAWN); //Trailer 1
		ricowoz[10] = AddStaticVehicleEx(435,-1022.50000000,-978.40002441,129.89999390,33.99719238,1,1,SPAWN); //Trailer 1
		ricowoz[11] = AddStaticVehicleEx(435,-1031.09960938,-978.09960938,129.89999390,33.99719238,1,1,SPAWN); //Trailer 1
		ricowoz[12] = AddStaticVehicleEx(435,-1039.09960938,-979.00000000,129.89999390,33.99719238,1,1,SPAWN); //Trailer 1
		ricowoz[13] = AddStaticVehicleEx(515,-1041.59960938,-939.79980469,130.39999390,139.99877930,86,86,SPAWN); //Roadtrain
		ricowoz[14] = AddStaticVehicleEx(515,-1182.30004883,-953.70001221,130.39999390,221.99523926,86,86,SPAWN); //Roadtrain
		ricowoz[15] = AddStaticVehicleEx(515,-1174.80004883,-947.29998779,130.39999390,221.99523926,86,86,SPAWN); //Roadtrain
		ricowoz[16] = AddStaticVehicleEx(515,-1167.40002441,-940.90002441,130.39999390,221.99523926,86,86,SPAWN); //Roadtrain
		ricowoz[17] = AddStaticVehicleEx(515,-1161.19995117,-935.20001221,130.39999390,221.99523926,86,86,SPAWN); //Roadtrain
		ricowoz[18] = AddStaticVehicleEx(450,-1145.90002441,-923.90002441,129.89999390,180.00000000,-1,-1,SPAWN); //Trailer 2
		ricowoz[19] = AddStaticVehicleEx(450,-1140.80004883,-923.79998779,129.89999390,180.00000000,-1,-1,SPAWN); //Trailer 2
		ricowoz[20] = AddStaticVehicleEx(591,-1135.30004883,-923.59997559,129.89999390,182.00000000,-1,-1,SPAWN); //Trailer 3
		ricowoz[21] = AddStaticVehicleEx(584,-1130.09997559,-924.70001221,130.39999390,182.00000000,-1,-1,SPAWN); //Trailer 3
		ricowoz[22] = AddStaticVehicleEx(584,-1125.00000000,-924.59997559,130.39999390,181.99951172,-1,-1,SPAWN); //Trailer 3

		// ============================================== QUAD KONKURSOWY ========================================
        pojazdznaleziony = DOF_GetInt("Truck/konkurs.ini", "Znalaziony");
		if(pojazdznaleziony == 1)
		{
			print("Zgubiona QUAD nie zosta≥ znaleziony");
        	pojazdkonkursowy = AddStaticVehicle(471,1839.0740,-2693.5940,13.0204,91.9348,0,1);//
		}
		if(pojazdznaleziony == 0)
		{
		    print("Zgubiona QUAD zosta≥ znaleziony");
		}
        // ============================================== QUAD KONKURSOWY ========================================
		

	    return 1;
	}
	CMD:znalazlem(playerid, params[])
	{
	    if(pojazdznaleziony == 1)
	    {
	    	if(DoInRange(4, playerid, 1839.0740,-2693.5940,13.0204))
			{
		        dDodajKase(playerid, 500000);
		        format(dstring,sizeof(dstring),""C_CZERWONY"UWAGA! "C_NIEBIESKI"Uøytkownik "C_ZIELONY"%s "C_NIEBIESKI"znalaz≥ zgubiony QUAD! "C_ZOLTY"GRATULUJEMY!", Nick(playerid));
				SendClientMessageToAll(KOLOR_ZIELONY,dstring);
				pojazdznaleziony = 0;
				DOF_SetInt("Truck/konkurs.ini", "Znalaziony", 0);
				DestroyVehicle(pojazdkonkursowy);
			}
			if(!DoInRange(4, playerid, 1839.0740,-2693.5940,13.0204))
			{
			    SendClientMessage(playerid, KOLOR_CZERWONY, "Nie znajdujesz siÍ przy zgubionym Quadzie!");
			}
		}
		else if(pojazdznaleziony == 0)
	    {
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Konkurs na zagubiony QUAD jest zakoÒczony!");
		}
		return 1;
	}
	CMD:rebuildc(playerid, params[])
	{
	    if(!ToAdminLevel(playerid, 3))
	        return 1;

    	for(new nr = 1; nr < LIMIT_SAMOCHODOW; nr++)
		{
		    DestroyVehicle(nr);
		}
		CreateWozy();
		WczytajWozy();
		SendClientMessage(playerid, KOLOR_ZIELONY, "Prze≥adowano wozy!");
		return 1;
	}

	CMD:rebuilbo(playerid, params[])
	{
	    if(!ToAdminLevel(playerid, 3))
	        return 1;

        SendRconCommand("reloadfs obiekty");
        SendClientMessage(playerid, KOLOR_ZIELONY, "Prze≥adowano obiekty!");
        return 1;
	}

	forward SendCompileInfo(id);
	public SendCompileInfo(id)
	{
	    new str[128];
		format(str,sizeof(str),""C_BIALY"Mapa skompilowana "C_CZERWONY"%s "C_BIALY"przez "C_CZERWONY"%s. "C_BIALY"Aktualna wersja to: "C_CZERWONY"%s",DATA,NICK,WERSJAMAPY);
	    SendClientMessage(id, KOLOR_BIALY, str);
	    return 1;
	}

    CMD:jj(playerid, params[])
    {
        if(AFK[playerid] == 1)
        {
			if(PlayerInfo[playerid][pAdmin] == 0)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"Gracz "C_CZERWONY"%s "C_NIEBIESKI"Juø Jest", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=0;
			}
			else if(PlayerInfo[playerid][pAdmin] == 1)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"Moderator "C_CZERWONY"%s "C_NIEBIESKI"Juø Jest", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=0;
			}
			else if(PlayerInfo[playerid][pAdmin] == 2)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"Admin "C_CZERWONY"%s "C_NIEBIESKI"Juø Jest", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=0;
			}
			else if(PlayerInfo[playerid][pAdmin] ==3)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"HeadAdmin "C_CZERWONY"%s "C_NIEBIESKI"Juø Jest", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=0;
			}
		}
		else if(AFK[playerid] != 1)
		{
			SendClientMessage(playerid, KOLOR_CZERWONY, "Nie masz statusu 'zw'");
		}
	    return 1;
    }

    CMD:zw(playerid, params[])
    {
        if(AFK[playerid] == 0)
        {
			if(PlayerInfo[playerid][pAdmin] == 0)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"Gracz "C_CZERWONY"%s "C_NIEBIESKI"Zaraz Wraca", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=1;
			}
			else if(PlayerInfo[playerid][pAdmin] == 1)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"Moderator "C_CZERWONY"%s "C_NIEBIESKI"Zaraz Wraca", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=1;
			}
			else if(PlayerInfo[playerid][pAdmin] == 2)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"Admin "C_CZERWONY"%s "C_NIEBIESKI"Zaraz Wraca", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=1;
			}
			else if(PlayerInfo[playerid][pAdmin] ==3)
			{
		    	format(dstring,sizeof(dstring),""C_NIEBIESKI"HeadAdmin "C_CZERWONY"%s "C_NIEBIESKI"Zaraz Wraca", Nick(playerid));
		 		SendClientMessageToAll(KOLOR_CZERWONY, dstring);
			    AFK[playerid]=1;
			}
		}
		else if(AFK[playerid] != 0)
		{
			SendClientMessage(playerid, KOLOR_CZERWONY, "Jesteú juø na 'zw'");
		}
	    return 1;
    }

	CMD:rekord(playerid, params[])
	{
	    format(dstring,sizeof(dstring),"Aktualnie jest graczy: %d\nRekord graczy to: %d", teraz, rekord);
	    Info(playerid, dstring);
	    return 1;
	}

	stock GivePlayerMoneyEx(playerid, moneys)
	{
		dDodajKase(playerid, moneys);
		return 1;
	}

	CMD:inferno(playerid, params[])
	{
	    SetPlayerSkin(playerid, 74);
	    SetPlayerScore(playerid, 1);
	    return 1;
	}

stock DajKase(playerid, ile)
{
	new tempDB[15];
	format(query, sizeof query, "SELECT `Kasa` FROM `Gracze` WHERE `login` = '%s'", PlayerName(playerid));
	DBResult = db_query(KASA, query);
	db_get_field(DBResult, 0, tempDB,sizeof tempDB);
	format(query, sizeof query, "UPDATE `Kasa` SET `Kasa` = %d WHERE `login` = '%s'", strlen(tempDB)+ile, PlayerName(playerid));
	db_free_result(db_query(KASA, query));
}

stock StanKasy(playerid)
{
	new tempDB[15];
	format(query, sizeof query, "SELECT `Kasa` FROM `Gracze` WHERE `login` = '%s'", PlayerName(playerid));
	DBResult = db_query(KASA, query);
	db_get_field(DBResult, 0, tempDB,sizeof tempDB);
	db_free_result(DBResult);
	return tempDB;
}

forward WczytajAutomaty();
public WczytajAutomaty()
{
	new file[64];
	for(new nr = 0; nr < LA; nr++)
	{
	    format(file,sizeof(file),AUTOMATY_FILE,nr);
	    if(DOF_FileExists(file))
	 	{
            AutomatInfo[nr][aAktywny] = 1;
            AutomatInfo[nr][aX] = DOF_GetFloat(file,"X");
            AutomatInfo[nr][aY] = DOF_GetFloat(file,"Y");
            AutomatInfo[nr][aZ] = DOF_GetFloat(file,"Z");
            AutomatInfo[nr][aAng] = DOF_GetFloat(file,"Ang");
            Automat[nr] = CreateDynamicObject(1775, AutomatInfo[nr][aX], AutomatInfo[nr][aY], AutomatInfo[nr][aZ], 0.0000, 0.0000, AutomatInfo[nr][aAng]);
            CreateDynamic3DTextLabel("Uøyj /automat\nRegeneracja HP kosztuje 15$\ni regeneruje 10HP",0x00FF40FF,AutomatInfo[nr][aX], AutomatInfo[nr][aY], AutomatInfo[nr][aZ],5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,5.0);
			printf("Zaladowano automat o ID: %d", nr);
		}
		else
		{
		    AutomatInfo[nr][aAktywny] = 0;
		}
	}
	return 1;
}

forward ZapiszAutomat(nr);
public ZapiszAutomat(nr)
{
	new file[25];
	format(file,sizeof(file),AUTOMATY_FILE,nr);
	if(!DOF_FileExists(file))
	{
	    DOF_CreateFile(file);
	}
	DOF_SetFloat(file,"X", AutomatInfo[nr][aX]);
	DOF_SetFloat(file,"Y", AutomatInfo[nr][aY]);
	DOF_SetFloat(file,"Z", AutomatInfo[nr][aZ]);
	DOF_SetFloat(file,"Ang", AutomatInfo[nr][aAng]);
	DOF_SaveFile();
	return 1;
}

CMD:cautomat(playerid, params[])
{
	if(!ToAdminLevel(playerid, 3))
	    return 1;

    new TworzenieAutomatu = 1;
    for(new nr = 0; nr < LA; nr++)
    {
        if(TworzenieAutomatu == 1)
        {
            new file[25];
			format(file,sizeof(file),AUTOMATY_FILE,nr);
            if(!DOF_FileExists(file))
			{
                TworzenieAutomatu = 0;
				new Float: Pos[4];
				GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
				GetPlayerFacingAngle(playerid, Pos[3]);
				AutomatInfo[nr][aX]=Pos[0];
				AutomatInfo[nr][aY]=Pos[1];
				AutomatInfo[nr][aZ]=Pos[2];
				AutomatInfo[nr][aAng]=Pos[3]+180;
			    Automat[nr] = CreateDynamicObject(1775, Pos[0], Pos[1], Pos[2], 0.0000, 0.0000, Pos[3]+180);
			    CreateDynamic3DTextLabel("Uøyj /automat\nJedna puszka kosztuje 10$\ni regeneruje 10HP",0x00FF40FF,Pos[0], Pos[1], Pos[2],5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,5.0);
			    ZapiszAutomat(nr);
			    SetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]+2);
			}
		}
	}
    return 1;
}

CMD:automat(playerid, params[])
{
    new playerState = GetPlayerState(playerid);

    if(playerState != PLAYER_STATE_ONFOOT)
        return SendClientMessage(playerid, 0xFF2F2FFF, "Musisz byÊ pieszo!");

	if(dCzyMaHP(playerid,100.0))
	    return SendClientMessage(playerid, 0xFF2F2FFF, "Jesteú w pe≥ni zdrowy!");

    for(new nr = 0; nr < LA; nr++)
    {
		if(DoInRange(4, playerid, AutomatInfo[nr][aX], AutomatInfo[nr][aY], AutomatInfo[nr][aZ]))
		{
		    if(dWyswietlHP(playerid) == 100.0)
		    {
		        SendClientMessage(playerid, KOLOR_ZIELONY, "Jesteú w pe≥ni zdrowy!");
			}
		    if(dWyswietlHP(playerid) < 100.0)
		    {
	            dUstawHP(playerid,100.0);
	            dDodajKase(playerid,-15);
	            SendClientMessage(playerid, KOLOR_ZIELONY, "Uzdrowi≥eú siÍ!");
			}
		}
	}
	return 1;
}

	stock Zaladunek(playerid, nazwa[], zal[], Float: zaX, Float: zaY, Float: zaZ, wyl[], Float: wyX, Float: wyY, Float: wyZ, kasa, ilescore)
	{
	    SetPVarInt(playerid, "etap", 1);
	    SetPVarString(playerid, "Towar", nazwa);
	    SetPVarString(playerid, "Zaladunek", zal);
	    SetPVarFloat(playerid, "ZaladunekX", zaX);
	    SetPVarFloat(playerid, "ZaladunekY", zaY);
	    SetPVarFloat(playerid, "ZaladunekZ", zaZ);
	    SetPVarString(playerid, "Zaladunek", wyl);
	    SetPVarFloat(playerid, "WyladunekX", wyX);
	    SetPVarFloat(playerid, "WyladunekY", wyY);
	    SetPVarFloat(playerid, "WyladunekZ", wyZ);
	    SetPVarInt(playerid, "Kasa", kasa);
	    ilemadacscore[playerid] = ilescore;

		SetPlayerCheckpoint(playerid, GetPVarFloat(playerid, "ZaladunekX"),GetPVarFloat(playerid, "ZaladunekY"),GetPVarFloat(playerid, "ZaladunekZ"), 5);
		new zalad[260];
		format(zalad, sizeof(zalad), ""C_BEZOWY"Za≥adowa≥eú: "C_ZIELONY"%s\n"C_BEZOWY"Za≥adunek: "C_ZIELONY"%s\n"C_BEZOWY"Wy≥adunek: "C_ZIELONY"%s", nazwa, zal, wyl);
		Zaladowano(playerid,zalad);
	    return 1;
	}

	CMD:sprawdz(playerid, params[])
	{
	    new player;

	    if(!ToPD(playerid))
	        return SendClientMessage(playerid, KOLOR_CZERWONY, ""C_CZERWONY"Musisz byÊ w policji");

	    if(sscanf(params, "d", player))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Wpisz: /sprawdz [ID gracza]");
		    
		if(!OdlegloscGracze(15.0,playerid,player))
  			return SendClientMessage(playerid, KOLOR_CZERWONY, "Gracz jest za daleko.");

		new towar[128];
		GetPVarString(player, "Towar", towar, sizeof(towar));
		new punkciki = GetPVarInt(player, "PunktyToll");

		new s[1000];
        format(dstring, sizeof(dstring),""C_BEZOWY"Gracz: "C_ZIELONY"%s\n", Nick(player));
		strcat(s,dstring);
		format(dstring, sizeof(dstring),""C_BEZOWY"Towar: "C_ZIELONY"%s\n", towar);
		strcat(s,dstring);
		format(dstring, sizeof(dstring),""C_BEZOWY"Stan punktÛw ViaToll: "C_ZIELONY"%d\n", punkciki);
		strcat(s,dstring);
		format(dstring, sizeof(dstring),""C_BEZOWY"Prawo jazdy kategori B: "C_ZIELONY"%d\n", PlayerInfo[player][pPrawkoB]);
		strcat(s,dstring);
		format(dstring, sizeof(dstring),""C_BEZOWY"Prawo jazdy kategori C+E: "C_ZIELONY"%d\n", PlayerInfo[player][pPrawkoCE]);
		strcat(s,dstring);
		format(dstring, sizeof(dstring),""C_BEZOWY"Prawo jazdy kategori A1: "C_ZIELONY"%d\n", PlayerInfo[player][pPrawkoA1]);
		strcat(s,dstring);
		format(dstring, sizeof(dstring),""C_BEZOWY"Punkty karne: "C_ZIELONY"%d"C_BEZOWY"/"C_ZIELONY"24", PlayerInfo[player][pPunkty]);
		strcat(s,dstring);
        ShowPlayerDialog(playerid,GUI_BRAK,DIALOG_STYLE_MSGBOX,"Informacje o przewoøonym towarze.",s,"Zatwierdü","");
		return 1;
	}

	public OnPlayerEnterCheckpoint(playerid)
	{
	    if(IsPlayerInAnyVehicle(playerid))
		{
		    new playerState = GetPlayerState(playerid);
    		if (playerState == PLAYER_STATE_DRIVER)
    		{
				if(GetPVarInt(playerid, "etap") == 1)
				{
		  			SetTimerEx("Laduje", 10000, 0, "d", playerid);
		  			TogglePlayerControllable(playerid,0);
		  			GInfo(playerid, "~r~Ladowanie...", 3);
				}
				if(GetPVarInt(playerid, "etap") == 2)
				{
		  			SetTimerEx("Wyladowuje", 10000, 0, "d", playerid);
		  			TogglePlayerControllable(playerid,0);
		  			GInfo(playerid, "~r~Wyladowanie...", 3);
				}
			}
			else
			{
			    SendClientMessage(playerid, KOLOR_ZIELONY, "Chcia≥ byú oszukiwaÊ co ??");
			}
		}
		return 1;
	}

	forward Laduje(playerid);
	public Laduje(playerid)
	{
		SetPlayerCheckpoint(playerid, GetPVarFloat(playerid, "WyladunekX"),GetPVarFloat(playerid, "WyladunekY"),GetPVarFloat(playerid, "WyladunekZ"), 5);
		SetPVarInt(playerid, "etap", 2);
		TogglePlayerControllable(playerid,1);
		GInfo(playerid, "~g~Zaladowano", 3);
		return 1;
	}

	forward Wyladowuje(playerid);
	public Wyladowuje(playerid)
	{
	    new v=GetPlayerVehicleID(playerid);
		if(GetVehicleModel(v)==403||GetVehicleModel(v)==514||GetVehicleModel(v)==515)//ciÍøarowe
		{
			if(GetVehicleTrailer(v)==0)
			{
				Info(playerid,""C_CZERWONY"Nie masz podczepionej naczepy!");
				return 1;
			}
			new naczepa=GetVehicleModel(GetVehicleTrailer(v));
			if(naczepa==435||naczepa==450||naczepa==591||naczepa==584)
			{
			    new wyplatka = ((GetPVarInt(playerid, "Kasa")/4)*3)+GetPVarInt(playerid, "Kasa");
                dDodajKase(playerid, wyplatka);
			}
		}
	    if(ToBus(v)||GetVehicleModel(v)==593||GetVehicleModel(v)==519||GetVehicleModel(v)==553||GetVehicleModel(v)==563||GetVehicleModel(v)==488||GetVehicleModel(v)==511)
	    {
			dDodajKase(playerid, GetPVarInt(playerid, "Kasa"));
		}
	
	
		DisablePlayerCheckpoint(playerid);
		GivePlayerScore(playerid, ilemadacscore[playerid]);

		SetPVarInt(playerid, "etap", 0);
		TogglePlayerControllable(playerid,1);

		new towar[128];
		GetPVarString(playerid, "Towar", towar, sizeof(towar));

		new zalad[260];
		format(zalad, sizeof(zalad), ""C_BEZOWY"Dostarczy≥eú "C_ZIELONY"%s"C_BEZOWY" w wyznaczone miejsce.\n"C_BEZOWY"W nagrodÍ otrzymujesz "C_ZIELONY"%d$"C_BEZOWY".", towar, GetPVarInt(playerid, "Kasa"));
		Zaladowano(playerid,zalad);
		GInfo(playerid, "~g~Wyladowano", 3);

		DeletePVar(playerid,"etap");
		DeletePVar(playerid,"Towar");
		DeletePVar(playerid,"Zaladunek");
		DeletePVar(playerid,"ZaladunekX");
		DeletePVar(playerid,"ZaladunekY");
		DeletePVar(playerid,"ZaladunekZ");
		DeletePVar(playerid,"Zaladunek");
		DeletePVar(playerid,"WyladunekX");
		DeletePVar(playerid,"WyladunekY");
		DeletePVar(playerid,"WyladunekZ");
		DeletePVar(playerid,"Kasa");
		ilemadacscore[playerid] = 0;

		return 1;
	}

	stock Zaladowano(playerid,text[])
	{
		ShowPlayerDialog(playerid,992,DIALOG_STYLE_MSGBOX,"Informacje o za≥adunku",text,"Zatwierdü","");
		return 1;
	}

	stock SCM(playerid, color, text[])
	{
		SendClientMessage(playerid, color, text);
		return 1;
	}
	stock SCMTA(color, text[])
	{
		SendClientToAll(color, text);
		return 1;
	}

	CMD:laduj(playerid, params[])
	{
	    if(!ToAdminLevel(playerid, 3))
	        return 1;
		WczytajStacje();
		WczytajTexty();
		WczytajDomy();
		WczytajAutomaty();
		SCM(playerid, KOLOR_ZIELONY, "Zaladowano...");
		return 1;
	}

	CMD:tphereall(playerid, params[])
	{
		if(!ToAdminLevel(playerid, 3))
		    return 1;

	    new Float: Pos[3];
	    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		foreach(Player, i)
		{
		    SetPlayerPos(i, Pos[0], Pos[1], Pos[2]);
		    SendClientMessage(i, KOLOR_ZIELONY, "Wszyscy zostali teleportowani do HeadAdministratora");
		}
		return 1;
	}

	CMD:tptoall(playerid, params[])
	{
		if(!ToAdminLevel(playerid, 3))
		    return 1;

		new player;

		if(!sscanf(params, "u", player))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Wpisz: /tptoall [ID gracza]");

	    new Float: Pos[3];
	    GetPlayerPos(player, Pos[0], Pos[1], Pos[2]);
		foreach(Player, i)
		{
		    SetPlayerPos(i, Pos[0], Pos[1], Pos[2]);
		    SendClientMessage(i, KOLOR_ZIELONY, "Wszyscy zostali teleportowani do HeadAdministratora");
		}
		return 1;
	}

	CMD:gora(playerid, params[])
	{
	    if(!ToPOMOC(playerid))
	        return 1;
		MoveObject(podnosnik, 1045.40, 1310.90, 11.899, 2);
		SCM(playerid, KOLOR_ZIELONY, "Podnoúnik jedzie w gÛrÍ");
		return 1;
	}

	CMD:dol(playerid, params[])
	{
	    if(!ToPOMOC(playerid))
	        return 1;
		MoveObject(podnosnik, 1045.40, 1310.90, 9.899, 2);
		SCM(playerid, KOLOR_ZIELONY, "Podnoúnik jedzie w dÛ≥");
		return 1;
	}

	CMD:unmute(playerid, params[])
	{
	    if(!ToAdminLevel(playerid, 2))
	        return 1;

	    new player;
	    if(!sscanf(params, "d", player))
		    return SendClientMessage(playerid, KOLOR_CZERWONY, "Wpisz: /unmute [ID gracza]");

	    format(dstring, sizeof(dstring), ""C_BEZOWY"Odciszy≥eú gracza "C_ZIELONY"%s"C_BEZOWY"["C_ZIELONY"%d"C_BEZOWY"].", Nick(player), player);
		SCM(playerid, KOLOR_ZIELONY, dstring);
		format(dstring, sizeof(dstring), ""C_BEZOWY"Zosta≥eú odciszony.");
		SCM(player, KOLOR_ZIELONY, dstring);

		Odcisz(player);
		return 1;
	}

	CMD:cash(playerid, params[])
	{
	    new player, ilosc;
	    if(PlayerInfo[playerid][pLider] > 0)
	    {
	    	if(!sscanf(params, "dd", player, ilosc))
			{
			    dDodajKase(player, ilosc);
			    format(dstring, sizeof(dstring), ""C_BEZOWY"Da≥eú "C_ZIELONY"%d"C_BEZOWY" graczowi "C_ZIELONY"%s"C_BEZOWY"["C_ZIELONY"%d"C_BEZOWY"].", ilosc, Nick(player), player);
				SCM(playerid, KOLOR_ZIELONY, dstring);
				format(dstring, sizeof(dstring), ""C_BEZOWY"Dosta≥eú "C_ZIELONY"%d"C_BEZOWY" od lidera swojej frakcji.", ilosc);
				SCM(player, KOLOR_ZIELONY, dstring);
			}
			else
			{
	        	SendClientMessage(playerid, KOLOR_CZERWONY, "Uzyj: /cash <id> <iloúÊ>");
			}
		}
		else
		{
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Nie jesteú liderem øadnej frakcji");
		}
		return 1;
	}

CMD:gmx(playerid, params[])
{
	if(!ToAdminLevel(playerid, 2))
		return 1;
	SendRconCommand("gmx");
	foreach(Player, i)
	{
		GInfo(i, "~y~Restart...", 4);
	}
	return 1;
}

CMD:prawko(playerid, params[])
{
	if(zdawanie == 1)
	    return SendClientMessage(playerid, KOLOR_CZERWONY, "Juø ktoú zdaje na prawo jazdy. Poczekaj aø zwolni siÍ miejsce.");

    ShowPlayerDialog(playerid, ZDAWANIE_PYTANIE, DIALOG_STYLE_MSGBOX, "Prawko", "Czy jesteú pewien øe chcesz zdawaÊ na prawo\njazdy?", "Tak", "Nie");

	return 1;
}

	CMD:punkty(playerid, params[])
	{
	    new player, ilosc;
	    if(ToPD(playerid))
	    {
	    	if(!sscanf(params, "dd", player, ilosc))
			{
			    if(playerid != player)
			    {
				    if(ilosc > 0 && ilosc < 25)
				    {
				        new punkcik = PlayerInfo[player][pPunkty]+ilosc;
				        if(punkcik > 25)
				        {
				            new stringeng[256];
					    	PlayerInfo[player][pPunkty]=punkcik;
						    format(stringeng, sizeof(stringeng), ""C_BEZOWY"Da≥eú "C_ZIELONY"%d"C_BEZOWY" punktÛw karnych graczowi "C_ZIELONY"%s"C_BEZOWY"["C_ZIELONY"%d"C_BEZOWY"]. Jego stan konta wynosi "C_BEZOWY"%d/24", ilosc, Nick(player), player, PlayerInfo[player][pPunkty]);
							SendClientMessage(playerid, KOLOR_ZIELONY, stringeng);
							format(stringeng, sizeof(stringeng), ""C_BEZOWY"Dosta≥eú "C_ZIELONY"%d"C_BEZOWY" punktÛw karnych od policjanta "C_ZIELONY"%s"C_BEZOWY"["C_ZIELONY"%d"C_BEZOWY"]. Jego stan konta wynosi "C_BEZOWY"%d/24", ilosc, Nick(playerid), playerid, PlayerInfo[player][pPunkty]);
							SendClientMessage(player, KOLOR_ZIELONY, stringeng);
							PlayerInfo[player][pPunkty]=0;
							PlayerInfo[player][pPrawkoB]=0;
						    PlayerInfo[player][pPrawkoA1]=0;
						    PlayerInfo[player][pPrawkoCE]=0;
						    SendClientMessage(playerid, KOLOR_CZERWONY, "Jego stan punktÛw przekroczy≥ iloúÊ 24 wiÍc zabra≥eú mu prawo jazdy");
							SendClientMessage(player, KOLOR_CZERWONY, "TwÛj stan punktÛw przekroczy≥ iloúÊ 24 wiÍc policjant zabra≥ Ci wszystkie prawa jazdy. Musisz zdaÊ od nowa "C_ZIELONY"/prawko");
							ZapiszKonto(player);

						}
						else if(punkcik < 25)
						{
						    new stringeng[256];
						    PlayerInfo[player][pPunkty]=punkcik;
						    ZapiszKonto(player);
			    			format(stringeng, sizeof(stringeng), ""C_BEZOWY"Da≥eú "C_ZIELONY"%d"C_BEZOWY" punktÛw karnych graczowi "C_ZIELONY"%s"C_BEZOWY"["C_ZIELONY"%d"C_BEZOWY"]. Jego stan konta wynosi "C_BEZOWY"%d/24", ilosc, Nick(player), player, PlayerInfo[player][pPunkty]);
							SendClientMessage(playerid, KOLOR_ZIELONY, stringeng);
							format(stringeng, sizeof(stringeng), ""C_BEZOWY"Dosta≥eú "C_ZIELONY"%d"C_BEZOWY" punktÛw karnych od policjanta "C_ZIELONY"%s"C_BEZOWY"["C_ZIELONY"%d"C_BEZOWY"]. Jego stan konta wynosi "C_BEZOWY"%d/24", ilosc, Nick(playerid), playerid, PlayerInfo[player][pPunkty]);
							SendClientMessage(player, KOLOR_ZIELONY, stringeng);
						}
					}
					else
					{
					    SendClientMessage(playerid, KOLOR_CZERWONY, "Maxymalnie punktÛw moøesz daÊ 25");
					}
				}
				else
				{
				    SendClientMessage(playerid, KOLOR_CZERWONY, "Chcesz ukaraÊ sam siebie? Øal mi CiÍ ch≥opie");
				}
			}
			else
			{
	        	SendClientMessage(playerid, KOLOR_CZERWONY, "Uzyj: /punkty <id> <iloúÊ>");
			}
		}
		else
		{
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Nie jesteú w policji!");
		}
		return 1;
	}

	CMD:czyscall(playerid, params[])
	{
	    if(!ToAdminLevel(playerid, 1))
	        return 1;

	    foreach(Player, i)
	    {
	    	CzyscCzat(i,20);
		}
		SCM(playerid, KOLOR_ZIELONY, "Wyczyszczono...");
		return 1;
	}

CMD:cdom(playerid, params[])
{
	new koszt;

	if(!ToAdminLevel(playerid, 3))
	    return 1;

    if(sscanf(params, "d", koszt))
    	return SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /cdom <koszt>");

    TworzyDomek[playerid] = 1;
    for(new nr = 0; nr < LIMIT_DOMOW; nr++)
	{
	    if(TworzyDomek[playerid] == 1)
	    {
		    if(DomInfo[nr][dAktywny]==0)
			{
				GetPlayerPos(playerid,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ]);
				DomInfo[nr][dWejscieInt]=GetPlayerInterior(playerid);
				DomInfo[nr][dWejscieVir]=GetPlayerVirtualWorld(playerid);
				DomInfo[nr][dWyjscieX]=444.646911;
				DomInfo[nr][dWyjscieY]=508.239044;
				DomInfo[nr][dWyjscieZ]=1001.419494;
				DomInfo[nr][dWyjscieInt]=12;
				format(dstring, sizeof(dstring),"Brak");
				DomInfo[nr][dOpis]=strlen(dstring);
				DomInfo[nr][dKoszt]=koszt;
				DomInfo[nr][dAktywny]=1;
				DomPickup[nr]=CreateDynamicPickup(1273,1,DomInfo[nr][dWejscieX],DomInfo[nr][dWejscieY],DomInfo[nr][dWejscieZ],DomInfo[nr][dWejscieVir],DomInfo[nr][dWejscieInt],-1,45.0);
				format(dstring, sizeof(dstring),""C_ZIELONY"ID domu: "C_ZOLTY"%d\n"C_ZIELONY"W≥aúciciel: "C_ZOLTY"brak\n"C_ZIELONY"Opis: "C_ZOLTY"brak\n"C_ZIELONY"Koszt: "C_ZOLTY"%d", nr, DomInfo[nr][dKoszt]);
				dtexty[nr] = CreateDynamic3DTextLabel(dstring, KOLOR_ZOLTY, DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);
                dikonka[nr] = CreateDynamicMapIcon(DomInfo[nr][dWejscieX], DomInfo[nr][dWejscieY], DomInfo[nr][dWejscieZ], 32, 0, -1, -1, -1, 100.0);
				ZapiszDom(nr);
				TworzyDomek[playerid] = 0;
				format(dstring, sizeof(dstring),"Poprawnie doda≥eú dom o ID: %d",nr);
				SendClientMessage(playerid, KOLOR_ZIELONY, dstring);
			}
		}
	}
	return 1;
}

forward WczytajWozy();
public WczytajWozy()
{
	new file[25];
	for(new nr = 0; nr < ILOSC_WOZOW; nr++)
	{
	    format(file,sizeof(file),WOZY_FILE,nr);
	    if(DOF_FileExists(file))
	 	{
	 	    PrivateCar[nr][cAktywny]=DOF_GetInt(file,"Aktywny");
	 	    PrivateCar[nr][cWlasciciel]=DOF_GetString(file,"Wlasciciel");
	 	    PrivateCar[nr][cModel]=DOF_GetInt(file,"Model");
	 	    PrivateCar[nr][cX]=DOF_GetFloat(file,"X");
	 	    PrivateCar[nr][cY]=DOF_GetFloat(file,"Y");
	 	    PrivateCar[nr][cZ]=DOF_GetFloat(file,"Z");
	 	    PrivateCar[nr][cRX]=DOF_GetFloat(file,"rX");
	 	    PrivateCar[nr][cColor1]=DOF_GetInt(file,"Color1");
	 	    PrivateCar[nr][cColor2]=DOF_GetInt(file,"Color2");
	 	    PrivateCar[nr][cRespawn]=DOF_GetInt(file,"Respawn");
	 	    PrivateCar[nr][cLock]=DOF_GetInt(file,"Lock");

   			KupneWozy[nr] = AddStaticVehicleEx(PrivateCar[nr][cModel],PrivateCar[nr][cX],PrivateCar[nr][cY],PrivateCar[nr][cZ],PrivateCar[nr][cRX],PrivateCar[nr][cColor1],PrivateCar[nr][cColor2],PrivateCar[nr][cRespawn]);
			printf("Zaladowano Prywatny Samochod: %d", nr);
		}
		else
		{
		    PrivateCar[nr][cAktywny] = 0;
		}
	}
	return 1;
}

forward ZapiszWoz(nr);
public ZapiszWoz(nr)
{
	new file[25];
	format(file,sizeof(file),WOZY_FILE,nr);
	if(!DOF_FileExists(file))
	{
	    DOF_CreateFile(file);
	}
	DOF_SetInt(file, "Aktywny", PrivateCar[nr][cAktywny]);
	DOF_SetString(file,"Wlasciciel", PrivateCar[nr][cWlasciciel]);
	DOF_SetInt(file,"Model", PrivateCar[nr][cModel]);
	DOF_SetFloat(file,"X", PrivateCar[nr][cX]);
	DOF_SetFloat(file,"Y", PrivateCar[nr][cY]);
	DOF_SetFloat(file,"Z", PrivateCar[nr][cZ]);
	DOF_SetFloat(file,"rX", PrivateCar[nr][cRX]);
	DOF_SetInt(file,"Color1", PrivateCar[nr][cColor1]);
	DOF_SetInt(file,"Color2", PrivateCar[nr][cColor2]);
	DOF_SetInt(file,"Respawn", PrivateCar[nr][cRespawn]);
	DOF_SetInt(file,"Lock", PrivateCar[nr][cLock]);
	DOF_SaveFile();
	return 1;
}

CMD:dajdj(playerid, params[])
{
	new player,
		stat;
	
	if(!ToAdminLevel(playerid, 3))
	    return 1;
	    
    if(sscanf(params, "dd", player, stat))
   		return 1;
   		
    format(dstring, sizeof(dstring), "Admin %s mianowa≥ CiÍ DJ'em poziom %d", Nick(playerid), stat);
    SendClientMessage(player, KOLOR_ZIELONY, dstring);
    format(dstring, sizeof(dstring), "Mianowa≥eú %s DJ'em poziom %d", Nick(player), stat);
    SendClientMessage(playerid, KOLOR_ZIELONY, dstring);
	PlayerInfo[player][pDJ] = stat;
	ZapiszKonto(player);
	return 1;
}

CMD:ccar(playerid, params[])
{
	if(!ToAdminLevel(playerid, 3))
	    return 1;
	    
	new idwozu, idgracza;
    if(sscanf(params, "dd", idwozu, idgracza))
   		return 1;

    TworzenieWozu = 1;
    for(new nr = 0; nr < ILOSC_WOZOW; nr++)
    {
        if(TworzenieWozu == 1)
        {
            new file[25];
			format(file,sizeof(file),WOZY_FILE,nr);
            if(!DOF_FileExists(file))
			{
		            TworzenieWozu = 0;
			        IdWozu[playerid] = nr;
			        new Float: X, Float: Y, Float: Z, Float: Ang;
			        GetPlayerPos(playerid, X, Y, Z);
			        GetPlayerFacingAngle(playerid, Ang);
			        KupneWozy[nr] = AddStaticVehicleEx(idwozu, X, Y, Z, Ang, -1, -1, SPAWN);
		  	 	    PrivateCar[nr][cAktywny] = 1;
			 	    PrivateCar[nr][cWlasciciel] = strlen(Nick(playerid));
			 	    PrivateCar[nr][cModel] = idwozu;
			 	    PrivateCar[nr][cX] = X;
			 	    PrivateCar[nr][cY] = Y;
			 	    PrivateCar[nr][cZ] = Z;
			 	    PrivateCar[nr][cRX] = Ang;
			 	    PrivateCar[nr][cColor1] = -1;
			 	    PrivateCar[nr][cColor2] = -1;
			 	    PrivateCar[nr][cRespawn] = SPAWN;
			 	    PrivateCar[nr][cLock] = 1;
			 	    ZapiszWoz(nr);
				}
		 }
	}
	return 1;
}

CMD:cmenu(playerid, params[])
{
    if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER)
    {
	    for(new nr = 0; nr < ILOSC_WOZOW; nr++)
		{
		    if(IsPlayerInVehicle(playerid, KupneWozy[nr]))
		    {
	    		ShowPlayerDialog(playerid,GUI_MENUCAR,DIALOG_STYLE_LIST,"Menu pojazdu",""C_BEZOWY"Parkuj\n"C_BEZOWY"Spawn\n"C_ZIELONY"Otworz"C_BEZOWY"/"C_CZERWONY"Zamknij "C_BEZOWY"pojazd","Wybierz","Zamknij");
			}
		}
	}
	else
	{
	    SendClientMessage(playerid, KOLOR_ZIELONY, "Musisz byÊ kierowcπ!");
	}
	return 1;
}

CMD:dcar(playerid, params[])
{

	if(!ToAdminLevel(playerid, 3))
	    return 1;

	if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER)
    {
        for(new nr = 0; nr < ILOSC_WOZOW; nr++)
		{
		    if(IsPlayerInVehicle(playerid, KupneWozy[nr]))
		    {
		        new file[25];
				format(file,sizeof(file),WOZY_FILE,nr);
				DOF_RemoveFile(file);
		        DestroyVehicle(KupneWozy[nr]);
                format(dstring, sizeof(dstring), ""C_BEZOWY"UsuniÍto pojazd o ID: "C_ZIELONY"%d"C_BEZOWY"!", nr);
			}
		}
	}
	else
	{
	    SendClientMessage(playerid, KOLOR_ZIELONY, "Musisz byÊ w pojezdzie!");
	}
	return 1;
}

CMD:chelp(playerid, params[])
{
    ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Pomoc do systemu prywatnych pojazdÛw", "/ccar <idwozu> <id gracza> - Tworzysz pojazd\n/dcar - niszczysz pojazd\n/cmenu - menu kupionego pojazdu", "Ok", "");
    return 1;
}

CMD:kogut(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		new carid = GetPlayerVehicleID(playerid);
		new carmodel = GetVehicleModel(carid);
		if(carmodel == 525)
 		{
	    	if(cmakogut[carid] == 0)
	    	{
     		
     		    kogut[carid] = CreateObject(18646, 0.0,0.0,0.0,0.0,0.0,0.0, 250.0);
				AttachObjectToVehicle(kogut[carid], carid, -0.7, -0.5, 1.4, 0.0, 0.0, 1.5);
     		    kogut2[carid] = CreateObject(18646, 0.0,0.0,0.0,0.0,0.0,0.0, 250.0);
				AttachObjectToVehicle(kogut2[carid], carid, 0.7, -0.5, 1.4, 0.0, 0.0, 1.5);
				cmakogut[carid] = 1;
				SendClientMessage(playerid, KOLOR_ZIELONY, "Przyczepiono kogut!");
			}
			else if(cmakogut[carid] == 1)
			{
				DestroyObject(kogut[carid]);
				DestroyObject(kogut2[carid]);
				cmakogut[carid] = 0;
				SendClientMessage(playerid, KOLOR_ZIELONY, "Odczepiono kogut!");
			}
		}
		else
		{
		    SendClientMessage(playerid, KOLOR_CZERWONY, "Nie jesteú w holowniku!");
		}
	}
	else
	{
 		SendClientMessage(playerid, KOLOR_CZERWONY, "Nie siedzisz w zadnym pojeüdzie!");
	}
	return 1;
}

CMD:konfiskuj(playerid, params[])
{
	if(!ToPD(playerid))
	    return 1;
	    
    new player;
    if(sscanf(params, "d", player))
   		return 1;
   		
	if(!OdlegloscGracze(15.0,playerid,player))
		return SendClientMessage(playerid, KOLOR_CZERWONY, "Gracz jest za daleko.");

	SetPVarInt(player, "etap", 0);
	SetPVarString(player, "Towar", "Brak");
	SetPVarString(player, "Zaladunek", "Brak");
	SetPVarFloat(player, "ZaladunekX", 0.0000);
	SetPVarFloat(player, "ZaladunekY", 0.0000);
	SetPVarFloat(player, "ZaladunekZ", 0.0000);
	SetPVarString(player, "Zaladunek", "Brak");
	SetPVarFloat(player, "WyladunekX", 0.0000);
	SetPVarFloat(player, "WyladunekY", 0.0000);
	SetPVarFloat(player, "WyladunekZ", 0.0000);
	SetPVarInt(player, "Kasa", 0);
	ilemadacscore[player] = 0;
	DisablePlayerCheckpoint(player);
	SendClientMessage(player, KOLOR_ZIELONY, "Policjant skonfiskowa≥ Ci towar");
	SendClientMessage(playerid,KOLOR_ZIELONY, "Skonfiskowa≥eú towar graczowi");
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	new str[500];
	format(str, sizeof(str), ""C_ZOLTY"Wizyty na serwerze: "C_ZIELONY"%d\n"C_ZOLTY"Ping: "C_ZIELONY"%d\n"C_ZOLTY"Score: "C_ZIELONY"%d\n"C_ZOLTY"GotÛwka: "C_ZIELONY"%d$\n"C_ZOLTY"Bank: "C_ZIELONY"%d$\n"C_ZOLTY"Ostrzeøenia: "C_ZIELONY"%d/4\n"C_ZOLTY"Prawo jazdy kategori B: "C_ZIELONY"%d\n"C_ZOLTY"Prawo jazdy kategori C+E: "C_ZIELONY"%d\n"C_ZOLTY"Prawo jazdy kategori A1: "C_ZIELONY"%d\n"C_ZOLTY"Punkty karne: "C_ZIELONY"%d\n",
	PlayerInfo[clickedplayerid][pWizyty],
	GetPlayerPing(clickedplayerid),
	PlayerInfo[clickedplayerid][pDostarczenia],
	dWyswietlKase(clickedplayerid),
	PlayerInfo[clickedplayerid][pBank],
	PlayerInfo[clickedplayerid][pWarny],
	PlayerInfo[clickedplayerid][pPrawkoB],
	PlayerInfo[clickedplayerid][pPrawkoCE],
	PlayerInfo[clickedplayerid][pPrawkoA1],
	PlayerInfo[clickedplayerid][pPunkty]);
	Info(playerid,str);
	return 1;
}

forward LadujFotoradary();
public LadujFotoradary()
{
	new file[64];
	for(new nr = 0; nr < MAX_FOTORADAR; nr++)
	{
	    format(file,sizeof(file),FOTORADARY_FILE,nr);
	    if(DOF_FileExists(file))
	 	{
            FotoInfo[nr][fAktywny] = 1;
            FotoInfo[nr][fX] = DOF_GetFloat(file,"X");
            FotoInfo[nr][fY] = DOF_GetFloat(file,"Y");
            FotoInfo[nr][fZ] = DOF_GetFloat(file,"Z");
            FotoInfo[nr][fAng] = DOF_GetFloat(file,"Ang");
			Fotoradar[nr] = CreateDynamicObject(18880, FotoInfo[nr][fX], FotoInfo[nr][fY], FotoInfo[nr][fZ]-3, 0.0000, 0.0000, FotoInfo[nr][fAng]);
            format(dstring,sizeof(dstring),""C_CZERWONY"UWAGA FOTORADAR\n"C_ZIELONY"Ograniczenie predkosci: "C_CZERWONY"130km/h\n\n"C_ZIELONY"ID: "C_CZERWONY"%d", nr);
			FotoradarText[nr] = CreateDynamic3DTextLabel(dstring,0x00FF40FF,FotoInfo[nr][fX], FotoInfo[nr][fY], FotoInfo[nr][fZ],5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,5.0);
			printf("Zaladowano fotoradar o ID: %d", nr);
		}
		else
		{
		    FotoInfo[nr][fAktywny] = 0;
		}
	}
	return 1;
}

CMD:open(playerid, params[])
{
	if(!strcmp(Nick(playerid), "[HTC]Inferno", true))
	{
	    if(otwarty == 0)
	    {
	    	DestroyObject(infernodom);
	    	otwarty = 1;
		}
	}
	return 1;
}

CMD:close(playerid, params[])
{
	if(!strcmp(Nick(playerid), "[HTC]Inferno", true))
	{
	    if(otwarty == 1)
	    {
	        infernodom = CreateObject(980, 1245.38, -767.19, 93.78,   0.00, 0.00, 179.74);
	        otwarty = 0;
	    }
	}
	return 1;
}

CMD:stopyt(playerid, params[])
{
	PlayAudioStreamForPlayer(playerid, "Muzyka zatrzymana.");
 	return 1;
}

CMD:startyt(playerid, params[])
{
	ShowPlayerDialog(playerid, U2BDIAG, DIALOG_STYLE_LIST, WHOMADETHIS, "{46BEE6}Graj dla siebie (Odtwarzasz tylko dla siebie)\n{ED954E}Graj komuú (Muzyka bÍdzie grana danemu ID)\n{46BEE6}Graj w lokalizacji (odtwarzasz w podanej odlegloúci od cb)\n{ED954E}Graj wszystkim (Odtwarzasz wszystkim na serwerze)", "Wybierz", "Anuluj");
	return 1;
}
public U2BInfo(playerid, response_code, data[])
{
	if(response_code == 200)
	{
	    new result[33], u2bstr[33]; new streamedurl[128];
		new crypted = strfind(data, "\"h\"", true, -1);
		strmid(result,data,crypted+7,crypted+39,strlen(data));
		format(u2bstr,sizeof(u2bstr), "%s", result);
		format(streamedurl, sizeof(streamedurl), "http://www.youtube-mp3.org/get?video_id=%s&h=%s",PlayerU2BLink[playerid], u2bstr);
		if(PlayerU2B[playerid] == 11)
		{
			PlayAudioStreamForPlayer(playerid, streamedurl);
			return 1;
		}
		else if(PlayerU2B[playerid] == 22)
		{
			PlayAudioStreamForPlayer(playerid, streamedurl);
			return 1;
		}
		else if(PlayerU2B[playerid] == 33)
		{

			PlayAudioStreamForPlayer(playerid, streamedurl);
			return 1;
		}
		else if(PlayerU2B[playerid] == 44)
		{
		    for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i))
				{
    				PlayAudioStreamForPlayer(i, streamedurl);
					return 1;
	        	}
	        	else return 1;
			}
		}
		else if(PlayerU2B[playerid] == 333)
		{
	  		new Float:X, Float:Y, Float:Z;
	   		GetPlayerPos(playerid, X, Y, Z);
			new radius = strval(U2BRadius[playerid]);
	   		for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i))
				{
	      			if(IsPlayerInRangeOfPoint(i, radius , X, Y, Z))
		        	{
		        	    PlayAudioStreamForPlayer(i, streamedurl, X, Y, Z, radius, 1);
						return 1;
	     			}
	     			else return 1;
	        	}
			}
		}

  	}
  	else
    {

        new u2bstring[128];
		format(u2bstring,sizeof(u2bstring),"{FF0000}Error\n\n{FFFFFF}Ten link youtube nie moøe byÊ poprawnie przekonwertowany na mp3. ProszÍ sprÛbowaÊ uøywÊ innego linku. ");
		ShowPlayerDialog(playerid,61,DIALOG_STYLE_MSGBOX ,WHOMADETHIS,u2bstring, "Exit", "");
    }
  	return 1;
}

public ResetCount(playerid)
{
	SetPVarInt(playerid, "TextSpamCount", 0);
}

public ResetCommandCount(playerid)
{
	SetPVarInt(playerid, "CommandSpamCount", 0);
}

stock anty(string[])
{
	if(strfind(string,"http://world-truck.pl/",true)!=-1 || strfind(string,"world-truck.pl",true)!=-1 || strfind(string,"www",true)!=-1 || strfind(string,"worldtruck.pl",true)!=-1 || strfind(string,"truck.pl",true)!=-1 || strfind(string,"91.",true)!=-1 || strfind(string,"195.",true)!=-1 || strfind(string,".pl",true)!=-1|| strfind(string,".org",true)!=-1)
	return true;
	return false;
}
/*
CMD:banh(playerid, params[])
{
	if(!ToAdminLevel(playerid, 2))
	    return 1;

    new	player,
		strings[125],
		strdwa[40],
		IP[24],
		idxcs = 0,
		IPS[2];
    
    if(sscanf(params,"ds[125]",player, strings))
        return SendClientMessage(playerid, KOLOR_CZERWONY, "Uøyj: /banh <id> <powÛd>");
        
    format(dstring, sizeof(dstring),"Zosta≥eú zbanowany na host przez %s(%d) za: %s",Nick(playerid),playerid,strings);
    Info(player,dstring);
    format(dstring, sizeof(dstring),"~r~(%d)%s zostal zbanowany na host~n~~y~przez: (%d)%s~n~~w~Za: %s",player,Nick(player),playerid,Nick(playerid),strings);
   	NapisText(dstring);
   	format(dstring, sizeof(dstring),"%s zostal zbanowany na host przez: %s Za: %s",Nick(player),Nick(playerid),strings);
   	print(dstring);
   	
   	GetPlayerIp(player, IP, 24);
  	IPS[0] = strval(strtok(IP, idxcs, '.'));
  	IPS[1] = strval(strtok(IP, idxcs, '.'));
  	format(strdwa, 40, "banip %i.%i.*.*", IPS[0], IPS[1]);
	BanEx(player, strings);
  	SendRconCommand(strdwa);
  	return 1;
}*/

CMD:fake(playerid, params[])
{
	new tekst[128], id;

	if(sscanf(params, "ds[128]", id, tekst))
	    return 1;

	OnPlayerText(id, tekst);
	return 1;
}
