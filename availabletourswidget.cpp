#include "availabletourswidget.h"

#include <QVBoxLayout>
#include <QLabel>

AvailableToursWidget::AvailableToursWidget(QWidget *parent)
    : QWidget{parent}
    , connection{DatabaseConnection::getInstance()}
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Доступные для бронирования туры", this);
    label->setAlignment(Qt::AlignCenter);

    availableTours = new QTableView(this);
    //Ошибки модели проверяет БД (это плохо).
    availableTours->setModel(connection.executeQuery("SELECT * FROM Доступные_Туры;"));

    layout->addWidget(availableTours);
}
