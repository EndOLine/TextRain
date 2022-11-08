/********************************************************************
Prog: clsHGOapplication.cpp
Desc: Initialization routine for windows appllications

library: Version.lib
Log : 090617 - created
	  170204 - (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE) setup for win64
	  170205 - include PeekMessage() in the Run() loop for games.
			 - bWaitForMessage was added to the Run() parameter list
			 - DoRunning() was created
	  201011 - fixing various char * to const char *
********************************************************************/

#include "clsHGOapplication.h"
#include "clsHGOwindow.h"

// sample window for testing base class
clsHGOWindow* pSampleWindow = 0;

LRESULT CALLBACK clsHGOapplicationProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	// get user parameter which is a pointer to clsHGOWindow
	//clsHGOWindow *ptrclsMainWindow = (clsHGOWindow*)GetWindowLong(hWnd, GWL_USERDATA);		// replaced by win64...
	clsHGOWindow* ptrclsMainWindow = (clsHGOWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);


	if (message == WM_CREATE) { // if create add to list
								//		AddWindow(hWnd,(clsHGOWindow *)(((LPCREATESTRUCT)lParam)->lpCreateParams) );
		ptrclsMainWindow = (clsHGOWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		//SetWindowLong(hWnd, GWL_USERDATA, (LONG)ptrclsMainWindow);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ptrclsMainWindow);
	};
	//	ptrclsMainWindow=FindWindow(hWnd);

	// if the pointer is null assume it was not created by clsHGOWindows
	if (!ptrclsMainWindow) {
		return DefWindowProc(hWnd, message, wParam, lParam);
	};
	if (message == WM_DESTROY) {
		//		RemoveWindow(hWnd);
	};
	return ptrclsMainWindow->DoWindowProc(hWnd, message, wParam, lParam);
};


clsHGOapplication::clsHGOapplication() {
	czWindowClass = 0;
	czWindowTitle = 0;
	hAccelTable = 0;

	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)clsHGOapplicationProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	SetWindowClass("Default clsHGOapplication Class Name");
	SetWindowTitle("Default clsHGOapplication Title");

	czProgramName[0] = 0;
	czVersion[0] = 0;

};

clsHGOapplication::~clsHGOapplication() {
	Clear();
};
void clsHGOapplication::Clear() {
	if (czWindowClass) {
		delete[] czWindowClass;
		czWindowClass = 0;
	};
	if (czWindowTitle) {
		delete[] czWindowTitle;
		czWindowTitle = 0;
	};
};

// Main run loop. Inputs are parameters from  from WinMain(). If bWaitForMessage 
// the run GetMessage() else perform PeekMessage()
int clsHGOapplication::Run(HINSTANCE hInst, int nCmdShow, bool bWaitForMessage) {

	hAppInst = hInst;
	if (!DoInitilize()) {
		return -1;
	};
	wcex.hInstance = hAppInst;
	wcex.lpszClassName = czWindowClass;
	RegisterClassEx(&wcex);

	GetVersionStr(czVersion, sizeof(czVersion), czProgramName, sizeof(czProgramName));
	if (!DoBegin(nCmdShow)) {
		return -1;
	};

	// Main message loop:
	MSG msg;
	BOOL bRet;		// if > 0: normal,  == 0: quit,  == -1: error

	// if bWaitForMessage is true use GetMessage() that waits for a posted messsage.
	// this was separated into two similar loops just make the while loop faster.
	if (bWaitForMessage) {
		while ((bRet = GetMessage(&msg, NULL, 0, 0)) > 0) {
			if (bRet == -1) {
				// handle the error and possibly exit
				DoEnd();
				return (int)msg.wParam;
			}

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) { // could set up AccelTable for each windows.
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			};
			// allow for program to run non-windows processes
			if (!DoRunning()) {
				break;
			};
		};
	} else {
		while (true) {
			// don't wait for message. but process all outstanding windows messages
			while ((bRet = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) > 0) {
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) { // could set up AccelTable for each windows.
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				};
			};
			// if we got a QUIT then exit loop
			if (msg.message == WM_QUIT) {
				break;
			};
			// allow for program to run non-windows processes
			if (!DoRunning()) {
				break;
			};
		};
	};
	DoEnd();
	return (int)msg.wParam;
};

void clsHGOapplication::SetWindowClass(const char* ClassName) {
	if (czWindowClass) {
		delete[] czWindowClass;
		czWindowClass = 0;
	};
	if (!ClassName) return;
	czWindowClass = new char[strlen(ClassName) + 1];
	strcpy_s(czWindowClass, strlen(ClassName) + 1, ClassName);
};

char* clsHGOapplication::GetWindowClass() {
	return czWindowClass;
};

void clsHGOapplication::SetWindowTitle(const char* Title) {
	if (czWindowTitle) {
		delete[] czWindowTitle;
		czWindowTitle = 0;
	};
	if (!Title) return;
	czWindowTitle = new char[strlen(Title) + 1];
	strcpy_s(czWindowTitle, strlen(Title) + 1, Title);
};

void clsHGOapplication::SetAcceleratorID(int iID) {
	hAccelTable = LoadAccelerators(hAppInst, MAKEINTRESOURCE(iID));
};

HINSTANCE clsHGOapplication::GetAppInst() {
	return hAppInst;
};


bool clsHGOapplication::DoInitilize() {
	// example stuff to be initialized
	// this is called prior to creating the class and window
	/*
	// setting hIcon to null will send a wm_paint to window when IsIconic()
	// you can then draw the minimized icon yourself
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_INOUTCLIENT);
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	wcex.lpszMenuName	= (LPCTSTR)IDC_INOUTCLIENT;
	SetWindowClass("Default clsMainWindow Class Name");
	SetWindowTitle("Default clsMainWindow Title");

	hAccelTable=LoadAccelerators(hAppInst,(LPCTSTR) IDR_ACCELERATOR_CONSOLE);

	*/
	pSampleWindow = new clsHGOWindow;
	return true;
};

bool clsHGOapplication::DoBegin(int nCmdShow) {
	// called just prior to the main message loop
	// good place to create windows

	// sample window
	/*
	HWND hWnd;
	DWORD dwError;

	hWnd = CreateWindow(czWindowClass, czWindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hAppInst, NULL);
	if (!hWnd) {
		dwError = GetLastError();
		return false;
	}
	ShowWindow(hWnd, nCmdShow);
	*/
	// create a sample window
	if (pSampleWindow) {
		pSampleWindow->CreateTheWindow(this, "Sample Window");
		pSampleWindow->ShowTheWindow(nCmdShow);
		pSampleWindow->MenuTest();
	};

	return true; // false will terminate run
};

bool clsHGOapplication::DoRunning() {
	// called during a message loop. after processing windows commands
	// good place to place rendering code if Run( , , false).
	// With PeekMessage() this will also be called if idle

	if (pSampleWindow) {	// if SampleWindow is gone...
		if (!IsWindow(pSampleWindow->GethWnd())) return false;
	};

	return true;	// false will terminate run
};


void clsHGOapplication::DoEnd() {
	// called just after to the main message loop completes
	if (pSampleWindow) {
		delete pSampleWindow;
		pSampleWindow = 0;
	};
}
// create output only console for 64bit windows.
void clsHGOapplication::Create64Console(char* czConsoleName) {
	AllocConsole();

	errno_t	Result;
	//	HANDLE stdHandle;
	//	int hConsole;
	FILE* fp;
	//	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	if (czConsoleName) {
		SetConsoleTitle(czConsoleName);
	};
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

	Result = freopen_s(&fp, "CONOUT$", "w", stdout);

	//	stdHandle = GetStdHandle(STD_ERROR_HANDLE);
	//	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	Result = freopen_s(&fp, "CONOUT$", "w", stderr);
};


void clsHGOapplication::CreateAChildClass(char* ChildClassName) {
	WNDCLASSEX wcex;
	ATOM aReturn;

	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)clsHGOapplicationProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wcex.hInstance = hAppInst;
	wcex.lpszClassName = ChildClassName;
	aReturn = RegisterClassEx(&wcex);
};

//
// library: Version.lib
//
void clsHGOapplication::GetVersionStr(char* czVersion, int iVersionBuffer, char* czProgramName, int iProgramBuffer) {
	DWORD dwSize, dwHandle = 0;
	VS_FIXEDFILEINFO* lpFixedInfo;
	UINT  uiSize;
	char* pczPrgPath;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_get_pgmptr(&pczPrgPath);


	_splitpath_s(pczPrgPath, drive, sizeof(drive), dir, sizeof(dir), fname, sizeof(fname), ext, sizeof(ext));
	strcpy_s(czProgramName, iProgramBuffer, fname);
	if (strlen(ext) > 0) {
		strcat_s(czProgramName, iProgramBuffer, ext);
	};

	dwSize = GetFileVersionInfoSize(pczPrgPath, &dwHandle);
	if (dwSize > 0) {
		char* lpData = new char[dwSize];
		if (GetFileVersionInfo(pczPrgPath, dwHandle, dwSize, lpData)) {
			if (VerQueryValue(lpData, "\\", (LPVOID*)&lpFixedInfo, &uiSize)) {
				if (lpFixedInfo->dwFileVersionLS != 0) {
					sprintf_s(czVersion, iVersionBuffer, "%i.%i.%i.%i", lpFixedInfo->dwFileVersionMS >> 16, lpFixedInfo->dwFileVersionMS & 0xffff,
						lpFixedInfo->dwFileVersionLS >> 16, lpFixedInfo->dwFileVersionLS & 0xffff);
				} else {
					sprintf_s(czVersion, iVersionBuffer, "%i.%i", lpFixedInfo->dwFileVersionMS >> 16, lpFixedInfo->dwFileVersionMS & 0xffff);
				}
			};
#ifdef _DEBUG
			strcat_s(czVersion, iVersionBuffer, "(Debug)");
#endif
		};
		delete[] lpData;
	};
};
// does not work cannot send to console. might work for 32 bit apps.
/*
static const WORD MAX_CONSOLE_LINES = 500;
void clsHGOapplication::RedirectIOToConsole() {
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "w");

	*stdout = *fp;

	setvbuf(stdout, NULL, _IONBF, 0);

	// redirect unbuffered STDIN to the console

	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "w");

	*stderr = *fp;

	setvbuf(stderr, NULL, _IONBF, 0);

	fprintf(stdout, "testing out method\n");
	printf("testing from method\n");
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	//	ios::sync_with_stdio();
};
*/