#pragma once
/********************************************************************
Prog: clsHGOapplication.h
Desc: Initialization routine for windows appllications
note that only one is allowed per program
Configuration Properties | General | Character Set = Use Multi-Byte Character Set
Library: Version.lib
Log : 090617 - created
	  170205 - bWaitForMessage was added to the Run() parameter list
			 - DoRunning() was created
	  170222 - created Create64Console()
	  210726 - note check for "Project configuration. Linker->System->SubSystem should be Windows."
			 - windows entry routine: int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ PSTR cmdline, _In_ int cmdshow){}
********************************************************************/
#ifndef CLSHGOAPPLICATION_H
#define CLSHGOAPPLICATION_H
#define WIN32_LEAN_AND_MEAN	
//#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>	// for redirect io to console
#include <io.h>		// for redirect io to console


#define CLSHGOMAXWINDOWS 50

class clsHGOapplication {

protected:
	HINSTANCE hAppInst;
	WNDCLASSEX wcex;
	HACCEL hAccelTable;

	char* czWindowClass;
	char* czWindowTitle;

	char czProgramName[255];
	char czVersion[255];

public:
	clsHGOapplication();
	virtual ~clsHGOapplication();
	int Run(HINSTANCE hInst, int nCmdShow, bool bWaitForMessage = true);

	void SetWindowClass(const char* ClassName);
	char* GetWindowClass();

	void SetWindowTitle(const char* Title);
	void CreateAChildClass(char* ChildClassName);

	void SetAcceleratorID(int iID);

	HINSTANCE GetAppInst();

	virtual bool DoInitilize();
	virtual bool DoBegin(int nCmdShow);
	virtual bool DoRunning();
	virtual void DoEnd();

	//	void RedirectIOToConsole();
	void Create64Console(char* czConsoleName = 0);

private:
	void Clear();
	void GetVersionStr(char* czVersion, int iVersionBuffer, char* czProgramName, int iProgramBuffer);
};


#endif