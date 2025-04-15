#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "bookingwindow.h"

#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

public slots:
    void bookingButton_clicked();

private:
    BookingWindow *bookingWindow = nullptr;
};

#endif // MAINWIDGET_H
