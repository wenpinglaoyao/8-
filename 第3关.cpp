#include "Game.h"
#include <math.h>
#define WID 780 //屏幕的宽度
#define HEI 780 //屏幕的高度
#define RADIUS 180 //爆炸圆效果的半径
#define BOUNDARY 9 //敌人和吃瓜群主的分界线
#define ALL 12  //除了玩家外，界面中的总角色数量
#define CORRODE 5 //敌人被引爆后的腐蚀量
void Game::FunState3()
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
				for (int i = 0;i < 12;i++) //挨个测试是否会撞到其它坦克
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
			if (my->horizonTop <= WID - LENGTH - my->speed)//测试是否过边界
			{
				my->horizonTop += my->speed;//如果没有，先位移一下
				for (int i = 0;i < 12;i++)
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
			if (my->verticalTop <= HEI - LENGTH - my->speed)//测试是否过边界
			{
				my->verticalTop += my->speed;;//如果没有，先位移一下
				for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
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
				for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
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
			switch (myBullet->direction)
			{
			case 0:
				if (myBullet->verticalTop < 0)
				{
					delete myBullet;
					myBullet = NULL;
				}
				else if (myBullet != NULL) {
					myBullet->verticalTop -= myBullet->speed;
					for (int i = 0;i < BOUNDARY;i++) //挨个测试敌人是否受到玩家攻击
					{
						if (enemy[i] != NULL&&myBullet != NULL)
						{
							if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0 && enemy[i]->HP==100)
							{
								delete myBullet;
								myBullet = NULL;
								enemy[i]->HP -= CORRODE;
							}
						}
					}
				}
				break;
			case 1:
				if (myBullet->horizonTop > WID)
				{
					delete myBullet;
					myBullet = NULL;
				}
				else if (myBullet != NULL) {
					myBullet->horizonTop += myBullet->speed;
					for (int i = 0;i < BOUNDARY;i++) //挨个测试敌人是否受到玩家攻击
					{
						if (enemy[i] != NULL&&myBullet != NULL)
						{
							if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0 && enemy[i]->HP == 100)
							{
								delete myBullet;
								myBullet = NULL;
								enemy[i]->HP -= CORRODE;
							}
						}
					}
				}
				break;
			case 2:
				if (myBullet->verticalTop > HEI)
				{
					delete myBullet;
					myBullet = NULL;
				}
				else if (myBullet != NULL) {
					myBullet->verticalTop += myBullet->speed;
					for (int i = 0;i < BOUNDARY;i++) //挨个测试敌人是否受到玩家攻击
					{
						if (enemy[i] != NULL&&myBullet != NULL)
						{
							if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0 && enemy[i]->HP == 100)
							{
								delete myBullet;
								myBullet = NULL;
								enemy[i]->HP -= CORRODE;
							}
						}
					}
				}
				break;
			case 3:
				if (myBullet->horizonTop < 0)
				{
					delete myBullet;
					myBullet = NULL;
				}
				else if (myBullet != NULL) {
					myBullet->horizonTop -= myBullet->speed;
					for (int i = 0;i < BOUNDARY;i++) //挨个测试敌人是否受到玩家攻击
					{
						if (enemy[i] != NULL&&myBullet != NULL)
						{
							if (enemy[i]->HP == 100 && enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0)
							{
								delete myBullet;
								myBullet = NULL;
								enemy[i]->HP -= CORRODE;
							}
						}
					}

				}
			}
		}
		/////////////////该敌人的坦克行动///////////////////
		for (int i = 0;i < 12; i++)
		{
			if (enemy[i] != NULL)
			{
				if (enemy[i]->HP >= 100)
				{
					if (rand() % 4 == 1)
					{
						enemy[i]->direction = rand() % 4;
					}
					enemy[i]->HP -= enemy[i]->HP / 101;
					switch (enemy[i]->direction)
					{
					case 0: //向上去
						if (enemy[i]->verticalTop >= enemy[i]->speed) //首先检测是否有会超越边界
						{
							enemy[i]->verticalTop -= enemy[i]->speed;
							if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true) //接下来检测是否碰撞了我方坦克
								enemy[i]->verticalTop += enemy[i]->speed; //如果碰撞了就把这个电脑坦克设为原先的位置


							for (int j = 0;j < 12;j++) //这里检测电脑坦克是否自己碰撞到自己人
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->verticalTop += enemy[i]->speed;
									enemy[i]->direction = rand() % 4;
									break;
								}
							}
							/*************以下检测敌方坦克是否该向上开火*****************/
							if (enemyBullet[i] == NULL && i<BOUNDARY)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop - LENGTH - 1, enemy[i]->horizonTop, 3, 0, 100);
								enemyBuCnt++;
							}
						}
						else 	enemy[i]->direction = rand() % 4;

						break;

					case 1: //向右走
						if (enemy[i]->horizonTop <= WID - LENGTH - enemy[i]->speed)
						{
							enemy[i]->horizonTop += enemy[i]->speed;
							if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								enemy[i]->horizonTop -= enemy[i]->speed;

							for (int j = 0;j < 12;j++)
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->horizonTop -= enemy[i]->speed;
									enemy[i]->direction = rand() % 4;
									break;
								}
							}
							/*************以下是敌人向右检测是否该开火******************/
							if (enemyBullet[i] == NULL && i<BOUNDARY)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop + LENGTH + 1, 3, 1, 100);
								enemyBuCnt++;
							}
						}
						else enemy[i]->direction = rand() % 4;
						break;

					case 2: //向下走
						if (enemy[i]->verticalTop <= HEI - LENGTH - enemy[i]->speed)
						{
							enemy[i]->verticalTop += enemy[i]->speed;
							if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								enemy[i]->verticalTop -= enemy[i]->speed;

							for (int j = 0;j < 12;j++)
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->verticalTop -= enemy[i]->speed;
									enemy[i]->direction = rand() % 4;
									break;
								}
							}
							/*************以下是敌人向下检测是否该开火******************/
							if (enemyBullet[i] == NULL && i<BOUNDARY)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop + LENGTH + 1, enemy[i]->horizonTop, 3, 2, 100);
								enemyBuCnt++;
							}
						}
						else enemy[i]->direction = rand() % 4;
						break;

					case 3: //向左走
						if (enemy[i]->horizonTop >= enemy[i]->speed)
						{
							enemy[i]->horizonTop -= enemy[i]->speed;
							if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								enemy[i]->horizonTop += enemy[i]->speed;

							for (int j = 0;j < 12;j++)
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->horizonTop += enemy[i]->speed;
									enemy[i]->direction = rand() % 4;
									break;
								}
							}
							/*************以下是敌人向左检测是否该开火******************/
							if (enemyBullet[i] == NULL && i<BOUNDARY)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop - LENGTH - 1, 3, 3, 100);
								enemyBuCnt++;
							}
						}
						else enemy[i]->direction = rand() % 4;
						break;
					}
				}
				else if (enemy[i]->HP < 0)
				{
					if (--enemyCount>BOUNDARY) {
						int x, y;bool flag;
					start3:
						x = rand() % (WID - 200) + 76;y = rand() % (HEI - 200) + 76;flag = true;
						for (int i = 0;i < 12;i++)
							if (enemy[i] != NULL&&enemy[i]->BeCollide(y, x) == true)
								flag = false;
						if (flag == true) {
							delete enemy[i];
							enemy[i] = new Tank(y, x, 0, 2, 120, true);
						}
						else goto start3;
					}
					else {
						delete enemy[i];
						enemy[i] = NULL;
					}
				}
				else //这里是爆炸的处理
				{
					SelectObject(bufDc, boom);
					TransparentBlt(mDc, enemy[i]->horizonTop + 25 - RADIUS, enemy[i]->verticalTop + 25 - RADIUS,
						RADIUS * 2, RADIUS * 2,
						bufDc, 0, 0, RADIUS * 2, RADIUS * 2, RGB(0, 0, 0));
					BitBlt(hDc, 0, 0, WID, HEI, mDc, 0, 0, SRCCOPY);
					for (int i = 0;i < 600000;i++)//这一段代码的作用是延迟爆炸效果的贴图，不然一闪而过玩家肉眼可能看不到爆炸效果
						my->HP = i % 100;         //而这句话的作用是为了防止编译器把这两句话优化掉

					if (sqrt((my->verticalTop - enemy[i]->verticalTop)*(my->verticalTop - enemy[i]->verticalTop) +
						(my->horizonTop - enemy[i]->horizonTop)*(my->horizonTop - enemy[i]->horizonTop)) < RADIUS) //这个测试玩家坦克是否被冲击波圆圈杀死
					{
						text = L"你被爆炸冲击波杀死，第4关挑战失败！";
						goto fail;
					}

					for (int j = BOUNDARY;j < 12;j++)
						if (enemy[j] != NULL && sqrt((enemy[j]->verticalTop - enemy[i]->verticalTop)*(enemy[j]->verticalTop - enemy[i]->verticalTop) +
							(enemy[j]->horizonTop - enemy[i]->horizonTop)*(enemy[j]->horizonTop - enemy[i]->horizonTop)) < RADIUS) //测试群众是否被冲击波杀死
						{
							text = L"吃瓜群众被爆炸冲击波杀死，第4关挑战失败！";
							goto fail;
						}

					for (int j = 0;j < BOUNDARY;j++)
						if (enemy[j] != NULL && enemy[j]->HP >= 100 &&
							sqrt((enemy[j]->verticalTop - enemy[i]->verticalTop)*(enemy[j]->verticalTop - enemy[i]->verticalTop) +
							(enemy[j]->horizonTop - enemy[i]->horizonTop)*(enemy[j]->horizonTop - enemy[i]->horizonTop)) < RADIUS)
							enemy[j]->HP -= CORRODE, enemyCount--;
					enemy[i]->HP -= CORRODE;
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
					if (enemyBullet[i]->verticalTop < 0)
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;

				case 1:
					enemyBullet[i]->horizonTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop > WID)
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;

				case 2:
					enemyBullet[i]->verticalTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->verticalTop > HEI)
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;

				case 3:
					enemyBullet[i]->horizonTop -= enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop < 0)
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;
				}


				if (enemyBullet[i] != NULL&&my != NULL) //这里测试玩家是否受伤
				{
					my->HP -= my->Hurt(enemyBullet[i]->verticalTop + LENGTH / 2, enemyBullet[i]->horizonTop + LENGTH / 2, enemyBullet[i]->power);
					if (my->HP <= 0)
					{
						text = L"你被敌人炮弹击中，第4关挑战失败！";
						goto fail;
					}
				}
			}
		} //在这里炮弹的移动和碰撞检测完毕
	}
	if (gameOver != 1)
	{
		SelectObject(bufDc, backGround); //首先要贴上背景图
		BitBlt(mDc, 0, 0, WID, HEI, bufDc, 0, 0, SRCCOPY);//这里不能用TransparentBlt

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
			if (enemy[i] != NULL && enemy[i]->HP >= 100)
			{
				SelectObject(bufDc, enemyDirection0[enemy[i]->direction]);
				TransparentBlt(mDc, enemy[i]->horizonTop, enemy[i]->verticalTop, LENGTH, LENGTH,
					bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}
		}

		for (int i = 0;i < BOUNDARY;i++) //贴上敌人的子弹
		{
			if (enemyBullet[i] != NULL)
			{
				SelectObject(bufDc, bullet);
				TransparentBlt(mDc, enemyBullet[i]->horizonTop, enemyBullet[i]->verticalTop,
					LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}
		}
		for (int i = BOUNDARY;i < 12;i++)
		{
			SelectObject(bufDc, mass);
			TransparentBlt(mDc, enemy[i]->horizonTop, enemy[i]->verticalTop,
				LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
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
		BitBlt(hDc, 0, 0, WID, HEI, mDc, 0, 0, SRCCOPY);
	}
	timePre = GetTickCount(); //获取当前时间
	return;
win:
	level++;
fail:
	level++;
	gameOver = 1;
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
	HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(hDc, hFont);
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 0, 255));
	TextOut(hDc, 0, 0, text, wcslen(text));
	DeleteObject(hFont);
	;
}

bool Game::InitLevel3()
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

	speedTemp = 8;enemyCount = 40;
	my = new Tank(100, 100, 0, 4, 100, false);
	for (int i = 0; i < BOUNDARY; i++) //这里是初始化敌军位置和状态
		enemy[i] = new Tank((i + 3)* LENGTH, (i + 3) * LENGTH, 0, 1, 120, true);
	enemy[BOUNDARY] = new Tank(0, 0, 0, 1, 120, true);
	enemy[BOUNDARY+1] = new Tank(300, 400, 0, 1, 120, true);
	enemy[BOUNDARY+2] = new Tank(400, 300, 0, 1, 120, true);
	myBullet = NULL;
	int count = 0;
	gameOver = 0;
	enemyDirection0[0] = (HBITMAP)LoadImage(NULL, L"image\\0up.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE); //敌方坦克素材图的读取，下面一样
	enemyDirection0[1] = (HBITMAP)LoadImage(NULL, L"image\\0right.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[2] = (HBITMAP)LoadImage(NULL, L"image\\0down.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[3] = (HBITMAP)LoadImage(NULL, L"image\\0left.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	boom = (HBITMAP)LoadImage(NULL, L"image\\BOOM.bmp", IMAGE_BITMAP, RADIUS * 2, RADIUS * 2, LR_LOADFROMFILE); //读取爆炸图
	mass = (HBITMAP)LoadImage(NULL, L"image\\mass.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE); //读取群众图
	backGround = (HBITMAP)LoadImage(NULL, L"image\\白色2.bmp", IMAGE_BITMAP, WID, HEI, LR_LOADFROMFILE); //读取第4关游戏特有背景图（缩小版）
	return false;
}