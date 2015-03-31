strreplace(target[], newstr[], source[]){
	new tmp[256];
	ustaw(tmp, source);
	new pos = strfind(tmp, target, false, 0);
	while(pos !=-1){
		tmp = strdelete(pos, strlen(target), tmp);
		strinject(tmp, pos, newstr);
		pos = strfind(tmp, target, false, pos);
 	}
	return tmp;
}

strdelete(pos, lenght, source[]){
	new tmp[256];
	new g=0;
	for(g=0;g<pos;g++)tmp[g] = source[g];
	for(g=pos;g<strlen(source)-lenght;g++)tmp[g] = source[g+lenght];
	tmp[g] = '\0';
	return tmp;
}

ustaw(str1[], str2[])for(new g=0;g<strlen(str2);g++)str1[g] = str2[g];

strinject(source[], adress, injection[]){// By Luby
	new temp[256];
	ustaw(temp, source);
	new g=adress;
	while(g<strlen(injection)+adress){
		temp[g]=injection[g-adress];
		g++;
	}
	g=adress+strlen(injection);
	while(g<strlen(source)+strlen(injection)){
		temp[g]=source[g-strlen(injection)];
		g++;
	}
	ustaw(source, temp);
	return temp;
}

forward OnProcessFile(file[], function[], args[][]);
forward OnProcessInit(file[]);
forward OnProcessEnd(file[], vehs, objs, picks);
