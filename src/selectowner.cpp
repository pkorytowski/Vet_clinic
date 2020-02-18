#include "selectowner.h"
#include "ui_selectowner.h"
#include <QDebug>
SelectOwner::SelectOwner(AddPetWindow &parent,QSqlDatabase &db) :
    QDialog(&parent),
    ui(new Ui::SelectOwner),
    database(db),
    root(parent)
{
    ui->setupUi(this);
    model = new QSqlTableModel(nullptr,database);
    ui->listView->setModel(model);
    itemModel = new QStandardItemModel();
    item=itemModel->invisibleRootItem();
    prepareModel(*model);
    ui->listView->setModel(itemModel);
}

SelectOwner::~SelectOwner()
{
    delete ui;
    delete model;
    delete itemModel;
}
void SelectOwner::prepareModel(QSqlTableModel &model){
    model.setTable("Owner");
    model.setSort(2,Qt::AscendingOrder);
    model.select();
    for(int i=0;i<model.rowCount();i++){
        QString str = model.record(i).value("Surname").toString()
                +" "+model.record(i).value("Name").toString()
                +", ul. "+model.record(i).value("Street").toString()
                +" "+model.record(i).value("Property_number").toString()
                +"/"+model.record(i).value("Flat_number").toString()
                +" "+model.record(i).value("Postal_code").toString()
                +" "+model.record(i).value("Country").toString();
        QStandardItem *element = new QStandardItem(str);
        element->setData(model.record(i).value("ID_owner").toString(),Qt::UserRole);
        item->appendRow(element);

    }
}

void SelectOwner::on_listView_doubleClicked(const QModelIndex &index)
{
    root.setId(index.data(Qt::UserRole).toString());
    root.setOwner(index.data().toString());
    this->close();

}
