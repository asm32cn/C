// CreateFontDemo1.cpp

#include <windows.h>

#define null 0

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

HFONT SetMyFont(HDC, LPCTSTR, int, int); 

LPCSTR szClassName = "font01";    // 窗口类名

// 主入口函数
int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;

    if (!hPrevInst) {
        if (!InitApp(hCurInst))   // 注册窗口类
            return FALSE;
    }
    if (!InitInstance(hCurInst, nCmdShow)) { // 初始化窗口
        return FALSE;
    }
    while (GetMessage(&msg, null, null, null)) { // 消息循环
        TranslateMessage(&msg);   // 消息解释
        DispatchMessage(&msg);    // 消息发送
    }
    return msg.wParam;
}

// 登记窗口类
BOOL InitApp(HINSTANCE hInst)
{
    WNDCLASS ou;                     // 定义一个窗口类，下面赋初值
    ou.style         = CS_HREDRAW | CS_VREDRAW; // 窗口式样
    ou.lpfnWndProc   = WndProc;      // 窗口处理函数
    ou.cbClsExtra    = 0;            // 分配给窗口类结构之后的额外字节数
    ou.cbWndExtra    = 0;            //
    ou.hInstance     = hInst;        // 实例句柄
    ou.hIcon         = LoadIcon(null, IDI_APPLICATION);
    ou.hCursor       = LoadCursor(null, IDC_ARROW);  // 光标
    ou.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 背景
    ou.lpszMenuName  = null;         // 菜单
    ou.lpszClassName = szClassName;  // 窗口名
    return (RegisterClass(&ou));
}

// 初始化窗口类
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    // 创建窗口
    hWnd = CreateWindow(szClassName, //窗口名
            "欧阳软件学习网", //窗口标题
            WS_OVERLAPPEDWINDOW, //窗口风格
            30,          // 窗口左上角的x坐标
            50,          // 窗口左上角的y坐标
            300,         // 窗口的宽度
            300,         // 窗口的高度
            null,        // 父窗口句柄
            null,        // 菜单句柄
            hInst,       // 实例句柄
            null);       // 创建参数
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, SW_SHOW); //显示窗口
    UpdateWindow(hWnd);  // 立即显示

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    HDC hdc;
    PAINTSTRUCT ps;
    HFONT hFont, hFontOld;
    char str1[] = "欧阳谦设计制作楷体";
    char str2[] = "倪粉蓝设计制作宋体";
    char str3[] = "欧阳卫兵设计制作黑体";

    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);  // 开始描画
            SetBkMode(hdc, TRANSPARENT);  // 设置字体背景

            hFont = SetMyFont(hdc, (LPCTSTR)"楷体_GB2312", 16, 450); // 创建字体
            hFontOld = (HFONT)SelectObject(hdc, hFont); // 选择字体
            TextOut(hdc, 10, 100, str1, strlen(str1));  // 输出文字
            SelectObject(hdc, hFontOld);                // 选择旧字体
            DeleteObject(hFont);                        // 删除新字体

            hFont = SetMyFont(hdc, (LPCTSTR)"宋体", 16, -450); // 创建字体
            hFontOld = (HFONT)SelectObject(hdc, hFont); // 选择字体
            SetTextColor(hdc, RGB(255, 0, 0));          // 选择颜色
            TextOut(hdc, 10, 100, str2, strlen(str2));  // 输出文字
            SelectObject(hdc, hFontOld);                // 选择旧字体
            DeleteObject(hFont);                        // 删除新字体

            hFont = SetMyFont(hdc, (LPCTSTR)"黑体", 16, 0); // 创建字体
            hFontOld = (HFONT)SelectObject(hdc, hFont); // 选择字体
            SetTextColor(hdc, RGB(0, 255, 0));          // 选择颜色
            TextOut(hdc, 10, 100, str3, strlen(str3));  // 输出文字
            SelectObject(hdc, hFontOld);                // 选择旧字体
            DeleteObject(hFont);                        // 删除新字体

            EndPaint(hWnd, &ps);  // 结束描画
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd,
                (LPCSTR)"真的退出吗？",
                (LPCSTR)"退出确认",
                MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                DestroyWindow(hWnd);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);  // 发送关闭消息
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0L;
}

HFONT SetMyFont(HDC hdc, LPCTSTR face, int height, int angle)
{
    HFONT hFont;
    hFont = CreateFont(height, // 字体的逻辑高度
        0,                     // 逻辑平均字符宽度
        angle,                 // 与水平线的角度
        0,                     // 基线方位角度
        FW_REGULAR,            // 字形：常规
        FALSE,                 // 字形：斜体
        FALSE,                 // 字形：下划线
        FALSE,                 // 字形：粗体
        GB2312_CHARSET,        // 字符集
        OUT_DEFAULT_PRECIS,    // 输出精度
        CLIP_DEFAULT_PRECIS,   // 剪截精度
        PROOF_QUALITY,         // 输出品质
        FIXED_PITCH | FF_MODERN, // 倾斜度
        face);                 // 字体
    return hFont;
}

