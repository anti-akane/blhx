#include"battlecannon.h"
#include"math.h"
battleCannon::battleCannon(int x,int y,int hurt,int speed,double angle,warShip *parent,QString pixmap,QPoint target,int size):
    cannonBall( x,y,hurt,speed,angle ,parent,pixmap,size),target(target)
{
this->getRect().setWidth(60);
    this->getRect().setWidth(60);
}

void battleCannon::move()
{
    if(check())
    {
        cannonBall::move();
    }
}

bool battleCannon::check()
{
    double len=sqrt((getX()-target.x())*(getX()-target.x())+(getY()-target.y())*(getY()-target.y()));
    if(len<=0.6*getSpeed())
        return 0;
    else
        return 1;
}
