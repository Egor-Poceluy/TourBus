#include "databaseconnection.h"

#include <QUuid>
#include <QSqlQuery>

DatabaseConnection& DatabaseConnection::getInstance()
{
    static DatabaseConnection instance;
    return instance;
}


void DatabaseConnection::connect(const QString& db_name,
                                 const QString& user_name,
                                 const QString& password,
                                 const QString& host,
                                 const int port)
{
    if (db.isOpen()) {
        if (db.databaseName() != db_name ||
            db.userName() != user_name ||
            db.password() != password ||
            db.hostName() != host ||
            db.port() != port)
            disconnect();
        else {
            emit connectionStatus({EventType::DatabaseConnectedSuccess, "Вы уже подключены"});
            return;
        }
    }

    connectionName = QUuid::createUuid().toString();
    db = QSqlDatabase::addDatabase("QPSQL", connectionName);
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(db_name);
    db.setUserName(user_name);
    db.setPassword(password);

    if (db.open())
        emit connectionStatus({EventType::DatabaseConnectedSuccess, "Соединение установлено"});
    else
        emit connectionStatus({EventType::DatabaseConnectedError, db.lastError().text()});
}


void DatabaseConnection::disconnect()
{
    if (db.isOpen()) db.close();

    if (!connectionName.isEmpty() && QSqlDatabase::contains(connectionName)) {
        QSqlDatabase::removeDatabase(connectionName);
        connectionName.clear();
    }
}


QSqlDatabase& DatabaseConnection::getDatabase() { return db; }


QSqlQueryModel* DatabaseConnection::executeQuery(const QString &query, const QVariantMap &params)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery sqlQuery(db);
    sqlQuery.prepare(query);

    for (auto i = params.constBegin(); i != params.constEnd(); ++i) {
        sqlQuery.bindValue(":" + i.key(), i.value());
    }

    if (!sqlQuery.exec()) {
        emit connectionStatus({EventType::QueryError, sqlQuery.lastError().text()});
        return nullptr;
    }

    model->setQuery(std::move(sqlQuery));

    if (model->lastError().isValid()) {
        emit connectionStatus({EventType::QueryError, model->lastError().text()});
        return nullptr;
    }
    else if (!query.startsWith("SELECT"))
        emit connectionStatus({EventType::QuerySuccess, "Запрос успешно выполнен"});

    return model;
}


DatabaseConnection::~DatabaseConnection() { disconnect(); }

