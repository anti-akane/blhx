/* * * * * * * * * ** * * * * * * * * *
 * 敌方舰艇类
 * 继承自warShip类（敌方舰艇类）
 * * * * * * * * * * * * * * * * * * * */
#ifndef ENEMYWARSHIP_H
#define ENEMYWARSHIP_H
#include<QPoint>
#include<QPixmap>
#include"warShip.h"
class enemyWarShip:public warShip{
public:
    //初始化构造函数
    enemyWarShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location);
    //返回碰撞箱
    QRect &getRect();
    //继承的纯虚函数
    virtual void move()=0;
    //控制射击的函数
    virtual bool shoot();
    //析构函数
    virtual ~enemyWarShip();
    //返回当先血量
    int getHP();
    //设置批次（第几波出现）
    void setState(int state);
    //获取批次
    int getState();

    private:
    QRect Rect;
    int state;
};

#endif // ENEMYWARSHIP_H
