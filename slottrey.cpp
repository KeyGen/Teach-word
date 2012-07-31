#include "mainwindow.h"

// Вызов настроек из трея
void MainWindow::slotTreySetting()
{
    slotTreyShow();

    Root->setProperty("state","shift");
}

// Включить/выключить звук из трея
void MainWindow::slotTreySound(bool BL)
{
    qDebug() << "Sound " << BL;
}

// Вызов помощи из трея
void MainWindow::slotTreyHelp()
{
    openUrlHelp();
}

// Вызов информации о программе из трея
void MainWindow::slotTreyInfo()
{
    slotTreyShow();
    Root->setProperty("state","shiftInfo");
}

// Показать программу из трея
void MainWindow::slotTreyShow()
{
    if(!this->isVisible())      // если скрыта программа
    {
        this->slotTimeOut(); // отображает
    }
}

// Скрыть программу из трея
void MainWindow::slotTreyMask()
{
    if(this->isVisible())      // если отображена программа
    {
        this->setVisible(false); // скрывает
        timerShow->start();
    }
}

// Закрыть программу из трея
void MainWindow::slotTreyClose()
{
    this->close(); // Завершает выполнение программы
    showmessage->close();
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
