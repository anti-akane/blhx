/* * * * * * * * * ** * * * * * * * * *
 * 战列炮弹类
 * 继承自cannonBall类（炮弹类）
 * 相较于基类，增加了预定位置，只在到达预定位置后爆炸
 * * * * * * * * * * * * * * * * * * * */
#ifndef BATTLECANNON_H
#define BATTLECANNON_H
#include"cannonBall.h"
class battleCannon:public cannonBall
{
public:
    //初始化函数，参数列表从左到右为位置，伤害，炮弹速度，角度，来自父舰艇（被哪艘舰艇发射），立绘，目标，大小
     battleCannon(int x = 0, int y = 0,int hurt = 0,int speed=0,double angle = 0,
                  warShip *parent=nullptr,QString pixmap=":/res/connanball.png",QPoint target=QPoint(0,0),int size=120);
     //实现移动逻辑的函数，若到达目的地则不移动
     virtual void move() override;
     //判断是否到达目的地
     bool ifBomb();
private:
     QPoint target;
};

#endif // BATTLECANNON_H
