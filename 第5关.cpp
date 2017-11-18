#include "Game.h"
#define ALL 6

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
				for (int i = 0;i < ALL;i++)//挨个测试是否会撞到其它坦克
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
				for (int i = 0;i < ALL;i++)//挨个测试是否会撞到其它坦克
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


		if (my->fire == true)
		{
			my->fire = false;
			if (myBullet == NULL)
			{
				myBullet = new Bullet(my->verticalTop, my->horizonTop, 16, my->direction, 200);
			}

			for (int a = 0;a < ALL;a++)
				if (enemyBullet[a] == NULL && enemy[a] != NULL)
					enemyBullet[a] = new Bullet(enemy[a]->verticalTop, enemy[a]->horizonTop, 16, enemy[a]->direction, 100);
		}
		if (myBullet != NULL)
		{
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
						if (--enemyCount > 6) {
							int x, y;bool flag;
						start:
							x = rand() % (WIDTH - 200) + 79;y = rand() % (HEIGHT - 200) + 79;flag = true;
							if (my->BeCollide(y, x) == true) flag = false;
							for (int i = 0;i < ALL;i++)
								if (enemy[i] != NULL&&enemy[i]->BeCollide(y, x) == true)
									flag = false;
							if (flag == true) {
								delete enemy[i];
								enemy[i] = new Tank(y, x, 0, 1, 100, true);
							}
							else goto start;
						}
						else {
							--enemyCount;
							delete enemy[i];
							enemy[i] = NULL;
						}
					}
				}
			}
		}
		
		/////////////////我们改动到这里了！！！！该下面了///////////////////
		for (int i = 0;i < ALL; i++)
		{
			if (enemy[i] != NULL)
			{
				if (rand() % 4 == 1)
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


						for (int j = 0;j < ALL;j++) //这里检测电脑坦克是否自己碰撞到自己人
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
					}
					else enemy[i]->direction = (enemy[i]->direction + 2) % 4;
					break;

				case 1: //向右走
					if (enemy[i]->horizonTop <= WIDTH - LENGTH - enemy[i]->speed)
					{
						enemy[i]->horizonTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							enemy[i]->horizonTop -= enemy[i]->speed;

						for (int j = 0;j < ALL;j++)
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
					}
					else enemy[i]->direction = (enemy[i]->direction + 2) % 4;
					break;

				case 2: //向下走
					if (enemy[i]->verticalTop <= HEIGHT - LENGTH - enemy[i]->speed)
					{
						enemy[i]->verticalTop += enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							enemy[i]->verticalTop -= enemy[i]->speed;

						for (int j = 0;j < ALL;j++)
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
					}
					else enemy[i]->direction = (enemy[i]->direction + 2) % 4;
					break;

				case 3: //向左走
					if (enemy[i]->horizonTop >= enemy[i]->speed)
					{
						enemy[i]->horizonTop -= enemy[i]->speed;
						if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							enemy[i]->horizonTop += enemy[i]->speed;

						for (int j = 0;j < ALL;j++)
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
					}
					else enemy[i]->direction = (enemy[i]->direction + 2) % 4;
					break;
				}
			}
		}

		for (int i = 0;i < ALL; i++)//这个是敌人子弹的移动和检测是否攻击到坦克
		{
			if (enemyBullet[i] != NULL) //如果子弹还存在
			{
				for (int j = 0;j < ALL;j++)
				{
					if (j != i && enemy[j] != NULL
						&& enemy[j]->Hurt(enemyBullet[i]->verticalTop + LENGTH / 2, enemyBullet[i]->horizonTop + LENGTH / 2, enemyBullet[i]->power) > 0)
					{
						text = L"敌人自相残杀了，您完成不了任务数量，挑战失败!";
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
						text = L"你被敌人炮弹击中，哈哈哈！";
						goto fail;
					}
				}
			}
		} //在这里炮弹的移动和碰撞检测完毕
	}
	if (enemyCount <= -4) {
		text = L"恭喜您过关，按下TAB进入下一关";
		/*goto win;*/
	}

	GamePaint();
	timePre = GetTickCount(); //获取当前时间
	return;

win:
	;
fail:
	HFONT hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(hDc, hFont);
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));
	TextOut(hDc, 150, 200, text, wcslen(text));
	DeleteObject(hFont);
	gameOver = 1;
	level++;
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

	speedTemp = 4;enemyCount = 20;
	my = new Tank(100, 0, 0, 2, 100, true);
	for (int i = 0; i < ALL; i++) //这里是初始化敌军位置和状态
	{
		enemy[i] = new Tank((i + 3)* LENGTH, (i + 3) * LENGTH, i%4, 1, 100, true);
	}
	myBullet = NULL;
	int count = 0;
	gameOver = 0;
	return false;
}