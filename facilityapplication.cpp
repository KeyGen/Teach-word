#include "mainwindow.h"
#include "qzip/qzipreader_p.h"
#include "qzip/qzipwriter_p.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QToolTip> // Подсказка для кнопки
#include <QTimer>

// Загрузка словарей StarDict
int MainWindow::bootDictionary()
{
    QDir dir("dic");                    // Создаем Qdir в папке dic

    dir.mkdir("tempdir");   // Создаем временную папку

    QStringList filters;                // Устанавливаем фильтры
    filters << "*.dict.zip" << "*.ifo"; // Устанавливаем фильтры
    dir.setNameFilters(filters);        // Устанавливаем фильтры

    QFileInfoList list = dir.entryInfoList();   // Чтение инфо о файлах

    QString dicname;
    QString dicifo;

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);        // Получим доступ к имени

        if(!fileInfo.fileName().contains(".ifo"))   // Если файл не *.ifo
        {
            dicname = fileInfo.fileName(); // Запоминаем имя архива
            dicname.chop(9);
            QZipReader zip_reader(QLatin1String("dic/" + fileInfo.fileName().toAscii())); // чтение указанного zip архива

            if (zip_reader.exists()) {          // Если все чудно

                // вывод информации об архиве
               // qDebug() << "Number of items in the zip archive =" << zip_reader.count(); // Количество элементов в архиве

//                foreach (QZipReader::FileInfo info, zip_reader.fileInfoList()) { // Инфорация о архиве
//                    if(info.isFile)
//                        qDebug() << "File:" << info.filePath << info.size;
//                    else if (info.isDir)
//                        qDebug() << "Dir:" << info.filePath;
//                    else
//                        qDebug() << "SymLink:" << info.filePath;
//                }

                // распаковка архива по указанному пути
                zip_reader.extractAll(QLatin1String("dic/tempdir"));
            }
        }
        else
        {
            QFile read_file("dic/" + fileInfo.fileName().toAscii()); // Открываем ifo
            QString all_file;

            if(read_file.open(QIODevice::ReadOnly)) // чтение ifo
            {
                QTextStream out(&read_file);
                out.setCodec("UTF-8");          // Установка кодека
                all_file = out.readAll();       // Считываем весь файл в QString
            }

            dicifo = all_file;
        }

        if(dicifo.contains(dicname.left(dicname.size()-2), Qt::CaseInsensitive))
        {
            listDict[dicifo] = dicname + ".dict.dz.uncompressed";

            QString dicnameclear;
            for(int i = dicifo.lastIndexOf("bookname=") + 9; dicifo.at(i)!='\n'; i++)
            dicnameclear += dicifo.at(i);

            dicInput->addItem(dicnameclear);

            dicname.clear();
            dicifo.clear();
        }

    }
//    QZipReader ztemp(QLatin1String("dic/AccountingER.dict.zip"));
//    QByteArray temp = ztemp.fileData(QLatin1String("AccountingER.dict.dz.uncompressed"));
    return 0;
}

void MainWindow::connectObject()
{
    // Вызывает WainWindow при клике на иконку в трее
    connect(systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(treyProgrammShow(QSystemTrayIcon::ActivationReason)));
    // Актион для выхода
    connect(actionTreyClose, SIGNAL(triggered()),this,SLOT(slotTreyClose()));         // Закрыть программу из трея
    // Актион включает/выключает звук
    connect(actionTreySound, SIGNAL(triggered(bool)),this,SLOT(slotTreySound(bool))); // Включить/выключить звук из трея
    // Актион который открывает справку
    connect(actionTreyHelp, SIGNAL(triggered()),this,SLOT(slotTreyHelp()));           // Вызов помощи из трея
    // Актион открывающий диалог инфор. о программе
    connect(actionTreyInfo, SIGNAL(triggered()),this,SLOT(slotTreyInfo()));           // Вызов информации о программе из трея
    // Актион открывающий диалог настроек
    connect(actionTreySetting, SIGNAL(triggered()),this,SLOT(slotTreySetting()));     // Вызов настроек из трея
    // Актион отображающий программу
    connect(actionTreyShow, SIGNAL(triggered()),this,SLOT(slotTreyShow()));           // Показать программу из трея
    // Актион прячет окно программы в трей
    connect(actionTreyMask, SIGNAL(triggered()),this,SLOT(slotTreyMask()));           // Скрыть программу из трея

    connect(setupUpdate, SIGNAL(clicked()), this,SLOT(verifyupdate()));               // Проверка обновлений

    connect(dicInput,SIGNAL(activated(QString)),this,SLOT(actionDict(QString)));
    connect(findWord,SIGNAL(textChanged(QString)),this,SLOT(slotFindWord(QString)));

    connect(transferWord,SIGNAL(anchorClicked(QUrl)), findWord,SLOT(clear()));
    connect(transferWord,SIGNAL(anchorClicked(QUrl)), this,SLOT(slotFindWordUrl(QUrl)));
    connect(ListBase,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotInputWordInFindWord(QModelIndex)));
    connect(ListLearnWords,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotInputWordInFindWord(QModelIndex)));

    connect(oneRadio, SIGNAL(clicked()),this,SLOT(slotRadioButtonClick()));
    connect(twoRadio, SIGNAL(clicked()),this,SLOT(slotRadioButtonClick()));
    connect(threeRadio, SIGNAL(clicked()),this,SLOT(slotRadioButtonClick()));

    connect(setupLanguageComboBox,SIGNAL(activated(QString)),this, SLOT(downloadLanguageProgramm(QString)));

    connect(setupTime,SIGNAL(timeChanged(QTime)),this,SLOT(setTimeShow(QTime)));
    connect(setupSinBoxInputAmountCorrect,SIGNAL(valueChanged(int)),this,SLOT(setAnswerTrue(int)));

    connect(timerShow, SIGNAL(timeout()),this,SLOT(slotTimeOut()));
}

// Поиск слова в словаре и выдется результат в html
QString MainWindow::DictInHtml(QString word)
{
    QString html;
    QString temp;

    int i =  activeDict.lastIndexOf("<k>" + word + "</k>") + 3;

    for(; temp != "<k>" ;i++)
    {
        html += activeDict.at(i);

        temp.clear();

        if(i < activeDict.size() - 4)
        {
            temp += activeDict.at(i+1);
            temp += activeDict.at(i+2);
            temp += activeDict.at(i+3);
        }
        else
            break;
    }

    html.prepend("<k>");

    html.replace("\n", "<br>");
    html.replace("<k>", "<b><span style=\"color:#000074; font-size:13pt;\">");
    html.replace("</k>", "</span></b>");
    html.replace("<dtrn>", "");
    html.replace("</dtrn>", "");
    html.replace("<co>", "<span style=\"color:#000074;\">");
    html.replace("</co>", "</span><br>");


    QRegExp rx("<kref>([^<]*)<\/kref>");
    rx.setMinimal(true);

     int pos = 0;
     while ((pos = rx.indexIn(html, pos)) != -1)
     {
         QString str = rx.cap(1);
         QString strUrl = str;
         strUrl.replace(" ", "-----------");

         html.replace("<kref>" + str + "</kref>", "<a href=" + strUrl + ">" + str + "</a>");

         pos += rx.matchedLength();
     }

    //qDebug() << html;

    return html;
}

// Добавление слова из базы для обучения
void MainWindow::addLearnWords(QStringList list)
{
    //qDebug() << "Количество слов в словаре: " << baseWord.count();

    if(list.at(0) == "null" || list.isEmpty())
    {
        list.clear();
        list << ListBase->item(ListBase->currentRow())->text();
    }

    for(int i = 0; i<list.size(); i++)
    {
        if(!learn_word.contains(list.at(i)))
        {
            learn_word << list.at(i);

            ///////////////////////////////////////////////////////////////

            setWords(); // Функция регулирует вывод изучаемых слов на qml из learn_word

            ///////////////////////////////////////////////////////////////

            StatisticsFunction(learn_word); // Проверка/запись статистики

            ///////////////////////////////////////////////////////////////

            ListLearnWords->clear();
            ListLearnWords->addItems(learn_word);

            for(int i=0; i<ListLearnWords->count(); i++)
            {
                if(i%2)
                {
                    ListLearnWords->item(i)->setBackgroundColor(QColor(187, 255, 255));
                }
            }

            int temp = ListBase->currentRow();

            if(temp < ListBase->count())
                ListBase->setCurrentRow(ListBase->currentRow()+1);

            fixedChanges = true; // Фиксирует были или нет изменения в learn_word (Слова для обучения)
        }
        else
        {
            showMassage("wordinsight=", "true");
        }
    }
}

// Очистка слов для обучения
void MainWindow::clearLearnWords()
{
    ListLearnWords->clear();
    learn_word.clear();
    answerTrue->clear();

    fixedChanges = true; // Фиксирует были или нет изменения в learn_word (Слова для обучения)
}

// Удаление выделенного слова из изучаемых слов
void MainWindow::deleteWord()
{
    if(ListLearnWords->currentRow() != -1)
    {
        int temp = ListLearnWords->currentRow();
        learn_word.removeAt(temp);

        ListLearnWords->clear();
        ListLearnWords->addItems(learn_word);

        if(!learn_word.isEmpty())
            StatisticsFunction(learn_word);
        else
            answerTrue->clear();

        for(int i=0; i<ListLearnWords->count(); i++)
        {
            if(i%2)
            {
                ListLearnWords->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }

        fixedChanges = true; // Фиксирует были или нет изменения в learn_word (Слова для обучения)

        if(learn_word.size() > 0)
        {
            ListLearnWords->setCurrentRow(temp - 1);
        }
    }
    else
    {
        if(!learn_word.isEmpty())
            showMassage("wordadddelete=", "true");
        else
            showMassage("worddeleteclear=", "true");
    }
}

// Форма для сообщения общается с qml
bool MainWindow::showMassage(QString text, QString button)
{
    showmessage->show();
    showmessage->activationQml(downloadlanguageMap[text], button);

    connect(showmessage, SIGNAL(signalMove(QPoint)),this,SLOT(setNewMove(QPoint)));

    QPixmap px = QPixmap::grabWindow(QApplication::desktop()->winId()); // получаем картинку

    showmessage->setBackground(px.copy(this->pos().x(),this->pos().y(),this->width(),this->height()));

    return true;
}

// Срабатывает при навидении на кнопку показывает подсказку
void MainWindow::helpButton(QString text,int x, int y)
{
    QToolTip::showText(QPoint(this->pos().x() + x, this->pos().y() + y),downloadlanguageMap[text],this,QRect(0,0,100,30));
}

// Функция устанавливающая размер шрифта относительно размера окна
QString MainWindow::setWidthFont(QString str, int maxwidth, int maxfont)
{
    QString newHtml;

    QFont font;

    int i;
    for(i = maxfont; i>0; i--)
    {
        font.setPixelSize(i);

        if(QFontMetrics(font).width(str) < maxwidth-10) // Если ширина шрифта меньше меньше ширины mazwidth
        {
            break;
        }
    }

    newHtml = "<center>";
    newHtml += "<span style=\" font-size:" + QString::number(i,10) + "px;\">" + str + "</span>";
    newHtml += "</center>";

    return newHtml;
}

// Установка слов в qml / проверка правильности введенного ответа
bool MainWindow::inputShowWords(QString str, QString strinput)
{
    QTextEdit *temp = new QTextEdit(str, this);
    str = temp->toPlainText();
    delete temp;

    QString conversion = wordConversion(str);

    if(containsWord(conversion, strinput))
    {
        setWords(); // Функция регулирует вывод изучаемых слов на qml из learn_word
        return true;
    }
    else
    {
        if(strinput.isEmpty())
        {
            showMassage("wordinput=", "true");
        }
        else
        {
            QObject *rect = Root->findChild<QObject*>("textInput");
            rect->setProperty("color","red");

            startSoundShow();
        }

        return false;
    }
}

// Функция осуществляющая проверку на идентицность без учета регистра
bool MainWindow::containsWord(QString one, QString two)
{
    one = one.toLower();
    two = two.toLower();

    if(two.size() != one.size())
    {
        if(one.contains(";"))
        {
            QStringList templist = one.split(";");

            for(int i = 0; i<templist.size(); i++)
            {
                QString tempstr = templist.at(i);

                if(tempstr.at(tempstr.size()-1) == ' ')
                    tempstr.chop(1);

                if(tempstr.at(0) == ' ')
                    tempstr = tempstr.right(tempstr.size()-1);

                if(tempstr == two)
                    return true;
            }

            return false;
        }
        else if(one.contains(","))
        {
            QStringList templist = one.split(",");

            for(int i = 0; i<templist.size(); i++)
            {
                QString tempstr = templist.at(i);

                if(tempstr.at(tempstr.size()-1) == ' ')
                    tempstr.chop(1);

                if(tempstr.at(0) == ' ')
                    tempstr = tempstr.right(tempstr.size()-1);

                if(tempstr == two)
                    return true;
            }

            return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(one == two)
            return true;
    }
}

// Поиск слова в словаре и выдется перевод
QString MainWindow::wordConversion(QString str)
{
    QString tempStr;
    QString conversion;

    int i =  activeDict.lastIndexOf("<k>" + str + "</k>") + 3;

    for(; tempStr != "<k>" ;i++)
    {
        conversion += activeDict.at(i);

        tempStr.clear();

        if(i < activeDict.size() - 4)
        {
            tempStr += activeDict.at(i+1);
            tempStr += activeDict.at(i+2);
            tempStr += activeDict.at(i+3);
        }
        else
            break;
    }

    if(!conversion.contains("<dtrn>"))
    {
        QRegExp rx("<kref>(.*)</kref>");
        QString kref = str;

         int pos = 0;
         while ((pos = rx.indexIn(conversion, pos)) != -1)
         {
             kref = rx.cap(1);
             pos += rx.matchedLength();
         }

         int i =  activeDict.lastIndexOf("<k>" + kref + "</k>") + 3;
         tempStr.clear();

         for(; tempStr != "<k>" ;i++)
         {
             conversion += activeDict.at(i);

             tempStr.clear();

             if(i < activeDict.size() - 4)
             {
                 tempStr += activeDict.at(i+1);
                 tempStr += activeDict.at(i+2);
                 tempStr += activeDict.at(i+3);
             }
             else
                 break;
         }
    }

    QStringList tempList;
    if(conversion.contains("<dtrn>"))
    {
        QRegExp rx("<dtrn>(.*)</dtrn>");

         int pos = 0;
         while ((pos = rx.indexIn(conversion, pos)) != -1)
         {
             tempList << rx.cap(1);
             pos += rx.matchedLength();
         }

         for(int i = 0;  i<tempList.size(); i++)
         {
             QString tempstr = tempList.at(i);
             tempstr.replace(QRegExp("<c>(.*)</c>"),"");

             tempstr.replace(QRegExp("<co>(.*)</co>"),"");

             tempstr.replace(QRegExp("<i>(.*)</i>"),"");

             tempstr.replace(QRegExp("<abr>(.*)</abr>"),"");

             tempstr.replace(QRegExp("</dtrn>(.*)<dtrn>"),"; ");

             tempstr.replace(QRegExp("<sub>(.*)</sub>"),"");

             tempstr.replace(QRegExp("<kref>(.*)</kref>"),"");

             tempstr.replace("\n","");
             tempstr.replace("  "," ");
             tempstr.replace("   "," ");

             if(tempstr.at(0) == ';')
                 tempstr = tempstr.right(tempstr.size()-1);

             if(tempstr.at(tempstr.size()-1) == ' ')
                 tempstr.chop(1);

             if(tempstr.at(0) == ' ')
                 tempstr = tempstr.right(tempstr.size()-1);

             if(tempstr.at(tempstr.size()-1) == ';')
                 tempstr.chop(1);

             tempList.replace(i, tempstr);
         }
    }
    else
    {
        QRegExp rx("<kref>(.*)</kref>");

         int pos = 0;
         while ((pos = rx.indexIn(conversion, pos)) != -1)
         {
             tempList << rx.cap(1);
             pos += rx.matchedLength();
         }

         qDebug() << conversion;
         qDebug() << "<kref>";
    }

    conversion.clear();
    conversion = tempList.at(0);

    if(tempList.size()>1)
        qDebug() << tempList.size();

    return conversion;
}

// Функция регулирует вывод изучаемых слов на qml из learn_word
void MainWindow::setWords()
{
    QObject *rectBLTwo = Root->findChild<QObject*>("show_" + QString::number(8,10));

    if(rectBLTwo->property("textShow").toString().isEmpty() || learn_word.size()<5)
    {
        for(int i = 0; i < 5 && i < learn_word.size(); i++)
        {
            // Достум из С++ к qml
            QObject *rect = Root->findChild<QObject*>("show_" + QString::number(i+1,10));

            rect->setProperty("textShow", setWidthFont(learn_word.at(i),300,35));
        }
    }
    else
    {
        rectBLTwo = Root->findChild<QObject*>("show_" + QString::number(5,10));
        rectBLTwo->setProperty("textShow","");

        if(rectBLTwo->property("textShow").toString().isEmpty())
        {
            QObject *rect = Root->findChild<QObject*>("show_" + QString::number(4,10));
            QTextEdit *temp = new QTextEdit(rect->property("textShow").toString(), this);

            QObject *rectTwo = Root->findChild<QObject*>("show_" + QString::number(5,10));

            if(rectTwo)
            {
                if(learn_word.indexOf(temp->toPlainText()) + 1 >= learn_word.size())
                    rectTwo->setProperty("textShow", setWidthFont(learn_word.at(0),300,35));
                else
                    rectTwo->setProperty("textShow", setWidthFont(learn_word.at(learn_word.indexOf(temp->toPlainText()) + 1),300,35));


                QObject *one = Root->findChild<QObject*>("show_" + QString::number(5,10));

                temp->setHtml(one->property("textShow").toString());

                if(temp->toPlainText() == learn_word.at(3)) //Если все слова повторили
                {
                    QTimer *message = new QTimer(this);
                    message->setInterval(1180);
                    message->start();

                    connect(message,SIGNAL(timeout()),this,SLOT(slotshowMassage()));
                    connect(message,SIGNAL(timeout()),message,SLOT(stop()));
                }
            }
        }
    }
}

// Функция устанавливает пумолчанию главное окно программы
void MainWindow::setShowOnDefault()
{
    if(fixedChanges) // Фиксирует были или нет изменения в learn_word (Слова для обучения)
    {
        QObject *rect = Root->findChild<QObject*>("defaultQml");
        rect->setProperty("running","true");

        setWords(); // Функция регулирует вывод изучаемых слов на qml из learn_word

        fixedChanges = false; // Фиксирует были или нет изменения в learn_word (Слова для обучения)
    }
}

// Функция проверяет сколько загружено слов для обучения (минимум 5)
int MainWindow::controlSize()
{
    if(learn_word.isEmpty())
        return 0;
    else if(learn_word.size()>= 5)
        return 1;
    else
        return 2;
}

// Подсказка по словам
void MainWindow::helpWord()
{
    // Достум из С++ к qml
    QObject *rect = Root->findChild<QObject*>("recOne");
    rect->setProperty("state", "normal");

    rect = Root->findChild<QObject*>("recTwo");
    rect->setProperty("state", "normal");

    rect = Root->findChild<QObject*>("recThree");
    rect->setProperty("state", "normal");

    rect = Root->findChild<QObject*>("recFour");
    rect->setProperty("state", "normal");

    rect = Root->findChild<QObject*>("massegeBackground");
    rect->setProperty("opacity", "0.7");

    rect = Root->findChild<QObject*>("timerMessage");
    rect->setProperty("running", "true");

    rect = Root->findChild<QObject*>("timerhelpWords");
    rect->setProperty("running", "true");
}

// Показыват/скрывает QRadioButton
void MainWindow::setVisibleQRadioButton(bool BL)
{
    oneRadio->setVisible(BL);
    twoRadio->setVisible(BL);
    threeRadio->setVisible(BL);
}

// Отобразить системное меню
void MainWindow::showSistemsTrey()
{
    // Отображаем иконку в трее
    systemTray->show();
}

// Установка значений в QRadioButton для помощи
void MainWindow::wordHelpTest(QString word)
{
    QTextEdit *temp = new QTextEdit(word, this);
    word = temp->toPlainText();
    delete temp;

    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());// Разный старт qrand

    QStringList templist;

    while(true)  // Если совпадает с word
    {
        templist.clear();
        templist << wordConversion(baseWord.at(qrand()%(baseWord.size()-1)));   // Случайное число в перделах размера baseWord
        templist << wordConversion(baseWord.at(qrand()%(baseWord.size()-1)));   // Случайное число в перделах размера baseWord

        if(!templist.contains(wordConversion(word)))
            break;
    }

    templist << wordConversion(word);

    int one = 0;
    int two = 1;
    int three = 2;

    for(int i = 0; one!=-1 || two!=-1 || three!=-1;)
    {
        int tempqrand = qrand()%3;

        if(one == tempqrand)
        {
            one = -1;
            oneRadioStr = templist.at(i);
            i++;
        }
        else if(two == tempqrand)
        {
            two = -1;
            twoRadioStr = templist.at(i);
            i++;
        }
        else if(three == tempqrand)
        {
            three = -1;
            threeRadioStr = templist.at(i);
            i++;
        }
    }

    oneRadio->setText(oneRadioStr);                     // При подсказке выбор варианта ответа
    twoRadio->setText(twoRadioStr);                     // При подсказке выбор варианта ответа
    threeRadio->setText(threeRadioStr);                 // При подсказке выбор варианта ответа

    oneRadio->click();
}

// Установка языка
void MainWindow::setupLanguageProgramm()
{
    QDir dir("language");                       // Создаем Qdir в папке dic

    QStringList filters;                        // Устанавливаем фильтры
    filters << "*.language";                    // Устанавливаем фильтры
    dir.setNameFilters(filters);                // Устанавливаем фильтры

    QFileInfoList list = dir.entryInfoList();   // Чтение инфо о файлах

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);        // Получим доступ к имени

        QFile read_file("language/" + fileInfo.fileName().toAscii()); // Открываем перевод

        if(read_file.open(QIODevice::ReadOnly)) // чтение язык перевода
        {
            QTextStream out(&read_file);
            out.setCodec("UTF-8");          // Установка кодека
            listLanguage[out.readLine().remove("id=")] = fileInfo.fileName();       // Считываем первую строку с именем
        }
    }

    QMap<QString,QString>::iterator it = listLanguage.begin();

    for(; it != listLanguage.end(); ++it)
    {
        setupLanguageComboBox->addItem(it.key());
    }
}

// Проверка/запись статистики
void MainWindow::StatisticsFunction(QStringList list)
{
    answerTrue->clear();

    if(!statistics.isEmpty())
    {
        for(int i = 0; i<learn_word.size(); i++)
        {
            bool BL = true;
            QMap <QString,QString>::iterator it = statistics.begin();

            for(; it != statistics.end(); ++it)
            {
                if(it.key() == learn_word.at(i))
                {
                    answerTrue->addItem(it.value());
                    BL = false;
                }
            }

            if(BL)
            {
                answerTrue->addItem("0");
            }

            if(i%2)
            {
                answerTrue->item(i)->setBackgroundColor(QColor(187, 255, 255));
            }
        }
    }
    else
    {
        if(!list.isEmpty())
        {
            for(int i=0; i<list.size(); i++)
            {
                answerTrue->addItem("0");

                if(i%2)
                {
                    answerTrue->item(i)->setBackgroundColor(QColor(187, 255, 255));
                }
            }
        }
    }
}

// Запись статистики при правильно введенном слове
void MainWindow::trueInputWord(QString str)
{
    QTextEdit *temp = new QTextEdit(str, this);
    str = temp->toPlainText();
    delete temp;

    qDebug() << str;

    if(statistics.isEmpty())
    {
        statistics[str] = "1";
    }
    else
    {
        bool BL = true;

        QMap <QString, QString>::iterator it = statistics.begin();

        for(; it != statistics.end(); ++it)
        {
            if(it.key() == str)
            {
                QString tempstr = it.value();
                int tempint = tempstr.toInt();
                tempint++;
                it.value() = QString::number(tempint,10);
                BL = false;
                break;
            }
        }

        if(BL)
        {
            statistics[str] = "1";
        }
    }

    StatisticsFunction(learn_word);
}

// Конец загрузки приложения
void MainWindow::downloadoff()
{
    dial->setValue(100);
    dial->setVisible(false);
}
