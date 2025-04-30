#include "ask.h"
#include "ui_ask.h"
#include "doctor.h"
#include <QSqlQuery>
#include <QLineEdit>
#include <QDebug>
Ask::Ask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ask)
{
    ui->setupUi(this);
    ui->name->setText(this->pname);
    this->setWindowTitle("问诊中");
    ui->name->setText(this->pname);
    QSqlQuery query;
    query.exec("SELECT * FROM patient WHERE id="+this->pid);
    query.next();
    ui->age->setText(query.value(2).toString());
    ui->sex->setText(query.value(3).toString());
}

Ask::~Ask()
{
    delete ui;
}

void Ask::on_buttonBox_accepted()
{
    QString d_page = ui->age->text();
    QString d_psex=ui->sex->text();
    QSqlQuery query;
    query.exec("UPDATE patient SET age='"+d_page+"',sex='"+d_psex+"'WHERE id ="+ this->pid);
    query.exec("DELETE FROM register WHERE id ="+ this->rid);
    Doctor *doc = new Doctor(nullptr, this->did, this->dname,this->droom);
    this->close();
    doc->show();

}



void Ask::on_buttonBox_rejected()
{

}

