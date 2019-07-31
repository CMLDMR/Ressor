#include "stokkartdialog.h"
#include "ui_stokkartdialog.h"

StokKartDialog::StokKartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StokKartDialog)
{
    ui->setupUi(this);
}

StokKartDialog::~StokKartDialog()
{
    delete ui;
}
