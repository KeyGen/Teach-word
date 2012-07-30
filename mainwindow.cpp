#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPalette>
#include <QRadioButton>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      settings("KeyGen","Learn-words")
{

    this->setWindowFlags(Qt::CustomizeWindowHint);  // Отключаем обводку

    this->setFixedSize(600,300);    // Фиксируем размер окна

    QDesktopWidget *desktop = QApplication::desktop();  // Определяем разрешение экрана

    this->move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2); // Распологаем MainWindow в ценре

    setRoundedCorners(20,20,20,20); // Вызываем функцию которая закруглит углы

    //////////////// Установки пременных по умолчанию
    timeShow = QTime(1,0,0);                     // Время отображения программы
    answerTrueGeneral = 15;              // При какой записи статистики слово считать выученным
    dicSave = "Biology (En-Ru)";                    // Название словоря загруженного в прошдый раз
    languageSave = "Russian";               // Выбранный язык в прошлый раз
    //////////////// Установки пременных по умолчанию the end

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

    actionTreySound->setCheckable(true);    // Разрешаем "галочку"
    actionTreySound->setChecked(true);

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
                            ///////////////////// The end ////////////////////
    //----------------------//////////////////////////////////////////////////----------------------/

    showmessage = new ShowMessage();           // Класс сообщения
    fixedChanges = false;                  // Фиксирует были или нет изменения в learn_word (Слова для обучения)

    oneRadioStr = "test one";                        // Текст на QRadioButton
    twoRadioStr = "test two";                        // Текст на QRadioButton
    threeRadioStr = "test three";                      // Текст на QRadioButton

    oneRadio = new QRadioButton(oneRadioStr,this);                     // При подсказке выбор варианта ответа
    twoRadio = new QRadioButton(twoRadioStr,this);                     // При подсказке выбор варианта ответа
    threeRadio = new QRadioButton(threeRadioStr,this);                   // При подсказке выбор варианта ответа

    oneRadio->setFixedWidth(320);
    twoRadio->setFixedWidth(320);
    threeRadio->setFixedWidth(320);

    oneRadio->move(this->width()/2-oneRadio->width()/2,125);
    twoRadio->move(this->width()/2-twoRadio->width()/2,150);
    threeRadio->move(this->width()/2-threeRadio->width()/2,175);

    QFont font;
    font.setPixelSize(18);

    oneRadio->setFont(font);
    twoRadio->setFont(font);
    threeRadio->setFont(font);

    // Показыват/скрывает QRadioButton
    setVisibleQRadioButton(false);

    transferWord->setOpenLinks(false); // запрет на открытие url в transferWord

    // phonon
    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(mediaObject, audioOutput);

    setupLanguageProgramm();        // Установка языка

    bootDictionary();
    connectObject();

    //DeleteSetting();

    ReadSetting();
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
    dir.rmdir("tempdir");  // Удаляем temp папку
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

    progressdownloaddic = new QProgressBar(this);  // Прогресс загрузки словоря
    progressdownloaddic->setMaximum(100);
    progressdownloaddic->setMinimum(0);
    progressdownloaddic->setGeometry(moveLautWordsInput + 200, 50, 225, 30); // Устанавливаем геометрию (положение/размер) обекта QComboBox
   // progressdownloaddic->setVisible(false);
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
    progressdownloaddic->move(moveLautWordsInput + 344, 50);       // Перемещаем обьект Прогресс загрузки словоря
}

// Показать/скрыть dicInput и dicInfo
void MainWindow::showObjectdicInputanddicInfo()
{
    if(dicInput->isVisible())
    {
        QApplication::processEvents(); // Обновим приложение

        dicInput->setVisible(false);
        dicInfo->setVisible(false);
        transferWord->setVisible(false);
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
    if(!dicInput->isVisible())
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
}

// Установка обьектов насторек qml
void MainWindow::SetupObjectSetup()
{
    // Точка отчета позиции обьектов для настроек из Qml
    moveObjectSetup = 600;

    setupTime = new QTimeEdit(this);
    setupTime->setMinimumTime(QTime(0,0,10));
    setupTime->setTime(timeShow);
    setupTime->setGeometry(moveObjectSetup, 0, 200, 30);
    setupTime->setVisible(false);

    setupSinBoxInputAmountCorrect = new QSpinBox(this);
    setupSinBoxInputAmountCorrect->setMinimum(5);
    setupSinBoxInputAmountCorrect->setValue(answerTrueGeneral);
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
    SaveSetting();
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

void MainWindow::temp(bool BL)
{
    progressdownloaddic->setVisible(BL);
}

// Чтение настроек
void MainWindow::ReadSetting()
{
    if(settings.value("/Settings/pos/x").toInt()!=0&&settings.value("/Settings/pos/y").toInt()!=0)
    this->move(settings.value("/Settings/pos/x").toInt(),settings.value("/Settings/pos/y").toInt());

    languageSave = settings.value("/Settings/language", languageSave).toString();
    dicSave = settings.value("/Settings/dictionary", dicSave).toString();
    answerTrueGeneral = settings.value("/Settings/answer", answerTrueGeneral).toInt();
    soundValue = settings.value("/Settings/soundValue", soundValue).toDouble();
    timeShow = settings.value("/Settings/timerShow", timeShow).toTime();


    QStringList key, value;
    key = settings.value("/Settings/statisticskey", key).toStringList();
    value = settings.value("/Settings/statisticsvalue", value).toStringList();

    // Чтение статистики
    if((!key.isEmpty())&&(!value.isEmpty()))
    {
        for(int i = 0; i<key.size(); i++)
        {
            statistics[key.at(i)] = value.at(i);
        }
    }

    // Установка словаря
    this->actionDict(dicSave);
    dicInput->setCurrentIndex(dicInput->findText(dicSave));

    downloadLanguageProgramm(languageSave);

    setupTime->setTime(timeShow);
    setupSinBoxInputAmountCorrect->setValue(answerTrueGeneral);
}

// Созранение настроек
void MainWindow::SaveSetting()
{
    settings.setValue("/Settings/pos/x" , this->pos().x());     // Позиция x
    settings.setValue("/Settings/pos/y" , this->pos().y());     // Позиция y

    settings.setValue("Settings/language", languageSave);       // Выбранный язык в прошлый раз
    settings.setValue("Settings/dictionary", dicSave);          // Название словоря загруженного в прошдый раз
    settings.setValue("Settings/answer", answerTrueGeneral);    // При какой записи статистики слово считать выученным
    settings.setValue("Settings/soundValue", soundValue);       // Сохраняет громкость звука
    settings.setValue("Settings/timerShow", timeShow);          // Время отображения программы

    // Запись статистики
    if(!statistics.isEmpty())
    {
        QStringList key, value;
        QMap<QString,QString>::iterator it = statistics.begin();

        for(; it != statistics.end(); ++it)
        {
            key << it.key();
            value << it.value();
        }

        settings.setValue("Settings/statisticskey", key);
        settings.setValue("Settings/statisticsvalue", value);
    }
}


// Удаление настроек
void MainWindow::DeleteSetting()
{
    settings.remove("/Settings/pos/x");
    settings.remove("/Settings/pos/y");

    settings.remove("Settings/language");       // Выбранный язык в прошлый раз
    settings.remove("Settings/dictionary");     // Название словоря загруженного в прошдый раз
    settings.remove("Settings/answer");         // При какой записи статистики слово считать выученным
    settings.remove("Settings/soundValue");     // Сохраняет громкость звука
    settings.remove("Settings/timerShow");      // Время отображения программы

    // Удаление статистики
    settings.remove("Settings/statisticskey");
    settings.remove("Settings/statisticsvalue");
}
