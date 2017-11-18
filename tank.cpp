#include "tank.h"

Tank::Tank(int vertical,int horizon,int dir,int sp,int hp,bool f)
{
	HP = hp;
	verticalTop = vertical;
	horizonTop = horizon;
	direction = dir;
	speed = sp;
	fire = f;
}
Tank::~Tank()
{

}

int Tank::Hurt(int verT, int horiT, int power)  //检测坦克是否受伤，其中传递过来的参数应该是炮弹的位置（由前两个参数表示），第三个参数是炮弹的威力
{
	if (horizonTop < horiT 
		&& verticalTop < verT 
		&& horizonTop + LENGTH > horiT
		&& verticalTop + LENGTH > verT)
		return power; //如果受伤了，就返回受伤值
	else return 0;
}

bool Tank::BeCollide(int vertical, int horizon) //检测坦克是否撞到别的坦克，两个参数表示另外坦克的位置
{
	if (verticalTop+1<vertical+LENGTH && horizonTop+1<horizon+LENGTH && verticalTop + LENGTH>vertical+1 && horizonTop + LENGTH>horizon+1)
		return true;
	else return false;
}

Bullet::Bullet(int ver,int hor,int sp, int dir, int pow)
{
	verticalTop = ver;
	horizonTop = hor;
	speed = sp;
	direction = dir;
	power = pow;
}

Obstacle::Obstacle(int ver, int hori, int hp):vertical(ver),horizon(hori),HP(hp)
{}
bool Obstacle::Hurt(int ver, int hori) //检测障碍物是否受伤
{
	if (horizon <= hori
		&& vertical <= ver
		&& horizon + LENGTH >= hori
		&& vertical + LENGTH >= ver)
		return true;
	else return false;
}