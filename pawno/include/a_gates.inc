#include <a_samp>

new gatetmp;

#define GATE_STATUS_CLOSED 0
#define GATE_STATUS_OPEN 1
#define IS_NEAR_RANGE 3.00

enum GateConfig
{
	Float:close_X,
	Float:close_Y,
	Float:close_Z,
	Float:open_X,
	Float:open_Y,
	Float:open_Z,
	Status,
}

new Gate[][GateConfig];

stock CreateGate(modelid, Float:close_x, Float:close_y, Float:close_z, Float:open_x, Float:open_y, Float:open_z, Float:rX, Float:rY, Float:rZ)
{
	new gg = gatetmp;
	gatetmp++;
	CreateObject(modelid, close_x, close_y, close_z, rX, rY, rZ);
	Gate[gg][close_X] = close_x;
	Gate[gg][close_Y] = close_y;
	Gate[gg][close_Z] = close_z;
	Gate[gg][open_X] = open_x;
	Gate[gg][open_Y] = open_y;
	Gate[gg][open_Z] = open_z;
	Gate[gg][Status] = GATE_STATUS_CLOSED;
	return gg;
}

stock FunctionGate(gateid, Float:speed)
{
	if(Gate[gateid][Status] == GATE_STATUS_CLOSED)
	{
		OpenGate(gateid, speed);
		Gate[gateid][Status] = GATE_STATUS_OPEN;
	}
	else if(Gate[gateid][Status] == GATE_STATUS_OPEN)
	{
	    CloseGate(gateid, speed);
	    Gate[gateid][Status] = GATE_STATUS_CLOSED;
	}
}

stock OpenGate(gateid, Float:speed)
{
	MoveObject(gateid, Gate[gateid][open_X], Gate[gateid][open_Y], Gate[gateid][open_Z], speed);
}

stock CloseGate(gateid, Float:speed)
{
	MoveObject(gateid,Gate[gateid][close_X], Gate[gateid][close_Y], Gate[gateid][close_Z], speed);
}

stock IsNearGate(playerid, gateid) // returns 0 if no gate is near || returns 1 if gate is near
{
	if(IsPlayerInRangeOfPoint(playerid, IS_NEAR_RANGE, Gate[gateid][close_X], Gate[gateid][close_Y], Gate[gateid][close_Z]))
	{
	    return 1;
	}
	else return 0;
}

/*
native CreateGate(modelid, Float:close_x, Float:close_y, Float:close_z, Float:open_x, Float:open_y, Float:open_z, Float:rX, Float:rY, Float:rZ);
native FunctionGate(gateid, Float:speed);
native OpenGate(gateid, Float:speed);
native CloseGate(gateid, Float:speed);
native IsNearGate(playerid, Float:gateid);
*/
