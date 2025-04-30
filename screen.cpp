#include "screen.h"
#include "mainwindow.h"
#include "registration.h"
#include "ui_screen.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextEdit>
QList<QString> notice;
Screen::Screen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Screen)
{
    ui->setupUi(this);
    this->setWindowTitle("大屏显示端");
    //QString selectQuery = "SELECT r.id, p.name, d.name FROM register r, patient p, doctor d WHERE r.pid = p.id AND r.did = d.id";
    db = QSqlDatabase::addDatabase("QSQLITE", "connection2");
    db.setDatabaseName("hospital.db");
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    queryModel->setQuery("SELECT r.id AS 挂号单号, p.name AS 姓名, d.room AS 诊室 FROM register r, patient p, doctor d WHERE r.pid = p.id AND r.did = d.id  ORDER BY r.id ASC");
    ui->tableView->setModel(queryModel);
    QString str="";
    for(int i=0;i<notice.size();i++){
        str+=notice[i];
        str+="\n";
    }
    ui->notice->setText(str);
}

Screen::~Screen()
{
    delete ui;
    db.close();
}

void Screen::on_quit_clicked()
{
    MainWindow *mw = new MainWindow();
    mw ->show();
    this->close();
}


void Screen::on_regisration_clicked()
{
    Registration *reg = new Registration();
    reg ->show();
    this->close();
}

