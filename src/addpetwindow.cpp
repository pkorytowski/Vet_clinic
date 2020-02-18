#include "addpetwindow.h"
#include "ui_addpetwindow.h"
#include "popuplittlewindow.h"
#include "selectowner.h"

AddPetWindow::AddPetWindow(MainWindow &parent,QSqlDatabase &db) :
    QDialog(&parent),
    ui(new Ui::AddPetWindow),
    database(db),
    ownerId(""),
    root(parent)
{
    ui->setupUi(this);

}

AddPetWindow::~AddPetWindow()
{
    delete ui;
}
void AddPetWindow::setId(QString str){
    ownerId=str;
}
bool AddPetWindow::prepareCastration(){
    return true;
}
bool AddPetWindow::isFilled(){
    if(ui->petName->text()=="" || ownerId=="" || ui->petSpecies->text()==""){
        return false;
    }
    return true;
}
void AddPetWindow::setOwner(QString str){
    ui->petOwner->setText(str);
}

bool AddPetWindow::checkIfExists(QString ownerId){
    QString str = "Name='"+ui->petName->text()+"' ";
            +"AND ID_owner='" + ownerId+"' "
            +"AND Species='"+ui->petSpecies->text()+"' "
            +"AND Breed='"+ui->petBreed->text()+"' "
            +"AND Coat='"+ui->petCoat->text()+"' "
            +"AND Mass='"+ui->petMass->text()+"' "
            +"AND Age='"+ui->petAge->text()+"' "
            +"AND Castration='"+ui->petCastration->isChecked()+"' "
            +"AND Allergy='"+ui->petAllergy->text()+"' "
            +"AND Comment='"+ui->petComment->text()+"'";
    QSqlTableModel model(nullptr,database);
    model.setTable("Pet");
    model.setFilter(str);
    model.select();
    if(model.rowCount()==0){
        return false;
    }
    return true;
}
void AddPetWindow::showMessage(QString str, bool state){
    PopUpLittleWindow *window = new PopUpLittleWindow(this, str);
    connect(window, SIGNAL(finished(int)), window, SLOT(deleteLater()));
    if(state){
        connect(window,SIGNAL(finished(int)),this,SLOT(close()));
    }
    window->show();
}

void AddPetWindow::on_pushButton_clicked()
{
    if(!checkIfExists(ownerId) && isFilled()){
        QSqlQuery qry;
        qry.prepare("insert into Pet(ID_owner,Name,Species,Breed,Coat,Mass,Age,Castration,Allergy,Comment) values (?,?,?,?,?,?,?,?,?,?);");
        qry.bindValue(0,ownerId);
        qry.bindValue(1,ui->petName->text());
        qry.bindValue(2,ui->petSpecies->text());
        qry.bindValue(3,ui->petBreed->text());
        qry.bindValue(4,ui->petCoat->text());
        qry.bindValue(5,ui->petMass->text());
        qry.bindValue(6,ui->petAge->text());
        qry.bindValue(7,ui->petCastration->isChecked());
        qry.bindValue(8,ui->petAllergy->text());
        qry.bindValue(9,ui->petComment->text());
        qry.exec();
        if(checkIfExists(ownerId)){
            showMessage("Dodano pomyślnie",true);
            root.updateTreeView();
        }
        else{
            showMessage("Wystąpił problem");
        }
    }
    else{
        showMessage("Taka osoba instnieje");
    }
}

void AddPetWindow::on_pushButton_2_clicked()
{
    this->close();
}

void AddPetWindow::on_pushButton_3_clicked()
{
    SelectOwner *window = new SelectOwner(*this, database);
    connect(window, SIGNAL(finished(int)), window, SLOT(deleteLater()));
    window->show();
}
