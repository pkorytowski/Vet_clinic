#pragma once
#include <QMainWindow>
#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QSqlRelationalTableModel>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>


namespace Ui { class MainWindow;}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void prepareItems(QSqlRelationalTableModel &)const;
    QStandardItem* prepareVisits(QSqlRelationalTableModel &,QString)const;
    void updateTreeView();
private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    QSqlDatabase db;
    QSqlRelationalTableModel *petModel;
    QSqlRelationalTableModel *visitModel;
    QSqlTableModel *ownerModel;
    QStandardItem *item;
    QStandardItemModel *standardModel;
    Ui::MainWindow *ui;
};


