#ifndef HUMANOIDENEMY_H
#define HUMANOIDENEMY_H
#include"enemyWarShip.h"
class humanoidEnemy:public enemyWarShip {
public:
    humanoidEnemy(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie, QPoint location);

    virtual void move() override;

    bool shoot() override;

    bool check_torp();

    QPoint* getTarget();

    void setTarget(QPoint *goal);

    ~humanoidEnemy();

private:
    QPoint *target;
    int moveclock;
};

#endif // HUMANOIDENEMY_H
