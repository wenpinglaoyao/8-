#include "Game.h"
#define ENEMYALL 4 //这个代表屏幕中最多存在敌人的数量
#define WID 800
#define HEI 800
#define SNOWSP 1  //雪崩的速度（要快于胜诉）
#define SOUNDWAVESP 1 //声波的速度
#define SOUNDWAVELEN 30 //声波的尺寸
#define SAFELEN  45 //这个是雪崩被巨石打断后的安全距离
void Game::FunState2()
{
	if (enemyCount == 4)
	{
		bool snow_exist = false;
		for (int i = 70;i < 94;i++)
			if (obstacle[i] != NULL)
				snow_exist = true;

		if (snow_exist == false)
		{
			text = L"恭喜您过关！";
			goto win;
		}
	}

	srand((unsigned)(time)(NULL));
	if (my != NULL && gameOver != 1)
	{
		switch (my->direction)
		{
		case 0: //我方向上
			if (my->verticalTop >= my->speed) //测试是否过边界
			{
				my->verticalTop -= my->speed; //如果没有，先位移一下
				for (int i = 0;i < ENEMYALL;i++) //挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL && enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						enemy[i]->verticalTop -= my->speed / 2;
						my->verticalTop += my->speed / 2;
						for (int j = 0;j <= ENEMYALL;j++)
						{
							if (i != j && enemy[j] != NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop += my->speed / 2;
								my->verticalTop += my->speed / 2;
								break;
							}
						}
					}
				}
				if (enemy[ENEMYALL]->BeCollide(my->verticalTop, my->horizonTop) == true) my->verticalTop += my->speed;
			}
			break;

		case 1:
			if (my->horizonTop <= WID - LENGTH - my->speed)//测试是否过边界
			{
				my->horizonTop += my->speed;//如果没有，先位移一下
				for (int i = 0;i < ENEMYALL;i++)
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)//挨个测试是否会撞到其它坦克
					{
						enemy[i]->horizonTop += my->speed / 2;
						my->horizonTop -= my->speed / 2;
						for (int j = 0;j <= ENEMYALL;j++)
						{
							if (i != j && enemy[j]!=NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop -= my->speed / 2;
								my->horizonTop -= my->speed / 2;
								break;
							}
						}
					}
				}
				if (enemy[ENEMYALL]->BeCollide(my->verticalTop, my->horizonTop) == true) my->horizonTop -= my->speed;
			}
			break;

		case 2:
			if (my->verticalTop <= HEI - LENGTH - my->speed)//测试是否过边界
			{
				my->verticalTop += my->speed;;//如果没有，先位移一下
				for (int i = 0;i < ENEMYALL;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						enemy[i]->verticalTop += my->speed / 2;
						my->verticalTop -= my->speed / 2;
						for (int j = 0;j <= ENEMYALL;j++)
						{
							if (i != j && enemy[j] != NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop -= my->speed / 2;
								my->verticalTop -= my->speed / 2;
								break;
							}
						}
					}
				}
				if (enemy[ENEMYALL]->BeCollide(my->verticalTop, my->horizonTop) == true) my->verticalTop -= my->speed;
			}
			break;

		case 3:;
			if (my->horizonTop >= my->speed)//测试是否过边界
			{
				my->horizonTop -= my->speed;;//如果没有，先位移一下
				for (int i = 0;i < ENEMYALL;i++)//挨个测试是否会撞到其它坦克
				{
					if (enemy[i] != NULL&&enemy[i]->BeCollide(my->verticalTop, my->horizonTop) == true)
					{
						enemy[i]->horizonTop -= my->speed / 2;
						my->horizonTop += my->speed / 2;
						for (int j = 0;j <= ENEMYALL;j++)
						{
							if (i != j && enemy[j] != NULL && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop += my->speed / 2;
								my->horizonTop += my->speed / 2;
								break;
							}
						}
					}
				}
				if (enemy[ENEMYALL]->BeCollide(my->verticalTop, my->horizonTop) == true) my->horizonTop += my->speed;
			}
			break;
		}

		if (my->fire == true && myBullet == NULL)
		{
			myBullet = new Bullet(my->verticalTop, my->horizonTop, 16, my->direction, 200);
			if (obstacle[ENEMYALL * 8] == NULL)
			{
				obstacle[ENEMYALL * 8] = new Obstacle(my->verticalTop, my->horizonTop, 0);
			}
			if (obstacle[ENEMYALL * 8+1] == NULL)
			{
				obstacle[ENEMYALL * 8+1] = new Obstacle(my->verticalTop, my->horizonTop, 1);
			}
			if (obstacle[ENEMYALL * 8+2] == NULL)
			{
				obstacle[ENEMYALL * 8+2] = new Obstacle(my->verticalTop, my->horizonTop, 2);
			}
			if (obstacle[ENEMYALL * 8+3] == NULL)
			{
				obstacle[ENEMYALL * 8+3] = new Obstacle(my->verticalTop, my->horizonTop, 3);
			}
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

			for (int i = 0;i < ENEMYALL;i++) //挨个测试敌人是否受到玩家攻击
			{
				if (enemy[i] != NULL&&myBullet != NULL)
				{
					if (enemy[i]->Hurt(myBullet->verticalTop + 25, myBullet->horizonTop + 25, myBullet->power) > 0)
					{
						if (obstacle[ENEMYALL * 4 + i * 4 + 0] == NULL) {
							obstacle[ENEMYALL * 4 + i * 4 + 0] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 0);
						}
						if (obstacle[ENEMYALL * 4 + i * 4 + 1] == NULL) {
							obstacle[ENEMYALL * 4 + i * 4 + 1] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 1);
						}
						if (obstacle[ENEMYALL * 4 + i * 4 + 2] == NULL) {
							obstacle[ENEMYALL * 4 + i * 4 + 2] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 2);
						}
						if (obstacle[ENEMYALL * 4 + i * 4 + 3] == NULL) {
							obstacle[ENEMYALL * 4 + i * 4 + 3] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 3);
						}

						delete enemy[i];
						enemy[i] = NULL;
						delete myBullet;
						myBullet = NULL;
					    
						enemyCount++;
					}
				}
			}
		}

		//接下来是敌人的移动
		if ((enemy[ENEMYALL]->speed++ % 3) == 0)
		{
			for (int i = 0;i < ENEMYALL; i++)
			{
				if (enemy[i] != NULL)
				{
					enemy[i]->HP += (rand()%100);
					if (enemy[i]->HP >= 9000)
					{
						enemy[i]->direction++;
						enemy[i]->direction = enemy[i]->direction % 4;
						enemy[i]->HP = 0;
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
								enemy[i]->direction = 1; //调整方向
							}

							for (int j = 0;j <= ENEMYALL;j++) //这里检测电脑坦克是否自己碰撞到自己人
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->verticalTop += enemy[i]->speed;
									enemy[i]->direction = 1; //调整方向
									break;
								}
							}

							/*************以下检测敌方坦克是否该向上开火*****************/
							if (my->horizonTop + 20 < enemy[i]->horizonTop + LENGTH && my->verticalTop<enemy[i]->verticalTop
								&& my->horizonTop + 30>enemy[i]->horizonTop && enemyBullet[i] == NULL)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop - LENGTH - 1, enemy[i]->horizonTop, 5, 0, 100);
								enemyBuCnt++;

								if (obstacle[i * 4 + 0] == NULL) {
									obstacle[i * 4 + 0] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 0);
								}
								if (obstacle[i * 4 + 1] == NULL) {
									obstacle[i * 4 + 1] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 1);
								}
								if (obstacle[i * 4 + 2] == NULL) {
									obstacle[i * 4 + 2] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 2);
								}
								if (obstacle[i * 4 + 3] == NULL) {
									obstacle[i * 4 + 3] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 3);
								}
							}
						}
						else 	enemy[i]->direction = 1; //如果超越了边界，就把电脑方向按规则调整一下

						break;

					case 1: //向右走
						if (enemy[i]->horizonTop <= WID - LENGTH - enemy[i]->speed)
						{
							enemy[i]->horizonTop += enemy[i]->speed;
							if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop -= enemy[i]->speed;
								enemy[i]->direction = 2;
							}

							for (int j = 0;j <= ENEMYALL;j++)
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->horizonTop -= enemy[i]->speed;
									enemy[i]->direction = 2; //调整方向
									break;
								}
							}

							/*************以下是敌人向右检测是否该开火******************/
							if (my->verticalTop + 20< enemy[i]->verticalTop + LENGTH && my->verticalTop + 30>enemy[i]->verticalTop
								&& my->horizonTop + 30 > enemy[i]->horizonTop && enemyBullet[i] == NULL)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop + LENGTH + 1, 5, 1, 100);
								enemyBuCnt++;

								if (obstacle[i * 4 + 0] == NULL) {
									obstacle[i * 4 + 0] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 0);
								}
								if (obstacle[i * 4 + 1] == NULL) {
									obstacle[i * 4 + 1] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 1);
								}
								if (obstacle[i * 4 + 2] == NULL) {
									obstacle[i * 4 + 2] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 2);
								}
								if (obstacle[i * 4 + 3] == NULL) {
									obstacle[i * 4 + 3] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 3);
								}
							}
						}
						else enemy[i]->direction = 2;
						break;

					case 2: //向下走
						if (enemy[i]->verticalTop <= HEI - LENGTH - enemy[i]->speed)
						{
							enemy[i]->verticalTop += enemy[i]->speed;
							if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->verticalTop -= enemy[i]->speed;
								enemy[i]->direction = 3;
							}

							for (int j = 0;j <= ENEMYALL;j++)
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->verticalTop -= enemy[i]->speed;
									enemy[i]->direction = 3; //调整方向
									break;
								}
							}

							/*************以下是敌人向下检测是否该开火******************/
							if (my->horizonTop + 20< enemy[i]->horizonTop + LENGTH && my->verticalTop + 30>enemy[i]->verticalTop
								&& my->horizonTop + 30 > enemy[i]->horizonTop && enemyBullet[i] == NULL)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop + LENGTH + 1, enemy[i]->horizonTop, 5, 2, 100);
								enemyBuCnt++;

								if (obstacle[i * 4 + 0] == NULL) {
									obstacle[i * 4 + 0] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 0);
								}
								if (obstacle[i * 4 + 1] == NULL) {
									obstacle[i * 4 + 1] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 1);
								}
								if (obstacle[i * 4 + 2] == NULL) {
									obstacle[i * 4 + 2] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 2);
								}
								if (obstacle[i * 4 + 3] == NULL) {
									obstacle[i * 4 + 3] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 3);
								}
							}
						}
						else 	enemy[i]->direction = 3;
						break;

					case 3: //向左走
						if (enemy[i]->horizonTop >= enemy[i]->speed)
						{
							enemy[i]->horizonTop -= enemy[i]->speed;
							if (my->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
							{
								enemy[i]->horizonTop += enemy[i]->speed;
								enemy[i]->direction = 0;
							}

							for (int j = 0;j <= ENEMYALL;j++)
							{
								if (enemy[j] != NULL&&j != i && enemy[j]->BeCollide(enemy[i]->verticalTop, enemy[i]->horizonTop) == true)
								{
									enemy[i]->horizonTop += enemy[i]->speed;
									enemy[i]->direction = 0; //调整方向
									break;
								}
							}
							/*************以下是敌人向左检测是否该开火******************/
							if (my->verticalTop + 20< enemy[i]->verticalTop + LENGTH && my->verticalTop + 30 > enemy[i]->verticalTop
								&& my->horizonTop + 30 < enemy[i]->horizonTop && enemyBullet[i] == NULL)
							{
								enemyBullet[i] = new Bullet(enemy[i]->verticalTop, enemy[i]->horizonTop - LENGTH - 1, 5, 3, 100);
								enemyBuCnt++;

								if (obstacle[i * 4 + 0] == NULL) {
									obstacle[i * 4 + 0] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 0);
								}
								if (obstacle[i * 4 + 1] == NULL) {
									obstacle[i * 4 + 1] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 1);
								}
								if (obstacle[i * 4 + 2] == NULL) {
									obstacle[i * 4 + 2] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 2);
								}
								if (obstacle[i * 4 + 3] == NULL) {
									obstacle[i * 4 + 3] = new Obstacle(enemy[i]->verticalTop, enemy[i]->horizonTop, 3);
								}
							}
						}
						else enemy[i]->direction = 0;
						break;
					}
				}
			}
		}

		for (int i = 0;i < ENEMYALL; i++)//这个是子弹的移动和检测是否攻击到坦克
		{
			if (enemyBullet[i] != NULL) //如果子弹还存在
			{
				switch (enemyBullet[i]->direction)//获取炮弹的发射方向
				{
				case 0: //向上射击
					enemyBullet[i]->verticalTop -= enemyBullet[i]->speed; //让炮弹飞
					if (enemyBullet[i]->verticalTop < -0) //让敌人的炮弹在屏幕外面多飞一会
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
						enemyBuCnt--;
					}
					break;

				case 1:
					enemyBullet[i]->horizonTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop > WID )
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
						enemyBuCnt--;
					}
					break;

				case 2:
					enemyBullet[i]->verticalTop += enemyBullet[i]->speed;
					if (enemyBullet[i]->verticalTop > HEI)
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
						enemyBuCnt--;
					}
					break;

				case 3:
					enemyBullet[i]->horizonTop -= enemyBullet[i]->speed;
					if (enemyBullet[i]->horizonTop < 0)
					{
						delete enemyBullet[i];
						enemyBullet[i] = NULL;
						enemyBuCnt--;
					}
					break;
				}

				if (enemyBullet[i] != NULL&&my != NULL) //这里测试玩家是否受伤
				{
					if (my->Hurt(enemyBullet[i]->verticalTop + LENGTH / 2, enemyBullet[i]->horizonTop + LENGTH / 2, enemyBullet[i]->power) > 0) {
						text = L"你被敌人炮弹击中，第3关挑战失败！";
						goto fail;
					}
				}
			}
		} //在这里炮弹的移动和碰撞检测完毕

		for (int i = 0;i < 70;i++)
		{
			if (obstacle[i] != NULL)
			{
				switch (obstacle[i]->HP)
				{
				case 0:
					obstacle[i]->vertical -= SOUNDWAVESP;
					if (obstacle[i]->vertical < 0) //如果声波超越边界，产生对应的雪崩
					{
						
						for (int j = 70;j < 94;j += 4)
						{
							if (obstacle[j] == NULL)
							{
								obstacle[j] = new Obstacle(-LENGTH, 0, 0);
								break;
							}
						}
						delete obstacle[i];
						obstacle[i] = NULL;
					}
					break;

				case 1:
					obstacle[i]->horizon += SOUNDWAVESP;
					if (obstacle[i]->horizon > WID)
					{
						delete obstacle[i];
						obstacle[i] = NULL;
						for (int j = 71;j < 94;j += 4)
						{
							if (obstacle[j] == NULL)
							{
								obstacle[j] = new Obstacle(0, WID, 0);
								break;
							}
						}
					}
					break;

				case 2:
					obstacle[i]->vertical += SOUNDWAVESP;
					if (obstacle[i]->vertical > HEI)
					{
						delete obstacle[i];
						obstacle[i] = NULL;
						for (int j = 72;j < 94;j += 4)
						{
							if (obstacle[j] == NULL)
							{
								obstacle[j] = new Obstacle(HEI, 0, 0);
								break;
							}
						}
					}
					break;

				case 3:
					obstacle[i]->horizon -= SOUNDWAVESP;
					if (obstacle[i]->horizon < 0)
					{
						delete obstacle[i];
						obstacle[i] = NULL;
						for (int j = 73;j < 94;j += 4)
						{
							if (obstacle[j] == NULL)
							{
								obstacle[j] = new Obstacle(0, -LENGTH, 0);
								break;
							}
						}
					}
					break;
				}
			}
		}

		for (int i = 70;i < 94;i++) //这里的雪崩的更新代码
		{
			switch ((i-70) % 4)
			{
			case 0: //雪崩向下走
				if (obstacle[i] != NULL)
				{
					if (my->verticalTop + 25 > obstacle[i]->vertical && 
						my->verticalTop + 25 < obstacle[i]->vertical + LENGTH)
					{
						if (obstacle[i]->HP == 250)
						{
							if (my->horizonTop + 25 <= WID / 2 - SAFELEN
								|| my->horizonTop + 25 >= WID / 2 + SAFELEN)
							{
								text = L"您被雪崩压死，挑战失败！";
								goto fail;
							}
						}
						else {
							text = L"您被雪崩压死，挑战失败！";
							goto fail;
						}
					}
					
					obstacle[i]->vertical += SNOWSP;
					
					if (obstacle[i]->vertical+LENGTH/2 > HEI/2)
					{
						obstacle[i]->HP = 250;
					}
					if (obstacle[i]->vertical > HEI)
					{
						delete obstacle[i]; obstacle[i] = NULL;
					}
				}
				break;

			case 1: //向左走
				if (obstacle[i] != NULL)
				{
					if (my->horizonTop + 25 > obstacle[i]->horizon &&
						my->horizonTop + 25 < obstacle[i]->horizon + LENGTH)
					{
						if (obstacle[i]->HP == 250)
						{
							if (my->verticalTop + 25 <= HEI / 2 - SAFELEN
								|| my->verticalTop + 25 >= HEI / 2 + SAFELEN)
							{
								text = L"您被雪崩压死，挑战失败！";
								goto fail;
							}
						}
						else {
							text = L"您被雪崩压死，挑战失败！";
							goto fail;
						}
					}
					
					obstacle[i]->horizon -= SNOWSP;
					
					if (obstacle[i]->horizon + LENGTH / 2 < WID / 2)
					{
						obstacle[i]->HP = 250;
					}
					if (obstacle[i]->horizon < 0)
					{
						delete obstacle[i];obstacle[i] = NULL;
					}
				}
				break;

			case 2: //向上走
				if (obstacle[i] != NULL)
				{
					if (my->verticalTop + 25 > obstacle[i]->vertical &&
						my->verticalTop + 25 < obstacle[i]->vertical + LENGTH)
					{
						if (obstacle[i]->HP == 250)
						{
							if (my->horizonTop + 25 <= WID / 2 - SAFELEN
								|| my->horizonTop + 25 >= WID / 2 + SAFELEN)
							{
								text = L"您被雪崩压死，挑战失败！";
								goto fail;
							}
						}
						else {
							text = L"您被雪崩压死，挑战失败！";
							goto fail;
						}
					}
					
					obstacle[i]->vertical -= SNOWSP;
					
					if (obstacle[i]->vertical + LENGTH / 2 < HEI / 2)
					{
						obstacle[i]->HP = 250;
					}
					if (obstacle[i]->vertical < 0)
					{
						delete obstacle[i];obstacle[i] = NULL;
					}
				}
				break;

			case 3: //向右走
				if (obstacle[i] != NULL)
				{
					if (my->horizonTop + 25 > obstacle[i]->horizon &&
						my->horizonTop + 25 < obstacle[i]->horizon + LENGTH)
					{
						if (obstacle[i]->HP == 250)
						{
							if (my->verticalTop + 25 <= HEI / 2 - SAFELEN
								|| my->verticalTop + 25 >= HEI / 2 + SAFELEN)
							{
								text = L"您被雪崩压死，挑战失败！";
								goto fail;
							}
						}
						else {
							text = L"您被得当雪崩压死，挑战失败！";
							goto fail;
						}
					}
					
					obstacle[i]->horizon += SNOWSP;
					
					if (obstacle[i]->horizon + LENGTH/2 > WID / 2)
					{
						obstacle[i]->HP = 250;
					}
					if (obstacle[i]->horizon > WID)
					{
						delete obstacle[i];obstacle[i] = NULL;
					}
				}
				break;
			}
		}
		if (1)
		{
			SelectObject(bufDc, backGround);
			BitBlt(mDc, 0, 0, WID, HEI, bufDc, 0, 0, SRCCOPY);//这里不能用TransparentBlt

			if (my != NULL)
			{
				SelectObject(bufDc, myDirection[my->direction]);
				TransparentBlt(mDc, my->horizonTop, my->verticalTop, LENGTH, LENGTH,
					bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}

			for (int i = 70;i < 94;i++) //贴上雪崩
			{
				switch ((i - 70) % 4)
				{
				case 0:
				case 2:
					if (obstacle[i] != NULL)
					{
						SelectObject(bufDc, boom);
						TransparentBlt(mDc, obstacle[i]->horizon, obstacle[i]->vertical,
							WID, LENGTH, bufDc, 0, 0, WID, LENGTH, RGB(obstacle[i]->HP, obstacle[i]->HP, obstacle[i]->HP));
					}
					break;
				case 1:
				case 3:
					if (obstacle[i] != NULL)
					{
						SelectObject(bufDc, bmp);
						TransparentBlt(mDc, obstacle[i]->horizon, obstacle[i]->vertical,
							 LENGTH, HEI, bufDc, 0, 0, LENGTH, HEI, RGB(obstacle[i]->HP, obstacle[i]->HP, obstacle[i]->HP));
					}
					break;
				}

			}
			if (myBullet != NULL)
			{
				SelectObject(bufDc, bullet);
				TransparentBlt(mDc, myBullet->horizonTop, myBullet->verticalTop, LENGTH, LENGTH,
					bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
			}

			for (int i = 0;i < ENEMYALL;i++)
			{
				if (enemy[i] != NULL)
				{
					SelectObject(bufDc, enemyDirection0[enemy[i]->direction]);
					TransparentBlt(mDc, enemy[i]->horizonTop, enemy[i]->verticalTop, LENGTH, LENGTH,
						bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
				}
			}
			for (int i = 0;i < ENEMYALL;i++)
			{
				if (enemyBullet[i] != NULL)
				{
					SelectObject(bufDc, bullet);
					TransparentBlt(mDc, enemyBullet[i]->horizonTop, enemyBullet[i]->verticalTop,
						LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
				}
			}

			SelectObject(bufDc, obbmp);
			TransparentBlt(mDc, enemy[ENEMYALL]->horizonTop-10, enemy[ENEMYALL]->verticalTop-10,
				LENGTH+10, LENGTH+10, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));

			for (int i = 0;i < 60;i++) //贴上障碍物
			{
				if (obstacle[i] != NULL)
				{
					SelectObject(bufDc, mass);
					TransparentBlt(mDc, obstacle[i]->horizon, obstacle[i]->vertical,
						LENGTH, LENGTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
				}
			}
			BitBlt(hDc, 0, 0, WID, HEI, mDc, 0, 0, SRCCOPY);
		}
		timePre = GetTickCount();
	}
	return;
win:
	level++;
fail:
	gameOver = 1;/*level++;*/
	delete my;
	my = NULL;

	HFONT hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(hDc, hFont);
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));
	TextOut(hDc, 150, 200, text, wcslen(text));
	DeleteObject(hFont);
	;
}

bool Game::InitLevel2()
{
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

	speedTemp = 8;
	backGround = (HBITMAP)::LoadImage(NULL, L"image\\backGround.bmp", IMAGE_BITMAP, WID, HEI, LR_LOADFROMFILE);
	mass = (HBITMAP)::LoadImage(NULL, L"image\\soundwave.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);
	boom = (HBITMAP)::LoadImage(NULL, L"image\\横雪.bmp", IMAGE_BITMAP, WID, LENGTH, LR_LOADFROMFILE);
	bmp = (HBITMAP)::LoadImage(NULL, L"image\\竖雪.bmp", IMAGE_BITMAP, LENGTH, WID, LR_LOADFROMFILE);
	my = new Tank(100, 100, 0, 4, 100, false);
	for (int i = 0; i < ENEMYALL; i++) //这里是初始化敌军位置和状态
	{
		enemy[i] = new Tank((i + 3)* LENGTH, (i + 3) * LENGTH, 0, 1, 100, false);
	}
	enemy[ENEMYALL] = new Tank(HEI/2-LENGTH/2, WID/2-LENGTH/2, 0, 0, 0, false);
	myBullet = NULL;
	gameOver = 0;
	enemyCount = 0;
	return false;
}