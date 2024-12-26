#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialog>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QDomDocument>
#include <QTextStream>
#include <QDebug>
#include <QSplitter>
#include <QRect>
#include <settingsdialog.h>
#include <QStackedWidget>
#include <QListWidget>
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>
#include <toolbar.h>
#include <textmanager.h>
#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QMenuBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int user_id = -1, QString name = "null");

private slots:
    void saveToFile();
    void loadFromFile();

    void closeEvent(QCloseEvent *event) override;
private:
    int q_user_id;
    QString q_name;

    TextManager *textManager;
    ToolBar *toolBar;
};




#endif // MAINWINDOW_H
