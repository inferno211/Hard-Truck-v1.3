// created by asturel based on business system, thx to Peter Steenbergen

#if defined _housing_included
#endinput
#endif

#define _housing_included
#pragma library housing
#include "base"
#include "utils\gtoutils"
#include "utils\dutils"
#include "utils\gtodudb"
#include "utils\dini"
#include "account"
#include "player"
#include "world"

forward HousesInit();
forward IsPlayerAtHouse(playerid);
forward OnPlayerEnterHousesCheckpoint(playerid);
forward GetHouseID(playerid);
forward HousesCommandHandler(playerid,text[]);
forward ganghouse(playerid);
forward gang2house(playerid,i);
forward HouseKeepUp();

forward HouseMenuInit();
forward FHouseInfo(playerid);
forward FHouseHouses(playerid);
forward FHouseBuy(playerid);
forward FHouseSell(playerid);
forward FHouseMyHouses(playerid);
forward FHouseKeep(playerid);

#define MAX_HOUSEBUYSELL 500000
#define MAX_HOUSES 165
#define HOUSE_DELAY 600000


enum HouseInfo {
	Houses_Name[MAX_STRING],  // house name
	Houses_Cost,     // cost
	Houses_Owner[MAX_NAME],   // owner
	Houses_Gang[MAX_NAME],  // gang
	Houses_UpKeep,    // keep up
	Houses_UpKeepLeft,   // keep up left
	Houses_Buyout        // Buyout price
}

new Houses[MAX_HOUSES][HouseInfo] = {
	//NAME, COST, OWNER, GANG, UpKeep, UpKeepLeft, BUYOUT
	{"[LV]Four Dragons Mansion",1250000,"Unknown","Unknown",500,0,0},
	{"[LV]Caligula Mansion",850000,"Unknown","Unknown",500,0,0},
	{"[LS]Willowfield",17000,"Unknown","Unknown",50,0,0},
	{"[LS]Verdant Bluffs",17000,"Unknown","Unknown",50,0,0},
	{"[LS]Jefferson",30000,"Unknown","Unknown",50,0,0},
	{"[LS]Mulholland",190000,"Unknown","Unknown",250,0,0},
	{"[LS]Verona Beach",40000,"Unknown","Unknown",80,0,0},
	{"[LS]Santa Maria Beach",70000,"Unknown","Unknown",100,0,0},
	{"[LS]Palomino Creek",390000,"Unknown","Unknown",500,0,0},
	{"[LS]Blueberry",30000,"Unknown","Unknown",50,0,0},
	{"[LS]Dillimore",70000,"Unknown","Unknown",150,0,0},
	{"[SF]Angel Pine",80000,"Unknown","Unknown",50,0,0},
	{"[SF]Whetstone",200000,"Unknown","Unknown",300,0,0},
	{"[SF]Hashbury",90000,"Unknown","Unknown",100,0,0},
	{"[SF]Doherty",50000,"Unknown","Unknown",50,0,0},
	{"[SF]Queens",150000,"Unknown","Unknown",120,0,0},
	{"[SF]Chinatown",120000,"Unknown","Unknown",50,0,0},
	{"[SF]Paradiso",120000,"Unknown","Unknown",50,0,0},
	{"[SF]Calton Heights",200000,"Unknown","Unknown",300,0,0},
	{"[LV]El Quebradas",120000,"Unknown","Unknown",50,0,0},
	{"[LV]Tierra Robada",120000,"Unknown","Unknown",50,0,0},
	{"[LV]Fort Carson",130000,"Unknown","Unknown",100,0,0},
	{"[LV]Whitewood Estates",130000,"Unknown","Unknown",100,0,0},
	{"[LV]Prickle Pine",250000,"Unknown","Unknown",200,0,0},
	{"[LV]Redsands West",230000,"Unknown","Unknown",100,0,0},
	{"[LV]Pirates In Mens Pants",46000,"Unknown","Unknown",20,0,0},
	{"[LV]The Camels Toe",46000,"Unknown","Unknown",20,0,0},
	{"[LV]Rockshore West",120000,"Unknown","Unknown",100,0,0},
	{"[LV]The Clowns Pocket",99000,"Unknown","Unknown",20,0,0},
	{"[LV]Old Venturas Strip",46000,"Unknown","Unknown",30,0,0},
	{"[LV]Creek",110000,"Unknown","Unknown",50,0,0},

//ADDED BY ERAGON

	{"[LS]st.Manhatan 12",850000,"Unknown","Unknown",100,0,0},
	{"[LS]st.Manhatan 32",17000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Jarry 55",17000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Carson 2",30000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Mulholland 21",190000,"Unknown","Unknown",250,0,0},
	{"[LS]st.Verona Beach 3",40000,"Unknown","Unknown",180,0,0},
	{"[LS]st.Santa Maria Beach 18",70000,"Unknown","Unknown",110,0,0},
	{"[LS]st.Palomino Creek 54",390000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Blueberry 33",30000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Dillimore 8",70000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Angel Pine 23",80000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Whetstone 32",200000,"Unknown","Unknown",200,0,0},
	{"[LS]st.Hashbury 83",90000,"Unknown","Unknown",100,0,0},
	{"[LS]st.Doherty 14",50000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Queens 17",150000,"Unknown","Unknown",120,0,0},
	{"[LS]st.Chinatown 21",120000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Paradiso 52",120000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Calton Heights 37",200000,"Unknown","Unknown",130,0,0},
	{"[LS]st.El Quebradas 78",120000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Tierra Robada 46",120000,"Unknown","Unknown",150,0,0},
	{"[LS]st.Fort Carson 58",130000,"Unknown","Unknown",100,0,0},
	{"[LS]st.Whitewood Estates 23",130000,"Unknown","Unknown",100,0,0},
	{"[LS]st.Prickle Pine 53",250000,"Unknown","Unknown",200,0,0},
	{"[LS]st.Redsands West 36",230000,"Unknown","Unknown",100,0,0},
	{"[LS]st.Pirates In Mens Pants 63",46000,"Unknown","Unknown",120,0,0},
	{"[LS]st.The Camels Toe 53",46000,"Unknown","Unknown",120,0,0},
	{"[LS]st.Rockshore West 23",120000,"Unknown","Unknown",100,0,0},
	{"[LS]st.The Clowns Pocket 101",99000,"Unknown","Unknown",120,0,0},
	{"[LS]st.Old Venturas Strip 37",46000,"Unknown","Unknown",130,0,0},


	{"[LS-Elite]st.Twisty 1",1500000,"Unknown","Unknown",700,0,0},
	{"[LS-Elite]st.Twisty 4",3900000,"Unknown","Unknown",750,0,0},
	{"[LS-Elite]st.Twisty 13",2100000,"Unknown","Unknown",650,0,0},
	{"[LS-Elite]st.Twisty 9",1000000,"Unknown","Unknown",700,0,0},
	{"[LS-Elite]st.Twisty 17",1400000,"Unknown","Unknown",700,0,0},
	{"[LS-Elite]st.Twisty 21",2000000,"Unknown","Unknown",590,0,0},
	{"[LS-Elite]st.Twisty 44",3000000,"Unknown","Unknown",650,0,0},
	{"[LS-Elite]st.Twisty 63",2100000,"Unknown","Unknown",700,0,0},
	{"[LS-Elite]st.Twisty 32",1500000,"Unknown","Unknown",700,0,0},
	{"[LS-Elite]st.Twisty 28",1200000,"Unknown","Unknown",700,0,0},
	{"[LS-Elite]st.Twisty 19",1200000,"Unknown","Unknown",700,0,0},
	{"[LS-Elite]st.Twisty 67",2000000,"Unknown","Unknown",700,0,0},
	{"[SF]st.Blutter 64",300000,"Unknown","Unknown",150,0,0},
	{"[SF]st.Blutter 34",70000,"Unknown","Unknown",150,0,0},
	{"[SF]st.Blutter 77",800000,"Unknown","Unknown",150,0,0},
	{"[SF]st.Ultrion 34",160000,"Unknown","Unknown",300,0,0},
	{"[SF]st.Festyval 47",180000,"Unknown","Unknown",100,0,0},
	{"[SF]st.Festyval 92",212000,"Unknown","Unknown",150,0,0},
	{"[SF]st.Tini 6",150000,"Unknown","Unknown",120,0,0},
	{"[SF]st.Jaina 43",120000,"Unknown","Unknown",150,0,0},
	{"[SF]st.Toreso 52",120000,"Unknown","Unknown",150,0,0},
	{"[SF]st.MiniLit 37",200000,"Unknown","Unknown",130,0,0},
	{"[SF]st.Simfony 72",120000,"Unknown","Unknown",150,0,0},
	{"[SF]st.Tierra 36",120000,"Unknown","Unknown",150,0,0},
	{"[SF]st.Frutty 32",130000,"Unknown","Unknown",100,0,0},
	{"[SF]st.RussianHouse 12",130000,"Unknown","Unknown",100,0,0},
	{"[SF]st.RussianHouse 23",250000,"Unknown","Unknown",200,0,0},
	{"[SF]st.Gimory 36",230000,"Unknown","Unknown",100,0,0},
	{"[SF]st.RussianHouse 53",460200,"Unknown","Unknown",120,0,0},
	{"[SF]st.The CameSF Toe 63",400000,"Unknown","Unknown",120,0,0},
	{"[SF]st.RMine 21",120000,"Unknown","Unknown",100,0,0},
	{"[SF]st.Strike 99",100000,"Unknown","Unknown",120,0,0},
	{"[SF]st.Old Fiero Strip 37",460000,"Unknown","Unknown",130,0,0},
	{"[SF]st.MiniLit 50",110000,"Unknown","Unknown",150,0,0},
	{"[SF-Elite]st.Mortynate 33",3000000,"Unknown","Unknown",800,0,0},
	{"[SF-Elite]st.Mortynate 13",2000000,"Unknown","Unknown",750,0,0},
	{"[SF-Elite]st.Mortynate 34",3000000,"Unknown","Unknown",790,0,0},
	{"[LV]st.TutiDruti 43",300000,"Unknown","Unknown",150,0,0},
	{"[LV]st.TutiDruti 23",190000,"Unknown","Unknown",250,0,0},
	{"[LV]st.Bellion 42",400000,"Unknown","Unknown",180,0,0},
	{"[LV]st.TutiDruti 22",700000,"Unknown","Unknown",110,0,0},
	{"[LV]st.Ferrary Creek 14",390000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Blueberry 37",300000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Terramore 8",700000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Angel Pine 22",800000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Whetstone 92",200000,"Unknown","Unknown",300,0,0},
	{"[LV]st.Hashbury 43",90000,"Unknown","Unknown",100,0,0},
	{"[LV]st.Doherty 63",50000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Queens 37",150000,"Unknown","Unknown",120,0,0},
	{"[LV]st.TutiDruti 21",120000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Sent 22",120000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Calton Heights 37",200000,"Unknown","Unknown",130,0,0},
	{"[LV]st.Don Mona 93",120000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Tierra Robada 37",120000,"Unknown","Unknown",150,0,0},
	{"[LV]st.Fort Carson 47",130000,"Unknown","Unknown",100,0,0},
	{"[LV]st.Terramore 23a",130000,"Unknown","Unknown",100,0,0},
	{"[LV]st.Prickle Pine 33",250000,"Unknown","Unknown",200,0,0},
	{"[LV]st.Redsands West 38",230000,"Unknown","Unknown",100,0,0},
	{"[LV]st.Pirates In Mens Pants 77",46000,"Unknown","Unknown",120,0,0},
	{"[LV]st.Gvard Toe 53",46000,"Unknown","Unknown",120,0,0},
	{"[LV]st.Rockshore West 23",120000,"Unknown","Unknown",100,0,0},
	{"[LV]st.BoomHack 1",99000,"Unknown","Unknown",120,0,0},
	{"[LV]st.Old Strip Bar 37",46000,"Unknown","Unknown",130,0,0},
	{"[LV]st.Marihuana 50",110000,"Unknown","Unknown",150,0,0},
	{"[LV-Elite]st.Million 12",3700000,"Unknown","Unknown",800,0,0},
	{"[LV-Elite]st.Million 32",1000000,"Unknown","Unknown",750,0,0},
	{"[LV-Elite]st.Million 17",2000000,"Unknown","Unknown",790,0,0},
	{"[LV-Elite]st.Million 43",1500000,"Unknown","Unknown",800,0,0},
	{"[LV-Elite]st.Million 22",2000000,"Unknown","Unknown",750,0,0},
	{"[LV-Motel]Motel Room 2",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 5",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 21",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 22",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 37",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 93",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 48",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 38",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 1",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 33",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 28",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 77",46000,"Unknown","Unknown",46,0,0},
	{"[LV-Motel]Motel Room 53",46000,"Unknown","Unknown",46,0,0},
	{"[LV-Motel]Motel Room 23",50000,"Unknown","Unknown",50,0,0},
	{"[LV-Motel]Motel Room 11",99000,"Unknown","Unknown",99,0,0},
	{"[LV-Motel]Motel Room 37",46000,"Unknown","Unknown",46,0,0},
	{"[LV-Motel]Motel Room 13",30000,"Unknown","Unknown",30,0,0},
	{"[BR]House Mymy",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Tester",150000,"Unknown","Unknown",120,0,0},
	{"[BR]House Violet",270000,"Unknown","Unknown",120,0,0},
	{"[BR]House Milki",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Tykte",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Bilka",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Camun",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Geomance",190000,"Unknown","Unknown",120,0,0},
	{"[BR]House Dodo",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Ferrary",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Blatnoy",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Feramon",230000,"Unknown","Unknown",120,0,0},

	{"[BR]House Californy",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Meteor",260000,"Unknown","Unknown",120,0,0},
	{"[BR]House Neon",260000,"Unknown","Unknown",120,0,0},
	{"[BR]House Figaro",200000,"Unknown","Unknown",120,0,0},
	{"[BR]House Pycucat",290000,"Unknown","Unknown",120,0,0},
	{"[BR]House SAS",260000,"Unknown","Unknown",120,0,0},
	{"[BR]House WayV",200000,"Unknown","Unknown",120,0,0}
};

new HousesCP[MAX_HOUSES][CoordInfo] = {
	{991.8711,-668.1383,121.9763},
	{300.2951,-1154.5029,81.3909},
	{2486.8389,-1997.4480,13.8343},
	{1687.8954,-2100.4861,13.8343},
	{2108.2073,-1280.1827,25.6875},
	{1325.8687,-633.3270,109.1349},
	{890.5464,-1638.7795,14.9616},
	{312.6361,-1772.2003,4.6282},
	{2238.4756,166.0871,28.1535},
	{206.6301,-109.8167,4.8965},
	{791.9865,-507.5847,18.0129},
	{-2080.1499,-2312.3855,30.6250},
	{-1442.8309,-1541.9430,101.7578},
	{-2456.8408,-131.7211,26.0440},
	{-2027.6254,-44.5550,38.4414},
	{-2421.6580,335.3531,35.7626},
	{-2210.9714,723.4057,49.4141},
	{-2703.1348,818.3945,49.9844},
	{-2103.9272,900.6589,76.7109},
	{-1534.4202,2649.6294,55.8359},
	{-1045.4006,1552.8932,33.3112},
	{-364.1446,1168.8844,19.7422},
	{926.3783,2010.8345,11.4609},
	{1282.0720,2525.0994,10.8203},
	{1405.6171,1900.5596,11.4609},
	{1969.4005,1623.1444,12.8625},
	{2233.6375,1288.4495,10.8203},
	{2446.2251,695.2101,11.4609},
	{2223.1616,1840.9108,10.8203},
	{2371.1787,2169.1052,10.8257},
	{2820.9004,2140.8269,14.6615},

//ADDED BY ERAGON

	{2487.073,-1646.585,13.265},
	{2495.479,-1690.834,13.960},
	{2396.199,-1647.489,12.732},
	{2328.642,-1681.613,13.999},
	{2067.023,-1700.507,13.343},
	{1983.229,-1716.938,15.163},
	{1855.599,-1915.128,14.451},
	{1890.086,-2066.387,14.230},
	{1736.992,-2128.999,12.741},
	{1687.525,-2100.221,13.029},
	{2463.217,-1996.910,12.883},
	{2691.140,-2017.328,12.728},
	{2630.277,-1071.674,68.813},
	{2629.399,-1117.942,66.677},
	{2539.907,-1061.115,68.762},
	{2554.512,-958.501,81.871},
	{2444.380,-965.150,79.234},
	{1107.973,-974.878,41.960},
	{940.709,-846.031,92.949},
	{697.757,-1058.628,48.608},
	{527.331,-1177.296,58.004},
	{817.150,-766.772,76.431},
	{1421.289,-884.693,49.824},
	{1326.435,-1092.259,27.171},
	{1242.796,-1098.000,27.178},
	{1183.146,-1076.684,30.866},
	{969.566,-1542.730,12.788},
// ýëèòíûå
	{768.810,-1746.158,12.272},
	{650.999,-1623.480,14.194},


	{1503.053,-691.452,93.944},
	{1473.440,-901.453,54.226},
	{1290.428,-798.630,87.507},
	{1093.638,-804.572,106.613},
	{1051.354,-638.648,119.312},
	{986.791,-671.282,121.171},
	{874.889,-695.124,113.337},
	{318.322,-1137.270,80.788},
	{252.211,-1227.374,73.802},
	{220.443,-1251.679,77.509},
	{693.871,-1706.249,3.014},
	{166.367,-1317.702,69.546},
//----------------------------------CÀÍ-ÔÈÅÉÐÎ----------------------------------
	{-2027.734,-42.028,37.999},
	{-2016.835,766.215,44.640},
	{-2528.760,-143.549,19.230},
	{-2580.921,-119.258,5.473},
	{-2620.736,-185.525,6.398},
	{-2623.224,-99.661,6.398},
	{-2720.792,-124.644,3.530},
	{-2684.688,-182.026,6.398},
	{-2783.329,-99.717,9.249},
	{-2779.904,-185.424,9.257},
	{-2780.863,73.764,6.374},
	{-2783.453,189.806,9.249},
	{-2373.403,627.190,32.621},
	{-2371.354,705.971,34.365},
	{-2446.600,817.687,34.374},
	{-2374.975,856.082,40.905},
	{-2236.224,870.549,65.839},
	{-2174.076,797.035,61.645},
	{-2016.753,994.915,49.152},
	{-2382.141,1305.989,17.773},
	{-2353.556,1250.259,27.800},
	{-2157.071,979.139,79.201},
// ýëèòíûå
	{-2624.417,1410.827,6.288},
	{-2105.307,899.656,75.905},
	{-2078.481,902.135,63.327},
//---------------------------------ËÀÑ-ÂÅÍÒÓÐÀÑ---------------------------------
	{2397.535,655.037,10.655},
	{2318.441,654.771,10.648},
	{2346.741,735.190,10.663},
	{2346.558,692.725,10.655},
	{2448.982,742.452,10.655},
	{2539.768,719.439,13.934},
	{2004.935,2758.146,10.015},
	{2049.476,2761.351,10.015},
	{2093.317,731.819,10.648},
	{2013.653,774.227,10.655},
	{2123.306,774.726,10.640},
	{984.356,1894.683,10.655},
	{1029.716,1927.262,10.663},
	{887.278,1979.872,10.655},
	{1032.377,2316.267,10.663},
	{1359.602,2566.876,10.015},
	{1229.857,2584.680,10.015},
	{1555.484,2663.311,10.015},
	{1603.561,2679.075,10.015},
	{1618.664,2606.625,10.015},
	{1733.996,2700.667,10.015},
	{1967.051,1623.265,12.056},
	{2367.264,2124.049,10.014},
	{2339.733,1621.617,10.015},
	{2025.345,1916.193,11.525},
	{2360.096,2378.085,10.015},
	{2609.640,2392.888,17.015},
//ýëèòíûå
	{2535.262,998.084,13.467},
	{1493.112,720.433,10.015},
	{2557.671,1561.958,10.015},
	{2483.931,1528.259,10.193},
	{2581.533,1061.976,10.469},
//ìîòåëè
	{1784.483,2866.863,13.460},
	{1740.401,2861.605,13.460},
	{1737.867,2802.571,13.468},
	{1830.707,2742.897,13.468},
	{2660.460,749.261,13.934},
	{2613.922,719.468,13.934},
	{2525.864,749.313,13.934},
	{2578.610,719.615,10.015},
	{2820.047,2271.459,13.856},
	{2793.985,2222.337,13.856},
	{2549.181,2202.389,13.311},
	{2609.615,2143.072,13.311},
	{2637.650,1979.056,13.311},
	{2652.686,2018.261,13.311},
	{2453.709,1419.763,10.101},
	{1904.929,664.622,13.468},
	{1929.276,741.587,13.468},
//-----------------------------------ÇÀÃÎÐÎÄ------------------------------------
	{2510.728,11.165,27.636},
	{2374.721,20.795,27.636},
	{2249.135,-121.139,27.348},
	{1294.500,174.799,20.105},
	{748.371,278.347,26.453},
	{252.318,-116.120,2.730},
	{-2157.860,-2536.616,31.011},
	{-2220.680,-2401.287,31.777},
	{-2045.275,-2523.618,30.261},
	{768.494,2006.660,5.261},
	{-37.578,1078.458,19.304},
	{-260.176,1047.628,20.134},

	{-907.070,1543.662,25.109},
	{-1483.853,2702.008,55.449},
	{-149.406,2688.812,61.624},
	{-285.919,2757.093,61.707},
	{-2389.537,2410.905,8.072},
	{-2634.079,2403.307,10.475},
	{-2524.967,2239.568,4.600}
};

new Menu:HouseMenu;

public HouseMenuInit()     //Create by FP
{
//	new rst[256]="edited...";

	HouseMenu = CreateMenu("House", 1, 30.0, 150.0, 100.0, 140.0);
//	SetMenuColumnHeader(HouseMenu, 0, "");
		AddMenuItem(HouseMenu, 0, "...cancel...");
		AddMenuItem(HouseMenu, 0, "Information");
		AddMenuItem(HouseMenu, 0, "Buy");
		AddMenuItem(HouseMenu, 0, "Sell");
//		AddMenuItem(HouseMenu, 0, "Set Sell Cost");
		AddMenuItem(HouseMenu, 0, "Keeping");
		AddMenuItem(HouseMenu, 0, "My Houses");
		AddMenuItem(HouseMenu, 0, "All Houses");


return 1;
}



new HousesDB[MAX_STRING] = "GTO/Housing/";

HousesLoadAll()
{
	if (ForceOverwrite) return;
	new temp[MAX_STRING];
	if (!dini_Exists(ConfigDB)) dini_Create(ConfigDB);
	set(temp,dini_Get(ConfigDB,"Houses_DB"));
	if (strlen(temp) > 0) set(HousesDB,temp);
	if (!dini_Exists(HousesDB))
	{

		HousesSaveAll();

		return;
	}
	for (new i=0;i<MAX_HOUSES;i++)
	{
		new housesdbname[MAX_STRING];
		format(housesdbname,sizeof(housesdbname),"%sGTO.Houses.%s.txt",HousesDB,Houses[i][Houses_Name]);
		if (!dini_Exists(housesdbname))
		{
			// continue;
			dini_Create(housesdbname); HousesSaveAll();
		}
		set(temp,dini_Get(housesdbname,"Name"));
		if (strlen(temp) > 0) set(Houses[i][Houses_Name],temp);
		set(temp,nullstr);
		set(temp,dini_Get(housesdbname,"Cost"));
		if (strlen(temp) > 0) Houses[i][Houses_Cost] = strval(temp);
		set(temp,nullstr);
		set(temp,dini_Get(housesdbname,"Owner"));
		if (strlen(temp) > 0) set(Houses[i][Houses_Owner],temp);
		set(temp,nullstr);
		set(temp,dini_Get(housesdbname,"Gang"));
		if (strlen(temp) > 0) set(Houses[i][Houses_Gang],temp);
		set(temp,nullstr);
		set(temp,dini_Get(housesdbname,"UpKeep"));
		if (strlen(temp) > 0) Houses[i][Houses_UpKeep] = strval(temp); 
		set(temp,nullstr);
		set(temp,dini_Get(housesdbname,"UpKeepLeft"));
		if (strlen(temp) > 0) Houses[i][Houses_UpKeepLeft] = strval(temp); 
		set(temp,nullstr);
		set(temp,dini_Get(housesdbname,"Buyout"));
		if (strlen(temp) > 0) Houses[i][Houses_Buyout] = strval(temp);
		set(temp,nullstr);
		
	}
	return;

}

HousesSaveAll()
{
	new temp[MAX_STRING];
	if (dini_Exists(ConfigDB))
	{
		dini_Set(ConfigDB,"Houses_DB",HousesDB);
	}

	for (new i=0;i<MAX_HOUSES;i++)
	{
		new housesdbname[MAX_STRING];
		format(housesdbname,sizeof(housesdbname),"%sGTO.Houses.%s.txt",HousesDB,Houses[i][Houses_Name]);
		if (!dini_Exists(housesdbname)) dini_Create(housesdbname);
		dini_Set(housesdbname,"Name",Houses[i][Houses_Name]);
		set(temp,nullstr);

		valstr(temp,Houses[i][Houses_Cost]);
		dini_Set(housesdbname,"Cost",temp);
		set(temp,nullstr);

		valstr(temp,Houses[i][Houses_Owner]);
		dini_Set(housesdbname,"Owner",Houses[i][Houses_Owner]);
		set(temp,nullstr);

		valstr(temp,Houses[i][Houses_Gang]);
		dini_Set(housesdbname,"Gang",Houses[i][Houses_Gang]);
		set(temp,nullstr);

		valstr(temp,Houses[i][Houses_UpKeep]);
		dini_Set(housesdbname,"UpKeep",temp);
		set(temp,nullstr);

		valstr(temp,Houses[i][Houses_UpKeepLeft]);
		dini_Set(housesdbname,"UpKeepLeft",temp);
		set(temp,nullstr);

		valstr(temp,Houses[i][Houses_Buyout]);
		dini_Set(housesdbname,"Buyout",temp);
		set(temp,nullstr);

	}
	return;

}

public HousesInit()
{
	for (new id=0;id<MAX_HOUSES;id++)
	{
		AddActiveCheckpoint(HousesCP[id][Coord_X],HousesCP[id][Coord_Y],HousesCP[id][Coord_Z],20,2);
		AddStaticPickup(1273,49,HousesCP[id][Coord_X],HousesCP[id][Coord_Y],HousesCP[id][Coord_Z]);	//çåëåíûé äîìèê
	}
	WriteLog("Housing checkpoints initialised");
}

public IsPlayerAtHouse(playerid)
{
	for (new id=0;id<MAX_HOUSES;id++)
	{
		if (oIsPlayerInCheckpoint(playerid,HousesCP[id][Coord_X],HousesCP[id][Coord_Y],HousesCP[id][Coord_Z],10))
		{
			return 1;
		}
	}
	return 0;
}

public OnPlayerEnterHousesCheckpoint(playerid)
{
	if (playerid == INVALID_PLAYER_ID) return;
	if (!IsPlayerConnected(playerid)) return;
	if (!IsPlayerAtHouse(playerid)) return;

	for (new id=0;id<MAX_HOUSES;id++)
	{
		if (oIsPlayerInCheckpoint(playerid,HousesCP[id][Coord_X],HousesCP[id][Coord_Y],HousesCP[id][Coord_Z],10))
		{
			new temp[MAX_STRING];
			format(temp,sizeof(temp), lang_texts[8][1] ,Houses[id][Houses_Name]);
			SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
		}
	}
}

public GetHouseID(playerid)
{
	new lookupid=-1;
	for (new id=0;id<MAX_HOUSES;id++)
	{
		if (oIsPlayerInCheckpoint(playerid,HousesCP[id][Coord_X],HousesCP[id][Coord_Y],HousesCP[id][Coord_Z],10)) lookupid = id;
	}
	return lookupid;
}


public HousesCommandHandler(playerid,text[]) 
{
	if (!IsPlayerConnected(playerid)) return 0;

	new cmd[20];
	new idx;

	set(cmd,strcharsplit(text, idx,strchar(" ")));
	if (strlen(cmd) == 0) return 0;


	if (!strcmp("/hmenu", cmd, true, 5))
	{
		if (!IsPlayerAtHouse(playerid))
		{
			SendPlayerFormattedText(playerid,  lang_texts[8][2]  , 0,COLOUR_RED);
			return 1;
		}
		else
		{
		TogglePlayerControllable(playerid, 0);
 	   	if(IsValidMenu(HouseMenu)) ShowMenuForPlayer(HouseMenu, playerid);
		return 1;
		}
	}

	//-- houseinfo --
	if((strcomp(cmd, "/houseinfo", true) == 1) || (strcomp(cmd, "/hinfo", true) == 1))
	{
		if (!IsPlayerAtHouse(playerid))
		{
			SendPlayerFormattedText(playerid,  lang_texts[8][2]  , 0,COLOUR_RED);
			return 1;
		} 
		else 
		{
		FHouseInfo(playerid);
		}

	}
	//---------------------

	//-- buyhouses --
	if((strcomp(cmd, "/housebuy", true) == 1) || (strcomp(cmd, "/hbuy", true) == 1))
	{
		if (!IsPlayerAtHouse(playerid))
		{
			SendPlayerFormattedText(playerid,  lang_texts[8][14]  , 0,COLOUR_RED);
			return 1;
		}
		else
		{
		FHouseBuy(playerid);
		}

	}
	//---------------------

	//-- sell house --
	if((strcomp(cmd, "/housesell", true) == 1) || (strcomp(cmd, "/hsell", true) == 1))
	{
		if (!IsPlayerAtHouse(playerid))
		{
			SendPlayerFormattedText(playerid,  lang_texts[8][22]  , 0,COLOUR_RED);
			return 1;
		}
		else
		{
		FHouseSell(playerid);
		}

	}
	//--------------------

//	//-- set buyout --
//	if(strcomp(cmd, "/sethbuyout", true) == 1)
//	{
//		new buyoutamount;
//		buyoutamount = strval(strcharsplit(text, idx,strchar(" ")));
//
//		if ((buyoutamount < -9999) || (buyoutamount == 0) || (buyoutamount > 9999) || (buyoutamount > Player[playerid][Money]))
//		{
//			SendPlayerFormattedText(playerid, lang_texts[8][29] , 0,COLOUR_RED);
//			return 1;
//		}
//
//		if (!IsPlayerAtHouse(playerid))
//		{
//			SendPlayerFormattedText(playerid,  lang_texts[8][30]  , 0,COLOUR_RED);
//			return 1;
//		} else {
//			new id=GetHouseID(playerid);
//			new temp[MAX_STRING];
//			if (id > -1)
//			{
//				if (IsPlayerRegistered(playerid))
//				{
//					if(strcomp(Houses[id][Houses_Owner], oGetPlayerName(playerid), true) == 0)
//					{
//						SendPlayerFormattedText(playerid,  lang_texts[8][31] , 0,COLOUR_RED);
//					} else if (GetPlayerMoney(playerid) < Houses[id][Houses_UpKeepLeft] || GetPlayerMoney(playerid) == 0){
//						SendPlayerFormattedText(playerid,  lang_texts[8][46] , 0,COLOUR_RED);
//						return 1;
//						} else {
//						new newbuyout;
//						newbuyout = Houses[id][Houses_Buyout] + buyoutamount;
//							
//						if(newbuyout < 0 || newbuyout > MAX_HOUSEBUYSELL)
//						{
//							SendPlayerFormattedText(playerid, lang_texts[8][32] , 0,COLOUR_RED);
//							return 1;
//						}
//						
//						oGivePlayerMoney(playerid,0-buyoutamount,1);
//						Houses[id][Houses_Buyout] = newbuyout;
//						new dinifilename[MAX_STRING];
//						format(dinifilename,sizeof(dinifilename),"%sGTO.Houses.%s.txt",HousesDB,Houses[id][Houses_Name]);
//						if (dini_Exists(dinifilename))
//						{
//							valstr(temp,Houses[id][Houses_Buyout]);
//							dini_Set(dinifilename,"Buyout",temp);
//							set(temp,nullstr);
//						}
//						if(buyoutamount > 0)
//						{
//							format(temp,sizeof(temp), lang_texts[8][33] ,Houses[id][Houses_Buyout]);
//							SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
//							set(temp,nullstr);
//							new logstring[256];
//							format(logstring, sizeof (logstring), "player: %d:  %s: increased the buy out of '%s' (house) to $%d",playerid,oGetPlayerName(playerid),Houses[id][Houses_Name],Houses[id][Houses_Buyout]);
//							WriteLog(logstring);
//						} else {
//							format(temp,sizeof(temp), lang_texts[8][34] ,Houses[id][Houses_Buyout]);
//							SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
//							set(temp,nullstr);
//							new logstring[256];
//							format(logstring, sizeof (logstring), "player: %d:  %s: decreased the buy out of '%s' (house) to $%d",playerid,oGetPlayerName(playerid),Houses[id][Houses_Name],Houses[id][Houses_Buyout]);
//							WriteLog(logstring);
//						}
//					}
//				} else {
//					SendPlayerFormattedText(playerid,  lang_texts[8][35] , 0,COLOUR_RED);
//					SendPlayerFormattedText(playerid,  lang_texts[8][36] , 0,COLOUR_RED);
//				}
//			} else {
//				SendPlayerFormattedText(playerid,  lang_texts[8][37] , 0,COLOUR_RED);
//			}
//		}
//		return 1;
//	}
//	//----------------------


	//-- houses list --
	if(strcomp(cmd, "/houses", true) == 1)
	{
	FHouseHouses(playerid);
	}

	//-------------------------

	//--  my houses list --
	if(strcomp(cmd, "/myhouses", true) == 1)
	{
	FHouseMyHouses(playerid);
	}

	//-------------------------
	// -- upkeep -- 
	if(strcomp(cmd, "/upkeep", true) == 1)
	{
		if (!IsPlayerAtHouse(playerid))
		{
			SendPlayerFormattedText(playerid,  lang_texts[8][43]  , 0,COLOUR_RED);
			return 1;
		} 
		else 
		{
		FHouseKeep(playerid);
		}

	}


	//--------------------------
	return 0;
}

//-------RECOMPIL FOR HOUSE MENUS
public FHouseInfo(playerid) {

			new id=GetHouseID(playerid);
			if (id > -1)
			{
				new temp[MAX_STRING];
				format(temp,sizeof(temp), lang_texts[8][3] ,Houses[id][Houses_Name]);
				SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
				set(temp,nullstr);
				if(strcomp(Houses[id][Houses_Owner], "Unknown", true) == 0 && strcomp(Houses[id][Houses_Gang], "Unknown", true) == 0)
				{
					format(temp,sizeof(temp), lang_texts[8][4] ,Houses[id][Houses_Gang],Houses[id][Houses_Owner]);
					SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
					set(temp,nullstr);
					new price;
					price = Houses[id][Houses_Cost] + Houses[id][Houses_Buyout];
					new UpKeep;
					UpKeep = Houses[id][Houses_UpKeep];
					if(strcomp(Houses[id][Houses_Owner], oGetPlayerName(playerid), true) == 0 || strcomp(Houses[id][Houses_Gang], PlayerGangName[playerid], true) == 0)
					{
						format(temp,sizeof(temp), lang_texts[8][5] ,price);
						SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
						set(temp,nullstr);
						
						format(temp,sizeof(temp), lang_texts[8][6] ,UpKeep);
						SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
						set(temp,nullstr);
						
						format(temp,sizeof(temp), lang_texts[8][7] ,Houses[id][Houses_UpKeepLeft], UpKeep*2800);
						SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
						set(temp,nullstr);
						
						
						SendPlayerFormattedText(playerid,  lang_texts[8][8] , 0,COLOUR_GREEN);
					} 
				} 
				else 
				{
					SendPlayerFormattedText(playerid,  lang_texts[8][9] , 0,COLOUR_GREEN);
					format(temp,sizeof(temp), lang_texts[8][10] ,Houses[id][Houses_Cost]);
					SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
					set(temp,nullstr);
					
					format(temp,sizeof(temp), lang_texts[8][11] ,Houses[id][Houses_UpKeep],Houses[id][Houses_UpKeepLeft]);
					SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
					set(temp,nullstr);
					
					SendPlayerFormattedText(playerid,  lang_texts[8][12] , 0,COLOUR_GREEN);
				}
			} else { SendPlayerFormattedText(playerid,  lang_texts[8][13] , 0,COLOUR_RED); }
			return 1;
}

public FHouseHouses(playerid) {
		new temp[MAX_STRING];
		for (new id=0;id<MAX_HOUSES;id++)
		{
			if(strcomp(Houses[id][Houses_Owner], "Unknown", true) == 0)
			{
				format(temp,sizeof(temp), lang_texts[8][38] ,Houses[id][Houses_Name],Houses[id][Houses_Gang],Houses[id][Houses_Owner]);
				SendPlayerScrollingText(playerid,temp);
				set(temp,nullstr);
			} 
			else 
			{
				format(temp,sizeof(temp), lang_texts[8][39] ,Houses[id][Houses_Name]);
				SendPlayerScrollingText(playerid,temp);
				set(temp,nullstr);
			}
		}
		return 1;
}


public FHouseBuy(playerid) {
			new id=GetHouseID(playerid);
			new temp[MAX_STRING];
			if (id > -1)
			{
				if (IsPlayerRegistered(playerid))
				{
					if (PlayerGangid[playerid] != 0) {
						new price;
						price = Houses[id][Houses_Cost] + Houses[id][Houses_Buyout];
						if(Player[playerid][Money] >= price)
						{
							if(strcomp(Houses[id][Houses_Owner], oGetPlayerName(playerid), true) == 1)
							{
								SendPlayerFormattedText(playerid,  lang_texts[8][15] , 0,COLOUR_RED);
							} 
							else 
							{
								new owner=-1;
								for (new ownerid = 0; ownerid < MAX_PLAYERS; ownerid++)
								{
									if (IsPlayerConnected(ownerid))
									{
										if(strcomp(Houses[id][Houses_Owner], oGetPlayerName(ownerid), true) == 1)
										{
											format(temp,sizeof(temp), lang_texts[8][16] ,Houses[id][Houses_Name],oGetPlayerName(playerid));
											SendPlayerFormattedText(ownerid, temp, 0,COLOUR_RED);
											set(temp,nullstr);
											owner=ownerid;
										}
									}
								}
								oGivePlayerMoney(playerid,0-price,1);
								if (owner > -1)
								{
									oGivePlayerMoney(owner,0+price,1);
								} 
								else 
								{
									new dinifilename[MAX_STRING];
									format(dinifilename,sizeof(dinifilename),"%sGTO.Player.%s.txt",PlayerDB,EncodeName(Houses[id][Houses_Owner]));
									if (dini_Exists(dinifilename))
									{
										new tempmoney;
										tempmoney = strval(dini_Get(dinifilename,"Money"));
										tempmoney = tempmoney + price;
										valstr(temp,tempmoney);
										dini_Set(dinifilename,"Money",temp);
										set(temp,nullstr);
									}
								}
								set(Houses[id][Houses_Owner],oGetPlayerName(playerid));
								
								set(Houses[id][Houses_Gang],PlayerGangName[playerid]);
								
								Houses[id][Houses_Buyout] = 0;
								new dinifilename[MAX_STRING];
								format(dinifilename,sizeof(dinifilename),"%sGTO.Houses.%s.txt",HousesDB,Houses[id][Houses_Name]);
								if (dini_Exists(dinifilename))
								{
									dini_Set(dinifilename,"Owner",Houses[id][Houses_Owner]);
									dini_Set(dinifilename,"Gang",Houses[id][Houses_Gang]);
									
									valstr(temp,Houses[id][Houses_Buyout]);
									dini_Set(dinifilename,"Buyout",temp);
									set(temp,nullstr);
									
									
								}
								format(temp,sizeof(temp), lang_texts[8][17] ,Houses[id][Houses_Name]);
								SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
								set(temp,nullstr);
								
								new logstring[256];
								format(logstring, sizeof (logstring), "player: %d:  %s: bought the '%s' (house)",playerid,oGetPlayerName(playerid),Houses[id][Houses_Name]);
								WriteLog(logstring);
							}
						} else {
							SendPlayerFormattedText(playerid,  lang_texts[8][18] , 0,COLOUR_RED);
						}
					} else { SendPlayerFormattedText(playerid,  lang_texts[8][19] , 0,COLOUR_RED); }
				} else {
					SendPlayerFormattedText(playerid,  lang_texts[8][20] , 0,COLOUR_RED);
				}
			} else {
				SendPlayerFormattedText(playerid,  lang_texts[8][21] , 0,COLOUR_RED);
			}
			return 1;
}

public FHouseSell(playerid) {
			FHouseKeep(playerid);
			
			new id=GetHouseID(playerid);
			new temp[MAX_STRING];
			if (id > -1)
			{
				if (IsPlayerRegistered(playerid))
				{
					if(strcomp(Houses[id][Houses_Owner], oGetPlayerName(playerid), true) == 0)
					{
						SendPlayerFormattedText(playerid,  lang_texts[8][23] , 0,COLOUR_RED);
					} else {
						new price;
						price = Houses[id][Houses_Cost] + Houses[id][Houses_Buyout];
						price = (price * 85) / 100;
						oGivePlayerMoney(playerid,0+price,1);
						set(Houses[id][Houses_Owner],"Unknown");
						set(Houses[id][Houses_Gang],"Unknown");
						Houses[id][Houses_Buyout] = 0;
						new dinifilename[MAX_STRING];
						format(dinifilename,sizeof(dinifilename),"%sGTO.Houses.%s.txt",HousesDB,Houses[id][Houses_Name]);
						if (dini_Exists(dinifilename))
						{
							dini_Set(dinifilename,"Owner","Unknown");
							dini_Set(dinifilename,"Gang","Unknown");
							dini_Set(dinifilename,"UpKeepLeft","0"); //"Unknown"
							valstr(temp,Houses[id][Houses_Buyout]);
							dini_Set(dinifilename,"Buyout",temp);
							set(temp,nullstr);
						}
						format(temp,sizeof(temp), lang_texts[8][24] ,Houses[id][Houses_Name]);
						SendPlayerFormattedText(playerid, temp, 0,COLOUR_GREEN);
						set(temp,nullstr);
						SendPlayerFormattedText(playerid,  lang_texts[8][25] , 0,COLOUR_GREEN);
						
						new logstring[256];
						format(logstring, sizeof (logstring), "player: %d:  %s: sold the '%s' (house)",playerid,oGetPlayerName(playerid),Houses[id][Houses_Name]);
						WriteLog(logstring);
					}
				} else {
					SendPlayerFormattedText(playerid,  lang_texts[8][26] , 0,COLOUR_RED);
					SendPlayerFormattedText(playerid,  lang_texts[8][27] , 0,COLOUR_RED);
				}
			} else {
				SendPlayerFormattedText(playerid,  lang_texts[8][28] , 0,COLOUR_RED);
			}
			return 1;
		}

public FHouseMyHouses(playerid) {
		new temp[MAX_STRING];
		new count = 0;
		for (new id=0;id<MAX_HOUSES;id++)
		{
			if(strcomp(Houses[id][Houses_Gang], PlayerGangName[playerid], true) == 1)
			{
				count++;
				format(temp,sizeof(temp), lang_texts[8][40] ,Houses[id][Houses_Name],Houses[id][Houses_Owner],Houses[id][Houses_Cost]);
				SendPlayerScrollingText(playerid,temp);
				set(temp,nullstr);
				
				format(temp,sizeof(temp), lang_texts[8][41] ,Houses[id][Houses_UpKeep], Houses[id][Houses_UpKeepLeft]);
				SendPlayerScrollingText(playerid,temp);
				set(temp,nullstr);
				
			}
		}
		if(count < 1)
		{
			SendPlayerFormattedText(playerid,  lang_texts[8][42] , 0,COLOUR_RED);
		}
		return 1;
	}


public FHouseKeep(playerid) {
			new id=GetHouseID(playerid);
			new temp[MAX_STRING];
			if (id > -1)
			{
				if (IsPlayerRegistered(playerid))
				{
					if(strcmp(Houses[id][Houses_Gang], PlayerGangName[playerid], true) == 0)
					{
						if (GetPlayerMoney(playerid) > Houses[id][Houses_UpKeepLeft]) {
							if(Houses[id][Houses_UpKeepLeft] > 0)
							{
								Player[playerid][Money] = Player[playerid][Money] - Houses[id][Houses_UpKeepLeft];
								SendPlayerFormattedText(playerid,  lang_texts[8][44] , 0,COLOUR_GREEN);
								Houses[id][Houses_UpKeepLeft] = 0;
								new dinifilename[MAX_STRING];
								format(dinifilename,sizeof(dinifilename),"%sGTO.Houses.%s.txt",HousesDB,Houses[id][Houses_Name]);
								if (dini_Exists(dinifilename))
								{
									valstr(temp,Houses[id][Houses_UpKeepLeft]);
									dini_Set(dinifilename,"UpKeepLeft",temp);
									set(temp,nullstr);
								}
							} else {  SendPlayerFormattedText(playerid,  lang_texts[8][45] , 0,COLOUR_RED); }
						} else { SendPlayerFormattedText(playerid,  lang_texts[8][46] , 0,COLOUR_RED); } 
					} else { SendPlayerFormattedText(playerid,  lang_texts[8][47] , 0,COLOUR_RED); }
				} else {
					SendPlayerFormattedText(playerid,  lang_texts[8][48] , 0,COLOUR_RED);
					SendPlayerFormattedText(playerid,  lang_texts[8][49] , 0,COLOUR_RED);
				}
			} else { SendPlayerFormattedText(playerid,  lang_texts[8][50] , 0,COLOUR_RED); }
		}

//--------------------------------------------------------------------------------



public ganghouse(playerid) {
	new hova = -1;
	if (!IsPlayerRegistered(playerid)) return hova;
	if (!strlen(PlayerGangName[playerid])) return hova;
	for (new id=0;id<MAX_HOUSES;id++)
	{
		if (!strcmp(Houses[id][Houses_Gang], PlayerGangName[playerid], true)) 
		{
			hova = id;
			new tmp[MAX_STRING];
			format(tmp,sizeof(tmp), lang_texts[8][51] , Houses[id][Houses_Name], Houses[id][Houses_UpKeepLeft],Houses[id][Houses_UpKeep]*2800);
			SendPlayerFormattedText(playerid,tmp,0, COLOUR_RED);
		}

	}
	return hova;
}

public gang2house(playerid,i)
{
	SetPlayerPos(playerid, HousesCP[i][Coord_X], HousesCP[i][Coord_Y], HousesCP[i][Coord_Z]);
}


public HouseKeepUp()
{
	new temp[MAX_STRING];
	new upkeepamount;
	new upkeep;
	new upkeepleft;
	for (new id=0;id<MAX_HOUSES;id++)
	{
		if(strcmp(Houses[id][Houses_Gang], "Unknown", true) == 0) { } else 
		{
			upkeep = Houses[id][Houses_UpKeep];
			upkeepleft = Houses[id][Houses_UpKeepLeft];
			upkeepamount = upkeep + upkeepleft;
			if (upkeepamount < upkeep*2800) {
				Houses[id][Houses_UpKeepLeft ] = upkeepamount;

				new dinifilename[MAX_STRING];
				format(dinifilename,sizeof(dinifilename),"%sGTO.Houses.%s.txt",HousesDB,Houses[id][Houses_Name]);
				if (dini_Exists(dinifilename))
				{
					valstr(temp,upkeepamount);
					dini_Set(dinifilename,"UpKeepLeft",temp);
					set(temp,nullstr);
				}
				if (upkeepamount > upkeep*500) 
				{
					// pay or suck.. the choice is yours..
				}
			} 
			else 
			{ 
				new dinifilename[MAX_STRING];
				format(dinifilename,sizeof(dinifilename),"%sGTO.Houses.%s.txt",HousesDB,Houses[id][Houses_Name]);
				if (dini_Exists(dinifilename)) {
					dini_Set(dinifilename,"Gang","Unknown");
					dini_Set(dinifilename,"Owner","Unknown");
					dini_Set(dinifilename,"UpKeepLeft","0");
				}   
			}
		} 
	}
}


