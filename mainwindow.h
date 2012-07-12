#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <QSystemTrayIcon>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QDebug>
#include <math.h>
#include <QSystemTrayIcon>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Q_INVOKABLE void quit();    // Функция C++ вызываемая из QML для завершения работы приложения
    Q_INVOKABLE void move_window();             // Функция C++ вызываемая из QML премещающие окно
    Q_INVOKABLE void cursor_up();               // Функция C++ вызываемая из QML изменяющие вид курсора
    Q_INVOKABLE void cursor_down();             // Функция C++ вызываемая из QML возвращающия вид курсора в первоначальное состояние

    Q_INVOKABLE void maskProgramm();            // Функция C++ вызываемая из QML для скрытия MainWindow

private slots:
    void treyProgrammShow(QSystemTrayIcon::ActivationReason); // Вызывает WainWindow при клике на иконку в трее

private:
    QDeclarativeView *ui;// Qml
    QObject *Root;    // Корневой элемент QML модели

    QPixmap screenshot;
    QPalette *palletteScreen;

    bool BL_move;                       // Нужна для правильного перемещения мышкой MainWindow
    int save_x;                         // Сохраняет X положение MainWindow на экране
    int save_y;                         // Сохраняет Y положение MainWindow на экране
    QStringList learn_word;             // Слова для обучения

    void setRoundedCorners(int,int,int,int);

    QSystemTrayIcon *systemTray;        // Трей
    QMenu *menuTrey;                    // Меню для трея
    QAction *actionTreyClose;           // Актион выхода
    QAction *actionTreyEdit;            // Актион включающий dialog_input
    QAction *actionTreyHelp;            // Справка (пока справку не родил еще)
    QAction *actionTreyInfo;            // Актион включающий dialog_info
    QAction *actionTreySetting;         // Актион включающий dialog_setting
    QAction *actionTreyStyle;           // Актион включающий dialog_style
    QAction *actionTreyMask;            // Актион скрывающий MainWindow
};

#endif // MAINWINDOW_H
