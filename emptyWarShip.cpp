#include"emptyWarShip.h"
#include"math.h"
emptyWarShip::emptyWarShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location)
    :warShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location)
{
    currentHP=HP;
Rect.setWidth(Tachie.width()/2);
Rect.setHeight(Tachie.height()/2);
height=Tachie.height();
width=Tachie.width();
Rect.moveTo(location.x()+width/4,location.y()+height/2);
shootclock=0;
}

QRect emptyWarShip::getRect()
{
    return Rect;
}

void emptyWarShip::move()
{

}

bool emptyWarShip::shoot()
{
    shootclock++;
    if (shootclock%shootcd==0) {
        return 1;
    }
    else if(shootclock%(shootcd+6)==0)
    {
        shootclock=0;
        return 1;
    }
    return 0;
}
