#include "mainwindow.h"
//#include <QBrush>
#include <QApplication>
#include <QDesktopWidget>
#include <QPalette>
#include <QLabel>
#include <QBitmap>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(Qt::CustomizeWindowHint); // Отключаем обводку

    this->setFixedSize(600,300);

    // Определяем разрешение экрана
    QDesktopWidget *desktop = QApplication::desktop();

    // Распологаем MainWindow в ценре
    this->move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);

    setRoundedCorners(20,20,20,20);

    learn_word << "hello" << "int" << "big" << "smoll" << "smooth" << "teach" << "learn" << "words";

    //Включаем наш QML Background_qml
    ui = new QDeclarativeView(this);
    ui->setSource(QUrl("qrc:/main.qml"));

    ui->setAutoFillBackground(true);
    ui->setBackgroundRole(QPalette::Window);


    //Находим корневой элемент
    Root = ui->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент Qt_fun
    ui->rootContext()->setContextProperty("Qt_fun", this);

    this->setCentralWidget(ui);

    //----------------------//////////////////////////////////////////////////----------------------//
                            ////////// Создаем иконку с меню в трее //////////

    // Создаем системный трей с иконкой
    systemTray = new QSystemTrayIcon(QIcon(":/picture/ico_main"),this);

    // Создаем меню для трея
    menuTrey = new QMenu;

    // Создаем актионы котрые пойдут в меню, а меню в системный трей

    actionTreyClose = new QAction("Выход", this);                   // Актион для выхода
    actionTreyEdit = new QAction("Музыка", this);
    actionTreyHelp = new QAction("Справка", this);                  // Актион который открывает справку
    actionTreyInfo = new QAction("О программе", this);              // Актион открывающий диалог инфор. о программе
    actionTreySetting = new QAction("Настройки", this);             // Актион открывающий диалог настроек
    actionTreyStyle = new QAction("Показать", this);
    actionTreyMask = new QAction("Скрыть программу", this);         // Актион прячет окно программы в трей

    // Вставляем иконки в актионы
    actionTreyClose->setIcon(QIcon(QPixmap(":/picture/quit")));      // Актион для выхода
    actionTreyEdit->setIcon(QIcon(QPixmap(":/picture/music")));
    actionTreyHelp->setIcon(QIcon(QPixmap(":/picture/help")));       // Актион который открывает справку
    actionTreyInfo->setIcon(QIcon(QPixmap(":/picture/info")));       // Актион открывающий диалог инфор. о программе
    actionTreySetting->setIcon(QIcon(QPixmap(":/picture/setting"))); // Актион открывающий диалог настроек
    actionTreyStyle->setIcon(QIcon(QPixmap(":/picture/up_arrow")));
    actionTreyMask->setIcon(QIcon(QPixmap(":/picture/down")));       // Актион прячет окно программы в трей

    // Вставляем в меню актионы (от порядка добавления зависит расположение)
    menuTrey->addAction(actionTreyEdit);
    menuTrey->addAction(actionTreySetting);
    menuTrey->addAction(actionTreyStyle);
    menuTrey->addAction(actionTreyHelp);
    menuTrey->addAction(actionTreyInfo);
    menuTrey->addSeparator();               // Разделитель
    menuTrey->addAction(actionTreyMask);
    menuTrey->addAction(actionTreyClose);

    // Вставляем меню в системный трей
    systemTray->setContextMenu(menuTrey);

    // Подключаем актоны к слотам подготовленых для них
    connect(systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(treyProgrammShow(QSystemTrayIcon::ActivationReason)));
//    connect(actionTreyEdit,SIGNAL(triggered()),this,SLOT(treyEdit()));
//    connect(actionTreySetting,SIGNAL(triggered()),this,SLOT(treySetting()));
//    connect(actionTreyStyle,SIGNAL(triggered()),this,SLOT(treyStyle()));
//    connect(actionTreyHelp,SIGNAL(triggered()),this,SLOT(tryeHelp()));
//    connect(actionTreyInfo,SIGNAL(triggered()),this,SLOT(treyInfo()));
//    connect(actionTreyMask,SIGNAL(triggered()),this,SLOT(treyMask()));
//    connect(actionTreyClose,SIGNAL(triggered()),this,SLOT(close()));

    // Отображаем иконку в трее
    systemTray->show();
                            ///////////////////// The end ////////////////////
    //----------------------//////////////////////////////////////////////////----------------------/

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функция C++ вызываемая из QML для завершения работы приложения
void MainWindow::quit()
{
    this->close();
}

void MainWindow::setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br) {
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

//Функция C++ вызываемая из QML изменяющие курсор
void MainWindow::cursor_down()
{
   this->setCursor(QCursor(Qt::ArrowCursor));
    BL_move = true;
}

//Функция C++ вызываемая из QML изменяющие курсор
void MainWindow::cursor_up()
{
    this->setCursor(QCursor(Qt::SizeAllCursor));
}

//Функция C++ вызываемая из QML премещающие окно
void MainWindow::move_window()
{
    if(BL_move)
    {
        save_x = QCursor::pos().x() - this->pos().x();
        save_y = QCursor::pos().y() - this->pos().y();

        this->setCursor(QCursor(Qt::SizeAllCursor));
    }

    if(BL_move)
        BL_move = false;

    this->move(QCursor::pos().x()-save_x , QCursor::pos().y() - save_y);
}

// Функция C++ вызываемая из QML для скрытия MainWindow
void MainWindow::maskProgramm()
{
    this->setVisible(false);
}

// Вызывает WainWindow при клике на иконку в трее
void MainWindow::treyProgrammShow(QSystemTrayIcon::ActivationReason temp)
{
    if(temp == QSystemTrayIcon::Trigger)
    {
        if(!this->isVisible())
        {
            this->setVisible(true);
        }
    }
}
