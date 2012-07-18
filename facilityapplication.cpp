#include "mainwindow.h"
#include "qzip/qzipreader_p.h"
#include "qzip/qzipwriter_p.h"

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
    connect(ListBase,SIGNAL(currentTextChanged(QString)), findWord,SLOT(clear()));
    connect(ListBase,SIGNAL(currentTextChanged(QString)), findWord,SLOT(setText(QString)));
}

// Чтение настроек
void MainWindow::ReadSetting()
{
    QString dicSave = "LingvoComputer (En-Ru)";

    // Установка словаря
    this->actionDict(dicSave);
    dicInput->setCurrentIndex(dicInput->findText(dicSave));
}

// Поиск слова в словаре и выдется результат в html
QString MainWindow::DictInHtml(QString word)
{

}
