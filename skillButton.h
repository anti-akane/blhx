/* * * * * * * * * ** * * * * * * * * *
 * 技能按钮类
 * * * * * * * * * * * * * * * * * * * */
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
    //析构函数
    ~skillButton();
    //构造函数
    skillButton(QWidget *parent = nullptr, QPixmap *pixmap = nullptr, QString type = "", int maxskillnumber = 0);
    //封装的代表发动技能的函数
    void Unleash_skills();
    //鼠标松开事件（发动技能）
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标按压事件，在舰炮按钮中这会使得屏幕中出现准心
    void mousePressEvent(QMouseEvent*);
    //封装的增加现在技能数的函数
    void addSkillNumber();
    //返回当前技能数
    int getSkillNumber();
    //返回最大技能数
    int getmaxSkillNumber();
    //返回是否被按下
    int IsDown();
    //封装的减少最大技能数的语句，用于角色死亡时
    void declineMaxSkill(int number);
    //封装的减少当前技能数的语句，用于角色死亡时
    void declineSkill(int number);
private:
    int skillNumber;//当前技能数
    int maxSkillNubmer;//最大技能数
    int isDown;//为1代表其被按下
    QString available_imagePath;//按钮可用时的图片路径
    QString unavailable_imagePath;//按钮不可用是的图片路径
    signals:
            void skills();
};

#endif // GAMEBUTTON_H
