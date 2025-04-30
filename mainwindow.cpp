#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "screen.h"
#include "doctor.h"
#include "admin.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QWidget>
#include <QStackedWidget>
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("医院网上分诊挂号系统");

    db = QSqlDatabase::addDatabase("QSQLITE");  // 使用数据库驱动（Qsqlite）和默认连接名称（qt_sql_default_connection）添加一个数据库
    db.setDatabaseName("hospital.db");        // 使用文件数据库（可生成数据库文件，数据一直有效）
    db.setUserName("admin");
    db.setPassword("123456");
    if(!db.open())             // 打开数据库
    {
        QMessageBox::critical(nullptr, "Error", "打开数据库失败！");
        return ;
    }
    // 在打开数据库后立即执行
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");  // 关键步骤！
    if (!query.exec("PRAGMA foreign_keys")) {
        qDebug() << "无法启用外键支持:" << query.lastError();
    }
    //QSqlQuery q;
    //q.exec("INSERT INTO patient (id, name, age, sex) VALUES (210804009, 'Test', '31', '男')");
    //query.exec("INSERT INTO register (id, pid, did) VALUES (250418, 210804009, 20225843)");
    //q.exec("DELETE FROM patient WHERE id = 210804009");  // 看子表记录是否被自动删除
    /*
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS register");
    //query.exec("DROP TABLE IF EXISTS patient");
    if(query.exec("CREATE TABLE register (id INT PRIMARY KEY, pid INT, did INT, "
               "FOREIGN KEY (pid) REFERENCES patient(id) ON DELETE CASCADE ON UPDATE CASCADE, "
                   "FOREIGN KEY (did) REFERENCES doctor(id) ON DELETE CASCADE ON UPDATE CASCADE)"))
        qDebug()<<"建立表r成功";

    //query.exec("CREATE TABLE doctor (id INT PRIMARY KEY, name varchar(20), department varchar(20), room varchar(20))");
    query.exec("CREATE TABLE patient (id INT PRIMARY KEY, name varchar(20), age varchar(20), sex varchar(20))");


    if(query.exec("INSERT INTO patient (id, name, age, sex) VALUES (210804001, 'Alice', 19, '女')"))
        qDebug()<<"插入成功";
    else
        qDebug()<<"插入失败";
    query.exec("INSERT INTO patient (id, name, age, sex) VALUES (210804002, 'Bob', '31', '男')");
    query.exec("INSERT INTO patient (id, name, age, sex) VALUES (210804003, 'Cora', '63', '女')");
    query.exec("INSERT INTO patient (id, name, age, sex) VALUES (210804004, 'Divad', '27', '男')");
    query.exec("INSERT INTO patient (id, name, age, sex) VALUES (210804005, 'Ella', '46', '女')");
    query.exec("INSERT INTO patient (id, name, age, sex) VALUES (210804006, 'Frank', '8', '男')");
    */
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

bool MainWindow::isTableExists(const QString &table)
{
    QSqlQuery query;
    QString sql = QString("select * from sqlite_master where name = '%1';").arg(table);  // 查询sqlite_master表中是否存在表名
    if(query.exec(sql))
    {
        return query.next();
    }
    return false;
}

void MainWindow::on_screenlog_clicked()
{
    Screen *screen = new Screen();
    screen ->show();
    this->close();
}


void MainWindow::on_doctorlog_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE","doctorlog");  // 使用数据库驱动（Qsqlite）和默认连接名称（qt_sql_default_connection）添加一个数据库
    db.setDatabaseName("hospital.db");
    QString account = ui->account->text();
    QString password = ui->password->text();
    int correct = 0;
    QSqlQuery query;
    if (query.exec("SELECT * FROM doctor")) {
        qDebug() <<"处理查询结果";
        while (query.next()) {
            QString a = query.value(0).toString();
            QString p = query.value(1).toString();
            QString n = query.value(2).toString();
            QString room = query.value(4).toString();
            qDebug() <<a<<p<<n;
            //qDebug() << "ID:" << id << "Name:" << name << "Age:" << age << "Department:" << department;
            if(a==account&&p==password){
                Doctor *doctor = new Doctor(nullptr,a,n,room);
                doctor->show();
                this->close();
                correct = 1;
                break;
            }
        }
    }
    qDebug() <<"处果";
    if(!correct){
        QMessageBox::warning(this,tr("登录失败"),tr("账号或密码输入错误！"),QMessageBox::Ok);
        ui->account->clear();
        ui->password->clear();
        ui->account->setFocus();
        db.close();
    }

}


void MainWindow::on_adminlog_clicked()
{

    if(ui->account->text() == "admin" && ui->password->text() == "123456"){
        Admin *admin=new Admin();
        admin->show();
        this->close();
    }else{
        QMessageBox::warning(this,tr("登录失败"),tr("账号或密码输入错误！"),QMessageBox::Ok);
        ui->account->clear();
        ui->password->clear();
        ui->account->setFocus();
    }
}



void MainWindow::on_quit_clicked()
{
    this->close();
}

