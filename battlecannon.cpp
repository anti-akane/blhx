#include"battlecannon.h"
#include"math.h"
battleCannon::battleCannon(int x,int y,int hurt,int speed,double angle,warShip *parent,QString pixmap,QPoint target,int size):
    cannonBall( x,y,hurt,speed,angle ,parent,pixmap,size),target(target)
{
    //更换碰撞箱
this->getRect().setWidth(size);
    this->getRect().setWidth(size);
}

void battleCannon::move()
{
    //在未到达目的地的时候正常移动,到达后不移动
    if(!ifBomb())
    {
        cannonBall::move();
    }
}

bool battleCannon::ifBomb()
{
    //计算与目的地距离
    double len=sqrt((getX()-target.x())*(getX()-target.x())+(getY()-target.y())*(getY()-target.y()));
    //若距离近则爆炸
    if(len<=0.6*getSpeed()||getX()>=target.x())
        return 1;
    else
        return 0;
}
