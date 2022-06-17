#include"fightScene.h"
#include"math.h"
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
    frontwarship.clear();
    backwarship.clear();
    enemylist.clear();
    totalenemy.clear();
    for(auto v:startfront)
    {

        frontwarship.push_back(new frontWarShip(*v));
        frontwarship[frontwarship.size()-1]->reStart();

    }
    for(auto v:startback)
    {
        battleShip*BB=dynamic_cast<battleShip*>(v);
        carrierVessel*CV=dynamic_cast<carrierVessel*>(v);
        if(BB!=nullptr)
        backwarship.push_back(new battleShip(*BB));
        else {
           backwarship.push_back(new carrierVessel(*CV));
        }
        backwarship[backwarship.size()-1]->reStart();
    }
    for(auto v:startEnemy)
    {
        humanoidEnemy *check = dynamic_cast<humanoidEnemy *>(v);
        standardEnemy *another = dynamic_cast<standardEnemy *>(v);

            if (check != nullptr)
                totalenemy.push_back(new humanoidEnemy(*check));
            else
                totalenemy.push_back(new standardEnemy(*another));
    }

    init();
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
    for (auto v: cannonball) {
        if (v->getAngle() > 0)
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() + v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
        else
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() - v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
    }

    for (auto v: enemycannon) {
        if (v->getAngle() > 0)
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() + v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
        else
            painter.drawPixmap(v->getX() + v->getH() * sin(v->getAngle()) / 2.0,
                               v->getY() - v->getH() * cos(v->getAngle()) / 2.0, *(v->getPixmap()));
    }
    QBrush green_brush(QColor("#33FF66"));
    QBrush black_brush(QColor("#000000"));

    for (int i = frontwarship.size() - 1; i >= 0; i--)
        drawfront(painter, frontwarship[i], &black_brush, &green_brush);


    for (auto v: enemylist) {
        painter.drawPixmap(v->getlocation().x(), v->getlocation().y(), v->getTachie());
        painter.setBrush(black_brush);
        painter.drawRect(v->getlocation().x() + v->getwidth() * 0.15, v->getlocation().y(),
                         v->getTachie().width() * 0.65, 8);
        painter.setBrush(green_brush);
        painter.drawRect(v->getlocation().x() + v->getwidth() * 0.15, v->getlocation().y(),
                         v->getTachie().width() * 0.65 * v->getHpRate(), 8);
    }

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
    if(navalgunButton->IsDown()&&navalgunButton->getSkillNumber()>0)
    {
        painter.drawPixmap(frontwarship[0]->getlocation().x()+600-50,frontwarship[0]->getlocation().y()-50,aim);
    }

    for(auto v:backwarship)
    {
           drawback(painter, v, &black_brush, &green_brush);
    }
    for(auto v:aircraft)
    {
        painter.drawPixmap(v->getX(),v->getY(),v->getPix());
    }
}
void fightScene::init() {
    target = QPoint(300, 337);
    QVector<cannonBall*>test;
    this->state=0;
    test.push_back(new cannonBall(0, 0,100,20,0, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,pi/6, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,-pi/6, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,-pi/12, nullptr, ":/res/comet.png",80));
    test.push_back(new cannonBall(0, 0,100,20,pi/12, nullptr, ":/res/comet.png",80));
    frontwarship[0]->setTarget(&target);
    for (int i = 1; i < frontwarship.size(); i++) {
        frontwarship[i]->setTarget(&(frontwarship[i - 1]->getlocation()));
    }
    frontwarship[0]->setBarrage(test);
    //三个技能按钮的初始化
    quitmessagebox = new quitMessageBox(this);
    QPixmap *plane = new QPixmap(":/res/feiji-available.png");
    QPixmap *torpedoes = new QPixmap(":/res/yvlei-available.png");
    QPixmap *navalgun = new QPixmap(":/res/jianpao-available.png");
    //设置按钮大小
    *plane = plane->scaled(100, 100, Qt::KeepAspectRatio);
    *torpedoes = torpedoes->scaled(100, 100, Qt::KeepAspectRatio);
    *navalgun = navalgun->scaled(100, 100, Qt::KeepAspectRatio);
    int torpnumber = 0;
    for (auto v: frontwarship)
        torpnumber += v->getTorpNumber();
    int navalnumber = 0;
    int planenumber=0;
    for (auto v: backwarship)
      {
        battleShip *check = dynamic_cast<battleShip *>(v);
         if(check!=nullptr)
        navalnumber += v->getMaxSkill();
         else
        planenumber+=v->getMaxSkill();
    }
    torpedoesButton = new skillButton(this, torpedoes, "yvlei", torpnumber);
    torpedoesButton->move(950, 570);
    navalgunButton = new skillButton(this, navalgun, "jianpao", navalnumber);
        planeButton = new skillButton(this, plane, "feiji", planenumber);
            planeButton->move(800, 570);
    navalgunButton->move(1100, 570);
    aim=QPixmap("://res/aim");
    aim=aim.scaled(100, 100, Qt::KeepAspectRatio);
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

    //角色初始化
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
void fightScene::callquitmessage() {
    updateTimer->stop();
    quitmessagebox->exec();
    updateTimer->start(frames);
}
fightScene::~fightScene() {
    frontwarship.clear();
    backwarship.clear();
    enemylist.clear();
    totalenemy.clear();
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
    if (event->key() == Qt::Key_Escape) {
        callquitmessage();
    }
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

        keyPress();
        qDebug()<<1<<endl;
        if (!operationbutton->getOpState()) {
            autoOperate();
        }
        for (auto v: frontwarship) {
            v->move();
        }
        for (auto v: enemylist) {
            v->move();
        }
        qDebug()<<2<<endl;
        shoot();
        qDebug()<<3<<endl;
        collide();
        qDebug()<<4<<endl;
        update();
        qDebug()<<5<<endl;
        Boundary();
        qDebug()<<6<<endl;
        check_airCraft();
        qDebug()<<7<<endl;
        checkDeath();
        qDebug()<<8<<endl;
        checkEnemy();
        qDebug()<<9<<endl;

    });
}
void fightScene::keyPress() {
    QMouseEvent *press = new QMouseEvent(QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                         Qt::NoModifier);
    QMouseEvent *release = new QMouseEvent(QEvent::MouseButtonRelease, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                           Qt::NoModifier);
     int targetspeed;
    if(!frontwarship.empty())
  targetspeed = frontwarship[0]->getSpeed() * 1.2;
    else
     targetspeed=10;
    for (int key: pressedKeys) {
        switch (key) {
            case Qt::Key_Q:
                QApplication::postEvent(operationbutton, press);
                break;
            case Qt::Key_E:
                if (!planeButton->IsDown())
                    QApplication::postEvent(planeButton, release);
                break;
            case Qt::Key_R:
                if (!torpedoesButton->IsDown())
                    QApplication::postEvent(torpedoesButton, release);
                break;
            case Qt::Key_T:
                QApplication::postEvent(navalgunButton, release);
                break;
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
    if (event->buttons() == Qt::LeftButton) {
        if (event->pos().x() <= 600) {
            updatetarger(event->pos().x(), event->pos().y());
        }
    }
}

void fightScene::shoot() {

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
    for (QVector<cannonBall *>::iterator it = enemycannon.begin(); it != enemycannon.end();) {

        if (!((*it)->check())) {
            *it = nullptr;
            delete *it;
            enemycannon.erase(it);
        } else {
            (*it)->move();
            it++;
        }
    }

    for (auto v: frontwarship) {
        frontshoot(v);
        if (v->checkBarrage()) {
            for (auto k: v->getBarrage()) {
                auto barr = new cannonBall(v->getlocation().x(), v->getlocation().y() + 5, k->getHurt(),
                                           k->getSpeed(), k->getAngle(), nullptr, ":/res/torp.png", k->getW());

                barr->setPix(k->getPixmap());
                cannonball.push_back(barr);
            }
        }
        if (v->checkTorp()) {
            torpedoesButton->addSkillNumber();
            torplist.push_back(new cannonBall(0, 0, 100, 10, 0, v));
        }
    }
    enemyshoot();

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
    if (WarShip->shoot()) {
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
    frontWarShip *front = dynamic_cast<frontWarShip *>(torp->getparent());
    front->declineTorpNumber();
    torplist[0] = nullptr;
    torplist.erase(torplist.begin());
}

void fightScene::autoOperate() {
    if(frontwarship.empty())
        return ;
    int l_x = frontwarship[0]->getlocation().x(), l_y = frontwarship[0]->getlocation().y();
    int t_x = target.x(), t_y = target.y();
    double len = sqrt((l_x - t_x) * (l_x - t_x) + (l_y - t_y) * (l_y - t_y));
    if (len <= 3 * frontwarship[0]->getSpeed()) {

        target.setX(120 + qrand() % 400);
        target.setY(100 + qrand() % 500);
    }

    QMouseEvent *release = new QMouseEvent(QEvent::MouseButtonRelease, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                           Qt::NoModifier);
    if (torpedoesButton->getSkillNumber() && !enemylist.empty())
        QApplication::postEvent(torpedoesButton, release);
    if (planeButton->getSkillNumber() && !enemylist.empty())
        QApplication::postEvent(planeButton, release);
    if (navalgunButton->getSkillNumber() && !enemylist.empty())
        QApplication::postEvent(navalgunButton, release);
}

double fightScene::cal_angle(QPoint *begin, QPoint *goal) {
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
    for (QVector<cannonBall *>::iterator can = cannonball.begin(); can != cannonball.end();) {
        int flag1 = 0;
        battleCannon *check = dynamic_cast<battleCannon *>(*can);
        if ((check != nullptr && check->check())) {
            can++;
            continue;
        }
        for (QVector<enemyWarShip *>::iterator  enemy= enemylist.begin(); enemy != enemylist.end();) {
            int flag2 = 0;
            if ((*enemy)->getRect().intersects((*can)->getRect())) {
                flag1 = 1;
                flag2 = 1;

                (*enemy)->declineHP((*can)->getHurt());
                if ((*enemy)->getHpRate() == 0)
                    enemylist.erase(enemy);
                    break;
            }

            if (!flag2)
                enemy++;

        }

        if (flag1 || (check != nullptr && !check->check()))
        {cannonball.erase(can);

        }
        else
           { can++;

        }

    }
    for (auto v: frontwarship) {
        frontcollide(v);
    }
}

void fightScene::enemyshoot() {
    if(frontwarship.empty())
        return;

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
            enemycannon.erase(can);
            if (times == 3)
                break;

        } else
            can++;
    }
}

void fightScene::checkDeath() {
    int flag = 0;
    for (QVector<backWarShip *>::iterator item = backwarship.begin(); item != backwarship.end();) {
        battleShip *check = dynamic_cast<battleShip *>(*item);
        if (check != nullptr) {
            if ((*item)->getHpRate() == 0) {
                navalgunButton->declineMaxSkill((*item)->getMaxSkill());
                navalgunButton->declineSkill((*item)->getCurrentSkill());
                for (QVector<cannonBall *>::iterator can = battlecannon.begin(); can != battlecannon.end();) {
                    if ((*can)->getparent() == *item)
                        battlecannon.erase(can);
                    else
                        can++;
                }
                backwarship.erase(item);
            } else
                item++;
        } else {
            if ((*item)->getHpRate() == 0) {
                planeButton->declineMaxSkill((*item)->getMaxSkill());
                planeButton->declineSkill((*item)->getCurrentSkill());
                for (QVector<cannonBall *>::iterator can = airRaid.begin(); can != airRaid.end();) {
                    if ((*can)->getparent() == *item)
                        airRaid.erase(can);
                    else
                        can++;
                }
                backwarship.erase(item);
            } else
                item++;
        }

    }

    for (QVector<frontWarShip *>::iterator item = frontwarship.begin(); item != frontwarship.end();) {
        if ((*item)->getHpRate() == 0) {
            flag = 1;
            torpedoesButton->declineMaxSkill((*item)->getTorpNumber());
            torpedoesButton->declineSkill((*item)->getCurrentTorpNumber());
            for (QVector<cannonBall *>::iterator can = torplist.begin(); can != torplist.end();) {
                if ((*can)->getparent() == *item)
                    torplist.erase(can);
                else
                    can++;
            }
            frontwarship.erase(item);
        } else
            item++;
    }
    if(frontwarship.empty()||backwarship.empty())
    {
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
    enemycannon.clear();
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
                                          start->torp_hurt(), 50, angle, nullptr, ":/res/battlecannon.png", *end));
    cannonball.push_back(new battleCannon(start->getlocation().x() + 20, start->getlocation().y() - 10,
                                          start->torp_hurt(), 50, angle, nullptr, ":/res/battlecannon.png", *end));
    cannonball.push_back(new battleCannon(start->getlocation().x(), start->getlocation().y() + 10,
                                          start->torp_hurt(), 50, angle, nullptr, ":/res/battlecannon.png", *end));
    start->decreaseSkill();
    battlecannon[0] = nullptr;
    battlecannon.erase(battlecannon.begin());

}

void fightScene::Boundary() {
    int n = backwarship.size();
    for (QVector<enemyWarShip *>::iterator enemy = enemylist.begin(); enemy != enemylist.end();) {
        if ((*enemy)->getlocation().x() <= 10) {

            backwarship[(*enemy)->getlocation().y() / (675.0 / n)]->declineHP(1000 * (*enemy)->getHpRate());
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
                    for (int i = 0; i < 3; i++) {
                        int tx = 500 + qrand() % 600, ty = 100 + qrand() % 450;
                        cannonball.push_back(new battleCannon(tx, ty,
                                                              (*item)->getHurt() / 4, 1, 0, nullptr,
                                                              "://res/bombing.png", QPoint(tx + 3, ty), 120));

                    }
                    aircraft.erase(item);
                } else {
                    (*item)->move();
                    item++;
                }
            } else {
                if ((*item)->check()) {
                    QPoint *now = new QPoint((*item)->getX(), (*item)->getY());

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
                    aircraft.erase(item);
                } else {
                    (*item)->move();
                    item++;
                }
            }
        }
    }}

QPoint *fightScene::findEnemy(QPoint start) {
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
