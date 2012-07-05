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

#include <phonon>
using namespace Phonon;

namespace Ui {
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

    // Р’С‹Р·С‹РІР°РµС‚СЃС‚СЏ РёР· qml
    Q_INVOKABLE void exec_dialog_setting();
    Q_INVOKABLE void exec_dialog_input();
    Q_INVOKABLE void exec_dialog_info();
    Q_INVOKABLE void execStyle();
    Q_INVOKABLE void exitProgramm();
    Q_INVOKABLE void maskProgramm();
    Q_INVOKABLE void helpProgramm();

    // Р—Р°РїСѓСЃРєР°РµРј Р·РІСѓРє РёР· qml
    Q_INVOKABLE void startSoundError();
    Q_INVOKABLE void startSoundButton();
    Q_INVOKABLE void startSoundShow();

    Q_INVOKABLE void move_window(); //Р¤СѓРЅРєС†РёСЏ C++ РІС‹Р·С‹РІР°РµРјР°СЏ РёР· QML РїСЂРµРјРµС‰Р°СЋС‰РёРµ РѕРєРЅРѕ
    Q_INVOKABLE void cursor_up(); //Р¤СѓРЅРєС†РёСЏ C++ РІС‹Р·С‹РІР°РµРјР°СЏ РёР· QML РёР·РјРµРЅСЏСЋС‰РёРµ РєСѓСЂСЃРѕСЂ
    Q_INVOKABLE void cursor_down(); //Р¤СѓРЅРєС†РёСЏ C++ РІС‹Р·С‹РІР°РµРјР°СЏ РёР· QML РёР·РјРµРЅСЏСЋС‰РёРµ РєСѓСЂСЃРѕСЂ

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
    void treyProgrammShow(QSystemTrayIcon::ActivationReason);
    void timerProgrammShow();
    void treyEdit();
    void treySetting();
    void treyStyle();
    void tryeHelp();
    void treyInfo();
    void treyMask();

    // РЎР»РѕС‚С‹ РґР»СЏ РёР·РјРµРЅРµРЅРёСЏ РіСЂР°РґРёРµРЅС‚Р°
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
    QLabel *show_word;
    QLineEdit *input_word_edit;
    QPushButton *push_help;
    QProgressBar *progress_lesson;

    Ui::Input_word *ui_input;
    Ui::Setting_programm *ui_setting;
    Ui::Info *ui_info;
    Ui::Style *ui_style;

    QDeclarativeView *ui_qml_background;
    QObject *Root_ui_qml_background; //РєРѕСЂРЅРµРІРѕР№ СЌР»РµРјРµРЅС‚ QML РјРѕРґРµР»Рё
    QDeclarativeView *ui_qml_menu;
    QObject *Root_ui_qml_menu; //РєРѕСЂРЅРµРІРѕР№ СЌР»РµРјРµРЅС‚ QML РјРѕРґРµР»Рё

    QTimeLine *timer;

    MediaObject *mediaObject;
    AudioOutput *audioOutput;

    bool BL_move;
    int save_x;
    int save_y;

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
    bool BL_help_apply; // Р¤РёРєСЃРёСЂСѓРµС‚ РїРѕР»СЊР·РѕРІР°Р»РёСЃСЊ Р»Рё РїРѕРґСЃРєР°Р·РєРѕР№
    bool BLsound; // Р’С‹РєР»СЋС‡Р°РµС‚/РІРєР»СЋС‡Р°РµС‚ Р·РІСѓРє
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
