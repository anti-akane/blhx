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

    void mousePressEvent(QMouseEvent *event);

    void addSkillNumber();
private:
    int skillNumber;
    int maxSkillNubmer;

    QString available_imagePath;
    QString unavailable_imagePath;
signals:
    void skills();
};

#endif // GAMEBUTTON_H
