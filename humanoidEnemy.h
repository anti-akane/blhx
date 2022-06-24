/* * * * * * * * * ** * * * * * * * * *
 * 人形敌舰类
 * 继承自enemyWarShip类（敌方舰艇类）
 * 战斗力高的敌方舰艇
 * * * * * * * * * * * * * * * * * * * */
#ifndef HUMANOIDENEMY_H
#define HUMANOIDENEMY_H
#include"enemyWarShip.h"
class humanoidEnemy:public enemyWarShip {
public:
    //构造函数
    humanoidEnemy(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie, QPoint location);
    //移动函数，实际上为随机移动
    virtual void move() override;
    //射击函数
    bool shoot() override;
    //鱼雷舰艇函数
    bool check_torp();
    //析构函数
    ~humanoidEnemy();

private:
    QPoint *target;//舰艇移动目标
    int moveclock;//移动间隔
};

#endif // HUMANOIDENEMY_H
