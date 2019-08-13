#include "yenicariekledialog.h"
#include "ui_yenicariekledialog.h"
#include "yenicarigrupekledialog.h"

YeniCariEkleDialog::YeniCariEkleDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QDialog(parent),
    ui(new Ui::YeniCariEkleDialog)
{
    ui->setupUi(this);
}

YeniCariEkleDialog::~YeniCariEkleDialog()
{
    delete ui;
}

void YeniCariEkleDialog::on_pushButton_CariGrpEkle_clicked()
{
    auto mDialog = new YeniCariGrupEkleDialog(this->db());
    mDialog->exec();

    mDialog->deleteLater();
}
