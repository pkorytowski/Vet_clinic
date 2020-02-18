#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "popupvisitwindow.h"
#include "addownerwindow.h"
#include "addpetwindow.h"
#include "addvisitwindow.h"
#include <QSqlRelation>
#include "mainwindow.moc"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,standardModel(new QStandardItemModel(this))
    , ui(new Ui::MainWindow)

{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("vet.db");
    db.open();
    petModel = new QSqlRelationalTableModel(nullptr,db);
    visitModel = new QSqlRelationalTableModel(nullptr,db);
    ownerModel = new QSqlTableModel(nullptr,db);
    item = standardModel->invisibleRootItem();
    prepareItems(*petModel);
    ui->setupUi(this);
    ui->treeView->setModel(standardModel);
    ui->treeView->setColumnWidth(0,300);
    ui->treeView->setHeaderHidden(1);


}
QString mapCastration(QString str){
    if(str=="0"){
        return "nie";
    }
    else{
        return "tak";
    }
}

void MainWindow::prepareItems(QSqlRelationalTableModel &petModel)const{
    petModel.setTable("Pet");
    petModel.setRelation(1,QSqlRelation("Owner","ID_owner","Name"));
    petModel.select();


    for(int i=0;i<petModel.rowCount();i++){
        QList<QStandardItem *> list;
        QStandardItem *firstColumn = new QStandardItem(petModel.record(i).value("Name").toString());
        firstColumn->setData(petModel.record(i).value("ID_Pet").toInt(),Qt::UserRole);
        firstColumn->setData("0",Qt::UserRole+1);
        QStandardItem *secondColumn = new QStandardItem("Opiekun: " + petModel.record(i).value(1).toString());
        secondColumn->setData(petModel.record(i).value("ID_Pet"),Qt::UserRole);
        secondColumn->setData("0",Qt::UserRole+1);
        QList<QString> names= {"Gatunek:","Rasa:","Umaszczenie:","Masa:","Data urodzenia:","Kastracja"};
        for(int j=0;j<6;j++){
            QList<QStandardItem *> attributesList;
            attributesList.append(new QStandardItem(names[j]));
            if(j!=5){
                attributesList.append(new QStandardItem(petModel.record(i).value(j+3).toString()));
            }
            else{
                attributesList.append(new QStandardItem(mapCastration(petModel.record(i).value(j+3).toString())));
            }
            firstColumn->appendRow(attributesList);
        }
        firstColumn->appendRow(prepareVisits(*visitModel,petModel.record(i).value("ID_pet").toString()));
        list.append(firstColumn);
        list.append(secondColumn);
        item->appendRow(list);
    }

}
QStandardItem* MainWindow::prepareVisits(QSqlRelationalTableModel &visitModel, QString id) const{
    QStandardItem *visits = new QStandardItem("Wizyty");
    QString str="ID_pet="+id;
    visitModel.setTable("Visit");
    visitModel.setFilter(str);
    visitModel.setSort(2,Qt::DescendingOrder);
    visitModel.select();

    for(int i=0;i<visitModel.rowCount();i++){
        QList<QStandardItem *> attributesList;
        QStandardItem *date = new QStandardItem(visitModel.record(i).value("Data").toString());
        date->setData(id,Qt::UserRole);
        date->setData(visitModel.record(i).value("ID_visit").toString(),Qt::UserRole+2);
        date->setData("1",Qt::UserRole+1);
        QStandardItem *treatment = new QStandardItem(visitModel.record(i).value("Treatment").toString());
        date->setData(id,Qt::UserRole);
        treatment->setData(visitModel.record(i).value("ID_visit").toString(),Qt::UserRole+2);
        treatment->setData("1",Qt::UserRole+1);
        attributesList.append(date);
        attributesList.append(treatment);
        visits->appendRow(attributesList);
    }
    return visits;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTreeView(){
    if(standardModel->hasChildren()){
        standardModel->removeRows(0,standardModel->rowCount());
    }
    prepareItems(*petModel);
    ui->treeView->setModel(standardModel);
}
void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
     if(index.data(Qt::UserRole+1).toString()=="1"){
        popUpVisitWindow *pop = new popUpVisitWindow(this,index.data(Qt::UserRole+2).toString(),*visitModel);
        connect(pop, SIGNAL(finished(int)), pop, SLOT(deleteLater()));
        pop->show();
     }

}


void MainWindow::on_pushButton_clicked()
{
    AddPetWindow *window = new AddPetWindow(*this,db);
    connect(window, SIGNAL(finished(int)), window, SLOT(deleteLater()));
    window->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    AddOwnerWindow *window = new AddOwnerWindow(this,db);
    connect(window, SIGNAL(finished(int)), window, SLOT(deleteLater()));
    window->show();


}

void MainWindow::on_pushButton_3_clicked()
{
   // ui->treeView->currentIndex().data(Qt::UserRole).toString();
    AddVisitWindow *window = new AddVisitWindow(*this, ui->treeView->currentIndex().data(Qt::UserRole).toString(),db);
    connect(window, SIGNAL(finished(int)), window, SLOT(deleteLater()));
    window->show();
}
