/* * * * * * * * * ** * * * * * * * * *
 * 量产敌舰类
 * 继承自enemyWarShip(敌方舰艇类)
 * 定位为威胁小的普通敌人
 * * * * * * * * * * * * * * * * * * * */
#ifndef STANDARDENEMY_H
#define STANDARDENEMY_H
#include"enemyWarShip.h"
class standardEnemy:public enemyWarShip {
public:
    //构造函数
    standardEnemy(int HP, int power, int torp, int speed, int movecd, int shootcd, int torpcd, QPixmap Tachie,
                  QPoint location);
    //移动函数，每隔一段时间间隔往前移动航速代表的距离
    virtual void move();

private:
    int moveclock;//移动计数器
    int movecd;//移动间隔

};

#endif // STANDARDENEMT_H
