#pragma once


#ifndef CLSWINDOW_H
#define CLSWINDOW_H

#include "clsHGOWindow.h"
#include <thread>
#include <shobjidl.h>		// for SaveFile Dialog box
#include <iostream>
#include <fstream>
#include <string>
#include "resource.h"
#include "SerialSaveDialog.h"
#include "clsRNG.h"
#include "clsHGOtimer.h"

#define IDM_SAVEAS 9004
#define IDM_EXIT 9009
#define IDM_ABOUT 9100
#define IDM_PAUSE 9101
#define IDM_RESTART 9102
#define IDM_STOP 9103
#define IDM_PROPERTIES 9104
#define IDM_FULLSCREEN 9105
#define IDM_FONT 9106
#define IDM_SERIALSAVE 9107
#define IDM_COPYBACKGROUND 9108
#define IDM_CLEARBACKGROUND 9109

class clsWindow :public clsHGOWindow {
public:
	struct stColour {
		int Red, Green, Blue;
	};
	bool bSizingWindow = false;
	double dZoom = 1.0;
	HDC SwapDC = 0;
	HDC BackGroundDC = 0;
	HBITMAP SwapBM = 0;
	HGDIOBJ OrigObject = 0;
	HFONT hOrigfont=0;
	HFONT hCurrentfont = 0;
	int PixelXsize = 512;
	int PixelYsize = 532;		// needed to make a bit bigger since menu creation can change size.
	int StartTTL = 15;
	int RefreshRate = 50;		// timer refresh rate in milliseconds
	int NewDripChance = 20;		// chance in one thousand
	unsigned char* pTextMatrix=0;
	int* pTextMatrixTTL = 0;
	/* Old monitor colour approxamations
	* amber    : 255,176, 0
	* lt amber : 255, 204, 0
	* Green 1  : 51,255,0
	* Apple ][ : 51,255,51
	* Green 2  : 0,255,51
	* Apple ][c: 102,255,102
	* Green 3  : 0,255,102
	* 
	* Background: 40,40,40
	*/
	//stColour Drop = { 255,255,255 };	// green screen
	//stColour Tail = { 0,255,0 };
	//stColour Back = { 0,0,0 };
	//stColour Drop = { 205,130,35 };	// golden amber
	stColour Drop = { 255,255,175 };	// amber
	stColour Tail = { 255,191,0 };
	stColour Back = { 20,10,0 };
	int LineWidth = 0;
	int NbrLines = 0;
	int BufferSize = 0;

	bool PauseOutput = false;
	bool StopRain = false;
	bool SaveThreadRunning = false;
	clsRNG rng;

public:
	//void ClientResize(HWND hWnd, int nWidth, int nHeight);
	virtual bool DoCreate(HWND hInitWnd, LPCREATESTRUCT pCreateStructer) override;
	virtual bool DoButtonUp(UINT ButtonMessage, WPARAM wParam, int X, int Y) override;
	virtual bool DoPaint(HDC hdc) override;
	virtual void DoSizeMove(UINT message) override;
	virtual bool DoSize(WPARAM wParam, int wmHeight, int wmWidth) override;
	virtual bool DoKeyDown(WPARAM wParam, LPARAM lParam) override;
	virtual bool DoCommand(int wmId, int wmEvent, LPARAM lParam) override;
	virtual bool DoTimer(UINT_PTR TimerID) override;

	void SetSwapBufferSize(const int iWidth, const int iHeight);
	void CopySwapBuffer(HDC DsthDC);
	void DeleteSwapBuffer();
	bool UpdateSwapBuffer();
	int Index(const int x, const int y);
	void WindowsFullScreenToggle();

	void GetLastErrorMessage(DWORD LastError, char* poBuffer, int BufferSize);
	bool GetFileSaveName(char* pFilePath, int iPathBufferSize);
	bool GetFolderSaveName(char* pFolderPath, int iPathBufferSize);
	bool SavePPM(char* pFilePath, HDC hSaveDC);
	void ChooseTextFont();
	void SerialSave(HWND hwndPB);
	void CaptureDesktop(HDC& hOutDevice);

	void MenuCreate();
	bool MenuItemIsChecked(HMENU hMenu, UINT iItem);
};

#endif