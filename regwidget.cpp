#include "regwidget.h"

#include <QVBoxLayout>
#include <QPushButton>

RegWidget::RegWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);


    username = new QLineEdit(this);
    username->setPlaceholderText("Введите логин");

    email = new QLineEdit(this);
    email->setPlaceholderText("Введите почту");

    password = new QLineEdit(this);
    password->setPlaceholderText("Введите пароль");
    password->setEchoMode(QLineEdit::Password);


    QPushButton *regButton = new QPushButton("Зарегистрироваться", this);
    connect(regButton, &QPushButton::clicked, this, [this](){
        authService = &AuthService::getInstance();
        authService->registerUser(username->text(), password->text(), email->text());
    });

    layout->addWidget(username);
    layout->addWidget(email);
    layout->addWidget(password);
    layout->addWidget(regButton);
}
