#include "stokkartdialog.h"
#include "ui_stokkartdialog.h"

StokKartDialog::StokKartDialog(mongocxx::database* _db , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StokKartDialog),
    DBClass (_db)
{
    ui->setupUi(this);
    this->setWindowTitle("Stok Kartlar");
}

StokKartDialog::~StokKartDialog()
{
    delete ui;
}
