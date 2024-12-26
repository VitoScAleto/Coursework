QT       += core gui sql
QT += xml
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += /usr/include/postgresql
LIBS += -L/usr/lib -lpq

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registrationwindow.cpp \
    settingsdialog.cpp \
    textmanager.cpp \
    toolbar.cpp


HEADERS += \
    database.h \
    loginwindow.h \
    mainwindow.h \
    registrationwindow.h \
    settingsdialog.h \
    textmanager.h \
    toolbar.h


FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    #CourseWork_qt_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    IconButton.qrc \
    style.qrc
