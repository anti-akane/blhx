#ifndef QUITMESSAGEBOX_H
#define QUITMESSAGEBOX_H
#include<QMessageBox>
#include<QWidget>
#include<QPushButton>
#include<QDialog>
#include<QLabel>
#include<QPainter>
class quitMessageBox:public QDialog
{
    Q_OBJECT
public:
    ~quitMessageBox();
    quitMessageBox(QWidget *parent=nullptr);
private:
    QPushButton *cancelButton;
    QPushButton *continueButton;
    QPushButton *quitButton;
    QLabel *Title;

};

#endif // QUITMESSAGEBOX_H
