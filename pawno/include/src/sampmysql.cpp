/**************************************************************************/
/*                                                                        */
/* SAMP-MySQL v0.14 plugin                                                */
/*                                                                        */
/* Coded by  ADreNaLINe-DJ                                                */
/* Contact: adrenalinedj@msn.com                                          */
/*                                                                        */
/*                                                                        */
/* This program is free software; you can redistribute it and/or modify   */
/*  it under the terms of the GNU General Public License as published by  */
/*  the Free Software Foundation; either version 3 of the License, or     */
/*  (at your option) any later version.                                   */
/*   This program is distributed in the hope that it will be useful,      */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/*  GNU General Public License for more details.                          */
/*                                                                        */
/*  You should have received a copy of the GNU General Public License     */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*                                                                        */
/**************************************************************************/

#include "SDK/plugin.h"
#if defined WIN32
  //include this before mysql.h because it depends on socket types
  #include <winsock.h>
#endif
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

typedef void (*logprintf_t)(char* format, ...);

logprintf_t logprintf;
void **ppPluginData;
extern void *pAMXFunctions;

//Some declaration functions
static char *pcCreateAndFillStringFromCell(AMX *amx,cell params);
int set_amxstring(AMX *amx,cell amx_addr, char *source,int max);

//Declaration of a "associative array"
struct assoc_array
{
	MYSQL_FIELD *fields;
	MYSQL_ROW row;
	int num_fields;
};
typedef struct assoc_array assoc_array;

//Global variables
MYSQL connexion;
MYSQL_RES *result;
char *stringtosplit;
assoc_array assoc_row;


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData )
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("\n/************************************************/\n/* SAMP-MySQL v0.14 Plugin loaded successfully ! */\n/************************************************/\n");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	logprintf("\n/**************************************************/\n/* SAMP-MySQL v0.14 Plugin unloaded successfully ! */\n/**************************************************/\n");
}

/*********************************************/
/* Initialisation and connection to database */
/*********************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_connect( AMX* amx, cell* params )
{
	const char* serveur_port;
	char* serveur;
	const char* port_s;
	const char* user;
	const char* password;
	int port_i;
	MYSQL* retval;
	serveur_port=pcCreateAndFillStringFromCell(amx, params[1]);
	user=pcCreateAndFillStringFromCell(amx, params[2]);
	password=pcCreateAndFillStringFromCell(amx, params[3]);
	mysql_init(&connexion);
	
	serveur=strtok((char*)serveur_port, ":");
	port_s=strtok(NULL, ":");
	if(port_s!=NULL)
	{
		port_i=atoi(port_s);
	}
	else
	{
		port_i=0;
	}
		
	retval=mysql_real_connect(&connexion, serveur, user, password, 0, port_i, 0, 0);
	if(retval)
	{
		logprintf("\nConnection to MySQL database: Successfull !");
		return 1;
	}
	else
	{
		logprintf("\nConnection to MySQL database: Failed !");
		logprintf("%s",mysql_error(&connexion));
		return 0;
	}
}

/***********************/
/* Select the database */
/***********************/
static cell AMX_NATIVE_CALL n_samp_mysql_select_db( AMX* amx, cell* params )
{
	int retval;
	const char *db;
	db=pcCreateAndFillStringFromCell(amx, params[1]);
	retval=mysql_select_db(&connexion, db); //mysql_select_db returns 0 if success
	if(!retval)
	{
		return 1;
	}
	else
	{
		logprintf("Error in mysql_select_db: %s",mysql_error(&connexion));
		return 0;
	}
}

/****************************************************/
/* Execute a query (connection must be initialized) */
/****************************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_query( AMX* amx, cell* params )
{
    if(result)
	{
		mysql_free_result(result);
		result=NULL;
	}
	int retval;
	const char *query;
	query=pcCreateAndFillStringFromCell(amx, params[1]);
	retval=mysql_query(&connexion, query); //mysql_query returns 0 if success
	if(!retval)
	{
		return 1;
	}
	else
	{
		logprintf("Error in mysql_query: %s",mysql_error(&connexion));
		return 0;
	}
}

/******************************************************/
/* Prepare the result (query must be executed before) */
/******************************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_store_result( AMX* amx, cell* params )
{
	result=mysql_store_result(&connexion);
	if(result!=0)
	{
		return 1;
	}
	else
	{
		logprintf("Error in mysql_store_result: %s",mysql_error(&connexion));
		return 0;
	}
}

/******************************************************************/
/* Return a line of result (store_result must be executed before) */
/******************************************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_fetch_row( AMX* amx, cell* params )
{
	MYSQL_ROW rowtoreturn;
	int num_fields;
	unsigned long *lengths;
	int i, stringsize, len;
	char *stringtoreturn;

	if(assoc_row.row!=NULL)
	{
		assoc_row.num_fields=0;
		assoc_row.row=NULL;
		assoc_row.fields=NULL;
	}

	assoc_row.num_fields=mysql_num_fields(result);
	assoc_row.row=mysql_fetch_row(result);
	assoc_row.fields=mysql_fetch_fields(result);
	lengths=mysql_fetch_lengths(result);
	if(assoc_row.row!=NULL)
	{
		stringsize=0;
		for(i=0;i<assoc_row.num_fields;i++)
		{
			stringsize=stringsize+lengths[i];
		}
		stringsize=stringsize+assoc_row.num_fields+1;
		stringtoreturn=(char*)malloc(stringsize);
		stringtoreturn[0]='\0';
		for(i=0;i<assoc_row.num_fields;i++)
		{
			if(assoc_row.row[i]==NULL) //if the field is set to NULL value
			{
				strcat(stringtoreturn, "NULL");
			}
			else
			{
				if(lengths[i]>0) //if field value is not empty
				{
					strcat(stringtoreturn, assoc_row.row[i]);
				}
				//if field is empty nothing is append to string
			}
			if(i!=assoc_row.num_fields-1)
			{
				strcat(stringtoreturn, "|");
			}
		}
    		len=strlen(stringtoreturn);
		set_amxstring(amx, params[1], stringtoreturn, len);
		free(stringtoreturn);
		return 1;
	}
	else
	{
		//mysql_free_result(result);
		return 0;
	}
}

/**********************************************************************************/
/* Return the number of rows in the result (store_result must be executed before) */
/**********************************************************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_get_field( AMX* amx, cell* params )
{
	const char* field_name;
	char *stringtoreturn;
	int i;
	
	field_name=pcCreateAndFillStringFromCell(amx, params[1]);
	
	for(i=0;i<assoc_row.num_fields;i++)
	{
		if(!strcmp(field_name, assoc_row.fields[i].name))
		{
			if(assoc_row.row[i]!=NULL)
			{
				stringtoreturn=(char*)malloc(strlen(assoc_row.row[i])+1);
				strcpy(stringtoreturn, assoc_row.row[i]);
			}
			else
			{
				stringtoreturn=(char*)malloc(5);
				strcpy(stringtoreturn, "NULL");
			}
			break;
		}
	}
	if(stringtoreturn!=NULL)
	{
		set_amxstring(amx, params[2], stringtoreturn, strlen(stringtoreturn));
		return 1;
	}
	else
	{
		sprintf(stringtoreturn, "Nothing found for field: %s\n", field_name);
		set_amxstring(amx, params[2], stringtoreturn, strlen(stringtoreturn));
		return 0;
	}
}

/**********************************************************************************/
/* Return the number of rows in the result (store_result must be executed before) */
/**********************************************************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_num_rows( AMX* amx, cell* params )
{
	int retval;
	retval=mysql_num_rows(result);
	return retval;
}

/************************************************************************************/
/* Return the number of fields in the result (store_result must be executed before) */
/************************************************************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_num_fields( AMX* amx, cell* params )
{
	int retval;
	retval=mysql_num_fields(result);
	return retval;
}

/**********************************************************************/
/* Check connection to MySQL server and try a re-connection if needed */
/**********************************************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_ping( AMX* amx, cell* params )
{
	int retval;
	retval=mysql_ping(&connexion);
	switch(retval)
	{
		case 0:
			return 0;
		case 2006:   //CR_SERVER_GONE_ERROR
			return 1;
		case 2000:   //CR_UNKNOWN_ERROR
			return 1;
		default:
			return 1;
	}
}

/*****************************************/
/* Prepare string by escaping characters */
/*****************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_real_escape_string( AMX* amx, cell* params )
{
	int len, retval;
	const char *src;
	char *dest;
	
	src=pcCreateAndFillStringFromCell(amx, params[1]);
	dest=(char*)malloc(strlen(src)*2+1);
	retval=mysql_real_escape_string(&connexion, dest, src, strlen(src));
	len=strlen(dest);
	set_amxstring(amx, params[2], dest, len);
	free(dest);
	return retval;
}

/********************************************/
/* Free allocated memory for a query result */
/********************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_free_result( AMX* amx, cell* params )
{
	mysql_free_result(result);
	return 1;
}

/******************************************/
/* Splitting function to parse row result */
/******************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_strtok( AMX* amx, cell* params )
{
	char *src;
	char *separator;
	char *dest;
	int len;
	
	separator=pcCreateAndFillStringFromCell(amx, params[2]);
	src=pcCreateAndFillStringFromCell(amx, params[3]);
	if(strlen(src)!=0)
	{
		stringtosplit=src;
		dest=strtok(stringtosplit, separator);
	}
	else
	{
		dest=strtok(NULL, separator);
	}
	if(dest!=NULL)
	{
		len=strlen(dest);
		set_amxstring(amx, params[1], dest, len);
		return 1;
	}
	else
	{
		return 0;
	}
}

/************************************/
/* Close the connection to database */
/************************************/
static cell AMX_NATIVE_CALL n_samp_mysql_close( AMX* amx, cell* params )
{
  mysql_close(&connexion);
	return 1;
}

AMX_NATIVE_INFO SAMPMySQLNatives[ ] =
{
	{ "samp_mysql_connect",			n_samp_mysql_connect },
	{ "samp_mysql_select_db",			n_samp_mysql_select_db },
	{ "samp_mysql_query",			n_samp_mysql_query },
	{ "samp_mysql_store_result",			n_samp_mysql_store_result },
	{ "samp_mysql_fetch_row",			n_samp_mysql_fetch_row },
	{ "samp_mysql_get_field",			n_samp_mysql_get_field },
	{ "samp_mysql_num_rows",			n_samp_mysql_num_rows },
	{ "samp_mysql_num_fields",			n_samp_mysql_num_fields },
	{ "samp_mysql_ping",			n_samp_mysql_ping },
	{ "samp_mysql_real_escape_string",			n_samp_mysql_real_escape_string },
	{ "samp_mysql_free_result",			n_samp_mysql_free_result },
	{ "samp_mysql_strtok",			n_samp_mysql_strtok },
	{ "samp_mysql_close",			n_samp_mysql_close },
	{ 0,					0 }
};


PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx )
{
	return amx_Register( amx, SAMPMySQLNatives, -1 );
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx )
{
	return AMX_ERR_NONE;
}

/***********************************************/
/* Function returns string from a "cell" param */
/***********************************************/
static char *pcCreateAndFillStringFromCell(AMX *amx,cell params)
{
	char *szDest;
	int nLen;
	cell *pString;
	amx_GetAddr(amx,params,&pString);
	amx_StrLen(pString, &nLen);
	szDest = new char[nLen+1];
	amx_GetString(szDest, pString, 0, UNLIMITED);
	return szDest;
}

/********************************************/
/* Function that set a string in the params */
/* Very useful for functions like           */
/* mysql_fetch_row                          */
/*                                          */
/* function provided by Static              */
/********************************************/
int set_amxstring(AMX *amx,cell amx_addr, char *source,int max)
{
	cell* dest = (cell *)(amx->base + (int)(((AMX_HEADER *)amx->base)->dat + amx_addr));
	cell* start = dest;
	while (max--&&*source)
	*dest++=(cell)*source++;
	*dest = 0;
	return dest-start;
}
