#ifndef FRONTWARSHIP_H
#define FRONTWARSHIP_H
#include<QPixmap>
#include<QPoint>
#include"warShip.h"
#include"cannonBall.h"
class frontWarShip :public warShip {
public:
    frontWarShip(int hp, int power, int torp, int speed, int shootcd, int torpcd, int tornumber, QPixmap tachie,
                 QPoint location, QPoint *target,int barragecd=0);

    void move() override;//更新自身位置

    bool shoot();

    bool checkTorp();

    int getTorpNumber();

    int getCurrentTorpNumber();

    void declineTorpNumber();

    int getSpeed();

    bool checkBarrage();

    QRect &getRect();

    void setTarget(QPoint *goal);

    void setBarrage(QVector<cannonBall*>Barrage);

    QVector<cannonBall*>getBarrage();


private:
    int torp_number;//携带鱼雷数量
    int current_torp_number;//角色现在的鱼雷数量
    QPixmap Tachie;//角色立绘
    QPoint *target;
    QRect Rect;
    int barragecd;
    int barrageclock;
    QVector<cannonBall*>barrage;

};

#endif // FRONTWARSHIP_H
