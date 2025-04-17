#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include "authservice.h"

#include <QLineEdit>

class AuthWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWidget(QWidget *parent = nullptr);

signals:
    void needRegistration();

private:
    AuthService *authService = nullptr;

    QLineEdit *username;
    QLineEdit *password;
};

#endif // AUTHWIDGET_H
