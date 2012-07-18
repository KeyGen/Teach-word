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


            ListBase->clear();
            QRegExp rx("<k>([^<]*)<\/k>");
            rx.setMinimal(true);

             int pos = 0;
             while ((pos = rx.indexIn(activeDict, pos)) != -1)
             {
                 ListBase->addItem(rx.cap(1));
                 pos += rx.matchedLength();
             }

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
