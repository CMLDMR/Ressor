#include "stokmaindialog.h"
#include "ui_stokmaindialog.h"

#include "stokkartdialog.h"
#include "yenistokkartdialog.h"

StokMainDialog::StokMainDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QDialog(parent),
    ui(new Ui::StokMainDialog)

{
    ui->setupUi(this);
}

StokMainDialog::~StokMainDialog()
{
    std::cout << "Stok Main Destructor" << std::endl;
    delete ui;
}


void StokMainDialog::on_pushButton_StokKartTanimla_clicked()
{
        auto mDialog = std::make_unique<YeniStokKartDialog>(this->db());

        mDialog->exec();
}
