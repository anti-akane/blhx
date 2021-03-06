#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include<QPushButton>
#include<QPixmap>
#include<QEvent>
#include<QBitmap>
#include<QString>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QTimer>
#include<QApplication>
class skillButton:public QPushButton {
    Q_OBJECT
public:
    ~skillButton();

    skillButton(QWidget *parent = nullptr, QPixmap *pixmap = nullptr, QString type = "", int maxskillnumber = 0);

    void Unleash_skills();

    void mouseReleaseEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent*);

    void addSkillNumber();

    int getSkillNumber();

    int getmaxSkillNumber();

    int IsDown();

    void declineMaxSkill(int number);

    void declineSkill(int number);
private:
    int skillNumber;
    int maxSkillNubmer;
    int isDown;
    QString available_imagePath;
    QString unavailable_imagePath;
    signals:
            void skills();
};

#endif // GAMEBUTTON_H
