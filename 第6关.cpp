//铁皮球王
#include "Game.h"
#include <math.h>
#define ACTURERADIUS 40
#define EFFECTRADIUS 55
#define SP 400 //这个代表金球的滚动速度
#define TIMES 1000 //这个代表陨石的攻击事件（可通过我方坦克的开火而缩短）

void Game::FunState6()
{
	srand((unsigned)(time)(NULL));
	int hehe = rand(); //这句代码是很奇怪，因为我也搞不明白为什么块的第一个rand()会有规律
	if (my != NULL && gameOver != 1 && my->HP <= TIMES)
	{
		my->HP++;
		for (int j = 0;j < 12;j++)
		{
			if (enemy[j] != NULL)
			{
				double a = enemy[j]->horizonTop + 25 - obstacle[0]->horizon;
				double b = enemy[j]->verticalTop + 25 - obstacle[0]->vertical;
				double c = sqrt(a*a + b*b);
				if (c <= ACTURERADIUS) //如果足球和敌人的位置重合，那么足球停止，敌人被消灭
				{
					delete enemy[j];
					enemy[j] = NULL;
					obstacle[3]->horizon = 0; //金球的速度清零（静止不动，以下同理）
					obstacle[3]->vertical = 0;

					enemyCount--;
					if (enemyCount <= 0)
					{
						text = L"蟹星人全部被撞到千里之外，恭喜过关！BGM:赤影战士第一关；下一关：横扫千军";
						goto win;
					}
				}
			}
		}
		obstacle[0]->horizon += obstacle[3]->horizon;
		obstacle[0]->vertical += obstacle[3]->vertical;

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

				if (obstacle[0] != NULL)
				{
					double a = my->horizonTop + 25 - obstacle[0]->horizon;
					double b = my->verticalTop + 25 - obstacle[0]->vertical;
					double c = sqrt(a*a + b*b);
					if (c <= EFFECTRADIUS) //如果我方坦克在足球脚下
					{
						my->verticalTop += my->speed; //因为撞到了足球，所以坦克归位
						if (my->horizonTop + 25 < obstacle[0]->horizon) //如果主角在足球左边
						{
							my->horizonTop -= 1; //那么主角向左小幅度移动
							for (int i = 0;i < 12;i++)//挨个测试小幅度移动时是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->horizonTop += 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
						if (my->horizonTop + 25 > obstacle[0]->horizon) //反之则向右小幅度移动
						{
							my->horizonTop += 1;
							for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->horizonTop -= 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
					}
				}

			}
			break;

		case 1:
			if (my->horizonTop <= WIDTH - LENGTH - my->speed)//测试是否过边界
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

				if (obstacle[0] != NULL)
				{
					double a = my->horizonTop + 25 - obstacle[0]->horizon;
					double b = my->verticalTop + 25 - obstacle[0]->vertical;
					double c = sqrt(a*a + b*b);
					if (c <= EFFECTRADIUS)
					{
						my->horizonTop -= my->speed;
						if (my->verticalTop + 25 < obstacle[0]->vertical)
						{
							my->verticalTop -= 1;
							for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->verticalTop += 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
						if (my->verticalTop + 25 > obstacle[0]->vertical)
						{
							my->verticalTop += 1;
							for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->verticalTop -= 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
					}
				}
			}
			break;

		case 2:
			if (my->verticalTop <= HEIGHT - LENGTH - my->speed)//测试是否过边界
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

				if (obstacle[0] != NULL)
				{
					double a = my->horizonTop + 25 - obstacle[0]->horizon;
					double b = my->verticalTop + 25 - obstacle[0]->vertical;
					double c = sqrt(a*a + b*b);
					if (c <= EFFECTRADIUS)
					{
						my->verticalTop -= my->speed;
						if (my->horizonTop + 25 < obstacle[0]->horizon)
						{
							my->horizonTop -= 1;
							for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->horizonTop += 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
						if (my->horizonTop + 25 > obstacle[0]->horizon)
						{
							my->horizonTop += 1;
							for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->horizonTop -= 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
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

				if (obstacle[0] != NULL)
				{
					double a = my->horizonTop + 25 - obstacle[0]->horizon;
					double b = my->verticalTop + 25 - obstacle[0]->vertical;
					double c = sqrt(a*a + b*b);
					if (c <= EFFECTRADIUS)
					{
						my->horizonTop += my->speed;
						if (my->verticalTop + 25 < obstacle[0]->vertical)
						{
							my->verticalTop -= 1;
							for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->verticalTop += 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
						if (my->verticalTop + 25 > obstacle[0]->vertical)
						{
							my->verticalTop += 1;
							for (int i = 0;i < 12;i++)//挨个测试是否会撞到其它坦克
							{
								if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
								{
									my->verticalTop -= 1; //如果撞到了，恢复位移前位置
									break;
								}
							}
						}
					}
				}
			}
			break;
		}


		if (my->fire == true && myBullet == NULL)
		{
			myBullet = new Bullet(my->verticalTop, my->horizonTop, 16, my->direction, 200);
			my->HP += 2;//我方坦克每发射一颗炮弹，都会加速陨石的到来
		}
		else if (myBullet != NULL)
		{
			my->fire = false;
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

			for (int i = 0;i < 12;i++) //挨个测试敌人是否受到玩家攻击
			{
				if (enemy[i] != NULL&&myBullet != NULL)
				{
					if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0)
					{
						delete myBullet;
						myBullet = NULL;
					}
				}
			}

			if (myBullet != NULL) //测试我的子弹是否击中足球，若是则子弹消失
			{
				double ma = myBullet->horizonTop + 25 - obstacle[0]->horizon;
				double mb = myBullet->verticalTop + 25 - obstacle[0]->vertical;
				double mc = sqrt(ma*ma + mb*mb);
				if (mc <= ACTURERADIUS)
				{
					delete myBullet;
					myBullet = NULL;
				}
			}
		}
		/////////////////我们改动到这里了！！！！该敌人行动了///////////////////
		obstacle[4]->vertical = ++obstacle[4]->vertical % 2;
		for (int i = 0;i < 12; i++)
		{
			if (enemy[i] != NULL && obstacle[4]->vertical == 0)
			{
				if (rand() % 10 == 1) //这一段代码用来随机调整敌人的走向
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
						{
							enemy[i]->verticalTop += enemy[i]->speed; //如果碰撞了就把这个电脑坦克设为原先的位置
							++enemy[i]->direction %= 4;
						}


						for (int j = 0;j < 12;j++) //这里检测电脑坦克是否自己碰撞到自己人
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop += enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						double a = enemy[i]->horizonTop + 25 - obstacle[0]->horizon;
						double b = enemy[i]->verticalTop + 25 - obstacle[0]->vertical;
						double c = sqrt(a*a + b*b);
						if (c <= EFFECTRADIUS) {
							enemy[i]->verticalTop += enemy[i]->speed;
							enemy[i]->direction = 2;
						}
						/*************以下检测敌方坦克是否该向上开火*****************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop - LENGTH - 1, enemy[i]->horizonTop, 3, 0, 100);
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
							++enemy[i]->direction %= 4;
						}

						for (int j = 0;j < 12;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						double a = enemy[i]->horizonTop + 25 - obstacle[0]->horizon;
						double b = enemy[i]->verticalTop + 25 - obstacle[0]->vertical;
						double c = sqrt(a*a + b*b);
						if (c <= EFFECTRADIUS) {
							enemy[i]->horizonTop -= enemy[i]->speed;
							enemy[i]->direction = 3;
						}
						/*************以下是敌人向右检测是否该开火******************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop + LENGTH + 1, 3, 1, 100);
						}
					}
					else 	enemy[i]->direction = 3; //如果超越了边界，就把电脑方向按规则调整一下
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

						for (int j = 0;j < 12;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						double a = enemy[i]->horizonTop + 25 - obstacle[0]->horizon;
						double b = enemy[i]->verticalTop + 25 - obstacle[0]->vertical;
						double c = sqrt(a*a + b*b);
						if (c <= EFFECTRADIUS) {
							enemy[i]->verticalTop -= enemy[i]->speed;
							enemy[i]->direction = 0;
						}
						/*************以下是敌人向下检测是否该开火******************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop + LENGTH + 1, enemy[i]->horizonTop, 3, 2, 100);
						}
					}
					else 	enemy[i]->direction = 0; //如果超越了边界，就把电脑方向按规则调整一下
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

						for (int j = 0;j < 12;j++)
						{
							if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								enemy[i]->direction = rand() % 4;
								break;
							}
						}
						double a = enemy[i]->horizonTop + 25 - obstacle[0]->horizon;
						double b = enemy[i]->verticalTop + 25 - obstacle[0]->vertical;
						double c = sqrt(a*a + b*b);
						if (c <= EFFECTRADIUS) {
							enemy[i]->horizonTop += enemy[i]->speed;
							enemy[i]->direction = 1;
						}
						/*************以下是敌人向左检测是否该开火******************/
						if (enemyBullet[i] == NULL)
						{
							enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop - LENGTH - 1, 3, 3, 100);
						}
					}
					else 	enemy[i]->direction = 1; //如果超越了边界，就把电脑方向按规则调整一下
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
					else //若敌人炮弹击中金球，炮弹消失
					{
						double ea = enemyBullet[i]->horizonTop + 25 - obstacle[0]->horizon;
						double eb = enemyBullet[i]->verticalTop + 25 - obstacle[0]->vertical;
						double ec = sqrt(ea*ea + eb*eb);
						if (ec <= ACTURERADIUS)
						{
							delete enemyBullet[i];
							enemyBullet[i] = NULL;
						}
					}
				}
			}
		} //在这里炮弹的移动和碰撞检测完毕
	}


	else if (my != NULL && gameOver != 1 && obstacle[3]->horizon <= TIMES + 50)
	{
		if (my->HP >= TIMES + 50)
		{
			my->HP = 0;
			obstacle[4]->horizon = ACTURERADIUS + 200;
			double x = obstacle[0]->horizon - obstacle[1]->horizon;
			double y = obstacle[0]->vertical - obstacle[1]->vertical;
			if (0 == x)
			{
				obstacle[3]->horizon = 0;
				if (y > 0) obstacle[3]->vertical = sqrt(SP);
				else obstacle[3]->vertical = -sqrt(SP);
			}
			else if (0 == y)
			{
				obstacle[3]->vertical = 0;
				if (x > 0)obstacle[3]->horizon = sqrt(SP);
				else obstacle[3]->horizon = -sqrt(SP);
			}
			else
			{
				double mul = (y / x);
				if (mul < 0.0) mul = -mul;
				double result = sqrt(x*x + y*y);
				if (result <= ACTURERADIUS * 2) //如果陨石砸在了金球上。。。
				{
					double X = sqrt(SP / (1 + mul*mul));
					double Y = X * mul;

					//这个用来给被砸跑的金球的水平速度赋值
					if (obstacle[1]->horizon < obstacle[0]->horizon)
					{
						obstacle[3]->horizon = X + 0.5;
					}
					else obstacle[3]->horizon = -(X + 0.5);

					//这个用来给被砸跑的金球的垂直速度赋值
					if (obstacle[0]->vertical > obstacle[1]->vertical)
					{
						obstacle[3]->vertical = Y + 0.5;
					}
					else obstacle[3]->vertical = -(Y + 0.5);
				}
				else //陨石没有砸在金球上，而是直接砸在我方坦克上，gameover阵亡！
				{
					text = L"您被星球陨石砸死，挑战失败！";
					goto fail;
				}
			}
		}
		obstacle[1]->horizon = my->horizonTop + 25;  //这个和下一句代码表示陨石始终瞄准主角坦克
		obstacle[1]->vertical = my->verticalTop + 25;

		obstacle[4]->horizon -= 4; //这个用来表示陨石掉落的速度
		my->HP++;
	}

	if (my!=NULL && gameOver != 1)
	{
		SelectObject(bufDc, backGround); //首先要贴上背景图
		BitBlt(mDc, 0, 0, WIDTH, HEIGHT + 20, bufDc, 0, 0, SRCCOPY);//这里不能用TransparentBlt

		if (my != NULL) //这里是贴上玩家的坦克图
		{
			SelectObject(bufDc, myDirection[my->direction]);
			TransparentBlt(mDc, my->horizonTop, my->verticalTop, LENGTH, LENGTH,
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

		SelectObject(bufDc, obbmp);
		TransparentBlt(mDc, obstacle[0]->horizon - ACTURERADIUS, obstacle[0]->vertical - ACTURERADIUS,
			ACTURERADIUS * 2, ACTURERADIUS * 2, bufDc, 0, 0, ACTURERADIUS * 2, ACTURERADIUS * 2, RGB(255, 255, 255));
		SelectObject(bufDc, bullet);
		if (myBullet != NULL) //贴上我们的子弹，如果有的话
		{
			TransparentBlt(mDc, myBullet->horizonTop, myBullet->verticalTop, LENGTH, LENGTH,
				bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		}

		//下面两段多余的代码，是为了给我们的坦克以及那个足球标注中心位置，以便玩家瞄准
		TransparentBlt(mDc, my->horizonTop, my->verticalTop, LENGTH, LENGTH,
			bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		TransparentBlt(mDc, obstacle[0]->horizon - 25, obstacle[0]->vertical - 25,
			LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));

		if (my->HP > TIMES)
		{
			SelectObject(bufDc, mass);
			TransparentBlt(mDc, obstacle[1]->horizon - obstacle[4]->horizon, obstacle[1]->vertical - obstacle[4]->horizon,
				obstacle[4]->horizon * 2, obstacle[4]->horizon * 2, bufDc, 0, 0, ACTURERADIUS * 2, ACTURERADIUS * 2, RGB(0, 0, 0));
		}
		BitBlt(hDc, 0, 0, WIDTH, HEIGHT + 20, mDc, 0, 0, SRCCOPY);
	}

	if (my != NULL && my->HP <= TIMES)
	{
		HPEN hpen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
		HPEN old = (HPEN)SelectObject(hDc, hpen);
		MoveToEx(hDc, 0, HEIGHT + 10, 0);
		LineTo(hDc, TIMES - my->HP, HEIGHT + 10);
		SelectObject(hDc, old);
		DeleteObject(hpen);
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

bool Game::InitLevel6()
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
	speedTemp = 5;
	enemyCount = 12;
	enemyBuCnt = 0;
	my = new Tank(475, 125, 3, 0, 0, false);
	obstacle[0] = new Obstacle(500, 500, true); //这个是我们的足球
	obstacle[1] = new Obstacle(0, 0, true);  //这个是敌人的星球陨石
	obstacle[3] = new Obstacle(0, 0, false); //这个是足球X轴和Y轴的速度
	obstacle[4] = new Obstacle(0, ACTURERADIUS + 200, false);
	for (int i = 0; i < 12; i++) //这里是初始化敌军位置和状态
	{
		enemy[i] = new Tank(159, (i + 3) * LENGTH, i % 4, 1, 100, true);
	}
	obbmp = (HBITMAP)LoadImage(NULL, L"image\\足球.bmp", IMAGE_BITMAP, ACTURERADIUS * 2, ACTURERADIUS * 2, LR_LOADFROMFILE);
	mass = (HBITMAP)LoadImage(NULL, L"image\\星球.bmp", IMAGE_BITMAP, ACTURERADIUS * 2, ACTURERADIUS * 2, LR_LOADFROMFILE);
	backGround = (HBITMAP)LoadImage(NULL, L"image\\backGround1.bmp", IMAGE_BITMAP, WIDTH, HEIGHT, LR_LOADFROMFILE); //读取这关游戏背景图
	//以下四行读取这关敌人图像
	enemyDirection0[0] = (HBITMAP)LoadImage(NULL, L"image\\6up.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[1] = (HBITMAP)LoadImage(NULL, L"image\\6right.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[2] = (HBITMAP)LoadImage(NULL, L"image\\6down.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	enemyDirection0[3] = (HBITMAP)LoadImage(NULL, L"image\\6left.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	myBullet = NULL;
	int count = 0;
	gameOver = 0;
	PlaySound(L"music\\6.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return false;
}