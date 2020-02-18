#include "popupvisitwindow.h"
#include "ui_popupvisitwindow.h"
#include <QDebug>


popUpVisitWindow::popUpVisitWindow(QWidget *parent,QString id, QSqlRelationalTableModel &model):
    QDialog(parent),
    ui(new Ui::popUpVisitWindow){

    ui->setupUi(this);

    QString str="ID_visit="+id;
    model.setTable("Visit");
    model.setFilter(str);
    model.select();
    ui->visitDate->setText(validateData(model.record(0).value("Data").toString()));
    ui->visitDoctor->setText(validateData(model.record(0).value("Doctor").toString()));
    ui->visitMainDoctor->setText(validateData(model.record(0).value("Doctor_main").toString()));
    ui->visitTreatment->setText(validateData(model.record(0).value("Treatment").toString()));
    ui->visitInterview->setText(validateData(model.record(0).value("Interview").toString()));
    ui->visitDescription->setText(validateData(model.record(0).value("Description").toString()));
    ui->visitRecommendation->setText(validateData(model.record(0).value("Recommendation").toString()));
    ui->visitNextVisit->setText(validateData(model.record(0).value("Next_visit").toString()));
    ui->visitTools->setText(validateData(model.record(0).value("Tools").toString()));
    ui->visitMedicines->setText(validateData(model.record(0).value("Medicines").toString()));
    ui->visitCost->setText(validateData(model.record(0).value("Cost").toString()));
    ui->visitPayment->setText(validateData(model.record(0).value("Payment").toString()));

}
QString popUpVisitWindow::validateData(QString str){
    if (str==""){
        return "Brak danych";
    }
    else{
        return str;
    }
}

popUpVisitWindow::~popUpVisitWindow()
{
    delete ui;
}

