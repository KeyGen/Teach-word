#ifndef SHOWMESSAGE_H
#define SHOWMESSAGE_H

#include <QtGui/QMainWindow>

#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QDebug>

class ShowMessage : public QMainWindow
{
    Q_OBJECT

public:
    ShowMessage(QWidget *parent = 0);
    ~ShowMessage();

    void activationQml(QString text, QString button); // активация qml
    void setBackground(QPixmap);            // Установка фоновой картинки

    Q_INVOKABLE void move_window();             // Функция C++ вызываемая из QML премещающие окно
    Q_INVOKABLE void cursor_up();               // Функция C++ вызываемая из QML изменяющие вид курсора
    Q_INVOKABLE void cursor_down();             // Функция C++ вызываемая из QML возвращающия вид курсора в первоначальное состояние
    Q_INVOKABLE void quit();                    // Функция C++ вызываемая из QML для завершения работы приложения
    Q_INVOKABLE void setQmlWindowOpacity(double); // Функция C++ вызываемая из QML для управлением прозрачностью


signals:
    void signalMove(QPoint);


private:
    QDeclarativeView *uiShowMessage;               // Qml
    QObject *RootShowMessage;                      // Корневой элемент QML модели

    int save_x;                         // Сохраняет X положение MainWindow на экране
    int save_y;                         // Сохраняет Y положение MainWindow на экране

    void setRoundedCorners(int,int,int,int); // Функция закругляет углы MainWindow
};

#endif // SHOWMESSAGE_H
