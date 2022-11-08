#include "clsApp.h"


bool clsApp::DoInitilize() {
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
	wcex.hIcon = LoadIcon(hAppInst, (LPCTSTR)IDI_ICON1);
	wcex.hIconSm = LoadIcon(hAppInst, (LPCTSTR)IDI_ICON1);
	SetWindowClass("Falling Text Rain Class");
	SetWindowTitle("Falling Text Rain Title");
	SetAcceleratorID(IDR_ACCELERATOR1);
	pWindow = new clsWindow;
	return true;
};


bool clsApp::DoBegin(int nCmdShow) {
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

	if (pWindow) {
		pWindow->CreateTheWindow(this, "Text Rain");
		pWindow->ShowTheWindow(nCmdShow);
		pWindow->MenuCreate();
		pWindow->UpdateSwapBuffer();
	};


	return true; // false will terminate run
};

bool clsApp::DoRunning() {
	// called during a message loop. after processing windows commands
	// good place to place rendering code if Run( , , false).
	// With PeekMessage() this will also be called if idle

	if (pWindow) {	// if SampleWindow is gone...
		if (!IsWindow(pWindow->GethWnd())) return false;
	};

	return true;	// false will terminate run
};


void clsApp::DoEnd() {
	// called just after to the main message loop completes
	if (pWindow) {
		delete pWindow;
		pWindow = 0;
	};
}