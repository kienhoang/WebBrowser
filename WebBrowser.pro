#-------------------------------------------------
#
# Project created by QtCreator 2015-09-08T17:54:55
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebBrowser
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    settingdialog.cpp

HEADERS  += mainwindow.h \
    settingdialog.h

FORMS    += mainwindow.ui \
    settingdialog.ui

RESOURCES +=

DISTFILES += \
    ico.rc

RC_FILE = ico.rc
