#include "carrierVessels.h"
carrierVessel::carrierVessel(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                 QPoint location,int skillcd,int maxskill,int avi)
    :backWarShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location,
                 skillcd,maxskill) ,avi(avi)
{
}
bool carrierVessel::shoot()
    {

    }

void carrierVessel::move()
    {

    }

int carrierVessel::getMax()
    {
        return maxskill;
    }

int carrierVessel::hurt()
    {
        return (avi/100.0+1)*300;
    }

int carrierVessel::getCurrent()
    {
       return number_skill;
    }
