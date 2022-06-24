/* * * * * * * * * ** * * * * * * * * *
 * 开始界面类
 * * * * * * * * * * * * * * * * * * * */
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
    //构造函数
    startScene(QWidget* parent);
    //鼠标按压事件，点击开始战斗
    void mousePressEvent(QMouseEvent*event);
    //绘制界面函数
    void paintEvent(QPaintEvent *);
    //处理关卡界面关闭函数
    void childClose();
private:
    gameScene *game;
};

#endif // STARTSCENE_H
