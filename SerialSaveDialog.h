#pragma once
/*
* File: SerialSaveDialog.h
* Description:
*	Creating a dialog to handle collecting information for performing a serial save of images
*   Note that this is an experiment to try this without a class
* Log:
*	20221107: Initial creation
*/

#ifndef SERIALSAVEDIALOG_H
#define SERIALSAVEDIALOG_H
#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <Windowsx.h>
#include <Commdlg.h>
#include <stdlib.h>
#include <shobjidl.h>		// for SaveFile Dialog box
#include "resource.h"
extern char SSD_czFilePrefix[80];
extern char SSD_czFrameCount[80];
extern char SSD_czEndRainCount[80];
extern char SSD_czDirectory[80];
BOOL CALLBACK SerialSaveDialogProcInput(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);


bool SSD_DialogBox(HINSTANCE hAppInst, HWND hWndParent);
bool SSD_GetFolderSaveName(HWND hWndParent, char* pFolderPath, int iPathBufferSize);


#endif