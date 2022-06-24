#include"startScene.h"
#include"QPixmap"
startScene::startScene(QWidget*parent):QWidget(parent)
{
    setFixedSize(1200, 675);
    setWindowTitle("碧蓝航线");
    setWindowIcon(QIcon("://res/aa9jv-f80ap-001.ico"));
    update();
}
void startScene::mousePressEvent(QMouseEvent *)
{
    game=nullptr;
    //每次点击则打开关卡界面
    game=new gameScene(this);
    connect(game,&gameScene::quit,this,&startScene::childClose);
    this->clearFocus();
    game->setFocus();
    game->upgateGame();
    game->show();

}
void startScene::paintEvent(QPaintEvent *)
    {
        QPainter paint(this);
        paint.drawPixmap(0,0,QPixmap(":/res/start.png"));
    }

void startScene::childClose()
{
    game->close();
        game=nullptr;
}


