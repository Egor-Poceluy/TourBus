#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include "databaseconnection.h"

#include <QDialog>
#include <QStackedWidget>
#include <QTableView>

namespace Ui {
class BookingWindow;
}

class BookingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BookingWindow(QWidget *parent = nullptr);
    ~BookingWindow();

private:
    Ui::BookingWindow *ui;
    DatabaseConnection &connection;

    //QStackedWidget *stackedWidget;
    QTableView *view;
};

#endif // BOOKINGWINDOW_H
