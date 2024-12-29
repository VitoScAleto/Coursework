#include "database.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>


QSqlDatabase Database::connect() {
    // Открываем JSON-файл конфигурации
    QFile configFile(QCoreApplication::applicationDirPath() + "/configDB.json");

    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл конфигурации: " << configFile.errorString();
        return QSqlDatabase();
    }

    // Считываем содержимое файла
    QByteArray configData = configFile.readAll();
    configFile.close();

    // Парсим JSON-документ
    QJsonDocument jsonDoc = QJsonDocument::fromJson(configData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qDebug() << "Ошибка парсинга JSON: некорректный формат";
        return QSqlDatabase();
    }

    // Извлекаем настройки из JSON-объекта
    QJsonObject jsonObj = jsonDoc.object();

    if (!jsonObj.contains("host") || !jsonObj["host"].isString()) {
        qDebug() << "Ошибка: ключ 'host' отсутствует или имеет некорректный формат";
        return QSqlDatabase();
    }
    QString host = jsonObj["host"].toString();

    if (!jsonObj.contains("database") || !jsonObj["database"].isString()) {
        qDebug() << "Ошибка: ключ 'database' отсутствует или имеет некорректный формат";
        return QSqlDatabase();
    }
    QString dbName = jsonObj["database"].toString();

    if (!jsonObj.contains("user") || !jsonObj["user"].isString()) {
        qDebug() << "Ошибка: ключ 'user' отсутствует или имеет некорректный формат";
        return QSqlDatabase();
    }
    QString user = jsonObj["user"].toString();

    if (!jsonObj.contains("password") || !jsonObj["password"].isString()) {
        qDebug() << "Ошибка: ключ 'password' отсутствует или имеет некорректный формат";
        return QSqlDatabase();
    }
    QString password = jsonObj["password"].toString();

    // Настройка подключения к базе данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    } else {
        qDebug() << "Подключение к базе данных успешно!";
    }

    return db;
}
