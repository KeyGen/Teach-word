#include "mainwindow.h"
#include <QCoreApplication>
#include <QApplication>

// Вызывает WainWindow при выборе словаря
void MainWindow::actionDict(QString str)
{
    dicSave = str;

    QMap<QString,QString>::iterator it = listDict.begin();

    progressdownloaddic->setVisible(true); // Это QProgressBar по идее должен отобразиться а его нет

    bool BL = false;
    if(dicInput->isVisible())
    {
        dicInput->setVisible(false);
        BL = true;
    }

    progressdownloaddic->setValue(0);
    QApplication::processEvents(); // Обновим приложение

    // Загрузка словоря stardict
    for(; it != listDict.end(); ++it)
    {
        if(it.key().contains(str))
        {

            QString htmlValue;

            htmlValue += "<br>";

            if(str.size()<=22)
                htmlValue += "<center><b><span style=\"color:#000074; font-size:13pt;\">" + str + "</span></b><br>";
            else
                htmlValue += "<center><b><span style=\"color:#000074;\">" + str + "</span></b><br>";

            htmlValue += "<br>";

            htmlValue += "<b><span style=\"color:#000074;\">версия: </span></b>";
            for(int i = it.key().lastIndexOf("version=") + 8; it.key().at(i)!='\n'; i++)
            htmlValue += it.key().at(i);

            htmlValue += "<br>";

            htmlValue += "<b><span style=\"color:#000074;\">количество слов: </span></b>";
            for(int i = it.key().lastIndexOf("wordcount=") + 10; it.key().at(i)!='\n'; i++)
            htmlValue += it.key().at(i);

            htmlValue += "<br>";

            htmlValue += "<b><span style=\"color:#000074;\">дата: </span></b>";
            for(int i = it.key().lastIndexOf("date=") + 5; it.key().at(i)!='\n'; i++)
            htmlValue += it.key().at(i);

            htmlValue += "</center>";

            dicInfo->setText(htmlValue);

            progressdownloaddic->setValue(progressdownloaddic->value() + 10);
            QApplication::processEvents(); // Обновим приложение

            QFile openDict("dic/tempdir/" + it.value().toAscii()); // Загружаем словарь

            if(openDict.open(QIODevice::ReadOnly)) // чтение словаря
            {
                QTextStream out(&openDict);
                out.setCodec("UTF-8");          // Установка кодека
                activeDict = out.readAll();       // Считываем весь файл в QString
            }

            activeDict.replace("&apos;", "\'"); // Уберем html замашки
            activeDict.replace("&quot;", "");   // Уберем html замашки
            activeDict.replace("&amp;", "&");

            progressdownloaddic->setValue(progressdownloaddic->value() + 10);
            QApplication::processEvents(); // Обновим приложение

            ListBase->clear();
            baseWord.clear();
            findWord->clear();
            transferWord->clear();


            QRegExp rx("<k>([^<]*)<\/k>");
            rx.setMinimal(true);

             int pos = 0;
             while ((pos = rx.indexIn(activeDict, pos)) != -1)
             {
                 baseWord << rx.cap(1);
                 pos += rx.matchedLength();
             }

             progressdownloaddic->setValue(progressdownloaddic->value() + 10);
             QApplication::processEvents(); // Обновим приложение
             int tempint = baseWord.size()/4;

             for(int i=0; i<baseWord.size(); i++)
             {
                 ListBase->addItem(baseWord.at(i));

                 if(!(i%tempint)&&i!=0)
                 {
                     if(progressdownloaddic->value()<60)
                     {
                         progressdownloaddic->setValue(progressdownloaddic->value() + 10);
                         QApplication::processEvents(); // Обновим приложение
                     }
                 }
             }

             ListBase->setCurrentRow(0);

             for(int i=0; i<ListBase->count(); i++)
             {
                 if(i%2)
                 {
                     ListBase->item(i)->setBackgroundColor(QColor(187, 255, 255));
                 }

                 if(!(i%tempint)&&i!=0)
                 {
                     if(progressdownloaddic->value()<100)
                     {
                         progressdownloaddic->setValue(progressdownloaddic->value() + 10);
                         QApplication::processEvents(); // Обновим приложение
                     }
                 }
             }

             progressdownloaddic->setValue(100);


            break;
        }
    }

    progressdownloaddic->setVisible(false); // Теперь должен скрыть QProgressBar

    if(BL)
    {
        dicInput->setVisible(true);
    }

    progressdownloaddic->setValue(0);
}

// Слот для поиска слов по загруженному словарю
void MainWindow::slotFindWord(QString find)
{
    if(!find.isEmpty())
    {
        int i;

        for(i = 0; i<baseWord.size(); i++)
        {
            if(baseWord.at(i).left(find.size()).contains(find, Qt::CaseInsensitive))
            {
                transferWord->setText(DictInHtml(baseWord.at(i)));

                ListBase->setCurrentRow(i+7);
                ListBase->setCurrentRow(i);

                break;
            }
        }
    }
    else
    {
        ListBase->setCurrentRow(0);
        transferWord->clear();
    }
}

// Ввод в findWord url
void MainWindow::slotFindWordUrl(QUrl url)
{
    QString temp;
    temp = url.toString();

    temp.replace("-----------", " ");

    findWord->setText(temp);
}

// Слот активируется двойным щелчком по baseWord для поиска слова
void MainWindow::slotInputWordInFindWord(QModelIndex model)
{
    findWord->clear();
    findWord->setText(model.data().toString());
}

// Слот перемещает MainWindow
void MainWindow::setNewMove(QPoint point)
{
    this->move(point);
}

// При завершении урока вывод сообщения
void MainWindow::slotshowMassage()
{
    showMassage("<br>Вы закончили урок<br><br>Выберите ваши дальнейшее действие", "true");
}

// Обрабатывает нажатие RadioButton из подсказки
void MainWindow::slotRadioButtonClick()
{
    QObject *rect = Root->findChild<QObject*>("textInput");

    if(oneRadio->isChecked())
    {
        rect->setProperty("text", oneRadioStr);
    }
    else if(twoRadio->isChecked())
    {
        rect->setProperty("text", twoRadioStr);
    }
    else if(threeRadio->isChecked())
    {
        rect->setProperty("text", threeRadioStr);
    }
}

// Слот активации звука при открытии программы
void MainWindow::startSoundShow()
{
    mediaObject->setCurrentSource(Phonon::MediaSource(":/sound/error"));

    mediaObject->play();
}

// Загрузка перевода в программу
void MainWindow::downloadLanguageProgramm(QString language)
{
    languageSave = language;

    if(!listLanguage.isEmpty())
    {
        QFile read_file("language/" + listLanguage[language].toAscii()); // Открываем перевод
        QString downloadlanguage;

        if(read_file.open(QIODevice::ReadOnly)) // чтение язык перевода
        {
            QTextStream out(&read_file);
            out.setCodec("UTF-8");          // Установка кодека
            downloadlanguage = out.readAll();
        }

        /////////////////////////////////////// objectTextStart
        QString tempstr;
        for(int i = downloadlanguage.indexOf("start="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("start=");

        QObject *rect = Root->findChild<QObject*>("objectTextStart");
        rect->setProperty("text", tempstr);

        /////////////////////////////////////// objectTextInfoLanguage
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("installationlanguage="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("installationlanguage=");

        rect = Root->findChild<QObject*>("objectTextInfoLanguage");
        rect->setProperty("text", tempstr);

        /////////////////////////////////////// objectTextInfoSound
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("installationsound="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("installationsound=");

        rect = Root->findChild<QObject*>("objectTextInfoSound");
        rect->setProperty("text", tempstr);

        /////////////////////////////////////// objectTextInfoTimer
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("installationtimer="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("installationtimer=");

        rect = Root->findChild<QObject*>("objectTextInfoTimer");
        rect->setProperty("text", tempstr);

        /////////////////////////////////////// objectTextInfoLearn
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("installationstatic="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("installationstatic=");

        rect = Root->findChild<QObject*>("objectTextInfoLearn");
        rect->setProperty("text", tempstr);

        /////////////////////////////////////// objectTextInfoRecresh
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("installationreload="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("installationreload=");

        rect = Root->findChild<QObject*>("objectTextInfoRecresh");
        rect->setProperty("text", tempstr);

        /////////////////////////////////////// objectTextInfo
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("infoprogramm="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("infoprogramm=");

        rect = Root->findChild<QObject*>("objectTextInfo");
        rect->setProperty("text", tempstr);

        /////////////////////////////////////// settingone
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("settingone="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("settingone=");

        rect = Root->findChild<QObject*>("settingone");
        rect->setProperty("textButton", tempstr);

        /////////////////////////////////////// settingtwo
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("settingtwo="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("settingtwo=");

        rect = Root->findChild<QObject*>("settingtwo");
        rect->setProperty("textButton", tempstr);

        /////////////////////////////////////// settingthree
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("settingthree="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("settingthree=");

        rect = Root->findChild<QObject*>("settingthree");
        rect->setProperty("textButton", tempstr);

        /////////////////////////////////////// settingfour
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("settingfour="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("settingfour=");

        rect = Root->findChild<QObject*>("settingfour");
        rect->setProperty("textButton", tempstr);

        /////////////////////////////////////// messageText
        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helptest="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helptest=");

        rect = Root->findChild<QObject*>("messageText");
        rect->setProperty("text", tempstr);

        ///////////////////////////////////////

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpsetting="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpsetting=");
        downloadlanguageMap["helpsetting="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpsettingtwo="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpsettingtwo=");
        downloadlanguageMap["helpsettingtwo="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helphelp="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helphelp=");
        downloadlanguageMap["helphelp="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpmask="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpmask=");
        downloadlanguageMap["helpmask="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpclose="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpclose=");
        downloadlanguageMap["helpclose="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpback="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpback=");
        downloadlanguageMap["helpback="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpclear="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpclear=");
        downloadlanguageMap["helpclear="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helptranslate="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helptranslate=");
        downloadlanguageMap["helptranslate="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpdictionary="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpdictionary=");
        downloadlanguageMap["helpdictionary="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpaddword="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpaddword=");
        downloadlanguageMap["helpaddword="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpdelword="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpdelword=");
        downloadlanguageMap["helpdelword="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("helpsave="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("helpsave=");
        downloadlanguageMap["helpsave="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("infostatic="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("infostatic=");
        downloadlanguageMap["infostatic="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("infolearnlist="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("infolearnlist=");
        downloadlanguageMap["infolearnlist="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("infobasedictionary="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("infobasedictionary=");
        downloadlanguageMap["infobasedictionary="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("infominimumsize="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("infominimumsize=");
        downloadlanguageMap["infominimumsize="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("buttonupdate="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("buttonupdate=");
        setupUpdate->setText(tempstr);

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("wordinsight="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("wordinsight=");
        downloadlanguageMap["wordinsight="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("wordadddelete="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("wordadddelete=");
        downloadlanguageMap["wordadddelete="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("worddeleteclear="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("worddeleteclear=");
        downloadlanguageMap["worddeleteclear="] = tempstr;

        tempstr.clear();
        for(int i = downloadlanguage.indexOf("wordinput="); downloadlanguage.at(i) != '\n'; i++) tempstr += downloadlanguage.at(i);
        tempstr.remove("wordinput=");
        downloadlanguageMap["wordinput="] = tempstr;

        QMap <QString, QString>::iterator it = listLanguage.begin();
        int i = 0;

        for(;it != listLanguage.end(); ++it, ++i)
        {
            if(it.key() == language)
                break;
        }

        setupLanguageComboBox->setCurrentIndex(i);
    }
}

// Установка появления программы
void MainWindow::setTimeShow(QTime newtime)
{
    timeShow = newtime;
}

// Установка При какой записи статистики слово считать выученным
void MainWindow::setAnswerTrue(int newint)
{
    answerTrueGeneral = newint;
}

// Установка громкости звука
void MainWindow::setSoundValue()
{

}

// Проверка обновлений
void MainWindow::verifyupdate()
{
    qDebug() << "Проверить обновления";
}
