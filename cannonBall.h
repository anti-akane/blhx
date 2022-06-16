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
    cannonBall(int x = 0, int y = 0,int hurt = 0,int speed=0, double angle = 0, warShip *parent=nullptr,QString pixmap=":/res/connanball.png",int Size=60);

    virtual void move();

    void boom();

    bool check();

    int getX();

    int getY();

    QPixmap *getPixmap();

    warShip* getparent();

    double getAngle();

    int getH();

    int getW();

    int getHurt();

    QRect getRect();

    int getSpeed();

    virtual ~cannonBall();

    void setPix(QPixmap*target);

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
    warShip*parent;
    bool isempty;
    int speed;
    int Size;
};

#endif // CANNONBALL_H
