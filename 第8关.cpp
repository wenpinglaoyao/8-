#include "Game.h"
#include <math.h>
#define SPU 20 //子弹撞击BOSS后的溅射半径
#define POWER 10 //这个代表我们的火力
#define BOSSWIDTH 100 //BOSS图像的宽度,BOSS用的中心点表示法
#define BOSSHEIGHT 100 //BOSS图像的高度
#define BOSSSPEED 120  //这个是BOSS神出鬼没的速度（最后要除以100的）
#define BULLETRADIUS 30 //这个是天女散花的子弹半径
#define BULLETSPEED 8   //这个是天女散花的子弹速度
#define BOOMRADIUS 130     //这个是狂轰滥炸的最大爆炸半径
#define BOOMSPEED 4        //这个是狂轰滥炸爆炸扩张速度
#define WALLRADIUS 40 //这个是障碍物的半径
#define HALF  60  //这个是小卒的直径
#define SSS 30000 //这个代表BOSS神出鬼没的加速值，值越高，加速越慢！
double x, y, xs, ys; //x与y是BOSS神出鬼没时的坐标值，xs与ys是神出鬼没时的两个速度值
int falx, faly; //这两个代表BOSS神出鬼没时的假身所在位置
int sparkX,sparkY ; //这两个代表射中BOSS身体时溅起的火花位置（平时隐藏起来）
bool Game::InitLevel8()
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

	speedTemp = 8;enemyCount = 0;enemyBuCnt = 0;
	my = new Tank(700, 500, 0, 0, 300, false);
	enemy[0] = new Tank(500, 500, 0, 2, 1000, false); //这个就是BOSS
	obstacle[99] = new Obstacle(0, 0, 0);  //ver代表炸弹数量，hori代表小卒数量
	obstacle[98] = new Obstacle(0, 1, 0); //ver代表横冲蛮撞的持续时间，hori代表横冲蛮撞的速度
	for (int i = 50;i < 70;i++) //这些代表横冲蛮撞的幻影记录表
		obstacle[i] = new Obstacle(-1000, -1000, 0);
	obstacle[97] = new Obstacle(0, 0, 0); //其中我们用horizon代表神出鬼没的碰壁次数
	obstacle[96] = new Obstacle(0, 0, 0); //这个是代表神出鬼没时的水平速度和垂直速度
	mass = (HBITMAP)::LoadImage(NULL, L"image\\BOSS.bmp", IMAGE_BITMAP, BOSSWIDTH*2, BOSSHEIGHT*2, LR_LOADFROMFILE);//读取BOSS背景图
	enemyDirection0[0] = (HBITMAP)::LoadImage(NULL, L"image\\绿球.bmp", IMAGE_BITMAP, HALF, HALF, LR_LOADFROMFILE);//读取外星小兵背景图
	enemyDirection0[1] = (HBITMAP)::LoadImage(NULL, L"image\\太极环.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);//读取子弹背景图
	enemyDirection0[2] = (HBITMAP)::LoadImage(NULL, L"image\\BOOM.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);//读取爆炸范围背景图
	enemyDirection0[3] = (HBITMAP)::LoadImage(NULL, L"image\\光球.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE);//读取炸弹模样背景图
	obbmp = (HBITMAP)::LoadImage(NULL, L"image\\墙.bmp", IMAGE_BITMAP, WALLRADIUS * 2, WALLRADIUS * 2, LR_LOADFROMFILE);//读取障碍物背景图
	bmp = (HBITMAP)::LoadImage(NULL, L"image\\红怒.bmp", IMAGE_BITMAP, HALF, HALF, LR_LOADFROMFILE);  //读取怒卒背景图
	bullet = (HBITMAP)::LoadImage(NULL, L"image\\大海.bmp", IMAGE_BITMAP, LENGTH, LENGTH, LR_LOADFROMFILE); //读取大海背景
	gameOver = 0;
	return false;
}

void Game::FunState8()
{
	srand((unsigned)(time)(NULL));
	if (my != NULL && gameOver != 1)
	{
		//首先看看BOSS是否撞到玩家
		if (enemy[0]->horizonTop - BOSSWIDTH<my->horizonTop &&
			enemy[0]->horizonTop + BOSSWIDTH>my->horizonTop &&
			enemy[0]->verticalTop - BOSSHEIGHT < my->verticalTop &&
			enemy[0]->verticalTop + BOSSHEIGHT >my->verticalTop)
			my->HP -= 1000;
		if (my->HP <= 0)
		{
			text = L"您已阵亡，游戏失败！";
			goto fail;
		}
		SelectObject(bufDc, backGround);
		BitBlt(mDc, 0, 0, WIDTH, HEIGHT, bufDc, 0, 0, SRCCOPY);//这两行代码用来更新背景图

		SelectObject(bufDc, bullet);
		TransparentBlt(mDc, 0, 0, WIDTH, BOSSHEIGHT, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		TransparentBlt(mDc, 0, 0, BOSSHEIGHT, HEIGHT, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		TransparentBlt(mDc, WIDTH - BOSSWIDTH, 0, BOSSWIDTH, HEIGHT, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		TransparentBlt(mDc, 0, HEIGHT - BOSSHEIGHT, WIDTH, BOSSWIDTH, bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		switch (my->direction) //下面这些是玩家位置的更新
		{
		case 0:
			if (my->verticalTop > BOSSWIDTH + my->speed) my->verticalTop -= my->speed;
			break;
		case 1:
			if (my->horizonTop < WIDTH - BOSSWIDTH - my->speed) my->horizonTop += my->speed;
			break;
		case 2:
			if (my->verticalTop < HEIGHT -BOSSWIDTH - my->speed) my->verticalTop += my->speed;
			break;
		case 3:
			if (my->horizonTop > BOSSWIDTH + my->speed) my->horizonTop -= my->speed;
			break;
		}
		SelectObject(bufDc, myDirection[my->direction]);
		TransparentBlt(mDc, my->horizonTop - 25, my->verticalTop - 25, LENGTH, LENGTH,
			bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0)); //至此，玩家更新结束并贴图

	BOSS:
		for (int i = 1;i < 12;i++) //这是小卒上吧的更新
		{
			if (enemy[i] != NULL)
			{
				if (enemy[i]->fire == false) //如果小卒还没有被引爆
				{
					if (rand() % 2 == 0) //这块负责小卒们的水平移动
					{
						int a = (rand() % 3) - 1;
						if (enemy[i]->horizonTop + a*enemy[i]->speed > 0 + 25 &&
							enemy[i]->horizonTop + a*enemy[i]->speed < WIDTH - 25) //这两句用于检测水平是否越界，是就归位
							enemy[i]->horizonTop += a*enemy[i]->speed;
					}
					else //而这块则负责小卒们的垂直移动 
					{
						int a = (rand() % 3) - 1;
						if (enemy[i]->verticalTop + a*enemy[i]->speed > 0 + 25 &&
							enemy[i]->verticalTop + a*enemy[i]->speed < HEIGHT - 25)//垂直是否越界，是则归位
							enemy[i]->verticalTop+= a*enemy[i]->speed;
					}

					if (enemy[i]->speed == 1) //小卒没被激怒前的移动
					{
						double ex = my->horizonTop - enemy[i]->horizonTop;
						double ey = my->verticalTop - enemy[i]->verticalTop;
						if (sqrt(ex*ex + ey*ey) < (HALF + LENGTH) / 2)
						{
							my->HP -= 1;
						} //以上这些用于处理龟卒撞到玩家

						SelectObject(bufDc, enemyDirection0[0]);
						TransparentBlt(mDc, enemy[i]->horizonTop - HALF/2, enemy[i]->verticalTop - HALF/2, HALF, HALF,
							bufDc, 0, 0, HALF, HALF, RGB(0, 0, 0));
					}
					else //小卒被激怒（中了BOSS的狂轰滥炸技能）后的状态
					{
						double ex = my->horizonTop - enemy[i]->horizonTop;
						double ey = my->verticalTop - enemy[i]->verticalTop;
						if (sqrt(ex*ex + ey*ey) < (HALF + LENGTH) / 2)
						{
							my->HP -= 5;
						} //以上这些用于处理怒卒撞到玩家

						SelectObject(bufDc, bmp);
						TransparentBlt(mDc, enemy[i]->horizonTop - HALF/2, enemy[i]->verticalTop - HALF/2, HALF, HALF,
							bufDc, 0, 0, HALF, HALF, RGB(255, 255, 255));
					}
				}
				else if (enemy[i]->fire == true) //小卒被玩家炮弹击中后，会引爆自身
				{
					double x[12] = { -1, -0.8660254, -0.5, 0, 0.5, 0.8660254, 1, 0.8660254, 0.5, 0, -0.5, -0.8660254 };//这个是12花的水平值
					double y[12] = { 0 ,-0.5, -0.8660254, -1, -0.8660254, -0.5, 0, 0.5, 0.8660254, 1, 0.8660254, 0.5 };//12花的垂直值

					for (int a=0;a<12;a++) //12个天女花
					{
						int ax = enemy[i]->horizonTop + enemy[i]->HP*x[a];
						int ay = enemy[i]->verticalTop + enemy[i]->HP*y[a];

						double dogface_x = ax - my->horizonTop;
						double dogface_y = ay - my->verticalTop;

						if (sqrt(dogface_x*dogface_x + dogface_y*dogface_y) <= LENGTH/2)
						{
							text = L"您被天女散花打死，挑战失败";
							goto fail;
							my->HP -= 5;
						}
						SelectObject(bufDc, enemyDirection0[1]);
						TransparentBlt(mDc, ax-25, ay-25, LENGTH, LENGTH,
							bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));//天女散花的贴图
						for (int b = 1;b < 12;b++) //测试是否有别的小卒被引爆
						{
							if (enemy[b] != NULL && b != i)
							{
								double dogface_X = ax - enemy[b]->horizonTop;
								double dogface_Y = ay - enemy[b]->verticalTop;

								if (sqrt(dogface_X*dogface_X + dogface_Y*dogface_Y) <= (HALF+LENGTH)/2 )
								{
									enemy[b]->fire = true;//天女散花击中别的小卒，该小卒被引爆
								}
							}
						}
					}
					enemy[i]->HP += BULLETSPEED; //这个HP的意思是天女散花飞出的半径
					if (enemy[i]->HP > 1300) //小卒的天女散花飞出界外，该小卒消失掉
					{
						delete enemy[i];
						enemy[i] = NULL;
					}
				}
			}
		}

		for (int i = 0;i < obstacle[99]->vertical;i++) //这段代码用于更新狂轰滥炸
		{
			if (obstacle[i] != NULL)
			{
				if (obstacle[20 + i]->vertical > 0) //这里的vertical代表狂轰滥炸是否在爆炸（小于0爆炸）
				{
					obstacle[20 + i]->vertical -= 1; //光球缩小
					if (obstacle[20 + i]->vertical < 70) //如果光球半径小于指定值，那么给该光球贴图
					{
						SelectObject(bufDc, enemyDirection0[3]);
						TransparentBlt(mDc, obstacle[i]->horizon, obstacle[i]->vertical, obstacle[20 + i]->vertical, obstacle[20 + i]->vertical,
							bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
					}
				}
				else //狂轰滥炸之炸弹被引爆的处理
				{
					double bx = my->horizonTop - obstacle[i]->horizon, by = my->verticalTop - obstacle[i]->vertical;
					if (sqrt(bx*bx + by*by) < obstacle[20 + i]->horizon)
					{
						my->HP -= 5;
					}
					obstacle[20 + i]->horizon += BOOMSPEED; //这个是爆炸半径扩张的速度
					SelectObject(bufDc, enemyDirection0[2]);
					TransparentBlt(mDc, obstacle[i]->horizon - obstacle[20 + i]->horizon, 
						obstacle[i]->vertical- obstacle[20 + i]->horizon, 
						obstacle[20 + i]->horizon*2, obstacle[20 + i]->horizon*2,
						bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));

					if (obstacle[20 + i]->horizon >= BOOMRADIUS) //如果爆炸范围大于150，那么爆炸消失
					{
						delete obstacle[i];delete obstacle[20 + i];
						obstacle[i] = NULL; obstacle[20 + i] = NULL;
					}
					
					for (int ei = 1;ei < 12;ei++)//这是检测爆炸是否炸到小卒，若是则激活小卒的狂暴状态
					{
						if (enemy[ei] != NULL && obstacle[i] != NULL)
						{
							int bx = enemy[ei]->horizonTop - 25 - obstacle[i]->horizon;
							int by = enemy[ei]->verticalTop - 25 - obstacle[i]->vertical;
							int bc = sqrt(bx*bx + by*by);
							if (bc < obstacle[20 + i]->horizon)
							{
								enemy[ei]->speed = 10; //把小卒的行走速度变快，就是狂暴了。。。
							}
						}
					}

				}
			}
		}

	    //这里的boss的处理
		enemy[0]->speed++; //这里的speed代表BOSS的蓝量
		if (enemy[0]->direction <= 3) 
		{
			if (enemy[0]->speed > enemy[0]->HP ) //BOSS的CD已满，可以释放技能了
			{
				enemy[0]->speed = 0; //开始CD冷却时间

				if (enemy[0]->direction == 0) //这里的direction代表BOSS的技能轮换（BOSS轮流释放技能），这里是小卒上吧的技能
				{
					int count = 0;
					for (int i = 1;i < 12;i++)
					{
						if (enemy[i] == NULL)
						{
							if (count++ < 2)
								enemy[i] = new Tank(enemy[0]->verticalTop, enemy[0]->horizonTop, 0, 1, 0, 0);
						}
					}
				}

				else if (enemy[0]->direction == 1) //这里是狂轰滥炸的技能
				{
					obstacle[99]->vertical = 16 /*+ (1000 - enemy[0]->HP) / 200*/; //obstacle[99].vertical代表狂轰滥炸的陨石炸弹数量（BOSS血越少炸弹越多）
					for (int i = 0;i < obstacle[99]->vertical;i++) //随机生成这些炸弹
					{
						if (obstacle[i] == NULL)
						{
							obstacle[i] = new Obstacle(rand() % HEIGHT, rand() % WIDTH, 0);
							obstacle[20 + i] = new Obstacle(rand() % 70 + 70, 0, 0);
						}
					}
				}
				else if (enemy[0]->direction == 2)//这里是横冲蛮撞的技能更新
				{
					obstacle[98]->vertical = 1;
					obstacle[98]->horizon = 10;
				}

				enemy[0]->direction++; //更换下一个技能
			}
			if (obstacle[98]->vertical > 0)
			{
				enemy[0]->speed = 0;
				obstacle[98]->vertical++;

				obstacle[50]->vertical = enemy[0]->verticalTop; //首先设置第一个紧跟后面的影子的垂直值
				obstacle[50]->horizon = enemy[0]->horizonTop;   //再设置第一个幻影的水平值
				for (int i = 69;i > 50;i--)
				{
					if (i > 50 && i < 69) 
					{
						if (obstacle[i]->horizon > 0 && obstacle[i]->vertical > 0)
						{
							SelectObject(bufDc, mass);
							TransparentBlt(mDc, obstacle[i]->horizon - BOSSWIDTH, obstacle[i]->vertical - BOSSHEIGHT,
								BOSSWIDTH * 2, BOSSHEIGHT * 2, bufDc, 0, 0, BOSSWIDTH * 2, BOSSHEIGHT * 2,
								RGB(255, 255, 255));
						}
						obstacle[i]->horizon = obstacle[i - 1]->horizon;
						obstacle[i]->vertical = obstacle[i - 1]->vertical;
					}
				}
				if (obstacle[98]->vertical > 150) //把这个放在上面的for选循环后很关键，不然会有不合理的幻影位置（上一次的）
				{
					for (int i = 50; i < 70;i++)
						obstacle[i]->vertical = -1000, obstacle[i]->horizon = -1000;

					obstacle[98]->vertical = 0; obstacle[98]->horizon = 1;
				}
			}
		
		BOSSSHIFT: //这里是BOSS的位移，随机位移，会斜着走
			int bossx=0, bossy=0; 
			if (obstacle[98]->vertical >= 1) //如果BOSS处于横冲蛮撞状态
			{
				int g, h;
				if (rand() % 2 == 0) g = 1; //随机左右走
				else g = -1;
				if (rand() % 2 == 0) h = 1; //随机上下走
				else h = -1;
				bossx = rand() % obstacle[98]->horizon; //随机获取水平移动速度
				bossy = obstacle[98]->horizon - bossx;  //总速度恒定，垂直移动速度就是减去水平移动速度
				bossx *= g, bossy *= h; //合成BOSS的横冲蛮撞技能速度
			}
			else  //BOSS正常移动
			{
				bossx = (rand() % 3) - 1;
				bossy = (rand() % 3) - 1;
			}

            if (enemy[0]->verticalTop + bossy < 0 || enemy[0]->horizonTop+bossx < 0 || //检测BOSS是否会飞出界外
				enemy[0]->horizonTop+bossx > WIDTH || enemy[0]->verticalTop+bossy > HEIGHT) //若是，则归位重新移动
				goto BOSSSHIFT;
			enemy[0]->verticalTop += bossy; //不然就这样移动吧
			enemy[0]->horizonTop += bossx;
			;

			SelectObject(bufDc, mass);
			TransparentBlt(mDc, enemy[0]->horizonTop - BOSSWIDTH, enemy[0]->verticalTop - BOSSHEIGHT,
				BOSSWIDTH * 2, BOSSHEIGHT * 2, bufDc, 0, 0, BOSSWIDTH * 2, BOSSHEIGHT * 2,
				RGB(255, 255, 255));

		}
		else  //BOSS终极技能的处理
		{
			if (obstacle[97]->horizon == 0) //这里初始化神出鬼没技能的水平速度和垂直速度
			{
				falx = x = enemy[0]->horizonTop; //BOSS假身的位置得到赋值
				faly = y = enemy[0]->verticalTop; //以上两行用于将BOSS的水平垂直值赋给我们的全局变量
				obstacle[96]->horizon = rand() % BOSSSPEED;
				obstacle[96]->vertical = BOSSSPEED - obstacle[96]->horizon;
				if (rand() % 2 == 0)obstacle[96]->horizon = -obstacle[96]->horizon;
				if (rand() % 2 == 0) obstacle[96]->vertical = -obstacle[96]->vertical;
				xs = double(obstacle[96]->horizon) / 100.00;
				ys = double(obstacle[96]->vertical) / 100.00;
   				obstacle[97]->horizon = 4; //这个代表BOSS神出鬼没的最多碰壁次数（3次）
				obstacle[97]->vertical = SSS;
			}
			else if (obstacle[97]->horizon == 1)
			{
				obstacle[97]->horizon = 0;
				enemy[0]->direction = 0;
				xs = 0.0;ys = 0.0;
			}
			x += xs; //更新（移动）水平位置
			y += ys; //同上，垂直位置

			if (x > WIDTH || x < 0)//BOSS在神出鬼没碰壁时的处理
			{
				xs = -xs;
				x += xs;
				obstacle[97]->horizon--;
			}
			if (y > HEIGHT || y < 0)//同上
			{
				ys = -ys;
				y += ys;
				obstacle[97]->horizon--;
			}

			enemy[0]->horizonTop = x; //更新BOSS的水平位置
			enemy[0]->verticalTop = y; //更新BOSS的垂直位置
			
			//以下这两句代码用于测试boss的终极技能（不让它真隐形）运动轨道是否靠谱，好了就删掉
			SelectObject(bufDc, mass);
			TransparentBlt(mDc, enemy[0]->horizonTop - BOSSWIDTH, enemy[0]->verticalTop - BOSSHEIGHT,
				BOSSWIDTH * 2, BOSSHEIGHT * 2, bufDc, 0, 0, BOSSWIDTH * 2, BOSSHEIGHT * 2,
				RGB(255, 255, 255));

			//以下两句代码用于给BOSS的假身贴图
			SelectObject(bufDc, mass);
			TransparentBlt(mDc, falx - BOSSWIDTH, faly - BOSSHEIGHT,
				BOSSWIDTH * 2, BOSSHEIGHT * 2, bufDc, 0, 0, BOSSWIDTH * 2, BOSSHEIGHT * 2,
				RGB(255, 255, 255));

			xs *= double(obstacle[97]->vertical)/SSS;
			ys *= double(obstacle[97]->vertical)/SSS;
  			obstacle[97]->vertical++;
			enemy[0]->speed = 0;
		}
		//到这里BOSS所有的处理完毕

		SelectObject(bufDc, enemyDirection0[2]);
		TransparentBlt(mDc, sparkX-10, sparkY-10, 20, 20,
			bufDc, 0, 0, LENGTH, LENGTH, RGB(0, 0, 0));
		BitBlt(hDc, 0, 0, WIDTH, HEIGHT+20, mDc, 0, 0, SRCCOPY);

		if (my->fire == true) //检测玩家是否开火
		{
			int sx, ex, sy, ey; //这几个代表激光的水平起始位置和垂直结束位置等等
			sx = ex = sy = ey = 0;
			switch (my->direction)
			{
			case 0:
				sx = my->horizonTop;
				sy = my->verticalTop - 25;
				ex = my->horizonTop;
				if (enemy[0]->verticalTop < my->verticalTop &&
					enemy[0]->horizonTop - BOSSWIDTH<my->horizonTop &&
					enemy[0]->horizonTop + BOSSWIDTH>my->horizonTop) //激光击中BOSS
				{
					sparkX = my->horizonTop;
					sparkY = ey = enemy[0]->verticalTop + BOSSHEIGHT;
					//这句代码留着给BOSS减血量
					if (obstacle[97]->horizon == 0)
						enemy[0]->HP -= POWER;
					////这句代码给BOSS减蓝量
					//enemy[0]->speed--;
				}
				else ey = 0;
				for (int b = 1;b < 12;b++) //检测玩家炮弹是否击中BOSS的小卒
				{
					if (enemy[b] != NULL)
					{
						if (enemy[b]->verticalTop < my->verticalTop &&
							enemy[b]->horizonTop - HALF / 2 < sx &&
							enemy[b]->horizonTop + HALF / 2 > sx) //检测小卒是否被激光射中
						{
							enemy[b]->fire = true;
						}
					}
				}
				break;
			case 1:
				sx = my->horizonTop + 25;
				sy = my->verticalTop;
				ey = my->verticalTop;
				if (enemy[0]->horizonTop > my->horizonTop &&
					enemy[0]->verticalTop - BOSSWIDTH < my->verticalTop &&
					enemy[0]->verticalTop + BOSSWIDTH > my->verticalTop)
				{
					sparkY = my->verticalTop;
					sparkX = ex = enemy[0]->horizonTop - BOSSHEIGHT;
					//这句代码留着给BOSS减血量
					if (obstacle[97]->horizon == 0)
						enemy[0]->HP -= POWER;
					////这句代码给BOSS减蓝量
					//enemy[0]->speed--;
				}
				else ex = WIDTH;
				for (int b = 1;b < 12;b++) //检测玩家炮弹是否击中BOSS的小卒
				{
					if (enemy[b] != NULL)
					{
						if (enemy[b]->horizonTop > my->horizonTop &&
							enemy[b]->verticalTop - HALF / 2 < sy &&
							enemy[b]->verticalTop + HALF / 2 > sy) //检测小卒是否被激光射中
						{
							enemy[b]->fire = true;
						}
					}
				}
				break;
			case 2:
				sx = my->horizonTop;
				sy = my->verticalTop + 25;
				ex = my->horizonTop;
				if (enemy[0]->verticalTop > my->verticalTop &&
					enemy[0]->horizonTop - BOSSWIDTH < my->horizonTop &&
					enemy[0]->horizonTop + BOSSWIDTH > my->horizonTop)
				{
					sparkX = my->horizonTop;
					sparkY = ey = enemy[0]->verticalTop - BOSSHEIGHT;
					//这句代码留着给BOSS减血量
					if (obstacle[97]->horizon == 0)
						enemy[0]->HP -= POWER;
					////这句代码给BOSS减蓝量
					//enemy[0]->speed--;
				}
				else ey = HEIGHT;
				for (int b = 1;b < 12;b++) //检测玩家炮弹是否击中BOSS的小卒
				{
					if (enemy[b] != NULL)
					{
						if (enemy[b]->verticalTop > my->verticalTop &&
							enemy[b]->horizonTop - HALF / 2 < sx &&
							enemy[b]->horizonTop + HALF / 2 > sx) //检测小卒是否被激光射中
						{
							enemy[b]->fire = true;
						}
					}
				}
				break;
			case 3:
				sx = my->horizonTop - 25;
				sy = my->verticalTop;
				ey = my->verticalTop;
				if (enemy[0]->horizonTop < my->horizonTop &&
					enemy[0]->verticalTop - BOSSWIDTH < my->verticalTop &&
					enemy[0]->verticalTop + BOSSWIDTH > my->verticalTop)
				{
					sparkY = my->verticalTop;
					sparkX = ex = enemy[0]->horizonTop + BOSSHEIGHT;
					//这句代码留着给BOSS减血量
					if (obstacle[97]->horizon == 0)
						enemy[0]->HP -= POWER;
					////这句代码给BOSS减蓝量
					//enemy[0]->speed--;
				}
				else ex = 0;
				for (int b = 1;b < 12;b++) //检测玩家炮弹是否击中BOSS的小卒
				{
					if (enemy[b] != NULL)
					{
						if (enemy[b]->horizonTop < my->horizonTop &&
							enemy[b]->verticalTop - HALF / 2 < sy &&
							enemy[b]->verticalTop + HALF / 2 > sy) //检测小卒是否被激光射中
						{
							enemy[b]->fire = true;
						}
					}
				}
				break;
			}

			HPEN hpen11 = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			HPEN old11 = (HPEN)SelectObject(hDc, hpen11);
			MoveToEx(hDc, sx, sy, 0);
			LineTo(hDc, ex, ey);
			SelectObject(hDc, old11);
			DeleteObject(hpen11);					   	
		}

		HPEN hpen = CreatePen(PS_SOLID, 10, RGB(255, 10, 0));
		HPEN old = (HPEN)SelectObject(hDc, hpen);
		MoveToEx(hDc, 0, HEIGHT+10, 0);
		LineTo(hDc, enemy[0]->HP, HEIGHT+10); //这几行代码用于画BOSS生命值
		SelectObject(hDc, old);
		DeleteObject(hpen);

		/*SelectObject(hDc, old);*/
		HPEN hpen2 = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
		HPEN old2 = (HPEN)SelectObject(hDc, hpen2);
		MoveToEx(hDc, 0, HEIGHT + 10, 0);
		LineTo(hDc, enemy[0]->speed, HEIGHT + 10); //这几行代码用于画蓝
		SelectObject(hDc, old2);
		DeleteObject(hpen2);
	}
	timePre = GetTickCount(); //获取当前时间
	return;

win:
	;
fail:
	HFONT hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(hDc, hFont);
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));
	TextOut(hDc, 100, 400, text, wcslen(text));
	DeleteObject(hFont);
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
	;
}