#if defined _strtok_included
	#endinput
#endif
#define _strtok_included
//moje :P

#define komenda(%1) if(strcmp(cmd, %1, true) == 0) {
#define vkomenda(%1) if(strcmp(cmd, %1, true) == 0) {\
if(!IsPlayerAdmin(playerid) && VIP[playerid] == 0){ \
SendClientMessage(playerid, NIEBIESKI, "Tylko dla Adminow/Vipow"); \
return 1;\
}

#define waucie IsPlayerInAnyVehicle
#define akomenda(%1) if(strcmp(cmd, %1, true) == 0) {\
if(!IsPlayerAdmin(playerid)){ \
SendClientMessage(playerid, CZERWONY, "Tylko Admini"); \
return 1;\
}


//kolory
#define BEZOWY 0xFFFFADAA
#define BIALY 0xFFFFFFAA
#define BLEKITNY 0x00FFFFAA
#define BORDOWY 0x99001FAA
#define BRAZOWY 0x997A00AA
#define CIEMNY_ZIELONY 0x336633AA
#define CZARNY 0x000000AA
#define CZERWONY 0xFF0000AA
#define FIOLETOWY 0x9E3DFFAA
#define NIEBIESKI 0x0000FFAA
#define POMARANCZOWY 0xFF8000AA
#define ROZOWY 0xFF66CCAA
#define SZARY 0xB0B0B0AA
#define ZIELONY 0x00CC00AA
#define ZOLTY 0xFFFF00AA
#define BEZOWY 0xFFFFADAA
#define BIALY 0xFFFFFFAA
#define BORDOWY 0x99001FAA
#define BRAZOWY 0x997A00AA
#define CIEMNY_ZIELONY 0x336633AA
#define CZARNY 0x000000AA
#define CZERWONY 0xFF0000AA
#define FIOLETOWY 0x9E3DFFAA
#define NIEBIESKI 0x0000FFAA
#define POMARANCZOWY 0xFF8000AA
#define ROZOWY 0xFF66CCAA
#define SZARY 0xB0B0B0AA
#define ZIELONY 0x00CC00AA
#define ZOLTY 0xFFFF00AA

#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_fiolet 0x8000FFFF
#define COLOR_LIGHTBLUE 0x6DC5F3FF
#define COLOR_LIGHTYELLOW 0xFAEAA9FF
#define COLOR_LIGHTGREEN 0x00FF00FF
#define COLOR_LIGHTORANGE 0xF7A26FFF
#define COLOR_LIGHTRED 0xFF0000FF
#define COLOR_RED 0xAA3333AA
#define COLOR_GREEN 0x33AA33AA
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_RED 0xAA3333AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_BLUE 0xFF9900AA
#define COLOR_SYSTEM 0xEFEFF7AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_PINK 0xFF66FFAA
#define SPAWN_DELAY 3000
#define COLOR_KOMENDA 0xC83322FF
#define COLOR_GRAD1 0xC83322FF

#define COLOR_WIADOMOSC 0x00FF00FF
#define COLOR_BLACK 0x000000FF

strtok(const string[], &index)
{
		new length = strlen(string);
		while ((index < length) && (string[index] <= ' '))
		{
			index++;
		}

		new offset = index;
		new result[20];
		while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
		{
			result[index - offset] = string[index];
			index++;
		}
		result[index - offset] = EOS;
		return result;
}
