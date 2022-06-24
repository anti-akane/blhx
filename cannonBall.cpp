#include"cannonBall.h"
#include"math.h"
#include"qdebug.h"
const double pi=acos(-1.0);
cannonBall::cannonBall(int x,int y,int hurt,int speed,double angle,warShip *parent,QString pixmap,int Size)
    :x(x),y(y),hurt(hurt),angle(angle),speed(speed),parent(parent),Size(Size){
    //旋转炮弹立绘
    QMatrix matrix;
    matrix.rotate((angle * 2 * 90)/ pi);
    cannonBallPixmap = new QPixmap(QPixmap(pixmap).scaled(Size,Size,Qt::KeepAspectRatio));
    *cannonBallPixmap = cannonBallPixmap->transformed(matrix,Qt::SmoothTransformation);
    //计算立绘宽高度
    height = cannonBallPixmap->height();
    width = cannonBallPixmap->width();
    //设置炮弹碰撞箱
    connonRect.setWidth(Size);
    connonRect.setHeight(Size);
    //根据角度调整炮弹碰撞箱位置
    if(angle>0)
   connonRect.moveTo(x-height*sin(angle)/2.0,y+height*cos(angle)/2.0);
    else
  connonRect.moveTo(x+height*sin(angle)/2.0,y-height*cos(angle)/2.0);
}

void cannonBall::move() {
    //沿角度按固定速度与移动
    x += (speed * cos(angle));
    y += (speed * sin(angle));
    //随舰艇移动改变碰撞箱位置
    if(angle>0)
   connonRect.moveTo(x+height*sin(angle)/2.0,y-height*cos(angle)/2.0);
    else
  connonRect.moveTo(x+height*sin(angle)/2.0,y-height*cos(angle)/2.0);
}

bool cannonBall::check() {
    //判断是否飞出地图外
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

warShip *cannonBall::getparent()
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

int cannonBall::getSpeed(){
    return speed;
}

cannonBall::~cannonBall()
{
    delete cannonBallPixmap;
}

void cannonBall::setPix(QPixmap *target)
{
    //重新设置图像
    *target=target->scaled(Size,Size,Qt::KeepAspectRatio);
 *cannonBallPixmap=*target;
}

int cannonBall::getSize()
{
    return this->Size;
}
