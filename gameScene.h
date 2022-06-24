/* * * * * * * * * ** * * * * * * * * *
 * 关卡界面类
 * 作用为让玩家自主选择攻打的舰队，主力舰队（对前排威胁大），侦查舰队（对后排威胁大）
 * * * * * * * * * * * * * * * * * * * */
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include<QWidget>
#include<QIcon>
#include<QtCore>
#include<QObject>
#include<QPixmap>
#include<QPainter>
#include<QRect>
#include<QLabel>
#include<QPoint>
#include"fightScene.h"
#include"levelMap.h"
#include"quitMessageBox.h"
#include"QCloseEvent"
class gameScene:public QWidget {
    Q_OBJECT
public:
    //构造函数
    gameScene(QWidget *parent = nullptr);
    //析构函数
    ~gameScene();
    //处理鼠标点击时间，负责链接寻路系统和游戏画面
    void mousePressEvent(QMouseEvent *event);
    //界面主体函数，按固定帧刷新界面状态
    void upgateGame();
    //处理键盘事件，主要为按Z进入战斗，按ESC唤出退出游戏选项
    void keyPressEvent(QKeyEvent *event);
    //游戏画面处理函数
    void paintEvent(QPaintEvent *);
    //封装的舰队移动函数
    void move(const int direction);
    //封装的唤出退出游戏消息框函数
    void callquitmessage();
    //处理窗口关闭事件函数
    void closeEvent(QCloseEvent *event);
    //封装的开启战斗函数
    void startFight();
    //封装的初始化前排舰艇函数
    void initFront();
    //封装的初始化后排舰艇函数
    void initBack();
    //封装的初始化敌方舰艇函数
    void initEnemy();
public
    slots:
            //处理战斗界面结束事件
            void closeFight();
  signals:  //关卡界面关闭信号
            void quit();
private:

    QTimer *moveTimer;//移动动画计时器
    QTimer *updateTimer;//寻路计时器
    int ismove;//判断我方舰队是否在移动
    grid *current;//我方所在单元格
    levelMap *gameMap;//关卡地图
    QPoint fleetLocation;//表示我方舰队存在位置
    int movecontroller = 0;//移动计时器，处理移动动画
    fightScene *game;//战斗界面
    QStack<grid *> gamePath;//储存移动路径
    QPixmap *flagShip;//旗舰立绘
    QPixmap *backgroud;//背景
    QPixmap *wall_1_1;//1*1的障碍物图片
    QPixmap *wall_1_3;//1*3的障碍物图片
    QPixmap *wall_2_2;//2*2的障碍物图片
    QPixmap *wall_2_1;//2*1的障碍物图片
    QPixmap *wall_3_1;//3*1的障碍物图片
    int drawclock;//控制战斗胜利或战斗失败界面计时器
    QPixmap result;//战斗胜利或 战斗失败界面图片
    quitMessageBox *quitmessagebox;//退出界面消息框
    QVector<frontWarShip*>front;//我方前排舰艇
    QVector<backWarShip*>back;//我方后排舰艇
    QVector<enemyWarShip*>Investigation;//敌方侦查舰队
    QVector<enemyWarShip*>main;//敌方主力舰队
    int isfail;//判断游戏是否失败

};

#endif // GAMESCENE_H
