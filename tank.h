#pragma once
#pragma once
#define LENGTH 50
class Tank {
public:
	Tank(int vertical, int horizon, int hp, int dircetion, int speed, bool fire);
	~Tank();

	int Hurt(int, int, int);
	bool BeCollide(int vertical, int horizon);


public:
	int  HP; //这个表示坦克的生命值
	int verticalTop, horizonTop; //第一个是坦克的垂直量，第二个是坦克的水平量，两者合起来表示坦克的位置
	int direction, speed; //第一个是坦克当前的面朝哪里，第二个表示坦克行走的速度
	bool fire; //开火权限
};

class Bullet
{
public:
	Bullet(int, int, int, int, int);
public:
	int speed, direction; //第一个表示炮弹的速度，第二个是炮弹的射向
	int verticalTop, horizonTop; //第一个表示炮弹的垂直量（Y轴），第二个表示炮弹的水平量（X轴）
	int power; //这个表示炮弹的威力
};

class Obstacle
{
public:
	Obstacle(int ver, int hori, int hp);
	bool Hurt(int, int);
	bool BeCollide(int vertical, int horizon);
public:
	int vertical, horizon; //第一个表示障碍物的垂直量，第二个是障碍物的水平量
	int HP; //障碍物的生命值
};