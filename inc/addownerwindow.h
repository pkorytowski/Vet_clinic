#pragma once

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>


namespace Ui {
class AddOwnerWindow;
}

class AddOwnerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddOwnerWindow(QWidget *,QSqlDatabase &);
    ~AddOwnerWindow();
    bool checkIfExists();
    void showMessage(QString,bool state=false);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::AddOwnerWindow *ui;
    QSqlDatabase &database;
};


