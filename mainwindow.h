#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>
#include <QTime>
#include <QSystemTrayIcon>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QtGui>

namespace Ui {
class MainWindow;
class Setting_programm;
class Input_word;
class Info;
class Style;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Вызываетстя из qml
    Q_INVOKABLE void exec_dialog_setting();
    Q_INVOKABLE void exec_dialog_input();
    Q_INVOKABLE void exec_dialog_info();
    Q_INVOKABLE void execStyle();
    Q_INVOKABLE void exitProgramm();
    Q_INVOKABLE void maskProgramm();
    Q_INVOKABLE void helpProgramm();

private slots:
    void setCurrnetRow_list_rus(int);
    void setCurrnetRow_list_eng(int);
    void setCurrnetRow_list_base(int);
    void setCurrnetRow_list_teach(int);
    bool addWord();
    void deleteWord();
    void setBaseWordEng();
    void setBaseWordRus();
    void inputWordTeach();
    void reductionSizeListTeach(int);
    void showTranslation(QString str);
    void closeDialogSetting();
    void settingSaveTrue();
    void deleteWordTeach();
    void returnPressedInputWord();
    void pushHelp();

    // slot for trey action
    void treyProgrammShow();
    void treyEdit();
    void treySetting();
    void treyStyle();
    void tryeHelp();
    void treyInfo();
    void treyMask();

    // Слоты для изменения градиента
    void sliderPositionOne(int);
    void sliderPositionTwo(int);
    void sliderPositionThree(int);

    void sliderColorOneR(int);
    void sliderColorOneG(int);
    void sliderColorOneB(int);

    void sliderColorTwoR(int);
    void sliderColorTwoG(int);
    void sliderColorTwoB(int);

    void sliderColorThreeR(int);
    void sliderColorThreeG(int);
    void sliderColorThreeB(int);

    void temp(int);
    
private:
    Ui::MainWindow *ui;
    Ui::Input_word *ui_input;
    Ui::Setting_programm *ui_setting;
    Ui::Info *ui_info;
    Ui::Style *ui_style;

    QDeclarativeView *ui_qml_background;
    QObject *Root_ui_qml_background; //корневой элемент QML модели
    QDeclarativeView *ui_qml_menu;
    QObject *Root_ui_qml_menu; //корневой элемент QML модели

    QTimeLine *timer;

    QSystemTrayIcon *systemTray;
    QMenu *menuTrey;
    QAction *actionTreyClose;
    QAction *actionTreyEdit;
    QAction *actionTreyHelp;
    QAction *actionTreyInfo;
    QAction *actionTreySetting;
    QAction *actionTreyStyle;
    QAction *actionTreyMask;

    QDialog *dialog_input;
    QDialog *dialog_setting;
    QDialog *dialog_info;
    QDialog *dialog_style;

    QColor colorGradientOne;
    QColor colorGradientTwo;
    QColor colorGradientThree;
    double positionGradientOne;
    double positionGradientTwo;
    double positionGradientTree;


    int chopHelpWord;
    int saveRow;
    int saveRowTeachWord;
    int shiftWord;
    int amount_correct;
    bool demandWord;
    bool reperatWord;
    bool BL_help_apply; // Фиксирует пользовались ли подсказкой
    int whatAmountWord;
    QTime saveTime;

    QSettings settings;
    QStringList ang_word;
    QStringList rus_word;
    QStringList teach_word;
    QStringList temp_teach_word;
    QList<QVariant> statistics_word;

    void installQml();
    void writeSetting();
    void readSetting();
};

#endif // MAINWINDOW_H
