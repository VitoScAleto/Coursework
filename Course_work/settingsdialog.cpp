#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Settings");
    setFixedSize(200, 200);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *flatDarkButton = new QPushButton("Flat Dark", this);
    QPushButton *flatLightButton = new QPushButton("Flat Light", this);

    layout->addWidget(flatDarkButton);
    layout->addWidget(flatLightButton);

    connect(flatDarkButton, &QPushButton::clicked, this, [this]() {
        emit themeChanged("dark");
        accept();
    });

    connect(flatLightButton, &QPushButton::clicked, this, [this]() {
        emit themeChanged("light");
        accept();
    });
}

