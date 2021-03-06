//王的沉默
#include "Game.h"
void Game::FunState4()
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
				for (int i = 0;i < 11;i++) //挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL && enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						enemy[i]->verticalTop -= my->speed ;
						my->verticalTop += my->speed;
						for (int j = 0;j < 11;j++)
						{
							if (i != j && enemy[j] != NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop += my->speed ;
								break;
							}
						}
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
				for (int i = 0;i < 11;i++)
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)//挨个测试是否会撞到其它坦克
					{
						enemy[i]->horizonTop += my->speed ;
						my->horizonTop -= my->speed;
						for (int j = 0;j < 11;j++)
						{
							if (i != j && enemy[j] != NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop -= my->speed ;
								break;
							}
						}
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
				for (int i = 0;i < 11;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						enemy[i]->verticalTop += my->speed ;
						my->verticalTop -= my->speed;
						for (int j = 0;j < 11;j++)
						{
							if (i != j && enemy[j] != NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop -= my->speed ;
								break;
							}
						}
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
				for (int i = 0;i < 11;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						enemy[i]->horizonTop -= my->speed ;
						my->horizonTop += my->speed;
						for (int j = 0;j < 11;j++)
						{
							if (i != j && enemy[j] != NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop += my->speed ;
								break;
							}
						}
					}
				}
				for (int i = 0;i < 100;i++) //挨个测试是否会撞到其它
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


		if (myBullet == NULL)
			myBullet = new Bullet(my->verticalTop, my->horizonTop, 4, my->direction, 200);
		else if (myBullet != NULL)
		{
			switch (myBullet->direction)
			{
			case 0:
				myBullet->verticalTop -= myBullet->speed;
				break;
			case 1:
				myBullet->horizonTop += myBullet->speed;
				break;
			case 2:
				myBullet->verticalTop += myBullet->speed;
				break;
			case 3:
				myBullet->horizonTop -= myBullet->speed;
				break;
			}

			if (myBullet->verticalTop < 0 || myBullet->horizonTop > WIDTH || myBullet->verticalTop > HEIGHT || myBullet->horizonTop < 0)
			{
				delete myBullet;
				myBullet = NULL;
				text = L"炮弹击中外网，惊醒敌人，挑战失败！";
				goto fail;
			}
			else if (myBullet != NULL) {
				for (int i = 0;i < 11;i++) //挨个测试敌人是否受到玩家攻击
				{
					if (enemy[i] != NULL&&myBullet != NULL)
					{
						if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0)
						{
							delete myBullet;
							myBullet = NULL;
							delete enemy[i];
							enemy[i] = NULL;
						}
					}
				}

				for (int i = 0;i < 100;i++)
				{
					if (obstacle[i] != NULL&&myBullet != NULL)
					{
						if (true == obstacle[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25))
						{
							delete myBullet;
							myBullet = NULL;
						}
					}
				}
			}
		}
		/////////////////我们改动到这里了！！！！该敌人了///////////////////
		for (int i = 0;i < 11; i++)
		{
			if (enemy[i] != NULL && my->HP == 0)
			{
				switch (enemy[i]->direction)
				{
				case 0: //向上去
					if (enemy[i]->verticalTop >= enemy[i]->speed) //首先检测是否有会超越边界
					{
						enemy[i]->verticalTop -= enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true) //接下来检测是否碰撞了我方坦克
						{
							enemy[i]->verticalTop += enemy[i]->speed; //如果碰撞了就把这个电脑坦克设为原先的位置
							enemy[i]->direction++;
							enemy[i]->direction %= 4;
						}

						for (int j = 0;j < 11;j++) //这里检测电脑坦克是否自己碰撞到自己人
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop += enemy[i]->speed;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->verticalTop += enemy[i]->speed;
								enemy[i]->direction += 2;
								enemy[i]->direction %= 4;
								break;
							}
						}
					}
					else 	enemy[i]->direction = 2; //如果超越了边界，就把电脑方向按规则调整一下

					break;

				case 1: //向右走
					if (enemy[i]->horizonTop <= WIDTH - LENGTH - enemy[i]->speed)
					{
						enemy[i]->horizonTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
						{
							enemy[i]->horizonTop -= enemy[i]->speed;
							enemy[i]->direction++;
							enemy[i]->direction %= 4;
						}

						for (int j = 0;j < 11;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								enemy[i]->direction += 2;
								enemy[i]->direction %= 4;
								break;
							}
						}
					}
					else enemy[i]->direction = 3;
					break;

				case 2: //向下走
					if (enemy[i]->verticalTop <= HEIGHT - LENGTH - enemy[i]->speed)
					{
						enemy[i]->verticalTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
						{
							enemy[i]->verticalTop -= enemy[i]->speed;
							enemy[i]->direction++;
							enemy[i]->direction %= 4;
						}

						for (int j = 0;j < 11;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								enemy[i]->direction += 2;
								enemy[i]->direction %= 4;
								break;
							}
						}
					}
					else enemy[i]->direction = 0;
					break;

				case 3: //向左走
					if (enemy[i]->horizonTop >= enemy[i]->speed)
					{
						enemy[i]->horizonTop -= enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
						{
							enemy[i]->horizonTop += enemy[i]->speed;
							enemy[i]->direction++;
							enemy[i]->direction %= 4;
						}

						for (int j = 0;j < 11;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								enemy[i]->direction += 2;
								enemy[i]->direction %= 4;
								break;
							}
						}
					}
					else enemy[i]->direction = 1;
					break;
				}
			}
			my->HP = ++my->HP % 4;
		}

		if (enemy[11]->HP >= 300) //测试是否到时间生成新人质
		{
			if (enemy[11]->BeCollide(my->verticalTop, my->horizonTop) == true)
			{
				delete enemy[11];
				enemy[11] = NULL;
				enemyCount++;
				if (enemyCount >= 4)
				{
					text = L"首领已被抓住，恭喜您过关！BGM:蝙蝠侠通关后；下一关：惊弓之鸟";
					goto win;
				}
				int x, y;
				x = rand() % 250;
				y = rand() % 250;
				enemy[11] = new Tank(275 + y, 375 + x, 0, 1, 100, true);
			}
		}
		else ++enemy[11]->HP;
	}
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

		for (int i = 0;i < 11;i++) //贴上敌人的坦克图
		{
			if (enemy[i] != NULL)
			{
				SelectObject(bufDc, enemyDirection0[enemy[i]->direction]);
				TransparentBlt(mDc, enemy[i]->horizonTop, enemy[i]->verticalTop, LENGTH, LENGTH,
					bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}
		}
		if (enemy[11] != NULL && enemy[11]->HP >= 300) //画上群众
		{
			SelectObject(bufDc, mass);
			TransparentBlt(mDc, enemy[11]->horizonTop, enemy[11]->verticalTop, LENGTH, LENGTH,
				bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		}
		for (int i = 0;i < 11;i++) //贴上敌人的子弹
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

bool Game::InitLevel4()
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
	speedTemp = 3;enemyCount = 0;
	my = new Tank(100, 0, 0, 2, 100, true);
	for (int i = 0; i < 11; i++) //这里是初始化敌军位置和状态
	{
		enemy[i] = new Tank((i + 3)* LENGTH, (i + 3) * LENGTH, rand() % 4, 1, 100, true);
	}
	enemy[11] = new Tank(375, 475, 0, 0, 300, false); //这个代表的是敌人首领
	myBullet = NULL;
	int count = 0;
	obstacle[0] = new Obstacle(0, 0, 0);
	obstacle[1] = new Obstacle(0, WIDTH - LENGTH, 0);
	obstacle[2] = new Obstacle(HEIGHT - LENGTH, 0, 0);
	obstacle[3] = new Obstacle(HEIGHT - LENGTH, WIDTH - LENGTH, 0);
	gameOver = 0;
	backGround = (HBITMAP)LoadImage(NULL, L"image\\backGround1.bmp", IMAGE_BITMAP, WIDTH, HEIGHT, LR_LOADFROMFILE); //读取这关游戏背景图
	//以下四行读取这关敌人图像
	enemyDirection0[0] = (HBITMAP)LoadImage(NULL, L"image\\4up.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE); 
	enemyDirection0[1] = (HBITMAP)LoadImage(NULL, L"image\\4right.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[2] = (HBITMAP)LoadImage(NULL, L"image\\4down.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[3] = (HBITMAP)LoadImage(NULL, L"image\\4left.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	
	mass = (HBITMAP)LoadImage(NULL, L"image\\mass.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	obbmp = (HBITMAP)LoadImage(NULL, L"image\\墙.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);  //障碍物素材图的读取
	PlaySound(L"music\\4.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return false;
}