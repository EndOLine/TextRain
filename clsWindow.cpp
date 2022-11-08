#include "clsWindow.h"

// call back function for input modal dialog
char czIDC_Width[80] = "";
char czIDC_Height[80] = "";
char czIDC_TTL[80] = "";
char czIDC_DropRed[80] = "";
char czIDC_DropGreen[80] = "";
char czIDC_DropBlue[80] = "";
char czIDC_TailRed[80] = "";
char czIDC_TailGreen[80] = "";
char czIDC_TailBlue[80] = "";
char czIDC_BackRed[80] = "";
char czIDC_BackGreen[80] = "";
char czIDC_BackBlue[80] = "";
char czIDC_Refresh[80] = "";
char czIDC_NewDrip[80] = "";

BOOL CALLBACK DialogProcInput1(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		
		// limit text box sizes
		SendMessage(GetDlgItem(hwndDlg, IDC_Width), EM_LIMITTEXT, 5, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_Height), EM_LIMITTEXT, 5, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_TTL), EM_LIMITTEXT, 5, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_DropRed), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_DropGreen), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_DropBlue), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_TailRed), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_TailGreen), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_TailBlue), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_BackRed), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_BackGreen), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_BackBlue), EM_LIMITTEXT, 3, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_REFRESH), EM_LIMITTEXT, 4, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_NewDrip), EM_LIMITTEXT, 4, 0);
		// initilize text boxes
		SetDlgItemText(hwndDlg, IDC_Width, czIDC_Width);
		SetDlgItemText(hwndDlg, IDC_Height, czIDC_Height);
		SetDlgItemText(hwndDlg, IDC_TTL, czIDC_TTL);
		SetDlgItemText(hwndDlg, IDC_DropRed, czIDC_DropRed);
		SetDlgItemText(hwndDlg, IDC_DropGreen, czIDC_DropGreen);
		SetDlgItemText(hwndDlg, IDC_DropBlue, czIDC_DropBlue);
		SetDlgItemText(hwndDlg, IDC_TailRed, czIDC_TailRed);
		SetDlgItemText(hwndDlg, IDC_TailGreen, czIDC_TailGreen);
		SetDlgItemText(hwndDlg, IDC_TailBlue, czIDC_TailBlue);
		SetDlgItemText(hwndDlg, IDC_BackRed, czIDC_BackRed);
		SetDlgItemText(hwndDlg, IDC_BackGreen, czIDC_BackGreen);
		SetDlgItemText(hwndDlg, IDC_BackBlue, czIDC_BackBlue);
		SetDlgItemText(hwndDlg, IDC_REFRESH, czIDC_Refresh);
		SetDlgItemText(hwndDlg, IDC_NewDrip, czIDC_NewDrip);
		// order tabs: (implement backwards;  ie. last tab first)
		SetWindowPos(GetDlgItem(hwndDlg, IDC_NewDrip), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_REFRESH), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_BackBlue), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_BackGreen), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_BackRed), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_TailBlue), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_TailGreen), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_TailRed), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_DropBlue), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_DropGreen), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_DropRed), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_TTL), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_Height), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_Width), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//
		return true;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hwndDlg, IDC_Width, czIDC_Width, 80);
			GetDlgItemText(hwndDlg, IDC_Height, czIDC_Height, 80);
			GetDlgItemText(hwndDlg, IDC_TTL, czIDC_TTL, 80);
			GetDlgItemText(hwndDlg, IDC_DropRed, czIDC_DropRed, 80);
			GetDlgItemText(hwndDlg, IDC_DropGreen, czIDC_DropGreen, 80);
			GetDlgItemText(hwndDlg, IDC_DropBlue, czIDC_DropBlue, 80);
			GetDlgItemText(hwndDlg, IDC_TailRed, czIDC_TailRed, 80);
			GetDlgItemText(hwndDlg, IDC_TailGreen, czIDC_TailGreen, 80);
			GetDlgItemText(hwndDlg, IDC_TailBlue, czIDC_TailBlue, 80);
			GetDlgItemText(hwndDlg, IDC_BackRed, czIDC_BackRed, 80);
			GetDlgItemText(hwndDlg, IDC_BackGreen, czIDC_BackGreen, 80);
			GetDlgItemText(hwndDlg, IDC_BackBlue, czIDC_BackBlue, 80);
			GetDlgItemText(hwndDlg, IDC_REFRESH, czIDC_Refresh, 80);
			GetDlgItemText(hwndDlg, IDC_NewDrip, czIDC_NewDrip, 80);
			// Fall through. 

		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
		}
	}
	return FALSE;
}

bool clsWindow::DoCreate(HWND hInitWnd, LPCREATESTRUCT pCreateStructer) {
	/*
	The WM_CREATE message is sent when an application requests that a window be created
	by calling the CreateWindowEx or CreateWindow function. (The message is sent before
	the function returns.) The window procedure of the new window receives this message
	after the window is created, but before the window becomes visible.
	*/

	srand(101);
	SetClientSize(PixelXsize, PixelYsize);
	SetupTimer(RefreshRate);
	return true;
};

bool clsWindow::DoButtonUp(UINT ButtonMessage, WPARAM wParam, int X, int Y) {
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
	if (ButtonMessage == WM_LBUTTONUP) {
		UpdateSwapBuffer();
		InvalidateRect(hWnd, NULL, FALSE);
		return true;
	};
	return false; // return false if message not handled by this route
}


void clsWindow::SetSwapBufferSize(const int iWidth, const int iHeight) {
	
	SelectObject(SwapDC, hOrigfont);
	SelectObject(SwapDC, OrigObject);		// restore original before delete
	DeleteObject(SwapBM);
	DeleteDC(SwapDC);
	PixelXsize = iWidth;
	PixelYsize = iHeight;

	auto hDC = GetDC(hWnd);

	SwapDC = CreateCompatibleDC(hDC);
	SwapBM = CreateCompatibleBitmap(hDC, PixelXsize, PixelYsize);
	OrigObject = SelectObject(SwapDC, SwapBM);
	hOrigfont = (HFONT)SelectObject(SwapDC, hCurrentfont);

	// get text dimensions
	TEXTMETRIC tm;
	GetTextMetrics(SwapDC, &tm);
	LineWidth = iWidth / tm.tmMaxCharWidth;
	NbrLines = iHeight / tm.tmHeight;
	BufferSize = LineWidth * NbrLines;

	// create text matrix
	if (pTextMatrix != 0) {
		delete[] pTextMatrix;
		pTextMatrix = 0;
	};
	pTextMatrix = new unsigned char[BufferSize];

	// create time to live matrix
	if (pTextMatrixTTL != 0) {
		delete[] pTextMatrixTTL;
		pTextMatrixTTL = 0;
	};
	pTextMatrixTTL = new int[BufferSize];

	// initialize matrix
	for (int i = 0; i < BufferSize; ++i){
		pTextMatrixTTL[i] = 0;
		pTextMatrix[i] = 0;
	}
	
	ReleaseDC(hWnd, hDC);
}

void clsWindow::CopySwapBuffer(HDC DsthDC) {
	auto BitBltResult = BitBlt(DsthDC, 0, 0, PixelXsize, PixelYsize, SwapDC, 0, 0, SRCCOPY);
	auto error = GetLastError();
	if ((error != 0)|| (BitBltResult==0)) {
		char Message[80] = "";
		GetLastErrorMessage(error,Message,sizeof(Message));
		OutputDebugString(" Error: ");
		OutputDebugString(Message);
		OutputDebugString("\n");
	}
}

void clsWindow::DeleteSwapBuffer() {
	SelectObject(SwapDC, hOrigfont);
	SelectObject(SwapDC, OrigObject);		// restore original before delete
	DeleteObject(SwapBM);
	DeleteDC(SwapDC);
	if (pTextMatrix != 0) {
		delete[] pTextMatrix;
		pTextMatrix = 0;
	};
	if (pTextMatrixTTL != 0) {
		delete[] pTextMatrixTTL;
		pTextMatrixTTL = 0;
	}
}

bool clsWindow::UpdateSwapBuffer() {
	bool SomeThingToDraw = false;
	// clear swap buffer
	HBRUSH hbrush = CreateSolidBrush(RGB(Back.Red, Back.Green, Back.Blue));		// window colour -- dont forget to delete hbrush
	RECT rect = { 0,0,PixelXsize,PixelYsize};			// set rectangle to window's dimensions
	FillRect(SwapDC, &rect, hbrush);					// fill window with colour

	SetBkColor(SwapDC, RGB(Back.Red, Back.Green, Back.Blue));

	// get text dimensions
	TEXTMETRIC tm;
	GetTextMetrics(SwapDC, &tm);
	
	// add new drip 
	if (!StopRain) {
		for (int x = 0; x < LineWidth; ++x) {
			if (pTextMatrix[x] == 0) {
				int temp = rand() % 1000;
				if (temp < NewDripChance) {			// Chance in a thousand
					pTextMatrix[x] = (rand() % ('~' - ' ')) + 1 + ' ';
					pTextMatrixTTL[x] = StartTTL;
				};
			};
		};
	};
	
	// update swap DC from the text matrix
	unsigned char Temp[2] = " ";
	for (int x = 0; x < LineWidth; ++x) {
		for (int y = 0; y < NbrLines; ++y) {
			if ((Index(x , y) >= BufferSize) || (Index(x, y) < 0)) {
				break; // error
			}
			Temp[0] = pTextMatrix[Index(x, y)];
			if (Temp[0] != 0) {
				if (pTextMatrixTTL[Index(x, y)] == StartTTL) {
					SetTextColor(SwapDC, RGB(Drop.Red, Drop.Green, Drop.Blue));
				} else {
					float fScale =1.0f - ((float)pTextMatrixTTL[Index(x, y)] / (float)StartTTL);
					stColour ScaledColour = { Tail.Red - ((Tail.Red - Back.Red) * fScale),
											Tail.Green - ((Tail.Green - Back.Green) * fScale),
											Tail.Blue - ((Tail.Blue - Back.Blue) * fScale) };
					SetTextColor(SwapDC, RGB(ScaledColour.Red, ScaledColour.Green, ScaledColour.Blue));
				};
				TextOut(SwapDC, tm.tmMaxCharWidth * x, tm.tmHeight * y, (LPCSTR)&Temp, 1);
				SomeThingToDraw = true;
				--pTextMatrixTTL[Index(x, y)];
				if (pTextMatrixTTL[Index(x, y)] == 0) {
					pTextMatrix[Index(x, y)] = 0;
				};
			};
		};
	};

	// move drip down screen
	for (int x = 0; x < LineWidth; ++x) {
		for (int y = NbrLines-1; y > 0; --y) {
			if (pTextMatrix[Index(x, y)]==0) {
				if (pTextMatrix[Index(x, y-1)] != 0) {
					pTextMatrix[Index(x, y)] = (rand() % ('~' - ' ')) + 1 + ' ';
					pTextMatrixTTL[Index(x, y)] = StartTTL;
				}
			}
		}
	};
	DeleteObject(hbrush);		// make sure to delete brush when not used
	return SomeThingToDraw;
}

// since I'm using a one dimensional array for a two dimensional array, 
// need to convert [x,y] into an index for the one dimensional array.
// And because I'm doing this the HARD way, I should correct for possible errors.
int clsWindow::Index(const int x, const int y) {
	int index = 0;
	int col = x, row = y;
	if (x >= LineWidth) {
		col = LineWidth - 1;
	};
	if (y >= NbrLines) {
		row = NbrLines - 1;
	};

	index = col + row * LineWidth;
	if (index < 0) {
		index = 0;
	} else if (index >= BufferSize) {
		index = BufferSize - 1;
	};
	return index;
}

void clsWindow::WindowsFullScreenToggle() {
	// from https://devblogs.microsoft.com/oldnewthing/20100412-00/?p=14353
	static WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
	static HMENU hMenu = {};
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	if (dwStyle & WS_OVERLAPPEDWINDOW) {
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(hWnd, &g_wpPrev) &&
			GetMonitorInfo(MonitorFromWindow(hWnd,
				MONITOR_DEFAULTTOPRIMARY), &mi)) {
			hMenu = GetMenu(hWnd);
			SetWindowLong(hWnd, GWL_STYLE,
				dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(hWnd, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			SetMenu(hWnd, NULL);
		}
	} else {
		SetWindowLong(hWnd, GWL_STYLE,
			dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hWnd, &g_wpPrev);
		SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		SetMenu(hWnd, hMenu);
	};
}

bool clsWindow::DoPaint(HDC hdc) {
	/*
	The WM_PAINT message is sent when the system or another application makes a request
	to paint a portion of an application's window.
	*/
	//RECT Rect;
	if (bSizingWindow) return true;
	if (hdc == NULL) {
		auto error = GetLastError();
		OutputDebugString(" Error: no display device context is available\n");
		char Message[80] = "";
		GetLastErrorMessage(error, Message, sizeof(Message));
		OutputDebugString(" Error: ");
		OutputDebugString(Message);
		OutputDebugString("\n");
		return  true;
	};

	CopySwapBuffer(hdc);

	return true;
}
void clsWindow::DoSizeMove(UINT message) {
	//	message is either WM_ENTERSIZEMOVE or WM_EXITSIZEMOVE
	if (message == WM_ENTERSIZEMOVE) {
		bSizingWindow = true;
	} else if (message == WM_EXITSIZEMOVE) {
		bSizingWindow = false;
	};
}

bool clsWindow::DoSize(WPARAM wParam, int wmHeight, int wmWidth) {
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

	PixelXsize = wmWidth;
	PixelYsize = wmHeight;
	InvalidateRect(hWnd, NULL, FALSE);
	SetClientSize(PixelXsize, PixelYsize);
	SetSwapBufferSize(PixelXsize, PixelYsize);
	//
	return true;
};

bool clsWindow::DoKeyDown(WPARAM wParam, LPARAM lParam) {

	switch (wParam) {
	case 'P':
		PostMessage(hWnd, WM_COMMAND, IDM_PAUSE, 0);
		break;
	case 'S':
		PostMessage(hWnd, WM_COMMAND, IDM_STOP, 0);
		break;
	case 'R':
		PostMessage(hWnd, WM_COMMAND, IDM_RESTART, 0);
		break;
	case VK_ESCAPE:
		WindowsFullScreenToggle();
		break;
	};
	return true;
}


void clsWindow::GetLastErrorMessage(DWORD LastError, char* poBuffer, int BufferSize) {
	if (BufferSize <= 0) {
		return;
	};
	DWORD CharCount;
	CharCount = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, 
		LastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		poBuffer,
		BufferSize,
		NULL);
	if (CharCount == 0) {
		// I never know what to do when an error handling routine has an error.
		// at least during debug it will print a message.
		DWORD FormatError = GetLastError();
		char czIntValue[10] = "";
		OutputDebugStringA(" REALLY!!!! another error: ");
		OutputDebugStringA(_itoa(FormatError, czIntValue, sizeof(czIntValue)));
		OutputDebugStringA("\n");
	}
}



// example from "https://docs.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box"
//				"https://docs.microsoft.com/en-us/windows/win32/shell/common-file-dialog#ifiledialog-ifileopendialog-and-ifilesavedialog"
bool clsWindow::GetFileSaveName(char* pFilePath, int iPathBufferSize) {
	bool bPathFound = false;

	COMDLG_FILTERSPEC FileTypes[] = {
		{ L"Portable Pixmap Format", L"*.ppm" },
		{ L"All files", L"*.*" }
	};

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileSaveDialog* pFileSave;
		// create the FileSave	CLSID_FileSaveDialog  IID_IFileSaveDialog
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

		pFileSave->SetFileTypes(_countof(FileTypes), FileTypes);	// allow selection of these file types
		pFileSave->SetDefaultExtension(L"ppm");						// set default extension on return. can be multiple seperated by ; L"doc;docx"
		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileSave->Show(hWnd);								// setting handle to owner blocks use of menu. Timer still works.

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileSave->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;

					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						std::wcstombs(pFilePath, pszFilePath, 100);
						bPathFound = true;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileSave->Release();
		}
		CoUninitialize();
	}
	return bPathFound;
}

bool clsWindow::GetFolderSaveName(char* pFolderPath, int iPathBufferSize) {
	bool bPathFound = false;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen=0;
		
		// create the FileSave	CLSID_FileSaveDialog  IID_IFileSaveDialog
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		pFileOpen->SetOptions(FOS_PICKFOLDERS | FOS_PATHMUSTEXIST); // for picking folders only
		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(hWnd);								// setting handle to owner blocks use of menu. Timer still works.

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFolderPath;

					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						std::wcstombs(pFolderPath, pszFolderPath, 100);
						bPathFound = true;
						CoTaskMemFree(pszFolderPath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return bPathFound;
}

// Portable Pixmap Format
// this was one of the simpler image formats to write to.
bool clsWindow::SavePPM(char* pFilePath, HDC hSaveDC) {
	COLORREF colour;
	std::ofstream  file;
	file.open(pFilePath, std::ios::out);
	if (!file) {
		MessageBox(hWnd, pFilePath, "Unable to open file", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	file << "P3" << "\n" << PixelXsize << " " << PixelYsize << "\n" << 255 << "\n";   // 255 is max value for each colour
	for (int y = 0; y < PixelYsize; y++) {
		for (int x = 0; x < PixelXsize; x++) {
			colour = GetPixel(hSaveDC, x, y);
			file << (int)GetRValue(colour) << " " << (int)GetGValue(colour) << " " << (int)GetBValue(colour) << "\n";
		};
	};

	file.close();
	return true;
}

void clsWindow::ChooseTextFont() {
	// from: https://learn.microsoft.com/en-us/windows/win32/dlgbox/using-common-dialog-boxes?redirectedfrom=MSDN
	CHOOSEFONT cf = {};            // common dialog box structure
	static LOGFONT lf;        // logical font structure
	static DWORD rgbCurrent;  // current text color
	//HFONT hfont;
	//DWORD rgbPrev;

	// Initialize CHOOSEFONT
	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof(cf);
	cf.hwndOwner = hWnd;
	cf.lpLogFont = &lf;
	cf.rgbColors = rgbCurrent;
	cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT; // | CF_EFFECTS;

	if (ChooseFont(&cf) == TRUE)
	{	
		DeleteObject(hCurrentfont);										// delete previous font
		hCurrentfont = CreateFontIndirect(cf.lpLogFont);				// need to save hfont for when swap is recreated
		//hOrigfont = (HFONT)SelectObject(SwapDC, hCurrentfont);			// this will cause a GDI object leak... needs to be cleaned up
		//rgbCurrent = cf.rgbColors;
		//rgbPrev = SetTextColor(SwapDC, rgbCurrent);			// not necessary
	}
}

void clsWindow::SerialSave(HWND hwndPB) {
	SaveThreadRunning = true;
	// setup for progress bar		// release version stops after 10 seconds ... window not responding... need worker thread?
	//RECT rcClient = {};  // Client area of parent window.
	//int cyVScroll = 0;  // Height of scroll bar arrow.
	//static HWND hwndPB = 0;    // Handle of progress bar. 

	//GetClientRect(hWnd, &rcClient);
	//cyVScroll = GetSystemMetrics(SM_CYVSCROLL);
	//hwndPB = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL,
	//	WS_CHILD | WS_VISIBLE, rcClient.left,
	//	rcClient.bottom - cyVScroll,
	//	rcClient.right, cyVScroll,
	//	hWnd, (HMENU)0, hAppInst, NULL);
	//SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, atoi(SSD_czFrameCount) - atoi(SSD_czEndRainCount)));
	//SendMessage(hwndPB, PBM_SETSTEP, (WPARAM)1, 0);

	//
	bool previousPause = PauseOutput;
	bool previousStopRain = StopRain;
	int FrameCount = atoi(SSD_czFrameCount);
	int EndRainCount = atoi(SSD_czEndRainCount);
	char FileName[120] = {};
	PauseOutput = true;
	OutputDebugString("Serial Save Start main loop\n");
	for (int i = 1; i <= FrameCount; ++i) {
		sprintf_s(FileName, sizeof(FileName), "%s\\%s%04i.ppm", SSD_czDirectory, SSD_czFilePrefix, i);
		if (!SavePPM(FileName, SwapDC)) {		// if unable to save then stop trying
			EndRainCount = 0;					// prevent stop rain on error
			break;
		};
		SendMessage(hwndPB, PBM_STEPIT, 0, 0);
		UpdateSwapBuffer();
	};
	for (int i = 1; i <= EndRainCount; ++i) {
		StopRain = true;
		sprintf_s(FileName, sizeof(FileName), "%s\\%s%04i.ppm", SSD_czDirectory, SSD_czFilePrefix, i + FrameCount);
		if (!SavePPM(FileName, SwapDC)) {		// if unable to save then stop trying
			break;
		}
		SendMessage(hwndPB, PBM_STEPIT, 0, 0);
		if (!UpdateSwapBuffer()) {			// if there is nothing to draw than stop
			break;
		}
	};
	ShowWindow(hwndPB, SW_HIDE);
	DestroyWindow(hwndPB);
	PauseOutput = previousPause;
	StopRain = previousStopRain;
	SaveThreadRunning = false;
	OutputDebugString("Serial Save End\n");
}

void clsWindow::MenuCreate() {
	HMENU hMenu, hSubMenu;
	if (!hWnd) return;
	hMenu = CreateMenu();
	hSubMenu = CreatePopupMenu();

	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9001, "&New\tCtl-N");
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9002, "&Open...\tCtl-O");
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9003, "&Save\tCtl-S");
	AppendMenu(hSubMenu, MF_STRING, IDM_SAVEAS, "Save &As...");
	AppendMenu(hSubMenu, MF_STRING, IDM_SERIALSAVE, "Serial Save As...");
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_EXIT, "E&xit");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

	hSubMenu = CreatePopupMenu();
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED | MF_CHECKED, 9011, "Undo\tCtl-Z");
	//AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9011, "&Copy\tCtl-C");
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9011, "Cu&t\tCtl-X");
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9011, "&Paste\tCtl-V");
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9011, "De&lete\tDel");
	//AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9011, "&Find...\tCtl-G");
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9011, "Find &Next\tF3");
	//AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, 9011, "&Replace...");
	AppendMenu(hSubMenu, MF_STRING, IDM_PROPERTIES, "&Properties...");
	AppendMenu(hSubMenu, MF_STRING, IDM_FONT, "Choose &Font...");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Edit");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, IDM_PAUSE, "&Pause\tP");
	AppendMenu(hSubMenu, MF_STRING, IDM_RESTART, "&Reset display\tR");
	AppendMenu(hSubMenu, MF_STRING, IDM_STOP, "&Stop rain\tS");
	AppendMenu(hSubMenu, MF_STRING, IDM_FULLSCREEN, "&Full Screen Toggle\tEsc");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Action");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, IDM_ABOUT, "&About");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");

	/*Resources associated with a menu that is assigned to a window are freed automatically.
	If the menu is not assigned to a window, an application must free system resources
	associated with the menu before closing. An application frees menu resources by calling
	the DestroyMenu function.*/
	SetMenu(hWnd, hMenu);
};



bool clsWindow::DoCommand(int wmId, int wmEvent, LPARAM lParam) {
	/*
	message is sent when the user selects a command item from a menu, when a control
	sends a notification message to its parent window, or when an accelerator keystroke
	is translated.
	*/
	/*
	wmEvent: 0 - Menu			(wmId = (Menu identifier (IDM_*))			(lParam = 0)
	1 - Accelerator	(wmId = (Accelerator identifier (IDM_*))	(lParam = 0)
	(Control-defined notification code) - Control
	(wmId = (Control identifier))				(lParan = (Handle to the control window) )
	*/

	// Parse the menu selections:
	//
	char FilePath[255] = "";
	bool bReturn = true;
	switch (wmId) {
	case IDM_EXIT:
		DestroyWindow(hWnd);
		bReturn = true;
		break;
	case IDM_SAVEAS:
		PauseOutput = true;
		//if (GetSaveFile(FilePath,sizeof(FilePath), (char *)&"Portable Pixmap Format\0*.ppm\0All\0*.*\0\0")) {		// this method is superseded 
		if (GetFileSaveName(FilePath, sizeof(FilePath))) {
			SavePPM(FilePath, SwapDC);
		};
		PauseOutput = MenuItemIsChecked(GetMenu(hWnd), IDM_PAUSE);
		bReturn = true;
		break;
	case IDM_SERIALSAVE:
		if (SSD_DialogBox(hAppInst, hWnd)) {
			OutputDebugString("Serial Save OK\n");
			if (!SaveThreadRunning) {
				// setup for progress bar		// release version stops after 10 seconds ... window not responding... need worker thread?
				RECT rcClient = {};  // Client area of parent window.
				int cyVScroll = 0;  // Height of scroll bar arrow.
				static HWND hwndPB = 0;    // Handle of progress bar. 

				GetClientRect(hWnd, &rcClient);
				cyVScroll = GetSystemMetrics(SM_CYVSCROLL);
				hwndPB = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL,
					WS_CHILD | WS_VISIBLE, rcClient.left,
					rcClient.bottom - cyVScroll,
					rcClient.right, cyVScroll,
					hWnd, (HMENU)0, hAppInst, NULL);
				SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, atoi(SSD_czFrameCount) + atoi(SSD_czEndRainCount)));
				SendMessage(hwndPB, PBM_SETSTEP, (WPARAM)1, 0);

				std::thread T0(&clsWindow::SerialSave, this, hwndPB);
				T0.detach();
				//SerialSave();
			};
/*			// setup for progress bar		// release version stops after 10 seconds ... window not responding... need worker thread?
			RECT rcClient = {};  // Client area of parent window.
			int cyVScroll=0;  // Height of scroll bar arrow.
			static HWND hwndPB=0;    // Handle of progress bar. 

			GetClientRect(hWnd, &rcClient);
			cyVScroll = GetSystemMetrics(SM_CYVSCROLL);
			hwndPB = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL,
				WS_CHILD | WS_VISIBLE, rcClient.left,
				rcClient.bottom - cyVScroll,
				rcClient.right, cyVScroll,
				hWnd, (HMENU)0, hAppInst, NULL);
			SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, atoi(SSD_czFrameCount)- atoi(SSD_czEndRainCount)));
			SendMessage(hwndPB, PBM_SETSTEP, (WPARAM)1, 0);
		
			//
			bool previousPause = PauseOutput;
			bool previousStopRain = StopRain;
			int FrameCount= atoi(SSD_czFrameCount);
			int EndRainCount = atoi(SSD_czEndRainCount);
			char FileName[120] = {};
			PauseOutput = true;
			
			for (int i = 1; i <= FrameCount; ++i) {
				sprintf_s(FileName, sizeof(FileName), "%s\\%s%04i.ppm", SSD_czDirectory, SSD_czFilePrefix, i);
				if (!SavePPM(FileName, SwapDC)) {		// if unable to save then stop trying
					EndRainCount = 0;					// prevent stop rain on error
					break;
				};
				SendMessage(hwndPB, PBM_STEPIT, 0, 0);
				UpdateSwapBuffer();
			};
			for (int i = 1; i <= EndRainCount; ++i) {
				StopRain = true;
				sprintf_s(FileName, sizeof(FileName), "%s\\%s%04i.ppm", SSD_czDirectory, SSD_czFilePrefix, i+ FrameCount);
				if (!SavePPM(FileName, SwapDC)) {		// if unable to save then stop trying
					break;
				}
				SendMessage(hwndPB, PBM_STEPIT, 0, 0);
				if (!UpdateSwapBuffer()) {			// if there is nothing to draw than stop
					break;
				}
			};
			DestroyWindow(hwndPB);
			PauseOutput = previousPause;
			StopRain = previousStopRain;
*/
		};
		break;
	case IDM_PROPERTIES:
		sprintf_s(czIDC_Width, sizeof(czIDC_Width), "%i", PixelXsize);
		sprintf_s(czIDC_Height, sizeof(czIDC_Height), "%i", PixelYsize);
		sprintf_s(czIDC_TTL, sizeof(czIDC_TTL), "%i", StartTTL);
		sprintf_s(czIDC_DropRed, sizeof(czIDC_DropRed), "%i", Drop.Red);
		sprintf_s(czIDC_DropGreen, sizeof(czIDC_DropGreen), "%i", Drop.Green);
		sprintf_s(czIDC_DropBlue, sizeof(czIDC_DropBlue), "%i", Drop.Blue);
		sprintf_s(czIDC_TailRed, sizeof(czIDC_TailRed), "%i", Tail.Red);
		sprintf_s(czIDC_TailGreen, sizeof(czIDC_TailGreen), "%i", Tail.Green);
		sprintf_s(czIDC_TailBlue, sizeof(czIDC_TailBlue), "%i", Tail.Blue);\
		sprintf_s(czIDC_BackRed, sizeof(czIDC_BackRed), "%i", Back.Red);
		sprintf_s(czIDC_BackGreen, sizeof(czIDC_BackGreen), "%i", Back.Green);
		sprintf_s(czIDC_BackBlue, sizeof(czIDC_BackBlue), "%i", Back.Blue);
		sprintf_s(czIDC_Refresh, sizeof(czIDC_Refresh), "%i", RefreshRate);
		sprintf_s(czIDC_NewDrip, sizeof(czIDC_NewDrip), "%i", NewDripChance);

		if (DialogBox(hAppInst, (LPCTSTR)IDD_PROPERTIES, hWnd, (DLGPROC)DialogProcInput1) == IDOK) {
			// do OK button action here
			PixelXsize = atoi(czIDC_Width);
			PixelYsize = atoi(czIDC_Height);
			StartTTL = atoi(czIDC_TTL);
			Drop.Red = atoi(czIDC_DropRed);
			Drop.Green = atoi(czIDC_DropGreen);
			Drop.Blue = atoi(czIDC_DropBlue);
			Tail.Red = atoi(czIDC_TailRed);
			Tail.Green = atoi(czIDC_TailGreen);
			Tail.Blue = atoi(czIDC_TailBlue);
			Back.Red = atoi(czIDC_BackRed);
			Back.Green = atoi(czIDC_BackGreen);
			Back.Blue = atoi(czIDC_BackBlue);
			RefreshRate = atoi(czIDC_Refresh);
			NewDripChance = atoi(czIDC_NewDrip);
			SetupTimer(RefreshRate);
			SetClientSize(PixelXsize, PixelYsize);
			SetSwapBufferSize(PixelXsize, PixelYsize);
			InvalidateRect(hWnd, NULL, FALSE);
		};
		bReturn = true;
		break;
	case IDM_FONT:
		ChooseTextFont();
		SetSwapBufferSize(PixelXsize, PixelYsize);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case IDM_PAUSE:
		if (PauseOutput) {
			CheckMenuItem(GetMenu(hWnd), IDM_PAUSE, MF_UNCHECKED);	// note that in full screen this may not work
			PauseOutput = false;
		} else {
			CheckMenuItem(GetMenu(hWnd), IDM_PAUSE, MF_CHECKED);	// note that in full screen this may not work
			PauseOutput = true;
		};
		bReturn = true;
		break;
	case IDM_RESTART:
		StopRain = false;
		for (int i = 0; i < BufferSize; ++i) {
			pTextMatrixTTL[i] = 0;
			pTextMatrix[i] = 0;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		bReturn = true;
		break;
	case IDM_STOP:
		if (StopRain){
			CheckMenuItem(GetMenu(hWnd), IDM_STOP, MF_UNCHECKED);	// note that in full screen this may not work
			StopRain = false;
		} else {
			CheckMenuItem(GetMenu(hWnd), IDM_STOP, MF_CHECKED);		// note that in full screen this may not work
			StopRain = true;
		};
		bReturn = true;
		break;
	case IDM_FULLSCREEN:
		WindowsFullScreenToggle();
		break;
	case IDM_ABOUT:
		MessageBox(hWnd, "Dynamic text rain display application", "About", MB_OK);
		bReturn = true;
	default:
		bReturn = false;
		break;
	};

	// return false if message not handled by this route
	return bReturn;
}
bool clsWindow::MenuItemIsChecked(HMENU hMenu, UINT iItem) {
	MENUITEMINFO mi = {0};
	bool bReturn = false;
	mi.cbSize = sizeof(MENUITEMINFO);
	mi.fMask = MIIM_STATE;
	bool result = GetMenuItemInfo(hMenu,iItem,false,&mi);
	bReturn = mi.fState & MFS_CHECKED;
	return bReturn;
}

bool clsWindow::DoTimer(UINT_PTR TimerID){
	if (PauseOutput) return true;
	UpdateSwapBuffer();
	InvalidateRect(hWnd, NULL, FALSE);
	return true;
};

/*
Run TaskMgr.exe, Programs tab, 
View + Select Columns and tick GDI Objects and USER32 Objects.  Your program will go belly-up 
when either column reaches 10,000.  Hurry that along by calling InvalidateRect() in 
a WM_TIMER handler so you don't have send breakpoints endlessly to force paint events.  
Oh, and *never* use a window handle in that thread, except for PostMessage()



You can track the GDI Objects per application through the Task Manager.

Start the Task Manager (right-click on Windows Taskbar to select Task Manager)
In Windows 10, go to the Details tab.  For Windows 7, go to the Processes tab.
Right-click on one of the column headers and ‘Select Columns’
Enable GDI Objects
Click on the GDI Object column header to sort in descending order

*/