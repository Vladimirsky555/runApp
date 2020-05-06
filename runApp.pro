#-------------------------------------------------
#
# Project created by QtCreator 2018-12-06T17:22:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0
QMAKE_TARGET_COMPANY = Parkrun Tula Limited
QMAKE_TARGET_PRODUCT = Calculator
QMAKE_TARGET_DESCRIPTION = Parkran calculator
QMAKE_TARGET_COPYRIGHT = Parkrun Tula Limited

TARGET = runApp
TEMPLATE = app

win32: RC_ICONS = $$PWD/bin/images/parkrun.ico


SOURCES += main.cpp\
        mainwindow.cpp \
    formitem.cpp \
    formwindow.cpp

HEADERS  += mainwindow.h \
    formitem.h \
    formwindow.h

FORMS    += mainwindow.ui \
    formitem.ui \
    formwindow.ui
