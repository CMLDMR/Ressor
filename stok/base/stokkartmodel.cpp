#include "stokkartmodel.h"
#include "stokkart.h"


StokKartModel::StokKartModel(mongocxx::database *_db)
    :DBClass (_db)
{
    this->setHorizontalHeaderLabels(QStringList() << "Stok Kodu"
                                    << "Stok Adı"
                                    << "Kategori"
                                    << "Birim"
                                    << "Alış Fiyatı"
                                    << "KDV Oranı"
                                    << "ÖTV Oranı"
                                    << "Satış Fiyatı");



    this->initStokKartList();

}

void StokKartModel::initStokKartList()
{
    this->removeRows(0,this->rowCount());
    auto list = StokKart::GetList(this->db());
    stokList.clear();
    for (auto item : list) {
        this->insert(this->rowCount(),item.value());
    }
}

void StokKartModel::insert(int row, const StokKart *kart)
{
    stokList[row] = kart;
    this->setItem(row,0,new QStandardItem(kart->KartAdi()));
    this->setItem(row,1,new QStandardItem(kart->StokKodu()));
    this->setItem(row,2,new QStandardItem(kart->Kategori()));
    this->setItem(row,3,new QStandardItem(kart->Birimi()));
    this->setItem(row,4,new QStandardItem(QString("%1 ₺").arg(kart->AlisFiyati())));
    this->setItem(row,5,new QStandardItem(QString("%%1").arg(kart->KDVOrani())));
    this->setItem(row,6,new QStandardItem(QString("%%1").arg(kart->OTVOrani())));
    this->setItem(row,7,new QStandardItem(QString("%1 ₺").arg(kart->SatisFiyati())));
}
