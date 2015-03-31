/*
	INCLUDE STWORZONY PRZEZ FIRE DRAGON'A !
	UKRADNIESZ MOJ¥ PRACÊ TO UMRZE CI MATKA !
*/

#define MAX_STREAM_OBJECTS          5000
#define MAX_ALLOW   				145
#define DRAW_DISTANCE               210
#if !defined dcmd
#define dcmd(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#endif
#if !defined foreach
#define foreach(%1,%2) for (new %2 = 0; %2 < MAX_PLAYERS; %2++) if (IsPlayerConnected(%2))
#endif
#if !defined __SSCANF_FOREACH__
#define __SSCANF_FOREACH__
#endif

/*------------------------------------
native dcmd_stream(stream, strlen("stream"), cmdtext);
native AddObject(modelid, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz);
native DelateObject(objid);
native SetupObject(objid, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz, Float: VDistance);
native GetupObject(objid, &Float: x, &Float: y, &Float: z, &Float: rx, &Float: ry, &Float: rz, &Float: VDistance);
native bool: IsObjectValid(objid);
native ResetupObject(objid, Float: newx, Float: newy, Float: newz, Float: speed);
native Stream_Init(playerid);
native Stream_Exit(playerid);
*/

enum _Objects
{
	ModelID,
	Float: objectX,
	Float: objectY,
	Float: objectZ,
	Float: rotationX,
	Float: rotationY,
	Float: rotationZ,
	Float: View_Distance,
	bool: IsObjectCreated,
	bool: IsObjectShown
};


new
	Objects[MAX_STREAM_OBJECTS][_Objects],
	ObjectStreamed[MAX_PLAYERS] = 0,
	ObjectModel[MAX_STREAM_OBJECTS][MAX_PLAYERS],
	oID,
	bool: Allow;

stock scan(string[], format[], {Float,_}:...)
{
	if (string[0] == 0 || (string[0] == 1 && string[1] == 0))
	{
		return format[0];
	}
	new	formatPos = 0, stringPos = 0, paramPos = 2, paramCount = numargs(), delim = ' ';
	while (string[stringPos] && string[stringPos] <= ' ')
	{
		stringPos++;
	}
	while (paramPos < paramCount && string[stringPos])
	{
		switch (format[formatPos++])
		{
			case '\0':
			{
				return 0;
			}
			case 'i', 'd':
			{
				new	neg = 1, num = 0, ch = string[stringPos];
				if (ch == '-')
				{
					neg = -1;
					ch = string[++stringPos];
				}
				do
				{
					stringPos++;
					if ('0' <= ch <= '9')
					{
						num = (num * 10) + (ch - '0');
					}
					else
					{
						return -1;
					}
				}
				while ((ch = string[stringPos]) > ' ' && ch != delim);
				setarg(paramPos, 0, num * neg);
			}
			case 'h', 'x':
			{
				new	num = 0, ch = string[stringPos];
				do
				{
					stringPos++;
					switch (ch)
					{
						case 'x', 'X':
						{
							num = 0;
							continue;
						}
						case '0' .. '9':
						{
							num = (num << 4) | (ch - '0');
						}
						case 'a' .. 'f':
						{
							num = (num << 4) | (ch - ('a' - 10));
						}
						case 'A' .. 'F':
						{
							num = (num << 4) | (ch - ('A' - 10));
						}
						default:
						{
							return -1;
						}
					}
				}
				while ((ch = string[stringPos]) > ' ' && ch != delim);
				setarg(paramPos, 0, num);
			}
			case 'c':
			{
				setarg(paramPos, 0, string[stringPos++]);
			}
			case 'f':
			{
				setarg(paramPos, 0, _:floatstr(string[stringPos]));
			}
			case 'p':
			{
				delim = format[formatPos++];
				continue;
			}
			case '\'':
			{
				new end = formatPos - 1, ch;
				while ((ch = format[++end]) && ch != '\'') {}
				if (!ch)
				{
					return -1;
				}
				format[end] = '\0';
				if ((ch = strfind(string, format[formatPos], false, stringPos)) == -1)
				{
					if (format[end + 1])
					{
						return -1;
					}
					return 0;
				}
				format[end] = '\'';
				stringPos = ch + (end - formatPos);
				formatPos = end + 1;
			}
			case 'u':
			{
				new end = stringPos - 1, id = 0, bool: num = true, ch;
				while ((ch = string[++end]) && ch != delim)
				{
					if (num)
					{
						if ('0' <= ch <= '9')
						{
							id = (id * 10) + (ch - '0');
						}
						else
						{
							num = false;
						}
					}
				}
				if (num && IsPlayerConnected(id))
				{
					setarg(paramPos, 0, id);
				}
				else
				{
					string[end] = '\0';
					num = false;
					new	name[MAX_PLAYER_NAME];
					id = end - stringPos;
					foreach (Player, playerid)
					{
						GetPlayerName(playerid, name, sizeof (name));
						if (!strcmp(name, string[stringPos], true, id))
						{
							setarg(paramPos, 0, playerid);
							num = true;
							break;
						}
					}
					if (!num)
					{
						setarg(paramPos, 0, INVALID_PLAYER_ID);
					}
					string[end] = ch;
				}
				stringPos = end;
			}
			case 's', 'z':
			{
				new
					i = 0,
					ch;
				if (format[formatPos])
				{
					while ((ch = string[stringPos++]) && ch != delim)
					{
						setarg(paramPos, i++, ch);
					}
					if (!i)
					{
						return -1;
					}
				}
				else
				{
					while ((ch = string[stringPos++]))
					{
						setarg(paramPos, i++, ch);
					}
				}
				stringPos--;
				setarg(paramPos, i, '\0');
			}
			default:
			{
				continue;
			}
		}
		while (string[stringPos] && string[stringPos] != delim && string[stringPos] > ' ')
		{
			stringPos++;
		}
		while (string[stringPos] && (string[stringPos] == delim || string[stringPos] <= ' '))
		{
			stringPos++;
		}
		paramPos++;
	}
	do
	{
		if ((delim = format[formatPos++]) > ' ')
		{
			if (delim == '\'')
			{
				while ((delim = format[formatPos++]) && delim != '\'') {}
			}
			else if (delim != 'z')
			{
				return delim;
			}
		}
	}
	while (delim > ' ');
	return 0;
}

dcmd_stream(playerid, params[])
{
		new tmp[128], Float: dis, Aname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, Aname, sizeof(Aname));
		if(!scan(params, "zf", tmp, dis)) goto ex_dis;
		if(scan(params, "z", tmp)) return SendClientMessage(playerid, COLOR_WHITE, "Use: /stream [distance [valute] | on | off]"), 1;
		if(!strcmp(tmp, "on", true))
		{
			format(tmp, sizeof(tmp), "%s(%i) has turned on objects.", Aname, playerid);
			SendClientMessageToAll(COLOR_ORANGE, tmp);
			Allow = false;
			return 1;
		}
		if(!strcmp(tmp, "off", true))
		{
			format(tmp, sizeof(tmp), "%s(%i) has turned off objects.",Aname, playerid);
			SendClientMessageToAll(COLOR_ORANGE, tmp);
			for(new i = 0, o = MAX_STREAM_OBJECTS; i < o; i++) for(new q = 0, k = GetMaxPlayers(); q < k; q++) DestroyPlayerObject(i, ObjectModel[i][q]);
			Allow = true;
			return 1;
		}
		ex_dis:
		if(!strcmp(tmp, "distance", true))
		{
			for(new i = 0, o = MAX_STREAM_OBJECTS; i < o; i++)
			{
				Objects[i][View_Distance] = dis;
			}
			format(tmp, sizeof(tmp), "%s(%i) has set object draw distance to %.02f.", Aname, playerid, dis);
			SendClientMessageToAll(COLOR_ORANGE, tmp);
		}
		return 1;
}

stock AddObject(modelid, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{
	oID++;
    Objects[oID][ModelID] = modelid;
    Objects[oID][objectX] = x;
    Objects[oID][objectY] = y;
    Objects[oID][objectZ] = z;
    Objects[oID][rotationX] = rx;
    Objects[oID][rotationY] = ry;
    Objects[oID][rotationZ] = rz;
    Objects[oID][View_Distance] = DRAW_DISTANCE;
    Objects[oID][IsObjectCreated] = true;
    return oID;
}

stock DelateObject(objid)
{
    Objects[objid][ModelID] = 0;
    Objects[objid][objectX] = 0;
    Objects[objid][objectY] = 0;
    Objects[objid][objectZ] = 0;
    Objects[objid][rotationX] = 0;
    Objects[objid][rotationY] = 0;
    Objects[objid][rotationZ] = 0;
    Objects[objid][View_Distance] = 0;
    Objects[objid][IsObjectCreated] = false;
    return 1;
}

stock SetupObject(objid, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz, Float: VDistance)
{
    Objects[objid][objectX] = x;
    Objects[objid][objectY] = y;
    Objects[objid][objectZ] = z;
    Objects[objid][rotationX] = rx;
    Objects[objid][rotationY] = ry;
    Objects[objid][rotationZ] = rz;
    Objects[objid][View_Distance] = VDistance;
    return 1;
}

stock GetupObject(objid, &Float: x, &Float: y, &Float: z, &Float: rx, &Float: ry, &Float: rz, &Float: VDistance)
{
    x = Objects[objid][objectX];
    y = Objects[objid][objectY];
    z = Objects[objid][objectZ];
    rx = Objects[objid][rotationX];
	ry = Objects[objid][rotationY];
    rz = Objects[objid][rotationZ];
    VDistance = Objects[objid][View_Distance];
    return 1;
}

stock bool: IsObjectValid(objid)
{
	if(Objects[objid][IsObjectCreated] == true) return true;
	return false;
}

stock ResetupObject(objid, Float: newx, Float: newy, Float: newz, Float: speed)
{
	MoveObject(objid, newx, newy, newz, speed);
 	Objects[objid][objectX] = newx;
    Objects[objid][objectY] = newy;
    Objects[objid][objectZ] = newz;
    return 1;
}

stock Float: GetPlayerDistanceToPoint(playerid,Float:x,Float:y,Float:z)
{
	new Float:x1,Float:y1,Float:z1;
	GetPlayerPos(playerid,x1,y1,z1);
	return floatsqroot((x-x1)*(x-x1)+(y-y1)*(y-y1)+(z-z1)*(z-z1));
}

stock IsReachet(playerid, Float: x, Float: y, Float: z, Float: radi)
{
	if(GetPlayerDistanceToPoint(playerid,x,y,z) < radi) return 1;
	return 0;
}

stock Stream_Exit(i)
{
    for(new q = 0, o = MAX_STREAM_OBJECTS; q < o; q++) DestroyPlayerObject(i, ObjectModel[q][i]);
    return 1;
}

stock Stream_Init(i)
{
	if(!Allow)
	{
		for(new k = 0, q = oID; k < q; k++)
		{
		    if(Objects[k][IsObjectCreated] == false) continue;
			if(IsReachet(i, Objects[k][objectX], Objects[k][objectY], Objects[k][objectZ], Objects[k][View_Distance]) && Objects[k][IsObjectShown] == false)
			{
				ObjectStreamed[i]++;
				if(ObjectStreamed[i] > MAX_ALLOW) break;
				ObjectModel[k][i] = CreatePlayerObject(i, Objects[k][ModelID], Objects[k][objectX], Objects[k][objectY], Objects[k][objectZ], Objects[k][rotationX], Objects[k][rotationY], Objects[k][rotationZ]);
			    Objects[k][IsObjectShown] = true;
			}
			if(!IsReachet(i, Objects[k][objectX], Objects[k][objectY], Objects[k][objectZ], Objects[k][View_Distance]) && Objects[k][IsObjectShown] == true)
			{
				DestroyPlayerObject(i, ObjectModel[k][i]);
				Objects[k][IsObjectShown] = false;
			    ObjectStreamed[i] =  ObjectStreamed[i] - 1;
     			}	
		}
	}
	return 1;
}