#include"fightScene.h"
#include"math.h"
#include"quitMessageBox.h"
#include<QMessageBox>
#include <QtGlobal>
#include<QCoreApplication>
const double pi=acos(-1.0);

fightScene::fightScene(QWidget *parent):QWidget(parent)
{
    init();
}
void fightScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
        painter.drawPixmap(0,0,QPixmap(":/res/1200px-Bg_banama_1.png"));

    painter.drawPixmap(target.x(),target.y(),QPixmap(":/res/target.png"));
    for(int i=0;i<cannonball.size();i++)
    {
        painter.drawPixmap(cannonball[i]->getX(),cannonball[i]->getY(),*(cannonball[i]->getPixmap()));
    }
    QBrush green_brush(QColor("#33FF66"));
    QBrush balck_brush(QColor("#000000"));

    painter.drawPixmap(thirdship->getlocation().x()-thirdship->getTachie().width()/2,thirdship->getlocation().y()-thirdship->getTachie().height()/2,thirdship->getTachie());
    painter.setBrush(balck_brush);
    painter.drawRect(thirdship->getlocation().x()-50,thirdship->getlocation().y()-thirdship->getTachie().height()/2,
                     100,10);
    painter.setBrush(green_brush);
    painter.drawRect(thirdship->getlocation().x()-50,thirdship->getlocation().y()-thirdship->getTachie().height()/2,
                     100*thirdship->getHpRate(),10);

    painter.drawPixmap(secondship->getlocation().x()-secondship->getTachie().width()/2,secondship->getlocation().y()-secondship->getTachie().height()/2,secondship->getTachie());
    painter.setBrush(balck_brush);
    painter.drawRect(secondship->getlocation().x()-50,secondship->getlocation().y()-secondship->getTachie().height()/2,
                     100,10);
    painter.setBrush(green_brush);
    painter.drawRect(secondship->getlocation().x()-50,secondship->getlocation().y()-secondship->getTachie().height()/2,
                     100*secondship->getHpRate(),10);
    painter.drawPixmap(firstship->getlocation().x()-firstship->getTachie().width()/2,firstship->getlocation().y()-firstship->getTachie().height()/2,firstship->getTachie());
    painter.setBrush(balck_brush);
    painter.drawRect(firstship->getlocation().x()-50,firstship->getlocation().y()-firstship->getTachie().height()/2,
                     100,10);
    painter.setBrush(green_brush);
    painter.drawRect(firstship->getlocation().x()-50,firstship->getlocation().y()-firstship->getTachie().height()/2,
                     100*firstship->getHpRate(),10);

}
void fightScene::init(){
    target=QPoint(300,337);
    firstship=new frontWarShip(1000,1,1,10,40,100,1,QPixmap(":/res/Portland.png"),QPoint(300,337),&target);
    secondship=new frontWarShip(1000,1,1,8,30,1,1,QPixmap(":/res/Helena.png"),QPoint(300,337),&firstship->getlocation());
    thirdship=new frontWarShip(1000,1,1,6,25,1,1,QPixmap(":/res/Santiago.png"),QPoint(300,337),&secondship->getlocation());
    //三个技能按钮的初始化
    quitmessagebox=new quitMessageBox(this);
    QPixmap *plane=new QPixmap(":/res/feiji-available.png");
    QPixmap *torpedoes=new QPixmap(":/res/yvlei-available.png");
    QPixmap *navalgun=new QPixmap(":/res/jianpao-available.png");
    //设置按钮大小
    *plane=plane->scaled(100, 100, Qt::KeepAspectRatio);
    *torpedoes=torpedoes->scaled(100, 100, Qt::KeepAspectRatio);
    *navalgun=navalgun->scaled(100, 100, Qt::KeepAspectRatio);
    planeButton=new skillButton(this,plane,"feiji",3);
    planeButton->move(800,570);
    torpedoesButton=new skillButton(this,torpedoes,"yvlei",firstship->getTorpNumber()+secondship->getTorpNumber()+thirdship->getTorpNumber());
    torpedoesButton->move(950,570);
    navalgunButton=new skillButton(this,navalgun,"jianpao",2);
    navalgunButton->move(1100,570);

    updateTimer=new QTimer(this);
    if(!updateTimer->isActive())
        updateTimer->start(40);
    //自律按钮初始化
    operationbutton=new operationButton(this);
    autoOpTimer=0;
    //界面设置
    setFixedSize(1200,675);
    setWindowTitle("碧蓝航线");
    setWindowIcon(QIcon("://res/aa9jv-f80ap-001.ico"));
    //暂停键
    QPixmap *pausepix=new QPixmap(":/res/pause.png");
    pause=new QPushButton(this);
    pause->resize(pausepix->size());
    pause->move(1200-pausepix->width(),0);
    pause->setStyleSheet("QPushButton{border-image: url(:/res/pause.png);}");
    connect(pause,&QPushButton::pressed,this,&fightScene::callquitmessage);

    //角色初始化
    connect(torpedoesButton,&skillButton::skills,this,&fightScene::torp);

    delete plane;
    delete  torpedoes;
    delete  navalgun;
    delete pausepix;
    update();

}
void fightScene::callquitmessage(){
    updateTimer->stop();
    quitmessagebox->exec();
    updateTimer->start(40);
}
fightScene::~fightScene(){
    delete quitmessagebox;
    delete planeButton;
    delete torpedoesButton;
    delete navalgunButton;
    delete updateTimer;
    delete operationbutton;
    delete pause;
}
void fightScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()== Qt::Key_Escape)
    {
        callquitmessage();
    }

    if(!event->isAutoRepeat())
        pressedKeys.insert(event->key());
    if(!updateTimer->isActive())
        updateTimer->start(40);
}

void fightScene::keyReleaseEvent(QKeyEvent *event)
{

    if(!event->isAutoRepeat())
        pressedKeys.remove(event->key());

}
void fightScene::updatetarger(int x, int y)
{
    if(!operationbutton->getOpState())
        return;
    if(x<0)
        target.setX(0);
    else if(x>600)
        target.setX(600);
    else
        target.setX(x);
    if(y<0)
        target.setY(0);
    else if(y>675)
        target.setX(675);
    else
        target.setY(y);
}
void fightScene::playGame()
{
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000);
    connect(updateTimer,&QTimer::timeout,[=](){
        qApp->processEvents();
        keyPress();
        if(!updateTimer->isActive())
            updateTimer->start(40);
        if(!operationbutton->getOpState())
        {
            autoOpTimer++;
            static int a=120,b=280;
            if(!(autoOpTimer%40))
            {
                a=120+qrand()%100;
                b=280+qrand()%30;
            }

           QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,QPoint(0,0),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
           if(torpedoesButton->getSkillNumber())
            QApplication::postEvent(torpedoesButton,press);
            target.setX(300+a*cos(autoOpTimer/(150/pi)));
            target.setY(337+b*sin(autoOpTimer/(150/pi)));
            if(autoOpTimer>300)
                autoOpTimer=0;
        }
        firstship->move();
        secondship->move();
        thirdship->move();
        shoot();
        update();
    });
}
void fightScene::keyPress(){
    QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,QPoint(0,0),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
    if(pressedKeys.isEmpty()){
        updateTimer->stop();
        return;}

    for(int key:pressedKeys)
    { switch (key) {
            case Qt::Key_Q:
                QApplication::postEvent(operationbutton,press);
                break;
            case Qt::Key_E:
                QApplication::postEvent(planeButton,press);
                break;
            case Qt::Key_R:
                QApplication::postEvent(torpedoesButton,press);
                break;
            case Qt::Key_T:
                QApplication::postEvent(navalgunButton,press);
                break;
            case Qt::Key_W:
                updatetarger(target.x(),target.y()-12);
                break;
            case Qt::Key_S:
                updatetarger(target.x(),target.y()+12);
                break;
            case Qt::Key_A:
                updatetarger(target.x()-12,target.y());
                break;
            case Qt::Key_D:
                updatetarger(target.x()+12,target.y());
                break;
        }
    }
}

void fightScene::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {if(event->pos().x()<=600)
        {updatetarger(event->pos().x(),event->pos().y());
            if(!updateTimer->isActive())
                updateTimer->start(40);}}
}

void fightScene::shoot(){
    for(int i=0;i<cannonball.size();i++)
    {
        if(!cannonball[i]->check())
           {
            cannonball[i]=nullptr;
            delete cannonball[i];
            cannonball.erase(cannonball.begin()+i);
        }
        else
            cannonball[i]->move();

    }
    if(firstship->shoot())
    {
        cannonball.push_back( new cannonBall(firstship->getlocation().x(),firstship->getlocation().y()+10,1,-pi/9));
        cannonball.push_back( new cannonBall(firstship->getlocation().x(),firstship->getlocation().y()-10,1,-pi/9));
    }
    if(secondship->shoot())
    {
        cannonball.push_back( new cannonBall(secondship->getlocation().x(),secondship->getlocation().y()+10,1,pi/9));
        cannonball.push_back( new cannonBall(secondship->getlocation().x(),secondship->getlocation().y()-10,1,pi/9));
    }
    if(thirdship->shoot())
    {
        cannonball.push_back( new cannonBall(thirdship->getlocation().x(),thirdship->getlocation().y()+10,1,0));
        cannonball.push_back( new cannonBall(thirdship->getlocation().x(),thirdship->getlocation().y()-10,1,0));
    }
    if(firstship->checkTorp())
    {
        torpedoesButton->addSkillNumber();
        torplist.push_back(new cannonBall(0,0,100,0,firstship));
    }
}

void fightScene::closeEvent(QCloseEvent *)
{
    this->clearFocus();
    emit closeFight();
}

void fightScene::torp()
{
    if(torplist.empty())
        return;
    cannonBall *torp=torplist[0];
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),1,0,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),1,pi/18,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),1,2*pi/18,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),1,-pi/18,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),1,-2*pi/18,nullptr,":/res/torp.png"));
    torp->getparent()->declineTorpNumber();
    torplist.erase(torplist.begin());
}


