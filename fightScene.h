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
#include<QCloseEvent>
#include"frontWarShip.h"
#include"cannonBall.h"
class fightScene:public QWidget
{
    Q_OBJECT
public:
    fightScene(QWidget *parent=nullptr);
    ~fightScene();
    void init();
     void playGame();
     QTimer *updateTimer;//游戏内部计时器
private:
    skillButton* planeButton;
    skillButton* torpedoesButton;
    skillButton* navalgunButton;
    operationButton *operationbutton;
    QPushButton *pause;
    QPoint target;

    frontWarShip *firstship;
    frontWarShip *secondship;
    frontWarShip *thirdship;

    QSet<int> pressedKeys;//储存每帧中的键盘事件

    int autoOpTimer;//处理自律作战的轨迹所设置的计时器

    quitMessageBox *quitmessagebox;

    QVector< cannonBall *> cannonball;
    
    void updatetarger(int x,int y);//封装的调整目的坐标函数

    void keyPressEvent(QKeyEvent *event);//处理战斗中的键盘信号

     void keyReleaseEvent(QKeyEvent *event);//处理键盘事件

    void paintEvent(QPaintEvent*);//绘制场景等

     void keyPress();//处理键盘事件，用于实现同时间处理多个键盘事件，实现八方向移动

      void mouseMoveEvent(QMouseEvent *event);//处理鼠标点击时间，主要用于处理点击改变坐标

      void closeEvent(QCloseEvent *event);

      void shoot();
        public slots:
      void callquitmessage();
};

#endif // FIGHTSCENE_H
