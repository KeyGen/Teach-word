#-------------------------------------------------
#
# Project created by QtCreator 2012-07-10T12:01:14
#
#-------------------------------------------------

QT       += core gui declarative phonon

TARGET = Learn-words
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    facilityapplication.cpp \
    qzip/qzip.cpp \
    slotapplication.cpp

HEADERS  += mainwindow.h

RESOURCES += \
    files.qrc

OTHER_FILES += \
    main.qml \
    Quit.qml \
    Show_words.qml \
    TextInputQml.qml \
    Down.qml \
    Setting.qml \
    Help_word.qml \
    Back.qml \
    Button_setting.qml \
    SaveSetting.qml \
    RectagleInfo.qml \
    RectangleSetting.qml

#INCLUDEPATH += $$[QT_INSTALL_PREFIX]/src/3rdparty/zlib
