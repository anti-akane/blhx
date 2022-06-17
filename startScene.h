#ifndef STARTSCENE_H
#define STARTSCENE_H
#include"QWidget"
#include"gameScene.h"
#include"QMouseEvent"
#include"QPaintEvent"
#include"QPainter"
#include"QTimer"
class startScene:public QWidget
{
public:
    startScene(QWidget* parent);
    void mousePressEvent(QMouseEvent*event);
    void paintEvent(QPaintEvent *);
    void childClose();
private:
    gameScene *game;
};

#endif // STARTSCENE_H
