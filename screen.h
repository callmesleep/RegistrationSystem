#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
extern  QList<QString> notice;
namespace Ui {
class Screen;
}

class Screen : public QWidget
{
    Q_OBJECT

public:
    explicit Screen(QWidget *parent = nullptr);
    ~Screen();

private slots:
    void on_quit_clicked();

    void on_regisration_clicked();

private:
    Ui::Screen *ui;
    QSqlDatabase db;
};

#endif // SCREEN_H
