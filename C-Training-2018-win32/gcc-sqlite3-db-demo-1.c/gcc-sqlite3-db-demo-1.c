// gcc-sqlite3-db-demo-1.c

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "sqlite3.h"

#define LVS_EX_FULLROWSELECT 0x20
#define LVS_EX_GRIDLINES 1

// void main(){
// 	char * A_szKeys[] = {"id", "strTitle", "strDate", "nCateID", "strCateName", "nCount", "strMemo"};
// 	sqlite3 * db = 0;
// 	char * errMsg = NULL;
// 	sqlite3_stmt * stmt = NULL;
// 	int rc = 0;+
// 	printf("Begin ...\n");

// 	rc = sqlite3_open("lesson12.sqlite3", &db);
// 	if(rc == SQLITE_OK){
// 		char szQuery[] = "select `id`, `strTitle`, `strDate`, `nCateID`, `strCateName`, `nCount`, `strMemo` from `table_article` order by `id` asc";
// 		INT nRow = 0;
// 		char szText[256] = {0};
// 		rc = sqlite3_prepare(db, szQuery, -1, &stmt, 0);
// 		if(rc == SQLITE_OK){
// 			INT nFields = sqlite3_column_count(stmt);
// 			while( (sqlite3_step(stmt)) == SQLITE_ROW){
// 				sprintf(szText, "%s = %s\n", A_szKeys[0], sqlite3_column_text(stmt, 0));
// 				printf(szText);
// 				for(int i = 1; i < 7; i++){
// 					sprintf(szText, "%s = %s\n", A_szKeys[i], sqlite3_column_text(stmt, i));
// 					printf(szText);
// 				}
// 			}
// 		}else{
// 			stmt = NULL;
// 		}
// 		sqlite3_close(db);
// 	}else{
// 		printf("Can't open database: %s\n", sqlite3_errmsg(db));
// 	}
// }

LRESULT CALLBACK WindowFunc(HWND,UINT,WPARAM,LPARAM);

char szWinName[]="gcc-sqlite3-db-demo-1.c";

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;
HWND hListCtrl = NULL;

int WINAPI WinMain(HINSTANCE hThisInst,HINSTANCE hPrevInst,
				   LPSTR lpszArgs,int nWinMode){
	HWND hWnd;
	MSG msg;
	WNDCLASS wc1;

	//定义一个窗口类
	wc1.hInstance=hThisInst;        //改实例的句柄
	wc1.lpszClassName=szWinName;    //窗口类的名称
	wc1.lpfnWndProc=WindowFunc;     //窗口名称
	wc1.style=0;                    //默认模式

	wc1.hIcon=LoadIcon(NULL,IDI_APPLICATION);   //图标模式
	wc1.hCursor=LoadCursor(NULL,IDC_ARROW);     //光标模式
	wc1.lpszMenuName=NULL;                      //没有菜单

	wc1.cbClsExtra=0;
	wc1.cbWndExtra=0;

	//设置窗口背景为白色
	wc1.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);

	//登记窗口类
	if(!RegisterClass(&wc1)) return 0;

	ghInstance = hThisInst;

	//创建一个窗口
	hWnd=CreateWindow(
		szWinName,                  //窗口类名
		"Windows 98 Framework",     //标题
		WS_OVERLAPPEDWINDOW,        //窗口模式
		CW_USEDEFAULT,              // X 坐标
		CW_USEDEFAULT,              // Y 坐标
		CW_USEDEFAULT,              //宽度
		CW_USEDEFAULT,              //高度
		HWND_DESKTOP,               //没有父窗口
		NULL,                       //没有菜单
		hThisInst,                  //该程序实例的句柄
		NULL
		);

	//显示窗口
	ShowWindow(hWnd,nWinMode);
	UpdateWindow(hWnd);

	//创建消息循环
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);     //允许使用键盘
		DispatchMessage(&msg);      //返回窗口控制
	}
	return msg.wParam;
}

//该函数被 Windows 98 调用，可以从消息队列中传递消息
LRESULT CALLBACK WindowFunc(HWND hWnd,UINT message,
							WPARAM wParam,LPARAM lParam){
	switch(message){
	case WM_CREATE:{
			RECT rect;
			int cx, cy;
			GetClientRect(hWnd, &rect);
			cx = rect.right;
			cy = rect.bottom;

			int rowIndex = 7;
			hListCtrl = CreateWindow("syslistview32", "", WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
						0, 0, cx, cy, hWnd, NULL, ghInstance, NULL);

			// ListView_SetExtendedListViewStyle(hListCtrl, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

			LV_ITEM lvItem;
			LV_COLUMN lvColumn;

			ZeroMemory(&lvItem, sizeof(LV_ITEM));
			ZeroMemory(&lvColumn, sizeof(LV_COLUMN));

			char * A_szColumnName[7] = {"ID", "标题", "日期", "分类ID", "分类", "阅读数", "备注"};
			int  A_nColumnWidth[7] = {25, 325, 130, 55, 85, 55, 115};

			for(int i = 0; i < 7; i++){
				lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
				lvColumn.fmt = (i == 3 || i == 5 ? LVCFMT_CENTER : LVCFMT_LEFT);
				lvColumn.pszText = A_szColumnName[i];
				lvColumn.cchTextMax = 0;
				lvColumn.cx = A_nColumnWidth[i];
				lvColumn.iSubItem = 0;

				ListView_InsertColumn(hListCtrl, i, &lvColumn);
			}

			char szDisplay[256] = {0};

			sqlite3 * db = 0;
			char * errMsg = NULL;
			sqlite3_stmt * stmt = NULL;
			int rc = 0;

			lvItem.mask = LVIF_PARAM | LVIF_TEXT;
			lvItem.iSubItem = 0;

			rc = sqlite3_open("lesson12.sqlite3", &db);
			if(rc == SQLITE_OK){
				char szQuery[] = "select `id`, `strTitle`, `strDate`, `nCateID`, `strCateName`, `nCount`, `strMemo` from `table_article` order by `id` asc";
				INT nRow = 0;
				char szText[256] = {0};
				rc = sqlite3_prepare(db, szQuery, -1, &stmt, 0);
				if(rc == SQLITE_OK){
					INT nFields = sqlite3_column_count(stmt);
					while( (sqlite3_step(stmt)) == SQLITE_ROW){
						sprintf(szText, "%s", sqlite3_column_text(stmt, 0));

						lvItem.iItem = nRow;
						lvItem.pszText = szText;
						lvItem.cchTextMax = lstrlen(szText);
						lvItem.lParam = (LPARAM)atoi(szText);
						INT nItemID = ListView_InsertItem(hListCtrl, &lvItem);
						if(nItemID >= 0){
							for(int i = 1; i < 7; i++){
							// 	char szCell[256] = {0};
							// 	sprintf(szCell, "%s", sqlite3_column_text(stmt, i));
							// // 	ListView_SetItemText(hListCtrl, nItemID, i, szText);
							}
						}
						nRow++;
					}
				}else{
					stmt = NULL;
				}
				sqlite3_close(db);
			}else{
				printf("Can't open database: %s\n", sqlite3_errmsg(db));
			}

		}
		break;
	case WM_DESTROY: //终止进程
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,
			message,wParam,lParam);
	}
	return 0;
}


