#include"operationButton.h"
#include<QTimer>
operationButton::operationButton(QWidget *parent):QPushButton(parent)
{
    operatingState=true;
    setFlat(true);
    this->setStyleSheet("border: 0px");
    setStyleSheet("QPushButton{border-image: url(:/res/manual-operation.png);}");
    resize(240,60);
};
operationButton::~operationButton(){
}
void operationButton::mousePressEvent( QMouseEvent * event )
{
    setEnabled(false);
    QTimer::singleShot(1000, this, [=] {
    setEnabled(true);
    });
    if (event->button() == Qt::LeftButton)
    {
        if(operatingState)
         {
            setStyleSheet("QPushButton{border-image: url(:/res/manual-operation.png);}");
            operatingState=false;
        }
        else
         {
            setStyleSheet("QPushButton{border-image: url(:/res/auto-operate.png);}");
                        operatingState=true;
        }
    }
}
bool operationButton::getOpState() const{

    return operatingState;
}


