#ifndef STANDARDEMPTY_H
#define STANDARDEMPTY_H
#include"emptyWarShip.h"
class standardEmpty:public emptyWarShip {
public:
    standardEmpty(int HP, int power, int torp, int speed, int movecd, int shootcd, int torpcd, QPixmap Tachie,
                  QPoint location);

    virtual void move();

private:
    int moveclock;
    int movecd;

};

#endif // STANDARDEMPTY_H
