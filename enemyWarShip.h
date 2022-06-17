#ifndef ENEMYWARSHIP_H
#define ENEMYWARSHIP_H
#include<QPoint>
#include<QPixmap>
#include"warShip.h"
class enemyWarShip:public warShip{
public:
    enemyWarShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location);

    QRect &getRect();

    virtual void move()=0;

    virtual bool shoot();

    virtual ~enemyWarShip();

    int getHP();

    void setState(int state);

    int getState();

private:
    QRect Rect;
    int state;
};

#endif // ENEMYWARSHIP_H
