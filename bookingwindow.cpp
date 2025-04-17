#include "bookingwindow.h"
#include "ui_bookingwindow.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlRecord>

BookingWindow::BookingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookingWindow),
    connection(DatabaseConnection::getInstance())
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Выбор тура");

    enterDataWidget = new EnterDataWidget(this);
    connect(enterDataWidget, &EnterDataWidget::readyToBook, this, &BookingWindow::dataEntered);

    availableToursWidget = new AvailableToursWidget(this);
    connect(availableToursWidget->getTable(), &QTableView::doubleClicked, this, &BookingWindow::tourSelected);

    displays = new QStackedWidget(this);
    displays->addWidget(availableToursWidget);
    displays->addWidget(enterDataWidget);
}


void BookingWindow::tourSelected(const QModelIndex &index)
{
    QMessageBox::StandardButton msgBox = QMessageBox::question(
        this,
        "Продолжить?",
        "Перейти к бронированию этого тура?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (msgBox == QMessageBox::Yes) {
        QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(availableToursWidget->getTable()->model());
        id_bus = model->record(index.row()).value("Код_Автобуса").toInt();
        id_service = model->record(index.row()).value("Код_Услуги").toInt();
        id_souvenir = model->record(index.row()).value("Код_Сувенира").toInt();
        id_photosession = model->record(index.row()).value("Код_Фотосессии").toInt();
        id_tour = model->record(index.row()).value("Код_Тура").toInt();

        displays->setCurrentIndex(1);
    }
    else
        return;
}


void BookingWindow::dataEntered(
    const QString &name,
    const QString &surname,
    const QString &fname,
    const QString &city,
    const QString &phone)
{
    QVariantMap params;
    params["name"] = name;
    params["surname"] = surname;
    params["fname"] = fname;
    params["city"] = city;
    params["phone"] = phone;

    QSqlQueryModel* model = connection.executeQuery(
        "INSERT INTO Клиенты (Имя, Фамилия, Отчество, Город, Телефон) "
        "VALUES (:name, :surname, :fathers_name, :city, :phone) RETURNING id;",
        params
    );

    if (model && model->rowCount() > 0) {
        int id = model->record(0).value("id").toInt();

        QVariantMap orderParams;
        orderParams["id"] = id;

        connection.executeQuery(
            "INSERT INTO Заказы (Код_Клиента, Код_Автобуса, Код_Услуги, Код_Сувенира, Код_Фотосессии, Код_Тура)"
            "VALUES (:id, :surname, :fathers_name, :city, :phone) RETURNING id;",
            params
        );
    }
}


BookingWindow::~BookingWindow()
{
    delete ui;
}
