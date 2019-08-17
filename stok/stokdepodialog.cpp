#include "stokdepodialog.h"
#include "ui_stokdepodialog.h"

StokDepoDialog::StokDepoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StokDepoDialog)
{
    ui->setupUi(this);
}

StokDepoDialog::~StokDepoDialog()
{
    delete ui;
}
