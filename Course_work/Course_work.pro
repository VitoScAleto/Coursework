# Основные модули Qt
QT       += core gui sql widgets printsupport xml

# Проверка версии Qt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Используемый стандарт C++
CONFIG += c++11

# Пути для PostgreSQL
INCLUDEPATH += /usr/include/postgresql
LIBS += -L/usr/lib -lpq
QMAKE_LIBDIR += /usr/lib

# Файл конфигурации и его копирование в директорию сборки
DISTFILES += configDB.json

CONFIG += no_check_exist
QMAKE_POST_LINK += cp $$PWD/configDB.json $$OUT_PWD

# Флаги для компиляции и предупреждений
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000  # Отключить устаревшие API до Qt 6.0.0

# Источники (SOURCES)
SOURCES += \
    database.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registrationwindow.cpp \
    settingsdialog.cpp \
    textmanager.cpp \
    toolbar.cpp

# Заголовки (HEADERS)
HEADERS += \
    database.h \
    loginwindow.h \
    mainwindow.h \
    registrationwindow.h \
    settingsdialog.h \
    textmanager.h \
    toolbar.h

# Формы Qt Designer (FORMS)
FORMS += \
    mainwindow.ui



# Конфигурация для перевода и встраивания переводов
CONFIG += lrelease
CONFIG += embed_translations

# Ресурсы Qt (RESOURCES)
RESOURCES += \
    IconButton.qrc \
    style.qrc

# Настройки установки
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
