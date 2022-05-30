#ifndef WARSHIP_H
#define WARSHIP_H
#include<QPixmap>
#include<QPoint>
#include"cannonBall.h"
class frontWarShip {
public:
    frontWarShip(int hp, int power, int torp, int speed, int shootcd, int torpcd, int tornumber, QPixmap Tachie,
                 QPoint location, QPoint *target);

    void move();//更新自身位置

    bool shoot();//判断是否需要开炮

    bool checkTorp();

    QPoint &getlocation();

    QPixmap getTachie();

    int getTorpNumber();

    int getCurrentTorpNumber();

private:
    int HP;//生命值上限
    int currentHP;//现在的生命值
    int power;//炮击
    int torp;//雷击
    int speed;//航速
    int shootcd;//射击cd
    int torpcd;//雷击cd
    int shootclock;//控制射击间隔
    int torpclock;//控制鱼雷冷却
    int torp_number;//携带鱼雷数量
    int current_torp_number;//角色现在的鱼雷数量
    QPixmap Tachie;//角色立绘
    QPoint location;
    QPoint *target;
    QRect Rect;

};

#endif // WARSHIP_H
