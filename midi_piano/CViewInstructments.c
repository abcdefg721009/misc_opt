// Generated by ResEdit 1.6.6
// Copyright (C) 2006-2015
// http://www.resedit.net

HINSTANCE hInst = GetModuleHandle(0);
WNDCLASSEX wcex;
ZeroMemory(&wcex, sizeof wcex);
wcex.cbSize         = sizeof wcex;
wcex.hbrBackground  = (HBRUSH)(COLOR_3DFACE + 1);
wcex.lpszMenuName   = 0;


wcex.style          = CS_HREDRAW | CS_VREDRAW;
wcex.lpfnWndProc    = DefWindowProc;
wcex.hInstance      = hInst;
wcex.hIcon          = LoadIcon(0, (LPCTSTR)IDI_APPLICATION);
wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
wcex.lpszClassName  = "WndClass0";
RegisterClassEx(&wcex);

HFONT hfont0 = CreateFont(-11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 1, 0, 0, 0, 0, ("Ms Shell Dlg"));
HWND hwnd = CreateWindowEx(WS_EX_LEFT, ("WndClass")0, ("CViewInstructments"), WS_CAPTION | WS_VISIBLE | WS_POPUP | WS_SYSMENU, 0, 0, 743, 269, 0, 0, hInst, 0);
HWND hCtrl0_0 = CreateWindowEx(0, WC_COMBOBOX, (""), WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 23, 195, 567, 132, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_0, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_1 = CreateWindowEx(0, WC_LISTVIEW, (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | LVS_ALIGNLEFT | LVS_REPORT, 23, 24, 566, 159, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_1, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_2 = CreateWindowEx(0, WC_BUTTON, ("Instructment List"), WS_VISIBLE | WS_CHILD | 0x00000007, 9, 3, 720, 228, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_2, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_3 = CreateWindowEx(0, WC_BUTTON, ("Remove DLS"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 600, 49, 110, 23, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_3, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_4 = CreateWindowEx(0, WC_BUTTON, ("Add Instructments"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 600, 75, 110, 23, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_4, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_5 = CreateWindowEx(0, WC_BUTTON, ("Import DLS"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 600, 23, 110, 23, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_5, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_6 = CreateWindowEx(0, WC_BUTTON, ("Del Instructments"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 600, 101, 110, 23, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_6, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_7 = CreateWindowEx(0, WC_BUTTON, ("Strength Feedback"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 600, 127, 110, 23, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_7, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_8 = CreateWindowEx(0, WC_BUTTON, ("Set Current"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 600, 151, 110, 23, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_8, WM_SETFONT, (WPARAM), FALSE);
HWND hCtrl0_9 = CreateWindowEx(0, WC_BUTTON, ("Apply"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 600, 176, 110, 23, hwnd, (HMENU)0, hInst, 0);
SendMessage(hCtrl0_9, WM_SETFONT, (WPARAM), FALSE);