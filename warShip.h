/* * * * * * * * * ** * * * * * * * * *
 * 战舰类（纯虚类）
 * 属性包含血量，炮击值，鱼雷值，航速，射击cd，鱼雷cd，立绘，位置
 * * * * * * * * * * * * * * * * * * * */
#ifndef WARSHIP_H
#define WARSHIP_H
#include<QPoint>
#include<QPixmap>
class warShip{
public:
    //构造函数
    warShip(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location);
    //移动函数（纯虚函数）
    virtual void move()=0;
    //返回位置
    QPoint &getlocation();
    //返回立绘
    QPixmap getTachie();
    //返回血量比例
    double getHpRate();
    //计算炮击伤害
    virtual int power_hurt();
    //计算鱼雷伤害
    int torp_hurt();
    //返回舰艇立绘宽度
    int getwidth();
    //返回舰艇立绘高度
    int getheight();
    //封装的舰艇受伤事件函数
    void declineHP(int hurt);
    //封装的舰艇恢复血量事件函数
    void addHP(int recover);

    virtual~warShip();

    protected:
    int HP;//生命值上限
    int currentHP;//现在的生命值
    int power;//炮击
    int torp;//雷击
    int speed;//航速
    int shootcd;//射击cd
    int torpcd;//雷击cd
    int shootclock;//控制射击间隔
    int torpclock;//控制鱼雷冷却
    QPixmap Tachie;//角色立绘
    QPoint location;//舰艇为位置
    int width;
    int height;
};
#endif // WARSHIP_H
