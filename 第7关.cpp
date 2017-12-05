//横扫千军
#include"Game.h"
#include<math.h>
#define RADIUS 1200 //这个是激光的半径长度
#define ALL 2 //这个是所有外星飞船最多存在的总数量
#define C 10
#define BUSP 3 //这个是子弹的速度，这一关子弹的速度尽量不要太快

void Game::FunState7()
{
	if (my != NULL && gameOver != 1)
	{
		SelectObject(bufDc, backGround); //首先要贴上背景图
		BitBlt(mDc, 0, 0, WIDTH, HEIGHT, bufDc, 0, 0, SRCCOPY);//这里不能用TransparentBlt
		srand((unsigned)(time)(NULL));
		if (my != NULL && gameOver != 1)
		{
			SelectObject(bufDc, myDirection[my->direction]);
			TransparentBlt(mDc, my->horizonTop, my->verticalTop, LENGTH, LENGTH,
				bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
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
							my->verticalTop += my->speed; //如果撞到了
							if (my->horizonTop > enemy[enemyBuCnt]->horizonTop)
								my->horizonTop += my->speed;
							else my->horizonTop -= my->speed;
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
							if (my->verticalTop > enemy[enemyBuCnt]->verticalTop)
								my->verticalTop += my->speed;
							else my->verticalTop -= my->speed;
							break;
						}
					}
					for (int i = 0;i < 100;i++) //挨个测试是否会撞到其它坦克
					{
						if (obstacle[i] != NULL && my->BeCollide(obstacle[i]->vertical, obstacle[i]->horizon) == true)
						{
							my->horizonTop -= my->speed; //撞到了
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
							if (my->horizonTop > enemy[enemyBuCnt]->horizonTop)
								my->horizonTop += my->speed;
							else my->horizonTop -= my->speed;
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
					for (int i = 0;i < ALL;i++)//挨个测试是否会撞到其它坦克
					{
						if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
						{
							my->horizonTop += my->speed; //撞到了，恢复位移前位置
							if (my->verticalTop > enemy[enemyBuCnt]->verticalTop)
								my->verticalTop += my->speed;
							else my->verticalTop -= my->speed;
							break;
						}
					}
					for (int i = 0;i < 100;i++) //挨个测试是否会撞到墙壁
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
				if (myBullet == NULL)
				{
					myBullet = new Bullet(my->verticalTop, my->horizonTop, BUSP, my->direction, 200);
				}

			}
			if (myBullet != NULL)
			{
				SelectObject(bufDc, bullet);
				TransparentBlt(mDc, myBullet->horizonTop, myBullet->verticalTop, LENGTH, LENGTH,
					bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
				if (myBullet->verticalTop<0 || myBullet->verticalTop>HEIGHT || myBullet->horizonTop<0 || myBullet->horizonTop>WIDTH)
				{
					delete myBullet;
					myBullet = NULL;
				}
				else switch (myBullet->direction)
				{
				case 0: myBullet->verticalTop -= myBullet->speed; break;
				case 1: myBullet->horizonTop += myBullet->speed; break;
				case 2: myBullet->verticalTop += myBullet->speed; break;
				case 3: myBullet->horizonTop -= myBullet->speed; break;
				}

				for (int i = 0;i < ALL;i++) //挨个测试敌人是否受到玩家攻击
				{
					if (enemy[i] != NULL&&myBullet != NULL)
					{
						if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0)
						{
							delete myBullet;
							myBullet = NULL;
							enemyBuCnt = (i + 1) % 2;
							if (--enemyCount > ALL)
							{
								int x, y, mulx, muly, X, Y;

							start:
								int scope = 700 + (rand() % 200);
								x = (rand() % 900); y = scope - x;
								mulx = (2 << (rand() % 2)) - 3;
								muly = (2 << (rand() % 2)) - 3;
								X = enemy[enemyBuCnt]->horizonTop + mulx*(x);
								Y = enemy[enemyBuCnt]->verticalTop + muly*(y);
								bool flag = my->BeCollide(Y, X);
								if (X > 80 && Y > 80 && X < WIDTH - 130 && Y < HEIGHT - 130 && //在屏幕指定大小的区域内重生
									my->BeCollide(Y, X) != true) //重生后有无重叠我方坦克
								{
									delete enemy[i];
									enemy[i] = new Tank(Y, X, 0, 0, 100, true);
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
			}
			if (enemyCount <= 1) {
				text = L"成功获得激光武器！BGM:忍者龙剑传中龙与鬼婆的对话；下一关：最终决战";
				goto win;
			}
			/////////////////我们改动到这里了！！！！该下面了///////////////////
			for (int i = 0;i < ALL; i++)
			{
				if (enemy[i] != NULL)
				{
					SelectObject(bufDc, enemyDirection0[0]);
					TransparentBlt(mDc, enemy[i]->horizonTop, enemy[i]->verticalTop, LENGTH, LENGTH,
						bufDc, 0, 0, LENGTH, LENGTH, RGB(255, 255, 255));
				}
			}
		}
		BitBlt(hDc, 0, 0, WIDTH, HEIGHT, mDc, 0, 0, SRCCOPY);
	}

	if (my != NULL && enemy[enemyBuCnt] != NULL && gameOver != 1)
	{
		HPEN hpen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		HPEN old = (HPEN)SelectObject(hDc, hpen);
		double Ox = enemy[enemyBuCnt]->horizonTop + 25 - RADIUS*cos(my->HP * 3.1415926 / 180);
		double Oy = enemy[enemyBuCnt]->verticalTop + 25 - RADIUS*sin(my->HP * 3.1415926 / 180);
		MoveToEx(hDc, enemy[enemyBuCnt]->horizonTop + 25, enemy[enemyBuCnt]->verticalTop + 25, 0);
		LineTo(hDc, (int)(Ox), (int)(Oy));
		SelectObject(hDc, old);
		DeleteObject(hpen);
		bool dead = false;

		double radus = RADIUS - sqrt(
			(enemy[enemyBuCnt]->horizonTop - my->horizonTop)*(enemy[enemyBuCnt]->horizonTop - my->horizonTop)
			+
			(enemy[enemyBuCnt]->verticalTop - my->verticalTop)*(enemy[enemyBuCnt]->verticalTop - my->verticalTop)
		);
		double X = my->horizonTop + 25 - radus*cos(my->HP * 3.1415926 / 180);
		double Y = my->verticalTop + 25 - radus*sin(my->HP * 3.1415926 / 180);

		int a = Ox - X;
		int b = Oy - Y;
		if (a<C && a> -C && b<C&& b>-C) dead = true;

		if (true == dead)
		{
			text = L"你被激光射死，挑战失败！";
			goto fail;
		}
		my->HP = ++my->HP % 360;
	}

	timePre = GetTickCount(); //获取当前时间
	return;
win:
	level++;
	;
fail:
	enemyBuCnt = 0;
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

bool Game::InitLevel7()
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

	speedTemp = 2;
	enemyCount = 8; //代表guanka关卡任务需要消灭的敌人数量（减去1就是）
	enemyBuCnt = 0;
	backGround = (HBITMAP)LoadImage(NULL, L"image\\backGround1.bmp", IMAGE_BITMAP, WIDTH, HEIGHT, LR_LOADFROMFILE); //读取这关游戏背景图
	//以下四行读取这关敌人图像
	enemyDirection0[0] = (HBITMAP)::LoadImage(NULL, L"image\\激光.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[1] = (HBITMAP)::LoadImage(NULL, L"image\\激光.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[2] = (HBITMAP)::LoadImage(NULL, L"image\\激光.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[3] = (HBITMAP)::LoadImage(NULL, L"image\\激光.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	my = new Tank(101, 200, 3, 0, 0, false);
	enemy[0] = new Tank(100, 100, 0, 0, 100, true);
	enemy[1] = new Tank(550, 550, 0, 0, 100, true);
	myBullet = NULL;
	int count = 0;
	gameOver = 0;
	PlaySound(L"music\\7.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return false;
}