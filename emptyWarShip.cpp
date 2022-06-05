#include"emptyWarShip.h"
#include"math.h"
emptyWarShip::emptyWarShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location)
    :HP(HP),power(power),torp(torp),speed(speed),shootcd(shootcd),torpcd(torpcd),Tachie(Tachie),location(location)
{
Rect.setWidth(Tachie.width());
Rect.setHeight(Tachie.height());
Rect.moveTo(location);
}

QPixmap emptyWarShip::getTachie() {
    return Tachie;
}

QPoint& emptyWarShip::getlocation() {
    return location;
}
bool emptyWarShip::shoot() {
    shootclock++;
    if (shootclock > shootcd) {
        shootclock = 0;
        return 1;
    }
    return 0;
}

void emptyWarShip::move() {

}

bool emptyWarShip::checkTorp()
{

    torpclock++;
    if(torpclock>torpcd)
    {
        torpclock=0;
        return 1;
    }
    return 0;
}

double emptyWarShip::getHpRate()
{
    return currentHP*1.0/HP;
}

int emptyWarShip::power_hurt()
{
    return (1+power*1.0/100)*100;
}

int emptyWarShip::torp_hurt()
{
    return (1+power*1.0/100)*200;
}
