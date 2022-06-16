#ifndef BATTLECANNON_H
#define BATTLECANNON_H
#include"cannonBall.h"
class battleCannon:public cannonBall
{
public:
     battleCannon(int x = 0, int y = 0,int hurt = 0,int speed=0,double angle = 0,warShip *parent=nullptr,QString pixmap=":/res/connanball.png",QPoint target=QPoint(0,0),int size=120);
     virtual void move() override;
     bool check();
private:
     QPoint target;
};

#endif // BATTLECANNON_H
