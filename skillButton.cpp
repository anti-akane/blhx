#include"skillButton.h"
#include"windows.h"
skillButton::skillButton(QWidget *parent,QPixmap *pixmap,QString type,int maxskillnumber):QPushButton(parent),maxSkillNubmer(maxskillnumber) {
    skillNumber = 0;
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
    setStyleSheet(unavailable_imagePath);
}

skillButton::~skillButton() {
}

void skillButton::mousePressEvent(QMouseEvent *) {
    Unleash_skills();
    setEnabled(false);
    QTimer::singleShot(500, this, [=] {
        setEnabled(true);
    });

}

void skillButton::Unleash_skills() {

    if (skillNumber) {

        skillNumber--;
        emit skills();
    }
    if (!skillNumber) {
        setStyleSheet(unavailable_imagePath);
    }
}

void skillButton::addSkillNumber()
{
    if(skillNumber<maxSkillNubmer)
    {skillNumber++;
    setStyleSheet(available_imagePath);}
}

int skillButton::getSkillNumber()
{
    return skillNumber;
}

int skillButton::getmaxSkillNumber()
{
    return maxSkillNubmer;
}



