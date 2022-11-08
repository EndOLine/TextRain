/********************************************************************
Prog: clsHGOWindow.cpp
Desc:
Log : 090617 - created
090726 - changed button style from BS_DEFPUSHBUTTON to BS_PUSHBUTTON
110129 - CreateAText now has additional styles parameter
	   - fix WM_MOUSEWHEEL checking of parameters
111228 - Change DoCtlColorStatic to DoCtlColor.
170204 - (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE) setup for win64
201011 - fixing various char* to const char*
********************************************************************/

#include "clsHGOwindow.h"

clsHGOWindow::clsHGOWindow() {
	pApplication = 0;
	czWindowClass = 0;
	czWindowTitle = 0;
	hAppInst = 0;
	hWnd = 0;
	hAccelTable = 0;
	wMenuID = 0;
	// initial scroll bar information
	bHScrollBar = false; bVScrollBar = false;	// are there scroll bars?
	iHScrollUnit = 10; iVScrollUnit = 10;
	iHMaxSize = 300; iVMaxSize = 300;

	bWindowVisibleLastCheck = true;
};

clsHGOWindow::~clsHGOWindow() {
	Clear();
};
void clsHGOWindow::Clear() {
	if (czWindowClass) {
		delete[] czWindowClass;
		czWindowClass = 0;
	};
	if (czWindowTitle) {
		delete[] czWindowTitle;
		czWindowTitle = 0;
	};
};

void clsHGOWindow::CreateTheWindow(clsHGOapplication* pApp, const char* Title, WORD MenuID, DWORD AdditionalStyles) {
	hAppInst = pApp->GetAppInst();
	SetWindowClass(pApp->GetWindowClass());
	SetWindowTitle(Title);
	if (MenuID) {
		SetWindowMenuID(MenuID);
	};
	// note that user lpparam is set to 'this'. the clsHGOapplicaition uses the value to call this->DoWindowProc()
	hWnd = CreateWindow(czWindowClass, czWindowTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | AdditionalStyles,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL,
		(wMenuID == 0 ? NULL : LoadMenu(hAppInst, MAKEINTRESOURCE(wMenuID))),
		hAppInst, (LPVOID)this);
};

void clsHGOWindow::CreateTheChildWindow(HINSTANCE pApp, char* Class, char* Title, HWND hParent, DWORD AdditionalStyles) {
	hAppInst = pApp;
	SetWindowClass(Class);
	SetWindowTitle(Title);
	// set flags if scroll bars are requested
	bHScrollBar = false; bVScrollBar = false;
	if (AdditionalStyles & WS_HSCROLL) {
		bHScrollBar = true;
	};
	if (AdditionalStyles & WS_VSCROLL) {
		bVScrollBar = true;
	};
	// note that user lpparam is set to 'this'. the clsHGOapplicaition uses the value to call this->DoWindowProc()
	hWnd = CreateWindow(czWindowClass, czWindowTitle,
		WS_CHILD | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | AdditionalStyles,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hParent,
		NULL,
		hAppInst, (LPVOID)this);
};

void clsHGOWindow::ShowTheWindow(int nCmdShow) {
	ShowWindow(hWnd, nCmdShow);
}
int clsHGOWindow::MsgBoxHGO(const char* czCaption, const char* czText, const UINT uType) {
	/* type will indicate the type of buttons:
		MB_ABORTRETRYIGNORE, MB_CANCELTRYCONTINUE,MB_HELP,MB_OK,MB_OKCANCEL,MB_RETRYCANCEL,MB_YESNO,MB_YESNOCANCEL
	   will indicate icon:
		MB_ICONEXCLAMATION,MB_ICONWARNING,MB_ICONINFORMATION,MB_ICONASTERISK,MB_ICONQUESTION,MB_ICONSTOP,MB_ICONERROR,MB_ICONHAND
	   indicate default button:
		MB_DEFBUTTON1,MB_DEFBUTTON2,MB_DEFBUTTON3,MB_DEFBUTTON4
	   indicate the modality of the box:
		MB_APPLMODAL,MB_SYSTEMMODAL,MB_TASKMODAL
	   other options:
		MB_DEFAULT_DESKTOP_ONLY,MB_RIGHT,MB_RTLREADING,MB_SETFOREGROUND,MB_TOPMOST,MB_SERVICE_NOTIFICATION

	   Return value:
		IDABORT,IDCANCEL,IDCONTINUE,IDIGNORE,IDNO,IDOK,IDRETRY,IDTRYAGAIN,IDYES
	*/
	return MessageBox(hWnd, czText, czCaption, uType);
};

HWND clsHGOWindow::CreateAButton(char* czText, int x, int y, int iWidth, int iHeight, DWORD AdditionalStyles) {
	HWND hwndButton;

	hwndButton = CreateWindow(
		"BUTTON",   // Predefined class; Unicode assumed. 
		czText,       // Button text. 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | AdditionalStyles,  // Styles. 
		x,         // x position. 
		y,         // y position. 
		iWidth,        // Button width.
		iHeight,        // Button height.
		hWnd,       // Parent window.
		NULL,       // No menu.
		//(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	return hwndButton;
};

// create an owner drawn button
// This will activate DoDrawItem() when it needs to draw.
HWND clsHGOWindow::CreateAOwnerButton(char* czText, int x, int y, int iWidth, int iHeight, DWORD AdditionalStyles) {
	HWND hwndButton;

	hwndButton = CreateWindow(
		"BUTTON",   // Predefined class; Unicode assumed. 
		czText,       // Button text. 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | AdditionalStyles,  // Styles. 
		x,         // x position. 
		y,         // y position. 
		iWidth,        // Button width.
		iHeight,        // Button height.
		hWnd,       // Parent window.
		NULL,       // No menu.
		//(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	return hwndButton;
};

HWND clsHGOWindow::CreateACheckBox(char* czText, int x, int y, int iWidth, int iHeight) {
	HWND hwndButton;

	hwndButton = CreateWindow(
		"BUTTON",   // Predefined class; Unicode assumed. 
		czText,       // Button text. 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,  // Styles. 
		x,         // x position. 
		y,         // y position. 
		iWidth,        // Button width.
		iHeight,        // Button height.
		hWnd,       // Parent window.
		NULL,       // No menu.
		//(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	return hwndButton;
};

HWND clsHGOWindow::CreateAEditLine(char* czText, int x, int y, int iWidth, int iHeight, int iTextLimit, DWORD additionaldwStyle) {
	HWND hwndEdit;

	hwndEdit = CreateWindow("EDIT",      // predefined class 
		NULL,        // no window title 
		WS_TABSTOP | WS_CHILD | WS_VISIBLE
		| additionaldwStyle,
		x, y, iWidth, iHeight,  // set size in WM_SIZE message 
		hWnd,        // parent window 
		NULL,		// no menu
					//		(HMENU) ID_EDITCHILD,   // edit control ID 
		//(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);       // pointer not needed 

	SendMessage(hwndEdit,      // handle to destination control     
		EM_SETLIMITTEXT,      // message ID     
		(WPARAM)iTextLimit,      // = (WPARAM) () wParam;    
		0				      // = 0; not used, must be zero 
	);
	if (czText) {
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)czText);
	};
	return hwndEdit;
};

HWND clsHGOWindow::CreateAText(char* czText, int x, int y, int iWidth, int iHeight, DWORD additionaldwStyle) {
	HWND hwndText;

	hwndText = CreateWindow("STATIC",      // predefined class 
		NULL,        // no window title 
		WS_CHILD | WS_VISIBLE
		| additionaldwStyle,
		x, y, iWidth, iHeight,  // set size in WM_SIZE message 
		hWnd,        // parent window 
		NULL,		// no menu 
		//(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);       // pointer not needed 

	if (czText) {
		SendMessage(hwndText, WM_SETTEXT, 0, (LPARAM)czText);
	};
	return hwndText;
};

void clsHGOWindow::PaintTest(HDC hdc) {
	HPEN hpen, hpenOld;
	HBRUSH hbrush, hbrushOld;
	RECT Rect;
	WINDOWINFO wi;

	// get size of content area
	GetClientRect(hWnd, &Rect);

	// get window information
	wi.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hWnd, &wi);

	// Create a green pen.
	hpen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
	// Create a red brush.
	hbrush = CreateSolidBrush(RGB(255, 0, 0));

	// Select the new pen and brush, and then draw.
	hpenOld = (HPEN)SelectObject(hdc, hpen);
	hbrushOld = (HBRUSH)SelectObject(hdc, hbrush);

	// added and extra '+1' on each term to create the white border
	Rectangle(hdc, wi.cxWindowBorders + 1 + 1, wi.cyWindowBorders + 1 + 1,
		Rect.right - (wi.cxWindowBorders + 1), Rect.bottom - (wi.cyWindowBorders + 1));

	// Do not forget to clean up.
	SelectObject(hdc, hpenOld);
	DeleteObject(hpen);
	SelectObject(hdc, hbrushOld);
	DeleteObject(hbrush);

	DrawLine(hdc, 11, 100, Rect.right - (wi.cxWindowBorders + 7), 100, RGB(0, 0, 255));

	DrawLine(hdc, 0, 0, Rect.right, Rect.bottom, RGB(0, 0, 255));
	DrawLine(hdc, 0, Rect.bottom, Rect.right, Rect.top, RGB(0, 0, 255));

	DrawLine(hdc, 0, 0, Rect.right, 0, RGB(0, 0, 255));
	DrawLine(hdc, Rect.right - 1, Rect.top, Rect.right - 1, Rect.bottom - 1, RGB(0, 0, 255));
	DrawLine(hdc, Rect.right - 1, Rect.bottom - 1, Rect.left, Rect.bottom - 1, RGB(0, 0, 255));
	DrawLine(hdc, 0, Rect.top, Rect.left, Rect.bottom, RGB(0, 0, 255));
};

void clsHGOWindow::MenuTest() {
	HMENU hMenu, hSubMenu;
	if (!hWnd) return;
	hMenu = CreateMenu();
	hSubMenu = CreatePopupMenu();

	AppendMenu(hSubMenu, MF_STRING, 9001, "&New\tCtl-N");
	AppendMenu(hSubMenu, MF_STRING, 9002, "&Open...\tCtl-O");
	AppendMenu(hSubMenu, MF_STRING, 9003, "&Save\tCtl-S");
	AppendMenu(hSubMenu, MF_STRING, 9004, "Save &As...");
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, 9009, "E&xit");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING | MF_GRAYED | MF_CHECKED, 9011, "Undo\tCtl-Z");
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, 9011, "&Copy\tCtl-C");
	AppendMenu(hSubMenu, MF_STRING, 9011, "Cu&t\tCtl-X");
	AppendMenu(hSubMenu, MF_STRING, 9011, "&Paste\tCtl-V");
	AppendMenu(hSubMenu, MF_STRING, 9011, "De&lete\tDel");
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, 9011, "&Find...\tCtl-G");
	AppendMenu(hSubMenu, MF_STRING, 9011, "Find &Next\tF3");
	AppendMenu(hSubMenu, MF_STRING, 9011, "&Replace...");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Edit");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, 9011, "&About");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");

	/*Resources associated with a menu that is assigned to a window are freed automatically.
	If the menu is not assigned to a window, an application must free system resources
	associated with the menu before closing. An application frees menu resources by calling
	the DestroyMenu function.*/
	SetMenu(hWnd, hMenu);
};


void clsHGOWindow::DrawPoint(HDC hdc, int x, int y, COLORREF colour) {
	DrawLine(hdc, x, y, x + 1, y + 1, colour);
};
void clsHGOWindow::DrawLine(HDC hdc, int fromX, int fromY, int toX, int toY, COLORREF colour) {
	HPEN hpen, hpenOld;

	hpen = CreatePen(PS_SOLID, 1, colour);
	hpenOld = (HPEN)SelectObject(hdc, hpen);
	MoveToEx(hdc, fromX, fromY, NULL);
	LineTo(hdc, toX, toY);
	// clean up
	SelectObject(hdc, hpenOld);
	DeleteObject(hpen);
};

void clsHGOWindow::GradientFill(HDC PaintDC, COLORREF StartColor, COLORREF EndColor,
	int iLeft, int iTop, int iRight, int iBottom) {
	float fDrawHeight;
	float fStartRed, fStartGreen, fStartBlue, fEndRed, fEndGreen, fEndBlue;
	float fDeltaRed, fDeltaGreen, fDeltaBlue;
	float fCurRed, fCurBlue, fCurGreen;
	int   iRed, iBlue, iGreen;
	HGDIOBJ original = NULL;

	original = SelectObject(PaintDC, GetStockObject(DC_PEN));

	fStartRed = GetRValue(StartColor); fStartGreen = GetGValue(StartColor); fStartBlue = GetBValue(StartColor);
	fEndRed = GetRValue(EndColor);   fEndGreen = GetGValue(EndColor);   fEndBlue = GetBValue(EndColor);

	fDrawHeight = (float)iBottom - (float)iTop;
	fDeltaRed = (fEndRed - fStartRed) / fDrawHeight;
	fDeltaGreen = (fEndGreen - fStartGreen) / fDrawHeight;
	fDeltaBlue = (fEndBlue - fStartBlue) / fDrawHeight;
	fCurRed = fStartRed;
	fCurGreen = fStartGreen;
	fCurBlue = fStartBlue;

	for (int y = iTop; y < iBottom; y++) {
		iRed = (int)fCurRed; iGreen = (int)fCurGreen; iBlue = (int)fCurBlue;
		SetDCPenColor(PaintDC, RGB(iRed, iGreen, iBlue));
		MoveToEx(PaintDC, iLeft, y, NULL);
		LineTo(PaintDC, iRight, y);
		fCurRed += fDeltaRed;
		fCurGreen += fDeltaGreen;
		fCurBlue += fDeltaBlue;
	};
	SelectObject(PaintDC, original);
};

// return true if window has scroll bars
bool clsHGOWindow::AdjustScrollSize() {
	int hPos, vPos;
	RECT rClientArea;
	int wmHeight, wmWidth;

	GetClientRect(hWnd, &rClientArea);
	wmHeight = rClientArea.bottom;
	wmWidth = rClientArea.right;
	// handling scroll bars
#ifdef _DEBUG
	char czIntValue[50];
	OutputDebugStringA("AdjustScrollSize ");
	OutputDebugStringA(" Height:");
	OutputDebugStringA(_itoa(wmHeight, czIntValue, 10));
	OutputDebugStringA(" Width:");
	OutputDebugStringA(_itoa(wmWidth, czIntValue, 10));
	OutputDebugStringA("\n");
#endif
	if (bVScrollBar) {
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_POS;
		GetScrollInfo(hWnd, SB_VERT, &ScrollInfo);
		vPos = ScrollInfo.nPos;  // range from: nMin and nMax - max( nPage? 1, 0)
								 // Set the vertical scrolling range and page size
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_RANGE | SIF_PAGE;
		ScrollInfo.nMin = 0;
		ScrollInfo.nMax = iVMaxSize; // - (wmHeight - 1); //MaxScrollPos = MaxRangeValue - (PageSize - 1)
		if (wmHeight < 0) {
			ScrollInfo.nPage = 0;
		} else if (wmHeight > (ScrollInfo.nMax - ScrollInfo.nMin + 1)) {
			ScrollInfo.nPage = ScrollInfo.nMax - ScrollInfo.nMin + 1;
		} else {
			ScrollInfo.nPage = wmHeight; // range from: 0 to nMax - nMin +1
		};
#ifdef _DEBUG
		char czIntValue[50];
		OutputDebugStringA("Vertical nMin:");
		OutputDebugStringA(_itoa(ScrollInfo.nMin, czIntValue, 10));
		OutputDebugStringA(" nMax:");
		OutputDebugStringA(_itoa(ScrollInfo.nMax, czIntValue, 10));
		OutputDebugStringA(" nPage:");
		OutputDebugStringA(_itoa(ScrollInfo.nPage, czIntValue, 10));
		OutputDebugStringA(" nPos:");
		OutputDebugStringA(_itoa(vPos, czIntValue, 10));
		OutputDebugStringA("\n");
#endif
		SetScrollInfo(hWnd, SB_VERT, &ScrollInfo, true);

		ScrollInfo.fMask = SIF_POS;
		GetScrollInfo(hWnd, SB_VERT, &ScrollInfo);
		if (ScrollInfo.nPos != vPos) {
			ScrollWindow(hWnd, 0, /*iVScrollUnit * */ (vPos - ScrollInfo.nPos), NULL, NULL);
			UpdateWindow(hWnd);
		};
	};

	if (bHScrollBar) {
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_POS;
		GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo);
		hPos = ScrollInfo.nPos;
		// Set the horizontal scrolling range and page size. 
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_RANGE | SIF_PAGE;
		ScrollInfo.nMin = 0;
		ScrollInfo.nMax = iHMaxSize;
		if (wmWidth < 0) {
			ScrollInfo.nPage = 0;
		} else if (wmWidth > (ScrollInfo.nMax - ScrollInfo.nMin + 1)) {
			ScrollInfo.nPage = ScrollInfo.nMax - ScrollInfo.nMin + 1;
		} else {
			ScrollInfo.nPage = wmWidth; // range from: 0 to nMax - nMin +1
		};
#ifdef _DEBUG
		char czIntValue[50];
		OutputDebugStringA("Horz nMin:");
		OutputDebugStringA(_itoa(ScrollInfo.nMin, czIntValue, 10));
		OutputDebugStringA(" nMax:");
		OutputDebugStringA(_itoa(ScrollInfo.nMax, czIntValue, 10));
		OutputDebugStringA(" nPage:");
		OutputDebugStringA(_itoa(ScrollInfo.nPage, czIntValue, 10));
		OutputDebugStringA(" nPos:");
		OutputDebugStringA(_itoa(hPos, czIntValue, 10));
		OutputDebugStringA("\n");
#endif
		SetScrollInfo(hWnd, SB_HORZ, &ScrollInfo, true);
		ScrollInfo.fMask = SIF_POS;
		GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo);
		if (ScrollInfo.nPos != hPos) {
			ScrollWindow(hWnd, /*iHScrollUnit * */ (hPos - ScrollInfo.nPos), 0, NULL, NULL);
			UpdateWindow(hWnd);
		};
	};
	if (bVScrollBar || bHScrollBar) {
		return true;
	};

	return false;
};

void clsHGOWindow::SetVirtualPageSize(int HMax, int VMax) {
	//	int iHeight,iWidth;

	iVMaxSize = VMax;
	if (iVMaxSize < 100) iVMaxSize = 100;
	iHMaxSize = HMax;
	if (iHMaxSize < 100) iHMaxSize = 100;
	/*
	ScrollInfo.cbSize = sizeof (ScrollInfo);
	ScrollInfo.fMask = SIF_PAGE;
	GetScrollInfo (hWnd, SB_VERT, &ScrollInfo);
	iHeight = ScrollInfo.nPage;

	ScrollInfo.cbSize = sizeof (ScrollInfo);
	ScrollInfo.fMask = SIF_PAGE;
	GetScrollInfo (hWnd, SB_HORZ, &ScrollInfo);
	iWidth = ScrollInfo.nPage;
	*/
	AdjustScrollSize();
	AdjustScrollSize();	// doing it a second time incase both scroll bars become visable at once.
};

/*
void clsHGOWindow::SetVirtualPageSize(int HMax, int VMax) {
//	int hDif,vDif;
int hPos,vPos;
int hPage,vPage;
//	SCROLLINFO ScrollInfo;

//	hDif=HMax-iHMaxSize;
//	vDif=VMax-iVMaxSize;


if ((bVScrollBar) &&(iVMaxSize!=VMax) ) {
iVMaxSize=VMax;
if (iVMaxSize < 100) iVMaxSize=100;
ScrollInfo.cbSize = sizeof (ScrollInfo);
ScrollInfo.fMask = SIF_POS;
GetScrollInfo (hWnd, SB_VERT, &ScrollInfo);
vPos = ScrollInfo.nPos;
// Set the vertical scrolling range and page size
ScrollInfo.cbSize = sizeof(ScrollInfo);
ScrollInfo.fMask  = SIF_RANGE | SIF_PAGE;
GetScrollInfo (hWnd, SB_VERT, &ScrollInfo);
ScrollInfo.nMax   = iVMaxSize; // - (ScrollInfo.nPage - 1);
SetScrollInfo(hWnd, SB_VERT, &ScrollInfo, true);

//adjust position if necessary
ScrollInfo.fMask = SIF_POS;
GetScrollInfo (hWnd, SB_VERT, &ScrollInfo);
if (ScrollInfo.nPos != vPos) {			// if it is not the same
ScrollInfo.nPos = vPos;
SetScrollInfo(hWnd, SB_VERT, &ScrollInfo, true);	// try to set it the same
GetScrollInfo (hWnd, SB_VERT, &ScrollInfo);			// check again
ScrollWindow(hWnd, 0, (vPos - ScrollInfo.nPos), NULL, NULL);
UpdateWindow (hWnd);
};
};

if ((bHScrollBar) &&(iHMaxSize!=HMax)) {
iHMaxSize=HMax;
if (iHMaxSize < 100) iHMaxSize=100;
ScrollInfo.cbSize = sizeof (ScrollInfo);
ScrollInfo.fMask = SIF_POS | SIF_PAGE;
GetScrollInfo (hWnd, SB_HORZ, &ScrollInfo);
hPos = ScrollInfo.nPos;
hPage= ScrollInfo.nPage;
// Set the horizontal scrolling range and page size.
ScrollInfo.cbSize = sizeof(ScrollInfo);
ScrollInfo.fMask  = SIF_RANGE;
GetScrollInfo (hWnd, SB_HORZ, &ScrollInfo);

ScrollInfo.cbSize = sizeof(ScrollInfo);
ScrollInfo.fMask  = SIF_RANGE;
ScrollInfo.nMin   = 0;
ScrollInfo.nMax   = iHMaxSize; // - (ScrollInfo.nPage - 1);
SetScrollInfo(hWnd, SB_HORZ, &ScrollInfo, true);

ScrollInfo.cbSize = sizeof(ScrollInfo);
ScrollInfo.fMask  = SIF_PAGE;
ScrollInfo.nPage  = hPage;
SetScrollInfo(hWnd, SB_HORZ, &ScrollInfo, true);
// adjust position if necessary
ScrollInfo.fMask = SIF_POS | SIF_ALL;
GetScrollInfo (hWnd, SB_HORZ, &ScrollInfo);
if (ScrollInfo.nPos != hPos) {
ScrollInfo.nPos = hPos;
SetScrollInfo(hWnd, SB_HORZ, &ScrollInfo, TRUE);	// try to set it the same
GetScrollInfo (hWnd, SB_HORZ, &ScrollInfo);			// check again
ScrollWindow(hWnd, (hPos - ScrollInfo.nPos), 0, NULL, NULL);
UpdateWindow (hWnd);
};
//		InvalidateRect(hWnd,NULL,TRUE);
//		ShowWindow(hWnd,SW_MINIMIZE);
//		ShowWindow(hWnd,SW_RESTORE);
};
};
*/

int clsHGOWindow::GetScrollHPos() {
	ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
	ScrollInfo.cbSize = sizeof(ScrollInfo);
	ScrollInfo.fMask = SIF_POS;
	if (!GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo)) {
		return 0;
	};
	return ScrollInfo.nPos;
};

int clsHGOWindow::GetScrollVPos() {
	ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
	ScrollInfo.cbSize = sizeof(ScrollInfo);
	ScrollInfo.fMask = SIF_POS;
	if (!GetScrollInfo(hWnd, SB_VERT, &ScrollInfo)) {
		return 0;
	};
	return ScrollInfo.nPos;
};

// return false if unable to complete action
// lpRect contain the size of the virtual client area.
bool clsHGOWindow::GetVirtualPageRect(LPRECT lpRect) {
	bool bResult;

	bResult = GetClientRect(hWnd, lpRect);
	if (!bResult) return bResult;
	if (bHScrollBar) {
		ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_POS;
		if (!GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo)) {
			return false;
		};
		lpRect->right += ScrollInfo.nPos;
		if (iHMaxSize > lpRect->right) {
			lpRect->right = iHMaxSize;
		};
	};
	if (bVScrollBar) {
		ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_POS;
		if (!GetScrollInfo(hWnd, SB_VERT, &ScrollInfo)) {
			return false;
		};
		lpRect->bottom += ScrollInfo.nPos;
		if (iVMaxSize > lpRect->bottom) {
			lpRect->bottom = iVMaxSize;
		};
	};
	return true;
};

bool clsHGOWindow::GetVirtualViewRect(LPRECT lpRect) {
	bool bResult;

	bResult = GetClientRect(hWnd, lpRect);
	if (!bResult) return bResult;
	if (bHScrollBar) {
		ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_POS;
		if (!GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo)) {
			return false;
		};
		lpRect->left += ScrollInfo.nPos;
		lpRect->right += ScrollInfo.nPos;
	};
	if (bVScrollBar) {
		ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_POS;
		if (!GetScrollInfo(hWnd, SB_VERT, &ScrollInfo)) {
			return false;
		};
		lpRect->top += ScrollInfo.nPos;
		lpRect->bottom += ScrollInfo.nPos;
	};
	return true;
};
/*
bool clsHGOWindow::GetVirtualClientRect(LPRECT lpRect) {
bool bResult;

bResult=GetClientRect(hWnd, lpRect);
if (!bResult) return bResult;
if (bHScrollBar) {
ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
ScrollInfo.cbSize = sizeof(ScrollInfo);
ScrollInfo.fMask = SIF_TRACKPOS;
if (!GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo)) {
return false;
};
lpRect->left+=ScrollInfo.nTrackPos;
lpRect->right+=ScrollInfo.nTrackPos;
};
if (bVScrollBar) {
ZeroMemory(&ScrollInfo, sizeof(ScrollInfo));
ScrollInfo.cbSize = sizeof(ScrollInfo);
ScrollInfo.fMask = SIF_TRACKPOS;
if (!GetScrollInfo(hWnd, SB_VERT, &ScrollInfo)) {
return false;
};
lpRect->top+=ScrollInfo.nTrackPos;
lpRect->bottom+=ScrollInfo.nTrackPos;
};
return bResult;
};
*/
void clsHGOWindow::SetWindowClass(char* ClassName) {
	if (czWindowClass) {
		delete[] czWindowClass;
		czWindowClass = 0;
	};
	if (!ClassName) return;
	czWindowClass = new char[strlen(ClassName) + 1];
	//	strcpy(czWindowClass,ClassName);
	strcpy_s(czWindowClass, strlen(ClassName) + 1, ClassName);
};

void clsHGOWindow::SetWindowTitle(const char* Title) {
	if (czWindowTitle) {
		delete[] czWindowTitle;
		czWindowTitle = 0;
	};
	if (!Title) return;
	czWindowTitle = new char[strlen(Title) + 1];
	//	strcpy(czWindowTitle,Title);
	strcpy_s(czWindowTitle, strlen(Title) + 1, Title);
};

bool clsHGOWindow::GetWindowDefaultTitle(char* Title, int BufferSize) {
	if (!czWindowTitle) {
		return false;
	};
	if (!Title) {
		return false;
	};
	if (strcpy_s(Title, BufferSize, czWindowTitle) == 0) {
		return true;
	} else {
		return false;
	};
};

void clsHGOWindow::SetWindowMenuID(WORD MenuID) {
	wMenuID = MenuID;
};

void clsHGOWindow::SetWindowSize(int iWidth, int iHeight) {
	RECT Rect;
	GetWindowRect(hWnd, &Rect);
	MoveWindow(hWnd, Rect.left, Rect.top, iWidth, iHeight, true);
};

void clsHGOWindow::SetClientSize(int iWidth, int iHeight) {
	//resize client area adjusting for borders
	RECT rcClient, rcWind;
	POINT ptDiff;
	GetClientRect(hWnd, &rcClient);		// get current client rect
	GetWindowRect(hWnd, &rcWind);		// get total windows size
	ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;	// calculate difference this will be the x borders
	ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;	// calculate difference this will be the y borders
	MoveWindow(hWnd, rcWind.left, rcWind.top, iWidth + ptDiff.x, iHeight + ptDiff.y, TRUE);
}

HWND clsHGOWindow::GethWnd() {
	return hWnd;
};
void clsHGOWindow::SethWnd(HWND Wnd) {
	hWnd = Wnd;
};

// uElapse is time in milliseconds
bool clsHGOWindow::SetupTimer(UINT uElapse, UINT_PTR upEventID) {
	UINT_PTR  uTimerID = 0;
	if (uElapse > 0) {
		uTimerID = SetTimer(hWnd, upEventID, uElapse, NULL);
		if (uTimerID == 0) {
			return false;
		};
	} else {
		KillTimer(hWnd, upEventID);
		uTimerID = 0;
	};
	return true;
};
// other messages of note:
// WM_CTLCOLORSTATIC: An edit control that is not read-only or disabled sends the WM_CTLCOLOREDIT message to its parent window when the control is about to be drawn.
LRESULT clsHGOWindow::DoWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT UpdateRect;
	int wmWidth, wmHeight;
	int wmRotate, wmVirtualKey, wmX, wmY;
	int wmScrollRequest, wmScrollPosition;
	//static HBRUSH hBrush = CreateSolidBrush(RGB(230,230,230)); 
	//static HBRUSH hBrush = GetSysColorBrush(COLOR_WINDOW);

	switch (message) {
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
#ifdef _DEBUG
		OutputDebugStringA("WM_COMMAND\n");
#endif
		if (!DoCommand(wmId, wmEvent, lParam)) {
			// if command not handled by DoCommand execute default
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_CREATE:
#ifdef _DEBUG
		OutputDebugStringA("WM_CREATE\n");
#endif
		this->hWnd = hWnd;
		if (!DoCreate(hWnd, (LPCREATESTRUCT)lParam)) {
			return -1;
		};
		break;
	case WM_PAINT:
		if (GetUpdateRect(hWnd, &UpdateRect, false)) {
			hdc = BeginPaint(hWnd, &ps);
			//			OutputDebugStringA("WM_PAINT\n");
			DoPaint(hdc);
			EndPaint(hWnd, &ps);
		};
		break;
	case WM_DESTROY:
#ifdef _DEBUG
		OutputDebugStringA("WM_DESTROY\n");
#endif
		DoDestroy();
		//		RemoveWindow(hWnd);
		break;
	case WM_ENDSESSION:
#ifdef _DEBUG
		OutputDebugStringA("WM_ENDSESSION\n");
#endif
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	case WM_ENTERSIZEMOVE:
	case WM_EXITSIZEMOVE:
		DoSizeMove(message);
		break;
	case WM_CLOSE:
#ifdef _DEBUG
		OutputDebugStringA("WM_Close\n");
#endif
		if (DoClose()) {
			DestroyWindow(hWnd);
		};
		break;
	case WM_QUIT:
#ifdef _DEBUG
		OutputDebugStringA("WM_QUIT\n");
#endif
		//		// this is never sent here. by this time the window is closed
		break;
	case WM_SIZE:
		//		OutputDebugStringA("WM_SIZE\n");
		wmWidth = LOWORD(lParam);
		wmHeight = HIWORD(lParam);
		if (!DoSize(wParam, wmHeight, wmWidth)) {
			//			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
		//		OutputDebugStringA("WM_TIMER\n");
		if ((TIMERPROC)lParam) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		if (!DoTimer((UINT_PTR)wParam)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_KEYUP:
#ifdef _DEBUG
		OutputDebugStringA("WM_KEYUP\n");
#endif
		if (!DoKeyUP(wParam, lParam)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_KEYDOWN:
#ifdef _DEBUG
		OutputDebugStringA("WM_KEYDOWN\n");
#endif
		if (!DoKeyDown(wParam, lParam)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_LBUTTONDBLCLK:
#ifdef _DEBUG
		OutputDebugStringA("WM_LBUTTONDBLCLK\n");
#endif
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
#ifdef _DEBUG
		OutputDebugStringA("WM_?BUTTONDOWN\n");
#endif
		wmX = GET_X_LPARAM(lParam);
		wmY = GET_Y_LPARAM(lParam);
		if (!DoButtonDown(message, wParam, wmX, wmY)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
#ifdef _DEBUG
		OutputDebugStringA("WM_?BUTTONUP\n");
#endif
		wmX = GET_X_LPARAM(lParam);
		wmY = GET_Y_LPARAM(lParam);
		if (!DoButtonUp(message, wParam, wmX, wmY)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_MOUSEMOVE:
		//OutputDebugStringA("WM_MOUSEMOVE\n");
		wmX = GET_X_LPARAM(lParam);
		wmY = GET_Y_LPARAM(lParam);
		if (!DoMouseMove(wParam, wmX, wmY)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_MOUSEWHEEL:
		//		wmRotate = HIWORD(wParam);
		//		if (wmRotate > 120) { wmRotate=wmRotate | 0xffff0000;};
		//		wmVirtualKey=LOWORD(wParam);
		//		wmX= LOWORD(lParam);
		//		wmY= HIWORD(lParam);
		wmVirtualKey = GET_KEYSTATE_WPARAM(wParam);
		wmRotate = GET_WHEEL_DELTA_WPARAM(wParam);
		if (wmRotate > 120) { wmRotate = wmRotate | 0xffff0000; };

		wmX = GET_X_LPARAM(lParam);
		wmY = GET_Y_LPARAM(lParam);
#ifdef _DEBUG
		OutputDebugStringA("WM_MOUSEWHEEL\n");
#endif
		if (!DoMouseWheel(wmRotate, wmVirtualKey, wmX, wmY)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	case WM_PARENTNOTIFY:
#ifdef _DEBUG
		OutputDebugStringA("WM_PARENTNOTIFY\n");
#endif
		wmEvent = LOWORD(wParam);
		wmId = HIWORD(wParam);
		if (!DoParentNotify(wmEvent, wmId, lParam)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
		//	case WM_CTLCOLORBTN:	// this is called too often let WM_DRAWITEM handle owner drawn buttons
	case WM_CTLCOLORSTATIC:
		//		OutputDebugStringA("WM_CTLCOLORSTATIC\n");
		return (INT_PTR)DoCtlColor(message, (HDC)wParam, (HWND)lParam);
	case WM_DRAWITEM:
		return DoDrawItem((int)wParam, (LPDRAWITEMSTRUCT)lParam);
	case WM_HSCROLL:
	case WM_VSCROLL:
		wmScrollRequest = LOWORD(wParam);
		wmScrollPosition = HIWORD(wParam);
		return DoScroll(message, wmScrollRequest, wmScrollPosition, lParam);
		break;
	default:
		// message ranges
		if ((message >= WM_USER) && (message <= 0x7FFF)) {
#ifdef _DEBUG
			OutputDebugStringA("WM_USER\n");
#endif
			if (!DoUser(message, wParam, lParam)) {
				return DefWindowProc(hWnd, message, wParam, lParam);
			};
		} else if ((message >= WM_APP) && (message <= 0xBFFF)) {
#ifdef _DEBUG
			OutputDebugStringA("WM_APP\n");
#endif
			if (!DoApp(message, wParam, lParam)) {
				return DefWindowProc(hWnd, message, wParam, lParam);
			};
		} else {
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
	}
	return 0;
};

bool clsHGOWindow::DoCreate(HWND hInitWnd, LPCREATESTRUCT pCreateStructer) {
	/*
	The WM_CREATE message is sent when an application requests that a window be created
	by calling the CreateWindowEx or CreateWindow function. (The message is sent before
	the function returns.) The window procedure of the new window receives this message
	after the window is created, but before the window becomes visible.
	*/

	//	hWnd=hInitWnd; // not return yet from CreateWindow... so what the heck... set it here
	return true;
};

bool clsHGOWindow::DoPaint(HDC hdc) {
	/*
	The WM_PAINT message is sent when the system or another application makes a request
	to paint a portion of an application's window.
	*/
	//	PaintTest(hdc);
	return true;
};

bool clsHGOWindow::DoClose() {
	/*
	message is sent as a signal that a window or an application should terminate.
	*/
	//PostQuitMessage(0);
	// return true to terminate window.
	return true;
};

void clsHGOWindow::DoDestroy() {
	/*
	message is sent when a window is being destroyed. It is sent to the window
	procedure of the window being destroyed after the window is removed from the
	screen.

	This message is sent first to the window being destroyed and then to the child
	windows (if any) as they are destroyed. During the processing of the message,
	it can be assumed that all child windows still exist.
	*/
	PostQuitMessage(0);	// quit application
};

bool clsHGOWindow::DoTimer(UINT_PTR TimerID) {
	/*
	message is posted to the installing thread's message queue when a timer expires.
	*/
	// return false if message not handled by this route
	return false;
};

bool clsHGOWindow::DoCommand(int wmId, int wmEvent, LPARAM lParam) {
	/*
	message is sent when the user selects a command item from a menu, when a control
	sends a notification message to its parent window, or when an accelerator keystroke
	is translated.
	*/
	/*
	wmEvent: 0 - Menu			(wmId = (Menu identifier (IDM_*))			(lParam = 0)
	1 - Accelerator	(wmId = (Accelerator identifier (IDM_*))	(lParam = 0)
	(Control-defined notification code) - Control
	(wmId = (Control identifier))				(lParan = (Handle to the control window))
	*/

	// Parse the menu selections:
	//
	//switch (wmId) {
	//case IDM_ABOUT:
	//	DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
	//	break;
	//case IDM_EXIT:
	//	DestroyWindow(hWnd);
	//	break;
	//default:
	//	return DefWindowProc(hWnd, message, wParam, lParam);
	//}
	//
#ifdef _DEBUG
	char	czText[100];
	sprintf(czText, "Command ID is: %i", wmId);
	MsgBoxHGO("Menu Command Selected", czText);
#endif 

	// return false if message not handled by this route
	return false;
};

bool clsHGOWindow::DoSize(WPARAM wParam, int wmHeight, int wmWidth) {
	/*
	The WM_SIZE message is sent to a window after its size has changed.
	wParam can be as follows:
	SIZE_MAXHIDE
	Message is sent to all pop-up windows when some other window is maximized.
	SIZE_MAXIMIZED
	The window has been maximized.
	SIZE_MAXSHOW
	Message is sent to all pop-up windows when some other window has been restored to its former size.
	SIZE_MINIMIZED
	The window has been minimized.
	SIZE_RESTORED
	The window has been resized, but neither the SIZE_MINIMIZED nor SIZE_MAXIMIZED value applies.
	*/
	// return false if message not handled by this route

	// handling scroll bars
	return AdjustScrollSize();

	//
	return false;
};

void clsHGOWindow::DoSizeMove(UINT message) {
	/*
	* WM_ENTERSIZEMOVE:
	Sent one time to a window after it enters the moving or sizing modal loop. The window enters the moving or
	sizing modal loop when the user clicks the window's title bar or sizing border, or when the window passes
	the WM_SYSCOMMAND message to the DefWindowProc function and the wParam parameter of the message specifies
	the SC_MOVE or SC_SIZE value. The operation is complete when DefWindowProc returns.

	The system sends the WM_ENTERSIZEMOVE message regardless of whether the dragging of full windows is enabled.

	WM_EXITSIZEMOVE:
	Sent one time to a window, after it has exited the moving or sizing modal loop. The window enters the moving
	or sizing modal loop when the user clicks the window's title bar or sizing border, or when the window passes
	the WM_SYSCOMMAND message to the DefWindowProc function and the wParam parameter of the message specifies
	the SC_MOVE or SC_SIZE value. The operation is complete when DefWindowProc returns.

	message is either WM_ENTERSIZEMOVE or WM_EXITSIZEMOVE
	*/

};

bool clsHGOWindow::DoButtonDown(UINT ButtonMessage, WPARAM wParam, int X, int Y) {
	/*
	The WM_LBUTTONDOWN message is posted when the user presses the left mouse button while the
	cursor is in the client area of a window. If the mouse is not captured, the message is posted
	to the window beneath the cursor. Otherwise, the message is posted to the window that has captured
	the mouse.
	*/
	/*
	ButtonMessage can be: WM_LBUTTONDOWN, WM_RBUTTONDOWN, WM_MBUTTONDOWN
	wParam: Indicates whether various virtual keys are down.
	*/

	return false; // return false if message not handled by this route
};

bool clsHGOWindow::DoButtonUp(UINT ButtonMessage, WPARAM wParam, int X, int Y) {
	/*
	The WM_?BUTTONUP message is posted when the user releases the left mouse button
	while the cursor is in the client area of a window. If the mouse is not captured,
	the message is posted to the window beneath the cursor. Otherwise, the message
	is posted to the window that has captured the mouse.
	*/
	/*
	ButtonMessage can be: WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP
	wParam: Indicates whether various virtual keys are down.
	*/

	return false; // return false if message not handled by this route
};

bool clsHGOWindow::DoKeyUP(WPARAM wParam, LPARAM lParam) {
	/*
	Posted to the window with the keyboard focus when a nonsystem key is released. A
	nonsystem key is a key that is pressed when the ALT key is not pressed, or a keyboard
	key that is pressed when a window has the keyboard focus
	*/
	/*
	wParam: the virtual-key code of the nonsystem key. (virtual-key codes WinUser.h)
			example: VK_LBUTTON,VK_RIGHT,VK_DOWN
			* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
			* 0x40 : unassigned
			* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	lParam: the repeat count, scan code, extended-key flag, context code, previous key-state
			flag, and transition-state flag.
			0-15 repeat count for the current message. the value is the
				 number of times the keystroke is autorepeaded as a result of the
				 user holding down the key. the repeat count is always 1 for a
				 wm_keyup message.
			16-23 The scan code. the value depends on the OEM.
			24   indicates whether the key is an extended key, such as the right-
				 hand alt and ctrl keys that appear on an extended 101- or
				 102-key keyboard. the value is 1 if it is an extended key;
				 otherwise, it is 0.
			25-28 reserved; do not use
			29   the context code.  the value is always 0 for a wm_keyup message
			30   the previous key state. the value is always 1 for a wm_keyup message
			31   the transition state. the value is always 1 for a wm_keyup message

	*/
	return false; // return false if message not handled by this route
};
bool clsHGOWindow::DoKeyDown(WPARAM wParam, LPARAM lParam) {
	/*
	Posted to the window with the keyboard focus when a nonsystem key is released. A
	nonsystem key is a key that is pressed when the ALT key is not pressed.
	*/
	/*
	wParam: the virtual - key code of the nonsystem key. (virtual - key codes WinUser.h)
		example : VK_LBUTTON, VK_RIGHT, VK_DOWN
		* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
		* 0x40 : unassigned
		* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	lParam : the repeat count, scan code, extended - key flag, context code, previous key - state
		flag, and transition - state flag.
		0 - 15 repeat count for the current message.the value is the
				number of times the keystroke is autorepeaded as a result of the
				user holding down the key. if the keystroke is held long enough,
				multiple messages are sent. however, the repeat count is not cumulative.
		16 - 23 The scan code.the value depends on the OEM.
		24   indicates whether the key is an extended key, such as the right -
			hand alt and ctrl keys that appear on an extended 101 - or
			102 - key keyboard.the value is 1 if it is an extended key;
			otherwise, it is 0.
		25 - 28 reserved; do not use
		29   the context code.the value is always 0 for a wm_keydown message
		30   the previous key state. the value is 1 if the key is down before
			 the message is sent, or it is zero if the key is up.
		31   the transition state.the value is always 0 for a wm_keydown message

	*/
	union uKeyState {
		LPARAM	lparam;
		struct {
			unsigned nRepeatCount : 16;
			unsigned nScanCode : 8;
			unsigned nExtended : 1;
			unsigned nReserved : 4;
			unsigned nContext : 1;
			unsigned nPrev : 1;
			unsigned nTrans : 1;
		};
	};
	uKeyState KeyState;
	KeyState.lparam = lParam;
	return false;	// return false if message not handled by this route
};

bool clsHGOWindow::DoMouseMove(WPARAM wParam, int X, int Y) {
	/*
	The WM_MOUSEMOVE message is posted to a window when the cursor moves.
	If the mouse is not captured, the message is posted to the window that
	contains the cursor. Otherwise, the message is posted to the window
	that has captured the mouse.
	*/
	/*
	wParam: Indicates whether various virtual keys are down.
	*/

	return false; // return false if message not handled by this route
};

bool clsHGOWindow::DoMouseWheel(int Rotate, int VirtualKey, int X, int Y) {
	/*
	The WM_MOUSEWHEEL message is sent to the focus window when the mouse wheel is rotated.

	*Rotate* indicates the distance the wheel is rotated, expressed in multiples or
	divisions of WHEEL_DELTA, which is 120. A positive value indicates that the wheel was rotated
	forward, away from the user; a negative value indicates that the wheel was rotated backward,
	toward the user.
	*/
	// return false if message not handled by this route
	return false;
};

bool clsHGOWindow::DoParentNotify(int wmEvent, int wmId, LPARAM lParam) {
	/*
	The WM_PARENTNOTIFY message is sent to the parent of a child window when the child window
	is created or destroyed, or when the user clicks a mouse button while the cursor is over
	the child window. When the child window is being created, the system sends WM_PARENTNOTIFY
	just before the CreateWindow or CreateWindowEx function that creates the window returns.
	When the child window is being destroyed, the system sends the message before any processing
	to destroy the window takes place.
	*/
	/*
	wmEvent is low-order of wparam
	wmId    is high-order of wparam
	The value of wmId and lParam depends on wmEvent
	*/

	switch (wmEvent) {
	case WM_CREATE:
		OutputDebugStringA("-WM_CREATE\n");
		break;
	case WM_DESTROY:
		OutputDebugStringA("-WM_DESTROY\n");
		break;
	case WM_LBUTTONDOWN:
		OutputDebugStringA("-WM_LBUTTONDOWN\n");
		break;
	case WM_RBUTTONDOWN:
		OutputDebugStringA("-WM_RBUTTONDOWN\n");
		break;
	case WM_MBUTTONDOWN:
		OutputDebugStringA("-WM_MBUTTONDOWN\n");
		break;
	case WM_XBUTTONDOWN:
		OutputDebugStringA("-WM_XBUTTONDOWN\n");
		break;
	default:
		OutputDebugStringA("-Unknown\n");
	};

	return false; // return false if message not handled by this route
};

bool clsHGOWindow::DoUser(UINT message, WPARAM wParam, LPARAM lParam) {
	/*
	The WM_USER constant is used by applications to help define private messages for
	use by private window classes, usually of the form WM_USER+X, where X is an integer value.

	Message numbers in the second range (WM_USER through 0x7FFF) can be defined and used
	by an application to send messages within a private window class. These values cannot
	be used to define messages that are meaningful throughout an application, because
	some predefined window classes already define values in this range. For example,
	predefined control classes such as BUTTON, EDIT, LISTBOX, and COMBOBOX may use these
	values. Messages in this range should not be sent to other applications unless the
	applications have been designed to exchange messages and to attach the same meaning
	to the message numbers.

	*/
	// return false if message not handled by this route
	return false;
};

bool clsHGOWindow::DoApp(UINT message, WPARAM wParam, LPARAM lParam) {
	/*
	The WM_APP constant is used by applications to help define private messages,
	usually of the form WM_APP+X, where X is an integer value.

	Message numbers in the third range (0x8000 through 0xBFFF) are available
	for application to use as private messages. Message in this range do not
	conflict with system messages.
	*/

	// return false if message not handled by this route
	return false;
};

HBRUSH clsHGOWindow::DoCtlColor(UINT message, HDC hDC, HWND hCtl) {
	/*
	A static control, or an edit control that is read-only or disabled,
	sends the WM_CTLCOLORSTATIC message to its parent window when the control
	is about to be drawn. By responding to this message, the parent window can
	use the specified device context handle to set the text and background
	colors of the static control.
	*/
	/*
	The WM_CTLCOLORBTN message is sent to the parent window of a button before
	drawing the button. The parent window can change the button's text and
	background colors. However, only owner-drawn buttons respond to the parent
	window processing this message.
	*/
	/*
	If an application processes this message, the return value is a handle to a
	brush that the system uses to paint the background of the static control.
	*/
	// example:
	//SetBkColor(hDC, RGB(230,0,0)); 
	//SetBkMode(hDC, TRANSPARENT);
	//SetTextColor(hDC, RGB(0,0,0));
	//return GetSysColorBrush(COLOR_WINDOW);

	// return 0 if message not handled by this route
	return 0;
};

int clsHGOWindow::DoScroll(UINT message, int wmScrollRequest, int wmScrollPosition, LPARAM lParam) {
	/*
	The WM_HSCROLL message is sent to a window when a scroll event occurs in the window's
	standard horizontal scroll bar. This message is also sent to the owner of a horizontal
	scroll bar control when a scroll event occurs in the control.

	The WM_VSCROLL message is sent to a window when a scroll event occurs in the window's
	standard vertical scroll bar. This message is also sent to the owner of a vertical scroll
	bar control when a scroll event occurs in the control.
	message is:
	WM_VSCROLL
	WM_HSCROLL
	wmScrollRequest is:
	SB_BOTTOM		Scrolls to the lower right.
	SB_ENDSCROLL	Ends scroll.
	SB_LINEDOWN		Scrolls one line down.
	SB_LINEUP		Scrolls one line up.
	SB_PAGEDOWN		Scrolls one page down.
	SB_PAGEUP		Scrolls one page up.
	SB_THUMBPOSITION	The user has dragged the scroll box (thumb) and released the mouse
	button. The high-order word indicates the position of the scroll box
	at the end of the drag operation.
	SB_THUMBTRACK	The user is dragging the scroll box. This message is sent repeatedly until
	the user releases the mouse button. The high-order word indicates the
	position that the scroll box has been dragged to.
	SB_TOP			Scrolls to the upper left.
	SB_LEFT			Scrolls to the upper left.
	SB_RIGHT		Scrolls to the lower right.
	SB_LINELEFT		Scrolls left by one unit.
	SB_LINERIGHT	Scrolls right by one unit.
	SB_PAGELEFT		Scrolls left by the width of the window.
	SB_PAGERIGHT	Scrolls right by the width of the window.

	wmScrollPosition is:
	specifies the current position of the scroll box if the low-order word is SB_THUMBPOSITION
	or SB_THUMBTRACK; otherwise, this word is not used.

	*/
	// If an application processes this message, it should return 0
	int hPos, vPos;

	if (bHScrollBar && message == WM_HSCROLL) {
		// Get all the vertial scroll bar information
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_ALL;
		// Save the position for comparison later on
		GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo);
		hPos = ScrollInfo.nPos;
		switch (wmScrollRequest) {
			// user clicked left arrow
		case SB_LINELEFT:
			ScrollInfo.nPos -= iHScrollUnit;
			break;

			// user clicked right arrow
		case SB_LINERIGHT:
			ScrollInfo.nPos += iHScrollUnit;
			break;

			// user clicked the scroll bar shaft left of the scroll box
		case SB_PAGELEFT:
			ScrollInfo.nPos -= ScrollInfo.nPage;
			break;

			// user clicked the scroll bar shaft right of the scroll box
		case SB_PAGERIGHT:
			ScrollInfo.nPos += ScrollInfo.nPage;
			break;

			// user dragged the scroll box
		case SB_THUMBTRACK:
			ScrollInfo.nPos = ScrollInfo.nTrackPos;
			break;

		default:
			break;
		};
		// Set the position and then retrieve it.  Due to adjustments
		//   by Windows it may not be the same as the value set.
		ScrollInfo.fMask = SIF_POS;
		SetScrollInfo(hWnd, SB_HORZ, &ScrollInfo, TRUE);
		GetScrollInfo(hWnd, SB_HORZ, &ScrollInfo);

		// If the position has changed, scroll the window 
		if (ScrollInfo.nPos != hPos) {
			ScrollWindow(hWnd, /*iHScrollUnit * */ (hPos - ScrollInfo.nPos), 0, NULL, NULL);
			//		  UpdateWindow (hWnd);
		};
		return 0;
	};

	if (bVScrollBar && message == WM_VSCROLL) {
		// Get all the vertial scroll bar information
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_ALL;
		GetScrollInfo(hWnd, SB_VERT, &ScrollInfo);
		// Save the position for comparison later on
		vPos = ScrollInfo.nPos;
		switch (wmScrollRequest) {
			// user clicked the HOME keyboard key
		case SB_TOP:
			ScrollInfo.nPos = ScrollInfo.nMin;
			break;

			// user clicked the END keyboard key
		case SB_BOTTOM:
			ScrollInfo.nPos = ScrollInfo.nMax;
			break;

			// user clicked the top arrow
		case SB_LINEUP:
			ScrollInfo.nPos -= iVScrollUnit;
			break;

			// user clicked the bottom arrow
		case SB_LINEDOWN:
			ScrollInfo.nPos += iVScrollUnit;
			break;

			// user clicked the scroll bar shaft above the scroll box
		case SB_PAGEUP:
			ScrollInfo.nPos -= ScrollInfo.nPage;
			break;

			// user clicked the scroll bar shaft below the scroll box
		case SB_PAGEDOWN:
			ScrollInfo.nPos += ScrollInfo.nPage;
			break;

			// user dragged the scroll box
		case SB_THUMBTRACK:
			ScrollInfo.nPos = ScrollInfo.nTrackPos;
			break;

		default:
			break;
		};
		// Set the position and then retrieve it.  Due to adjustments
		//   by Windows it may not be the same as the value set.
		ScrollInfo.fMask = SIF_POS;
		SetScrollInfo(hWnd, SB_VERT, &ScrollInfo, TRUE);
		GetScrollInfo(hWnd, SB_VERT, &ScrollInfo);
		// If the position has changed, scroll window and update it
		if (ScrollInfo.nPos != vPos) {
			ScrollWindow(hWnd, 0, /*iVScrollUnit * */ (vPos - ScrollInfo.nPos), NULL, NULL);
			UpdateWindow(hWnd);
		};
		return 0;
	};
	return 1;
};

bool clsHGOWindow::DoDrawItem(int iCtlID, LPDRAWITEMSTRUCT pDrawItemStruct) {
	/*
	The WM_DRAWITEM message is sent to the parent window of an owner-drawn button,
	combo box, list box, or menu when a visual aspect of the button, combo box, list
	box, or menu has changed.
	*/
	/*
	iCtlID:	Specifies the identifier of the control that sent the WM_DRAWITEM message.
	If the message was sent by a menu, this parameter is zero.
	pDrawItemStruct:	Pointer to a DRAWITEMSTRUCT structure containing information
	about the item to be drawn and the type of drawing required.
	*/

	/* example owner drawn button
	if (!pDrawItemStruct) { // something wrong here
	return false;
	};
	if (pDrawItemStruct->CtlType!=ODT_BUTTON) { // only doing buttons
	return false;
	};

	iLength = SendMessage(pDrawItemStruct->hwndItem, WM_GETTEXT, sizeof(czButtonText), (LPARAM)czButtonText);
	original=SelectObject(pDrawItemStruct->hDC,GetStockObject(DC_PEN));

	if (ODS_SELECTED & pDrawItemStruct->itemState) { // ie. clicked
	rButtonDown=pDrawItemStruct->rcItem;
	DrawText(pDrawItemStruct->hDC,czButtonText,-1,&(pDrawItemStruct->rcItem),DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	DrawEdge(pDrawItemStruct->hDC,&(pDrawItemStruct->rcItem),EDGE_SUNKEN,BF_RECT);
	} else {
	DrawText(pDrawItemStruct->hDC,czButtonText,-1,&(pDrawItemStruct->rcItem),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawEdge(pDrawItemStruct->hDC,&(pDrawItemStruct->rcItem),EDGE_RAISED,BF_RECT);
	};
	SelectObject(pDrawItemStruct->hDC,original);
	return true;

	*/

	// If an application processes this message, it should return TRUE.
	return false;
};

// set FileName[0]=0 to not use contents to initialize itself
// if Filter==0 then "Text\0*.TXT\0All\0*.*\0" will be used
bool clsHGOWindow::GetOpenFile(char* FileName, int iBufferSize, char* Filter) {
	OPENFILENAME ofRec;
	char czDefaultFilter[] = "Text\0*.TXT\0All\0*.*\0\0";	// the final \0 may be already included since this is definded as a string.
	ZeroMemory(&ofRec, sizeof(ofRec));
	ofRec.lStructSize = sizeof(ofRec);
	ofRec.hwndOwner = hWnd;
	ofRec.lpstrFile = FileName; // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
								// use the contents of szFile to initialize itself.
	ofRec.nMaxFile = iBufferSize;
	if (Filter) {
		ofRec.lpstrFilter = Filter;
	} else {
		ofRec.lpstrFilter = &czDefaultFilter[0];
	};
	ofRec.nFilterIndex = 1;			// first item in filter will be selected
	ofRec.lpstrFileTitle = NULL;
	ofRec.nMaxFileTitle = 0;
	ofRec.lpstrInitialDir = NULL;
	ofRec.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofRec) != 0) {
		return true;
	} else {
		return false;
	};
};

// set FileName[0]=0 to not use contents to initialize itself
// if Filter==0 then "Text\0*.TXT\0All\0*.*\0" will be used
bool clsHGOWindow::GetSaveFile(char* FileName, int iBufferSize, char* Filter) {
	OPENFILENAME ofRec;
	char czDefaultFilter[] = "Text\0*.TXT\0All\0*.*\0\0";
	char czDefaultExt[] = "txt";
	ZeroMemory(&ofRec, sizeof(ofRec));
	ofRec.lStructSize = sizeof(ofRec);
	ofRec.hwndOwner = hWnd;
	ofRec.lpstrFile = FileName; // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
								// use the contents of szFile to initialize itself.
	ofRec.nMaxFile = iBufferSize;
	if (Filter) {
		ofRec.lpstrFilter = Filter;
	} else {
		ofRec.lpstrFilter = &czDefaultFilter[0];
	};
	ofRec.nFilterIndex = 1;			// first item in filter will be selected
	ofRec.lpstrFileTitle = NULL;
	ofRec.nMaxFileTitle = 0;
	ofRec.lpstrInitialDir = NULL;
	ofRec.Flags = OFN_OVERWRITEPROMPT;
	ofRec.lpstrDefExt = &czDefaultExt[0];

	if (GetSaveFileName(&ofRec) != 0) {
		return true;
	} else {
		return false;
	};
};

// Is this window even partically visible?
bool clsHGOWindow::IsWindowVisible() {
	HDC  hDC;
	RECT rRect;

	bWindowVisibleLastCheck = true;
	if (IsIconic(hWnd)) {
		bWindowVisibleLastCheck = false;
	} else {
		hDC = GetDC(hWnd);
		if (NULLREGION == GetClipBox(hDC, &rRect)) {
			bWindowVisibleLastCheck = false;
		};
		ReleaseDC(hWnd, hDC);
	};

	return bWindowVisibleLastCheck;
};

// since IsWindowVisible can be cpu intensive. if you need to check alot in a loop use this instead.
// after doing IsWindowVisible() once.
bool clsHGOWindow::WasWindowVisible() {
	return bWindowVisibleLastCheck;
};
