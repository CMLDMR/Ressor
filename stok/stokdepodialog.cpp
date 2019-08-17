#include "stokdepodialog.h"
#include "ui_stokdepodialog.h"

StokDepoDialog::StokDepoDialog(mongocxx::database *_db, QWidget *parent) :
    QDialog(parent),
    DBClass (_db),
    ui(new Ui::StokDepoDialog)
{
    ui->setupUi(this);

    mModel = new StokDepoModel(this->db());

    ui->listView->setModel(mModel);
}

StokDepoDialog::~StokDepoDialog()
{
    delete ui;
}

void StokDepoDialog::on_pushButton_Ekle_clicked()
{
    mModel->initModel();
}
