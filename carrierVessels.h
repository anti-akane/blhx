/* * * * * * * * * ** * * * * * * * * *
 * 航母类
 * 继承自backWarShip类（后排舰艇类）
 * 定位为恢复己方血量，对敌方全体伤害，以及清除对方弹幕
 * * * * * * * * * * * * * * * * * * * */
#ifndef CARRIERVESSELS_H
#define CARRIERVESSELS_H
#include"backWarShip.h"
class carrierVessel:public backWarShip
{
public:
    //初始构造函数，与基类不同的是最后参数为航空值，确定伤害
    carrierVessel(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                 QPoint location,int skillcd,int maxskill,int avi);
    //移动，在本类中无意义
    void move()override;
    //获取最大技能数
    int getMax();
    //伤害
    int hurt();
    //获取当前技能数
    int getCurrent();

private:
    int avi;
};

#endif // CARRIERVESSELS_H
