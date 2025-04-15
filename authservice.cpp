#include "authservice.h"

#include <QSqlRecord>

AuthService& AuthService::getInstance()
{
    static AuthService instance;
    return instance;
}


bool AuthService::registerUser(const QString &username, const QString &password, const QString &email, UserRole role) {
    const QString query("INSERT INTO users (username, password, email, role) "
                        "VALUES (:username, :password, :email, :role)");

    QVariantMap params;
    params["username"] = username;
    params["password"] = password;
    params["email"] = email;
    params["role"] = static_cast<int>(role);

    QSqlQueryModel* model = connection.executeQuery(query, params);

    if (!model || model->lastError().isValid()) {
        emit authStatus({EventType::LoginError, "Ошибка регистрации"});
        return false;
    }
    return true;
}


bool AuthService::login(const QString &username, const QString &password) {
    const QString query = "SELECT password, role FROM users WHERE username = :username";

    QVariantMap params;
    params["username"] = username;

    QSqlQueryModel* model = connection.executeQuery(query, params);

    if (!model || model->rowCount() == 0) {
        emit authStatus({EventType::LoginError, "Пользователь не найден"});
        return false;
    }

    QSqlRecord record = model->record(0);

    QString passwordFromDatabase = record.value("password").toString();
    UserRole role = static_cast<UserRole>(record.value("role").toInt());

    if (password == passwordFromDatabase) {
        currentUser = username;
        currentRole = role;
        emit authStatus({EventType::LoginSuccess, "Вход успешно выполнен"});
        return true;
    }

    emit authStatus({EventType::LoginError, "Неверный пароль"});
    return false;
}


void AuthService::logout() {
    currentUser.clear();
    currentRole = UserRole::Guest;
    emit authStatus({EventType::Logout, "Вы вышли из аккаунта"});
}
