#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "databaseconnection.h"
#include "eventtypes.h"

class AuthService : public QObject
{
    Q_OBJECT

public:
    enum class UserRole {
        Guest = 1,
        Customer,
        Admin
    };
    Q_ENUM(UserRole)

    static AuthService& getInstance();

    bool registerUser(const QString &username, const QString &password, const QString &email, UserRole role = UserRole::Customer);
    bool login(const QString &username, const QString &password);
    void logout();

    AuthService(const AuthService&) = delete;
    AuthService& operator=(const AuthService&) = delete;

signals:
    void authStatus(const Event &event);

private:
    AuthService() = default;
    DatabaseConnection &connection = DatabaseConnection::getInstance();

    QString currentUser;
    UserRole currentRole = UserRole::Guest;
};

#endif // AUTHSERVICE_H
