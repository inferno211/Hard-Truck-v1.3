// 	[MiscFunctions.inc]
//  [Pawn Library Include]
// 	
// 	© João Pedro Lopes, All right's reserved

/* natives
   native strtok(str[], &idx); // Simple STR tok, used to separate commands in OnPlayerCommand
*/

// Avoding this library to be included more then once
#if defined _MISC_FUNCTIONS
	#endinput
#endif

// Defining the library
#define _MISC_FUNCTIONS
#pragma library MiscFunctions

//----------------------------------------------------------------------------------------------------------

// Simple STR tok, used to separate commands in OnPlayerCommand
stock strtok(str[], &idx){
	new result[256];
	new rIdx;
	
	while(str[idx] != ' ' && idx < strlen(str)){
		result[rIdx] = str[idx];
		idx++;
		rIdx++;
	}
	
	idx++;
	return result;
}
