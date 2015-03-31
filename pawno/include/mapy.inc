stock isValidMap(mapid) {
	new TotalMaps = 3; // Set the total amount of maps here
	for(new i=0;i<TotalMaps+1;i++) {
		if(mapid==i) return 1;
	}
	return 0;
}

stock CreateMap(mapid)
{
	#define MAX_DISTANCE_BOUNDARY 600.0
	if(mapid==0)
	{
	
	}

	if(mapid==1)
	{

	}
	return 1;
}