#include "stokkategoridialog.h"
#include "ui_stokkategoridialog.h"
#include "base/stokkategori.h"
#include <QStandardItemModel>

StokKategoriDialog::StokKategoriDialog(mongocxx::database *_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StokKategoriDialog),
    DBClass (_db)
{
    ui->setupUi(this);

    mKategoriModel = new QStandardItemModel();
    ui->listView_KategoriList->setModel(mKategoriModel);

    this->initList();

}

StokKategoriDialog::~StokKategoriDialog()
{
    delete mKategoriModel;
    delete ui;
}

void StokKategoriDialog::on_pushButton_YeniKaydet_clicked()
{
    auto coll = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION);
    auto kat = STOKKATEGORI::StokKategori::Create_Kategori(&coll,ui->lineEdit_YeniStokKategroi->text());

    this->initList();
}

void StokKategoriDialog::initList()
{

    auto coll = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION);
    auto list = STOKKATEGORI::StokKategori::GetKategoriList(&coll);

    mKategoriModel->removeRows(0,mKategoriModel->rowCount());

    for( auto item : list )
    {
        mKategoriModel->insertRow(0,item);
    }
}
