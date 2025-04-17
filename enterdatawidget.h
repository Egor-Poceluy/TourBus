#ifndef ENTERDATAWIDGET_H
#define ENTERDATAWIDGET_H

#include <QWidget>
#include <QLineEdit>

class EnterDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnterDataWidget(QWidget *parent = nullptr);

signals:
    void readyToBook(
        const QString &name,
        const QString &surname,
        const QString &fname,
        const QString &city,
        const QString &phone
    );

private:
    QLineEdit *name, *surname, *fname, *city, *phone;
};

#endif // ENTERDATAWIDGET_H
