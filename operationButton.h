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
    operationButton(QWidget *parent = nullptr);

    bool getOpState() const;

    ~operationButton();

    void mousePressEvent(QMouseEvent *event);

private:
    bool operatingState;
    QString type;
};
#endif // SKILLBUTTON_H
