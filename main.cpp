#include "mainwindow.h"
#include"fightScene.h"
#include <QApplication>
#include"startScene.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    startScene w(nullptr);
    w.show();
    return a.exec();
}
