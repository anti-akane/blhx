#include "mainwindow.h"
#include"fightScene.h"
#include <QApplication>
#include"gameScene.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    gameScene w;
    w.upgateGame();
    w.show();
    return a.exec();
}
