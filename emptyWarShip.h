#ifndef EMPTYWARSHIP_H
#define EMPTYWARSHIP_H
#include<QPoint>
#include<QPixmap>
class emptyWarShip{
public:
    emptyWarShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location);

    void move();//更新自身位置

    bool shoot();//判断是否需要开炮

    bool checkTorp();

    QPoint &getlocation();

    QPixmap getTachie();

    double getHpRate();

    int power_hurt();

    int torp_hurt();

    int getwidth();

    int getheight();

    void declineHP(int hurt);

    QRect getRect();

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
    QPixmap Tachie;//角色立绘
    QPoint location;
    QRect Rect;
    int width;
    int height;
};

#endif // EMPTYWARSHIP_H
