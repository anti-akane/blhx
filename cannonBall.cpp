#include"cannonBall.h"
#include"math.h"
const double pi=acos(-1.0);
cannonBall::cannonBall(int x,int y,int hurt,double angle,frontWarShip *parent,QString pixmap):x(x),y(y),hurt(hurt),angle(angle) ,parent(parent){
    QMatrix matrix;
    matrix.rotate((angle * 2 * 90)/ pi);
    cannonBallPixmap = new QPixmap(pixmap);
    if(pixmap==":/res/torp.png")
        *this->cannonBallPixmap=(this->cannonBallPixmap)->scaled(35,35,Qt::KeepAspectRatio);
    else
     *this->cannonBallPixmap=(this->cannonBallPixmap)->scaled(70,70,Qt::KeepAspectRatio);
    height = cannonBallPixmap->height();
    width = cannonBallPixmap->width();
    *cannonBallPixmap = cannonBallPixmap->transformed(matrix,Qt::SmoothTransformation);
    connonRect.setWidth(width);
    connonRect.setHeight(width);
    connonRect.moveTo(x + width * cos(angle) / 2, y - width * sin(angle) / 2);
}

void cannonBall::move() {
    x += (15 * cos(angle));
    y += (15 * sin(angle));
    connonRect.moveTo(x + width * cos(angle) / 2, y - width * sin(angle) / 2);
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
