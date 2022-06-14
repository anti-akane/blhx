#include"standardEmpty.h"
void standardEmpty::move() {
    moveclock++;
    if (moveclock >= movecd) {
        location.setX(location.x() - speed);
        getRect().moveTo(location.x() + width / 8, location.y() + height / 3);
        moveclock = 0;
    }

}
standardEmpty::standardEmpty(int HP,int power,int torp,int speed,int movecd,int shootcd,int torpcd,QPixmap Tachie,QPoint location)
    :emptyWarShip(HP,power,torp,speed,shootcd,torpcd,Tachie,location),movecd(movecd) {
    moveclock = 0;
}
