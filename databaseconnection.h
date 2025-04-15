#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include "eventtypes.h"

#include <QObject>
#include <QVariantMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>

class DatabaseConnection : public QObject
{
    Q_OBJECT

public:
    static DatabaseConnection& getInstance();

    void connect(
            const QString& db_name,
            const QString& user_name,
            const QString& password,
            const QString& host,
            const int port
    );

    void disconnect();

    QSqlDatabase& getDatabase();

    QSqlQueryModel* executeQuery(const QString &query, const QVariantMap &params = QVariantMap());

    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

    ~DatabaseConnection();

signals:
    void connectionStatus(const Event &event);

private:
    DatabaseConnection() = default;
    QSqlDatabase db;
    QString connectionName;
};

#endif // DATABASECONNECTION_H
