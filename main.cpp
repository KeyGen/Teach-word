#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем кодировку с которй будет работать программа (UTF-8)
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

    // Создаем наш класс (программу)
    MainWindow w;

    // Отображаем
    w.show();
    w.showSistemsTrey(); // Отображаем трей
    
    return a.exec();
}
