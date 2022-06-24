#include"battleShip.h"
battleShip:: battleShip(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                      QPoint location,int skillcd,int maxskill):backWarShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location,
    skillcd,maxskill)
{
this->Tachie=this->Tachie.scaled(85,80);
}

void battleShip::move()
{

}

int battleShip::getMax(){
    return  maxskill;
}

int battleShip::getCurrent()
{
    return number_skill;
}

int battleShip::power_hurt()
{
    //返回炮击伤害
    return (1+power/100.0)*800;
}
