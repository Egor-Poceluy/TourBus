#include "enterdatawidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QRegExp>
#include <QRegExpValidator>

EnterDataWidget::EnterDataWidget(QWidget *parent)
    : QWidget{parent}
{
    QRegExp nameRegex("^[a-zA-Zа-яА-ЯёЁ\\s-]+$");
    QRegExpValidator *nameValidator = new QRegExpValidator(nameRegex, this);

    QRegExp phoneRegex("^\\d{10,15}$");
    QRegExpValidator *phoneValidator = new QRegExpValidator(phoneRegex, this);

    QRegExp cityRegex("^[a-zA-Zа-яА-ЯёЁ\\s-]+$");
    QRegExpValidator *cityValidator = new QRegExpValidator(cityRegex, this);


    QVBoxLayout *layout = new QVBoxLayout(this);


    QLabel *nameLabel = new QLabel("Имя", this);
    name = new QLineEdit();
    name->setPlaceholderText("Введите имя...");
    name->setValidator(nameValidator);

    QLabel *surnameLabel = new QLabel("Фамилия", this);
    surname = new QLineEdit();
    surname->setPlaceholderText("Введите фамилию...");
    surname->setValidator(nameValidator);

    QLabel *fnameLabel = new QLabel("Отчество", this);
    fname = new QLineEdit();
    fname->setPlaceholderText("Введите отчество...");
    fname->setValidator(nameValidator);

    QLabel *cityLabel = new QLabel("Город", this);
    city = new QLineEdit();
    city->setPlaceholderText("Введите город...");
    city->setValidator(cityValidator);

    QLabel *phoneLabel = new QLabel("Телефон", this);
    phone = new QLineEdit();
    phone->setPlaceholderText("Введите номер телефона...");
    phone->setValidator(phoneValidator);


    //QComboBox для выбора доп. услуг


    QPushButton *bookTour = new QPushButton("Забронировать", this);
    connect(bookTour, &QPushButton::clicked, this, [this](){
        if (!name->text().isEmpty() && !surname->text().isEmpty() &&
            !city->text().isEmpty() && !phone->text().isEmpty())
        {
            emit readyToBook(
                name->text(),
                surname->text(),
                fname->text(),
                city->text(),
                phone->text()
            );
        }
    });


    layout->addWidget(nameLabel);
    layout->addWidget(name);

    layout->addWidget(surnameLabel);
    layout->addWidget(surname);

    layout->addWidget(fnameLabel);
    layout->addWidget(fname);

    layout->addWidget(cityLabel);
    layout->addWidget(city);

    layout->addWidget(phoneLabel);
    layout->addWidget(phone);
}
