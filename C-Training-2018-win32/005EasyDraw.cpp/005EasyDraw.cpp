/*      EasyDraw.cpp        */
#include <windows.h>
#include "resource.h"

TCHAR szTitle[32]="欧阳软件学习网";    //窗口的标题
TCHAR szWindowClass[32]="EasyDraw";   //窗口的名称
int iDrawType=0;    //作图类型 0-直线，1-折线箭头
HMENU hMenu;    //菜单句柄

POINTS start, end, old_end;
short x, y;
BOOL bDraw = FALSE;
LONG clsCur;

ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawRect(HWND, POINTS, POINTS);

//主入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    MSG msg;

    MyRegisterClass(hInstance);   //注册窗口类

    if (!InitInstance (hInstance, nCmdShow)) //初始化窗口
    {
        return FALSE;
    }

    while (GetMessage(&msg, NULL, 0, 0)) //消息循环
    {
        TranslateMessage(&msg); //消息解释
        DispatchMessage(&msg);  //消息发送
    }

    return msg.wParam;
}

//登记窗口类
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX ou;  //定义一个窗口类，下面赋初值

    ou.cbSize           = sizeof(WNDCLASSEX); //类的字节长度
    ou.style            = CS_HREDRAW | CS_VREDRAW; //窗口式样
    ou.lpfnWndProc      = (WNDPROC)WndProc; //窗口处理函数
    ou.cbClsExtra       = 0;  //分配给窗口类结构之后的额外字节数
    ou.cbWndExtra       = 0;  //
    ou.hInstance        = hInstance;  //实例句柄
    ou.hIcon            = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
    ou.hCursor          = LoadCursor(NULL, IDC_ARROW);  //光标
    ou.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景
    ou.lpszMenuName     = (LPCSTR)IDR_MENU1; //菜单
    ou.lpszClassName    = szWindowClass; //窗口名
    ou.hIconSm          = LoadIcon(ou.hInstance, (LPCTSTR)IDI_APPLICATION);

    return RegisterClassEx(&ou);
}

//初始化窗口类
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   //创建窗口
   hWnd = CreateWindow( szWindowClass, //窗口名
                        szTitle, //窗口标题
                        WS_OVERLAPPEDWINDOW, //窗口风格
                        100, //窗口左上角的x坐标
                        100, //窗口左上角的y坐标
                        400, //窗口的宽度
                        380,  //窗口的高度
                        NULL, //父窗口句柄
                        NULL, //菜单句柄
                        hInstance, //实例句柄
                        NULL); //创建参数
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow); //显示窗口
   UpdateWindow(hWnd); //立即显示

   return TRUE;
}

//消息处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR szHello[32]="一个简单作图窗口。";

    switch (message) 
    {
        case WM_CREATE:
            hMenu=GetMenu(hWnd); //在创建窗口时取菜单的句柄
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDM_EXIT:
                    SendMessage(hWnd, WM_CLOSE, 0, 0L); //发送关闭窗口消息
                    break;
                case IDM_LINE:
                    iDrawType = 0;    //0代表画线 
                    CheckMenuItem(hMenu,IDM_LINE,MF_CHECKED); //设置“直线”为1
                    CheckMenuItem(hMenu,IDM_BROCKEN,MF_UNCHECKED); //设置“折线”为0
                    break;
                case IDM_BROCKEN:
                    iDrawType = 1;    //1代表画折线
                    CheckMenuItem(hMenu,IDM_LINE,MF_UNCHECKED); ////设置“直线”为0
                    CheckMenuItem(hMenu,IDM_BROCKEN,MF_CHECKED); //设置“折线”为1
                    break;
            }
            break;
        case WM_PAINT:   //窗口刷新
            hdc = BeginPaint(hWnd, &ps);  //开始描画
            RECT rt;    //定义一个矩形区域变量
            GetClientRect(hWnd, &rt); //取窗口的区域到变量中
            DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER); //显示文字
            EndPaint(hWnd, &ps);  //结束描画
            break;

        case WM_LBUTTONDOWN:
            bDraw = TRUE;  //描画状态开始
            old_end = start = MAKEPOINTS(lParam); //开始点保存于start和old_end中
            clsCur=GetClassLong(hWnd,GCL_HCURSOR); //取窗口类的光标值
            SetClassLong(hWnd,GCL_HCURSOR,NULL);   //关闭窗口类对光标的控制
            SetCursor(LoadCursor(NULL, IDC_CROSS)); //设置光标为十字形
            break;
        case WM_MOUSEMOVE:
            if(bDraw) {  //如果是描画状态
                end = MAKEPOINTS(lParam);  //当前点保存于end中
                DrawRect(hWnd, start, old_end); //擦去前一次所画内容
                DrawRect(hWnd, start, end); //画开始点到当前点
                old_end = end;  //当前点设置为旧的点
            }
            break;
        case WM_LBUTTONUP:
            bDraw = FALSE;    //描画状态结束
            SetClassLong(hWnd,GCL_HCURSOR,clsCur);  //恢复窗口类对光标的控制
            SetCursor(LoadCursor(NULL, IDC_ARROW)); //恢复箭头光标
            break;
        case WM_DESTROY:  //关闭窗口
            PostQuitMessage(0);  //发送关闭消息
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

//作图
void DrawRect(HWND hWnd, POINTS beg, POINTS end)
{
    HDC hdc;

    hdc = GetDC(hWnd);      //取设备句柄
    SetROP2(hdc, R2_NOT);   //设置描画方式为象素反转
    MoveToEx(hdc, beg.x, beg.y, NULL);  //移动描画点到按下鼠标键的地方
    if (iDrawType==1) {  //如果是画折线
        LineTo(hdc, beg.x, (int)((beg.y+end.y)/2)); //先向下画一半
        LineTo(hdc, end.x, (int)((beg.y+end.y)/2)); //再向右画
    }
    LineTo(hdc, end.x, end.y); //从描画点到(end.x, end.y)点
    
    ReleaseDC(hWnd, hdc); //释放设备句柄
    return;
} 
