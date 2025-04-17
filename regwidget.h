#ifndef REGWIDGET_H
#define REGWIDGET_H

#include "authservice.h"

#include <QWidget>
#include <QLineEdit>

class RegWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegWidget(QWidget *parent = nullptr);

signals:

private:
    AuthService *authService = nullptr;
    QLineEdit *username, *password, *email;
};

#endif // REGWIDGET_H
