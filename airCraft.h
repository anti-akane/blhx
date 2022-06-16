#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include"QPixmap"
class airCraft
{
public:
    airCraft(int x,int y,int hurt,int isBombing,QPixmap pix=QPixmap("://res/airCraft.png"));
    bool check();
    int getX();
    int getY();
    int getHurt();
    void move();
    int isbombing();
    QPixmap getPix();
private:
    int x;
    int y;
    int hurt;
    int isBombing;
    QPixmap pix;
};

#endif // AIRCRAFT_H
