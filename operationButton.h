#ifndef SKILLBUTTON_H
#define SKILLBUTTON_H
#include<QPushButton>
#include<QPixmap>
#include<QEvent>
#include<QBitmap>
#include<QString>
#include<QMouseEvent>
class operationButton:public QPushButton{
    Q_OBJECT
public:
    operationButton(QWidget *parent=nullptr);
    bool getOpState()const;
~operationButton();
signals:

private:
  bool operatingState;
  QString type;
  void mousePressEvent(QMouseEvent *event);
};
#endif // SKILLBUTTON_H
