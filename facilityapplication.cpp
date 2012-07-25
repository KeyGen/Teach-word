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

    qDebug() << dir.mkdir("tempdir");   // Создаем временную папку

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
    connect(dicInput,SIGNAL(activated(QString)),this,SLOT(actionDict(QString)));
    connect(findWord,SIGNAL(textChanged(QString)),this,SLOT(slotFindWord(QString)));

    connect(transferWord,SIGNAL(anchorClicked(QUrl)), findWord,SLOT(clear()));
    connect(transferWord,SIGNAL(anchorClicked(QUrl)), this,SLOT(slotFindWordUrl(QUrl)));
    connect(ListBase,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotInputWordInFindWord(QModelIndex)));
    connect(ListLearnWords,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotInputWordInFindWord(QModelIndex)));

    connect(oneRadio, SIGNAL(clicked()),this,SLOT(slotRadioButtonClick()));
    connect(twoRadio, SIGNAL(clicked()),this,SLOT(slotRadioButtonClick()));
    connect(threeRadio, SIGNAL(clicked()),this,SLOT(slotRadioButtonClick()));
}

// Чтение настроек
void MainWindow::ReadSetting()
{
    QString dicSave = "Biology (En-Ru)";

    // Установка словаря
    this->actionDict(dicSave);
    dicInput->setCurrentIndex(dicInput->findText(dicSave));
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
void MainWindow::addLearnWords()
{
    //qDebug() << "Количество слов в словаре: " << baseWord.count();


    if(!learn_word.contains(ListBase->item(ListBase->currentRow())->text()))
    {
        learn_word << ListBase->item(ListBase->currentRow())->text();

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
        showMassage("<center><br>Cлово<br>" + ListBase->item(ListBase->currentRow())->text() + "<br>уже добавленно</center>", "true");
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
            showMassage("<center><br>Выберите слово для удаления</center>", "true");
        else
            showMassage("<center><br>Список изучаемых слов пуст!<br><br>Удалять нечего!</center>", "true");
    }
}

// Форма для сообщения общается с qml
bool MainWindow::showMassage(QString text, QString button)
{
    showmessage->show();
    showmessage->activationQml(text, button);

    connect(showmessage, SIGNAL(signalMove(QPoint)),this,SLOT(setNewMove(QPoint)));

    QPixmap px = QPixmap::grabWindow(QApplication::desktop()->winId()); // получаем картинку

    showmessage->setBackground(px.copy(this->pos().x(),this->pos().y(),this->width(),this->height()));

    return true;
}

// Срабатывает при навидении на кнопку показывает подсказку
void MainWindow::helpButton(QString text,int x, int y)
{
    QToolTip::showText(QPoint(this->pos().x() + x, this->pos().y() + y),text,this,QRect(0,0,100,30));
}

// Проверка/запись статистики
void MainWindow::StatisticsFunction(QStringList list)
{
    if(!statistics.isEmpty())
    {
        //statistics[ListBase->item(ListBase->currentRow())->text()] = 0;
        //QMap<QVariant,QVariant>::iterator it = statistics.begin();
    }
    else
    {
        if(!list.isEmpty())
        {
            answerTrue->clear();
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
    if(str != strinput)
    {
        setWords(); // Функция регулирует вывод изучаемых слов на qml из learn_word
        return true;
    }
    else
        return false;
}

// Функция регулирует вывод изучаемых слов на qml из learn_word
void MainWindow::setWords()
{
    QObject *rectBLTwo = Root->findChild<QObject*>("show_" + QString::number(8,10));

    if(rectBLTwo->property("textShow").toString().isEmpty())
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

    rect = Root->findChild<QObject*>("messageText");
    rect->setProperty("text", "<center>Выберите правильный вариант:</center>");

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
