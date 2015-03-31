#if defined NO_MYSQL				/* USE LOCAL MYSQL DATABASE */
	#define SQL_HOST 				"localhost"
	#define SQL_USER 				"baza_3286"
	#define SQL_PASS 				"fjgespjqeD"
	#define SQL_DB 					"baza_3286"
#else								/* USE EXTERNAL DATABASE, FILL IN DETAILS YOURSELF */
	#define SQL_HOST 				"localhost"
	#define SQL_USER 				"baza_3286"
	#define SQL_PASS 				"fjgespjqeD"
	#define SQL_DB 					"baza_3286"
#endif

#undef MAX_PLAYERS
#define MAX_PLAYERS 20

#define SCRIPT_NAME "Capture The Ship"
#define SCRIPT_AUTHOR "William"
#define SCRIPT_VERSION "1.0.0"
#define SCRIPT_WEBSITE "www.CTS2011.ugu.pl"

#define DIALOG_AUTOFIX          (100)
#define DIALOG_CARMENU          (101)
#define DIALOG_CARMENU_COLOR1   (102)
#define DIALOG_CARMENU_COLOR2   (103)
#define DIALOG_CARMENU_PLATE	(104)
#define DIALOG_CARMENU_WHEELS   (105)
#define DIALOG_LOGIN 			(106)
#define DIALOG_REGISTER         (107)
#define DIALOG_RULES			(108)
#define DIALOG_ADMINLIST		(109)
#define DIALOG_HELP				(110)
#define DIALOG_REPORT_ID		(111)
#define DIALOG_REPORT_REAS		(112)
#define DIALOG_REPORT_REAS2		(113)
#define DIALOG_BUGREPORT		(114)
#define DIALOG_WEATHER			(115)
#define DIALOG_TIME				(116)
#define DIALOG_SKYDIVE			(117)
#define DIALOG_POSINFO			(118)
#define DIALOG_QUICKANNOUNCE	(119)
#define DIALOG_AWEAPONS			(120)
#define DIALOG_AWEAPONS_COMBAT	(121)
#define DIALOG_AWEAPONS_LIGHT	(122)
#define DIALOG_AWEAPONS_HEAVY	(123)
#define DIALOG_REPORTLOG		(124)
#define DIALOG_GMX				(125)
#define DIALOG_LPLATE			(126)
#define DIALOG_STATS			(127)
#define DIALOG_SSTATS			(128)
#define DIALOG_RESETPLAYER		(129)
#define DIALOG_SETSPAWN			(130)
#define DIALOG_WEAPONSET		(131)
#define DIALOG_INTERIORS		(132)
#define DIALOG_INTERIORS1		(133)
#define DIALOG_INTERIORS2		(134)
#define DIALOG_INTERIORS3		(135)
#define DIALOG_INTERIORS4		(136)
#define DIALOG_INTERIORS5		(137)
#define DIALOG_INTERIORS6		(138)
#define DIALOG_INTERIORS7		(139)
#define DIALOG_INTERIORS8		(140)
#define DIALOG_INTERIORS9		(141)
#define DIALOG_INTERIORS10		(142)
#define DIALOG_INTERIORS11		(143)
#define DIALOG_INTERIORS12		(144)
#define DIALOG_INTERIORS13		(145)
#define DIALOG_INTERIORS14		(146)
#define DIALOG_INTERIORS15		(147)
#define DIALOG_INTERIORS16		(148)
#define DIALOG_INTERIORS17		(149)
#define DIALOG_INTERIORS18		(150)
#define DIALOG_INTERIORS19		(151)
#define DIALOG_CHALLENGESTART	(152)
#define DIALOG_CMDHELP			(153)
#define DIALOG_MENU_ACMDS		(154)
#define DIALOG_CARCONFIG		(155)
#define DIALOG_BUSINESS			(156)
#define DIALOG_BUSINESS_OWNED	(157)
#define DIALOG_BUSINESS_POWNED	(158)
#define DIALOG_CARTUNE			(159)
#define DIALOG_CARSELECT		(160)
#define DIALOG_CARSELECT1		(161)
#define DIALOG_CARSELECT2		(162)
#define DIALOG_CARSELECT3		(163)
#define DIALOG_CARSELECT4		(164)
#define DIALOG_CARSELECT5		(165)
#define DIALOG_CARSELECT6		(166)
#define DIALOG_CARSELECT7		(167)
#define DIALOG_CARSELECT8		(168)
#define DIALOG_CARSELECT9		(169)
#define DIALOG_CARSELECT10		(170)
#define DIALOG_CARSELECT11		(171)
#define DIALOG_CARSELECT12		(172)
#define DIALOG_CARSELECT13		(173)
#define DIALOG_CARSELECT14		(174)
#define DIALOG_CARSELECT15		(175)
#define DIALOG_CHANNELS			(176)
#define DIALOG_CNAME			(177)
#define DIALOG_CHANNELSPAWN		(178)
#define DIALOG_LMS_CHOOSEZONE	(179)
#define DIALOG_LMS_HELP			(180)
#define DIALOG_GANGDM			(181)
#define DIALOG_LMS_EXPLOSIONS	(182)
#define DIALOG_LMS_WEAPONS		(183)
#define DIALOG_LMS_STAKE		(184)
#define DIALOG_LMS_ADMINS		(185)
#define DIALOG_ACHAT			(186)
#define DIALOG_TOPMENU			(187)
#define DIALOG_TOP				(188)
#define DIALOG_BANS				(189)
#define DIALOG_LCONNECTS		(190)
#define DIALOG_DONATE			(191)
#define DIALOG_DONATE2			(192)
#define DIALOG_ALIST			(193)
#define DIALOG_TOP_SCORE		(194)
#define DIALOG_TOP_CHWON		(195)
#define DIALOG_TOP_BBOUGHT		(196)
#define DIALOG_TOP_PLAYED		(197)
#define DIALOG_TOP_KILLS		(198)
#define DIALOG_GROUPS			(199)
#define DIALOG_CRASHED			(200)
#define DIALOG_TOP_CHTIME		(201)
#define DIALOG_PAINTJOB			(202)
#define DIALOG_APAINTJOB		(203)
#define DIALOG_ATUNE			(204)
#define DIALOG_RECENTLYLEFT		(205)
#define DIALOG_CHECKW			(206)
#define DIALOG_SPEEDO			(207)

#define VWORLD_HOME				(0)

#define COLOR_YELLOW			0xFFDD00AA
#define COLOR_GREY 				0xAFAFAFAA
#define COLOR_REDONLY			0xE60000FF
#define COLOR_LIGHTBLUE 		0x00C2ECFF
#define COLOR_DARKBLUE 			0x2641FEAA
#define COLOR_GREEN 			0x33AA33AA
#define COLOR_RED 				0xAA3333AA
#define COLOR_WHITE 			0xF6F6F6AA
#define COLOR_BLUEONLY			0x0000F6AA
#define COLOR_BLACK 			0x000000AA
#define COLOR_NICE_BLUE 		0xa0d3ffAA
#define COLOR_GREEN2			0x21DD00FF
#define COLOR_ADMIN_RED 		0xFB0000FF
#define COLOR_ORANGE 			0xFF9900AA
#define COLOR_LIGHTRED 			0xFF6347AA
#define COLOR_LIGHTBLUE 		0x00C2ECFF
#define COLOR_PURPLE 			0xB360FDFF
#define COLOR_BLUE 				0x1229FAFF
#define COLOR_LIGHTGREEN 		0x38FF06FF
#define COLOR_DARKPINK 			0xE100E1FF
#define COLOR_DARKGREEN 		0x008040FF
#define COLOR_ANNOUNCEMENT		0x00CACAFB
#define COLOR_MESSAGE 			0x00C7FFAA
#define COLOR_SYSTEM 			0xEFEFF7AA << 2
#define COLOR_NICEBLUE 			0x00FFFFFF
#define COLOR_GRAY				0xCECECEFF
#define COLOR_PINKPURPLE		0xFF00FFFF
#define COLOR_BROWN 			0xA52A2AAA
#define COLOR_PINK 				0xFF66FFAA
#define GRP_CHAT_CLR    		0x22FF22EE
#define GRP_INFO_CLR    		0x00BB33DD
#define GRP_WARN_CLR    		0x00BB00FF
/*
#define dcmd(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define dcmdS(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid)))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid))))) return 1
#define dcmd2(%1,%2,%3,%4,%5) if (((strcmp((%5)[1], #%1, true, (%2)) == 0) && ((((%5)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%5)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%5)[(%2) + 2]))))) || ((strcmp((%5)[1], #%3, true, (%4)) == 0) && ((((%5)[(%4) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%5)[(%4) + 1] == 32) && (dcmd_%1(playerid, (%5)[(%4) + 2]))))) ) return 1
#define dcmd2S(%1,%2,%3,%4,%5) if (((strcmp((%5)[1], #%1, true, (%2)) == 0) && ((((%5)[(%2) + 1] == 0) && (dcmd_%1(playerid)))||(((%5)[(%2) + 1] == 32) && (dcmd_%1(playerid))))) || ((strcmp((%5)[1], #%3, true, (%4)) == 0) && ((((%5)[(%4) + 1] == 0) && (dcmd_%1(playerid)))||(((%5)[(%4) + 1] == 32) && (dcmd_%1(playerid))))) ) return 1
#define UpperToLower(%1) for ( new ToLowerChar; ToLowerChar < strlen( %1 ); ToLowerChar ++ ) if ( %1[ ToLowerChar ]> 64 && %1[ ToLowerChar ] < 91 ) %1[ ToLowerChar ] += 32
*/
#define SetPlayerHoldingObject(%1,%2,%3,%4,%5,%6,%7,%8,%9) SetPlayerAttachedObject(%1,MAX_PLAYER_ATTACHED_OBJECTS-1,%2,%3,%4,%5,%6,%7,%8,%9)
#define StopPlayerHoldingObject(%1) RemovePlayerAttachedObject(%1,MAX_PLAYER_ATTACHED_OBJECTS-1)
#define IsPlayerHoldingObject(%1) IsPlayerAttachedObjectSlotUsed(%1,MAX_PLAYER_ATTACHED_OBJECTS-1)