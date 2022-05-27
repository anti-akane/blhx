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
class gameScene:public QWidget
{
   Q_OBJECT
public:
    gameScene(QWidget* parent=nullptr);
    ~gameScene();
    void mousePressEvent(QMouseEvent *event);
    void upgateGame();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent*);
    void move();
    void move(const int direction);
private:
   int ismove;
   levelMap* gameMap;
   QPoint fleetLocation;
   QTimer *moveTimer;
   QTimer *upgateTimer;
   int movecontroller=0;
   fightScene *game;
   QStack<grid*>gamePath;
   QPixmap* flagShip;
   QPixmap* backgroud;
   QPixmap* wall_1_1;
   QPixmap* wall_1_3;
   QPixmap* wall_2_2;
   QPixmap* wall_2_1;
   QPixmap* wall_3_1;
};

#endif // GAMESCENE_H
