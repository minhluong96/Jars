// Jars.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Jars.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_JARS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JARS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JARS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_JARS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, onCreate);
		HANDLE_MSG(hWnd, WM_PAINT, onPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, onDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, onCommand);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void onPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);

	SaveRect(hWnd);
}

void onDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}

BOOL onCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	LoadRect(hWnd);

	// Take system's font
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	HFONT bigFont = CreateFont(28, 10,0, 0, 0, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, TEXT("Arial"));
	HFONT myFont = CreateFont(18, 7, 0, 0, 700, 0, TRUE, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, TEXT("Arial"));
	
	//Create boxes
	HWND hwnd = CreateWindowEx(0, L"STATIC", L"JARS - System of money management", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 150, 20, 420, 80, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(bigFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Input money", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 150, 100, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(myFont), TRUE);

	input = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER, 300, 100, 300, 20, hWnd, NULL, hInst, NULL);
	SendMessage(input, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"BUTTON", L"Calculate", WS_CHILD | WS_VISIBLE | BS_CENTER, 300, 130, 100, 40, hWnd, (HMENU)IDC_BUTTON_1, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Necessities", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 30, 200, 150, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(myFont), TRUE);

	NEC = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER , 30, 230, 150, 30, hWnd, NULL, hInst, NULL);
	SendMessage(NEC, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Long Term Saving for Spending", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 200, 200, 300, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(myFont), TRUE);

	LTSS = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, 280, 230, 150, 30, hWnd, NULL, hInst, NULL);
	SendMessage(LTSS, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Play", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 530, 200, 150, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(myFont), TRUE);

	PLAY = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, 530, 230, 150, 30, hWnd, NULL, hInst, NULL);
	SendMessage(PLAY, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Education", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 30, 300, 150, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(myFont), TRUE);

	EDU = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, 30, 330, 150, 30, hWnd, NULL, hInst, NULL);
	SendMessage(EDU, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Financial Freedom Account", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 200, 300, 300, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(myFont), TRUE);

	FFA = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, 280, 330, 150, 30, hWnd, NULL, hInst, NULL);
	SendMessage(FFA, WM_SETFONT, WPARAM(hFont), TRUE);
	
	hwnd = CreateWindowEx(0, L"STATIC", L"Give to Charity", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 530, 300, 150, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(myFont), TRUE);

	GIVE = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_BORDER, 530, 330, 150, 30, hWnd, NULL, hInst, NULL);
	SendMessage(GIVE, WM_SETFONT, WPARAM(hFont), TRUE);

	return true;
}

void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;

	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case IDC_BUTTON_1:
		Count(hWnd);
		break;
	}
}

void Count(HWND hWnd)
{
	int size;
	long money;
	double temp;
	size = GetWindowTextLength(input);
	WCHAR *buff = new WCHAR[size + 1];
	GetWindowText(input, buff, size + 1);

	money = _wtoi(buff);
	delete []buff;

	if (money <= 0)
	{
		MessageBox(hWnd, L"Amount money must be positive", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	temp = money * 55 / 100;
	buff = new WCHAR[255];
	swprintf(buff, 255, L"%.1f", temp);
	SetWindowText(NEC, buff);
	
	temp = money * 10 / 100;
	swprintf(buff, 255, L"%.1f", temp);
	SetWindowText(LTSS, buff);
	SetWindowText(FFA, buff);
	SetWindowText(EDU, buff);
	SetWindowText(PLAY, buff);

	temp = money * 5 / 100;
	swprintf(buff, 255, L"%.1f", temp);
	SetWindowText(GIVE, buff);
}
