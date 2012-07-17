#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <QSystemTrayIcon>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QListWidget>
#include <QTimeEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <phonon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Q_INVOKABLE void quit();                    // Функция C++ вызываемая из QML для завершения работы приложения
    Q_INVOKABLE void move_window();             // Функция C++ вызываемая из QML премещающие окно
    Q_INVOKABLE void cursor_up();               // Функция C++ вызываемая из QML изменяющие вид курсора
    Q_INVOKABLE void cursor_down();             // Функция C++ вызываемая из QML возвращающия вид курсора в первоначальное состояние

    Q_INVOKABLE void maskProgramm();            // Функция C++ вызываемая из QML для скрытия MainWindow
    Q_INVOKABLE void moveInputWords(int);       // Функция C++ вызываемая из QML для перемещания обьектов редактора уроков обучения
    Q_INVOKABLE void moveSetup(int);            // Функция C++ вызываемая из QML для перемещания обьектов настроек
    Q_INVOKABLE void openUrlHelp();             // Функция C++ вызываемая из QML запускает справку по адресу url

    Q_INVOKABLE void setVisibleObjectsetupLanguageComboBox(bool);   // Показать/скрыть setupLanguageComboBox
    Q_INVOKABLE void setVisibleObjectsetupTime(bool);               // Показать/скрыть setupTime
    Q_INVOKABLE void setVisibleObjectsetupSinBoxInputAmountCorrect(bool); // Показать/скрыть setupSinBoxInputAmountCorrect
    Q_INVOKABLE void setVisibleObjectsetupVolume(bool);             // Показать/скрыть setupVolume
    Q_INVOKABLE void setVisibleObjectsetupUpdate(bool);             // Показать/скрыть setupUpdate
    Q_INVOKABLE void setVisibleObjectLernWord();                    // Показывает/скрывает findWord transferWord

    Q_INVOKABLE bool inputShowWords(QString, QString); // Установка слов в qml / проверка правильности введенного ответа

private slots:
    void treyProgrammShow(QSystemTrayIcon::ActivationReason); // Вызывает WainWindow при клике на иконку в трее

private:
    QDeclarativeView *ui;               // Qml
    QObject *Root;                      // Корневой элемент QML модели

    bool BL_move;                       // Нужна для правильного перемещения мышкой MainWindow
    int save_x;                         // Сохраняет X положение MainWindow на экране
    int save_y;                         // Сохраняет Y положение MainWindow на экране
    QStringList learn_word;             // Слова для обучения

    void setRoundedCorners(int,int,int,int); // Функция закругляет углы MainWindow

    QSystemTrayIcon *systemTray;        // Трей
    QMenu *menuTrey;                    // Меню для трея
    QAction *actionTreyClose;           // Актион выхода
    QAction *actionTreySound;           // Актион включает/выключает звук
    QAction *actionTreyHelp;            // Справка находиться на сайте
    QAction *actionTreyInfo;            // Актион включающий информацию о программе
    QAction *actionTreySetting;         // Актион включающий настройки
    QAction *actionTreyShow;            // Актион отображающий MainWindow
    QAction *actionTreyMask;            // Актион скрывающий MainWindow

    void SetupLautWordsInput();         // Установка обьектов для редактора уроков
    int moveLautWordsInput;             // Точка отчета позиции обьектов для установки уроков из Qml
    QListWidget *answerTrue;            // Обьект QListWidget предназначен для отображения статистики правильных ответов
    QListWidget *LestLearnWords;        // Обьект QListWidget предназначен для отображения слов которые будем учить
    QListWidget *ListBase;              // Обьект QListWidget предназначен для отображения словоря (базы слов для обучения)
    QLineEdit *findWord;                // Обьект QLineEdit предназначен для поиска слов по словарю
    QTextBrowser *transferWord;         // Обьект QTextBrowser предназначен для отображения перевода слов

    void SetupObjectSetup();            // Установка обьектов насторек qml
    int moveObjectSetup;                // Точка отчета позиции обьектов для настроек из Qml

    QTimeEdit *setupTime;                       // Установка времени отображения программы
    QSpinBox  *setupSinBoxInputAmountCorrect;   // Установка статистики правильных ответов
    QComboBox *setupLanguageComboBox;           // Установка языка
    Phonon::VolumeSlider   *setupVolume;        // Громкость звука
    QPushButton *setupUpdate;                   // Проверка обновлений

    void bootDictionary();                      // Загрузка словарей StarDict

};

#endif // MAINWINDOW_H
