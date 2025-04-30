#include "doctor.h"
#include "mainwindow.h"
#include "ui_doctor.h"
#include "ask.h"
#include "screen.h"
Doctor::Doctor(QWidget *parent, QString did, QString dname, QString droom)
    : QWidget(parent)
    , ui(new Ui::Doctor)
{
    this->did=did;
    this->dname=dname;
    this->droom=droom;
    ui->setupUi(this);
    this->setWindowTitle("医生呼叫端");
    ui->docname->setText(dname);
    db = QSqlDatabase::addDatabase("QSQLITE", "connection3");
    db.setDatabaseName("hospital.db");
    queryModel = new QSqlQueryModel(this);
    queryModel->setQuery("SELECT r.id AS 挂号单号,p.id AS 身份证号,p.name AS 姓名, p.age AS 年龄, p.sex AS 性别 FROM patient p,register r,doctor d WHERE p.id = r.pid and d.id = r.did and d.id ="+did);
    ui->tableView->setModel(queryModel);

}

Doctor::~Doctor()
{
    delete ui;
}

void Doctor::on_quit_clicked()
{
    MainWindow *mw = new MainWindow();
    mw ->show();
    this->close();
}


void Doctor::on_call_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        int selectedRow = selectedRows.first().row();
        QModelIndex index = queryModel->index(selectedRow, 2);
        QVariant data = queryModel->data(index);
        QString pname = data.toString();
        QString notice_="请"+pname+"到"+this->droom+"就诊";
        if(notice.size()==5)
            notice.removeAt(0);
        notice.append(notice_);
    }
}


void Doctor::on_ask_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        int selectedRow = selectedRows.first().row();
        QModelIndex index = queryModel->index(selectedRow, 0);
        QVariant data = queryModel->data(index);
        QString rid = data.toString();
        index = queryModel->index(selectedRow, 1);
        data = queryModel->data(index);
        QString pid = data.toString();
        index = queryModel->index(selectedRow, 2);
        data = queryModel->data(index);
        QString pname = data.toString();
        Ask *ask =new Ask();
        ask->rid=rid;
        ask->pid=pid;
        ask->pname = pname;
        ask->did=this->did;
        ask->dname=this->dname;
        ask->droom=this->droom;
        this->close();
        ask->show();
    }
}

