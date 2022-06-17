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
    gameScene(QWidget *parent = nullptr);

    ~gameScene();

    void mousePressEvent(QMouseEvent *event);

    void upgateGame();

    void keyPressEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *);

    void move(const int direction);

    void callquitmessage();

    void closeEvent(QCloseEvent *event);


    QTimer *moveTimer;
    QTimer *upgateTimer;

    void startFight();

    void initFront();

    void initBack();

    void initEnemy();
public
    slots:
            void closeFight();
  signals:
            void quit();
private:
    int ismove;
    grid *current;
    levelMap *gameMap;
    QPoint fleetLocation;
    int movecontroller = 0;
    fightScene *game;
    QStack<grid *> gamePath;
    QPixmap *flagShip;
    QPixmap *backgroud;
    QPixmap *wall_1_1;
    QPixmap *wall_1_3;
    QPixmap *wall_2_2;
    QPixmap *wall_2_1;
    QPixmap *wall_3_1;
    int drawclock;
    QPixmap picture;
    quitMessageBox *quitmessagebox;
    QVector<frontWarShip*>front;
    QVector<backWarShip*>back;
    QVector<enemyWarShip*>Investigation;
    QVector<enemyWarShip*>main;
    int isfail;

};

#endif // GAMESCENE_H
