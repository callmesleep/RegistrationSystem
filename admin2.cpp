#include "admin2.h"
#include "admin.h"
#include "admin3.h"
#include "mainwindow.h"
#include "ui_admin2.h"
#include <QSqlRecord>
admin2::admin2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::admin2)
{
    ui->setupUi(this);
    this->setWindowTitle("分诊管理端");
    db = QSqlDatabase::addDatabase("QSQLITE","connection_d");  // 使用数据库驱动（Qsqlite）和默认连接名称（qt_sql_default_connection）添加一个数据库
    db.setDatabaseName("hospital.db");
    model=new QSqlTableModel;
    model->setTable("doctor");
    model->select();
    ui->tableView->setModel(model);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

admin2::~admin2()
{
    delete ui;
    delete model;
}

void admin2::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString str = ui->comboBox->currentText();
    if(str == "病人"){
        Admin *admin =new Admin();
        admin->show();
        this->close();
    }else if (str == "挂号"){
        Admin3 *admin_=new Admin3();
        admin_->show();
        this->close();
    }
}


void admin2::on_quit_clicked()
{
    MainWindow *mw = new MainWindow();
    mw ->show();
    this->close();
}

//insert
void admin2::on_pushButton_clicked()
{
    qDebug()<<"插入成功";
    QSqlRecord record = model->record();  //获取空记录
    //获取行号
    int row = model->rowCount();
    //添加空行
    model->insertRecord(row, record);
}

//cancel
void admin2::on_pushButton_2_clicked()
{
    model->revertAll();
    //提交所有动作
    model->submitAll();
}

//delete
void admin2::on_pushButton_3_clicked()
{

    QItemSelectionModel *sModel = ui->tableView->selectionModel();
    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for (int i = 0; i < list.size(); i++) {
        model->removeRow(list.at(i).row());
    }
}

//asve
void admin2::on_pushButton_4_clicked()
{

    model->submitAll();
}
