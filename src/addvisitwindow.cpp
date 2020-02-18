#include "addvisitwindow.h"
#include "ui_addvisitwindow.h"

AddVisitWindow::AddVisitWindow(MainWindow &parent,QString id,QSqlDatabase &db) :
    QDialog(&parent),
    ui(new Ui::AddVisitWindow),
    petId(id),
    database(db),
    root(parent)
{
    ui->setupUi(this);
    ui->visitDate->setDate(date.currentDate());
}

AddVisitWindow::~AddVisitWindow()
{
    delete ui;
}

void AddVisitWindow::showMessage(QString str, bool state){
    PopUpLittleWindow *window = new PopUpLittleWindow(this, str);
    connect(window, SIGNAL(finished(int)), window, SLOT(deleteLater()));
    if(state){
        connect(window,SIGNAL(finished(int)),this,SLOT(close()));
    }
    window->show();
}
bool AddVisitWindow::checkIfExists(){
    QString str = "ID_pet='"+petId+"' "
            +"AND Data='" + ui->visitDate->text() +"' "
            +"AND Doctor='"+ui->visitDoctor->text()+"' "
            +"AND Doctor_main='"+ui->visitDoctorMain->text()+"' "
            +"AND Treatment='"+ui->visitTreatment->toPlainText()+"' "
            +"AND Description='"+ui->visitDescription->toPlainText()+"' "
            +"AND Recommendation='"+ui->visitRecommendation->toPlainText()+"' "
            +"AND Next_visit='"+ui->visitNextVisit->toPlainText()+"' "
            +"AND Tools='"+ui->visitTools->toPlainText()+"' "
            +"AND Medicines='"+ui->visitMedicines->toPlainText()+"' "
            +"AND Cost='"+ui->visitCost->text()+"' "
            +"AND Payment='"+ui->visitPayment->text()+"'";
    QSqlTableModel model(nullptr,database);
    model.setTable("Visit");
    model.setFilter(str);
    model.select();
    if(model.rowCount()==0){
        return false;
    }
    return true;
}
void AddVisitWindow::on_pushButton_clicked()
{
    if(!checkIfExists()){
        QSqlQuery qry;
        qry.prepare("insert into Visit(ID_Pet,Data,Doctor,Doctor_main,Treatment,Description,Recommendation,Next_visit,Tools,Medicines,Cost,Payment) values (?,?,?,?,?,?,?,?,?,?,?,?);");
        qry.bindValue(0,petId);
        qry.bindValue(1,ui->visitDate->text());
        qry.bindValue(2,ui->visitDoctor->text());
        qry.bindValue(3,ui->visitDoctorMain->text());
        qry.bindValue(4,ui->visitTreatment->toPlainText());
        qry.bindValue(5,ui->visitDescription->toPlainText());
        qry.bindValue(6,ui->visitRecommendation->toPlainText());
        qry.bindValue(7,ui->visitNextVisit->toPlainText());
        qry.bindValue(8,ui->visitTools->toPlainText());
        qry.bindValue(9,ui->visitMedicines->toPlainText());
        qry.bindValue(10,ui->visitCost->text());
        qry.bindValue(11,ui->visitPayment->text());
        qry.exec();
        if(checkIfExists()){
            showMessage("Dodano pomyślnie",true);
            root.updateTreeView();
        }
        else{
            showMessage("Wystąpił problem");
        }
    }
    else{
        showMessage("Taka wizyta istnieje");
    }
}

void AddVisitWindow::on_pushButton_2_clicked()
{
    this->close();
}
