#include "database.h"
#include <QDebug>

QSqlDatabase Database::connect() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("89.104.68.236");
    db.setDatabaseName("VitalyaDB");
    db.setUserName("vitalya"); // Имя пользователя
    db.setPassword("0000"); // Пароль

    if (!db.open())
    {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    }
    else
    {
        qDebug() << "Подключение к базе данных успешно!";
    }

    return db;
}
