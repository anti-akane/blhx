#ifndef CARRIERVESSELS_H
#define CARRIERVESSELS_H
#include"backWarShip.h"
class carrierVessel:public backWarShip
{
public:
    carrierVessel(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                 QPoint location,int skillcd,int maxskill,int avi);
    bool shoot();

    void move();

    int getMax();

    int hurt();

    int getCurrent();
private:
    int avi;
};

#endif // CARRIERVESSELS_H
