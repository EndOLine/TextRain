/*
* File: SerialSaveDialog.cpp
* Description:
*	Creating a dialog to handle collecting information for performing a serial save of images
*   Note that this is an experiment to try this without a class
* Log:
*	20221107: Initial creation
*/
#include "SerialSaveDialog.h"
char SSD_czFilePrefix[80] = "Image";
char SSD_czFrameCount[80] = "300";
char SSD_czEndRainCount[80] = "0";
char SSD_czDirectory[80] = "c:\\temp";

BOOL CALLBACK SerialSaveDialogProcInput(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		// limit text box sizes
		SendMessage(GetDlgItem(hwndDlg, IDC_FILEPREFIX), EM_LIMITTEXT,80, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_FRAMECOUNT), EM_LIMITTEXT, 4, 0);
		SendMessage(GetDlgItem(hwndDlg, IDC_ENDRAINCOUNT), EM_LIMITTEXT, 4, 0);
		
		// initilize text boxes
		SetDlgItemText(hwndDlg, IDC_DIRECTORY, SSD_czDirectory);
		SetDlgItemText(hwndDlg, IDC_FILEPREFIX, SSD_czFilePrefix);
		SetDlgItemText(hwndDlg, IDC_FRAMECOUNT, SSD_czFrameCount);
		SetDlgItemText(hwndDlg, IDC_ENDRAINCOUNT, SSD_czEndRainCount);
		
		// order tabs: (implement backwards;  ie. last tab first)
		SetWindowPos(GetDlgItem(hwndDlg, IDC_ENDRAINCOUNT), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_FRAMECOUNT), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(GetDlgItem(hwndDlg, IDC_FILEPREFIX), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//
		return true;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hwndDlg, IDC_FILEPREFIX, SSD_czFilePrefix, 80);
			GetDlgItemText(hwndDlg, IDC_FRAMECOUNT, SSD_czFrameCount, 80);
			GetDlgItemText(hwndDlg, IDC_ENDRAINCOUNT, SSD_czEndRainCount, 80);
			// Fall through. 

		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
		case IDC_SELECTFOLDER:
			OutputDebugString("Serial Save Directory button\n");
			//char FolderName[80] = {};
			if (SSD_GetFolderSaveName(hwndDlg, SSD_czDirectory, sizeof(SSD_czDirectory))) {
				SetDlgItemText(hwndDlg, IDC_DIRECTORY, SSD_czDirectory);
			};
			break;
		}

	}
	return FALSE;
}

bool SSD_DialogBox(HINSTANCE hAppInst, HWND hWndParent) {
	return (DialogBox(hAppInst, (LPCTSTR)IDD_SERIALSAVE, hWndParent, (DLGPROC)SerialSaveDialogProcInput)==IDOK);
}


bool SSD_GetFolderSaveName(HWND hWndParent, char* pFolderPath, int iPathBufferSize) {
	bool bPathFound = false;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen = 0;

		// create the FileSave	CLSID_FileSaveDialog  IID_IFileSaveDialog
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		pFileOpen->SetOptions(FOS_PICKFOLDERS | FOS_PATHMUSTEXIST); // for picking folders only
		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(hWndParent);								// setting handle to owner blocks use of menu. Timer still works.

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
						wcstombs(pFolderPath, pszFolderPath, iPathBufferSize);
						size_t i;
						//wcstombs_s(i, pFolderPath, (size_t)iPathBufferSize, (const wchar_t *)pszFolderPath, (size_t)10);
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