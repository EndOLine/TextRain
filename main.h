#pragma once
/*
 File: Main.h
 Description:
	Create a Matrix like screen with raining letters.

 project parameters:
	Character Set = Use Multi-byte Character set
*/
// looking for memory leaks
// https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#ifdef _DEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//// allocations to be of _CLIENT_BLOCK type
//#else
//#define DBG_NEW new
//#endif
//
#include <windows.h>
#include "clsApp.h"

clsApp App;
