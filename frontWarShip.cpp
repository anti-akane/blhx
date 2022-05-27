#include"frontWarShip.h"
#include"math.h"
QPixmap frontWarShip::getTachie()
{
    return Tachie;
}
QPoint& frontWarShip::getlocation()
{
    return location;
}
frontWarShip::frontWarShip(int hp,int power,int torp,int speed,int shootcd,
                           int torpcd,int tornumber,QPixmap Tachie,
                           QPoint location,QPoint*target)
    :HP(hp),power(power),torp(torp),speed(speed),shootcd(shootcd),torpcd(torpcd),torp_number(tornumber),Tachie(Tachie),location(location),target(target)
{
    Rect.setWidth(Tachie.width());
    Rect.setHeight(Tachie.height());
    Rect.moveTo(location);
    shootclock=0;
}
bool frontWarShip::shoot()
{
    shootclock++;
    if(shootclock>shootcd)
    {
        shootclock=0;
        return 1;
    }
    return 0;
}
void frontWarShip::move()
{
    int l_x=location.x(),l_y=location.y();
    int t_x=target->x(),t_y=target->y();
    double len=sqrt((l_x-t_x)*(l_x-t_x)+(l_y-t_y)*(l_y-t_y));
    if(len<=speed)
        return;
    location.setX(l_x+speed*(t_x-l_x)/len);
    location.setY(l_y+speed*(t_y-l_y)/len);
}
