#-------------------------------------------------
#
# Project created by QtCreator 2020-05-21T11:29:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uchet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.3
#DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_LFLAGS += -static -static-libgcc
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    dbmanager.cpp \
    logindialog.cpp \
    devicetypedialog.cpp \
    addclient.cpp \
    workswidget.cpp \
    worksettings.cpp \
    workcellwidget.cpp \
    addrequestform.cpp \
    adduser.cpp \
    adddevice.cpp \
    deletecell.cpp \
    work.cpp \
    appsettings.cpp \
    newstatusform.cpp \
    statusmanager.cpp \
    statussubview.cpp \
    colorviewwidget.cpp \
    colorviewform.cpp

HEADERS += \
        mainwindow.h \
    dbmanager.h \
    logindialog.h \
    devicetypedialog.h \
    addclient.h \
    workswidget.h \
    worksettings.h \
    workcellwidget.h \
    addrequestform.h \
    adduser.h \
    adddevice.h \
    deletecell.h \
    work.h \
    appsettings.h \
    newstatusform.h \
    statusmanager.h \
    statussubview.h \
    colorviewwidget.h \
    colorviewform.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    devicetypedialog.ui \
    addclient.ui \
    workswidget.ui \
    worksettings.ui \
    workcellwidget.ui \
    addrequestform.ui \
    adduser.ui \
    adddevice.ui \
    deletecell.ui \
    work.ui \
    newstatusform.ui \
    statusmanager.ui \
    statussubview.ui \
    colorviewform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    styles.qss
