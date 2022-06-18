#ifndef BACKWARSHIP_H
#define BACKWARSHIP_H
#include"warShip.h"
class backWarShip:public warShip
{
public:
    backWarShip(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                 QPoint location,int skillcd,int maxskill);
    int getCurrentSkill();
    void decreaseSkill();
    int getMaxSkill();
    bool check();
    void reStart();
   ~backWarShip();
    protected:
    int skillcd;
    int maxskill;
    int number_skill;
    int skill_clock;
};

#endif // BACKWARSHIP_H
