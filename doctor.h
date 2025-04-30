#ifndef DOCTOR_H
#define DOCTOR_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace Ui {
class Doctor;
}

class Doctor : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr, QString id = "admin", QString name = "123456",QString room="-");
    ~Doctor();
    QString did ;
    QString dname;
    QString droom;
private slots:
    void on_quit_clicked();

    void on_call_clicked();

    void on_ask_clicked();

private:
    Ui::Doctor *ui;

    QSqlDatabase db;
    QSqlQueryModel *queryModel;
};

#endif // DOCTOR_H
