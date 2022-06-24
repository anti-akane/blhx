/* * * * * * * * * ** * * * * * * * * *
 * 炮弹类（非抽象基类）
 * * * * * * * * * * * * * * * * * * * */
#ifndef CANNONBALL_H
#define CANNONBALL_H
#include<QRect>
#include<QWidget>
#include<QPixmap>
#include<QMatrix>
#include<QString>
#include"warShip.h"
class cannonBall {
public:
    //初始化函数，参数列表从左到右为位置，伤害，炮弹速度，角度，来自父舰艇（被哪艘舰艇发射），立绘，目标，大小
    cannonBall(int x = 0, int y = 0,int hurt = 0,int speed=0, double angle = 0, warShip *parent=nullptr,QString pixmap=":/res/connanball.png",int Size=60);
    //实现移动逻辑的函数，为朝着某一方向定速移动
    virtual void move();
    //判断是否触碰边界
    bool check();
    //返回位置横坐标
    int getX();
    //返回位置纵坐标
    int getY();
    //返回立绘
    QPixmap *getPixmap();
    //返回父舰艇
    warShip* getparent();
    //返回角度
    double getAngle();
    //返回炮弹高度
    int getH();
    //返回炮弹宽度
    int getW();
    //返回炮弹伤害
    int getHurt();
    //返回炮弹碰撞箱
    QRect getRect();
    //返回炮弹速度
    int getSpeed();
    //析构函数
    virtual ~cannonBall();
    //重新设置炮弹立绘
    void setPix(QPixmap*target);
    //获取炮弹大小
    int getSize();

private:
    int x;
    int y;
    int hurt;
    int height;
    int width;
    QRect connonRect;
    double angle;
    QPixmap *cannonBallPixmap;
    warShip *parent;
    bool isempty;
    int Size;
        int speed;
};

#endif // CANNONBALL_H
