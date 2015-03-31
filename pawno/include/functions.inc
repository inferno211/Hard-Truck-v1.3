#include <foreach>
#include <a_mysql>
native WP_Hash(buffer[], len, const str[]);
stock GetPlayerByIp(ip[])
{
	new pip[32];
	foreach(Player, i)
	{
	    GetPlayerIp(i, pip, sizeof(pip));
	    if(!strcmp(ip, pip, true)) return i;
	}
	return -1;
}
stock PlayerName(playerid)
{
	new pname[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pname, sizeof(pname));
	return pname;
}
stock FormatTime(secs=0)
{
	new timestr[12], hours=0, mins=0;
	while(secs>=60)
	{
	    mins++;
	    secs -= 60;
	}
	while(mins>=60)
	{
	    hours++;
	    mins -= 60;
	}
	if(hours>0) {
		if(hours<10) format(timestr, sizeof(timestr), "0%d:", hours);
		else format(timestr, sizeof(timestr), "%d:", hours);
	}
	if(mins<10) format(timestr, sizeof(timestr), "%s0%d:", timestr, mins);
	else format(timestr, sizeof(timestr), "%s%d:", timestr, mins);
	if(secs<10) format(timestr, sizeof(timestr), "%s0%d", timestr, secs);
	else format(timestr, sizeof(timestr), "%s%d", timestr, secs);
	return timestr;
}
stock SCM(playerid, message[])
{
	new str[128];
	format(str, 128, "%s", message);
	SendClientMessage(playerid, (0x888888AA+(random(0x99)*1000000)+(random(0x99)*10000)+(random(0x99)*100)), str);
	return 1;
}

stock SCMA(message[])
{
	for(new playerid=0; playerid<MAX_PLAYERS; playerid++)
	{
		if(IsPlayerConnected(playerid))
		{
			new str[128];
			format(str, 128, "%s", message);
			SendClientMessage(playerid, (0x666666AA+(random(0x99)*1000000)+(random(0x99)*10000)+(random(0x99)*100)), str);
		}
	}
	return 1;
}
stock SendMessageToAdmins(color, message[])
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
	    if(GetPVarInt(i, "adminlvl")>0) SendClientMessage(i, color, message);
	}
	return 1;
}
stock sql_connect()
{
	new conn;
	if(!(conn = mysql_connect(SQL_HOST, SQL_USER, SQL_DB, SQL_PASS)))
    {
        print("SQL connection attempt 1 FAILED!");
        if(!(conn = mysql_connect(SQL_HOST, SQL_USER, SQL_DB, SQL_PASS)))
        {
            print("SQL connection attempt 2 FAILED!");
            if(!(conn = mysql_connect(SQL_HOST, SQL_USER, SQL_DB, SQL_PASS)))
            {
                print("SQL connection attempt 3 FAILED!");
				print("Serwer nie mo¿e pod³¹czyæ siê do bazy danych");
				return 0;
            }
        }
    }
	SetPVarInt(-1, "mysql_connection", conn);
	print("Serwer po³¹czy³ siê z MySQL");
	return 1;
}

stock sql_close()
{
	new conn;
	for(conn=0; conn<5; conn++)
	{
		mysql_close(conn);
	}
	print("Serwer zakoñczy³ wszystkie po³¹czenia z MySQL!");
}
stock mysql_get_int(field[])
{
	new str[19];
	mysql_get_field(field, str);
	return strval(str);
}
stock sql_add_col(table[], value[], type[])
{
	new query[128];
	format(query, sizeof(query),"ALTER TABLE %s ADD COLUMN %s %s", table, value, type);
	mysql_query(query);
	mysql_free_result();
}
stock sql_build()
{
	new query[128];
	format(query, sizeof(query),\
	"\
		CREATE TABLE dm_users\
		(\
			ID int NOT NULL AUTO_INCREMENT,\
			PRIMARY KEY(ID)\
		)\
	");
	mysql_query(query);
	mysql_free_result();
	sql_add_col("dm_users", "username", "varchar(24)");
	sql_add_col("dm_users", "banned", "int");
	sql_add_col("dm_users", "password", "varchar(129)");
	sql_add_col("dm_users", "ip", "varchar(32)");
	sql_add_col("dm_users", "adminlvl", "int");
	sql_add_col("dm_users", "score", "int");
	sql_add_col("dm_users", "played", "int");
	sql_add_col("dm_users", "registered", "varchar(32)");
	sql_add_col("dm_users", "lastonline", "varchar(32)");
	sql_add_col("dm_users", "kills", "int");
	sql_add_col("dm_users", "deaths", "int");
	sql_add_col("dm_users", "banreason", "varchar(128)");
	sql_add_col("dm_users", "banadmin", "varchar(24)");
	sql_add_col("dm_users", "bantime", "varchar(32)");
	sql_add_col("dm_users", "bandate", "varchar(32)");
	print("MySQL tabled succesfully built & updated!");
}