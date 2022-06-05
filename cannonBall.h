#ifndef CANNONBALL_H
#define CANNONBALL_H
#include<QRect>
#include<QWidget>
#include<QPixmap>
#include<QMatrix>
#include<QString>
class frontWarShip;
class cannonBall {
public:
    cannonBall(int x = 0, int y = 0,int hurt = 0, double angle = 0,frontWarShip *parent=nullptr,QString pixmap=":/res/connanball.png");

    void move();

    void boom();

    bool check();

    int getX();

    int getY();

    QPixmap *getPixmap();

    frontWarShip* getparent();

private:
    int x;
    int y;
    int hurt;
    int height;
    int width;
    QRect connonRect;
    double angle;
    QPixmap *cannonBallPixmap;
    frontWarShip*parent;
    bool isempty;
};

#endif // CANNONBALL_H
