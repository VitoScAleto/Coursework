#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "database.h"

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *registerLabel;

    void setupUI(); // Для инициализации интерфейса
    void applyStyles(); // Для применения стилей
};

#endif // LOGINWINDOW_H
