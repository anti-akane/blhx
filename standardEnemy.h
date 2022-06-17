#ifndef STANDARDENEMY_H
#define STANDARDENEMY_H
#include"enemyWarShip.h"
class standardEnemy:public enemyWarShip {
public:
    standardEnemy(int HP, int power, int torp, int speed, int movecd, int shootcd, int torpcd, QPixmap Tachie,
                  QPoint location);

    virtual void move();

private:
    int moveclock;
    int movecd;

};

#endif // STANDARDENEMT_H
