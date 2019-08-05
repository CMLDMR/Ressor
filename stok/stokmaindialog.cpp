#include "stokmaindialog.h"
#include "ui_stokmaindialog.h"

#include "stokkartdialog.h"
#include "yenistokkartdialog.h"
#include "base/stokkartmodel.h"


StokMainDialog::StokMainDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QDialog(parent),
    ui(new Ui::StokMainDialog)

{
    ui->setupUi(this);

    mkartModel = new StokKartModel (this->db());

    ui->tableView_StokKartView->setModel(mkartModel);

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

void StokMainDialog::on_pushButton_ListeyiGuncelle_clicked()
{
    this->mkartModel->initStokKartList();
}
