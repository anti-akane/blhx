#include"fightScene.h"
#include"math.h"
#include <synchapi.h>
#include"quitMessageBox.h"
#include<QMessageBox>
#include<QFont>
#include<QDebug>
#include <QtGlobal>
#include<QCoreApplication>
const double pi=acos(-1.0);
const int frames =30;
fightScene::fightScene(QWidget *parent,QVector<frontWarShip*>startfront,QVector<backWarShip*>startback,QVector<enemyWarShip*>startEnemy):QWidget(parent)
{
    //清除原信息
    for(auto v:frontwarship){delete v;v=nullptr;}frontwarship.clear();
    for(auto v:backwarship){delete v;v=nullptr;}backwarship.clear();
    for(auto v:totalenemy){delete v;v=nullptr;}totalenemy.clear();
    for(auto v:enemylist){delete v;v=nullptr;}enemylist.clear();
    //从关卡界面加载前排舰艇信息
    for(auto v:startfront)
    {
        frontwarship.push_back(new frontWarShip(*v));
        //重置技能数
        frontwarship[frontwarship.size()-1]->reStart();

    }
    //从关卡界面加载后排舰艇信息
    for(auto v:startback)
    {
        //判断为后排战舰类型
        battleShip*BB=dynamic_cast<battleShip*>(v);
        carrierVessel*CV=dynamic_cast<carrierVessel*>(v);
        //若为战列则调用战列构造函数
        if(BB!=nullptr)
        backwarship.push_back(new battleShip(*BB));
        else {
        //若为航母则调用战列构造函数
           backwarship.push_back(new carrierVessel(*CV));
        }
        //重置技能数
        backwarship[backwarship.size()-1]->reStart();
    }
    //从关卡界面加载敌方舰艇信息
    for(auto v:startEnemy)
    {
        //判断敌人类型
        humanoidEnemy *check = dynamic_cast<humanoidEnemy *>(v);
        standardEnemy *another = dynamic_cast<standardEnemy *>(v);
            //若为人形则调用人形敌舰构造函数
            if (check != nullptr)
                totalenemy.push_back(new humanoidEnemy(*check));
            //若为量产型则调用量产型敌舰构造函数
            else
                totalenemy.push_back(new standardEnemy(*another));
    }
    //初始化前排舰艇移动目标
    target = QPoint(300, 337);
    //初始化敌人批次为0
    this->state=0;
    //设置前排舰艇移动目标，领舰朝着target移动，其他朝着前一个目标移动，实现保持战列
    frontwarship[0]->setTarget(&target);
    for (int i = 1; i < frontwarship.size(); i++) {
        frontwarship[i]->setTarget(&(frontwarship[i - 1]->getlocation()));
    }
    //三个技能按钮，退出消息框的初始化
    quitmessagebox = new quitMessageBox(this);
    QPixmap *plane = new QPixmap(":/res/feiji-available.png");
    QPixmap *torpedoes = new QPixmap(":/res/yvlei-available.png");
    QPixmap *navalgun = new QPixmap(":/res/jianpao-available.png");
    //设置按钮大小
    *plane = plane->scaled(100, 100, Qt::KeepAspectRatio);
    *torpedoes = torpedoes->scaled(100, 100, Qt::KeepAspectRatio);
    *navalgun = navalgun->scaled(100, 100, Qt::KeepAspectRatio);
    int torpnumber = 0;
    int navalnumber = 0;
    int planenumber=0;
    for (auto v: frontwarship)
        torpnumber += v->getTorpNumber();
    for (auto v: backwarship)
      {
        battleShip *check = dynamic_cast<battleShip *>(v);
         if(check!=nullptr)
        navalnumber += v->getMaxSkill();
         else
        planenumber+=v->getMaxSkill();
    }
    torpedoesButton = new skillButton(this, torpedoes, "yvlei", torpnumber);
    navalgunButton = new skillButton(this, navalgun, "jianpao", navalnumber);
    planeButton = new skillButton(this, plane, "feiji", planenumber);
    torpedoesButton->move(950, 570);
    planeButton->move(800, 570);
    navalgunButton->move(1100, 570);

    //初始化战列准心图标
    aim=QPixmap("://res/aim");
    aim=aim.scaled(100, 100, Qt::KeepAspectRatio);
    //初始化画面更新定时器
    updateTimer = new QTimer(this);

    //自律按钮初始化
    operationbutton = new operationButton(this);
    //界面设置
    setFixedSize(1200, 675);
    setWindowTitle("碧蓝航线");
    setWindowIcon(QIcon("://res/aa9jv-f80ap-001.ico"));
    //暂停键
    QPixmap *pausepix = new QPixmap(":/res/pause.png");
    pause = new QPushButton(this);
    pause->resize(pausepix->size());
    pause->move(1200 - pausepix->width(), 0);
    pause->setStyleSheet("QPushButton{border-image: url(:/res/pause.png);}");
    connect(pause, &QPushButton::pressed, this, &fightScene::callquitmessage);

    //链接按钮和技能发动事件
    connect(torpedoesButton, &skillButton::skills, this, &fightScene::torp);
    connect(planeButton, &skillButton::skills, this, &fightScene::airraid);
    connect(navalgunButton, &skillButton::skills, this, &fightScene::battleShoot);
    connect(this,&fightScene::fail,this,&fightScene::close);
    connect(this,&fightScene::succeed,this,&fightScene::close);
    delete plane;
    delete torpedoes;
    delete navalgun;
    delete pausepix;
    isEnding=0;
    update();
    updateTimer->start(frames);
}

void fightScene::drawfront(QPainter&painter,frontWarShip*WarShip,QBrush*black_brush,QBrush*green_brush)
{
    painter.drawPixmap(WarShip->getlocation().x()-WarShip->getTachie().width()/2,WarShip->getlocation().y()-WarShip->getTachie().height()/2,WarShip->getTachie());
    painter.setBrush(*black_brush);
    painter.drawRect(WarShip->getlocation().x()-40,WarShip->getlocation().y()-WarShip->getTachie().height()/2,
                     80,8);
    painter.setBrush(*green_brush);
    painter.drawRect(WarShip->getlocation().x()-40,WarShip->getlocation().y()-WarShip->getTachie().height()/2,
                     80*WarShip->getHpRate(),8);
}
void fightScene::drawback(QPainter &painter, backWarShip *WarShip, QBrush *black_brush, QBrush *green_brush)
{
    painter.drawPixmap(WarShip->getlocation().x(),WarShip->getlocation().y(),WarShip->getTachie());
    painter.setBrush(*black_brush);
    painter.drawRect(WarShip->getlocation().x(),WarShip->getlocation().y()+WarShip->getTachie().height(),
                     80,8);
    painter.setBrush(*green_brush);
    painter.drawRect(WarShip->getlocation().x(),WarShip->getlocation().y()+WarShip->getTachie().height(),
                     80*WarShip->getHpRate(),8);
}
void fightScene::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/res/1200px-Bg_banama_1.png"));

    painter.drawPixmap(target.x(), target.y(), QPixmap(":/res/target.png"));
    //绘制我方子弹
    for (auto v: cannonball) {
        if (v->getAngle() > 0)
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() + v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
        else
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() - v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
    }
    //绘制敌方子弹
    for (auto v: enemycannon) {
        if (v->getAngle() > 0)
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() + v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
        else
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() - v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
    }
    //绘制我方舰艇
    QBrush green_brush(QColor("#33FF66"));
    QBrush black_brush(QColor("#000000"));
    for (int i = frontwarship.size() - 1; i >= 0; i--)
        drawfront(painter, frontwarship[i], &black_brush, &green_brush);
    //绘制敌方舰艇
    for (auto v: enemylist) {
        painter.drawPixmap(v->getlocation().x(), v->getlocation().y(), v->getTachie());
        painter.setBrush(black_brush);
        painter.drawRect(v->getlocation().x() + v->getwidth() * 0.15, v->getlocation().y(),
                         v->getTachie().width() * 0.65, 8);
        painter.setBrush(green_brush);
        painter.drawRect(v->getlocation().x() + v->getwidth() * 0.15, v->getlocation().y(),
                         v->getTachie().width() * 0.65 * v->getHpRate(), 8);
    }
    //绘制技能按钮技能数量
    QFont font;
    font.setPointSize(20);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(800, 570, QString::number(planeButton->getSkillNumber()) + "/" +
                               QString::number(planeButton->getmaxSkillNumber()));
    painter.drawText(950, 570, QString::number(torpedoesButton->getSkillNumber()) + "/" +
                               QString::number(torpedoesButton->getmaxSkillNumber()));
    painter.drawText(1100, 570, QString::number(navalgunButton->getSkillNumber()) + "/" +
                               QString::number(navalgunButton->getmaxSkillNumber()));
    //绘制战列准心
    if(navalgunButton->IsDown()&&navalgunButton->getSkillNumber()>0)
    {
        painter.drawPixmap(frontwarship[0]->getlocation().x()+600-50,frontwarship[0]->getlocation().y()-50,aim);
    }
    //绘制后排战列
    for(auto v:backwarship)
    {
           drawback(painter, v, &black_brush, &green_brush);
    }
    //绘制舰载机
    for(auto v:aircraft)
    {
        painter.drawPixmap(v->getX(),v->getY(),v->getPix());
    }
}

void fightScene::callquitmessage() {
    updateTimer->stop();
    quitmessagebox->exec();
    updateTimer->start(frames);
}
fightScene::~fightScene() {
    for(auto v:frontwarship){delete v;v=nullptr;}frontwarship.clear();
    for(auto v:backwarship){delete v;v=nullptr;}backwarship.clear();
    for(auto v:totalenemy){delete v;v=nullptr;}totalenemy.clear();
    for(auto v:enemylist){delete v;v=nullptr;}enemylist.clear();
    for(auto v:enemycannon){delete v;v=nullptr;}enemycannon.clear();
    for(auto v:cannonball){delete v;v=nullptr;}cannonball.clear();
    for(auto v:airRaid){delete v;v=nullptr;}airRaid.clear();
    for(auto v:torplist){delete v;v=nullptr;}torplist.clear();
    for(auto v:battlecannon){delete v;v=nullptr;}battlecannon.clear();
    for(auto v:aircraft){delete v;v=nullptr;}aircraft.clear();
    delete quitmessagebox;
    delete planeButton;
    delete torpedoesButton;
    delete navalgunButton;
    delete updateTimer;
    delete operationbutton;
    delete pause;
}
void fightScene::keyPressEvent(QKeyEvent *event) {
    if(!updateTimer->isActive())
        return;
    //呼出退出消息提示框
    if (event->key() == Qt::Key_Escape) {
        callquitmessage();
    }
    //实现按下T键打开准心
   QMouseEvent *press = new QMouseEvent(QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                         Qt::NoModifier);
    if(event->key()==Qt::Key_T)
        QApplication::postEvent(navalgunButton, press);
    switch (event->key()) {
        case Qt::Key_E:
        case Qt::Key_R:
        case Qt::Key_T:
            return;
    }
    if (!event->isAutoRepeat())
        pressedKeys.insert(event->key());
}

void fightScene::keyReleaseEvent(QKeyEvent *event) {
        if(!updateTimer->isActive())
            return;
    if (event->isAutoRepeat())
        return;
    //处理技能按钮事件
    switch (event->key()) {
        case Qt::Key_E:
            pressedKeys.insert(event->key());
            break;
        case Qt::Key_R:
            pressedKeys.insert(event->key());
            break;
        case Qt::Key_T:
            pressedKeys.insert(event->key());
            break;
    }
    keyPress();
    if (!event->isAutoRepeat())
        pressedKeys.remove(event->key());

}
void fightScene::updatetarger(int x, int y) {
    if (!operationbutton->getOpState())
        return;
    if (x < 10)
        target.setX(10);
    else if (x > 600)
        target.setX(600);
    else
        target.setX(x);
    if (y < 10)
        target.setY(10);
    else if (y > 660)
        target.setY(660);
    else
        target.setY(y);
}
void fightScene::playGame() {

    connect(updateTimer, &QTimer::timeout, [=]() {
        QTime start;
        start.start();
        qApp->processEvents();
        //处理键盘事件
        keyPress();
        //处理自律操作
        if (!operationbutton->getOpState()) {
            autoOperate();
        }
        //处理战舰移动
        for (auto v: frontwarship) {
            v->move();
        }
        for (auto v: enemylist) {
            v->move();
        }
        qDebug();//不知道意义，但是一旦删去就会崩溃
        //处理战舰射击
        shoot();
        qDebug();//不知道意义，但是一旦删去就会崩溃
        //处理子弹与战舰碰撞事件
        collide();
        qDebug();//不知道意义，但是一旦删去就会崩溃
        //绘制图片
        update();
        qDebug();//不知道意义，但是一旦删去就会崩溃
        //处理敌方舰艇撞击边界事件
        Boundary();
        qDebug();//不知道意义，但是一旦删去就会崩溃
        //处理空袭事件
        check_airCraft();
        qDebug();//不知道意义，但是一旦删去就会崩溃
        //处理我方角色死亡事件
        checkDeath();
        qDebug();//不知道意义，但是一旦删去就会崩溃
        //处理敌方角色死亡和出现批次逻辑事件
        checkEnemy();
        qDebug();//不知道意义，但是一旦删去就会崩溃

    });
}
void fightScene::keyPress() {
    QMouseEvent *press = new QMouseEvent(QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                         Qt::NoModifier);
    QMouseEvent *release = new QMouseEvent(QEvent::MouseButtonRelease, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                           Qt::NoModifier);
     int targetspeed;//判断目标移动的速度，避免目标移动过快，领舰无法跟上
    if(!frontwarship.empty())
  targetspeed = frontwarship[0]->getSpeed() * 1.2;
    else
     targetspeed=10;
    for (int key: pressedKeys) {
        switch (key) {
            case Qt::Key_Q:
            //Q键按下自动操作按钮
                QApplication::postEvent(operationbutton, press);
                break;
            case Qt::Key_E:
            //E键释放空袭技能按钮
                if (!planeButton->IsDown())
                    QApplication::postEvent(planeButton, release);
                break;
            case Qt::Key_R:
            //R键释放鱼雷技能按钮
                if (!torpedoesButton->IsDown())
                    QApplication::postEvent(torpedoesButton, release);
                break;
            case Qt::Key_T:
            //T键释放战舰开火技能按钮
                QApplication::postEvent(navalgunButton, release);
                break;
            //WSAD控制目标点移动
            case Qt::Key_W:
                updatetarger(target.x(), target.y() - targetspeed);
                break;
            case Qt::Key_S:
                updatetarger(target.x(), target.y() + targetspeed);
                break;
            case Qt::Key_A:
                updatetarger(target.x() - targetspeed, target.y());
                break;
            case Qt::Key_D:
                updatetarger(target.x() + targetspeed, target.y());
                break;
        }
    }
}

void fightScene::mouseMoveEvent(QMouseEvent *event) {
    //实现鼠标拖动准心移动
    if (event->buttons() == Qt::LeftButton) {
        if (event->pos().x() <= 600) {
            updatetarger(event->pos().x(), event->pos().y());
        }
    }
}

void fightScene::shoot() {
    //处理我方子弹移动逻辑
    for (QVector<cannonBall *>::iterator it = cannonball.begin(); it != cannonball.end();) {

        if (!((*it)->check())) {
            *it = nullptr;
            delete *it;
            cannonball.erase(it);
        } else {
            (*it)->move();
            it++;
        }
    }
    //处理敌方子弹移动逻辑
    for (QVector<cannonBall *>::iterator it = enemycannon.begin(); it != enemycannon.end();) {

        if (!((*it)->check())) {
            *it = nullptr;
            delete *it;
            delete (*it);
            *it=nullptr;
            enemycannon.erase(it);
        } else {
            (*it)->move();
            it++;
        }
    }
    //处理我方前排舰艇射击
    for (auto v: frontwarship) {
        //处理普通射击
        frontshoot(v);
        //处理弹幕射击事件
        if (v->checkBarrage()) {
            for (auto k: v->getBarrage()) {
                auto barr = new cannonBall(v->getlocation().x(), v->getlocation().y() + 5, k->getHurt(),
                                           k->getSpeed(), k->getAngle(), nullptr, ":/res/torp.png", k->getW());

                barr->setPix(k->getPixmap());
                cannonball.push_back(barr);
            }
        }
        //处理鱼雷事件
        if (v->checkTorp()) {
            torpedoesButton->addSkillNumber();
            torplist.push_back(new cannonBall(0, 0, 100, 10, 0, v));
        }
    }
    //处理敌方射击
    enemyshoot();
    //处理我方空袭和战列开火冷却
    for (auto v: backwarship) {
        battleShip *check = dynamic_cast<battleShip *>(v);
        if (check != nullptr) {
            if (v->check()) {

                navalgunButton->addSkillNumber();
                battlecannon.push_back(new cannonBall(0, 0, 1, 1, 1, v));
            }
        } else {
            if (v->check()) {

                planeButton->addSkillNumber();
                airRaid.push_back(new cannonBall(0, 0, 1, 1, 1, v));
            }

        }
    }
}

void fightScene::frontshoot(frontWarShip*WarShip) {
    //处理前排射击
    if (WarShip->shoot()) {
        //自动将目标设定为距离己方最近的单位
        QPoint *goal = findEnemy(QPoint(WarShip->getlocation().x(), WarShip->getlocation().y()));

        cannonball.push_back(
                new cannonBall(WarShip->getlocation().x(), WarShip->getlocation().y() + 5, WarShip->power_hurt(), 50,
                               cal_angle(&WarShip->getlocation(), goal)));
        cannonball.push_back(
                new cannonBall(WarShip->getlocation().x(), WarShip->getlocation().y() - 5, WarShip->power_hurt(), 50,
                               cal_angle(&WarShip->getlocation(), goal)));
        delete goal;
    }

}
void fightScene::closeEvent(QCloseEvent *) {
    this->clearFocus();
    emit closeFight();
    this->updateTimer->stop();
}

void fightScene::torp() {
    if (torplist.empty())
        return;
    //处理鱼雷释放事件
    cannonBall *torp = torplist[0];
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), 10, 0, nullptr, ":/res/torp.png", 35));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), 10, pi / 30.0, nullptr, ":/res/torp.png", 35));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), 10, -1.0 * pi / 30.0, nullptr, ":/res/torp.png",
                                        35));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), 10, pi / 40.0, nullptr, ":/res/torp.png", 35));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), 10, -1.0 * pi / 40.0, nullptr, ":/res/torp.png",
                                        35));
    //释放后处理对应舰艇技能数量
    frontWarShip *front = dynamic_cast<frontWarShip *>(torp->getparent());
    front->declineTorpNumber();
    delete torplist[0];
    torplist[0] = nullptr;
    torplist.erase(torplist.begin());
}

void fightScene::autoOperate() {
    if(frontwarship.empty())
        return ;
    //随机移动
    int l_x = frontwarship[0]->getlocation().x(), l_y = frontwarship[0]->getlocation().y();
    int t_x = target.x(), t_y = target.y();
    double len = sqrt((l_x - t_x) * (l_x - t_x) + (l_y - t_y) * (l_y - t_y));
    if (len <= 3 * frontwarship[0]->getSpeed()) //判断是否到达目的地，若到达则随机选择新的目标点
    {

        target.setX(120 + qrand() % 400);
        target.setY(100 + qrand() % 500);
    }

    QMouseEvent *release = new QMouseEvent(QEvent::MouseButtonRelease, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                           Qt::NoModifier);
    //自动释放技能
    if (torpedoesButton->getSkillNumber() && !enemylist.empty())
        QApplication::postEvent(torpedoesButton, release);
    if (planeButton->getSkillNumber() && !enemylist.empty())
        QApplication::postEvent(planeButton, release);
    if (navalgunButton->getSkillNumber() && !enemylist.empty())
        QApplication::postEvent(navalgunButton, release);
}

double fightScene::cal_angle(QPoint *begin, QPoint *goal) {
    //单纯计算两点之间角度
    if (goal == nullptr)
        return 0;
    int b_x = begin->x(), b_y = begin->y();
    int g_x = goal->x(), g_y = goal->y();
    double xx = g_x - b_x;
    double yy = g_y - b_y;
    double tempAngle;
    if (xx == 0.0)
        tempAngle = pi / 2.0;
    else
        tempAngle = atan(fabs(yy / xx));

    if ((xx < 0.0) && (yy >= 0.0))
        tempAngle = pi - tempAngle;
    else if ((xx < 0.0) && (yy < 0.0))
        tempAngle = pi + tempAngle;
    else if ((xx >= 0.0) && (yy < 0.0))
        tempAngle = pi * 2.0 - tempAngle;

    return (tempAngle);
}

void fightScene::collide() {
    //处理我方子弹与敌方舰艇碰撞逻辑
    for (QVector<cannonBall *>::iterator can = cannonball.begin(); can != cannonball.end();) {
        int isBomb = 0;//判断是否爆炸过，若爆炸过则删除
        battleCannon *check = dynamic_cast<battleCannon *>(*can);
        if ((check != nullptr && !check->ifBomb())) {
            can++;
            continue;
        }
        for (QVector<enemyWarShip *>::iterator  enemy= enemylist.begin(); enemy != enemylist.end();) {
            if ((*enemy)->getRect().intersects((*can)->getRect())) {
                isBomb = 1;//碰撞箱相交，则发生爆炸
                (*enemy)->declineHP((*can)->getHurt());
                if ((*enemy)->getHpRate() == 0)
                   {
                    delete (*enemy);
                    *enemy=nullptr;
                    enemylist.erase(enemy);
                }
                    break;
            }
                enemy++;
        }
        if (isBomb || (check != nullptr && check->ifBomb()))
        { delete (*can);
            *can=nullptr;
            cannonball.erase(can);

        }
        else
           { can++;

        }
    }
    //处理前排受伤
    for (auto v: frontwarship) {
        frontcollide(v);
    }
}

void fightScene::enemyshoot() {
    if(frontwarship.empty())
        return;
    //敌方射击
    for (auto v: enemylist) {
        if (v->shoot()) {
            int b_x = v->getlocation().x() + v->getwidth() / 4, b_y = v->getlocation().y() + v->getheight() / 2;
            QPoint *goal = new QPoint(frontwarship[0]->getlocation());
            enemycannon.push_back(new cannonBall(b_x, b_y - 5, v->power_hurt() / 4, 30,
                                                 cal_angle(new QPoint(b_x, b_y), goal)));
            enemycannon.push_back(new cannonBall(b_x, b_y + 5, v->power_hurt() / 4, 30,
                                                 cal_angle(new QPoint(b_x, b_y), goal)));
            delete goal;
        }
        //敌方人形鱼雷
        humanoidEnemy *check = dynamic_cast<humanoidEnemy *>(v);
        if (check != nullptr) {
            if (check->check_torp()) {
                enemycannon.push_back(new cannonBall(v->getlocation().x(), v->getlocation().y() + v->getheight() / 2,
                                                     v->torp_hurt() / 4, 20, 0 + pi, nullptr, ":/res/torp.png", 35
                ));
                enemycannon.push_back(new cannonBall(v->getlocation().x(), v->getlocation().y() + v->getheight() / 2,
                                                     v->torp_hurt() / 4, 20, pi / 8 + pi, nullptr, ":/res/torp.png",
                                                     35));
                enemycannon.push_back(new cannonBall(v->getlocation().x(), v->getlocation().y() + v->getheight() / 2,
                                                     v->torp_hurt() / 4, 20, -pi / 8 + pi, nullptr, ":/res/torp.png",
                                                     35));
            }
        }
    }

}

void fightScene::frontcollide(frontWarShip *Warship) {
    int times = 0;
    for (QVector<cannonBall *>::iterator can = enemycannon.begin(); can != enemycannon.end();) {
        if (Warship->getRect().intersects((*can)->getRect())) {
            times++;
            Warship->declineHP((*can)->getHurt());
            {
                delete (*can);
                *can=nullptr;
                enemycannon.erase(can);}
            if (times == 3)//避免同时间收到过多伤害被秒杀
                break;

        } else
            can++;
    }
}

void fightScene::checkDeath() {
    int flag = 0;
    //检查后排舰艇是否死亡
    for (QVector<backWarShip *>::iterator item = backwarship.begin(); item != backwarship.end();) {
        battleShip *check = dynamic_cast<battleShip *>(*item);
        if (check != nullptr) {

            if ((*item)->getHpRate() == 0) {
                //若死亡，则撤销其已经冷却好的技能
                navalgunButton->declineMaxSkill((*item)->getMaxSkill());
                navalgunButton->declineSkill((*item)->getCurrentSkill());
                for (QVector<cannonBall *>::iterator can = battlecannon.begin(); can != battlecannon.end();) {
                    if ((*can)->getparent() == *item)
                    {
                        delete (*can);
                        *can=nullptr;
                        battlecannon.erase(can);}
                    else
                        can++;
                }
                delete (*item);
                *item=nullptr;
                backwarship.erase(item);
            } else
                item++;
        } else {
            if ((*item)->getHpRate() == 0) {
                 //若死亡，则撤销其已经冷却好的技能
                planeButton->declineMaxSkill((*item)->getMaxSkill());
                planeButton->declineSkill((*item)->getCurrentSkill());
                for (QVector<cannonBall *>::iterator can = airRaid.begin(); can != airRaid.end();) {
                    if ((*can)->getparent() == *item)
                    {
                        delete (*can);
                        *can=nullptr;
                        airRaid.erase(can);}
                    else
                        can++;
                }
                delete (*item);
                *item=nullptr;
                backwarship.erase(item);
            } else
                item++;
        }

    }
//检查前排舰艇是否死亡
    for (QVector<frontWarShip *>::iterator item = frontwarship.begin(); item != frontwarship.end();) {
        if ((*item)->getHpRate() == 0) {
            flag = 1;
             //若死亡，则撤销其已经冷却好的技能
            torpedoesButton->declineMaxSkill((*item)->getTorpNumber());
            torpedoesButton->declineSkill((*item)->getCurrentTorpNumber());
            for (QVector<cannonBall *>::iterator can = torplist.begin(); can != torplist.end();) {
                if ((*can)->getparent() == *item)
                {
                    delete (*can);
                    *can=nullptr;
                    torplist.erase(can);
                }
                else
                    can++;
            }
            delete (*item);
            *item=nullptr;
            frontwarship.erase(item);
        } else
            item++;
    }
    if(frontwarship.empty()||backwarship.empty())
    {
        //若前排或后排全死，则游戏失败
        isEnding=1;
        isSucceed=0;
        emit fail();
        return;
    }
    if (flag) {
        frontwarship[0]->setTarget(&target);
        for (int i = 1; i < frontwarship.size(); i++) {
            frontwarship[i]->setTarget(&(frontwarship[i - 1]->getlocation()));
        }
    }

}

void fightScene::airraid() {
    for(auto v:enemycannon){delete v;v=nullptr;}enemycannon.clear();
    //空袭恢复己方血量
    for (auto v: frontwarship) {
        v->addHP(1600*(1-v->getHpRate()));
    }
    for (auto v: backwarship) {
        v->addHP(400*(1-v->getHpRate()));
    }
    if (airRaid.empty())
        return;
    cannonBall *air = airRaid[0];
    carrierVessel *CV = dynamic_cast<carrierVessel *>(air->getparent());
    CV->decreaseSkill();
    aircraft.push_back(new airCraft(10, 200, CV->hurt(), 0));
    aircraft.push_back(new airCraft(50, 300, CV->hurt(), 0));
    aircraft.push_back(new airCraft(30, 400, CV->hurt(), 0));
    aircraft.push_back(new airCraft(15, 35, CV->hurt(), 1));
    aircraft.push_back(new airCraft(55, 30, CV->hurt(), 1));
    aircraft.push_back(new airCraft(35, 40, CV->hurt(), 1));
}

void fightScene::battleShoot() {
    if(frontwarship.empty())
        return;
    if (battlecannon.empty())
        return;
    cannonBall *cannon = battlecannon[0];
    backWarShip *start = dynamic_cast<backWarShip *>(cannon->getparent());
    QPoint *end;
    if (operationbutton->getOpState())
        //若为自律，则寻找敌方血量最多的单位攻击
        end = new QPoint(frontwarship[0]->getlocation().x() + 600 - 50, frontwarship[0]->getlocation().y() - 50);
    else {
        int Max = 0;
        for (auto v: enemylist) {
            if (v->getHP() > Max) {
                end = new QPoint(v->getlocation().x() + v->getTachie().width() / 2,
                                 v->getlocation().y() + v->getTachie().height() / 2);
                Max = v->getHP();
            }

        }

    }
    QPoint *begin = new QPoint(start->getlocation());
    double angle = cal_angle(begin, end);
    cannonball.push_back(new battleCannon(start->getlocation().x() + 10, start->getlocation().y(),
                                          start->power_hurt(), 50, angle, nullptr, ":/res/battlecannon.png", *end));
    cannonball.push_back(new battleCannon(start->getlocation().x() + 20, start->getlocation().y() - 10,
                                          start->power_hurt(), 50, angle, nullptr, ":/res/battlecannon.png", *end));
    cannonball.push_back(new battleCannon(start->getlocation().x(), start->getlocation().y() + 10,
                                          start->power_hurt(), 50, angle, nullptr, ":/res/battlecannon.png", *end));
    start->decreaseSkill();
    delete battlecannon[0];
    battlecannon[0] = nullptr;
    battlecannon.erase(battlecannon.begin());

}

void fightScene::Boundary() {
    int n = backwarship.size();
    for (QVector<enemyWarShip *>::iterator enemy = enemylist.begin(); enemy != enemylist.end();) {
        if ((*enemy)->getlocation().x() <= 10) {
            //根据横坐标判断哪艘后排舰艇收到伤害
            backwarship[(*enemy)->getlocation().y() / (675.0 / n)]->declineHP(1000 * (*enemy)->getHpRate());
            delete (*enemy);
            *enemy=nullptr;
            enemylist.erase(enemy);
        } else
            enemy++;
    }
}

void fightScene::check_airCraft() {
    for (QVector<airCraft *>::iterator item = aircraft.begin(); item != aircraft.end();) {
        {
            if ((*item)->isbombing()) {
                if ((*item)->check()) {
                    //每架轰炸机随机丢下三枚炸弹
                    for (int i = 0; i < 3; i++) {
                        int tx = 500 + qrand() % 600, ty = 100 + qrand() % 450;
                        cannonball.push_back(new battleCannon(tx, ty,
                                                              (*item)->getHurt() / 4, 1, 0, nullptr,
                                                              "://res/bombing.png", QPoint(tx + 3, ty), 120));

                    }
                    delete (*item);
                    *item=nullptr;
                    aircraft.erase(item);
                } else {
                    (*item)->move();
                    item++;
                }
            } else {
                if ((*item)->check()) {
                    QPoint *now = new QPoint((*item)->getX(), (*item)->getY());
                    //每架轰炸机丢下三枚平行雷，三枚自动瞄准雷
                    cannonball.push_back(new cannonBall((*item)->getX(), (*item)->getY(),
                                                        (*item)->getHurt(), 20, 0, nullptr, ":/res/torp.png", 35));
                    cannonball.push_back(new cannonBall((*item)->getX() - 5, (*item)->getY() - 40,
                                                        (*item)->getHurt(), 20, 0, nullptr, ":/res/torp.png", 35));
                    cannonball.push_back(new cannonBall((*item)->getX() + 5, (*item)->getY() + 40,
                                                        (*item)->getHurt(), 20, 0, nullptr, ":/res/torp.png", 35));
                    cannonball.push_back(new cannonBall((*item)->getX(), (*item)->getY() + 10,
                                                        (*item)->getHurt(), 15,
                                                        cal_angle(now, findEnemy(*now)), nullptr, ":/res/torp.png",
                                                        35));
                    cannonball.push_back(new cannonBall((*item)->getX(), (*item)->getY() - 10,
                                                        (*item)->getHurt(), 15,
                                                        cal_angle(now, findEnemy(*now)), nullptr, ":/res/torp.png",
                           35));
                    delete (*item);
                    *item=nullptr;
                    aircraft.erase(item);
                } else {
                    (*item)->move();
                    item++;
                }
            }
        }
    }}

QPoint *fightScene::findEnemy(QPoint start) {
    //寻找距离最近的敌方，若为人形敌方舰艇则更为优先打击
        int b_x = start.x(), b_y = start.y();
        QPoint *goal = nullptr;
        int len = 1e8;
        for (auto v: enemylist) {
            int g_x = v->getlocation().x() + v->getwidth() / 2, g_y = v->getlocation().y() + v->getheight() / 2;
            int temp = (b_x - g_x) * (b_x - g_x) + (b_y - g_y) * (b_y - g_y);
            humanoidEnemy *check = dynamic_cast<humanoidEnemy *>(v);
            if (check != nullptr)
                temp /= 2;
            if (temp < len) {
                goal = new QPoint(g_x, g_y);
                len = temp;
            }

        }
        return goal;
    }


void fightScene::checkEnemy() {
    if (enemylist.empty()) {
        state++;
        if(totalenemy.empty())
        {
            //若敌人全部死亡，游戏胜利
            isEnding=1;
            isSucceed=1;
            emit succeed();
            return;
        }
        for (QVector<enemyWarShip *>::iterator item = totalenemy.begin(); item != totalenemy.end();) {
            {
                humanoidEnemy *check = dynamic_cast<humanoidEnemy *>(*item);
                standardEnemy *another = dynamic_cast<standardEnemy *>(*item);
                if ((*item)->getState() == state) {
                    if (check != nullptr)
                        enemylist.push_back(new humanoidEnemy(*check));
                    else
                        enemylist.push_back(new standardEnemy(*another));
                    delete (*item);
                    *item=nullptr;
                    totalenemy.erase(item);
                } else
                    item++;
            }

        }

    }

}

int fightScene::getEnd()
{
    return isEnding;
}

int fightScene::getSuccess()
{
    return isSucceed;
}

QVector<frontWarShip*>fightScene::getFront(){
    return frontwarship;
}

QVector<backWarShip*>fightScene::getBack(){
    return backwarship;
}

