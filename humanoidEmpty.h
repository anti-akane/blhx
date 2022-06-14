#ifndef HUMANOIDEMPTY_H
#define HUMANOIDEMPTY_H
#include"emptyWarShip.h"
class humanoidEmpty:public emptyWarShip {
public:
    humanoidEmpty(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie, QPoint location);

    virtual void move() override;

    bool shoot() override;

    bool check_torp();

private:
    QPoint *target;
    int moveclock;
};

#endif // HUMANOIDEMPTY_H
