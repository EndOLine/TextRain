#pragma once
/********************************************************************
Prog: clsHGOWindow.h
Desc: Window initialization.
Configuration Properties | General | Character Set = Use Multi-Byte Character Set
Log : 0090617 - created
110129 - added DoButtonDown, DoButtonUP and DoMouseMove
110215 - added GetWindowDefaultTitle()
111228 - Change DoCtlColorStatic to DoCtlColor.
170226 - Created MsgBoxHGO()
170530 - created DoKeyUp();
170602 - created DoKeyDown();
210727 - created DoSizeMove(); SetClientSize();
********************************************************************/

#ifndef CLSHGOWINDOW_H
#define CLSHGOWINDOW_H
#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <Windowsx.h>
#include <Commdlg.h>
#include "clsHGOapplication.h"

class clsHGOWindow {
protected:

	clsHGOapplication* pApplication;

	HINSTANCE hAppInst;
	WNDCLASSEX wcex;
	HWND hWnd;
	HACCEL hAccelTable;
	WORD 	wMenuID;

	char* czWindowClass;
	char* czWindowTitle;

	SCROLLINFO ScrollInfo = {};	// temp storage for Scroll bar information
	bool bHScrollBar, bVScrollBar;		// are there scroll bars?
	int  iHScrollUnit, iVScrollUnit;	// scrolling units
	int  iHMaxSize, iVMaxSize;			// Max virtual page/window size

	bool bWindowVisibleLastCheck;		// was window visible during last check

public:
	clsHGOWindow();
	virtual ~clsHGOWindow();

	void SetWindowClass(char* ClassName);
	void SetWindowTitle(const char* Title);
	bool GetWindowDefaultTitle(char* Title, int BufferSize);
	void SetWindowMenuID(WORD MenuID);
	void SetWindowSize(int iWidth, int iHeight);
	void SetClientSize(int iWidth, int iHeight);
	bool SetupTimer(UINT uElapse, UINT_PTR upEventID = 1);

	HWND GethWnd();
	void SethWnd(HWND Wnd);

	void CreateTheWindow(clsHGOapplication* pApp, const char* Title, WORD MenuID = 0, DWORD AdditionalStyles = 0);
	void CreateTheChildWindow(HINSTANCE pApp, char* Class, char* Title, HWND hParent, DWORD AdditionalStyles = 0);
	void ShowTheWindow(int nCmdShow);
	int  MsgBoxHGO(const char* czCaption, const char* czText, const UINT uType = MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1);
	HWND CreateAButton(char* czText, int x, int y, int iWidth, int iHeight, DWORD AdditionalStyles = 0);
	HWND CreateAOwnerButton(char* czText, int x, int y, int iWidth, int iHeight, DWORD AdditionalStyles = 0);
	HWND CreateACheckBox(char* czText, int x, int y, int iWidth, int iHeight);
	HWND CreateAEditLine(char* czText, int x, int y, int iWidth, int iHeight, int iTextLimit = 0, DWORD additionaldwStyle = ES_AUTOHSCROLL | ES_LEFT | WS_BORDER);
	HWND CreateAText(char* czText, int x, int y, int iWidth, int iHeight, DWORD additionaldwStyle = SS_SIMPLE);
	void PaintTest(HDC hdc);
	void MenuTest();
	void DrawLine(HDC hdc, int fromX, int fromY, int toX, int toY, COLORREF colour = RGB(0, 0, 0));
	void DrawPoint(HDC hdc, int x, int y, COLORREF colour = RGB(0, 0, 0));
	void GradientFill(HDC PaintDC, COLORREF StartColor, COLORREF EndColor,
		int iLeft, int iTop, int iRight, int iBottom);
	//
	//bool AdjustScrollSize(int wmHeight, int wmWidth);
	bool AdjustScrollSize();
	bool GetVirtualPageRect(LPRECT lpRect);		// return virtual Page
	bool GetVirtualViewRect(LPRECT lpRect);		// return the view the client rect has of the virtual page
	void SetVirtualPageSize(int HMax, int VMax);
	int  GetScrollHPos();
	int  GetScrollVPos();
	//
	bool GetOpenFile(char* FileName, int iBufferSize, char* Filer = NULL);
	bool GetSaveFile(char* FileName, int iBufferSize, char* Filer = NULL);
	//
	bool IsWindowVisible();		// is window visible now
	bool WasWindowVisible();	// was window visible during last check.
								//
	virtual LRESULT DoWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual bool DoCreate(HWND hInitWnd, LPCREATESTRUCT pCreateStructer);
	virtual bool DoPaint(HDC hdc);
	virtual bool DoClose();
	virtual void DoDestroy();
	virtual bool DoTimer(UINT_PTR TimerID);
	virtual bool DoCommand(int wmId, int wmEvent, LPARAM lParam);
	virtual bool DoSize(WPARAM wParam, int wmHeight, int wmWidth);
	virtual void DoSizeMove(UINT message);
	virtual bool DoButtonDown(UINT ButtonMessage, WPARAM wParam, int X, int Y);
	virtual bool DoButtonUp(UINT ButtonMessage, WPARAM wParam, int X, int Y);
	virtual bool DoKeyUP(WPARAM wParam, LPARAM lParam);
	virtual bool DoKeyDown(WPARAM wParam, LPARAM lParam);
	virtual bool DoMouseMove(WPARAM wParam, int X, int Y);
	virtual bool DoMouseWheel(int Rotate, int VirtualKey, int X, int Y);
	virtual bool DoParentNotify(int wmEvent, int wmId, LPARAM lParam);
	virtual bool DoUser(UINT message, WPARAM wParam, LPARAM lParam);
	virtual bool DoApp(UINT message, WPARAM wParam, LPARAM lParam);
	virtual HBRUSH DoCtlColor(UINT message, HDC hDC, HWND hCtl);
	virtual int DoScroll(UINT message, int wmScrollRequest, int wmScrollPosition, LPARAM lParam);
	virtual bool DoDrawItem(int iCtlID, LPDRAWITEMSTRUCT pDrawItemStruct);


private:
	void Clear();
};


#endif
