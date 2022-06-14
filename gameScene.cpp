#include"gameScene.h"
const int startpos_x=100;
const int startpos_y=40;
const int gridWdith=100;
const int gridHeight=100;
const int row=6;
const int col=10;
const int dir[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
int m[20][20]= {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}
};
gameScene::gameScene(QWidget *parent):QWidget(parent) {
    ismove = 0;
    setFixedSize(1200, 675);
    moveTimer = new QTimer;
    moveTimer->start(16);
    upgateTimer = new QTimer;
    upgateTimer->start(450);
    setWindowTitle("碧蓝航线");
    setWindowIcon(QIcon("://res/aa9jv-f80ap-001.ico"));
    fleetLocation = QPoint(startpos_x - gridHeight / 2, startpos_y - 2 * gridWdith / 3);
    update();
    flagShip = new QPixmap(":/res/lisailiu.png");
    backgroud = new QPixmap(":/res/1200px-Bg_banama_1.png");
    wall_1_1 = new QPixmap(":/res/wall 1-1.png");
    wall_1_3 = new QPixmap(":/res/wall 1-3.png");
    wall_2_1 = new QPixmap(":/res/wall 2-1.png");
    wall_2_2 = new QPixmap(":/res/wall 2-2.png");
    wall_3_1 = new QPixmap(":/res/wall 3-1.png");
    movecontroller = 0;
    gameMap = new levelMap(row, col, m);
};

gameScene::~gameScene() {
    delete moveTimer;
    delete game;
}

void gameScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);

        painter.drawPixmap(0, 0, *backgroud);
    for (int i = 0; i <= col; i++) {
        painter.drawLine(QPoint(startpos_x + i * gridWdith, startpos_y),
                         QPoint(startpos_x + i * gridWdith, startpos_y + row * gridHeight));
    }
    for (int i = 0; i <= row; i++) {
        painter.drawLine(QPoint(startpos_x, startpos_y + i * gridHeight),
                         QPoint(startpos_x + col * gridWdith, startpos_y + i * gridHeight));
    }

    painter.drawPixmap(startpos_x + 0 * gridWdith, startpos_y + 1 * gridHeight, *wall_1_3);
    painter.drawPixmap(startpos_x + 6 * gridWdith, startpos_y + 1 * gridHeight, *wall_2_2);
    painter.drawPixmap(startpos_x + 2 * gridWdith, startpos_y + 0 * gridHeight, *wall_2_1);
    painter.drawPixmap(startpos_x + 4 * gridWdith, startpos_y + 3 * gridHeight, *wall_1_1);
    painter.drawPixmap(startpos_x + 4 * gridWdith, startpos_y + 5 * gridHeight, *wall_3_1);
    painter.drawPixmap(fleetLocation.x(), fleetLocation.y(), *flagShip);
}

void gameScene::move(int direction) {
    if (ismove)
        return;
    else
        ismove = 1;
    if (direction == 2)
        flagShip = new QPixmap(":/res/lisailiu(reverse).png");
    if (direction == 3)
        flagShip = new QPixmap(":/res/lisailiu.png");
    if (!moveTimer->isActive())
        moveTimer->start(16);
    moveTimer->disconnect();  
    connect(moveTimer, &QTimer::timeout, [=]() {
        movecontroller++;
        if (movecontroller > 25) {
            moveTimer->stop();
            movecontroller = 0;
            ismove = 0;
            return;
        }
        fleetLocation.setX(fleetLocation.x() + 4 * dir[direction][0]);
        fleetLocation.setY(fleetLocation.y() + 4 * dir[direction][1]);

        update();
    });

}

//void

 void gameScene::keyPressEvent(QKeyEvent *event) {
     if (event->key() == Qt::Key_Z&&!ismove) {
         game = new fightScene(this);
         connect(game,&fightScene::closeFight,this,&gameScene::closeFight);
         game->show();
         upgateTimer->stop();
         moveTimer->stop();
         game->setFocus();
         game->playGame();
     }
 }
 void gameScene::upgateGame() {
     int fx = (fleetLocation.x() + gridWdith / 2) / 100;
     int fy = (fleetLocation.y() + 60 + 2 * gridHeight / 3) / 100;
     static grid *current = new grid(fx, fy, m[fy][fx]);
     upgateTimer->disconnect();
     connect(upgateTimer, &QTimer::timeout, [&]() {
         if (!gamePath.empty()) {

             grid *next = gamePath.top();
             gamePath.pop();
             if (next->gety() == current->gety() - 1)
                 move(0);
             else if (next->gety() == current->gety() + 1)
                 move(1);
             else if (next->getx() == current->getx() - 1)
                 move(2);
             else if (next->getx() == current->getx() + 1)
                 move(3);
             current = next;
         }
     });
 }

 void gameScene::mousePressEvent(QMouseEvent *event) {
     if (ismove||!gamePath.empty())
         return;
     gamePath.clear();
     int tx = event->x() / 100;
     int ty = (event->y() + 60) / 100;
     int fx = (fleetLocation.x() + gridWdith / 2) / 100;
     int fy = (fleetLocation.y() + 60 + 2 * gridHeight / 3) / 100;
     grid *current = new grid(fx, fy, m[fy][fx]);
     grid *end = new grid(tx, ty, m[ty][tx]);
     if (!gamePath.empty())
         return;
     if (event->x() >= 100 && event->x() <= 1100 && event->y() >= 40 && event->y() <= 640) {
         gamePath = gameMap->search(current, end);

     }

 }

 void gameScene::closeFight()
 {
     setFocus();
     game->clearFocus();
     moveTimer->disconnect();
     upgateTimer->start(450);
     moveTimer->start(16);

 }
