#include"warShip.h"
#include"math.h"
warShip::warShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location)
    :HP(HP),power(power),torp(torp),speed(speed),shootcd(shootcd),torpcd(torpcd),Tachie(Tachie),location(location) {
    currentHP = HP;
    height = Tachie.height();
    width = Tachie.width();
    shootclock = 0;
}

QPixmap warShip::getTachie() {
    return Tachie;
}

QPoint& warShip::getlocation() {
    return location;
}

double warShip::getHpRate()
{
    return currentHP*1.0/HP;
}

int warShip::power_hurt()
{
    return (1+power*1.0/100)*50;
}

int warShip::torp_hurt()
{
    return (1+power*1.0/100)*500;
}

int warShip::getwidth()
{
    return width;
}

int warShip::getheight()
{
    return height;
}

void warShip::declineHP(int hurt)
{
    if(currentHP>hurt)
    currentHP-=hurt;
    else
    currentHP=0;
}
