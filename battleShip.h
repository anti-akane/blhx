/* * * * * * * * * ** * * * * * * * * *
 * 战列类
 * 继承自backWarShip类（后排舰艇类）
 * 定位为定点击杀地方某一单位的舰艇
 * * * * * * * * * * * * * * * * * * * */
#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include"backWarShip.h"
class battleShip:public backWarShip
{
public:
    //构造函数，从左到右参数依次为血量，炮击，雷击，航速，射击cd，鱼雷cd，立绘，位置，技能cd，最大技能数
    battleShip(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                 QPoint location,int skillcd,int maxskill);
    //移动（在本类中无意义）
    void move()override;
    //获取最大技能数
    int getMax();
    //获取当前技能数
    int getCurrent();
    //炮击伤害
     int power_hurt() override;


};

#endif // BATTLESHIP_H
