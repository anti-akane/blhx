/* * * * * * * * * ** * *
 * * * * * * *
 * 战斗画面类
 * * * * * * * * * * * * * * * * * * * */
#ifndef FIGHTSCENE_H
#define FIGHTSCENE_H
#include<QWidget>
#include<QIcon>
#include<QtCore>
#include<QObject>
#include<QPixmap>
#include<QPainter>
#include<QRect>
#include<QLabel>
#include<QVector>
#include"skillButton.h"
#include"quitMessageBox.h"
#include"operationButton.h"
#include<QSet>
#include<QBrush>
#include<QCloseEvent>
#include"cannonBall.h"
#include"frontWarShip.h"
#include"enemyWarShip.h"
#include"standardEnemy.h"
#include"humanoidEnemy.h"
#include"battleShip.h"
#include"backWarShip.h"
#include"battlecannon.h"
#include"carrierVessels.h"
#include"airCraft.h"
class fightScene:public QWidget {
    Q_OBJECT
public:
    //构造函数
    fightScene(QWidget *parent,QVector<frontWarShip*>startfront,QVector<backWarShip*>startback,QVector<enemyWarShip*>startEnemy);
    //析构函数
    ~fightScene();

    void playGame();//主体函数，游戏每一帧画面都在这里完成计算，

    void updatetarger(int x, int y);//封装的调整目的坐标函数

    void keyPressEvent(QKeyEvent *event);//处理战斗中的键盘信号

    void keyReleaseEvent(QKeyEvent *event);//处理键盘事件

    void paintEvent(QPaintEvent *);//绘制场景等

    void keyPress();//处理键盘事件，用于实现同时间处理多个键盘事件，实现八方向移动

    void mouseMoveEvent(QMouseEvent *event);//处理鼠标点击时间，主要用于处理点击改变坐标

    void closeEvent(QCloseEvent *event);//处理界面关闭事件

    void shoot();//处理总的射击事件

    void frontshoot(frontWarShip *WarShip);//封装的处理前排舰艇射击函数

    void enemyshoot();//处理敌方舰艇射击的函数

    void autoOperate();//处理自律时逻辑的函数

    double cal_angle(QPoint *begin, QPoint *goal);//计算角度

    void drawfront(QPainter &painter, frontWarShip *WarShip,
                   QBrush *black_brush, QBrush *green_brush);//封装的绘制每个前排舰艇血量和立绘的函数

    void collide();//游戏总的处理炮弹和舰艇碰撞的函数


    void frontcollide(frontWarShip *Warship);//封装的处理前排舰艇与敌方子弹碰撞的函数

    void checkDeath();//鉴定我方舰艇是否存活的函数

    void battleShoot();//处理后排战列的函数

    void drawback(QPainter &painter, backWarShip *WarShip,
                  QBrush *black_brush, QBrush *green_brush);//封装的绘制后排战舰立绘和血量的函数

    void Boundary();//判断敌方是否到达边界并对我方后排造成伤害的函数

    void check_airCraft();//处理我方航母空袭冷却的函数

    QPoint *findEnemy(QPoint start);//判断离某艘舰艇最近的敌舰的函数，用于我方舰艇普通射击和鱼雷机自动索敌

    void checkEnemy();//判断敌人是否全部死亡，以及实现敌人依批次出现

    int getEnd();//返回游戏是否结束

    int getSuccess();//返回游戏是否成功

    QVector<frontWarShip*>getFront();//返回战斗结束后前排舰艇信息

    QVector<backWarShip*>getBack();//返回战斗结束后后排舰艇信息

private:
    QVector<cannonBall *> torplist;//储存我方鱼雷信息
    skillButton *planeButton;//右下空袭技能按钮
    skillButton *torpedoesButton;//右下鱼雷技能按钮
    skillButton *navalgunButton;//右下战列炮击技能按钮
    operationButton *operationbutton;//左上自律战斗按钮
    QPushButton *pause;//右上暂停按钮
    QPoint target;//游戏中前排舰艇目标地点


    QVector<frontWarShip *> frontwarship;//储存战斗中前排舰艇

    QSet<int> pressedKeys;//储存每帧中的键盘事件

    quitMessageBox *quitmessagebox;//退出提示框

    QVector<cannonBall *> cannonball;//储存我方炮弹
    QVector<cannonBall *> enemycannon;//储存地方炮弹

    QTimer *updateTimer;//游戏内部计时器


    QVector<enemyWarShip *> enemylist;//储存目前场上具有的敌人

    QPixmap aim;//战列开炮准心立绘

    QVector<backWarShip*>backwarship;//储存战斗中后排舰艇

    QVector<cannonBall*>battlecannon;//储存战斗中战列信息

    QVector<cannonBall*>airRaid;//储存战斗中空袭信息

    QVector<airCraft*>aircraft;//储存战斗中舰载机

    QVector<enemyWarShip*>totalenemy;//储存战斗中全部敌人

    int state;//储存战斗进行到第几阶段（出现第几批次敌人

    int isEnding;//游戏是否结束

    int isSucceed;//游戏是否胜利



public
    slots:
    void callquitmessage();//创建退出战斗提示框

    void torp();//处理鱼雷事件

     void airraid();//处理空袭事件

    signals:
            void closeFight();//战斗结束或者暂时退出信号

            void fail();//战斗失败信号

            void succeed();//战斗成功信号
};

#endif // FIGHTSCENE_H
