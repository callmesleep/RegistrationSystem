#ifndef ADMIN2_H
#define ADMIN2_H

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
class admin2;
}

class admin2 : public QWidget
{
    Q_OBJECT

public:
    explicit admin2(QWidget *parent = nullptr);
    ~admin2();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_quit_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::admin2 *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // ADMIN2_H
