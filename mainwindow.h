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
#include <QDir>
#include <QRadioButton>
#include "showmessage.h"
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
    Q_INVOKABLE bool inputShowWords(QString, QString);              // Установка слов в qml / проверка правильности введенного ответа
    Q_INVOKABLE void showObjectdicInputanddicInfo();                // Показать/скрыть dicInput и dicInfo
    Q_INVOKABLE void addLearnWords();                               // Добавление слова из базы для обучения
    Q_INVOKABLE void clearLearnWords();                             // Очистка слов для обучения
    Q_INVOKABLE void deleteWord();                                  // Удаление выделенного слова из изучаемых слов

    Q_INVOKABLE bool showMassage(QString text = "On text", QString button = "true, false");     // Форма для сообщения общается с qml
    Q_INVOKABLE void helpButton(QString text, int, int); // Срабатывает при навидении на кнопку показывает подсказку
    Q_INVOKABLE void setShowOnDefault();    // Функция устанавливает пумолчанию главное окно программы
    Q_INVOKABLE int controlSize();         // Функция проверяет сколько загружено слов для обучения (минимум 5)
    Q_INVOKABLE void helpWord();            // Подсказка по словам
    Q_INVOKABLE void setVisibleQRadioButton(bool); // Показыват/скрывает QRadioButton
    Q_INVOKABLE void wordHelpTest(QString); // Установка значений в QRadioButton для помощи

    void showSistemsTrey(); // Отобразить системное меню

private slots:
    void treyProgrammShow(QSystemTrayIcon::ActivationReason);   // Вызывает WainWindow при клике на иконку в трее
    void actionDict(QString);                                   // Вызывает WainWindow при выборе словаря
    QString DictInHtml(QString word);                           // Поиск слова в словаре и выдется результат в html
    void slotFindWord(QString find);                            // Слот для поиска слов по загруженному словарю
    void slotFindWordUrl(QUrl);                                 // Ввод в findWord url
    void slotInputWordInFindWord(QModelIndex);                  // Слот активируется двойным щелчком по baseWord для поиска слова
    void setNewMove(QPoint);                                    // Слот перемещает MainWindow
    void slotshowMassage();                                     // При завершении урока вывод сообщения
    void slotRadioButtonClick();                                // Обрабатывает нажатие RadioButton из подсказки
    void startSoundShow();                                      // Слот активации звука при открытии программы
    void downloadLanguageProgramm(QString);                     // Загрузка перевода в программу

    void slotTreySetting();     // Вызов настроек из трея
    void slotTreySound(bool);   // Включить/выключить звук из трея
    void slotTreyHelp();        // Вызов помощи из трея
    void slotTreyInfo();        // Вызов информации о программе из трея
    void slotTreyShow();        // Показать программу из трея
    void slotTreyMask();        // Скрыть программу из трея
    void slotTreyClose();       // Закрыть программу из трея

private:
    QDeclarativeView *ui;               // Qml
    QObject *Root;                      // Корневой элемент QML модели

    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;

    ShowMessage *showmessage;           // Класс сообщения

    int save_x;                         // Сохраняет X положение MainWindow на экране
    int save_y;                         // Сохраняет Y положение MainWindow на экране

    QString activeDict;                 // Загруженный в оперативку активный словарь

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
    QListWidget *ListLearnWords;        // Обьект QListWidget предназначен для отображения слов которые будем учить
    QListWidget *ListBase;              // Обьект QListWidget предназначен для отображения словоря (базы слов для обучения)
    QLineEdit *findWord;                // Обьект QLineEdit предназначен для поиска слов по словарю
    QStringList baseWord;               // База слов по ней будем искать слова
    QStringList learn_word;             // Слова для обучения
    QTextBrowser *transferWord;         // Обьект QTextBrowser предназначен для отображения перевода слов
    QComboBox *dicInput;                // Обьект QComboBox предназначен для выбора словаря
    QTextBrowser *dicInfo;              // Обьект QTextBrowser предназначен для отображения свойств словаря
    bool fixedChanges;                  // Фиксирует были или нет изменения в learn_word (Слова для обучения)

    void SetupObjectSetup();            // Установка обьектов насторек qml
    int moveObjectSetup;                // Точка отчета позиции обьектов для настроек из Qml

    QTimeEdit *setupTime;                       // Установка времени отображения программы
    QSpinBox  *setupSinBoxInputAmountCorrect;   // Установка статистики правильных ответов
    QComboBox *setupLanguageComboBox;           // Установка языка
    Phonon::VolumeSlider *setupVolume;          // Громкость звука
    QPushButton *setupUpdate;                   // Проверка обновлений

    QRadioButton *oneRadio;                     // При подсказке выбор варианта ответа
    QRadioButton *twoRadio;                     // При подсказке выбор варианта ответа
    QRadioButton *threeRadio;                   // При подсказке выбор варианта ответа
    QString oneRadioStr;                        // Текст на QRadioButton
    QString twoRadioStr;                        // Текст на QRadioButton
    QString threeRadioStr;                      // Текст на QRadioButton

    int bootDictionary();                       // Загрузка словарей StarDict
    QMap<QString,QString> listDict;             // Запись информации и имя словоря
    QMap<QString,QString> listLanguage;         // Переводы программы
    QMap<QString,QString> downloadlanguageMap;  // Загруженный перевод
    QMap<QVariant, QVariant> statistics;        // Запись статистики первая-слово вторая-количество правильных ответов
    void StatisticsFunction(QStringList);       // Проверка/запись статистики

    bool containsWord(QString one, QString two); // Функция осуществляющая проверку на идентицность без учета регистра

    void connectObject();       // Функция для подсоединения сигналов и слотов
    QString setWidthFont(QString, int maxwidth = 100, int maxfont = 40); // Функция устанавливающая размер шрифта относительно размера окна
    void setWords(); // Функция регулирует вывод изучаемых слов на qml из learn_word

    QString wordConversion(QString word);                           // Поиск слова в словаре и выдется перевод

    void setupLanguageProgramm(); // Установка языка


    void ReadSetting();     // Чтение настроек
};

#endif // MAINWINDOW_H
