#include"cannonBall.h"
#include"math.h"
const double pi=acos(-1.0);
cannonBall::cannonBall(int x,int y,int hurt,double angle,frontWarShip *parent,QString pixmap):x(x),y(y),hurt(hurt),angle(angle) ,parent(parent){
    QMatrix matrix;
    matrix.rotate((angle * 2 * 90)/ pi);
    cannonBallPixmap = new QPixmap(pixmap);
    speed=50;
    if(pixmap==":/res/torp.png")
    {
        *this->cannonBallPixmap=(this->cannonBallPixmap)->scaled(35,35,Qt::KeepAspectRatio);
        speed=10;
    }
    else
     *this->cannonBallPixmap=(this->cannonBallPixmap)->scaled(70,70,Qt::KeepAspectRatio);
    height = cannonBallPixmap->height();
    width = cannonBallPixmap->width();
    *cannonBallPixmap = cannonBallPixmap->transformed(matrix,Qt::SmoothTransformation);
    connonRect.setWidth(width);
    connonRect.setHeight(width);
    if(angle>0)
   connonRect.moveTo(x-height*sin(angle)/2.0,y+height*cos(angle)/2.0);
    else
  connonRect.moveTo(x+height*sin(angle)/2.0,y-height*cos(angle)/2.0);
}

void cannonBall::move() {
    x += (speed * cos(angle));
    y += (speed * sin(angle));
    if(angle>0)
   connonRect.moveTo(x+height*sin(angle)/2.0,y-height*cos(angle)/2.0);
    else
  connonRect.moveTo(x+height*sin(angle)/2.0,y-height*cos(angle)/2.0);
}

bool cannonBall::check() {
    if (x > 1200 || x < 0 || y > 675 || y < 0)
        return 0;
    else
        return 1;
}

int cannonBall::getX() {
    return x;
}

int cannonBall::getY() {
    return y;
}

QPixmap* cannonBall::getPixmap() {
    return cannonBallPixmap;
}

frontWarShip *cannonBall::getparent()
{
    return parent;
}

double cannonBall::getAngle()
{
    return angle;
}

int cannonBall::getH()
{
    return height;
}

int cannonBall::getW()
{
    return width;
}

int cannonBall::getHurt()
{
    return hurt;
}

QRect cannonBall::getRect()
{
    return connonRect;
}
