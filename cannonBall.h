#ifndef CANNONBALL_H
#define CANNONBALL_H
#include<QRect>
#include<QWidget>
#include<QPixmap>
#include<QMatrix>
class cannonBall{
public:
   cannonBall(int x=0,int y=0,int hurt=0,double angle=0);
   void move();
   void boom();
   bool check();
   int getX();
   int getY();
   QPixmap *getPixmap();
private:
   int x;
   int y;
   int hurt;
   int height;
   int width;
   QRect connonRect;
   double angle;
   QPixmap *cannonBallPixmap;
};

#endif // CANNONBALL_H
