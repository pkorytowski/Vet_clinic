#pragma once

#include <QDialog>
#include <QDate>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "popuplittlewindow.h"
#include "mainwindow.h"

namespace Ui {
class AddVisitWindow;
}

class AddVisitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddVisitWindow(MainWindow &parent,QString,QSqlDatabase &);
    ~AddVisitWindow();
    bool checkIfExists();
    void showMessage(QString,bool state=false);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddVisitWindow *ui;
    QDate date;
    QString petId;
    QSqlDatabase &database;
    MainWindow &root;
};


