#include "loginwindow.h"
#include "registrationwindow.h"
#include "mainwindow.h"



RegistrationWindow::RegistrationWindow(QWidget *parent) : QWidget(parent)
{
    applyStyle();

    Shortcut();

    // Подключение сигналов
    connect(registerButton, &QPushButton::clicked, this, &RegistrationWindow::onRegisterButtonClicked);
    connect(backToLoginBut, &QPushButton::clicked, this, &RegistrationWindow::backToLogin);

    // Основной вертикальный макет
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(3);  // Добавляем отступ сверху для выравнивания
    layout->addWidget(loginEdit);
    layout->addSpacing(10);
    layout->addWidget(nameEdit);
    layout->addSpacing(10);
    layout->addWidget(passwordEdit);
    layout->addSpacing(10);
    layout->addWidget(confirmPasswordEdit);
    layout->addSpacing(20);
    layout->addWidget(registerButton);
    layout->addSpacing(20);
    layout->addWidget(backToLoginBut);
    layout->addSpacing(20);
    layout->addWidget(messageLabel, 0, Qt::AlignCenter);
    setLayout(layout);

    // Центрирование окна на экране
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int windowWidth = 400;
    int windowHeight = 400;
    int xPos = (screenWidth - windowWidth) / 2;
    int yPos = (screenHeight - windowHeight) / 2;
    move(xPos, yPos);

    setFixedSize(windowWidth, windowHeight);
    setWindowTitle("Регистрация");
}

void RegistrationWindow::Shortcut()
{
    QShortcut *shortcutRegister = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(shortcutRegister, &QShortcut::activated, registerButton, &QPushButton::click);

    QShortcut *shortcutBackToLogin = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcutBackToLogin, &QShortcut::activated, backToLoginBut, &QPushButton::click);
}



void RegistrationWindow::onRegisterButtonClicked()
{
    QString login = loginEdit->text().trimmed();
    QString name = nameEdit->text().trimmed();
    QString password = passwordEdit->text();
    QString confirmPassword = confirmPasswordEdit->text();

    // Проверка на пустые поля
    if (login.isEmpty() || name.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        messageLabel->setText("Все поля должны быть заполнены!");
        return;
    }

    // Проверка на совпадение паролей
    if (password != confirmPassword) {
        messageLabel->setText("Пароли не совпадают!");
        return;
    }

    // Подключение к базе данных
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        messageLabel->setText("Ошибка подключения к базе данных");
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE login = :login");
    query.bindValue(":login", login);  // Используем bindValue для параметра login

    if (!query.exec()) {
        messageLabel->setText("Ошибка выполнения запроса");
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    query.next();
    if (query.value(0).toInt() > 0) {
        messageLabel->setText("Пользователь с таким логином уже существует");
        return;
    }

    // Хеширование пароля
    QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    // Преобразование хеша в шестнадцатеричную строку
    QString passwordHashHex = passwordHash.toHex();

    // Вставка нового пользователя в базу данных
    query.prepare("INSERT INTO users (username, pasword_hash, login, theme) "
                  "VALUES (:username, :pasword_hash, :login, :theme)");
    query.bindValue(":username", name);
    query.bindValue(":pasword_hash", passwordHashHex); // Хеш пароля в шестнадцатеричной строке
    query.bindValue(":login", login); // Логин как email
    query.bindValue(":theme", "light"); // Значение по умолчанию для поля theme

    if (!query.exec()) {
        messageLabel->setText("Ошибка при сохранении данных");
        qDebug() << "Insert error:" << query.lastError().text();
        return;
    }

    // Успешная регистрация
    QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
    backToLogin();  // Переход к окну входа
}

void RegistrationWindow::backToLogin()
{
    LoginWindow* logInWindow = new LoginWindow();
    logInWindow->show();
    this->close();

}


void RegistrationWindow::applyStyle()
{
    // Устанавливаем белый фон для окна
    setStyleSheet("background-color: #ffffff;");

    // Поле ввода логина
    loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("Введите логин");
    loginEdit->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #ccc;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 16px;"
        "    color: #333;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #4CAF50;"
        "}"
    );

    // Поле ввода имени
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Введите имя");
    nameEdit->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #ccc;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 16px;"
        "    color: #333;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #4CAF50;"
        "}"
    );

    // Поле ввода пароля
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Введите пароль");
    passwordEdit->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #ccc;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 16px;"
        "    color: #333;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #4CAF50;"
        "}"
    );

    // Поле подтверждения пароля
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setPlaceholderText("Повторите пароль");
    confirmPasswordEdit->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #ccc;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 16px;"
        "    color: #333;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #4CAF50;"
        "}"
    );

    // Кнопка "Зарегистрироваться"
    registerButton = new QPushButton("Зарегистрироваться", this);
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

    //Кнопка назад к логину
    backToLoginBut = new QPushButton("Назад",this);
    backToLoginBut->setStyleSheet(
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

    // Место для сообщения об ошибке или успехе
    messageLabel = new QLabel("", this);
    messageLabel->setStyleSheet("color: #FF5733; font-size: 14px;");




}
