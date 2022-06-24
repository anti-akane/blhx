/* * * * * * * * * ** * * * * * * * * *
 * 退出消息框类
 * 退出战斗界面或关卡界面的提示框
 * * * * * * * * * * * * * * * * * * * */
#ifndef QUITMESSAGEBOX_H
#define QUITMESSAGEBOX_H
#include<QMessageBox>
#include<QWidget>
#include<QPushButton>
#include<QDialog>
#include<QLabel>
#include<QPainter>
class quitMessageBox:public QDialog {
    Q_OBJECT
public:
    //析构函数
    ~quitMessageBox();
    //构造函数
    quitMessageBox(QWidget *parent = nullptr);

private:
    QPushButton *cancelButton;//退出消息框按钮
    QPushButton *continueButton;//继续战斗按钮
    QPushButton *quitButton;//退出界面按钮
    QLabel *Title;//标题行

};

#endif // QUITMESSAGEBOX_H
