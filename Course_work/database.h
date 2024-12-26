#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>


class Database {
public:
    static QSqlDatabase connect();
};

#endif // DATABASE_H
