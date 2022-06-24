#include"gameScene.h"
#include<QDataStream>
#include<QFile>
const double pi=acos(-1);

const int startpos_x=100;
const int startpos_y=40;
const int gridWdith=100;
const int gridHeight=100;
const int row=6;
const int col=10;
const int dir[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
//地图
int m[20][20]= {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 3, 0, 0, 0, 2, 0},
        {0, 1, 0, 2, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 3, 0, 0, 3, 0, 1, 2, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 2, 3, 0, 0, 0, 2, 0, 3, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}
};
gameScene::gameScene(QWidget *parent):QWidget(parent) {
    ismove = 0;
    setFixedSize(1200, 675);
    moveTimer = new QTimer;
    moveTimer->start(16);
    updateTimer = new QTimer;
    updateTimer->start(450);
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
    quitmessagebox=new quitMessageBox(this);
    QVector<frontWarShip*>front;
    QVector<backWarShip*>back;
    QVector<enemyWarShip*>Investigation;
    QVector<enemyWarShip*>main;
    initFront();
    initBack();
    initEnemy();
    game=nullptr;
 isfail=0;
};

gameScene::~gameScene() {
    delete moveTimer;
    delete game;
    delete gameMap;
}

void gameScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    //绘制背景
    painter.drawPixmap(0, 0, *backgroud);
    for (int i = 0; i <= col; i++) {
        painter.drawLine(QPoint(startpos_x + i * gridWdith, startpos_y),
                         QPoint(startpos_x + i * gridWdith, startpos_y + row * gridHeight));
    }
    for (int i = 0; i <= row; i++) {
        painter.drawLine(QPoint(startpos_x, startpos_y + i * gridHeight),
                         QPoint(startpos_x + col * gridWdith, startpos_y + i * gridHeight));
    }
    //绘制敌方舰队
    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=col;j++)
        {
            if(gameMap->getState(j,i)==2)
                painter.drawPixmap((j-1)*100+startpos_x,(i-1)*100+startpos_y,QPixmap(":/res/Investigation.png").scaled(100,100));
            if(gameMap->getState(j,i)==3)
                 painter.drawPixmap((j-1)*100+startpos_x,(i-1)*100+startpos_y,QPixmap(":/res/Main.png").scaled(100,100));

        }
    }

    painter.drawPixmap(startpos_x + 0 * gridWdith, startpos_y + 1 * gridHeight, *wall_1_3);
    painter.drawPixmap(startpos_x + 6 * gridWdith, startpos_y + 1 * gridHeight, *wall_2_2);
    painter.drawPixmap(startpos_x + 2 * gridWdith, startpos_y + 0 * gridHeight, *wall_2_1);
    painter.drawPixmap(startpos_x + 4 * gridWdith, startpos_y + 3 * gridHeight, *wall_1_1);
    painter.drawPixmap(startpos_x + 4 * gridWdith, startpos_y + 5 * gridHeight, *wall_3_1);
    painter.drawPixmap(fleetLocation.x(), fleetLocation.y(), *flagShip);
    //判断是否放结算画面
    if(drawclock>0)
    {
        painter.drawPixmap(0,0,result);
    }
}

void gameScene::move(int direction) {
    if(drawclock>0)
        return;
    if (ismove)
        return;
    else
        ismove = 1;
    //判断立绘朝向
    if (direction == 2)
        flagShip = new QPixmap(":/res/lisailiu(reverse).png");
    if (direction == 3)
        flagShip = new QPixmap(":/res/lisailiu.png");
    if (!moveTimer->isActive())
        moveTimer->start(16);
    moveTimer->disconnect();
    //移动
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

 void gameScene::keyPressEvent(QKeyEvent *event) {
     if(drawclock>0)
         return;
        //开始战斗
     if (event->key() == Qt::Key_Z&&!ismove) {
        startFight();
     }
     //呼出退出提示框
     if(event->key() == Qt::Key_Escape&&!ismove)
     {
         callquitmessage();
     }
 }
 void gameScene::upgateGame() {
     int fx = (fleetLocation.x() + gridWdith / 2) / 100;
     int fy = (fleetLocation.y() + 60 + 2 * gridHeight / 3) / 100;
    current = new grid(fx, fy,  gameMap->getState(fx,fy));

     updateTimer->disconnect();
     connect(updateTimer, &QTimer::timeout, [&]() {
            //判断是否放结算画面
         if(drawclock>2)
         {
             drawclock=0;
             update();
              if(isfail)
                  this->close();
         }
         if(drawclock>0)
         {
             drawclock++;
             update();
             return;
         }
         //由寻路结果判断移动方向
         if (!gamePath.empty()) {
             QVector<grid*>a,b;

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

        if(game!=nullptr)
            return;
     if(drawclock>0)
         return;
     if (ismove || !gamePath.empty())
         return;
     if(current->getstate()>1)
     {
        startFight();
        return;
     }
     int tx = event->x() / 100;
     int ty = (event->y() + 60) / 100;
     int fx = (fleetLocation.x() + gridWdith / 2) / 100;
     int fy = (fleetLocation.y() + 60 + 2 * gridHeight / 3) / 100;
     if(tx<1||tx>col||ty<1||ty>row)
         return;
     gamePath.clear();

     grid *current  = new grid(fx, fy,  gameMap->getState(fx,fy));
     grid *end = new grid(tx, ty, gameMap->getState(tx,ty));
     if (!gamePath.empty())
         return;
     //若点击合法，则根据A*算法寻找合法路径
     if (event->x() >= 100 && event->x() <= 1100 && event->y() >= 40 && event->y() <= 640) {
         gamePath = gameMap->search(current, end);

     }

 }

 void gameScene::closeFight()
 {if(game==nullptr)
         return;

        game->close();
        game->clearFocus();
        if(game->getEnd())
        {
            if(game->getSuccess())
            {
                //若胜利则播放胜利结算图片
                result=QPixmap(":/res/win.png").scaled(1200,675);
                for(auto v:front){delete v;v=nullptr;}front.clear();
                for(auto v:back){delete v;v=nullptr;}back.clear();
                //继承战斗结束的舰艇状态
                for(auto v:game->getFront())
                {
                    v->setTarget(nullptr);
                    front.push_back(new frontWarShip(*v));

                }
                //清除击败的敌方舰队
                gameMap->setState(current->getx(),current->gety(), 0);
                current->setState(0);
                for(auto v:game->getBack())
                {
                    battleShip*BB=dynamic_cast<battleShip*>(v);
                    carrierVessel*CV=dynamic_cast<carrierVessel*>(v);
                    if(BB!=nullptr)
                    back.push_back(new battleShip(*BB));
                    else {
                       back.push_back(new carrierVessel(*CV));
                    }
                }
            }
            else
            {
                result=QPixmap(":/res/fail.png").scaled(1200,675);
                isfail=1;
            }
            drawclock=1;
        }

        game=nullptr;
        this->setFocus();
     moveTimer->disconnect();
    updateTimer->start(450);
    moveTimer->start(16);

 }

void gameScene::closeEvent(QCloseEvent *)
{
    moveTimer->stop();
    updateTimer->stop();
}
void gameScene::callquitmessage()
{
    quitmessagebox->exec();
}

void gameScene::startFight()
{
    if(ismove)
        return;
    if(game!=nullptr)
        return;
    //判断敌方舰队类型
    if(current->getstate()==2)
    game = new fightScene(this,front,back,Investigation);
    else if(current->getstate()==3)
    game= new fightScene(this,front,back,main);
    else
        return;
    game->show();
    updateTimer->stop();
    moveTimer->stop();
    game->setFocus();
    game->playGame();
    connect(game, &fightScene::closeFight, this, &gameScene::closeFight);
}

void gameScene::initFront()
{
    QVector<cannonBall*>test;
    test.push_back(new cannonBall(0, 0,100,20,0, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,pi/6, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,-pi/6, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,-pi/12, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,pi/12, nullptr, ":/res/comet.png",80));
    front.push_back(
            new frontWarShip(4000, 100, 400, 8, 100, 750, 2, QPixmap(":/res/Portland.png"), QPoint(300, 337),
                             nullptr,100));
    front.push_back(
            new frontWarShip(3000, 100, 400, 7, 70, 650, 2, QPixmap(":/res/Helena.png"), QPoint(200, 337),
                                            nullptr,110));
    front.push_back(
            new frontWarShip(3500, 100, 400, 7, 45, 500, 2, QPixmap(":/res/Santiago.png"), QPoint(100, 337),
                            nullptr,120));
       front[0]->setBarrage(test);
       front[1]->setBarrage(test);
       front[2]->setBarrage(test);
}

void gameScene::initBack()
{
    back.push_back(new carrierVessel(4000,300,0,0,100,0,QPixmap("://res/unicorn.png"),QPoint(0,100),700,2,400));
back.push_back(new battleShip(8000,700,0,0,1000,0,QPixmap(":/res/Richelieu.png"),QPoint(0,300),1000,1));
 back.push_back(new battleShip(8000,350,0,0,100,0,QPixmap("://res/Hutten.png"),QPoint(0,500),450,1));
}

void gameScene::initEnemy()
{  standardEnemy *enemy1=new standardEnemy(10000, 100, 100, 2, 5, 90, 1000, QPixmap("://res/liangchan-1.png"), QPoint(700, 200));
    standardEnemy *enemy2=new standardEnemy(10000, 100, 100, 2, 5, 90, 1000, QPixmap("://res/liangchan-1.png"), QPoint(900, 100));
    standardEnemy *enemy3=new standardEnemy(10000, 100, 100, 2, 5, 90, 1000, QPixmap("://res/liangchan-1.png"), QPoint(900, 500));
    standardEnemy *enemy4=new standardEnemy(10000, 100, 100, 2, 5, 90, 1000, QPixmap("://res/liangchan-1.png"), QPoint(700, 400));
    standardEnemy *Selfdetonation1=new standardEnemy(1000, 0, 0, 10, 1, 9000, 2000, QPixmap("://res/Self-detonation.png"), QPoint(1200, 500));
    standardEnemy *Selfdetonation2=new standardEnemy(1000, 0, 0, 10, 1, 9000, 2000, QPixmap("://res/Self-detonation.png"), QPoint(1200, 150));
    humanoidEnemy *Yukikaze=new humanoidEnemy(20000, 400, 200, 3, 110, 600, QPixmap("://res/Yukikaze.png"), QPoint(900, 300));
    humanoidEnemy *Takao=  new humanoidEnemy(30000, 400, 200, 3, 110, 600, QPixmap("://res/Takao.png"), QPoint(900, 300));

    Investigation.push_back(new standardEnemy(*enemy1));
    Investigation.push_back(new standardEnemy(*enemy2));
    Investigation.push_back( new humanoidEnemy(*Yukikaze));
    Investigation.push_back( new standardEnemy(*enemy3));
    Investigation.push_back( new standardEnemy(*enemy4));
    Investigation.push_back(new standardEnemy(*Selfdetonation1));
    Investigation.push_back(new standardEnemy(*Selfdetonation2));
    Investigation.push_back(new standardEnemy(*Selfdetonation2));
    Investigation.push_back(new standardEnemy(*Selfdetonation1));
    Investigation[0]->setState(1);
    Investigation[1]->setState(2);
    Investigation[2]->setState(2);
    Investigation[3]->setState(2);
    Investigation[4]->setState(1);
    Investigation[5]->setState(1);
    Investigation[6]->setState(1);
    Investigation[7]->setState(2);
    Investigation[8]->setState(2);

    main.push_back(new standardEnemy(*enemy1));
    main.push_back(new standardEnemy(*enemy1));
    main.push_back(new standardEnemy(*enemy2));
    main.push_back( new humanoidEnemy(*Yukikaze));
    main.push_back( new humanoidEnemy(*Takao));
    main.push_back(new standardEnemy(*enemy3));
    main.push_back(
            new standardEnemy(*enemy4));
    main.push_back(
            new standardEnemy(*enemy4));
    main.push_back(
            new standardEnemy(*Selfdetonation1));
    main.push_back(
            new standardEnemy(*Selfdetonation2));
    main[0]->setState(1);
    main[1]->setState(2);
    main[2]->setState(3);
    main[3]->setState(2);
    main[4]->setState(3);
    main[5]->setState(3);
    main[6]->setState(2);
    main[7]->setState(1);
    main[8]->setState(2);
    main[9]->setState(2);

    delete enemy1;
    delete enemy2;
    delete enemy3;
    delete enemy4;
    delete Yukikaze;
    delete Takao;
    delete Selfdetonation1;
    delete Selfdetonation2;
}
