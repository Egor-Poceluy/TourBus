#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , connection(DatabaseConnection::getInstance())
{
    ui->setupUi(this);
    connection.connect("users", "postgres", "qwerty", "localhost", 5432);

    connect(&connection, &DatabaseConnection::connectionStatus, this, &MainWindow::eventHandler);
    connect(&AuthService::getInstance(), &AuthService::authStatus, this, &MainWindow::eventHandler);

    //!!!!!!!!!!!!!!!!!!!!
    connect(authWidget, &AuthWidget::needRegistration, this, &MainWindow::handleRegistration);

    stackedWidget = new QStackedWidget(this);

    authWidget = new AuthWidget(this);
    //regWidget = new RegWidget(this);
    mainwidget = new MainWidget(this);
    adminWidget = new AdminWidget(this);

    stackedWidget->addWidget(authWidget);
    stackedWidget->addWidget(regWidget);
    stackedWidget->addWidget(mainwidget);
    //stackedWidget->addWidget(adminWidget);

    setCentralWidget(stackedWidget);
}


void MainWindow::eventHandler(const Event &event)
{
    switch (event.type) {
        case EventType::DatabaseConnectedError:
            QMessageBox::critical(this, "Ошибка", event.data);
            break;
        case EventType::DatabaseConnectedSuccess:
            QMessageBox::information(this, "Успех", event.data);
            break;
        case EventType::LoginError:
            QMessageBox::critical(this, "Ошибка", event.data);
            break;
        case EventType::LoginSuccess:
            QMessageBox::information(this, "Успех", event.data);
            handleLogin();
            break;
        case EventType::Logout:
            QMessageBox::information(this, "Успех", event.data);
            handleLogout();
            break;
        case EventType::QueryError:
            QMessageBox::critical(this, "Ошибка", event.data);
            break;
        case EventType::QuerySuccess:
            QMessageBox::information(this, "Успех", event.data);
            break;
    }
}


void MainWindow::handleLogin()
{
    stackedWidget->setCurrentIndex(2);
}


void MainWindow::handleLogout()
{
    stackedWidget->setCurrentIndex(0);
}


void MainWindow::handleRegistration()
{
    stackedWidget->setCurrentIndex(1);
}


MainWindow::~MainWindow()
{
    delete ui;
}

