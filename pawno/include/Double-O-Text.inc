#if defined _dot_included
	#endinput
#endif
#define _dot_included

#include <a_samp>
#include <YSI\y_bit>
//#include <Double-O-Bits>

#if !defined _dob_included
	#define DOB_SetBit      Bit_Set
	#define DOB_GetBit      Bit_Get
	#define DOB_GetOnes     Bit_GetCount
	#define DOB_SetAllBits  Bit_SetAll
	#define DOB:: \
	    DOB_
#endif

//==============================================================================

#define MAX_STREAMED_TEXT_DRAWS         (50000)
#define MAX_TEXT_DRAW_STRING            (10240)
#define FADE_OUT_INTERVAL 				(1000)

#define PUBLIC:%0(%1) 	forward %0(%1); \
						public %0(%1)

#define DOT:: \
	DOT_

//==============================================================================

enum tdInfo
{
	Text: tdTextDrawID,
	tdString [MAX_TEXT_DRAW_STRING char],
	Float: tdPosX,
	Float: tdPosY,
	Float: tdLetterSizeX,
	Float: tdLetterSizeY,
	Float: tdTextSizeX,
	Float: tdTextSizeY,
	tdFont,
	tdAlignment,
	tdColor,
	tdBoxColor,
	tdShadow,
	tdOutline,
	tdBackgroundColor
}

static
	DOT::TextDrawInfo [MAX_STREAMED_TEXT_DRAWS][tdInfo],
	BitArray: DOT::TextDrawCreated <MAX_STREAMED_TEXT_DRAWS>,
	BitArray: DOT::TextDrawBoxUsed <MAX_STREAMED_TEXT_DRAWS>,
	BitArray: DOT::TextDrawProportional <MAX_STREAMED_TEXT_DRAWS>,
	BitArray: DOT::TextDrawShown [MAX_STREAMED_TEXT_DRAWS]<MAX_PLAYERS>;

//==============================================================================

PUBLIC: Text: DOT::TextDrawCreate (Float: x, Float:y, text [])
{
	if (text [0])
	{
		for (new i = 0; i < MAX_STREAMED_TEXT_DRAWS; ++i)
		{
		    if (!DOB::GetBit (DOT::TextDrawCreated, i))
		    {
		        DOT::TextDrawInfo [i][tdTextDrawID] = Text: INVALID_TEXT_DRAW;
		        strpack (DOT::TextDrawInfo [i][tdString], text, MAX_TEXT_DRAW_STRING);
		        DOT::TextDrawInfo [i][tdPosX] = x;
		        DOT::TextDrawInfo [i][tdPosY] = y;
		        DOT::TextDrawInfo [i][tdLetterSizeX] = 0.48;
		        DOT::TextDrawInfo [i][tdLetterSizeY] = 1.12;
		        DOT::TextDrawInfo [i][tdTextSizeX] = 1280.0;
		        DOT::TextDrawInfo [i][tdTextSizeY] = 1280.0;
		        DOT::TextDrawInfo [i][tdFont] = 1;
		        DOT::TextDrawInfo [i][tdAlignment] = 1; // left
		        DOT::TextDrawInfo [i][tdColor] = 0xE1E1E1FF;
		        DOT::TextDrawInfo [i][tdBoxColor] = 0x80808080;
		        DOT::TextDrawInfo [i][tdShadow] = 2;
		        DOT::TextDrawInfo [i][tdOutline] = 0;
		        DOT::TextDrawInfo [i][tdBackgroundColor] = 0x000000FF;
		        DOB::SetBit (DOT::TextDrawCreated, i, true);
		        DOB::SetBit (DOT::TextDrawBoxUsed, i, false);
				DOB::SetBit (DOT::TextDrawProportional, i, false);
				DOB::SetAllBits (DOT::TextDrawShown [i], false);
		        return Text: i;
		    }
		}
	}
	return Text: INVALID_TEXT_DRAW;
}

PUBLIC: DOT::TextDrawDestroy (Text: text)
{
	if (DOT::TextDrawValid (text))
	{
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
        {
		    TextDrawDestroy (DOT::TextDrawInfo [_: text][tdTextDrawID]);
		    DOT::TextDrawInfo [_: text][tdTextDrawID] = Text: INVALID_TEXT_DRAW;
		}
        DOB::SetBit (DOT::TextDrawCreated, _: text, false);
        DOB::SetAllBits (DOT::TextDrawShown [_: text], false);
        return 0;
	}
	return 0;
}

PUBLIC: DOT::TextDrawLetterSize (Text: text, Float: x, Float: y)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdLetterSizeX] = x;
        DOT::TextDrawInfo [_: text][tdLetterSizeY] = y;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawLetterSize (DOT::TextDrawInfo [_: text][tdTextDrawID], x, y);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawTextSize (Text: text, Float: x, Float: y)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdTextSizeX] = x;
        DOT::TextDrawInfo [_: text][tdTextSizeY] = y;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawTextSize (DOT::TextDrawInfo [_: text][tdTextDrawID], x, y);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawAlignment (Text: text, alignment)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdAlignment] = alignment;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawAlignment (DOT::TextDrawInfo [_: text][tdTextDrawID], alignment);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawColor (Text: text, color)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdColor] = color;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawColor (DOT::TextDrawInfo [_: text][tdTextDrawID], color);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawUseBox (Text: text, use)
{
    if (DOT::TextDrawValid (text))
	{
	    DOB::SetBit (DOT::TextDrawBoxUsed, _: text, (use != 0));
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawUseBox (DOT::TextDrawInfo [_: text][tdTextDrawID], use);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawBoxColor (Text: text, color)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdBoxColor] = color;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawBoxColor (DOT::TextDrawInfo [_: text][tdTextDrawID], color);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawSetShadow (Text: text, size)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdShadow] = size;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawSetShadow (DOT::TextDrawInfo [_: text][tdTextDrawID], size);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawSetOutline (Text: text, size)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdOutline] = size;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawSetOutline (DOT::TextDrawInfo [_: text][tdTextDrawID], size);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawBackgroundColor (Text: text, color)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdBackgroundColor] = color;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawBackgroundColor (DOT::TextDrawInfo [_: text][tdTextDrawID], color);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawFont (Text: text, font)
{
    if (DOT::TextDrawValid (text))
	{
        DOT::TextDrawInfo [_: text][tdFont] = font;
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawFont (DOT::TextDrawInfo [_: text][tdTextDrawID], font);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawSetProportional (Text: text, set)
{
    if (DOT::TextDrawValid (text))
	{
	    DOB::SetBit (DOT::TextDrawProportional, _: text, (set != 0));
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawSetProportional (DOT::TextDrawInfo [_: text][tdTextDrawID], set);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawSetString (Text: text, string [])
{
    if (DOT::TextDrawValid (text))
	{
	    strpack (DOT::TextDrawInfo [_: text][tdString], string, MAX_TEXT_DRAW_STRING);
        if (DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
	        TextDrawSetString (DOT::TextDrawInfo [_: text][tdTextDrawID], string);
        return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawShowForPlayer (playerid, Text: text)
{
    if (IsPlayerConnected (playerid) && !IsPlayerNPC (playerid) && DOT::TextDrawValid (text))
    {
        if (DOB::GetBit (DOT::TextDrawShown [_: text], playerid))
        {
            TextDrawShowForPlayer (playerid, DOT::TextDrawInfo [_: text][tdTextDrawID]);
            return 1;
		}

		if (DOT::TextDrawInfo [_: text][tdTextDrawID] == Text: INVALID_TEXT_DRAW)
		{
		    new string [MAX_TEXT_DRAW_STRING];
		    strunpack (string, DOT::TextDrawInfo [_: text][tdString]);
			if ((DOT::TextDrawInfo [_: text][tdTextDrawID] = TextDrawCreate (DOT::TextDrawInfo [_: text][tdPosX], DOT::TextDrawInfo [_: text][tdPosY], string)) != Text: INVALID_TEXT_DRAW)
		    {
		        if (DOB::GetBit (DOT::TextDrawBoxUsed, _: text))
		        {
					TextDrawUseBox (DOT::TextDrawInfo [_: text][tdTextDrawID], true);
					TextDrawTextSize (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdTextSizeX], DOT::TextDrawInfo [_: text][tdTextSizeY]);
					TextDrawBoxColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdBoxColor]);
				}
				TextDrawAlignment (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdAlignment]);
				TextDrawColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdColor]);
				TextDrawSetShadow (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdShadow]);
				TextDrawSetOutline (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdOutline]);
				TextDrawBackgroundColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdBackgroundColor]);
				TextDrawFont (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdFont]);
				if (DOB::GetBit (DOT::TextDrawProportional, _: text))
					TextDrawSetProportional (DOT::TextDrawInfo [_: text][tdTextDrawID], true);
		        TextDrawLetterSize (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdLetterSizeX], DOT::TextDrawInfo [_: text][tdLetterSizeY]);
				TextDrawShowForPlayer (playerid, DOT::TextDrawInfo [_: text][tdTextDrawID]);
				DOB::SetBit (DOT::TextDrawShown [_: text], playerid, true);
				return 1;
			}
		}
		else
		{
		    TextDrawShowForPlayer (playerid, DOT::TextDrawInfo [_: text][tdTextDrawID]);
			DOB::SetBit (DOT::TextDrawShown [_: text], playerid, true);
        	return 1;
		}
    }
    return 0;
}

PUBLIC: DOT::TextDrawHideForPlayer (playerid, Text: text)
{
	if (IsPlayerConnected (playerid) && !IsPlayerNPC (playerid) && DOT::TextDrawValid (text))
    {
        if (DOB::GetBit (DOT::TextDrawShown [_: text], playerid))
		{
		    TextDrawHideForPlayer (playerid, DOT::TextDrawInfo [_: text][tdTextDrawID]);
		    DOB::SetBit (DOT::TextDrawShown [_: text], playerid, false);
		    if (!DOB::GetOnes (DOT::TextDrawShown [_: text]) && DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
		    {
                TextDrawDestroy (DOT::TextDrawInfo [_: text][tdTextDrawID]);
                DOT::TextDrawInfo [_: text][tdTextDrawID] = Text: INVALID_TEXT_DRAW;
		    }
			return 1;
		}
    }
    return 0;
}

PUBLIC: DOT::TextDrawShowForAll (Text: text)
{
	if (DOT::TextDrawValid (text))
	{
	    for (new i = 0; i < MAX_PLAYERS; ++i)
	        if (IsPlayerConnected (i) && !IsPlayerNPC (i))
				DOT::TextDrawShowForPlayer (i, text);
		return 1;
	}
	return 0;
}

PUBLIC: DOT::TextDrawHideForAll (Text: text)
{
	if (DOT::TextDrawValid (text))
	{
	    for (new i = 0; i < MAX_PLAYERS; ++i)
	        if (IsPlayerConnected (i) && !IsPlayerNPC (i))
				DOT::TextDrawHideForPlayer (i, text);
		return 1;
	}
	return 0;
}

// Additional functions.

PUBLIC: bool: DOT::TextDrawValid (Text: text)
	return (_: text >= 0 && _: text < MAX_STREAMED_TEXT_DRAWS && DOB::GetBit (DOT::TextDrawCreated, _: text));

PUBLIC: DOT::TextDrawFadeOutForAll (Text: text, time)
{
	if (DOT::TextDrawValid (text) && DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW)
		return SetTimerEx ("DOT_FadeOutUpdateForAll", FADE_OUT_INTERVAL, false, "iii", _: text, time / FADE_OUT_INTERVAL, time / FADE_OUT_INTERVAL);
	return 0;
}

PUBLIC: DOT::FadeOutUpdateForAll (Text: text, update, start)
{
    if (DOT::TextDrawValid (text) && DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW && update >= 0)
	{
        if (update)
        {
            TextDrawColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawFadeOutColor (DOT::TextDrawInfo [_: text][tdColor], update, start));
        	TextDrawBackgroundColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawFadeOutColor (DOT::TextDrawInfo [_: text][tdBackgroundColor], update, start));
        	TextDrawBoxColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawFadeOutColor (DOT::TextDrawInfo [_: text][tdBoxColor], update, start));
        	
			for (new i = 0; i < MAX_PLAYERS; ++i)
			{
			    if (IsPlayerConnected (i) && !IsPlayerNPC (i))
			    {
			        if (DOB::GetBit (DOT::TextDrawShown [_: text], i))
			        {
			            TextDrawHideForPlayer (i, DOT::TextDrawInfo [_: text][tdTextDrawID]);
	                    TextDrawShowForPlayer (i, DOT::TextDrawInfo [_: text][tdTextDrawID]);
			        }
			    }
			}
			
 			TextDrawColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdColor]);
        	TextDrawBackgroundColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdBackgroundColor]);
        	TextDrawBoxColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdBoxColor]);
        	SetTimerEx ("DOT_FadeOutUpdateForAll", FADE_OUT_INTERVAL, false, "iii", _: text, update - 1, start);
		}
		else
			DOT::TextDrawHideForAll (text);
		return 1;
    }
    return 0;
}

PUBLIC: DOT::TextDrawFadeOutForPlayer (playerid, Text: text, time)
{
	if (DOT::TextDrawValid (text) && DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW && DOB::GetBit (DOT::TextDrawShown [_: text], playerid))
		return SetTimerEx ("DOT_FadeOutUpdateForPlayer", FADE_OUT_INTERVAL, false, "iiii", playerid, _: text, time / FADE_OUT_INTERVAL, time / FADE_OUT_INTERVAL);
	return 0;
}

PUBLIC: DOT::FadeOutUpdateForPlayer (playerid, Text: text, update, start)
{
    if (DOT::TextDrawValid (text) && DOT::TextDrawInfo [_: text][tdTextDrawID] != Text: INVALID_TEXT_DRAW && DOB::GetBit (DOT::TextDrawShown [_: text], playerid) && update >= 0)
	{
        if (update)
        {
            TextDrawColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawFadeOutColor (DOT::TextDrawInfo [_: text][tdColor], update, start));
        	TextDrawBackgroundColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawFadeOutColor (DOT::TextDrawInfo [_: text][tdBackgroundColor], update, start));
        	TextDrawBoxColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawFadeOutColor (DOT::TextDrawInfo [_: text][tdBoxColor], update, start));
        	
            TextDrawHideForPlayer (playerid, DOT::TextDrawInfo [_: text][tdTextDrawID]);
            TextDrawShowForPlayer (playerid, DOT::TextDrawInfo [_: text][tdTextDrawID]);
	                    
 			TextDrawColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdColor]);
        	TextDrawBackgroundColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdBackgroundColor]);
        	TextDrawBoxColor (DOT::TextDrawInfo [_: text][tdTextDrawID], DOT::TextDrawInfo [_: text][tdBoxColor]);
        	SetTimerEx ("DOT_FadeOutUpdateForPlayer", FADE_OUT_INTERVAL, false, "iiii", playerid, _: text, update - 1, start);
		}
		else
			DOT::TextDrawHideForPlayer (playerid, text);
		return 1;
    }
    return 0;
}

PUBLIC: DOT::TextDrawGetString (Text: text, string [], len)
{
	if (DOT::TextDrawValid (text))
		return strunpack (string, DOT::TextDrawInfo [_: text][tdString], len);
	return 0;
}

static stock DOT::TextDrawFadeOutColor (color, update, start)
    return ((color & 0xFFFFFF00) | (floatround (float (color & 0xFF) * (float (update) / float (start))) & 0xFF));

//==============================================================================

public OnPlayerDisconnect (playerid, reason)
{
	if (reason == 2)
		SetTimerEx ("DOT_KickFix", max ((GetPlayerPing (playerid) * 2) + 50, 500), false, "i", playerid);
	else
	    for (new i = 0; i < MAX_STREAMED_TEXT_DRAWS; ++i)
			DOT::TextDrawHideForPlayer (playerid, Text: i);
	return CallLocalFunction ("DOT_OnPlayerDisconnect", "ii", playerid, reason);
}

PUBLIC: DOT::KickFix (playerid)
{
    for (new i = 0; i < MAX_STREAMED_TEXT_DRAWS; ++i)
		DOT::TextDrawHideForPlayer (playerid, Text: i);
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect DOT_OnPlayerDisconnect
forward DOT_OnPlayerDisconnect (playerid, reason);

//==============================================================================

#define TextDrawCreate          	DOT_TextDrawCreate
#define TextDrawDestroy         	DOT_TextDrawDestroy
#define TextDrawLetterSize      	DOT_TextDrawLetterSize
#define TextDrawTextSize            DOT_TextDrawTextSize
#define TextDrawAlignment           DOT_TextDrawAlignment
#define TextDrawColor               DOT_TextDrawColor
#define TextDrawUseBox              DOT_TextDrawUseBox
#define TextDrawBoxColor            DOT_TextDrawBoxColor
#define TextDrawSetShadow           DOT_TextDrawSetShadow
#define TextDrawSetOutline          DOT_TextDrawSetOutline
#define TextDrawBackgroundColor     DOT_TextDrawBackgroundColor
#define TextDrawFont                DOT_TextDrawFont
#define TextDrawSetProportional     DOT_TextDrawSetProportional
#define TextDrawShowForPlayer       DOT_TextDrawShowForPlayer
#define TextDrawHideForPlayer       DOT_TextDrawHideForPlayer
#define TextDrawShowForAll          DOT_TextDrawShowForAll
#define TextDrawHideForAll          DOT_TextDrawHideForAll
#define TextDrawSetString           DOT_TextDrawSetString
#define TextDrawValid               DOT_TextDrawValid
#define TextDrawFadeOutForAll       DOT_TextDrawFadeOutForAll
#define TextDrawFadeOutForPlayer    DOT_TextDrawFadeOutForPlayer
#define TextDrawGetString           DOT_TextDrawGetString

#if defined MAX_TEXT_DRAWS
	#undef MAX_TEXT_DRAWS
#endif
#define MAX_TEXT_DRAWS              MAX_STREAMED_TEXT_DRAWS
