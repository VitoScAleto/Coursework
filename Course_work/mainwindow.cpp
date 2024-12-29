#include <mainwindow.h>
#include "settingsdialog.h"


MainWindow::MainWindow(QWidget *parent, int user_id, QString name) : QMainWindow(parent), q_user_id(user_id), q_name(name)
{
    setWindowTitle("Text Editor");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    textManager = new TextManager(this, user_id, name);
    layout->addWidget(textManager);



    setCentralWidget(centralWidget);
}


void MainWindow:: saveToFile()
{
   QString filePath = QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML Files (*.xml);;All Files (*)"));
    if (!filePath.isEmpty())
    {
        textManager->savePagesToXml(filePath);
    }
}

void MainWindow::  loadFromFile()
{
   QString filePath = QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML Files (*.xml);;All Files (*)"));

        textManager->loadPagesFromXml(filePath);

}





void MainWindow::closeEvent(QCloseEvent *event)
{
    // Сохраняем все страницы в базе данных перед закрытием приложения
    textManager->updatePagesInDatabase();
qDebug() << "Saving pages and closing the app...";
QWidget::closeEvent(event);
    // Закрываем приложение
    event->accept();
}

