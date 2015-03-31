#if defined _dot_included
	#endinput
#endif
#define _dot_included

#include <a_samp>

#define DOTC:: \
	DOTC_

stock Text: DOTC::TextDrawCreate (Float: x, Float: y, text [])
	return Text: CallRemoteFunction ("DOT_TextDrawCreate", "ffs", x, y, text);

stock DOTC::TextDrawDestroy (Text: text)
	return CallRemoteFunction ("DOT_TextDrawDestroy", "i", _: text);

stock DOTC::TextDrawLetterSize (Text: text, Float: x, Float: y)
	return CallRemoteFunction ("DOT_TextDrawLetterSize", "iff", _: text, x, y);

stock DOTC::TextDrawTextSize (Text: text, Float: x, Float: y)
	return CallRemoteFunction ("DOT_TextDrawTextSize", "iff", _: text, x, y);

stock DOTC::TextDrawAlignment (Text: text, alignment)
	return CallRemoteFunction ("DOT_TextDrawAlignment", "ii", _: text, alignment);

stock DOTC::TextDrawColor (Text: text, color)
	return CallRemoteFunction ("DOT_TextDrawColor", "ii", _: text, color);

stock DOTC::TextDrawUseBox (Text: text, use)
	return CallRemoteFunction ("DOT_TextDrawUseBox", "ii", _: text, use);

stock DOTC::TextDrawBoxColor (Text: text, color)
	return CallRemoteFunction ("DOT_TextDrawBoxColor", "ii", _: text, color);

stock DOTC::TextDrawSetShadow (Text: text, size)
	return CallRemoteFunction ("DOT_TextDrawSetShadow", "ii", _: text, size);

stock DOTC::TextDrawSetOutline (Text: text, size)
	return CallRemoteFunction ("DOT_TextDrawSetOutline", "ii", _: text, size);

stock DOTC::TextDrawBackgroundColor (Text: text, color)
	return CallRemoteFunction ("DOT_TextDrawBackgroundColor", "ii", _: text, color);

stock DOTC::TextDrawFont (Text: text, font)
	return CallRemoteFunction ("DOT_TextDrawFont", "ii", _: text, font);

stock DOTC::TextDrawSetProportional (Text: text, set)
	return CallRemoteFunction ("DOT_TextDrawSetProportional", "ii", _: text, set);

stock DOTC::TextDrawShowForPlayer (playerid, Text: text)
	return CallRemoteFunction ("DOT_TextDrawShowForPlayer", "ii", playerid, _: text);

stock DOTC::TextDrawHideForPlayer (playerid, Text: text)
	return CallRemoteFunction ("DOT_TextDrawHideForPlayer", "ii", playerid, _: text);

stock DOTC::TextDrawShowForAll (Text: text)
	return CallRemoteFunction ("DOT_TextDrawShowForAll", "i", _: text);

stock DOTC::TextDrawHideForAll (Text: text)
	return CallRemoteFunction ("DOT_TextDrawHideForAll", "i", _: text);

stock DOTC::TextDrawSetString (Text: text, string [])
	return CallRemoteFunction ("DOT_TextDrawSetString", "is", _: text, string);
	
stock DOTC::TextDrawValid (Text: text)
	return CallRemoteFunction ("DOT_TextDrawValid", "i", _: text);
	
stock DOTC::TextDrawFadeOutForAll (Text: text, time)
	return CallRemoteFunction ("DOT_TextDrawFadeOutForAll", "ii", _: text, time);
	
stock DOTC::TextDrawFadeOutForPlayer (playerid, Text: text, time)
	return CallRemoteFunction ("DOT_TextDrawFadeOutForPlayer", "iii", playerid, _: text, time);
	
#define TextDrawCreate   			DOTC_TextDrawCreate
#define TextDrawDestroy   			DOTC_TextDrawDestroy
#define TextDrawLetterSize  		DOTC_TextDrawLetterSize
#define TextDrawTextSize   			DOTC_TextDrawTextSize
#define TextDrawAlignment   		DOTC_TextDrawAlignment
#define TextDrawColor    			DOTC_TextDrawColor
#define TextDrawUseBox    			DOTC_TextDrawUseBox
#define TextDrawBoxColor   			DOTC_TextDrawBoxColor
#define TextDrawSetShadow   		DOTC_TextDrawSetShadow
#define TextDrawSetOutline   		DOTC_TextDrawSetOutline
#define TextDrawBackgroundColor 	DOTC_TextDrawBackgroundColor
#define TextDrawFont    			DOTC_TextDrawFont
#define TextDrawSetProportional 	DOTC_TextDrawSetProportional
#define TextDrawShowForPlayer  		DOTC_TextDrawShowForPlayer
#define TextDrawHideForPlayer 		DOTC_TextDrawHideForPlayer
#define TextDrawShowForAll   		DOTC_TextDrawShowForAll
#define TextDrawHideForAll   		DOTC_TextDrawHideForAll
#define TextDrawSetString   		DOTC_TextDrawSetString
#define TextDrawValid           	DOTC_TextDrawValid
#define TextDrawFadeOutForAll   	DOTC_TextDrawFadeOutForAll
#define TextDrawFadeOutForPlayer	DOTC_TextDrawFadeOutForPlayer

#if defined MAX_TEXT_DRAWS
	#undef MAX_TEXT_DRAWS
#endif
#define MAX_TEXT_DRAWS          (5000)
