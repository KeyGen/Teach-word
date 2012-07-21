#include "showmessage.h"
#include <QDesktopWidget>
#include <QApplication>

ShowMessage::ShowMessage(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);  // Отключаем обводку

    this->setFixedSize(600,300);    // Фиксируем размер окна

    QDesktopWidget *desktop = QApplication::desktop();  // Определяем разрешение экрана

    this->move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2); // Распологаем MainWindow в ценре

    setRoundedCorners(20,20,20,20); // Вызываем функцию которая закруглит углы

    //Включаем наш QML
    uiShowMessage = new QDeclarativeView(this);
    uiShowMessage->setSource(QUrl("qrc:/ShowMessage.qml"));

    //Находим корневой элемент
    RootShowMessage = uiShowMessage->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент Qt_fun
    uiShowMessage->rootContext()->setContextProperty("Qt_fun", this);
}

// Деструктор
ShowMessage::~ShowMessage()
{

}

// Функция закругляет углы MainWindow
void ShowMessage::setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br)
{
    QRegion region(0, 0, width(), height(), QRegion::Rectangle);

    // top left
    QRegion round (0, 0, 2*radius_tl, 2*radius_tl, QRegion::Ellipse);
    QRegion corner(0, 0, radius_tl, radius_tl, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // top right
    round = QRegion(width()-2*radius_tr, 0, 2*radius_tr, 2*radius_tr, QRegion::Ellipse);
    corner = QRegion(width()-radius_tr, 0, radius_tr, radius_tr, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // bottom right
    round = QRegion(width()-2*radius_br, height()-2*radius_br, 2*radius_br, 2*radius_br, QRegion::Ellipse);
    corner = QRegion(width()-radius_br, height()-radius_br, radius_br, radius_br, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    // bottom left
    round = QRegion(0, height()-2*radius_bl, 2*radius_bl, 2*radius_bl, QRegion::Ellipse);
    corner = QRegion(0, height()-radius_bl, radius_bl, radius_bl, QRegion::Rectangle);
    region = region.subtracted(corner.subtracted(round));

    setMask(region);
}

// активация qml
void ShowMessage::activationQml(QString text, QString button)
{
    // Достум из С++ к qml
    QObject *rect = RootShowMessage->findChild<QObject*>("recOne");
    rect->setProperty("state", "normal");

    rect = RootShowMessage->findChild<QObject*>("recTwo");
    rect->setProperty("state", "normal");

    rect = RootShowMessage->findChild<QObject*>("recThree");
    rect->setProperty("state", "normal");

    rect = RootShowMessage->findChild<QObject*>("recFour");
    rect->setProperty("state", "normal");

    rect = RootShowMessage->findChild<QObject*>("massegeBackground");
    rect->setProperty("opacity", "0.7");

    rect = RootShowMessage->findChild<QObject*>("messageText");
    rect->setProperty("text", "<center>" + text + "</center>");

    rect = RootShowMessage->findChild<QObject*>("timerMessage");
    rect->setProperty("running", "true");

    if(button == "true")
    {
        rect = RootShowMessage->findChild<QObject*>("no");
        rect->setProperty("opacity", "0.0");
    }
    else if(button == "false")
    {
        rect = RootShowMessage->findChild<QObject*>("yes");
        rect->setProperty("opacity", "0.0");

        rect = RootShowMessage->findChild<QObject*>("no");
        rect->setProperty("x", "155");
    }
    else if(button == "true, false")
    {
        rect = RootShowMessage->findChild<QObject*>("yes");
        rect->setProperty("x", "155");

        rect = RootShowMessage->findChild<QObject*>("no");
        rect->setProperty("x", "110");
    }
    else if(button == "test")
    {
        qDebug() << "test";
    }
}

//Функция C++ вызываемая из QML изменяющие курсор
void ShowMessage::cursor_down()
{
    this->setCursor(QCursor(Qt::ArrowCursor));  // Востанавливает нормальный вид курсора
}

//Функция C++ вызываемая из QML изменяющие курсор
void ShowMessage::cursor_up()
{
    this->setCursor(QCursor(Qt::SizeAllCursor));    // Изменяет вид курсора при клике на обьект

    save_x = QCursor::pos().x() - this->pos().x();
    save_y = QCursor::pos().y() - this->pos().y();
}

//Функция C++ вызываемая из QML премещающие окно
void ShowMessage::move_window()
{
    // Перемещаем окно
    this->move(QCursor::pos().x()-save_x , QCursor::pos().y() - save_y);

    emit signalMove(QPoint(QCursor::pos().x()-save_x , QCursor::pos().y() - save_y));
}

// Функция C++ вызываемая из QML для завершения работы приложения
void ShowMessage::quit()
{
    this->close();
}

// Функция C++ вызываемая из QML для управлением прозрачностью
void ShowMessage::setQmlWindowOpacity(double dou)
{
    this->setWindowOpacity(dou);
}

// Установка фоновой картинки
void ShowMessage::setBackground(QPixmap px)
{
    uiShowMessage->setBackgroundBrush(QBrush(px));
    //px.save("save.png");
}
