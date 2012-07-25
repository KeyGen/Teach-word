#include "mainwindow.h"

// Вызывает WainWindow при выборе словаря
void MainWindow::actionDict(QString str)
{
    QMap<QString,QString>::iterator it = listDict.begin();

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

            QFile openDict("dic/tempdir/" + it.value().toAscii()); // Загружаем словарь

            if(openDict.open(QIODevice::ReadOnly)) // чтение словаря
            {
                QTextStream out(&openDict);
                out.setCodec("UTF-8");          // Установка кодека
                activeDict = out.readAll();       // Считываем весь файл в QString
            }

            activeDict.replace("&apos;", "\'"); // Уберем thml замашки

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

             ListBase->addItems(baseWord);
             ListBase->setCurrentRow(0);

             for(int i=0; i<ListBase->count(); i++)
             {
                 if(i%2)
                 {
                     ListBase->item(i)->setBackgroundColor(QColor(187, 255, 255));
                 }
             }

            break;
        }
    }
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
