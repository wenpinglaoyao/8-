#pragma once
#include <CoreWindow.h>
#include <Windows.h>
#include <tchar.h>
#include "tank.h"
#include <time.h>
#define WIDTH 1000
#define HEIGHT 800
class Game
{
public:
	Game(HWND hWnd);
	~Game();

	void GamePaint();

	void FunState0(); //这些声明函数，用来更新这一关的局势，以下同理
	void FunState1();
	void FunState2();
	void FunState3();
	void FunState4();
	void FunState5();
	void FunState6();
	void FunState7();
	void FunState8();
	void FunState9();

	bool InitLevel0(); //这些声明函数，用来初始化当前的每一关，以下同理
	bool InitLevel1();
	bool InitLevel2();
	bool InitLevel3();
	bool InitLevel4();
	bool InitLevel5();
	bool InitLevel6();
	bool InitLevel7();
	bool InitLevel8();
	bool InitLevel9();
public:
	DWORD timeNow, timePre; //声明两个时间变量，用来记录时间差
	HDC hDc, mDc, bufDc; //声明3个DC，设备DC，内存DC，缓存DC，
	HBITMAP bmp;
	HBITMAP backGround; //顾名思义，主要用作背景图
	HBITMAP myDirection[4]; //这个是用作玩家坦克贴图，之所以是4个量的数组，因为坦克具有上下左右4个方向
	HBITMAP enemyDirection0[4]; //同上，是敌人坦克
	HBITMAP bullet; //用作子弹的贴图，不论敌我
	HBITMAP obbmp; //用作障碍物的贴图
	HBITMAP boom; //爆炸图，也可以用作别的用途
	HBITMAP mass; //同上，不固定的用途
	wchar_t *text;

	int gameOver = 0;
	int level; //这个用来表示游戏当前的关卡是第几关
	Tank *my; //声明一个玩家坦克对象指针
	Tank* enemy[12]; //声明12个敌人对象指针
	int enemyCount; //这个用来记录敌人数量或者用来记录敌人被消灭数量
	Bullet* myBullet; //这个是玩家的子弹，其实直觉告诉我，可以与下面的子弹对象数组合并在一起，但保险起见，还是单挑出来吧
	Bullet* enemyBullet[12]; //这个是敌人的子弹，每次最多存在12颗敌人炮弹
	int enemyBuCnt, speedTemp; //第一个是子弹数量，第二个是记录这一关的玩家坦克应该的速度，与空格键配合使用，方便复位玩家速度
	Obstacle* obstacle[100]; //最多有100个障碍物
	void(Game::*pFunState[10])(); //这个是函数指针，用它来指向不同的关卡更新函数，这样当我们玩到某一关时，就可以调用相应的函数
	bool(Game::*pFunInitLevel[10])(); //与上面同理，不同的是指向关卡初始化函数
};