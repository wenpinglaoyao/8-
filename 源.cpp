#include <CoreWindow.h>
#include <tchar.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include "Game.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
Game* game = NULL;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;							//窗口的附加内存，依然取0就行了
	wndClass.hInstance = hInstance;						//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //为hbrBackground成员指定一个白色画刷句柄	
	wndClass.lpszMenuName = NULL;						//设置菜单资源为空。
	wndClass.lpszClassName = L"机甲传说，作者by范效萌";		//用一个以空终止的字符串，指定窗口类的名字。

	if (!RegisterClassEx(&wndClass)) return -1;


	HWND hWnd = CreateWindow(wndClass.lpszClassName, L"机甲传说，作者by范效萌",
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,//这3个表示不允许改变窗口大小
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	game = new Game(hWnd); //先初始化我们的游戏类对象
	game->level = 8;  //做好后删除这一句代码！！这是测试所用
	MoveWindow(hWnd, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//在这里初始化游戏资源等等

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game->timeNow = GetTickCount();
			if (game->timeNow - game->timePre > 1) //如果时间间隔大于1毫秒，那么就调用相关函数刷新当前局势
				(game ->* (game->pFunState[game->level]))();
		}
	}
	ReleaseDC(hWnd, game->hDc);
	delete game;
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		break;
	case WM_KEYDOWN: //接收键盘按下的消息并做相应处理
		if (game->my != NULL)
		{
			if (wParam == VK_UP)    game->my->direction = 0,game->my->speed = game->speedTemp; //按下向上键时，恢复玩家坦克速度（与下面的松开按键配合），让坦克向上走，以下同理
			if (wParam == VK_RIGHT) game->my->direction = 1,game->my->speed = game->speedTemp; //。。。
			if (wParam == VK_DOWN)  game->my->direction = 2, game->my->speed = game->speedTemp;//。。。
			if (wParam == VK_LEFT)  game->my->direction = 3, game->my->speed = game->speedTemp;//。。。
			if (wParam == VK_SPACE)   game->my->fire = true; //按下空格键之后，如果玩家坦克没有炮弹存在，那么发射一颗炮弹
		}
	  	if (wParam == VK_TAB) (game ->* (game->pFunInitLevel[game->level]))(); //这个用来初始化当前关卡（按下TAB键之后）
		break;
	case WM_KEYUP: //接收按键的消息并做相应处理
		if (game->my != NULL)
		{
			if (wParam == VK_UP)      game->my->speed = 0; //松开按键时，将玩家坦克速度置为0，就好象玩家坦克不会动一样，以下同理
			if (wParam == VK_RIGHT)   game->my->speed = 0; //同上。。。
			if (wParam == VK_DOWN)    game->my->speed = 0; //同上。。。
			if (wParam == VK_LEFT)    game->my->speed = 0; //同上。。。
			if (wParam == VK_RETURN)  game->gameOver = ++game->gameOver & 1; //这个负责暂停（按下并松开空格键之后）
			if (wParam == VK_SPACE)   game->my->fire = false; //松开空格键之后
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}