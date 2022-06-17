#include"frontWarShip.h"
#include"math.h"
frontWarShip::frontWarShip(int hp,int power,int torp,int speed,int shootcd,
                           int torpcd,int tornumber,QPixmap tachie,
                           QPoint location,QPoint*target,int barragecd)
    :warShip(hp,power,torp,speed,shootcd,torpcd,tachie,location),torp_number(tornumber),target(target),barragecd(barragecd) {
    currentHP = HP;
    (this->Tachie) = tachie.scaled(120, 120, Qt::KeepAspectRatio);
    Rect.setWidth(Tachie.width() / 4);
    Rect.setHeight(Tachie.height() / 4);
    Rect.moveTo(location.x() + Tachie.width() / 4, location.y() + Tachie.height() / 2);
    shootclock = 0;
    torpclock = 0;
    barrageclock=0;
    current_torp_number = 0;
}

bool frontWarShip::shoot() {
    shootclock++;
    if (shootclock % shootcd == 0) {
        return 1;
    } else if (shootclock % (shootcd + 3) == 0) {
        return 1;
    } else if (shootclock % (shootcd + 6) == 0) {
        shootclock = 0;
        return 1;
    }
    return 0;
}

void frontWarShip::move() {
    int l_x = location.x(), l_y = location.y();
    int t_x = target->x(), t_y = target->y();
    double len = sqrt((l_x - t_x) * (l_x - t_x) + (l_y - t_y) * (l_y - t_y));
    if (len <= 3 * speed) {
        return;
    }
    location.setX(l_x + speed * (t_x - l_x) / len);
    location.setY(l_y + speed * (t_y - l_y) / len);
    Rect.moveTo(location.x() + Tachie.width() / 4, location.y() + Tachie.height() / 2);
}

bool frontWarShip::checkTorp() {
    if (current_torp_number < torp_number)
        torpclock++;
    if (torpclock > torpcd) {
        torpclock = 0;
        current_torp_number++;
        return 1;
    }
    return 0;
}

int frontWarShip::getSpeed() {
    return speed;
}

int frontWarShip::getTorpNumber() {
    return torp_number;
}

int frontWarShip::getCurrentTorpNumber() {
    return current_torp_number;
}

void frontWarShip::declineTorpNumber() {
    current_torp_number--;
}



QRect & frontWarShip::getRect(){
    return Rect;
}

void frontWarShip::setTarget(QPoint *goal)
{
    target=goal;
}

bool frontWarShip::checkBarrage()
{if(!barragecd)
        return 0;
    barrageclock++;
    if(barrageclock>=barragecd)
    {
        barrageclock=0;
        return 1;
    }
    return 0;
}

void frontWarShip::setBarrage(QVector<cannonBall *> Barrage)
{
    for(auto v:Barrage)
    {
        barrage.push_back(new cannonBall(*v));
    }
}

QVector<cannonBall*>frontWarShip::getBarrage()
{
    return barrage;
}

void frontWarShip::reStart()
{
    shootclock = 0;
    torpclock = 0;
    barrageclock=0;
    current_torp_number = 0;
}


