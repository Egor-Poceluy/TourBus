#include "authwidget.h"

#include <QVBoxLayout>
#include <QPushButton>

AuthWidget::AuthWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    username = new QLineEdit(this);
    username->setPlaceholderText("Логин...");

    password = new QLineEdit(this);
    password->setPlaceholderText("Пароль...");
    password->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Войти", this);
    connect(loginButton, &QPushButton::clicked, this, [this]() {
        authService = &AuthService::getInstance();
        authService->login(username->text(), password->text());
    });

    layout->addWidget(username);
    layout->addWidget(password);
    layout->addWidget(loginButton);
}
