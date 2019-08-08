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

void StokKartModel::insert(int row, StokKart *kart)
{
    this->setItem(stokList.count(),0,new QStandardItem(kart->KartAdi()));
    this->setItem(stokList.count(),1,new QStandardItem(kart->StokKodu()));
    this->setItem(stokList.count(),2,new QStandardItem(kart->Kategori()));
    this->setItem(stokList.count(),3,new QStandardItem(kart->Birimi()));
    this->setItem(stokList.count(),4,new QStandardItem(QString("%1 ₺").arg(kart->AlisFiyati())));
    this->setItem(stokList.count(),5,new QStandardItem(QString("%%1").arg(kart->KDVOrani())));
    this->setItem(stokList.count(),6,new QStandardItem(QString("%%1").arg(kart->OTVOrani())));
    this->setItem(stokList.count(),7,new QStandardItem(QString("%1 ₺").arg(kart->SatisFiyati())));
    stokList.push_back(kart);

}

bool StokKartModel::deleteStokKart(const int &row)
{
    std::cout << __LINE__ << " Remove ROW: " << row << std::endl ;
    auto kart = stokList[row];
    if( kart->deleteStokKart() )
    {
        this->removeRow(row);
        stokList.removeAt(row);
        return true;
    }
    std::cout << __LINE__ << " Last Row Count: " << stokList.count() << std::endl ;

    return false;
}
