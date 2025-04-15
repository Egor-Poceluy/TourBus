#include "mainwidget.h"

#include <QPushButton>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *bookingButton = new QPushButton("Забронировать тур", this);
    connect(bookingButton, &QPushButton::clicked, this, &MainWidget::bookingButton_clicked);

    layout->addWidget(bookingButton);
}


void MainWidget::bookingButton_clicked()
{
    if (bookingWindow != nullptr) {
        bookingWindow->raise();
        bookingWindow->activateWindow();
        return;
    }

    bookingWindow = new BookingWindow(this);
    connect(bookingWindow, &QWidget::destroyed, this, [this]() { bookingWindow = nullptr; });
    bookingWindow->show();
}
