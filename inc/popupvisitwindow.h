#pragma once
#include <QDialog>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {class popUpVisitWindow;}
QT_END_NAMESPACE

class popUpVisitWindow : public QDialog
{
    Q_OBJECT
public:
    popUpVisitWindow(QWidget *,QString, QSqlRelationalTableModel &);
    ~popUpVisitWindow();
    QString validateData(QString);

private:
    Ui::popUpVisitWindow *ui;
};
