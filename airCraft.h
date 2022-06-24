/* * * * * * * * * ** * * * * * * * * *
 * 舰载机类
 * 属性包括位置，伤害，是否为轰炸机和图片
 * 分为轰炸机和舰载机两种
 * 使用if else语句实现多态性
 * * * * * * * * * * * * * * * * * * * */
#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include"QPixmap"
class airCraft
{
public:
    //初始化（构造）函数，包括位置，伤害，类型（为1表示为轰炸机否则为鱼雷机），立绘
    airCraft(int x,int y,int hurt,int isBombing,QPixmap pix=QPixmap("://res/airCraft.png"));
    //判断是否发动舰载机的技能的函数
    bool check();
    //返回舰载机位置横坐标
    int getX();
    //返回舰载机位置纵坐标
    int getY();
    //返回舰载机伤害
    int getHurt();
    //控制舰载机移动的函数
    void move();
    //返回舰载机属性的函数
    int isbombing();
    //返回舰载机立绘的函数
    QPixmap getPix();
private:
    int x;
    int y;
    int hurt;
    int isBombing;
    QPixmap pix;
};

#endif // AIRCRAFT_H
