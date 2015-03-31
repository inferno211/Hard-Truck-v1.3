#include <pDefinitions>

stock getLight(vehicleid, element)
{
	if(GetVehicleModel(vehicleid) != 0 && element > 0 && element < 3)
	{
	    new part[4];
        GetVehicleDamageStatus(vehicleid,part[0],part[1],part[2],part[3]);
        if(part[2] != 0)
        {
            new str[5];
        	new strtemp[5];
        	new length;
        	new status;
            format(str,sizeof(str),"%b",part[2]);
        	length = strlen(str);
        	strcat(strtemp,str);
        	if(length != 3)
			{
			    length = 3 - length;
            	new length2 = 3 - length;
            	for(new i = 0; i < length; i++)
            	{
               		str[i] = '0';
                	strdel(str,length,length2);
            	}
            	strins(str,strtemp,length);
			}
			if(element == LEFT_LIGHT)
			{
			    GetChar(2,str);
			    if(strcmp(str,"1",true) == 0)
			        status = DAMAGED;

				else if(strcmp(str,"0",true) == 0)
				    status = FULL;
			}
			else if(element == RIGHT_LIGHT)
			{
			    GetChar(0,str);
			    if(strcmp(str,"1",true) == 0)
			        status = DAMAGED;

				else if(strcmp(str,"0",true) == 0)
				    status = FULL;
			}
			return status;
        }
        else
			return FULL;

	}
	return -1;
}

stock setLight(vehicleid, element, status)
{
    if(GetVehicleModel(vehicleid) != 0 && element > 0 && element < 3 && status == FULL || status == DAMAGED)
    {
        new tmp[2][2];
        new light[2];
        light[0] = getLight(vehicleid,LEFT_LIGHT);
        light[1] = getLight(vehicleid,RIGHT_LIGHT);

        if(element == LEFT_LIGHT)
            light[0] = status;

        else if(element == RIGHT_LIGHT)
            light[1] = status;

		for(new i = 0; i < 2; i++)
		{
		    if(light[i] == FULL)
		        tmp[i] = "0";

		     else if(light[i] == DAMAGED)
		        tmp[i] = "1";
		}

		new str[5];
		new part[4];
		format(str,sizeof(str),"%s0%s",tmp[1],tmp[0]);
		GetVehicleDamageStatus(vehicleid,part[0],part[1],part[2],part[3]);
		new val = BinToDec(str);
		UpdateVehicleDamageStatus(vehicleid,part[0],part[1],val,part[3]);
    }
}
