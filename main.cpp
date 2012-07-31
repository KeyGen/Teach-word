#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);

    // Устанавливаем кодировку с которй будет работать программа (UTF-8)
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

    // Создаем наш класс (программу)
    MainWindow *appmain = new MainWindow();

    // Отображаем
    appmain->show();
    appmain->showSistemsTrey(); // Отображаем трей
    appmain->downloadoff();
    
    return app->exec();
}
