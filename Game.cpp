#include"Game.h"
#define LENGTH 50

Game::Game(HWND hWnd)
{
	timeNow = timePre = 0;
	hDc = GetDC(hWnd); //获取设备句柄
	mDc = CreateCompatibleDC(hDc); //建一个和hdc兼容的内存对象
	bufDc = CreateCompatibleDC(hDc); //建一个和hdc兼容的缓冲对象
	bmp = CreateCompatibleBitmap(hDc, 1000, 1000);//建一个和窗口兼容的空位图对象
	SelectObject(mDc, bmp); //将空位图对象放到mDc中

	myDirection[0] = (HBITMAP)LoadImage(NULL, L"image\\0up.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);  //读取坦克往上走的素材图
	myDirection[1] = (HBITMAP)LoadImage(NULL, L"image\\0right.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);  //。。。向右走。。。
	myDirection[2] = (HBITMAP)LoadImage(NULL, L"image\\0down.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);  //。。。向下走。。。
	myDirection[3] = (HBITMAP)LoadImage(NULL, L"image\\0left.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);  //。。。向左走。。。


	bullet = (HBITMAP)LoadImage(NULL, L"image\\子弹.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE); //子弹素材图的读取
	obbmp = (HBITMAP)LoadImage(NULL, L"image\\墙.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);  //障碍物素材图的读取
	level = 0;
	gameOver = 1;
	my = new Tank(0, 0, 0, 6, 100, false);
	myBullet = NULL;
	for (int i = 0; i < 12; i++) enemy[i] = NULL;  //敌人初始化为空
	for (int i = 0; i < 12; i++) enemyBullet[i] = NULL; //这个是初始化子弹为空
	for (int i = 0;i < 100;i++) obstacle[i] = NULL; //障碍物初始化为空

	pFunState[0] = &Game::FunState0; //首先将函数指针设为对应的每一关函数，以下同理。
	pFunState[1] = &Game::FunState1;
	pFunState[2] = &Game::FunState2;
	pFunState[3] = &Game::FunState3;
	pFunState[4] = &Game::FunState4;
	pFunState[5] = &Game::FunState5;
	pFunState[6] = &Game::FunState6;
	pFunState[7] = &Game::FunState7;
	pFunState[8] = &Game::FunState8;
	pFunState[9] = &Game::FunState9;

	pFunInitLevel[0] = &Game::InitLevel0; //初始化关卡的函数指针设置，以下同理
	pFunInitLevel[1] = &Game::InitLevel1;
	pFunInitLevel[2] = &Game::InitLevel2;
	pFunInitLevel[3] = &Game::InitLevel3;
	pFunInitLevel[4] = &Game::InitLevel4;
	pFunInitLevel[5] = &Game::InitLevel5;
	pFunInitLevel[6] = &Game::InitLevel6;
	pFunInitLevel[7] = &Game::InitLevel7;
	pFunInitLevel[8] = &Game::InitLevel8;
	pFunInitLevel[9] = &Game::InitLevel9;
}

void Game::GamePaint() //大部分的关卡游戏画面绘制
{
	if (gameOver != 1)
	{
		SelectObject(bufDc, backGround); //首先要贴上背景图
		BitBlt(mDc, 0, 0, WIDTH, HEIGHT, bufDc, 0, 0, SRCCOPY);//这里不能用TransparentBlt

		if (my != NULL) //这里是贴上玩家的坦克图
		{
			SelectObject(bufDc, myDirection[my->direction]);
			TransparentBlt(mDc, my->horizonTop, my->verticalTop, LENGTH, LENGTH,
				bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		}
		if (myBullet != NULL) //贴上玩家的子弹，如果有的话
		{
			SelectObject(bufDc, bullet);
			TransparentBlt(mDc, myBullet->horizonTop, myBullet->verticalTop, LENGTH, LENGTH,
				bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		}

		for (int i = 0;i < 12;i++) //贴上敌人的坦克图
		{
			if (enemy[i] != NULL)
			{
				SelectObject(bufDc, enemyDirection0[enemy[i]->direction]);
				TransparentBlt(mDc, enemy[i]->horizonTop, enemy[i]->verticalTop, LENGTH, LENGTH,
					bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}
		}

		for (int i = 0;i < 12;i++) //贴上敌人的子弹
		{
			if (enemyBullet[i] != NULL)
			{
				SelectObject(bufDc, bullet);
				TransparentBlt(mDc, enemyBullet[i]->horizonTop, enemyBullet[i]->verticalTop,
					LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}
		}

		for (int i = 0;i < 100;i++) //贴上障碍物
		{
			if (obstacle[i] != NULL)
			{
				SelectObject(bufDc, obbmp);
				TransparentBlt(mDc, obstacle[i]->horizon, obstacle[i]->vertical,
					LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}
		}
		BitBlt(hDc, 0, 0, WIDTH, HEIGHT, mDc, 0, 0, SRCCOPY);
	}
	timePre = GetTickCount(); //获取当前时间
}



void Game::FunState0()
{
	text = L"欢迎您玩游戏，按下Tab进入第一关：修罗之主";
	HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(hDc, hFont);
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 0, 0));
	TextOut(hDc, 0, 0, text, wcslen(text));
	DeleteObject(hFont);
	level++;
	return;
}
void Game::FunState1()
{
	srand((unsigned)(time)(NULL));
	if (my != NULL && gameOver != 1)
	{
		switch (my->direction)
		{
		case 0: //我方向上
			if (my->verticalTop >= my->speed) //测试是否过边界
			{
				my->verticalTop -= my->speed; //如果没有，先位移一下
				for (int i = 0;i < 6;i++) //挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL && enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						my->verticalTop += my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++) //挨个测试是否会撞到墙壁
				{
					if (obstacle[i] != NULL && my->BeCollide(obstacle[i]->vertical, obstacle[i]->horizon) == true)
					{
						my->verticalTop += my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
			}
			break;

		case 1:
			if (my->horizonTop <= WIDTH - LENGTH - my->speed)//测试是否过边界
			{
				my->horizonTop += my->speed;//如果没有，先位移一下
				for (int i = 0;i < 6;i++)
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)//挨个测试是否会撞到其它坦克
					{
						my->horizonTop -= my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++) //挨个测试是否会撞到其它坦克
				{
					if (obstacle[i] != NULL && my->BeCollide(obstacle[i]->vertical, obstacle[i]->horizon) == true)
					{
						my->horizonTop -= my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
			}
			break;

		case 2:
			if (my->verticalTop <= HEIGHT - LENGTH - my->speed)//测试是否过边界
			{
				my->verticalTop += my->speed;;//如果没有，先位移一下
				for (int i = 0;i < 6;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						my->verticalTop -= my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++) //挨个测试是否会撞到其它坦克
				{
					if (obstacle[i] != NULL && my->BeCollide(obstacle[i]->vertical, obstacle[i]->horizon) == true)
					{
						my->verticalTop -= my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
			}
			break;

		case 3:;
			if (my->horizonTop >= my->speed)//测试是否过边界
			{
				my->horizonTop -= my->speed;;//如果没有，先位移一下
				for (int i = 0;i < 6;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						my->horizonTop += my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++) //挨个测试是否会撞到其它坦克
				{
					if (obstacle[i] != NULL && my->BeCollide(obstacle[i]->vertical, obstacle[i]->horizon) == true)
					{
						my->horizonTop += my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
			}
			break;
		}


		if (my->fire == true && myBullet == NULL)
			myBullet = new Bullet(my->verticalTop, my->horizonTop, 16, my->direction, 200);
		else if (myBullet != NULL)
		{
			my->fire = false;
			if (myBullet->verticalTop<0 || myBullet->verticalTop>HEIGHT || myBullet->horizonTop<0 || myBullet->horizonTop>WIDTH)
			{
				text = L"你误杀了围观者，失败！";
				goto fail;
			}
			else switch (myBullet->direction)
			{
			case 0: myBullet->verticalTop -= myBullet->speed; break;
			case 1: myBullet->horizonTop += myBullet->speed; break;
			case 2: myBullet->verticalTop += myBullet->speed; break;
			case 3: myBullet->horizonTop -= myBullet->speed; break;
			}

			for (int i = 0;i < 6;i++) //挨个测试敌人是否受到玩家攻击
			{
				if (enemy[i] != NULL&&myBullet != NULL)
				{
					if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0)
					{
						myBullet->power -= enemy[i]->HP;
						if (myBullet->power <= 0)
						{
							delete myBullet;
							myBullet = NULL;
						}
						if (++enemyCount <= 14) {
							int x, y;bool flag;
						start:
							x = rand() % (WIDTH - 200) + 79;y = rand() % (HEIGHT - 200) + 79;flag = true;
							if (my->BeCollide(y, x) == true) flag = false;
							for (int i = 0;i < 6;i++)
								if (enemy[i] != NULL&&enemy[i]->BeCollide(y, x) == true)
									flag = false;
							if (flag == true) {
								delete enemy[i];
								enemy[i] = new Tank(y, x, 0, 1, 100, true);
							}
							else goto start;
						}
						else {
							delete enemy[i];
							enemy[i] = NULL;
						}
					}
				}
			}

			for (int i = 0;i < 100;i++)
			{
				if (obstacle[i] != NULL&&myBullet != NULL)
				{
					if (true == obstacle[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25))
					{
						myBullet->power -= 100;
						if (myBullet->power <= 0)
						{
							delete myBullet;
							myBullet = NULL;
						}
						delete obstacle[i];
						obstacle[i] = NULL;
					}
				}
			}
		}
		/////////////////我们改动到这里了！！！！该下面了///////////////////
		for (int i = 0;i < 6; i++)
		{
			if (enemy[i] != NULL)
			{
				if (rand() % 6 == 1)
				{
					enemy[i]->direction = rand() % 4;
				}
				switch (enemy[i]->direction)
				{
				case 0: //向上去
					if (enemy[i]->verticalTop >= enemy[i]->speed) //首先检测是否有会超越边界
					{
						enemy[i]->verticalTop -= enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true) //接下来检测是否碰撞了我方坦克
							enemy[i]->verticalTop += enemy[i]->speed; //如果碰撞了就把这个电脑坦克设为原先的位置


						for (int j = 0;j < 6;j++) //这里检测电脑坦克是否自己碰撞到自己人
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop += enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->verticalTop += enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								break;
							}
						}
						/*************以下检测敌方坦克是否该向上开火*****************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop - LENGTH - 1, enemy[i]->horizonTop, 3, 0, 100);
							enemyBuCnt++;
						}
					}
					else 	enemy[i]->direction = 1; //如果超越了边界，就把电脑方向按规则调整一下

					break;

				case 1: //向右走
					if (enemy[i]->horizonTop <= WIDTH - LENGTH - enemy[i]->speed)
					{
						enemy[i]->horizonTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							enemy[i]->horizonTop -= enemy[i]->speed;

						for (int j = 0;j < 6;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								break;
							}
						}
						/*************以下是敌人向右检测是否该开火******************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop + LENGTH + 1, 3, 1, 100);
							enemyBuCnt++;
						}
					}
					//
					break;

				case 2: //向下走
					if (enemy[i]->verticalTop <= HEIGHT - LENGTH - enemy[i]->speed)
					{
						enemy[i]->verticalTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							enemy[i]->verticalTop -= enemy[i]->speed;

						for (int j = 0;j < 6;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								break;
							}
						}
						/*************以下是敌人向下检测是否该开火******************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop + LENGTH + 1, enemy[i]->horizonTop, 3, 2, 100);
							enemyBuCnt++;
						}
					}
					break;

				case 3: //向左走
					if (enemy[i]->horizonTop >= enemy[i]->speed)
					{
						enemy[i]->horizonTop -= enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							enemy[i]->horizonTop += enemy[i]->speed;

						for (int j = 0;j < 6;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								break;
							}
						}
						/*************以下是敌人向左检测是否该开火******************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop - LENGTH - 1, 3, 3, 100);
							enemyBuCnt++;
						}
					}
					break;
				}
			}
		}

		for (int i = 0;i < 12; i++)//这个是子弹的移动和检测是否攻击到坦克
		{
			if (enemyBullet[i] != NULL) //如果子弹还存在
			{
				switch (enemyBullet[i]->direction)//获取炮弹的发射方向
				{
				case 0: //向上射击
					enemyBullet[i]->verticalTop -= enemyBullet[i]->speed; //让炮弹飞
					if (enemyBullet[i]->verticalTop < 0) {
						text = L"敌人炮弹击中围观者，挑战失败！";
						goto fail;
					}
					break;

				case 1:
					enemyBullet[i]->horizonTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop > WIDTH) {
						text = L"敌人炮弹击中围观者，挑战失败！";
						goto fail;
					}
					break;

				case 2:
					enemyBullet[i]->verticalTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->verticalTop > HEIGHT) {
						text = L"敌人炮弹击中围观者，挑战失败！";
						goto fail;
					}
					break;

				case 3:
					enemyBullet[i]->horizonTop -= enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop < 0) {
						text = L"敌人炮弹击中围观者，挑战失败！";
						goto fail;
					}
					break;
				}


				if (enemyBullet[i] != NULL&&my != NULL) //这里测试玩家是否受伤
				{
					my->HP -= my->Hurt(enemyBullet[i]->verticalTop + LENGTH / 2, enemyBullet[i]->horizonTop + LENGTH / 2, enemyBullet[i]->power);
					if (my->HP <= 0)
					{
						text = L"你被敌人炮弹击中！";
						goto fail;
					}
				}
				for (int j = 0;j < 100;j++)
				{
					if (obstacle[j] != NULL&&enemyBullet[i] != NULL)
					{
						if (true == obstacle[j]->Hurt(enemyBullet[i]->verticalTop + 25, enemyBullet[i]->horizonTop + 25))
						{
							delete enemyBullet[i];
							enemyBullet[i] = NULL;
						}
					}
				}
			}
		} //在这里炮弹的移动和碰撞检测完毕
	}
	if (enemyCount >= 20)
	{
		text = L"恭喜您从擂台赛中脱颖而出！BGM：功夫；下一关：枪林弹雨";
		goto win;
	}

	GamePaint();
	return;
win:
	level++;
fail:
	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(hDc, hFont);
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 0, 255));
	TextOut(hDc, 0, 0, text, wcslen(text));
	DeleteObject(hFont);
	gameOver = 1;
	delete my;
	my = NULL;

}

void Game::FunState9()
{

}

bool Game::InitLevel0()
{
	return false;
}
bool Game::InitLevel1()
{
	delete my;
	my = NULL;

	for (int i = 0;i < 12;i++)
	{
		if (enemy[i] != NULL)
		{
			delete enemy[i];
			enemy[i] = NULL;
		}
	}
	for (int i = 0;i < 12;i++)
	{
		if (enemyBullet[i] != NULL)
		{
			delete enemyBullet[i];
			enemyBullet[i] = NULL;
		}
	}
	for (int i = 0;i < 100;i++)
	{
		if (obstacle[i] != NULL)
		{
			delete obstacle[i];
			obstacle[i] = NULL;
		}
	}
	speedTemp = 8;enemyCount = 0;
	my = new Tank(100, 100, 0, 4, 100, false);
	for (int i = 0; i < 6; i++) //这里是初始化敌军位置和状态
	{
		enemy[i] = new Tank((i + 3)* LENGTH, (i + 3) * LENGTH, 0, 1, 100, true);
	}
	myBullet = NULL;
	int count = 0;
	for (int i = LENGTH + 25;i < WIDTH - LENGTH - LENGTH / 2;i += LENGTH) obstacle[count++] = new Obstacle(25, i, 100);
	for (int i = LENGTH + 25;i < HEIGHT - LENGTH - 25;i += LENGTH) obstacle[count++] = new Obstacle(i, WIDTH - 75, 100);
	for (int i = LENGTH + 25;i < WIDTH - LENGTH - 25;i += LENGTH) obstacle[count++] = new Obstacle(HEIGHT - 75, i, 100);
	for (int i = LENGTH + 25;i < HEIGHT - LENGTH - 25;i += LENGTH) obstacle[count++] = new Obstacle(i, 25, 100);
	gameOver = 0;
	backGround = (HBITMAP)LoadImage(NULL, L"image\\backGround.bmp", IMAGE_BITMAP, WIDTH, HEIGHT, LR_LOADFROMFILE); //读取这关游戏背景图
    //以下四行读取这关敌人图像
	enemyDirection0[0] = (HBITMAP)LoadImage(NULL, L"image\\1up.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE); 
	enemyDirection0[1] = (HBITMAP)LoadImage(NULL, L"image\\1right.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[2] = (HBITMAP)LoadImage(NULL, L"image\\1down.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[3] = (HBITMAP)LoadImage(NULL, L"image\\1left.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	PlaySound(L"music\\1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return false;
}

bool Game::InitLevel9()
{
	return false;
}

Game::~Game()
{
	DeleteObject(bmp);
	DeleteObject(backGround);
	DeleteObject(bullet);
	DeleteObject(obbmp);
	for (int i = 0;i < 4;i++)
	{
		DeleteObject(myDirection[i]);
		DeleteObject(enemyDirection0[i]);
	}

	DeleteDC(hDc);
	DeleteDC(mDc);
	DeleteDC(bufDc);
}