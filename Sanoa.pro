#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T02:30:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sanoa
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGSD
DEFINES += PROJECT_DIRECTORY=\\\"$$PWD\\\"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    adddevice.cpp \
    devicepage.cpp \
    mtpdevicepage.cpp \
    standarddevicepage.cpp \
    devicetreewidget.cpp \
    musictagmodel.cpp \
    musictagitem.cpp

HEADERS += \
        mainwindow.h \
    adddevice.h \
    devicepage.h \
    defines.h \
    mtpdevicepage.h \
    standarddevicepage.h \
    devicetreewidget.h \
    musictagmodel.h \
    musictagitem.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    LICENSE \
    readme.md \
    THANKS \
    translations/Sanoa_ja.ts

macx{
INCLUDEPATH += /usr/local/Cellar/libmtp/1.1.15/include/ \
    /usr/local/Cellar/taglib/1.11.1/include/
LIBS += -L/usr/local/Cellar/libmtp/1.1.15/lib/ -lmtp \
    -L/usr/local/Cellar/taglib/1.11.1/lib/ -ltag
}

TRANSLATIONS = translations/Sanoa_ja.ts
