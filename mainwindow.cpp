#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_input_word_ui.h"
#include "ui_setting_programm_ui.h"
#include <QMessageBox>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ui_input(new Ui::Input_word), ui_setting(new Ui::Setting_programm), settings("KeyGen","Teach_eng")
{
    ui->setupUi(this);
    // Отключаем обводку
    this->setWindowFlags(Qt::CustomizeWindowHint);

    installQml();

    dialog_input = new QDialog(this);
    ui_input->setupUi(dialog_input);

    dialog_setting = new QDialog(this);
    ui_setting->setupUi(dialog_setting);

    ////////////////////// Создаем трей
    systemTray = new QSystemTrayIcon(QIcon(":/icon/icon_trey"),this);

    // Создаем меню
    menuTrey = new QMenu;

    // Создаем актионы
    actionTreyClose = new QAction("Выход", this);
    actionTreyEdit = new QAction("Редактор словоря", this);
    actionTreyHelp = new QAction("Справка", this);
    actionTreyInfo = new QAction("О программе", this);
    actionTreySetting = new QAction("Настройки", this);
    actionTreyStyle = new QAction("Выбор стиля", this);
    actionTreyMask = new QAction("Скрыть программу", this);

    // Вставляем иконки в актионы
    actionTreyClose->setIcon(QIcon(QPixmap(":/icon/exit")));
    actionTreyEdit->setIcon(QIcon(QPixmap(":/icon/edit")));
    actionTreyHelp->setIcon(QIcon(QPixmap(":/icon/help")));
    actionTreyInfo->setIcon(QIcon(QPixmap(":/icon/info")));
    actionTreySetting->setIcon(QIcon(QPixmap(":/icon/setting")));
    actionTreyStyle->setIcon(QIcon(QPixmap(":/icon/style")));
    actionTreyMask->setIcon(QIcon(QPixmap(":/icon/mask")));

    // Вставляем в меню актионы

    menuTrey->addAction(actionTreyEdit);
    menuTrey->addAction(actionTreySetting);
    menuTrey->addAction(actionTreyStyle);
    menuTrey->addAction(actionTreyHelp);
    menuTrey->addAction(actionTreyInfo);
    menuTrey->addSeparator();
    menuTrey->addAction(actionTreyMask);
    menuTrey->addAction(actionTreyClose);

    // Вставляем меню в трей
    systemTray->setContextMenu(menuTrey);

    // Подключаем актоны к слотам
    connect(systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(treyProgrammShow()));
    connect(actionTreyEdit,SIGNAL(triggered()),this,SLOT(treyEdit()));
    connect(actionTreySetting,SIGNAL(triggered()),this,SLOT(treySetting()));
    connect(actionTreyStyle,SIGNAL(triggered()),this,SLOT(treyStyle()));
    connect(actionTreyHelp,SIGNAL(triggered()),this,SLOT(tryeHelp()));
    connect(actionTreyInfo,SIGNAL(triggered()),this,SLOT(treyInfo()));
    connect(actionTreyMask,SIGNAL(triggered()),this,SLOT(treyMask()));
    connect(actionTreyClose,SIGNAL(triggered()),this,SLOT(close()));

    // Отображаем иконку в трее
    systemTray->show();
    ////////////////////// end

    // Разрешение экрана
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);

    // Настройки программы это по умочанию
    reperatWord = true;
    whatAmountWord = 5;
    ui_setting->input_amount->setMinimum(3);

    saveTime.setHMS(1,0,0);
    ui_setting->intup_time->setMinimumTime(QTime(0,0,30));
    ui_setting->intup_time->setMaximumTime(QTime(2,0,0));

    amount_correct = 10;
    ui_setting->input_amount_correct->setMinimum(5);

//    settings.remove("/Settings/ang_word");
//    settings.remove("/Settings/rus_word");
//    settings.remove("/Settings/statistics_word");
//    settings.remove("Settings/teach_word");
//    settings.remove("Settings/reperatWord");
//    settings.remove("Settings/whatAmountWord");
//    settings.remove("Settings/saveTime");

    readSetting();

    int temp = saveTime.hour()*120*1000 + saveTime.minute()*60*1000 + saveTime.second()*1000;
    timer = new QTimeLine(temp, this);
    timer->setFrameRange(0, temp);

    // Подключаем таймер к слоту
    connect(timer,SIGNAL(finished()),this,SLOT(treyProgrammShow()));
    //connect(timer,SIGNAL(frameChanged(int)),this,SLOT(temp(int)));

    demandWord = true;
    shiftWord = 0;
    saveRowTeachWord = -1;

    if(!teach_word.isEmpty())
    {
        ui->show_word->setText(teach_word.at(shiftWord));
        ui->progress_lesson->setMaximum(teach_word.size()-1);
        ui->progress_lesson->setValue(0);
    }
    else
    {
        ui->progress_lesson->setValue(0);
    }

    connect(ui->input_word_edit,SIGNAL(returnPressed()),this,SLOT(returnPressedInputWord()));
    connect(ui->push_help,SIGNAL(clicked()),this,SLOT(pushHelp()));

    connect(ui_input->list_ang_word,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrnetRow_list_rus(int)));
    connect(ui_input->list_rus_word,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrnetRow_list_eng(int)));
    connect(ui_input->add_word,SIGNAL(clicked()),this,SLOT(addWord()));
    connect(ui_input->delete_word,SIGNAL(clicked()),this,SLOT(deleteWord()));

    connect(dialog_input,SIGNAL(rejected()),ui_input->list_ang_word,SLOT(clear()));
    connect(dialog_input,SIGNAL(rejected()),ui_input->list_rus_word,SLOT(clear()));
    connect(dialog_input,SIGNAL(rejected()),ui_input->Edit_ang_word,SLOT(clear()));
    connect(dialog_input,SIGNAL(rejected()),ui_input->Edit_rus_word,SLOT(clear()));


    connect(ui_setting->save_false,SIGNAL(clicked()),dialog_setting,SLOT(close()));
    connect(ui_setting->ang_one,SIGNAL(clicked()),this,SLOT(setBaseWordEng()));
    connect(ui_setting->rus_one,SIGNAL(clicked()),this,SLOT(setBaseWordRus()));
    connect(ui_setting->list_base,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrnetRow_list_base(int)));
    connect(ui_setting->list_teach,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrnetRow_list_teach(int)));
    connect(ui_setting->input_word_teach,SIGNAL(clicked()),this,SLOT(inputWordTeach()));
    connect(ui_setting->list_base,SIGNAL(activated(QModelIndex)),this,SLOT(inputWordTeach()));
    connect(ui_setting->input_amount,SIGNAL(valueChanged(int)),this,SLOT(reductionSizeListTeach(int)));

    connect(dialog_setting,SIGNAL(rejected()),this,SLOT(closeDialogSetting()));
    connect(ui_setting->save_true,SIGNAL(clicked()),this,SLOT(settingSaveTrue()));
    connect(ui_setting->save_true,SIGNAL(clicked()),dialog_setting,SLOT(close()));
    connect(ui_setting->del_word_teach,SIGNAL(clicked()),this,SLOT(deleteWordTeach()));

    // Перевод
    connect(ui_setting->list_teach,SIGNAL(currentTextChanged(QString)),this,SLOT(showTranslation(QString)));
    connect(ui_setting->list_base,SIGNAL(currentTextChanged(QString)),this,SLOT(showTranslation(QString)));
}

void MainWindow::temp(int temp)
{
    qDebug() << temp;
}

// slot for trey action
void MainWindow::treyProgrammShow()
{
    shiftWord = 0;
    ui->progress_lesson->setValue(shiftWord);
    ui->show_word->setText(teach_word.at(shiftWord));
    ui->input_word_edit->clear();

    timer->stop();
    this->show();
}

void MainWindow::treyEdit()
{
    timer->stop();
    this->setVisible(true);
    exec_dialog_input();
}

void MainWindow::treySetting()
{
    timer->stop();
    this->setVisible(true);
    exec_dialog_setting();
}

void MainWindow::treyStyle()
{
    qDebug() << "Trey style";
}

void MainWindow::tryeHelp()
{
    qDebug() << "Trey help";
}

void MainWindow::treyInfo()
{
    qDebug() << "Trey info";
}

void MainWindow::treyMask()
{
    this->setVisible(false);
    timer->start();
}

// function for qml
void MainWindow::exitProgramm()
{
    this->close();
}

void MainWindow::maskProgramm()
{
    this->setVisible(false);
    timer->start();
}
/////////////////////////////////end

void MainWindow::installQml()
{
    //Включаем наш QML Background_qml
    ui_qml_background = new QDeclarativeView(this);
    ui_qml_background->setSource(QUrl("qrc:/Background_qml.qml"));
    // Помещаем на в конец стека виджетов
    ui_qml_background->lower();

    //Находим корневой элемент
    Root_ui_qml_background = ui_qml_background->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент Qt_fun
    ui_qml_background->rootContext()->setContextProperty("Qt_fun", this);

    /////////////////////////////////////////////////////////////////////

    //Включаем наш QML Menu_qml
    ui_qml_menu = new QDeclarativeView(this);
    ui_qml_menu->setSource(QUrl("qrc:/Menu_qml.qml"));
    ui_qml_menu->setBackgroundRole(QPalette::Background);

    //Находим корневой элемент
    Root_ui_qml_menu = ui_qml_menu->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент Qt_fun
    ui_qml_menu->rootContext()->setContextProperty("Qt_fun", this);


//    // Кнопки на верх стека
//    QObject *rect = Root->findChild<QObject*>("edit_push");

//     if (rect)
//     {
//         //rect->setProperty("buttonLabel", "input_text");
//         rect->setParent(this);
//     }
}

void MainWindow::pushHelp()
{
    if(ui->show_word->text().contains(QRegExp("([А-Я])|([а-я])")))
    {
        for(int i = 0; i<rus_word.size(); i++)
        {
            if(rus_word.at(i) == ui->show_word->text())
            {
                ui->input_word_edit->setText(ang_word.at(i));
                ui->input_word_edit->setFocus();
            }
        }
    }
    else if(ui->show_word->text().contains(QRegExp("([A-Z])|([a-z])")))
    {
        for(int i = 0; i<ang_word.size(); i++)
        {
            if(ang_word.at(i) == ui->show_word->text())
            {
                ui->input_word_edit->setText(rus_word.at(i));
                ui->input_word_edit->setFocus();
            }
        }
    }
}

void MainWindow::returnPressedInputWord()
{
    if(ui->show_word->text().contains(QRegExp("([А-Я])|([а-я])")))
    {
        for(int i = 0; i<ang_word.size(); i++)
        {
            if(rus_word.at(i) == ui->show_word->text())
            {
                if(ang_word.at(i) == ui->input_word_edit->text())
                {
                    if(shiftWord < teach_word.size()-1)
                    {
                        int temp = statistics_word.at(shiftWord).toInt();
                        temp++;
                        statistics_word[shiftWord] = QVariant(temp);

                        if(temp >= amount_correct)
                        {
                            QString temp;
                            temp.setNum(amount_correct);

                            int ret = QMessageBox::information(this,
                                                               tr("Информация"),
                                                               tr("Вы ответили правильно уже ") + temp + tr(" раз."
                                                                  "\n\nУдалить слово из списка?"),
                                                               QMessageBox::Yes | QMessageBox::No);

                            if(ret == 16384)
                            {
                                teach_word.removeAt(shiftWord);
                                statistics_word.removeAt(shiftWord);

                                shiftWord--;
                            }
                            else
                            {
                                statistics_word[shiftWord] = QVariant(0);
                            }
                        }

                        shiftWord++;

                        ui->progress_lesson->setValue(shiftWord);
                        ui->show_word->setText(teach_word.at(shiftWord));
                        ui->input_word_edit->clear();
                        break;
                    }
                    else
                    {
                        bool BL_temp = true;
                        if(shiftWord < teach_word.size())
                        {
                            int temp = statistics_word.at(shiftWord).toInt();
                            temp++;
                            statistics_word[shiftWord] = QVariant(temp);

                            if(temp >= amount_correct)
                            {
                                QString temp;
                                temp.setNum(amount_correct);
                                int ret = QMessageBox::information(this,
                                                                   tr("Информация"),
                                                                   tr("Вы ответили правильно уже ") + temp + tr(" раз."
                                                                      "\n\nУдалить слово из списка?"),
                                                                   QMessageBox::Yes | QMessageBox::No);

                                if(ret == 16384)
                                {
                                    teach_word.removeAt(shiftWord);
                                    statistics_word.removeAt(shiftWord);

                                    shiftWord--;

                                    if(teach_word.isEmpty())
                                    {
                                        QMessageBox::information(this, tr("Информация"),tr("Все слова выучены  \nДобавьте новые  "));

                                        ui->show_word->setText("<center><span style=\"font-size:16pt;\">Добавте слова для обучения <br>в настройках <br><img src=\":/icon/setting\" width=\"50\"/></span></center>");

                                        BL_temp = false;
                                        ui->input_word_edit->clear();
                                    }
                                }
                                else
                                {
                                    statistics_word[shiftWord] = QVariant(0);
                                }
                            }
                        }

                        if(BL_temp)
                        {
                            int ret = QMessageBox::information(this,
                                                               tr("Информация"),
                                                               tr("Повторение слов закончено\nПовторим еще раз?"),
                                                               QMessageBox::Yes | QMessageBox::No);

                            if(ret == 16384)
                            {
                                shiftWord = 0;
                                ui->progress_lesson->setValue(shiftWord);
                                ui->show_word->setText(teach_word.at(shiftWord));
                                ui->input_word_edit->clear();
                            }
                            else
                            {
                                this->setVisible(false);
                                timer->start();
                            }
                        }

                        break;
                    }
                }
                else
                {
                    QMessageBox::information(this,tr("Информация"), tr("Ответ не верен"));
                    break;
                }
            }
        }
    }
    else if(ui->show_word->text().contains(QRegExp("([A-Z])|([a-z])")))
    {
        for(int i = 0; i<ang_word.size(); i++)
        {
            if(ang_word.at(i) == ui->show_word->text())
            {
                if(rus_word.at(i) == ui->input_word_edit->text())
                {
                    ui->input_word_edit->clear();

                    if(shiftWord < teach_word.size()-1)
                    {
                        int temp = statistics_word.at(shiftWord).toInt();
                        temp++;
                        statistics_word[shiftWord] = QVariant(temp);

                        if(temp >= amount_correct)
                        {
                            QString temp;
                            temp.setNum(amount_correct);
                            int ret = QMessageBox::information(this,
                                                               tr("Информация"),
                                                               tr("Вы ответили правильно уже ") + temp + tr(" раз."
                                                                  "\n\nУдалить слово из списка?"),
                                                               QMessageBox::Yes | QMessageBox::No);

                            if(ret == 16384)
                            {
                                teach_word.removeAt(shiftWord);
                                statistics_word.removeAt(shiftWord);

                                shiftWord--;
                            }
                            else
                            {
                                statistics_word[shiftWord] = QVariant(0);
                            }
                        }

                        shiftWord++;
                        ui->progress_lesson->setValue(shiftWord);
                        ui->show_word->setText(teach_word.at(shiftWord));
                        ui->input_word_edit->clear();
                        break;
                    }
                    else
                    {
                        bool BL_temp = true;
                        if(shiftWord < teach_word.size())
                        {
                            int temp = statistics_word.at(shiftWord).toInt();
                            temp++;
                            statistics_word[shiftWord] = QVariant(temp);

                            if(temp >= amount_correct)
                            {
                                QString temp;
                                temp.setNum(amount_correct);
                                int ret = QMessageBox::information(this,
                                                                   tr("Информация"),
                                                                   tr("Вы ответили правильно уже ") + temp + tr(" раз."
                                                                      "\n\nУдалить слово из списка?"),
                                                                   QMessageBox::Yes | QMessageBox::No);

                                if(ret == 16384)
                                {
                                    teach_word.removeAt(shiftWord);
                                    statistics_word.removeAt(shiftWord);

                                    shiftWord--;

                                    if(teach_word.isEmpty())
                                    {
                                        QMessageBox::information(this, tr("Информация"),tr("Все слова выучены  \nДобавьте новые  "));
                                        ui->show_word->setText("<center><span style=\"font-size:16pt;\">Добавте слова для обучения <br>в настройках <br><img src=\":/icon/setting\" width=\"50\"/></span></center>");
                                        ui->input_word_edit->clear();
                                        BL_temp = false;
                                    }
                                }
                                else
                                {
                                    statistics_word[shiftWord] = QVariant(0);
                                }
                            }
                        }

                        if(BL_temp)
                        {
                            int ret = QMessageBox::information(this,
                                                               tr("Информация"),
                                                               tr("Повторение слов закончено\nПовторим еще раз?"),
                                                               QMessageBox::Yes | QMessageBox::No);

                            if(ret == 16384)
                            {
                                shiftWord = 0;
                                ui->progress_lesson->setValue(shiftWord);
                                ui->show_word->setText(teach_word.at(shiftWord));
                                ui->input_word_edit->clear();
                            }
                            else
                            {
                                this->setVisible(false);
                                timer->start();
                            }
                        }

                        break;
                    }
                }
                else
                {
                    QMessageBox::information(this,tr("Информация"), tr("Ответ не верен"));
                    break;
                }
            }
        }
    }
}

void MainWindow::settingSaveTrue()
{
    teach_word = temp_teach_word;
    reperatWord = ui_setting->reperat_yes->isChecked();
    whatAmountWord = ui_setting->input_amount->value();
    saveTime = ui_setting->intup_time->time();
    amount_correct = ui_setting->input_amount_correct->value();


    if(!statistics_word.isEmpty())
        statistics_word.clear();

        for(int i = 0; i<teach_word.size(); i++)
        {
            statistics_word << 0;
        }


    // Приведим все данные к милисекундам
    int temp = saveTime.hour()*120*1000 + saveTime.minute()*60*1000 + saveTime.second()*1000;

    // Переустановка таймера
    timer->setDuration(temp);
    timer->setFrameRange(0, temp);

    if(!teach_word.isEmpty())
    {
        shiftWord = 0;
        ui->show_word->setText(teach_word.at(shiftWord));
    }
    else
    {
        ui->show_word->setText("<center><span style=\"font-size:16pt;\">Добавте слова для обучения <br>в настройках <br><img src=\":/icon/setting\" width=\"50\"/></span></center>");
    }

    if(!teach_word.isEmpty())
    {
        ui->progress_lesson->setMaximum(teach_word.size()-1);
        ui->progress_lesson->setValue(0);
    }
}

void MainWindow::setCurrnetRow_list_teach(int row)
{
    saveRowTeachWord = row;
}

void MainWindow::deleteWordTeach()
{
    if(!temp_teach_word.isEmpty())
    {
        temp_teach_word.removeAt(saveRowTeachWord);

        ui_setting->list_teach->clear();
        ui_setting->list_teach->addItems(temp_teach_word);

        for(int i=0; i<temp_teach_word.size(); i++)
        {
            if(i%2)
            {
                ui_setting->list_teach->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }

        if(!temp_teach_word.isEmpty())
        {
            saveRowTeachWord = temp_teach_word.size()-1;
            ui_setting->list_teach->setCurrentRow(saveRowTeachWord);
            ui_setting->list_teach->setFocus();
        }
        else
        {
            ui_setting->label_translation->setText(tr("Выбирите слово для перевода"));
            ui_setting->del_word_teach->setEnabled(false);
            ui_setting->list_base->setFocus();
        }
    }
}

void MainWindow::closeDialogSetting()
{
    ui_setting->list_base->clear();
    ui_setting->list_teach->clear();
    ui_setting->save_false->setFocus();
    ui->input_word_edit->setFocus();
}

void MainWindow::showTranslation(QString str)
{
    if(str.contains(QRegExp("([А-Я])|([а-я])")))
    {
        for(int i = 0; i<rus_word.size(); i++)
        {
            if(rus_word.at(i) == str)
            {
                ui_setting->label_translation->setText("<b>" + str + "</b>" + "<br>" + ang_word.at(i));
            }
        }
    }
    else if(str.contains(QRegExp("([A-Z])|([a-z])")))
    {
        for(int i = 0; i<ang_word.size(); i++)
        {
            if(ang_word.at(i) == str)
            {
                ui_setting->label_translation->setText("<b>" + str + "</b>" + "<br>" + rus_word.at(i));
            }
        }
    }
}

void MainWindow::reductionSizeListTeach(int value)
{
    if(value < temp_teach_word.size())
    {
        temp_teach_word.removeAt(temp_teach_word.size()-1);

        ui_setting->list_teach->clear();

        ui_setting->list_teach->addItems(temp_teach_word);

        for(int i = 0; i<temp_teach_word.size(); i++)
        {
            if(i%2)
            {
                ui_setting->list_teach->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }
    }
}

void MainWindow::inputWordTeach()
{
    if(saveRow == -1)
    {
        QMessageBox::information(this, tr("Информация"),tr("Выберите слово!"));
    }
    else
    {
        if(demandWord)
        {
            if(temp_teach_word.size()<ui_setting->input_amount->value())
            {
                if(!temp_teach_word.contains(ang_word.at(saveRow)))
                {
                    bool BL_temp = true;

                    if(!temp_teach_word.isEmpty())
                    {
                        for(int i = 0; i<temp_teach_word.size(); i++)
                        {
                            if(temp_teach_word.at(i).contains(QRegExp("([А-Я])|([а-я])")))
                            {
                                int ret = QMessageBox::information(this,
                                                                   tr("Добавление слова"),
                                                                   tr("Вы выбрали другой язык для добавления.\n"
                                                                      "Слова выбранные Вами ранее будут стерты.\n"
                                                                      "\nПродолижить?"),
                                                                   QMessageBox::Yes | QMessageBox::No);

                                if(ret == 16384)
                                {
                                    temp_teach_word.clear();
                                    statistics_word.clear();
                                }
                                else
                                {
                                    BL_temp = false;
                                }
                                break;
                            }
                        }
                    }

                    if(BL_temp)
                    {
                        ui_setting->del_word_teach->setEnabled(true);

                        temp_teach_word << ang_word.at(saveRow);

                        ui_setting->list_teach->clear();

                        ui_setting->list_teach->addItems(temp_teach_word);

                        for(int i = 0; i<temp_teach_word.size(); i++)
                        {
                            if(i%2)
                            {
                                ui_setting->list_teach->item(i)->setBackgroundColor(QColor(187, 255, 255));
                            }
                        }

                        saveRowTeachWord = temp_teach_word.size()-1;
                        ui_setting->list_teach->setCurrentRow(saveRowTeachWord);

                        if(saveRow != ang_word.size()-1)
                        {
                            saveRow++;
                            ui_setting->list_base->setCurrentRow(saveRow);
                            ui_setting->list_base->setFocus();
                        }
                    }
                }
                else
                {
                    QMessageBox::information(this,tr("Информация"), tr("Слово уже добавленно"));
                }
            }
            else
            {
                QMessageBox::information(this,tr("Информация"), tr("Добавленно максимум элиментов"));
            }
        }
        else
        {
            if(temp_teach_word.size()<ui_setting->input_amount->value())
            {
                if(!temp_teach_word.contains(rus_word.at(saveRow)))
                {
                    bool BL_temp = true;

                    if(!temp_teach_word.isEmpty())
                    {
                        for(int i = 0; i<temp_teach_word.size(); i++)
                        {
                            if(temp_teach_word.at(i).contains(QRegExp("([A-Z])|([a-z])")))
                            {
                                int ret = QMessageBox::information(this,
                                                                   tr("Добавление слова"),
                                                                   tr("Вы выбрали другой язык для добавления.\n"
                                                                      "Слова выбранные Вами ранее будут стерты.\n"
                                                                      "\nПродолижить?"),
                                                                   QMessageBox::Yes | QMessageBox::No);

                                if(ret == 16384)
                                {
                                    temp_teach_word.clear();
                                    statistics_word.clear();
                                }
                                else
                                {
                                    BL_temp = false;
                                }
                                break;
                            }
                        }
                    }

                    if(BL_temp)
                    {
                        ui_setting->del_word_teach->setEnabled(true);

                        temp_teach_word << rus_word.at(saveRow);

                        ui_setting->list_teach->clear();

                        ui_setting->list_teach->addItems(temp_teach_word);

                        for(int i = 0; i<temp_teach_word.size(); i++)
                        {
                            if(i%2)
                            {
                                ui_setting->list_teach->item(i)->setBackgroundColor(QColor(187, 255, 255));
                            }
                        }

                        saveRowTeachWord = temp_teach_word.size()-1;
                        ui_setting->list_teach->setCurrentRow(saveRowTeachWord);

                        if(saveRow != rus_word.size()-1)
                        {
                            saveRow++;
                            ui_setting->list_base->setCurrentRow(saveRow);
                            ui_setting->list_base->setFocus();
                        }
                    }
                }
                else
                {
                    QMessageBox::information(this,tr("Информация"), tr("Слово уже добавленно"));
                }
            }
            else
            {
                QMessageBox::information(this,tr("Информация"), tr("Добавленно максимум элиментов"));
            }
        }
    }
}

void MainWindow::setCurrnetRow_list_base(int row)
{
    if(row!=-1)
    saveRow = row;
}

void MainWindow::setBaseWordEng()
{
    demandWord = true;
    ui_setting->list_base->clear();

    ui_setting->list_base->addItems(ang_word);

    for(int i = 0; i<ang_word.size(); i++)
    {
        ui_setting->list_base->item(i)->setToolTip(rus_word.at(i));
    }

    for(int i = 0; i<ang_word.size(); i++)
    {
        if(i%2)
        {
            ui_setting->list_base->item(i)->setBackgroundColor(QColor(187, 255, 255));
        }
    }

    ui_setting->list_base->setCurrentRow(saveRow);
    ui_setting->list_base->setFocus();
}

void MainWindow::setBaseWordRus()
{
    demandWord = false;
    ui_setting->list_base->clear();

    ui_setting->list_base->addItems(rus_word);

    for(int i = 0; i<rus_word.size(); i++)
    {
        ui_setting->list_base->item(i)->setToolTip(ang_word.at(i));
    }

    for(int i = 0; i<rus_word.size(); i++)
    {
        if(i%2)
        {
            ui_setting->list_base->item(i)->setBackgroundColor(QColor(187, 255, 255));
        }
    }

    ui_setting->list_base->setCurrentRow(saveRow);
    ui_setting->list_base->setFocus();
}

void MainWindow::exec_dialog_setting()
{
    saveRow = -1;
    ui_setting->input_amount->setMaximum(ang_word.size());
    ui_setting->input_amount->setValue(whatAmountWord);

    ui_setting->label_translation->setText(tr("Выбирите слово для перевода"));

    if(teach_word.isEmpty())
        ui_setting->del_word_teach->setEnabled(false);

    temp_teach_word = teach_word;
    ui_setting->list_teach->addItems(temp_teach_word);

    ui_setting->input_amount_correct->setValue(amount_correct);

    for(int i = 0; i<temp_teach_word.size(); i++)
    {
        if(i%2)
        {
            ui_setting->list_teach->item(i)->setBackgroundColor(QColor(187, 255, 255));
        }
    }

    if(demandWord)
        ui_setting->ang_one->setChecked(true);
    else
        ui_setting->rus_one->setChecked(true);

    if(reperatWord)
        ui_setting->reperat_yes->setChecked(true);
    else
        ui_setting->reperat_no->setChecked(true);

    ui_setting->intup_time->setTime(saveTime);

    if(ui_setting->ang_one->isChecked())
    {
        ui_setting->list_base->addItems(ang_word);

        for(int i = 0; i<ang_word.size(); i++)
        {
            ui_setting->list_base->item(i)->setToolTip(rus_word.at(i));
        }

        for(int i = 0; i<ang_word.size(); i++)
        {
            if(i%2)
            {
                ui_setting->list_base->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }
    }
    else if(ui_setting->rus_one->isChecked())
    {
        ui_setting->list_base->addItems(rus_word);

        for(int i = 0; i<rus_word.size(); i++)
        {
            ui_setting->list_base->item(i)->setToolTip(ang_word.at(i));
        }

        for(int i = 0; i<rus_word.size(); i++)
        {
            if(i%2)
            {
                ui_setting->list_base->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }
    }

    dialog_setting->exec();
}

bool MainWindow::addWord()
{
    if(ui_input->Edit_ang_word->text().isEmpty()||ui_input->Edit_rus_word->text().isEmpty())
    {
        QMessageBox::information(this, tr("Информация"),tr("Напишите слово!"));
        return false;
    }

    if(ui_input->Edit_ang_word->text().contains(QRegExp("([0-9])")) ||
        ui_input->Edit_rus_word->text().contains(QRegExp("([0-9])")))
    {
        QMessageBox::information(this, tr("Информация"),tr("Пишите буквами пожалуйста"));

        return false;
    }

    if(!ui_input->Edit_ang_word->text().contains(QRegExp("([A-Z])|([a-z])")))
    {
        QMessageBox::information(this, tr("Информация"),tr("Введите английский!"));
        return false;
    }

    if(!ui_input->Edit_rus_word->text().contains(QRegExp("([А-Я])|([а-я])")))
    {
        QMessageBox::information(this, tr("Информация"),tr("Введите русский!"));
        return false;
    }

    for(int i = 0; i< ang_word.size(); i++)
    {
        if(ang_word.at(i) == ui_input->Edit_ang_word->text())
        {
            QMessageBox::information(this,tr("Информация"), tr("Слово есть в наличии"));
            ui_input->list_ang_word->setCurrentRow(i);
            ui_input->list_ang_word->setFocus();
            return false;
        }
    }

    for(int i = 0; i< rus_word.size(); i++)
    {
        if(rus_word.at(i) == ui_input->Edit_rus_word->text())
        {
            QMessageBox::information(this,tr("Информация"), tr("Слово есть в наличии"));
            ui_input->list_rus_word->setCurrentRow(i);
            ui_input->list_rus_word->setFocus();
            return false;
        }
    }

    int ret = QMessageBox::information(this,
                                       tr("Добавление слова"),tr("Добавить: \n") +
                                       ui_input->Edit_ang_word->text() + " - " +
                                       ui_input->Edit_rus_word->text() + "?",
                                       QMessageBox::Yes | QMessageBox::No);

    if(ret == 16384)
    {
        ang_word << ui_input->Edit_ang_word->text();
        rus_word << ui_input->Edit_rus_word->text();

        ui_input->list_ang_word->clear();
        ui_input->list_rus_word->clear();
        ui_input->Edit_ang_word->clear();
        ui_input->Edit_rus_word->clear();

        ui_input->list_ang_word->addItems(ang_word);
        ui_input->list_rus_word->addItems(rus_word);

        for(int i = 0; i<ang_word.size(); i++)
        {
            if(i%2)
            {
                ui_input->list_ang_word->item(i)->setBackgroundColor(QColor(187, 255, 255));
                ui_input->list_rus_word->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }

        if(!ui_input->delete_word->isEnabled())
            ui_input->delete_word->setEnabled(true);

        saveRow = ang_word.size()-1;
        ui_input->list_ang_word->setCurrentRow(saveRow);
    }

    return true;
}

void MainWindow::deleteWord()
{
    int ret = QMessageBox::information(this,
                                       tr("Удаление слова"),tr("Удалить: \n") +
                                       ang_word.at(saveRow) + " - " +
                                       rus_word.at(saveRow) + "?",
                                       QMessageBox::Yes | QMessageBox::No);

    if(ret == 16384)
    {
        teach_word.removeOne(ang_word.at(saveRow));
        teach_word.removeOne(rus_word.at(saveRow));
        ang_word.removeAt(saveRow);
        rus_word.removeAt(saveRow);

        if(ang_word.isEmpty())
        {
           ui_input->delete_word->setEnabled(false);
        }

        ui_input->list_ang_word->clear();
        ui_input->list_rus_word->clear();

        ui_input->list_ang_word->addItems(ang_word);
        ui_input->list_rus_word->addItems(rus_word);

        for(int i = 0; i<ang_word.size(); i++)
        {
            if(i%2)
            {
                ui_input->list_ang_word->item(i)->setBackgroundColor(QColor(187, 255, 255));
                ui_input->list_rus_word->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }

        saveRow = 0;
        ui_input->list_ang_word->setCurrentRow(saveRow);
    }
}

void MainWindow::setCurrnetRow_list_rus(int row)
{
    saveRow = row;
    ui_input->list_rus_word->setCurrentRow(row);
}

void MainWindow::setCurrnetRow_list_eng(int row)
{
    saveRow = row;
    ui_input->list_ang_word->setCurrentRow(row);
}

void MainWindow::exec_dialog_input()
{
    ui_input->list_ang_word->addItems(ang_word);
    ui_input->list_rus_word->addItems(rus_word);

    for(int i = 0; i<ang_word.size(); i++)
    {
        if(i%2)
        {
            ui_input->list_ang_word->item(i)->setBackgroundColor(QColor(187, 255, 255));
            ui_input->list_rus_word->item(i)->setBackgroundColor(QColor(187, 255, 255));
        }
    }

    saveRow = 0;
    ui_input->list_ang_word->setCurrentRow(saveRow);

    dialog_input->exec();
}

void MainWindow::writeSetting()
{
    settings.setValue("/Settings/pos/x" , this->pos().x());
    settings.setValue("/Settings/pos/y" , this->pos().y());
    settings.setValue("/Settings/ang_word", ang_word);
    settings.setValue("/Settings/rus_word", rus_word);
    settings.setValue("Settings/statistics_word", statistics_word);

    settings.setValue("Settings/teach_word" , teach_word);
    settings.setValue("Settings/reperatWord" , reperatWord);
    settings.setValue("Settings/whatAmountWord" , whatAmountWord);
    settings.setValue("Settings/saveTime" , saveTime);
    settings.setValue("Settings/amount_correct", amount_correct);
}

void MainWindow::readSetting()
{
    if(settings.value("/Settings/pos/x").toInt()!=0&&settings.value("/Settings/pos/y").toInt())
    this->move(settings.value("/Settings/pos/x").toInt(),settings.value("/Settings/pos/y").toInt());

    ang_word = settings.value("/Settings/ang_word", ang_word).toStringList();
    rus_word = settings.value("/Settings/rus_word", rus_word).toStringList();
    statistics_word = settings.value("Settings/statistics_word", statistics_word).toList();

    teach_word = settings.value("Settings/teach_word" , teach_word).toStringList();
    reperatWord = settings.value("Settings/reperatWord" , reperatWord).toBool();
    whatAmountWord = settings.value("Settings/whatAmountWord" , whatAmountWord).toInt();
    saveTime = settings.value("Settings/saveTime" , saveTime).toTime();
    amount_correct = settings.value("Settings/amount_correct", amount_correct).toInt();

    if(ang_word.isEmpty()||rus_word.isEmpty())
    {
        QFile read_file("word.dic");
        QString all_file;

        if(read_file.open(QIODevice::ReadOnly))
        {
            QTextStream out(&read_file);
            all_file = out.readAll();
        }

        all_file.remove("\t");
        all_file.remove("\n");

        qDebug() << "read word";

        QStringList tempList = all_file.split(";");

        for(int i = 0; i<tempList.size(); i+=2)
        {
            ang_word << tempList.at(i);
            rus_word << tempList.at(i+1);
        }
    }
}

MainWindow::~MainWindow()
{
    writeSetting();
    delete ui;
}
