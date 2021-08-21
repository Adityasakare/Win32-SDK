#include <windows.h>
#include <tchar.h>

// Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI TreadProcOne(LPVOID);
DWORD WINAPI TreadProcTwo(LPVOID);

// Global Variable Declarations

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local Variable Declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	// Code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //API 
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	// Create Window in memeory
	hwnd = CreateWindow(szAppName,
		TEXT("APS : My First Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	// Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hTread1 = NULL;
	static HANDLE hTread2 = NULL;

	// Code
	switch (iMsg)
	{
		case WM_CREATE :
			hTread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TreadProcOne,(LPVOID)hwnd, 0, NULL);	
			// Here should be error checking for hTread1
			hTread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TreadProcTwo,(LPVOID)hwnd, 0, NULL);
			// Here should be error checking for hTread2
		break;

		case WM_LBUTTONDOWN :
			MessageBox(hwnd, TEXT("I am Thread number 4"), TEXT("Message"), MB_OK);
		break;

		case WM_DESTROY :
			CloseHandle(hTread1);
			CloseHandle(hTread2);
			PostQuitMessage(0);
		break;

		default :
		break;
	}

	
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

DWORD WINAPI TreadProcOne(LPVOID param)
	{
		// variable Decldration
		HDC hdc = NULL;
		TCHAR str[255];
		long i;

		//code
		hdc = GetDC((HWND)param);
		SetBkColor(hdc, RGB(0,0,0));
		SetTextColor(hdc, RGB(0, 255, 0));
		for(i = 0; i < 65535; i++)
		{
			wsprintf(str, TEXT("Incrementing Order = %ld") , i);
			TextOut(hdc, 5, 5, str, (int)_tcslen(str));
		}
		ReleaseDC((HWND)param, hdc);
		return 0;
	}

	DWORD WINAPI TreadProcTwo(LPVOID param)
	{
		// variable Decldration
		HDC hdc = NULL;
		TCHAR str[255];
		long i;

		//code
		hdc = GetDC((HWND)param);
		SetBkColor(hdc, RGB(0,0,0));
		SetTextColor(hdc, RGB(255, 0, 0));
		for(i = 65535; i >= 0 ; i--)
		{
			wsprintf(str, TEXT("Decrementing Order = %ld") , i);
			TextOut(hdc, 5, 25, str, (int)_tcslen(str));
		}
		ReleaseDC((HWND)param, hdc);
		return 0;
	}

