#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QVBoxLayout>
namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
