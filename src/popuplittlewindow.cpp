#include "popuplittlewindow.h"
#include "ui_popuplittlewindow.h"

PopUpLittleWindow::PopUpLittleWindow(QWidget *parent, QString string) :
    QDialog(parent),
    ui(new Ui::PopUpLittleWindow)
{
    ui->setupUi(this);
    ui->label->setText(string);
}

PopUpLittleWindow::~PopUpLittleWindow()
{
    delete ui;
}

void PopUpLittleWindow::on_pushButton_clicked()
{
    this->close();

}
