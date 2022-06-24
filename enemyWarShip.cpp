#include"enemyWarShip.h"
#include"math.h"
enemyWarShip::enemyWarShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location)
    :warShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location) {
    //初始化补满血量
    currentHP = HP;
    //调整碰撞箱
    Rect.setWidth(Tachie.width() * 3 / 4);
    Rect.setHeight(Tachie.height() * 2 / 3);
    //根据立绘判断宽高度
    height = Tachie.height();
    width = Tachie.width();
    //绑定碰撞箱
    Rect.moveTo(location.x() + width / 8, location.y() + height / 3);
    //重置射击计时器
    shootclock = 0;
}

QRect &enemyWarShip::getRect()
{
    return Rect;
}

bool enemyWarShip::shoot() {
    //令每次射击其每次发射两轮子弹
    shootclock++;
    if (shootclock % shootcd == 0) {
        return 1;
    } else if (shootclock % (shootcd + 6) == 0) {
        shootclock = 0;
        return 1;
    }
    return 0;
}

int enemyWarShip::getHP()
{
    return currentHP;
}

int enemyWarShip::getState()
{
    return state;
}

void enemyWarShip::setState(int state)
{
    this->state=state;
}
enemyWarShip::~enemyWarShip()
{

}
