#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>
#include <QPalette>
#include <QCryptographicHash>
#include <QScreen>
#include <QDebug>
#include <QShortcut>

class RegistrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);

private slots:
    void onRegisterButtonClicked();
    void backToLogin();
    void applyStyle();
    void Shortcut();
private:
    QLineEdit *loginEdit;
    QLineEdit *nameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;
    QPushButton *registerButton;
    QLabel *messageLabel;
    QPushButton *backToLoginBut;
    QShortcut **shortcutRegister;
    QShortcut *shortcutBackToLogin;
};

#endif // REGISTRATIONWINDOW_H
