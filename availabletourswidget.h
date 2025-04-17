#ifndef AVAILABLETOURSWIDGET_H
#define AVAILABLETOURSWIDGET_H

#include "databaseconnection.h"

#include <QWidget>
#include <QTableView>

class AvailableToursWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AvailableToursWidget(QWidget *parent = nullptr);
    QTableView* getTable() const { return availableTours; }

private:
    DatabaseConnection &connection;
    QTableView *availableTours;
};

#endif // AVAILABLETOURSWIDGET_H
