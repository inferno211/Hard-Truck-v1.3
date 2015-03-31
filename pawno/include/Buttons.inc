#define MAX_BUTTONS   				10

/*------------------------------------------------------------------------------
native AddButton(Float:X, Float:Y, Float:Z, Float: RotZ);
*/

/*
	INCLUDE STWORZONY PRZEZ FIRE DRAGON'A !
	UKRADNIESZ MOJ¥ PRACÊ TO UMRZE CI MATKA !
*/

forward OnPlayerPressingButton(playerid, buttonid);
forward CheckButtons();
new ButtonCount = 0;

enum ButtonInfo
{
	Created,
	Float: posX,
	Float: posY,
	Float: posZ,
	Float: ExRotZ,
	ButtonObject,
};

new Button[MAX_BUTTONS][ButtonInfo];

stock GetXYInFrontOfObject(objectid, &Float:x, &Float:y, Float:distance)
{
	new Float:a, Float: rx, Float: ry;
	GetObjectPos(objectid, x, y, a); GetObjectRot(objectid, rx, ry, a);
	x += (distance * floatsin(-a, degrees)); y += (distance * floatcos(-a, degrees));
}

stock PlayerToPoint(Float:radi,playerid,Float:x,Float:y,Float:z)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	tempposx = (oldposx -x);
	tempposy = (oldposy -y);
	tempposz = (oldposz -z);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) return 1;
	return 0;
}


stock AddButton(Float: fX, Float: fY, Float: fZ, Float: rZ)
{
	ButtonCount++;
 	new ID = ButtonCount;
	Button[ID][Created] = 1;
	Button[ID][posX] = fX;
	Button[ID][posY] = fY;
	Button[ID][posZ] = fZ;
	Button[ID][ExRotZ] = rZ;
	Button[ID][ButtonObject] = CreateObject(2961,fX,fY,fZ,0,0,rZ);
	if(ID == 1)
	{
		SetTimer("CheckButtons", 250, true);
	}
	return ID;
}

public CheckButtons()
{
	for(new ID = 0; ID < MAX_BUTTONS; ID++)
	{
		if(Button[ID][Created] == 1)
		{
			for(new i = 0; i < GetMaxPlayers(); i++)
			{
				if(IsPlayerConnected(i))
				{
					if(PlayerToPoint(2,i,Button[ID][posX],Button[ID][posY],Button[ID][posZ]))
					{
						new ExKey, UpnDown, LeftnRight, Float: ButX, Float: ButY, Float: ButZ;
						GetPlayerKeys(i, ExKey, UpnDown, LeftnRight);
						if(ExKey == 16)
						{
							GetPlayerPos(i, ButX, ButY, ButZ);
						    GetXYInFrontOfObject(Button[ID][ButtonObject], ButX, ButY, -0.65);
						    SetPlayerPos(i, ButX, ButY, ButZ);
						    SetPlayerFacingAngle(i, Button[ID][ExRotZ]);
						    CallRemoteFunction("OnPlayerPressingButton", "ii", i, ID);
						    ApplyAnimation(i, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
						}
					}
				}
			}
		}
	}
	return 1;
}
