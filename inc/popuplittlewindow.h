#pragma once

#include <QDialog>

namespace Ui {
class PopUpLittleWindow;
}

class PopUpLittleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PopUpLittleWindow(QWidget *parent,QString);
    ~PopUpLittleWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PopUpLittleWindow *ui;
};

