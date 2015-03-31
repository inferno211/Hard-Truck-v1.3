#include <a_samp>
/*
		ROUTER PLUGIN
		- GPS ADDITION TO SA-MP
		- Made By Gamer_Z a.k.a. grasmanek94 , Rafal Grasman

		October-


		contact: grasmanek94@live.nl

		http://gamer-gps.googlecode.com/
*/

#if defined ROUTE_CONNECTOR_PLUGIN_INCLUDED

#else

#define MAX_NODES					(32768)
#define MAX_CONNECTIONS				(5)

#define CONNECT_TYPE_BOTH			(0)
#define CONNECT_TYPE_One_To_Two		(1)

#define INCLUDE_VERSION				(167)

#define ROUTE_CONNECTOR_PLUGIN_INCLUDED
#pragma library "RouteConnectorPlugin"

native AddNode(Float:X,Float:Y,Float:Z,AddToPathFinder = 0);
/*
	Function: 
		AddNode
	Description: 
		Adds a node into the memory of the plugin,
		This node will be unavailable in route calculations.
	Parameters: 
		Position as X Y Z
		AddToPathFinder - if set to 1 it will also make sure the graph will be updated so when searching for a route it will be added to the list.
	Returns the added nodeID, -1 if failed.
	Note:
		NEVER EVER set AddToPathFinder to 1 when a calculation is in progress! THAT IS YOUR OWN RESPOSIBILITY IF IT HAPPENS.
*/
native AddNodeEx(ID,Float:X,Float:Y,Float:Z,AddToPathFinder = 0);
/*
	Function: 
		AddNodeEx
	Description: 
		The only difference with AddNode is that you can specify your own NodeID here.
		Gaps may now be present.
	Parameters: 
		ID as Custom NodeID
		Position as X Y Z
		AddToPathFinder - if set to 1 it will also make sure the graph will be updated so when searching for a route it will be added to the list.
	Returns the added nodeID, -1 if failed.
	Note:
		NEVER EVER set AddToPathFinder to 1 when a calculation is in progress! THAT IS YOUR OWN RESPOSIBILITY IF IT HAPPENS.
*/
native ConnectNodes(NodeID_one,NodeID_two,AddToPathFinder = 0,direction = 0);
/*
	Function: 
		ConnectNodes
	Description: 
		This will connect two nodes stored in memory, same rules as for AddNode(Ex), it won't be available in path calculations.
		When you connect NodeID_one with NodeID_two it will automaticly connect the opposite, no distance suplying is needed as the XYZ are supplied at node creation.
	Parameters: 
		NodeID_one and NodeID_two as NodeID's
		AddToPathFinder - if set to 1 it will also make sure the graph will be updated so when searching for a route it will be added to the list.
		direction - you can choose to only connect nodeID one with nodeID two (One_To_Two = 1) or to connect them together (BOTH = 0)
	Returns:
		-1 - NodeOne is out of boundaries
		-2 - NodeTwo is out of boundaries
		-3 - NodeOne equals NodeTwo
		-4 - NodeOne doesn't exist
		-5 - NodeTwo doesn't exist
		-6 - NodeOne already connected with NodeTwo
		-7 - NodeTwo already connected with NodeOne
		-8 - No more connection slots left or direction does not equal 1 or 0
		Anything above or equal to 0 means success (the NodeOne[connectid] is retuned).
	Note:
		NEVER EVER set AddToPathFinder to 1 when a calculation is in progress! THAT IS YOUR OWN RESPOSIBILITY IF IT HAPPENS.
*/
native NearestPlayerNode(playerid,Float:MaxDist=9999.99,IgnoreNodeID=(-1));
/*
	Function: 
		NearestPlayerNode
	Description: 
		This function will get the closest player node, if you used AddNode(Ex) this nodes will also be considered.
	Parameters: 
		playerid - the playerid to count from
		MaxDist - the maximal distance to search from the player
		IgnoreNodeID - this node ID will not be returned as the closest one, it will be ignored in the search.
	Returns the closest nodeID, -1 if no node Id is found in range
*/
native NearestNodeFromPoint(Float:X,Float:Y,Float:Z,Float:MaxDist=9999.99,IgnoreNodeID=(-1));
/*
	Function: 
		NearestNodeFromPoint
	Description: 
		Same as NearestPlayerNode, but here you can supply an point instead of an playerid
	Parameters: 
		XYZ - the position of the point to search from
		MaxDist - the maximal distance to search from the player
		IgnoreNodeID - this node ID will not be returned as the closest one, it will be ignored in the search.
	Returns the closest nodeID, -1 if no node Id is found in range
*/
native WriteNodesToFile(filename[]);
/*
	Function: 
		WriteNodesToFile
	Description: 
		Write all nodes, connections, contents of the memory into an loadable file,
		can be used by ReadNodesFromFile later.
	Parameters: 
		filename -	the "path/filename.extension" to store the information in,
					note that if you want to make a file in the scriptfiles folder you need to supply:
					WriteNodesToFile("scriptfiles/your.file.name");
	Returns 1 on success, 0 on failure.
*/
native ReadNodesFromFile(filename[]);
/*
	Function: 
		ReadNodesFromFile
	Description: 
		Read all nodes, connections, contents of the file into the memory,
		This function will automaticly create nodes, connect them, create the virtual graph to search paths on
		after it has been loaded into the memory.
	Parameters: 
		filename -	the "path/filename.extension" to read the information from,
					note that if you want to read a file in the scriptfiles folder you need to supply:
					ReadNodesFromFile("scriptfiles/your.file.name");
	Warning:
		It is not recommended to use this funcion, use at your own risk.
		The plugin calls this function only at server startup, however I have included it for you.
		You still can make aditional nodes with it (if you analyse the project source code correctly, you will know what I mean)
	Returns 1 on success, 0 on failure.
*/
native GetNodePos(NodeID,&Float:X,&Float:Y,&Float:Z);
/*
	Function: 
		GetNodePos
	Description: 
		Get the XYZ position of the supplied NodeID
	Parameters: 
		NodeID - The NodeID to get the XYZ from
		(returns) X Y Z - The XYZ positions.
	Returns 0 on failure (Out Of Range?), -1 if node doesn't exist, 1 on success.
*/
native CalculatePath(Start,End,routeID = 0);//Threaded calculating, everything done here will be added to an Queue
/*
	Function: 
		CalculatePath
	Description: 
		Get the XYZ position of the supplied NodeID
	Parameters: 
		Start - The start NodeID
		End - the destination NodeID
		routeID (optional) - [custom integer supply] Here you can specify an integer value that will be passed 
		to the callback, along with the calculated path information, for example the PlayerID.
	Note:
		if you will be using the routeID parameter for recognizing routes, make sure they all are unique,
		once started route search cannot be aborted and will just be queued and the callback will still be called.

		This function is Threaded, this means that if the CalculatePath search takes 3 seconds, it won't lagg your server.
		Your server will continue to work normally.

		Only the callback in the script which calls the plugin will get executed with this, if you do CalculatePath in Script1, 
		and have your callback in Script2 then it won't get executed

		Returns always 1.
*/
native IsNodeIntersection(NodeID);
/*
	Function: 
		IsNodeIntersection
	Description: 
		Check if a node has 3 or more connections
	Parameters: 
		NodeID - The ID of the node
	Return 1 if true, 0 if false, -1 if node doesn't exist.
*/
native Float:GetAngleBetweenNodes(NodeID_one,NodeID_middle_aka_two,NodeID_three);
/*
	Function: 
		GetAngleBetweenNodes (Returns Float)
	Description: 
		Gets the angle between 3 nodes (2 connections/lines).
	Parameters: 
		NodeID* - The ID of the node
	Return 0.0 if one of the three nodes doesn't exist
*/
native GetConnectedNodes(NodeID);
/*
	Function: 
		GetConnectedNodes
	Description: 
		returns the amount of other nodes that are connected to this node, max is 5
	Parameters: 
		NodeID* - The ID of the node
	Returns amount of nodes connected (0 to 5), on failure -1.
*/
native GetNextEmptyNodeID();
/*
	Function: 
		GetNextEmptyNodeID
	Description: 
		returns the closest empty node ID (closest starting from 0 to up);
	Note:
		Example: 

				 new id = GetNextEmptyNodeID();
				 if(id != -1)AddNodeEx(id,X,Y,Z); 

				 However this example results in:

				 AddNode(X,Y,Z);
		Returns -1 if no more available node slots.
*/
native GetQueueSize();
/*
	Function: 
		GetQueueSize
	Description: 
		gets the size of all queued path calculations to do.
	Returns -1 if the vector was locked when tried to access (Threading crash prevention), else it returns the vector size.
*/
native GetConnectedNodeID(NodeID,ConnectID);
/*
	Function: 
		GetConnectedNodeID
	Description: 
		gets the ID of an connection to NodeID, -1 if ConnectID has no connection, connectid must be between 0 and (MAX_CONNECTIONS-1), however there is OFB prevention check.
*/
native Float:GetConnectedNodeDistance(NodeID,ConnectID);
/*
	Function: 
		GetConnectedNodeDistance (Returns Float)
	Description: 
		gets the distance to a connected node (ConnectID) from the selected node (NodeID).
*/
native Float:GetDistanceBetweenNodes(NodeID_one,NodeID_two);
/*
	Function: 
		GetDistanceBetweenNodes (Returns Float)
	Description: 
		gets the distance between the two nodes (NOT VIA OTHER NODES, THIS JUST DOES THE X Y Z POSITION CALCULATION).
*/
native IsNodeInPathFinder(NodeID);
/*
	Function: 
		IsNodeInPathFinder
	Description: 
		Checks if NodeID is added to the routecalculator.
	Returns -1 if the NodeID is invalid and 0 if node is not in the route calculator, 1 if yes.
*/
native GetRouteArray(ID,destination[],size = sizeof(destination));
/*
	Function: 
		GetRouteArray
	Description: 
		Stores an saved array with assigned ID to destination[]
	Returns the amount of nodes in array at ID, Returns 0 if array is empty or ID doesn't exist.
*/
native GetRouteAtPos(ID,Array_Pos,&amount_of_nodes=0);
/*
	Function: 
		GetRouteAtPos
	Description: 
		Returns the NodeID in array[Array_Pos] at ID.
		Optionally you can specify an variable to store the amount of nodes in it.
*/
native StoreRouteArray(amount_of_nodes,array[]);
/*
	Function: 
		StoreRouteArray
	Description: 
		Stores an array to the plugins vector memory, returns the ID you can use in GetRouteArray or DeleteArray.
*/
native DeleteArray(ID);
/*
	Function: 
		DeleteArray
	Description: 
		Remove contents of the memory at ID.
*/
native AddExistingNodeToPathFinder(NodeID);
/*
	Function: 
		AddExistingNodeToPathFinder
	Description: 
		Adds an created node to the routecalculator.
	Returns -1 if the NodeID is invalid and 0 if node id does not exist or is already added, 1 on success.
*/
native RemoveNode(NodeID);
/*
	Function: 
		RemoveNode
	Description: 
		Deletes an node from the memory, to use in Write data, nodes loaded into the calculator won't be deleted, connections too.
	Returns -1 if the NodeID is invalid and 0 if node id does not exist, 1 on success.
*/
native DisconnectNodeFromNode(NodeIDOne,NodeIDTwo);
/*
	Function: 
		DisconnectNodeFromNode
	Description: 
		Disconnects Node ID One from Two, please see RemoveNode for information about the calculator memory.
	Returns -1 if the NodeID is invalid and 0 if node id does not exist, 1 on success.
*/
native DisconnectAllFromNode(NodeID);
/*
	Function: 
		DisconnectAllFromNode
	Description: 
		Disconnects all other nodes from NodeID, and NodeID from them.
	Returns -1 if the NodeID is invalid and 0 if node id does not exist, 1 on success.
*/
native DeleteNodeSystemAtNode(NodeID,array[],size = sizeof(array));
/*
	Function: 
		DeleteNodeSystemAtNode
	Description: 
		Get ALL nodeIDs that are CONNECTED IN ANY WAY, ALSO VIA OTHER NODES to NodeID into the array[].
		Usefull for deleting big-not-connected chunks of nodes.
	Returns 0 on failure, the array size on success.
*/
native GetNodeDirectionToConnect(NodeID,ConnectID);
/*
	Function: 
		GetNodeDirectionToConnect
	Description: 
		Get the direction this node[connectid] is connected in, 
		0 means that :
			connectid is connected to nodeid
			nodeid is connected to connectid
		1 means that:
			nodeid is connected to connectid
			connectid is NOT connected to nodeid
		2 means that:
			nodeid is NOT connected to connectid
			connectid is connected to nodeid
	Note:
		Usefull for making 'left and right' road sides.
	Returns -1 on failure.
*/
native SetNodeDirectionToConnect(NodeID,ConectID,Direction);
/*
	Function: 
		SetNodeDirectionToConnect
	Description: 
		See GetNodeDirectionToConnect, this SETS the direction manually.
		It automaticly get the nodeID of 'ConectID' and sets the connection_direction to the good value.
	Returns 0 on failure, 1 on success.
*/
native NodeExists(NodeID);
/*
	Function: 
		NodeExists
	Description: 
		Checks if the given nodeID exists in the memory.
	Returns 0 if not, 1 if yes, -1 on failure.
*/
native RemoveAllRouteIDFromQueue(routeid);
/*
	Function: 
		RemoveAllRouteIDFromQueue
	Description: 
		Removes all pending calculations with 'routeid' from the queue.
	Returns -1 if the Queue is locked/accessed, else it returns the amount of entries deleted.
*/
forward GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,distance);//Every processed Queue will be called here
/*
	Called when a path finding calculation is done.
	
	routeid - the id you specified for recognition of calls
	node_id_array -	this array is up to 1792 cells long
					it is build from the following information:

					node_id_array[0] ... node_id_array[1791] - 
						all points (Node ID's) on the route
						in following order:
							from start, to end
	amount_of_nodes - this is the amount of nodes the total path is, is set to 0 when it's impossible to calculate the route.
	distance - the total distance all nodes take, rounded to an integer, is -1 if it's impossible to calculate the route.
	so you can do:
	public GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,distance)
	{
		for(new i = 0; i < amount_of_nodes; ++i)
		{
			printf("Point(%d)=NodeID(%d)",i,node_id_array[i]);
		}
		return 1;
	}
*/
forward OnPlayerClosestNodeIDChange(playerid,old_NodeID,new_NodeID);
/*
	Called when a player's closest nodeID changes.
	
	playerid - the id of the player
	old_NodeID and new_NodeID - the node ID's, old and new.
		new_NodeID is 'now' the closest node ID.

*/
native GetGPSdatVersion();
/*
	Function: 
		GetGPSdatVersion
	Description: 
		Gets the file version of GPS.dat
	Returns -1 if getting the GPS.dat version failed, else it returns the version number, this function is only available since package 162
*/
native GetPluginVersion();
/*
	Function: 
		GetPluginVersion
	Description: 
		Gets the plugin version
	Returns the plugin version, this function is only available since package 162
*/
stock GetIncludeVersion()
{
	return INCLUDE_VERSION;
}
/*
	Function: 
		GetIncludeVersion
	Description: 
		Gets the include file version
	Returns the inclde file version, this function is only available since package 162
*/

#include <a_http>
forward private_GPS_VersionCheck();
public  private_GPS_VersionCheck()
{
	HTTP(0, HTTP_GET, "gamer-gps.googlecode.com/svn/wiki/version.wiki", "", "private_GPS_VC_response");
	return 1;
}

forward private_GPS_VC_response(index, response_code, data[]);
public private_GPS_VC_response(index, response_code, data[])
{
	new GPS_formatstring[1024];
    if(response_code == 200) //Did the request succeed?
    {
		new GPS_index = 0;
		new PackageVersion = strval(GPS_strtok(data,GPS_index));
		new PluginVersion  = strval(GPS_strtok(data,GPS_index));
		new IncludeVersion = strval(GPS_strtok(data,GPS_index));
		new GPSdatversion  = strval(GPS_strtok(data,GPS_index));
		new bool:GPS_update[3] = {false,false,false};

		format(GPS_formatstring,1024,"\r\n\
		\t----------------------------------------------------------\r\n\r\n\
		\tGPS PLUGIN REPORT:\r\n\t\tUpdate report:\r\n\r\n\
		\t\t\tNewest Package version: %d\r\n\r\n\t\t\tNewest Plugin Version: %d\r\n\t\t\tCurrent Plugin Version: %d\r\n\t\t\t(",PackageVersion,PluginVersion,GetPluginVersion());

		if(GetPluginVersion() == PluginVersion)
		{
			format(GPS_formatstring,1024,"%sYour current plugin is UP-TO-DATE)\r\n\r\n\t\t\t",GPS_formatstring);
		}
		else
		{
			format(GPS_formatstring,1024,"%sYour current plugin is OUTDATED)\r\n\r\n\t\t\t",GPS_formatstring);
			GPS_update[0] = true;
		}

		format(GPS_formatstring,1024,"%sNewest Include version: %d\r\n\t\t\tCurrent Include version: %d\r\n\t\t\t(",GPS_formatstring,IncludeVersion,GetIncludeVersion());

		if(GetIncludeVersion() == IncludeVersion)
		{
			format(GPS_formatstring,1024,"%sYour current include is UP-TO-DATE)\r\n\r\n\t\t\t",GPS_formatstring);
		}
		else
		{
			format(GPS_formatstring,1024,"%sYour current include is OUTDATED)\r\n\r\n\t\t\t",GPS_formatstring);
			GPS_update[1] = true;
		}

		format(GPS_formatstring,1024,"%sNewest GPS.dat version: %d\r\n\t\t\tCurrent GPS.dat version: %d\r\n\t\t\t(",GPS_formatstring,GPSdatversion,GetGPSdatVersion());

		if(GetGPSdatVersion() == GPSdatversion)
		{
			format(GPS_formatstring,1024,"%sYour current GPS.dat is UP-TO-DATE)\r\n\r\n",GPS_formatstring);
		}
		else
		{
			format(GPS_formatstring,1024,"%sYour current GPS.dat is OUTDATED)\r\n\r\n",GPS_formatstring);
			GPS_update[2] = true;
		}

		if(GPS_update[0] == false && GPS_update[1] == false && GPS_update[2] == false)
		{
			format(GPS_formatstring,1024,"%s\t\tRequired Actions:\r\n\t\t\tNo actions required, everything is UP-TO-DATE\r\n",GPS_formatstring);
		}
		else
		{
			format(GPS_formatstring,1024,"%s\t\tRequired Actions:\r\n\t\t\t",GPS_formatstring);
			if(GPS_update[0] == true && GPS_update[1] == true && GPS_update[2] == true)
			{
				format(GPS_formatstring,1024,"%s-Update the Whole package (Plugin+Include+GPS.dat)\r\n",GPS_formatstring);
			}
			else
			{
				if(GPS_update[0] == true)
				{
					format(GPS_formatstring,1024,"%s-Update the Plugin\r\n\t\t\t",GPS_formatstring);
				}
				if(GPS_update[1] == true)
				{
					format(GPS_formatstring,1024,"%s-Update the Include\r\n\t\t\t",GPS_formatstring);
				}
				if(GPS_update[2] == true)
				{
					format(GPS_formatstring,1024,"%s-Update the GPS.dat\r\n\t\t\t",GPS_formatstring);
				}
			}
			format(GPS_formatstring,1024,"%s\r\n\t\tThe changelog can be found at:\r\n\t\thttp://gamer-gps.googlecode.com/svn/wiki/changelog.wiki\r\n",GPS_formatstring);
		}
		format(GPS_formatstring,1024,"%s\r\n\
		\t----------------------------------------------------------\r\n\r\n",GPS_formatstring);
    }
    else
    {
    	format(GPS_formatstring,1024,"\r\n\t\
		----------------------------------------------------------\r\n\
		\r\n\tGPS PLUGIN REPORT:\r\n\tCannot check for updates! You have to do it manually going to:\r\n\t\
		http://gamer-gps.googlecode.com/svn/wiki/version.wiki\r\n\t\
		You will see a file with example contents:\r\n\t\
		100.101.102.103\r\n\t\
		100 - the newest package version\r\n\t\
		101 - the newest plugin version\r\n\t\
		102 - the newest include version\r\n\t");
		format(GPS_formatstring,1024,"%s\
		103 - the newest GPS.dat version\r\n\r\n\t\
		Your current versions look like this (package version unavailable):\r\n\t\
		000.%d.%d.%d\r\n\r\n\t\
		Newest download always available from:\r\n\t\
		http://code.google.com/p/gamer-gps/downloads/list\r\n\r\n\
		\t----------------------------------------------------------\r\n",GPS_formatstring,GetPluginVersion(),GetIncludeVersion(),GetGPSdatVersion());
    }
    print(GPS_formatstring);
    return 1;
}

stock GPS_strtok(const string99[], &index,seperator='.')
{
	new length = strlen(string99);
	new offset = index;
	new result[128];
	while ((index < length) && (string99[index] != seperator) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string99[index];
		index++;
	}

	result[index - offset] = EOS;
	if ((index < length) && (string99[index] == seperator))
	{
		index++;
	}
	return result;
}


/* below is the plugin callback support code, you really shouldn't touch this */
native gps_OnGameModeInit();
native gps_OnPlayerConnect(playerid);
native gps_OnPlayerDisconnect(playerid);//YES, no reason needed, duuh!

public OnGameModeInit()
{
	gps_OnGameModeInit();
	return CallLocalFunction("call_gps_OnGameModeInit","");
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit call_gps_OnGameModeInit
forward call_gps_OnGameModeInit();

public OnPlayerConnect(playerid)
{
	gps_OnPlayerConnect(playerid);
	return CallLocalFunction("call_gps_OnPlayerConnect","i",playerid);
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect call_gps_OnPlayerConnect
forward call_gps_OnPlayerConnect(playerid);

public OnPlayerDisconnect(playerid,reason)
{
	gps_OnPlayerDisconnect(playerid);
	return CallLocalFunction("call_gps_OnPlayerDisconnect","ii",playerid,reason);
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect call_gps_OnPlayerDisconnect
forward call_gps_OnPlayerDisconnect(playerid,reason);

#endif
