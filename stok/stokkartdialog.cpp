#include "stokkartdialog.h"
#include "ui_stokkartdialog.h"

#include "stok/yenistokkartdialog.h"

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

void StokKartDialog::on_pushButton_YENISTOKKART_clicked()
{
    auto mDialog = std::make_unique<YeniStokKartDialog>(this->db());

    mDialog->exec();
}
