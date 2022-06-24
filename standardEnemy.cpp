#include"standardEnemy.h"
void standardEnemy::move() {
    moveclock++;
    //移动逻辑为定向定速移动
    if (moveclock >= movecd) {
        location.setX(location.x() - speed);
        getRect().moveTo(location.x() + width / 8, location.y() + height / 3);
        moveclock = 0;
    }

}
standardEnemy::standardEnemy(int HP,int power,int torp,int speed,int movecd,int shootcd,int torpcd,QPixmap Tachie,QPoint location)
    :enemyWarShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location),movecd(movecd) {
    moveclock = 0;
}
