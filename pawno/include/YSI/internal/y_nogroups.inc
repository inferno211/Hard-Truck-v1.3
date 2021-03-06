/*----------------------------------------------------------------------------*-
					=======================================
					 y_groups - Player group abstractions! 
					=======================================
Description:
	Admin levels, gangs, teams etc - they're all "groups" of people, this
	provides an abstraction for all of these collections.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the SA:MP script information include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk
	
	Thanks:
		Peter, Cam - Support.
		ZeeX - Very productive conversations.
		koolk - IsPlayerinAreaEx code.
		TheAlpha - Danish translation.
		breadfish - German translation.
		Fireburn - Dutch translation.
		yom - French translation.
		50p - Polish translation.
		Zamaroht - Spanish translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN.
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
Version:
	1.0
Changelog:
	29/11/10:
		First version
-*----------------------------------------------------------------------------*/

// This file defines functions which are called if the group system is not used.

static stock _Groups_DefineStates_() <YSI_has_groups:n>
{
}

static stock _Groups_DefineStates_() <YSI_has_groups:y>
{
}

/*stock _@Group_Sink(e)
{
	#pragma unused e
}*/

// Now you can use the default fallback to define functions:
//  
//  stock Class_InitialiseFromGroups() <YSI_has_groups:n>
//  {
//      // Enable the class for all players.
//  }
//  
//  stock Class_InitialiseFromGroups() <>
//  {
//      // Enable the class for all players.
//  }
//  

#define _GROUP_LOCAL_NAME               e
#define _GROUP_INITIALISE               _GROUP_MAKE_NAME<..._InitialiseFromGroups>
//#define __GROUP_INITIALISE              _GROUP_MAKE_NAME<_..._InitialiseFromGroups>

#define Group:

// Dummy values.
#define _GROUP_MAKE_NAME<%0...%1>       %0_%1
#define _GROUP_MAKE_LIMIT               0

#define GROUP_GLOBAL                    (Group:-1)
#define GROUP_MASK                      (Group:0x80000000)
#define GROUP_FIX(%0)                   ((%0)&=~GROUP_MASK)

#define NO_GROUPS(%0) if(!_GROUP_INITIALISE(%0))
