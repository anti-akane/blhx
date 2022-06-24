#include"airCraft.h"
airCraft::airCraft(int x,int y,int hurt,int isBombing,QPixmap pix):x(x),y(y),hurt(hurt),isBombing(isBombing)
{
    //固定立绘大小
 this->pix=pix.scaled(90,90,Qt::KeepAspectRatio);
}

bool airCraft::check()
{
    //判断是否发动技能

    //轰炸机在横坐标大于800时发动投掷炸弹
    if(isBombing)
    {
        if(x>=800)
            return 1;
        else
            return 0;
    }
    //鱼雷机在横坐标大于300时发动投掷鱼雷
    else
    {
        if(x>=300)
            return 1;
        else
            return 0;
    }
}

int airCraft::getX()
{
    return x;
}

int airCraft::getY()
{
    return y;
}

int airCraft::getHurt()
{
    return hurt;
}

void airCraft::move()
{
    x+=20;
}

int airCraft::isbombing()
{
    return isBombing;
}

QPixmap airCraft::getPix()
{
    return pix;
}
