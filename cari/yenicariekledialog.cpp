#include "yenicariekledialog.h"
#include "ui_yenicariekledialog.h"
#include "yenicarigrupekledialog.h"
#include "carigrup/carigruplistmodel.h"
#include "cariItem/cariitem.h"

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

void YeniCariEkleDialog::on_pushButton_KaydetCik_clicked()
{
    auto item = CariItem::CariItem::Create_CariItem(this->db(),ui->lineEdit_FirmaAdi->text());

    if( item )
    {
        item->addElement(CariItem::KEY::yetkiliKisi,ui->lineEdit_FirmaYetkili->text().toStdString());
        item->addElement(CariItem::KEY::grupAdi,ui->comboBox_CariGruplar->currentText().toStdString());
        item->addElement(CariItem::KEY::telefon,ui->lineEdit_Telefon->text().toStdString());
        item->addElement(CariItem::KEY::fax,ui->lineEdit_Fax->text().toStdString());
        item->addElement(CariItem::KEY::cepTelefonu,ui->lineEdit_CepTelefonu->text().toStdString());
        item->addElement(CariItem::KEY::eMail,ui->lineEdit_eMail->text().toStdString());
        item->addElement(CariItem::KEY::web,ui->lineEdit_Web->text().toStdString());
        item->addElement(CariItem::KEY::postaKodu,ui->lineEdit_PostaKodu->text().toStdString());
        item->addElement(CariItem::KEY::vergiDairesi,ui->lineEdit_VergiDairesi->text().toStdString());
        item->addElement(CariItem::KEY::vergiNo,ui->lineEdit_VergiNo->text().toStdString());
        item->addElement(CariItem::KEY::sicilKodu,ui->lineEdit_SicilNo->text().toStdString());
        item->addElement(CariItem::KEY::il,ui->lineEdit_il->text().toStdString());
        item->addElement(CariItem::KEY::ilce,ui->lineEdit_ilce->text().toStdString());
    }

    this->close();

}
