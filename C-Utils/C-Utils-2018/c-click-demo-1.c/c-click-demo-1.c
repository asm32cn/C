
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

#define ICON1 1

#define MAX_COUNT 70
#define MAX_STEP 24

HICON ghIcon;

char * pszDlgTitle = "c-click-demo-1";
char szDisplay[1024] = {0};

INT nTimer1 = 1;

INT isStart = FALSE;

INT nPosX = 1328;
INT nPosY = 777;
INT nCount = 0;
INT nStep = 0;

INT nMaxCount = MAX_COUNT;
INT nMaxStep = MAX_STEP;


void PA_DoClick(int x, int y){
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	Sleep(50);
}

// void main(){
// 	for(int i = 0; i < 70; i++){
// 		PA_DoClick(1328, 777);
// 		printf("%d / %d ", i, 10);
// 		for(int j = 0; j < 12; j++){
// 			Sleep(1000);
// 			printf(".");
// 		}
// 		printf("\n");
// 	}
// }

LRESULT CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch(uMsg){
		// case WM_CREATE:{ // 这个消息在这里是不会生效的
		// 	CREATESTRUCT * pcs = (CREATESTRUCT*)lParam;
		// 	MessageBox(NULL, "WM_CREATE", pszDlgTitle, MB_OK);
		// 	break;
		// }
		case WM_COMMAND:{
			switch(LOWORD(wParam)){
				case IDOK:{
					POINT pt;
					GetCursorPos(&pt);

					nPosX = pt.x;
					nPosY = pt.y;

					SetDlgItemInt(hWnd, IDC_POSOTION_X, nPosX, FALSE);
					SetDlgItemInt(hWnd, IDC_POSOTION_Y, nPosY, FALSE);
					break;
				}
				case IDCANCEL:
					if(isStart) KillTimer(hWnd, nTimer1);
					EndDialog(hWnd, IDOK);
					return TRUE;
				case IDC_START:{
					EnableWindow( GetDlgItem( hWnd, IDC_POSOTION_X), isStart);
					EnableWindow( GetDlgItem( hWnd, IDC_POSOTION_Y), isStart);
					EnableWindow( GetDlgItem( hWnd, IDC_COUNT), isStart);
					EnableWindow( GetDlgItem( hWnd, IDC_STEP), isStart);
					if(isStart){
						isStart = FALSE;
						KillTimer(hWnd, nTimer1);
					}else{

						nPosX = GetDlgItemInt(hWnd, IDC_POSOTION_X, NULL, TRUE);
						nPosY = GetDlgItemInt(hWnd, IDC_POSOTION_Y, NULL, TRUE);
						nMaxCount = GetDlgItemInt(hWnd, IDC_COUNT, NULL, TRUE);
						nMaxStep  = GetDlgItemInt(hWnd, IDC_STEP, NULL, TRUE);

						HWND hPBMCount = GetDlgItem(hWnd, IDC_PROGRESS_COUNT);
						if(hPBMCount != NULL){
							SendMessage(hPBMCount,PBM_SETRANGE,0,MAKELPARAM(0, nMaxCount));
							SendMessage(hPBMCount, PBM_SETPOS, (WPARAM)nCount, 0L);
						}

						HWND hPBMStep = GetDlgItem(hWnd, IDC_PROGRESS_STEP);
						if(hPBMStep != NULL){
							SendMessage(hPBMStep,PBM_SETRANGE,0,MAKELPARAM(0, nMaxStep));
							SendMessage(hPBMStep, PBM_SETPOS, (WPARAM)nStep, 0L);
						}

						isStart = TRUE;
						SetTimer(hWnd, nTimer1, 500, NULL);
					}
					break;
				}
			}
			break;
		}
		case WM_INITDIALOG:{

			SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

			SetDlgItemInt(hWnd, IDC_POSOTION_X, nPosX, TRUE);
			SetDlgItemInt(hWnd, IDC_POSOTION_Y, nPosY, TRUE);
			SetDlgItemInt(hWnd, IDC_COUNT, MAX_COUNT, TRUE);
			SetDlgItemInt(hWnd, IDC_STEP, nMaxStep, TRUE);

			RECT rect;
			GetWindowRect(hWnd, &rect);
			INT m_nDlgW = rect.right - rect.left;
			INT m_nDlgH = rect.bottom - rect.top;
			INT m_nScreenW = GetSystemMetrics(SM_CXSCREEN);
			INT m_nScreenH = GetSystemMetrics(SM_CYSCREEN);
			MoveWindow(hWnd, (m_nScreenW - m_nDlgW) / 2, (m_nScreenH - m_nDlgH) / 2, m_nDlgW, m_nDlgH, TRUE);

			// SetIcon(ghIcon, TRUE);  // 设置大图标无效
			// SetIcon(ghIcon, FALSE); // 设置大图标无效
			SendMessage(hWnd, WM_SETICON, ICON_BIG, (long)ghIcon);
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (long)ghIcon);

			break;
		}
		case WM_TIMER:{

			HWND hPBMCount = GetDlgItem(hWnd, IDC_PROGRESS_COUNT);
			if(hPBMCount != NULL){
				SendMessage(hPBMCount, PBM_SETPOS, (WPARAM)nCount, 0L);
			}

			HWND hPBMStep = GetDlgItem(hWnd, IDC_PROGRESS_STEP);
			if(hPBMStep != NULL){
				SendMessage(hPBMStep, PBM_SETPOS, (WPARAM)nStep, 0L);
			}

			nStep++;
			if(nStep >= nMaxStep){

				PA_DoClick(nPosX, nPosY);

				nStep = 0;
				nCount++;
				if(nCount >= nMaxCount){
					nCount = 0;
				}
			}
			break;
		}
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow){
	ghIcon = LoadIcon(NULL, MAKEINTRESOURCE(ICON1));
	DialogBox(hInst, (LPCTSTR)IDD_DIALOG1, NULL, (DLGPROC)DlgProc);
	return 0;
}