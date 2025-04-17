#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include "databaseconnection.h"
#include "enterdatawidget.h"
#include "availabletourswidget.h"

#include <QDialog>
#include <QStackedWidget>

namespace Ui {
class BookingWindow;
}

class BookingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BookingWindow(QWidget *parent = nullptr);
    ~BookingWindow();

public slots:
    void tourSelected(const QModelIndex &index);
    void dataEntered(
        const QString &name,
        const QString &surname,
        const QString &fname,
        const QString &city,
        const QString &phone
    );

private:
    Ui::BookingWindow *ui;
    DatabaseConnection &connection;

    AvailableToursWidget *availableToursWidget = nullptr;
    EnterDataWidget *enterDataWidget = nullptr;

    QStackedWidget *displays;
    int id_bus, id_service, id_souvenir, id_photosession, id_tour;
};

#endif // BOOKINGWINDOW_H
