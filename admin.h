#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>
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
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_quit_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Admin *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};


#endif // ADMIN_H











