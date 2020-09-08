#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QMediaPlayer>
#include <QDir>
#include <QMediaplayList>
#include <QMediaplayer>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
