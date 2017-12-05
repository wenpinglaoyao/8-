//惊弓之鸟
#include "Game.h"
#define TASKNUM 20
#define ALL 4
#define CD 150 //复生敌人的无敌时间，要减去100

#define SWERVETIME WIDTH //和下一面一行代码配合设置敌人转弯冷却时间
int swervetime;
void Game::FunState5()
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
				for (int i = 0;i < ALL;i++) //挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL && enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						my->verticalTop += my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++) //挨个测试是否撞壁
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
				for (int i = 0;i < ALL;i++)
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)//挨个测试是否会撞到其它坦克
					{
						my->horizonTop -= my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++) //挨个测试是否撞壁
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
				for (int i = 0;i < ALL;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						my->verticalTop -= my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++)  //挨个测试是否撞壁
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
				for (int i = 0;i < ALL;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						my->horizonTop += my->speed; //如果撞到了，恢复位移前位置
						break;
					}
				}
				for (int i = 0;i < 100;i++)  //挨个测试是否撞壁
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


		if (my->fire == true)
		{
			my->fire = false;
			if (myBullet == NULL) //生成炮弹
			{
				myBullet = new Bullet(my->verticalTop, my->horizonTop, 16, my->direction, 200);
				for (int a = 0;a < ALL;a++)
					if (enemyBullet[a] == NULL && enemy[a] != NULL && enemy[a]->HP <= 100)
						enemyBullet[a] = new Bullet(enemy[a]->verticalTop, enemy[a]->horizonTop, 16, enemy[a]->direction, 100);
			}
		}
		if (myBullet != NULL)
		{
			if (myBullet->verticalTop<0 || myBullet->verticalTop>HEIGHT || myBullet->horizonTop<0 || myBullet->horizonTop>WIDTH)
			{
				delete myBullet;
				myBullet = NULL;
			}
			else switch (myBullet->direction)//让炮弹飞
			{
			case 0: myBullet->verticalTop -= myBullet->speed; break;
			case 1: myBullet->horizonTop += myBullet->speed; break;
			case 2: myBullet->verticalTop += myBullet->speed; break;
			case 3: myBullet->horizonTop -= myBullet->speed; break;
			}

			for (int i = 0;i < ALL;i++) //挨个测试敌人是否受到玩家攻击
			{
				if (enemy[i] != NULL && myBullet != NULL)
				{
					if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0)
					{
						delete myBullet;
						myBullet = NULL;
						if (enemyBullet[i] != NULL)
						{
							delete enemyBullet[i];
							enemyBullet[i] = NULL;
						}
						if (enemyCount < TASKNUM  - ALL)
						{
							int x, y;bool flag;
						start:
							x = rand() % (WIDTH - 200) + 79;y = rand() % (HEIGHT - 200) + 79;flag = true;

							if (my->BeCollide(y, x) == true) //首先检测出生地是否与主角重合
								flag = false;

							for (int i = 0;i < ALL;i++) //其次检测是否和同胞重合
								if (enemy[i] != NULL&&enemy[i]->BeCollide(y, x) == true)
									flag = false;

							for (int i = 0;i < 100;i++) //最后检测是否和障碍物重合
								if (obstacle[i] != NULL && obstacle[i]->BeCollide(y, x) == true)
									flag = false;
							if (flag == true)
							{
								obstacle[enemyCount] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 0);//敌人被冻住
								enemyCount++;//障碍物+1

								delete enemy[i];
								enemy[i] = new Tank(y, x, 0, 1, CD, true);
							}
							else goto start;
						}
						else
						{
							obstacle[enemyCount] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 0);//敌人被冻住
							enemyCount++;//资料+1

							delete enemy[i];
							enemy[i] = NULL;
						}

						if (enemyCount >= TASKNUM) //这里是过关任务的数量
						{
							text = L"正在搜集全部资料！BGM:魂斗罗第2关；下一关：铁皮球王";
							goto win;
						}
					}
				}
			}
		}

		/////////////////我们改动到这里了！！！！该敌人行动了///////////////////
		swervetime+=3;
		for (int i = 0;i < ALL; i++)
		{
			if (enemy[i] != NULL)
			{
				enemy[i]->HP -= enemy[i]->HP / 101;//这个是让敌人冷却，每次敌人转弯或刚出生都不能开火或被杀

				if (enemy[i]->HP > 100) //如果敌人处于保护圈状态，那么给贴上“闪图”
				{
					SelectObject(bufDc, backGround);
					TransparentBlt(mDc, enemy[i]->horizonTop, enemy[i]->verticalTop,
						LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(11, 11, 11));
					BitBlt(hDc, 0, 0, WIDTH, HEIGHT, mDc, 0, 0, SRCCOPY);
				}

				if (swervetime >= SWERVETIME) //冷却时间完毕，敌人也许该转弯了
				{
					swervetime = 0;
					for (int i = 0;i < ALL; i++)
					{
						if (enemy[i]!=NULL && rand() % 3 == 0)
						{
							enemy[i]->direction = rand() % 4;
						}
					}
				}

				switch (enemy[i]->direction)
				{
				case 0: //向上去
					if (enemy[i]->verticalTop >= enemy[i]->speed) //首先检测是否有会超越边界
					{
						enemy[i]->verticalTop -= enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true) //接下来检测是否碰撞了我方坦克
						{
							enemy[i]->verticalTop += enemy[i]->speed; //如果碰撞了就把这个电脑坦克设为原先的位置
							++enemy[i]->direction %= 4;
						}



						for (int j = 0;j < ALL;j++) //这里检测电脑坦克是否自己碰撞到自己人
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop += enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->verticalTop += enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
					}
					else
					{
						enemy[i]->direction = (enemy[i]->direction + 2) % 4;
						//enemy[i]->HP = CD; //敌人转向后开启保护圈
					}
					break;

				case 1: //向右走
					if (enemy[i]->horizonTop <= WIDTH - LENGTH - enemy[i]->speed)
					{
						enemy[i]->horizonTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
						{
							enemy[i]->horizonTop -= enemy[i]->speed;
							++enemy[i]->direction %= 4;
						}

						for (int j = 0;j < ALL;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
					}
					else
					{
						enemy[i]->direction = (enemy[i]->direction + 2) % 4;
						//enemy[i]->HP = CD; //敌人转向后开启保护圈
					}
					break;

				case 2: //向下走
					if (enemy[i]->verticalTop <= HEIGHT - LENGTH - enemy[i]->speed)
					{
						enemy[i]->verticalTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
						{
							enemy[i]->verticalTop -= enemy[i]->speed;
							++enemy[i]->direction %= 4;
						}

						for (int j = 0;j < ALL;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
					}
					else
					{
						enemy[i]->direction = (enemy[i]->direction + 2) % 4;
						//enemy[i]->HP = CD; //敌人转向后开启保护圈
					}
					break;

				case 3: //向左走
					if (enemy[i]->horizonTop >= enemy[i]->speed)
					{
						enemy[i]->horizonTop -= enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
						{
							enemy[i]->horizonTop += enemy[i]->speed;
							++enemy[i]->direction %= 4;
						}

						for (int j = 0;j < ALL;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
						for (int j = 0;j < 100;j++) //这里检测电脑坦克是否撞壁
						{
							if (enemy[i] != NULL&&obstacle[j] != NULL && enemy[i]->BeCollide(obstacle[j]->vertical, obstacle[j]->horizon) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								enemy[i]->direction = (enemy[i]->direction + 2) % 4;
								//enemy[i]->HP = CD; //敌人转向后开启保护圈
								break;
							}
						}
					}
					else
					{
						enemy[i]->direction = (enemy[i]->direction + 2) % 4;
						//enemy[i]->HP = CD; //敌人转向后开启保护圈
					}
					break;
				}
			}
		}

		for (int i = 0;i < ALL; i++)//这个是敌人子弹的移动和检测是否攻击到什么
		{
			if (enemyBullet[i] != NULL) //如果子弹还存在
			{
				for (int j = 0;j < ALL;j++)
				{
					if (j != i && enemy[j] != NULL && enemy[j]->HP <= 100
						&& enemy[j]->Hurt(enemyBullet[i]->verticalTop + LENGTH / 2, enemyBullet[i]->horizonTop + LENGTH / 2, enemyBullet[i]->power))
					{
						text = L"一份资料被摧毁，无法拼凑完全，挑战失败!";
						goto fail;
					}
				}
				for (int j = 0;j < 100;j++)
				{
					if (j != i && obstacle[j] != NULL
						&& obstacle[j]->Hurt(enemyBullet[i]->verticalTop + LENGTH / 2, enemyBullet[i]->horizonTop + LENGTH / 2))
					{
						text = L"一份资料被摧毁，无法拼凑完全，挑战失败!";
						goto fail;
					}
				}

				switch (enemyBullet[i]->direction)//获取炮弹的发射方向
				{
				case 0: //向上射击
					enemyBullet[i]->verticalTop -= enemyBullet[i]->speed; //让炮弹飞
					if (enemyBullet[i]->verticalTop < 0) {
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;

				case 1:
					enemyBullet[i]->horizonTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop > WIDTH) {
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;

				case 2:
					enemyBullet[i]->verticalTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->verticalTop > HEIGHT) {
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;

				case 3:
					enemyBullet[i]->horizonTop -= enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop < 0) {
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
					}
					break;
				}


				if (enemyBullet[i] != NULL&&my != NULL) //这里测试玩家是否受伤
				{
					if (my->Hurt(enemyBullet[i]->verticalTop + LENGTH / 2, enemyBullet[i]->horizonTop + LENGTH / 2, enemyBullet[i]->power) > 0)
					{
						text = L"你被敌人炮弹击中！";
						goto fail;
					}
				}
			}
		} //在这里炮弹的移动和碰撞检测完毕
	}

	GamePaint(); //绘制图
	timePre = GetTickCount(); //获取当前时间

	HPEN hpen = CreatePen(PS_SOLID, 10, RGB(255, 10, 0));
	HPEN old = (HPEN)SelectObject(hDc, hpen);
	MoveToEx(hDc, 0, HEIGHT - 10, 0);
	LineTo(hDc, swervetime, HEIGHT - 10); //这几行代码用于画转弯条
	SelectObject(hDc, old);
	DeleteObject(hpen);
	return;

win:
	level++;
	;
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
bool Game::InitLevel5()
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

	obbmp = (HBITMAP)LoadImage(NULL, L"image\\ice.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);//读取敌人被冻结后的图像
	backGround = (HBITMAP)LoadImage(NULL, L"image\\backGround1.bmp", IMAGE_BITMAP, WIDTH, HEIGHT, LR_LOADFROMFILE); //读取这关游戏背景图
	//以下四行读取这关敌人图像
	enemyDirection0[0] = (HBITMAP)LoadImage(NULL, L"image\\5up.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[1] = (HBITMAP)LoadImage(NULL, L"image\\5right.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[2] = (HBITMAP)LoadImage(NULL, L"image\\5down.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[3] = (HBITMAP)LoadImage(NULL, L"image\\5left.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);

	speedTemp = 6;
	enemyCount = 0;
	my = new Tank(100, 0, 0, 2, 0, false);
	for (int i = 0; i < ALL; i++) //这里是初始化敌军位置和状态
	{
		enemy[i] = new Tank((i + 3)* LENGTH, (i + 3) * LENGTH, i % 4, 1, 100, true);
	}

	myBullet = NULL;
	int count = 0;
	gameOver = 0;
	PlaySound(L"music\\5.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return false;
}