#include "stokmaindialog.h"
#include "ui_stokmaindialog.h"

StokMainDialog::StokMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StokMainDialog)
{
    ui->setupUi(this);
}

StokMainDialog::~StokMainDialog()
{
    delete ui;
}
