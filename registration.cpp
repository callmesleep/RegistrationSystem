#include "registration.h"
#include "ui_registration.h"
#include "queuesystem.h"
#include "screen.h"
#include <QString>
#include <QDate>
Registration::Registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
    QString n=QString::number(no+1);
    this->setWindowTitle("挂号"+n);

}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_buttonBox_accepted()
{
    QString pid = ui->id->text();
    QString pname = ui->name->text();
    QString department = ui->department->currentText();
    QString did;
    QSqlQuery query;
    if(pid.length() !=9){
        QMessageBox::warning(this,tr("挂号失败"),tr("身份证号输入错误！"),QMessageBox::Ok);
        return;
    }
    query.exec("SELECT * FROM patient WHERE id =" + pid);
    if (!query.next())
        query.exec("INSERT INTO patient (id, name, age, sex) VALUES (" + pid + ", '" + pname + "', '-', '-')");
    else{
        if(query.value(1).toString()!=pname){
            QMessageBox::warning(this,tr("挂号失败"),tr("身份证号与姓名不匹配！"),QMessageBox::Ok);
            Registration *reg = new Registration();
            reg ->show();
            this->close();
            return;
        }
    }
    //查找对应科室排号最少的医生
    //QString queryStr = "SELECT d.id, COUNT(r.id)  FROM doctor d, register r WHERE d.department = "+ department +"GROUP BY d.id ORDER BY registration_count ASC LIMIT 1";
    QString queryStr = "SELECT doctor.id,doctor.department, COUNT(register.id) AS rd FROM doctor LEFT JOIN register ON doctor.id = register.did GROUP BY doctor.id ORDER BY rd ASC";
    //

    if (query.exec(queryStr)) {
        while(query.next()) {
            QString ddp = query.value(1).toString();
            if(ddp == department){
                did = query.value(0).toString();
                QDate currentDate = QDate::currentDate();
                //int y = currentDate.year();
                int m = currentDate.month();
                int d = currentDate.day();
                QString id = "25"+QString::number(m).rightJustified(2, '0')+QString::number(d).rightJustified(2, '0')+QString::number(no+1).rightJustified(3, '0');
                if(!query.exec("INSERT INTO register (id, pid, did) VALUES (" + id + ", " + pid + ", " + did + ")"))
                    qDebug() << "未找到";
                else qDebug() << "成功插入";
                break;
            }
        }
    }else{
        qDebug() << "未找到符合条";
    }

    //id INT PRIMARY KEY, pid varchar(20), did varchar(20), remark

    no++;
    Screen *screen = new Screen();
    screen->show();
    this->close();
}


void Registration::on_buttonBox_rejected()
{
    Screen *screen = new Screen();
    screen->show();
    this->close();
}

