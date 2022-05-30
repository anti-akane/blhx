#include"skillButton.h"
#include"windows.h"
skillButton::skillButton(QWidget *parent,QPixmap *pixmap,QString type,int skillnumber):QPushButton(parent) {
    skillNumber = skillnumber;
    this->setFlat(true);
    this->setStyleSheet("border: 0px");
    resize(pixmap->size());
    setMask(QBitmap(pixmap->mask()));
    available_imagePath = "QPushButton{border-image: url(:/res/";
    available_imagePath += type;
    available_imagePath += "-available.png);};";
    unavailable_imagePath = "QPushButton{border-image: url(:/res/";
    unavailable_imagePath += type;
    unavailable_imagePath += "-unavailable.png);};";
    setStyleSheet(available_imagePath);
}

skillButton::~skillButton() {
}

void skillButton::mousePressEvent(QMouseEvent *) {
    Unleash_skills();
    setEnabled(false);
    QTimer::singleShot(1000, this, [=] {
        setEnabled(true);
    });

}

void skillButton::Unleash_skills() {

    if (skillNumber) {

        skillNumber--;
    }
    if (!skillNumber) {
        setStyleSheet(unavailable_imagePath);
    }
}

void skillButton::addSkillNumber()
{
    skillNumber++;
    setStyleSheet(available_imagePath);
}

