#include"quitMessageBox.h"
#include<QPixmap>
#include<QColor>
quitMessageBox::quitMessageBox(QWidget *parent):QDialog(parent)
{
    update();
           QPixmap title(":/res/messagetitle.png");
           QPixmap cancel(":/res/cancel.png");
            QPixmap continuefight(":/res/continuefight.png");
             QPixmap quitfight(":/res/quitfight.png");
    this->resize(title.width()+cancel.width(),cancel.height()+continuefight.height()+100);
        //设置标题栏隐藏
          this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
          Title = new QLabel(this);
          Title->setPixmap(title);
         Title->setGeometry(0,0,title.width(),title.height());
         cancelButton=new QPushButton(this);
         cancelButton->resize(cancel.size());
         cancelButton->setStyleSheet("QPushButton{border-image: url(:/res/cancel.png);}");
         cancelButton->move(title.width(),0);
         continueButton=new QPushButton(this);
         continueButton->resize(continuefight.size());
         continueButton->setStyleSheet("QPushButton{border-image: url(:/res/continuefight.png);}");
         continueButton->move(continuefight.width()+300,cancel.height()+50);
         quitButton=new QPushButton(this);
         quitButton->resize(quitfight.size());
         quitButton->setStyleSheet("QPushButton{border-image: url(:/res/quitfight.png);}");
         quitButton->move(50,cancel.height()+50);
this->setStyleSheet("QDialog{background-color:rgb(148,162,189)}");
         QObject::connect(cancelButton,&QPushButton::pressed,this,&QDialog::close);
          QObject::connect(continueButton,&QPushButton::pressed,this,&QDialog::close);
                      QObject::connect(quitButton,&QPushButton::pressed,this,&QDialog::close);
           QObject::connect(quitButton,&QPushButton::pressed,parent,&QWidget::close);

}
quitMessageBox::~quitMessageBox()
{
    delete Title;
    delete cancelButton;
    delete continueButton;
    delete quitButton;
}

