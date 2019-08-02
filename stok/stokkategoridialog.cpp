#include "stokkategoridialog.h"
#include "ui_stokkategoridialog.h"

StokKategoriDialog::StokKategoriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StokKategoriDialog)
{
    ui->setupUi(this);
}

StokKategoriDialog::~StokKategoriDialog()
{
    delete ui;
}
