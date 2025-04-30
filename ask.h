#ifndef ASK_H
#define ASK_H

#include <QDialog>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace Ui {
class Ask;
}

class Ask : public QDialog
{
    Q_OBJECT

public:
    explicit Ask(QWidget *parent = nullptr);
    ~Ask();
    QString rid;
    QString pid;
    QString pname;
    QString did;
    QString dname;
    QString droom;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Ask *ui;

};

#endif // ASK_H
