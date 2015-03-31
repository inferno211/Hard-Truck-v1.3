#include <pDefinitions>

stock getTire(vehicleid, element)
{
	if(GetVehicleModel(vehicleid) != 0 &&  element > 0 &&  element < 5)
	{
	    new str[15];
	    new part[4];
	    new strtemp[15];
	    new status;
	    new length;
	    GetVehicleDamageStatus(vehicleid,part[0],part[1],part[2],part[3]);
	    format(str,sizeof(str),"%b",part[3]);
	    strcat(strtemp,str);
	    length = strlen(str);
		if(length != 4)
	 	{
	 	    length = 4 - length;
	 	    new length2 = 4 - length;
 	    	for(new i = 0; i < length; i++)
 	    	{
	 	        str[i] = '0';
	 	       	strdel(str,length,length2);
	 	    }
	 	    strins(str,strtemp,length);
	 	    
	   	 	for(new i = 0; i < 4; i++)
	    	{
	       		if(i + 1 == element)
				{
			 		GetChar(i,str); //Begin
					if(strcmp(str,"1",true) == 0)
				   		status = DAMAGED;

					else if(strcmp(str,"0",true) == 0)
				   		status = FULL;
				    
					strdel(str,0,5);
					strcat(str,strtemp); //End
			    	break;
				}
			}
			return status;
	    }
	    else if(length == 4)
	   	{
	        new strtmp[5];
	        strcat(strtmp,str);
	        for(new i = 0; i < 4; i++)
	       	{
	          	if(i + 1 == element)
	           	{
	            	GetChar(i,str); //Begin
					if(strcmp(str,"1",true) == 0)
				   		status = DAMAGED;

					else if(strcmp(str,"0",true) == 0)
				   		status = FULL;

					strdel(str,0,5);
					strcat(str,strtmp); //End
			   		break;
			   	}
	       	}
	       	return status;
	   	}
	}
	return -1;
}

stock setTire(vehicleid, element, status)
{
	if(GetVehicleModel(vehicleid) != 0 && element > 0 && element < 5)
	{
	    new tmp[4][20];
	    new tire[4];
	    tire[0] = getTire(vehicleid,LEFT_F_TIRE);
	    tire[1] = getTire(vehicleid,LEFT_B_TIRE);
		tire[2] = getTire(vehicleid,RIGHT_F_TIRE);
		tire[3] = getTire(vehicleid,RIGHT_B_TIRE);
		
		if(element == LEFT_F_TIRE)
			tire[0] = status;

		else if(element == LEFT_B_TIRE)
		    tire[1] = status;
		    
		else if(element == RIGHT_F_TIRE)
		    tire[2] = status;
		    
		else if(element == RIGHT_B_TIRE)
		    tire[3] = status;
		    
		for(new i = 0; i < 4; i++)
		{
			if(tire[i] == FULL)
			    tmp[i] = "0";
			    
			else if(tire[i] == DAMAGED)
			    tmp[i] = "1";
		}
		new str[5];
		new part[4];
		GetVehicleDamageStatus(vehicleid,part[0],part[1],part[2],part[3]);
		format(str,sizeof(str),"%s%s%s%s",tmp[0],tmp[1],tmp[2],tmp[3]);
		new val = BinToDec(str);
		UpdateVehicleDamageStatus(vehicleid,part[0],part[1],part[2],val);
	}
}
