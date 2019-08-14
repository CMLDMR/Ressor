#include "yenicariekledialog.h"
#include "ui_yenicariekledialog.h"
#include "yenicarigrupekledialog.h"
#include "carigrup/carigruplistmodel.h"

YeniCariEkleDialog::YeniCariEkleDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QDialog(parent),
    ui(new Ui::YeniCariEkleDialog)
{
    ui->setupUi(this);

    mGrupModel = new CariGrupListModel(this->db());
    ui->comboBox_CariGruplar->setModel(mGrupModel);
}

YeniCariEkleDialog::~YeniCariEkleDialog()
{
    delete ui;
}

void YeniCariEkleDialog::on_pushButton_CariGrpEkle_clicked()
{
    auto mDialog = new YeniCariGrupEkleDialog(this->db());
    mDialog->exec();

    mGrupModel->initModel();

    mDialog->deleteLater();
}
