#include "bookingwindow.h"
#include "ui_bookingwindow.h"

#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>

BookingWindow::BookingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookingWindow)
    , connection(DatabaseConnection::getInstance())
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Выбор тура");

    QVBoxLayout *layout = new QVBoxLayout(this);

    //stackedWidget = new QStackedWidget(this);
    view = new QTableView(this);

    view->setModel(connection.executeQuery("SELECT * FROM Доступные_Туры;"));

    layout->addWidget(view);

}

BookingWindow::~BookingWindow()
{
    delete ui;
}
