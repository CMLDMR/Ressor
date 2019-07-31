#-------------------------------------------------
#
# Project created by QtCreator 2019-07-31T22:49:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ressor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        base/dbclass.cpp \
        main.cpp \
        mainwindow.cpp \
        stok/base/stokkart.cpp \
        stok/stokkartdialog.cpp \
        stok/stokmaindialog.cpp \
        stok/yenistokkartdialog.cpp

HEADERS += \
        base/dbclass.h \
        mainwindow.h \
        mongoheaders.h \
        stok/base/stokkart.h \
        stok/stokkartdialog.h \
        stok/stokmaindialog.h \
        stok/yenistokkartdialog.h

FORMS += \
        mainwindow.ui \
        stok/stokkartdialog.ui \
        stok/stokmaindialog.ui \
        stok/yenistokkartdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




win32: LIBS += -L$$PWD/libmongodb/lib/ -lbsoncxx

INCLUDEPATH += $$PWD/libmongodb/include/bsoncxx/v_noabi
DEPENDPATH += $$PWD/libmongodb/include/bsoncxx/v_noabi



win32: LIBS += -L$$PWD/libmongodb/lib/ -lmongocxx

INCLUDEPATH += $$PWD/libmongodb/include/mongocxx/v_noabi
DEPENDPATH += $$PWD/libmongodb/include/mongocxx/v_noabi




INCLUDEPATH += $$PWD/../../../../../local/boost_1_70_0
DEPENDPATH += $$PWD/../../../../../local/boost_1_70_0
