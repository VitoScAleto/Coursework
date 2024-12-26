#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
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


class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);


signals:
    void themeChanged(const QString &theme);
};


#endif // SETTINGSDIALOG_H
