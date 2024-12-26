#include "loginwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include "textmanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TextManager s;
    s.applyTheme("dark");

    LoginWindow w;
    w.show();

    return a.exec();
}

