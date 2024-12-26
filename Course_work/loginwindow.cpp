#include "loginwindow.h"
#include "registrationwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QScreen>
#include <QGuiApplication>
#include <QShortcut>


LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setupUI();
    applyStyles();

    // Устанавливаем подключение к базе данных
    Database::connect();

    QShortcut *shortcutLogin = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(shortcutLogin, &QShortcut::activated, loginButton, &QPushButton::click);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterButtonClicked);
}

LoginWindow::~LoginWindow() {}

void LoginWindow::setupUI() {
    loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("Введите логин");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Введите пароль");

    loginButton = new QPushButton("Войти", this);
    registerButton = new QPushButton("Зарегистрироваться", this);

    registerLabel = new QLabel("Нет аккаунта? Зарегистрируйтесь", this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(50);
    layout->addWidget(loginEdit);
    layout->addSpacing(10);
    layout->addWidget(passwordEdit);
    layout->addSpacing(20);
    layout->addWidget(loginButton);
    layout->addSpacing(20);
    layout->addWidget(registerLabel, 0, Qt::AlignCenter);
    layout->addWidget(registerButton);
    setLayout(layout);

    // Центрирование окна
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int windowWidth = 400;
    int windowHeight = 300;
    int xPos = (screenWidth - windowWidth) / 2;
    int yPos = (screenHeight - windowHeight) / 2;
    move(xPos, yPos);

    setFixedSize(windowWidth, windowHeight);
    setWindowTitle("Авторизация");
}

void LoginWindow::applyStyles() {
    setStyleSheet("background-color: #ffffff;");
    loginEdit->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #ccc;"
        "    border-radius: 8px;"
        "    padding: 8px;"
        "    font-size: 16px;"
        "    color: #333;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #4CAF50;"
        "}"
    );
    passwordEdit->setStyleSheet(loginEdit->styleSheet());
    loginButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border-radius: 8px;"
        "    padding: 10px 20px;"
        "    font-size: 16px;"
        "    border: none;"
        "    transition: background-color 0.3s;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
    );
    registerButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border-radius: 8px;"
        "    padding: 10px 20px;"
        "    font-size: 16px;"
        "    border: none;"
        "    transition: background-color 0.3s;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0b79d0;"
        "}"
    );
    registerLabel->setStyleSheet("color: #555; font-size: 14px;");
}

void LoginWindow::onLoginButtonClicked()
{
    QString login = loginEdit->text();
    QString password = passwordEdit->text();

    // Хеширование пароля
    QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString passwordHashHex = passwordHash.toHex();  // Преобразуем хеш в строку в шестнадцатеричном формате

    // Поиск пользователя в базе данных
    QSqlQuery query;
    query.prepare("SELECT user_id, username FROM users WHERE login = :login AND pasword_hash = :pasword_hash");
    query.bindValue(":login", login);
    query.bindValue(":pasword_hash", passwordHashHex);

    if (query.exec() && query.next())
    {
        int userId = query.value(0).toInt(); // Сохраняем id пользователя
        QString name = query.value(1).toString();
        // Создаем главное окно и передаем id пользователя
        MainWindow *editorWindow = new MainWindow(nullptr,userId, name);
        editorWindow->show();
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
    }
}

void LoginWindow::onRegisterButtonClicked() {
    RegistrationWindow *registerWindow = new RegistrationWindow();
    registerWindow->show();
    this->close();
}
