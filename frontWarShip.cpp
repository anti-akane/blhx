#include"frontWarShip.h"
#include"math.h"
QPixmap  frontWarShip::getTachie() {
    return (Tachie);
}

QPoint& frontWarShip::getlocation() {
    return location;
}
frontWarShip::frontWarShip(int hp,int power,int torp,int speed,int shootcd,
                           int torpcd,int tornumber,QPixmap tachie,
                           QPoint location,QPoint*target)
    :HP(hp),power(power),torp(torp),speed(speed),shootcd(shootcd),
    torpcd(torpcd),torp_number(tornumber),location(location),target(target) {
    currentHP=HP/2;
    (this->Tachie)=tachie.scaled(120,120,Qt::KeepAspectRatio);
    Rect.setWidth(Tachie.width());
    Rect.setHeight(Tachie.height());
    Rect.moveTo(location);
    shootclock = 0;
    torpclock=0;
    current_torp_number=0;
}

bool frontWarShip::shoot() {
    shootclock++;
    if (shootclock%shootcd==0) {
        return 1;
    }
    else if(shootclock%(shootcd+3)==0)
    {
        return 1;
    }
    else if(shootclock%(shootcd+6)==0)
    {
        shootclock=0;
        return 1;
    }
    return 0;
}

void frontWarShip::move() {
    int l_x = location.x(), l_y = location.y();
    int t_x = target->x(), t_y = target->y();
    double len = sqrt((l_x - t_x) * (l_x - t_x) + (l_y - t_y) * (l_y - t_y));
    if (len <= 3*speed)
       {
        return;
        }
    location.setX(l_x + speed * (t_x - l_x) / len);
    location.setY(l_y + speed * (t_y - l_y) / len);
}

bool frontWarShip::checkTorp()
{
    if(current_torp_number<torp_number)
    torpclock++;
    if(torpclock>torpcd)
    {
        torpclock=0;
        current_torp_number++;
        return 1;
    }
    return 0;
}

int frontWarShip::getSpeed()
{
    return speed;
}
int frontWarShip::getTorpNumber()
{
    return torp_number;
}

int frontWarShip::getCurrentTorpNumber()
{
    return current_torp_number;
}

void frontWarShip::declineTorpNumber()
{
current_torp_number--;
}

double frontWarShip::getHpRate()
{
    return currentHP*1.0/HP;
}

int frontWarShip::power_hurt()
{
    return (1+power*1.0/100)*40;
}

int frontWarShip::torp_hurt()
{
    return (1+power*1.0/100)*500;
}
