#include <QDialog>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "addpetwindow.h"
namespace Ui {
class SelectOwner;
}

class SelectOwner : public QDialog
{
    Q_OBJECT

public:
    explicit SelectOwner(AddPetWindow &parent,QSqlDatabase &);
    ~SelectOwner();
    void prepareModel(QSqlTableModel &);
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectOwner *ui;
    QSqlDatabase &database;
    AddPetWindow &root;
    QSqlTableModel *model;
    QStandardItem *item;
    QStandardItemModel *itemModel;

};


