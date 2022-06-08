#include"fightScene.h"
#include"math.h"
#include"quitMessageBox.h"
#include<QMessageBox>
#include<QFont>
#include<QDebug>
#include <QtGlobal>
#include<QCoreApplication>
const double pi=acos(-1.0);

fightScene::fightScene(QWidget *parent):QWidget(parent)
{
    init();
}

void fightScene::drawfront(QPainter&painter,frontWarShip*WarShip,QBrush*black_brush,QBrush*green_brush)
{
    painter.drawPixmap(WarShip->getlocation().x()-WarShip->getTachie().width()/2,WarShip->getlocation().y()-WarShip->getTachie().height()/2,WarShip->getTachie());
    painter.setBrush(*black_brush);
    painter.drawRect(WarShip->getlocation().x()-40,WarShip->getlocation().y()-WarShip->getTachie().height()/2,
                     80,8);
    painter.setBrush(*green_brush);
    painter.drawRect(WarShip->getlocation().x()-40,WarShip->getlocation().y()-WarShip->getTachie().height()/2,
                     80*WarShip->getHpRate(),8);
}
void fightScene::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/res/1200px-Bg_banama_1.png"));

    painter.drawPixmap(target.x(),target.y(),QPixmap(":/res/target.png"));
    for(auto v:cannonball)
    {
        if(v->getAngle()>0)
        painter.drawPixmap(v->getX()+v->getH()*sin(v->getAngle())/2.0,v->getY()+v->getH()*cos(v->getAngle())/2.0,*(v->getPixmap()));
       else
        painter.drawPixmap(v->getX()+v->getH()*sin(v->getAngle())/2.0,v->getY()-v->getH()*cos(v->getAngle())/2.0,*(v->getPixmap()));
    }
    QBrush green_brush(QColor("#33FF66"));
    QBrush black_brush(QColor("#000000"));

    drawfront(painter,thirdship,&black_brush,&green_brush);
    drawfront(painter,secondship,&black_brush,&green_brush);
    drawfront(painter,firstship,&black_brush,&green_brush);
    for(int i=0;i<emptylist.size();i++)
    {
        painter.drawPixmap(emptylist[i]->getlocation().x(),emptylist[i]->getlocation().y(),emptylist[i]->getTachie());
        painter.setBrush(black_brush);
        painter.drawRect(emptylist[i]->getlocation().x()+40,emptylist[i]->getlocation().y(),
                         emptylist[i]->getTachie().width()*0.6,8);
        painter.setBrush(green_brush);
        painter.drawRect(emptylist[i]->getlocation().x()+40,emptylist[i]->getlocation().y(),
                         emptylist[i]->getTachie().width()*0.6*emptylist[i]->getHpRate(),8);
    }

    QFont font;
    font.setPointSize(20);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(950,570,QString::number(torpedoesButton->getSkillNumber())+"/"+QString::number(torpedoesButton->getmaxSkillNumber()));


}
void fightScene::init(){
    target=QPoint(300,337);
    firstship=new frontWarShip(1000,100,400,8,100,750,2,QPixmap(":/res/Portland.png"),QPoint(300,337),&target);
    secondship=new frontWarShip(1000,100,400,7,70,650,2,QPixmap(":/res/Helena.png"),QPoint(200,337),&firstship->getlocation());
    thirdship=new frontWarShip(1000,100,400,7,45,500,2,QPixmap(":/res/Santiago.png"),QPoint(100,337),&secondship->getlocation());
    emptylist.push_back(new emptyWarShip(10000,100,100,1,100,1000,QPixmap("://res/liangchan-1.png"),QPoint(900,200)));
    emptylist.push_back(new emptyWarShip(10000,100,100,1,100,1000,QPixmap("://res/liangchan-1.png"),QPoint(900,300)));
    emptylist.push_back(new emptyWarShip(10000,100,100,1,100,1000,QPixmap("://res/liangchan-1.png"),QPoint(900,400)));
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
        updateTimer->start(30);
    //自律按钮初始化
    operationbutton=new operationButton(this);
    autoOpTimer=0;
    autoState=0;
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
    updateTimer->start(30);
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
        updateTimer->start(30);
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
    if(x<10)
        target.setX(10);
    else if(x>600)
        target.setX(600);
    else
        target.setX(x);
    if(y<10)
        target.setY(10);
    else if(y>660)
        target.setY(660);
    else
        target.setY(y);
}
void fightScene::playGame()
{

    connect(updateTimer,&QTimer::timeout,[=](){


        qApp->processEvents();
        keyPress();
        if(!updateTimer->isActive())
            updateTimer->start(30);
        if(!operationbutton->getOpState())
        {
            autoOperate();
        }
        firstship->move();
        secondship->move();
        thirdship->move();
        shoot();
        collide();
        update();


    });
}
void fightScene::keyPress(){
    QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,QPoint(0,0),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
    if(pressedKeys.isEmpty()){
        updateTimer->stop();
        return;}
    int targetspeed=firstship->getSpeed()*1.2;
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
                updatetarger(target.x(),target.y()-targetspeed);
                break;
            case Qt::Key_S:
                updatetarger(target.x(),target.y()+targetspeed);
                break;
            case Qt::Key_A:
                updatetarger(target.x()-targetspeed,target.y());
                break;
            case Qt::Key_D:
                updatetarger(target.x()+targetspeed,target.y());
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
                updateTimer->start(30);}}
}

void fightScene::shoot(){

    for (QVector<cannonBall*>::iterator it = cannonball.begin(); it != cannonball.end();) {

        if(!((*it)->check()))
           {
            *it=nullptr;
           delete *it;
            cannonball.erase(it);
        }
        else
           { (*it)->move();
            it++;
        }
    }

    frontshoot(firstship);
    frontshoot(secondship);
    frontshoot(thirdship);
    if(firstship->checkTorp())
    {
        torpedoesButton->addSkillNumber();
        torplist.push_back(new cannonBall(0,0,100,0,firstship));
    }
    if(secondship->checkTorp())
    {
        torpedoesButton->addSkillNumber();
        torplist.push_back(new cannonBall(0,0,100,0,secondship));
    }
    if(thirdship->checkTorp())
    {
        torpedoesButton->addSkillNumber();
        torplist.push_back(new cannonBall(0,0,100,0,thirdship));
    }
}

void fightScene::frontshoot(frontWarShip*WarShip)
{
    //if(emptylist.empty())
        //return;
    if(WarShip->shoot())
    {
        int b_x=WarShip->getlocation().x(),b_y=WarShip->getlocation().y();
        QPoint *goal=nullptr;
        int len=1e8;
        for(auto v:emptylist)
        {
        int g_x=v->getlocation().x()+v->getwidth()/2,g_y=v->getlocation().y()+v->getheight()/2;
        int temp=(b_x-g_x)*(b_x-g_x)+(b_y-g_y)*(b_y-g_y);
        if(temp<len)
        {
            goal=new QPoint(g_x,g_y);
            len=temp;
        }

        }
        cannonball.push_back( new cannonBall(WarShip->getlocation().x(),WarShip->getlocation().y()+5,WarShip->power_hurt(),
                                             cal_angle(&WarShip->getlocation(),goal)));
        cannonball.push_back( new cannonBall(WarShip->getlocation().x(),WarShip->getlocation().y()-5,WarShip->power_hurt(),
                                             cal_angle(&WarShip->getlocation(),goal)));
        delete  goal;
    }


}

void fightScene::closeEvent(QCloseEvent *)
{
    this->clearFocus();
    emit closeFight();
    this->updateTimer->stop();
}

void fightScene::torp()
{
    if(torplist.empty())
        return;
    cannonBall *torp=torplist[0];
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),torp->getparent()->torp_hurt(),0,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),torp->getparent()->torp_hurt(),pi/30.0,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),torp->getparent()->torp_hurt(),-1.0*pi/30.0,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),torp->getparent()->torp_hurt(),pi/40.0,nullptr,":/res/torp.png"));
    cannonball.push_back(new cannonBall(torp->getparent()->getlocation().x(),torp->getparent()->getlocation().y(),torp->getparent()->torp_hurt(),-1.0*pi/40.0,nullptr,":/res/torp.png"));
    torp->getparent()->declineTorpNumber();
    torplist[0]=nullptr;
    torplist.erase(torplist.begin());
}

void fightScene::autoOperate()
{
    autoOpTimer++;
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000);
    int l_x = firstship->getlocation().x(), l_y = firstship->getlocation().y();
    int t_x = target.x(), t_y = target.y();
    double len = sqrt((l_x - t_x) * (l_x - t_x) + (l_y - t_y) * (l_y - t_y));
if(len<=3*firstship->getSpeed())
    {
       int tx,ty;
       autoOpTimer=0;
        tx=120+qrand()%400;
        ty=100+qrand()%500;

        target.setX(tx);
        target.setY(ty);
    }

    QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,QPoint(0,0),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
    if(torpedoesButton->getSkillNumber())
     QApplication::postEvent(torpedoesButton,press);
}

double fightScene::cal_angle(QPoint *begin, QPoint *goal)
{
    if(goal==nullptr)
        return 0;
    int b_x=begin->x(),b_y=begin->y();
    int g_x=goal->x(),g_y=goal->y();
    double xx = g_x - b_x;
    double yy = g_y - b_y;
   double tempAngle;
        if (xx == 0.0)
            tempAngle = pi / 2.0;
        else
            tempAngle = atan(fabs(yy / xx));

        if ((xx < 0.0) && (yy >= 0.0))
            tempAngle = pi - tempAngle;
        else if ((xx < 0.0) && (yy < 0.0))
            tempAngle = pi + tempAngle;
        else if ((xx >= 0.0) && (yy < 0.0))
            tempAngle = pi * 2.0 - tempAngle;

        return (tempAngle);
}

void fightScene::collide(){
    for (QVector<cannonBall*>::iterator can = cannonball.begin(); can != cannonball.end();) {
int flag1=0;
         for (QVector<emptyWarShip*>::iterator empty = emptylist.begin(); empty != emptylist.end();)
         {
             int flag2=0;
             if((*empty)->getRect().intersects((*can)->getRect()))
             {
                 flag1=1;
                 flag2=1;
                 (*empty)->declineHP((*can)->getHurt());
                 if((*empty)->getHpRate()==0)
                    emptylist.erase(empty);
                 qDebug()<<(*can)->getHurt()<<endl;

                 break;
             }
             if(!flag2)
                 empty++;
         }
         if(flag1)
             cannonball.erase(can);
         else
         can++;
    }
}

