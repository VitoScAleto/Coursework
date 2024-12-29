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
#include <QObject>
#include <QEvent>
#include <QKeyEvent>

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

class NoSpaceFilter : public QObject {
    Q_OBJECT
public:
    explicit NoSpaceFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Space) {
                // Игнорируем пробел
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }
};

#endif // REGISTRATIONWINDOW_H
