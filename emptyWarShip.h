#ifndef EMPTYWARSHIP_H
#define EMPTYWARSHIP_H
#include<QPoint>
#include<QPixmap>
#include"warShip.h"
class emptyWarShip:public warShip{
public:
    emptyWarShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location);

    QRect &getRect();

    virtual void move()=0;

    virtual bool shoot();

    virtual ~emptyWarShip();

    int getHP();

    void setState(int state);

    int getState();

private:
    QRect Rect;
    int state;
};

#endif // EMPTYWARSHIP_H
