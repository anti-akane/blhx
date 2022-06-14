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
#include"emptyWarShip.h"
#include"standardEmpty.h"
#include"humanoidEmpty.h"
class fightScene:public QWidget {
    Q_OBJECT
public:
    fightScene(QWidget *parent = nullptr);

    ~fightScene();

    void init();

    void playGame();

    void updatetarger(int x, int y);//封装的调整目的坐标函数

    void keyPressEvent(QKeyEvent *event);//处理战斗中的键盘信号

    void keyReleaseEvent(QKeyEvent *event);//处理键盘事件

    void paintEvent(QPaintEvent *);//绘制场景等

    void keyPress();//处理键盘事件，用于实现同时间处理多个键盘事件，实现八方向移动

    void mouseMoveEvent(QMouseEvent *event);//处理鼠标点击时间，主要用于处理点击改变坐标

    void closeEvent(QCloseEvent *event);

    void shoot();

    void frontshoot(frontWarShip *WarShip);

    void autoOperate();

    double cal_angle(QPoint *begin, QPoint *goal);//计算角度

    void drawfront(QPainter &painter, frontWarShip *WarShip, QBrush *black_brush, QBrush *green_brush);

    void collide();

    void emptyshoot();

    void frontcollide(frontWarShip *Warship);

    void checkDeath();

private:
    QVector<cannonBall *> torplist;
    skillButton *planeButton;
    skillButton *torpedoesButton;
    skillButton *navalgunButton;
    operationButton *operationbutton;
    QPushButton *pause;
    QPoint target;


    QVector<frontWarShip *> frontwarship;

    QSet<int> pressedKeys;//储存每帧中的键盘事件

    quitMessageBox *quitmessagebox;

    QVector<cannonBall *> cannonball;
    QVector<cannonBall *> emptycannon;

    QTimer *updateTimer;//游戏内部计时器


    QVector<emptyWarShip *> emptylist;

public
    slots:
            void callquitmessage();

    void torp();

    signals:
            void closeFight();

    void fail();
};

#endif // FIGHTSCENE_H
