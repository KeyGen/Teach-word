#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPalette>
#include <QRadioButton>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);  // Отключаем обводку

    this->setFixedSize(600,300);    // Фиксируем размер окна

    QDesktopWidget *desktop = QApplication::desktop();  // Определяем разрешение экрана

    this->move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2); // Распологаем MainWindow в ценре

    setRoundedCorners(20,20,20,20); // Вызываем функцию которая закруглит углы

    //Включаем наш QML
    ui = new QDeclarativeView();
    ui->setSource(QUrl("qrc:/main.qml"));

    //Находим корневой элемент
    Root = ui->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент Qt_fun
    ui->rootContext()->setContextProperty("Qt_fun", this);

    this->setCentralWidget(ui); // Устанавливаем ui по центру

    SetupLautWordsInput(); // Установка обьектов для редактора уроков
    SetupObjectSetup();            // Установка обьектов насторек qml

//    QPixmap pix = QPixmap::grabWindow(QWidget::winId(uiShowMessage)); // скрин под программой
//    pix.save("kdjfk.png");

    //----------------------//////////////////////////////////////////////////----------------------//
                            ////////// Создаем иконку с меню в трее //////////

    // Создаем системный трей с иконкой
    systemTray = new QSystemTrayIcon(QIcon(":/picture/ico_main"),this);

    // Создаем меню для трея
    menuTrey = new QMenu;

    // Создаем актионы котрые пойдут в меню, а меню в системный трей

    actionTreyClose = new QAction("Выход", this);                   // Актион для выхода
    actionTreySound = new QAction("Звук", this);                    // Актион включает/выключает звук
    actionTreyHelp = new QAction("Справка", this);                  // Актион который открывает справку
    actionTreyInfo = new QAction("О программе", this);              // Актион открывающий диалог инфор. о программе
    actionTreySetting = new QAction("Настройки", this);             // Актион открывающий диалог настроек
    actionTreyShow = new QAction("Показать", this);                 // Актион отображающий программу
    actionTreyMask = new QAction("Скрыть программу", this);         // Актион прячет окно программы в трей

    // Вставляем иконки в актионы
    actionTreyClose->setIcon(QIcon(QPixmap(":/picture/quit")));         // Актион для выхода
    actionTreySound->setIcon(QIcon(QPixmap(":/picture/music")));        // Актион включает/выключает звук
    actionTreyHelp->setIcon(QIcon(QPixmap(":/picture/help")));          // Актион который открывает справку
    actionTreyInfo->setIcon(QIcon(QPixmap(":/picture/info")));          // Актион открывающий диалог инфор. о программе
    actionTreySetting->setIcon(QIcon(QPixmap(":/picture/setting")));    // Актион открывающий диалог настроек
    actionTreyShow->setIcon(QIcon(QPixmap(":/picture/up_arrow")));      // Актион отображающий программу
    actionTreyMask->setIcon(QIcon(QPixmap(":/picture/down")));          // Актион прячет окно программы в трей

    // Вставляем в меню актионы (от порядка добавления зависит расположение)
    menuTrey->addAction(actionTreySetting);
    menuTrey->addAction(actionTreySound);
    menuTrey->addSeparator();               // Разделитель
    menuTrey->addAction(actionTreyHelp);
    menuTrey->addAction(actionTreyInfo);
    menuTrey->addSeparator();               // Разделитель
    menuTrey->addAction(actionTreyShow);
    menuTrey->addAction(actionTreyMask);
    menuTrey->addSeparator();               // Разделитель
    menuTrey->addAction(actionTreyClose);

    // Вставляем меню в системный трей
    systemTray->setContextMenu(menuTrey);

    // Отображаем иконку в трее
    systemTray->show();
                            ///////////////////// The end ////////////////////
    //----------------------//////////////////////////////////////////////////----------------------/

    //qDebug() << bootDictionary();

    transferWord->setOpenLinks(false); // запрет на открытие url в transferWord

    connectObject();
    ReadSetting();

    showmessage = new ShowMessage();           // Класс сообщения
}

// Деструктор
MainWindow::~MainWindow()
{
    delete ui; // Удаляем обькт qml

    QDir dir("dic/tempdir");        // Создаем Qdir в папке tempdir

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks); // Устанавливаем фильтры

    QFileInfoList list = dir.entryInfoList(); // Чтение инфо о файлах

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        dir.remove(fileInfo.fileName());    // Удаляем файлы из папки tempdir
    }

    dir.cdUp(); // Выходим в папку dic
    qDebug() << dir.rmdir("tempdir");  // Удаляем temp папку
}

// Функция C++ вызываемая из QML вызывающая справку по адресу url
void MainWindow::openUrlHelp()
{
    QDesktopServices::openUrl(QUrl("http://www.cyberforum.ru/beta-testing/thread617608.html"));
}

// Установка обьектов для редактора уроков
void MainWindow::SetupLautWordsInput()
{
    moveLautWordsInput = 600;

    answerTrue = new QListWidget(this); // Создаем обект QListWidget
    answerTrue->setGeometry(moveLautWordsInput + 20, 50, 40, 185); // Устанавливаем геометрию (положение/размер) обекта QListWidget

    ListLearnWords = new QListWidget(this); // Создаем обект QListWidget
    ListLearnWords->setGeometry(moveLautWordsInput + 100, 50, 225, 185); // Устанавливаем геометрию (положение/размер) обекта QListWidget

    ListBase = new QListWidget(this); // Создаем обект QListWidget
    ListBase->setGeometry(moveLautWordsInput + 200, 50, 225, 155); // Устанавливаем геометрию (положение/размер) обекта QListWidget

    // Обьект QLineEdit предназначен для поиска слов по словарю
    findWord = new QLineEdit(this);
    findWord->setGeometry(moveLautWordsInput + 200, 50, 225, 30); // Устанавливаем геометрию (положение/размер) обекта QListWidget

    // Обьект QTextBrowser предназначен для отображения перевода слов
    transferWord = new QTextBrowser(this);
    transferWord->setGeometry(moveLautWordsInput + 200, 50, 225, 155); // Устанавливаем геометрию (положение/размер) обекта QTextBrowser
    transferWord->setVisible(false);

    dicInput = new QComboBox(this);                // Обьект QComboBox предназначен для выбора словаря
    dicInput->setGeometry(moveLautWordsInput + 200, 50, 225, 30); // Устанавливаем геометрию (положение/размер) обекта QComboBox
    dicInput->setVisible(false);

    dicInfo = new QTextBrowser(this);       // Обьект QTextBrowser предназначен для отображения свойств словаря
    dicInfo->setGeometry(moveLautWordsInput + 200, 50, 225, 155); // Устанавливаем геометрию (положение/размер) обекта QTextBrowser
    dicInfo->setVisible(false);
}

// Функция C++ вызываемая из QML для перемещания обьектов редактора уроков обучения
void MainWindow::moveInputWords(int moveInt)
{
    moveLautWordsInput = moveInt; // Приравниваем полученное число из qml к нашей точки отчета позиции

    answerTrue->move(moveLautWordsInput + 30, 50);      // Перемещаем обьект
    ListLearnWords->move(moveLautWordsInput + 77, 50);  // Перемещаем обьект
    ListBase->move(moveLautWordsInput + 344, 80);       // Перемещаем обьект

    findWord->move(moveLautWordsInput + 344, 50);  // Перемещаем обьект
    transferWord->move(moveLautWordsInput + 344, 80);       // Перемещаем обьект

    dicInput->move(moveLautWordsInput + 344, 50);  // Перемещаем обьект
    dicInfo->move(moveLautWordsInput + 344, 80);       // Перемещаем обьект
}

// Показать/скрыть dicInput и dicInfo
void MainWindow::showObjectdicInputanddicInfo()
{
    if(dicInput->isVisible())
    {
        dicInput->setVisible(false);
        dicInfo->setVisible(false);
    }
    else
    {
        dicInput->setVisible(true);
        dicInfo->setVisible(true);
    }
}

// Показывает/скрывает findWord transferWord
void MainWindow::setVisibleObjectLernWord()
{
    if(ListBase->isVisible())
    {
        ListBase->setVisible(false);
        transferWord->setVisible(true);
    }
    else
    {
        ListBase->setVisible(true);
        transferWord->setVisible(false);
    }
}

// Установка обьектов насторек qml
void MainWindow::SetupObjectSetup()
{
    // Точка отчета позиции обьектов для настроек из Qml
    moveObjectSetup = 600;

    setupTime = new QTimeEdit(this);
    setupTime->setGeometry(moveObjectSetup, 0, 200, 30);
    setupTime->setVisible(false);

    setupSinBoxInputAmountCorrect = new QSpinBox(this);
    setupSinBoxInputAmountCorrect->setGeometry(moveObjectSetup, 0, 200, 30);
    setupSinBoxInputAmountCorrect->setVisible(false);

    setupLanguageComboBox = new QComboBox(this);
    setupLanguageComboBox->setGeometry(moveObjectSetup, 0, 200, 30);
    setupLanguageComboBox->setVisible(true);

    setupVolume = new Phonon::VolumeSlider(this);
    setupVolume->setGeometry(moveObjectSetup, 0, 200, 30);
    setupVolume->setVisible(false);

    setupUpdate = new QPushButton("Проверить обновления", this);
    setupUpdate->setGeometry(moveObjectSetup,0,200,30);
    setupUpdate->setVisible(false);
}

// Функция C++ вызываемая из QML для перемещания обьектов настроек
void MainWindow::moveSetup(int moveInt)
{
    // Точка отчета позиции обьектов для настроек из Qml
    moveObjectSetup = moveInt;

    setupTime->move(moveObjectSetup + 35, 135);

    setupSinBoxInputAmountCorrect->move(moveObjectSetup + 35, 135);

    setupLanguageComboBox->move(moveObjectSetup + 35, 135);

    setupVolume->move(moveObjectSetup + 35, 138);

    setupUpdate->move(moveObjectSetup + 35, 138);
}

// Показать/скрыть setupLanguageComboBox
void MainWindow::setVisibleObjectsetupLanguageComboBox(bool BL)
{
    setupLanguageComboBox->setVisible(BL);
}

// Показать/скрыть setupTime
void MainWindow::setVisibleObjectsetupTime(bool BL)
{
    setupTime->setVisible(BL);
}

// Показать/скрыть setupSinBoxInputAmountCorrect
void MainWindow::setVisibleObjectsetupSinBoxInputAmountCorrect(bool BL)
{
    setupSinBoxInputAmountCorrect->setVisible(BL);
}

// Показать/скрыть setupVolume
void MainWindow::setVisibleObjectsetupVolume(bool BL)
{
    setupVolume->setVisible(BL);
}

// Показать/скрыть setupUpdate
void MainWindow::setVisibleObjectsetupUpdate(bool BL)
{
    setupUpdate->setVisible(BL);
}

// Функция C++ вызываемая из QML для завершения работы приложения
void MainWindow::quit()
{
    this->close(); // Завершает выполнение программы
    showmessage->close();
}

// Функция закругляет углы MainWindow
void MainWindow::setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br)
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

//Функция C++ вызываемая из QML изменяющие курсор
void MainWindow::cursor_down()
{
    this->setCursor(QCursor(Qt::ArrowCursor));  // Востанавливает нормальный вид курсора
}

//Функция C++ вызываемая из QML изменяющие курсор
void MainWindow::cursor_up()
{
    this->setCursor(QCursor(Qt::SizeAllCursor));    // Изменяет вид курсора при клике на обьект

    save_x = QCursor::pos().x() - this->pos().x();
    save_y = QCursor::pos().y() - this->pos().y();
}

//Функция C++ вызываемая из QML премещающие окно
void MainWindow::move_window()
{
    // Перемещаем окно
    this->move(QCursor::pos().x()-save_x , QCursor::pos().y() - save_y);
    showmessage->move(QCursor::pos().x()-save_x , QCursor::pos().y() - save_y);
}

// Функция C++ вызываемая из QML для скрытия MainWindow
void MainWindow::maskProgramm()
{
    this->setVisible(false);    // Прячет MainWindow
}

// Вызывает WainWindow при клике на иконку в трее
void MainWindow::treyProgrammShow(QSystemTrayIcon::ActivationReason temp)
{
    if(temp == QSystemTrayIcon::Trigger)    // При одинарном клики на иконку в трее
    {
        if(!this->isVisible())      // если скрыта программа
        {
            this->setVisible(true); // отображает
        }
    }
}

// Установка слов в qml / проверка правильности введенного ответа
bool MainWindow::inputShowWords(QString str, QString strinput)
{
    if(str == strinput)
        return true;
    else
        return false;
}
