#include"humanoidEnemy.h"
void humanoidEnemy::move() {
    moveclock++;
    if (moveclock >= 2) {
        moveclock = 0;
        return;
    }

    int l_x = location.x(), l_y = location.y();
    int t_x = target->x(), t_y = target->y();
    double len = sqrt((l_x - t_x) * (l_x - t_x) + (l_y - t_y) * (l_y - t_y));
    if (len <= speed) {
        target->setX(700 + qrand() % 200);
        target->setY(200 + qrand() % 200);
    } else {
        location.setX(l_x + speed * (t_x - l_x) / len);
        location.setY(l_y + speed * (t_y - l_y) / len);
        getRect().moveTo(location.x() + Tachie.width() / 8, location.y() + Tachie.height() / 3);
    }

}

humanoidEnemy::humanoidEnemy(int HP,int power,int torp,int speed,int shootcd,int torpcd,QPixmap Tachie,QPoint location)
    :enemyWarShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location) {
    (this->Tachie) = Tachie.scaled(150, 150, Qt::KeepAspectRatio);
    getRect().setWidth(Tachie.width() * 3 / 4);
    getRect().setHeight(Tachie.height() * 2 / 3);
    height = Tachie.height();
    width = Tachie.width();
    getRect().moveTo(location.x() + width / 8, location.y() + height / 3);
    target = new QPoint(this->location);
    moveclock = 0;
    torpclock = 0;
}

bool humanoidEnemy::shoot() {
    shootclock++;
    if (shootclock % shootcd == 0) {
        return 1;
    } else if (shootclock % (shootcd + 3) == 0) {
        return 1;
    } else if (shootclock % (shootcd + 6) == 0) {
        shootclock = 0;
        return 1;
    }
    return 0;
}

bool humanoidEnemy::check_torp() {
    torpclock++;
    if (torpclock >= torpcd) {
        torpclock = 0;
        return 1;
    } else
        return 0;
}

humanoidEnemy::~humanoidEnemy() {
this->target=nullptr;
    delete this->target;
}


