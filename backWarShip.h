/* * * * * * * * * ** * * * * * * * * *
 * 后排舰艇类（抽象基类）
 * 继承自warShip类（舰艇类）
 * 相较于基类，增加了技能冷却时间和数量
 * * * * * * * * * * * * * * * * * * * */
#ifndef BACKWARSHIP_H
#define BACKWARSHIP_H
#include"warShip.h"
class backWarShip:public warShip
{
public:
    //构造函数，从左到右参数依次为血量，炮击，雷击，航速，射击cd，鱼雷cd，立绘，位置，技能cd，最大技能数
    backWarShip(int HP, int power, int torp, int speed, int shootcd, int torpcd, QPixmap Tachie,
                 QPoint location,int skillcd,int maxskill);
    //获取当前技能数量，便于死亡后技能按钮正确显示
    int getCurrentSkill();
    //减少当前技能数量的函数，一般在发动技能时使用
    void decreaseSkill();
    //获取最大技能数
    int getMaxSkill();
    //用于判断技能是否冷却完
    bool check();
    //用于每次开始战斗时重置技能
    void reStart();
    //析构函数
   ~backWarShip();
    protected:
    int skillcd;
    int maxskill;
    int number_skill;
    int skill_clock;
};

#endif // BACKWARSHIP_H
