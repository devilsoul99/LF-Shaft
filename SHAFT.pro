#-------------------------------------------------
#
# Project created by QtCreator 2014-06-13T14:40:42
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Shaft
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    intro.cpp \
    platform.cpp \
    pf_normal.cpp \
    character.cpp \
    pf_spike.cpp \
    pf_flip.cpp \
    pf_left.cpp \
    pf_right.cpp \
    pf_string.cpp \
    pf_ufox.cpp \
    pf_ufoy.cpp \
    entername.cpp \
    showhigh.cpp

HEADERS  += mainwindow.h \
    intro.h \
    platform.h \
    pf_normal.h \
    character.h \
    pf_spike.h \
    pf_flip.h \
    pf_left.h \
    pf_right.h \
    pf_string.h \
    pf_ufox.h \
    pf_ufoy.h \
    entername.h \
    showhigh.h

FORMS    += mainwindow.ui \
    intro.ui \
    entername.ui \
    showhigh.ui

RESOURCES += \
    Source.qrc

OTHER_FILES += \
    icon.rc

RC_FILE += \
icon.rc
