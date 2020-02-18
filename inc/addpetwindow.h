#pragma once

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "mainwindow.h"

namespace Ui {
class AddPetWindow;
}

class AddPetWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddPetWindow(MainWindow &,QSqlDatabase &);
    ~AddPetWindow();
    bool checkIfExists(QString);
    void showMessage(QString,bool state=false);
    void setId(QString);
    void setOwner(QString);
    bool prepareCastration();
    bool isFilled();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::AddPetWindow *ui;
    QSqlDatabase &database;
    QString ownerId;
    MainWindow &root;
};


