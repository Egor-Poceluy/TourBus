#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authwidget.h"
#include "mainwidget.h"
#include "adminwidget.h"
#include <regwidget.h>
#include "eventtypes.h"
#include "databaseconnection.h"

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void eventHandler(const Event &event);

private:
    Ui::MainWindow *ui;
    void handleLogin();
    void handleLogout();
    void handleRegistration();

    QStackedWidget *stackedWidget;
    AuthWidget *authWidget = nullptr;
    RegWidget *regWidget = nullptr;
    MainWidget *mainwidget = nullptr;
    AdminWidget *adminWidget = nullptr;

    DatabaseConnection &connection;

};
#endif // MAINWINDOW_H
