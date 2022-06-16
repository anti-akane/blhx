#ifndef WARSHIP_H
#define WARSHIP_H
#include<QPoint>
#include<QPixmap>
class warShip{
public:
    warShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location);

    virtual void move()=0;

    QPoint &getlocation();

    QPixmap getTachie();

    double getHpRate();

    int power_hurt();

    int torp_hurt();

    int getwidth();

    int getheight();

    void declineHP(int hurt);

    void addHP(int recover);


    protected:
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
    int width;
    int height;
};
#endif // WARSHIP_H
