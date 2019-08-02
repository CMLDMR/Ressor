#include "yenistokbirimekledialog.h"
#include "ui_yenistokbirimekledialog.h"

#include <QStandardItemModel>

#include "base/stokbirim.h"

YeniStokBirimEkleDialog::YeniStokBirimEkleDialog(mongocxx::database *_db, QWidget *parent) :
    QDialog(parent),
    DBClass (_db),
    ui(new Ui::YeniStokBirimEkleDialog)
{
    ui->setupUi(this);
    mModel = new QStandardItemModel();
    ui->listView->setModel(mModel);
    this->initList();
}

YeniStokBirimEkleDialog::~YeniStokBirimEkleDialog()
{
    delete mModel;
    delete ui;
}

void YeniStokBirimEkleDialog::on_pushButton_YeniBirimEkle_clicked()
{
    auto stokBirim = StokBirim::StokBirim::CreateStokBirim(this->db(),ui->lineEdit_YeniBirimAdi->text());
    this->initList();
}

void YeniStokBirimEkleDialog::initList()
{
    auto cursor = StokBirim::StokBirim::GetStokBirimList(this->db());
    mModel->removeRows(0,mModel->rowCount());
    for( auto item : cursor )
    {
        mModel->insertRow(mModel->rowCount(),item->newQStandardItem());
    }
}

void YeniStokBirimEkleDialog::on_pushButton_deleteSecili_clicked()
{
    auto indexes = ui->listView->selectionModel()->selectedIndexes();

    for( auto item : indexes )
    {
        if( StokBirim::StokBirim::deleteBirim(this->db(),bsoncxx::oid{item.data(Qt::UserRole+1).toString().toStdString()}))
        {
            this->initList();
            break;
        }
    }
}
