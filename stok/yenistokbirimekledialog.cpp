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


    if( stokBirim )
    {
        std::cout << "VALUE" << std::endl;
    }else{
        std::cout << "NOVALUE() " << std::endl;
    }


    if( stokBirim.has_value() )
    {
        std::cout << stokBirim->getBirimAdi().toStdString() << std::endl;
        std::cout << stokBirim->getBirimOid().to_string() << std::endl;
    }else{
        std::cout << "NOVALUE" << std::endl;
    }


    this->initList();







}

void YeniStokBirimEkleDialog::initList()
{
    auto cursor = StokBirim::StokBirim::GetStokBirimList(this->db());
    mModel->removeRows(0,mModel->rowCount());
    for( auto item : cursor )
    {
        std::cout << item->getBirimAdi().toStdString() << std::endl;

        mModel->insertRow(0,item->newQStandardItem());
        //        if( item )
//        {
//
//        }
    }
}
