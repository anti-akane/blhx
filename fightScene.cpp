#include"fightScene.h"
#include"math.h"
#include"quitMessageBox.h"
#include<QMessageBox>
#include<QFont>
#include<QDebug>
#include <QtGlobal>
#include<QCoreApplication>
const double pi=acos(-1.0);

fightScene::fightScene(QWidget *parent):QWidget(parent)
{
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

    for (auto v: emptycannon) {
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


    for (auto v: emptylist) {
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
    painter.drawText(950, 570, QString::number(torpedoesButton->getSkillNumber()) + "/" +
                               QString::number(torpedoesButton->getmaxSkillNumber()));


}
void fightScene::init() {
    target = QPoint(300, 337);
    frontwarship.push_back(
            new frontWarShip(4000, 100, 400, 8, 100, 75, 2, QPixmap(":/res/Portland.png"), QPoint(300, 337), &target));
    frontwarship.push_back(new frontWarShip(3000, 100, 400, 7, 70, 65, 2, QPixmap(":/res/Helena.png"), QPoint(200, 337),
                                            &(frontwarship[0]->getlocation())));
    frontwarship.push_back(
            new frontWarShip(3500, 100, 400, 7, 45, 50, 2, QPixmap(":/res/Santiago.png"), QPoint(100, 337),
                             &(frontwarship[1]->getlocation())));
    emptylist.push_back(
            new standardEmpty(10000, 100, 100, 1, 5, 90, 1000, QPixmap("://res/liangchan-1.png"), QPoint(700, 100)));
    emptylist.push_back(
            new humanoidEmpty(20000, 400, 100, 3, 110, 1000, QPixmap("://res/Yukikaze.png"), QPoint(900, 300)));
    emptylist.push_back(
            new standardEmpty(10000, 100, 100, 1, 5, 100, 1000, QPixmap("://res/liangchan-1.png"), QPoint(700, 500)));
    //三个技能按钮的初始化
    quitmessagebox = new quitMessageBox(this);
    QPixmap *plane = new QPixmap(":/res/feiji-available.png");
    QPixmap *torpedoes = new QPixmap(":/res/yvlei-available.png");
    QPixmap *navalgun = new QPixmap(":/res/jianpao-available.png");
    //设置按钮大小
    *plane = plane->scaled(100, 100, Qt::KeepAspectRatio);
    *torpedoes = torpedoes->scaled(100, 100, Qt::KeepAspectRatio);
    *navalgun = navalgun->scaled(100, 100, Qt::KeepAspectRatio);
    planeButton = new skillButton(this, plane, "feiji", 3);
    planeButton->move(800, 570);
    int torpnumber = 0;
    for (auto v: frontwarship)
        torpnumber += v->getTorpNumber();
    torpedoesButton = new skillButton(this, torpedoes, "yvlei", torpnumber);
    torpedoesButton->move(950, 570);
    navalgunButton = new skillButton(this, navalgun, "jianpao", 2);
    navalgunButton->move(1100, 570);

    updateTimer = new QTimer(this);
    if (!updateTimer->isActive())
        updateTimer->start(30);
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

    delete plane;
    delete torpedoes;
    delete navalgun;
    delete pausepix;
    update();
    this->grabKeyboard();

}
void fightScene::callquitmessage() {
    updateTimer->stop();
    quitmessagebox->exec();
    updateTimer->start(30);
}
fightScene::~fightScene() {
    delete quitmessagebox;
    delete planeButton;
    delete torpedoesButton;
    delete navalgunButton;
    delete updateTimer;
    delete operationbutton;
    delete pause;
}
void fightScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        callquitmessage();
    }
    switch (event->key()) {
        case Qt::Key_E:
        case Qt::Key_R:
        case Qt::Key_T:
            return;
    }
    if (!event->isAutoRepeat())
        pressedKeys.insert(event->key());
    if (!updateTimer->isActive())
        updateTimer->start(30);
}

void fightScene::keyReleaseEvent(QKeyEvent *event) {
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

        qApp->processEvents();
        checkDeath();
        keyPress();
        if (!updateTimer->isActive())
            updateTimer->start(30);
        if (!operationbutton->getOpState()) {
            autoOperate();
        }
        for (auto v: frontwarship) {
            v->move();
        }
        for (auto v: emptylist) {
            v->move();
        }
        shoot();
        collide();
        update();

    });
}
void fightScene::keyPress() {
    QMouseEvent *press = new QMouseEvent(QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                         Qt::NoModifier);
    QMouseEvent *release = new QMouseEvent(QEvent::MouseButtonRelease, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                           Qt::NoModifier);
    if (pressedKeys.isEmpty()) {
        updateTimer->stop();
        return;
    }
    int targetspeed = frontwarship[0]->getSpeed() * 1.2;
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
                if (!navalgunButton->IsDown())
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
            if (!updateTimer->isActive())
                updateTimer->start(30);
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
    for (QVector<cannonBall *>::iterator it = emptycannon.begin(); it != emptycannon.end();) {

        if (!((*it)->check())) {
            *it = nullptr;
            delete *it;
            emptycannon.erase(it);
        } else {
            (*it)->move();
            it++;
        }
    }

    for (auto v: frontwarship) {
        frontshoot(v);
        if (v->checkTorp()) {
            torpedoesButton->addSkillNumber();
            torplist.push_back(new cannonBall(0, 0, 100, 0, v));
        }
    }
    emptyshoot();

}

void fightScene::frontshoot(frontWarShip*WarShip) {
    if (WarShip->shoot()) {
        int b_x = WarShip->getlocation().x(), b_y = WarShip->getlocation().y();
        QPoint *goal = nullptr;
        int len = 1e8;
        for (auto v: emptylist) {
            int g_x = v->getlocation().x() + v->getwidth() / 2, g_y = v->getlocation().y() + v->getheight() / 2;
            int temp = (b_x - g_x) * (b_x - g_x) + (b_y - g_y) * (b_y - g_y);
            humanoidEmpty *check = dynamic_cast<humanoidEmpty *>(v);
            if (check != nullptr)
                temp /= 2;
            //delete check;
            if (temp < len) {
                goal = new QPoint(g_x, g_y);
                len = temp;
            }

        }
        cannonball.push_back(
                new cannonBall(WarShip->getlocation().x(), WarShip->getlocation().y() + 5, WarShip->power_hurt(),
                               cal_angle(&WarShip->getlocation(), goal)));
        cannonball.push_back(
                new cannonBall(WarShip->getlocation().x(), WarShip->getlocation().y() - 5, WarShip->power_hurt(),
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
                                        torp->getparent()->torp_hurt(), 0, nullptr, ":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), pi / 30.0, nullptr, ":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), -1.0 * pi / 30.0, nullptr, ":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), pi / 40.0, nullptr, ":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(), torp->getparent()->getlocation().y(),
                                        torp->getparent()->torp_hurt(), -1.0 * pi / 40.0, nullptr, ":/res/torp.png"));
    torp->getparent()->declineTorpNumber();
    torplist[0] = nullptr;
    torplist.erase(torplist.begin());
}

void fightScene::autoOperate() {
    int l_x = frontwarship[0]->getlocation().x(), l_y = frontwarship[0]->getlocation().y();
    int t_x = target.x(), t_y = target.y();
    double len = sqrt((l_x - t_x) * (l_x - t_x) + (l_y - t_y) * (l_y - t_y));
    if (len <= 3 * frontwarship[0]->getSpeed()) {

        target.setX(120 + qrand() % 400);
        target.setY(100 + qrand() % 500);
    }

    QMouseEvent *press = new QMouseEvent(QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton,
                                         Qt::NoModifier);
    if (torpedoesButton->getSkillNumber())
        QApplication::postEvent(torpedoesButton, press);
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
        for (QVector<emptyWarShip *>::iterator empty = emptylist.begin(); empty != emptylist.end();) {
            int flag2 = 0;
            if ((*empty)->getRect().intersects((*can)->getRect())) {
                flag1 = 1;
                flag2 = 1;
                (*empty)->declineHP((*can)->getHurt());
                qDebug() << (*can)->getHurt() << endl;
                if ((*empty)->getHpRate() == 0)
                    emptylist.erase(empty);
                break;
            }
            if (!flag2)
                empty++;
        }
        if (flag1)
            cannonball.erase(can);
        else
            can++;
    }
    for (auto v: frontwarship) {
        frontcollide(v);
    }
}

void fightScene::emptyshoot() {
    for (auto v: emptylist) {
        if (v->shoot()) {
            int b_x = v->getlocation().x() + v->getwidth() / 4, b_y = v->getlocation().y() + v->getheight() / 2;
            QPoint *goal = new QPoint(frontwarship[0]->getlocation());
            emptycannon.push_back(new cannonBall(b_x, b_y - 5, v->power_hurt() / 30,
                                                 cal_angle(new QPoint(b_x, b_y), goal)));
            emptycannon.push_back(new cannonBall(b_x, b_y + 5, v->power_hurt() / 30,
                                                 cal_angle(new QPoint(b_x, b_y), goal)));
            delete goal;
        }
        humanoidEmpty *check = dynamic_cast<humanoidEmpty *>(v);
        if (check != nullptr) {
            if (check->check_torp()) {
                emptycannon.push_back(new cannonBall(v->getlocation().x(), v->getlocation().y() + v->getheight() / 2,
                                                     v->torp_hurt() / 20, 0 + pi, nullptr, ":/res/torp.png"));
                emptycannon.push_back(new cannonBall(v->getlocation().x(), v->getlocation().y() + v->getheight() / 2,
                                                     v->torp_hurt() / 20, pi / 8 + pi, nullptr, ":/res/torp.png"));
                emptycannon.push_back(new cannonBall(v->getlocation().x(), v->getlocation().y() + v->getheight() / 2,
                                                     v->torp_hurt() / 20, -pi / 8 + pi, nullptr, ":/res/torp.png"));
            }
        }
    }

}

void fightScene::frontcollide(frontWarShip *Warship) {
    int times = 0;
    for (QVector<cannonBall *>::iterator can = emptycannon.begin(); can != emptycannon.end();) {
        if (Warship->getRect().intersects((*can)->getRect())) {
            times++;
            Warship->declineHP((*can)->getHurt());
            emptycannon.erase(can);
            if (times == 3)
                break;

        } else
            can++;
    }
}

void fightScene::checkDeath() {
    int flag = 0;
    for (QVector<frontWarShip *>::iterator item = frontwarship.begin(); item != frontwarship.end();) {
        if ((*item)->getHpRate() == 0) {
            flag = 1;
            frontwarship.erase(item);
        } else
            item++;
    }
    if (flag) {
        if (frontwarship.empty()) {
            emit fail();
            return;
        }
        frontwarship[0]->setTarget(&target);
        for (int i = 1; i < frontwarship.size(); i++) {
            frontwarship[i]->setTarget(&(frontwarship[i - 1]->getlocation()));
        }
    }

}

