#include "addownerwindow.h"
#include "ui_addownerwindow.h"
#include "popuplittlewindow.h"

AddOwnerWindow::AddOwnerWindow(QWidget *parent,QSqlDatabase &db) :
    QDialog(parent),
    ui(new Ui::AddOwnerWindow),
    database(db)
{
    ui->setupUi(this);
}

AddOwnerWindow::~AddOwnerWindow()
{
    delete ui;
}
void AddOwnerWindow::showMessage(QString str, bool state){
    PopUpLittleWindow *window = new PopUpLittleWindow(this, str);
    connect(window, SIGNAL(finished(int)), window, SLOT(deleteLater()));
    if(state){
        connect(window,SIGNAL(finished(int)),this,SLOT(close()));
    }
    window->show();
}
bool AddOwnerWindow::checkIfExists(){
    QString str = "Name='"+ui->ownerName->text()+"' ";
            +"AND Surname='" + ui->ownerSurname->text()+"' "
            +"AND Country='"+ui->ownerCountry->text()+"' "
            +"AND Postal_code='"+ui->ownerPostalCode->text()+"' "
            +"AND City='"+ui->ownerCity->text()+"' "
            +"AND Street='"+ui->ownerStreet->text()+"' "
            +"AND Property_number='"+ui->ownerPropNum->text()+"' "
            +"AND Flat_number='"+ui->ownerFlatNum->text()+"'";
    QSqlTableModel model(nullptr,database);
    model.setTable("Owner");
    model.setFilter(str);
    model.select();
    if(model.rowCount()==0){
        return false;
    }
    return true;
}
void AddOwnerWindow::on_pushButton_clicked()
{
    if(!checkIfExists()){
        QSqlQuery qry;
        qry.prepare("insert into Owner(Name,Surname,Country,Postal_code,City,Street,Property_number,Flat_number) values (?,?,?,?,?,?,?,?);");
        qry.bindValue(0,ui->ownerName->text());
        qry.bindValue(1,ui->ownerSurname->text());
        qry.bindValue(2,ui->ownerCountry->text());
        qry.bindValue(3,ui->ownerPostalCode->text());
        qry.bindValue(4,ui->ownerCity->text());
        qry.bindValue(5,ui->ownerStreet->text());
        qry.bindValue(6,ui->ownerPropNum->text());
        qry.bindValue(7,ui->ownerFlatNum->text());
        qry.exec();
        if(checkIfExists()){
            showMessage("Dodano pomyślnie",true);
        }
        else{
            showMessage("Wystąpił problem");
        }
    }
    else{
        showMessage("Taka osoba instnieje");
    }
}

void AddOwnerWindow::on_pushButton_2_clicked()
{
    this->close();
}
