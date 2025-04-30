#include "register.h"
#include "mainwindow.h"
#include "ui_register.h"

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowTitle("挂号");
    QSqlTableModel *model_;
    QTableView *tableview;

    model_=new QSqlTableModel; //负责提取数据
    model_->setTable("register");
    model_->select();
    tableview=new QTableView;//负责显示数据
    tableview->setFixedSize(600, 500);
    tableview->setModel(model_);

    QVBoxLayout *lay=new QVBoxLayout(this);
    lay->addWidget(tableview);

}

Register::~Register()
{
    delete ui;
}

void Register::on_quit_clicked()
{
    MainWindow *mw = new MainWindow();
    mw ->show();
    this->close();
}

