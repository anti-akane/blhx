#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include"backWarShip.h"
class battleShip:public backWarShip
{
public:
    battleShip(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                 QPoint location,int skillcd,int maxskill);
    bool shoot();

    void move();

    int getMax();

    int getCurrent();
     int power_hurt() override;


};

#endif // BATTLESHIP_H
