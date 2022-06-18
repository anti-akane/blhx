#include"backWarShip.h"
backWarShip:: backWarShip(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                      QPoint location,int skillcd,int maxskill):warShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location),
    skillcd(skillcd),maxskill(maxskill)
{
    skill_clock=0;
    number_skill=0;
}
bool backWarShip::check()
{
    if (number_skill < maxskill)
       skill_clock++;
    if (skill_clock > skillcd) {
        skill_clock = 0;
        number_skill++;
        return 1;
    }
    return 0;
}

int backWarShip::getMaxSkill()
{
    return maxskill;
}

int backWarShip::getCurrentSkill()
{
    return number_skill;
}

void backWarShip::decreaseSkill()
{
    number_skill--;
}

void backWarShip::reStart()
{
    skill_clock=0;
    number_skill=0;
}

backWarShip::~backWarShip()
{

}
