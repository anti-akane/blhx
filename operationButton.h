/* * * * * * * * * ** * * * * * * * * *
 * 操作按钮类
 * 实现切换操作状态
 * * * * * * * * * * * * * * * * * * * */
#ifndef SKILLBUTTON_H
#define SKILLBUTTON_H
#include<QPushButton>
#include<QPixmap>
#include<QEvent>
#include<QBitmap>
#include<QString>
#include<QMouseEvent>
class operationButton:public QPushButton {
    Q_OBJECT
public:
    //初始化函数
    operationButton(QWidget *parent = nullptr);
    //返回操作状态
    bool getOpState() const;
    //析构函数
    ~operationButton();
    //鼠标按钮时间（切换操作状态）
    void mousePressEvent(QMouseEvent *event);

private:
    bool operatingState;//操作状态，为true时代表手动操作，反之为自动操作
    QString type;//判断此时按钮图片类型
};
#endif // SKILLBUTTON_H
