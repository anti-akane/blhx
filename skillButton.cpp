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
    isDown = 0;
}

skillButton::~skillButton() {
}

void skillButton::mouseReleaseEvent(QMouseEvent *) {
    Unleash_skills();
    setEnabled(false);
    isDown = 1;
    QTimer::singleShot(500, this, [=] {
        setEnabled(true);
        isDown = 0;
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


int skillButton::IsDown() {
    return isDown;
}


void skillButton::mousePressEvent(QMouseEvent*)
{
    isDown=1;
}

void skillButton::declineMaxSkill(int number)
{
    maxSkillNubmer-=number;
}

void skillButton::declineSkill(int number)
{
    skillNumber-=number;
}
