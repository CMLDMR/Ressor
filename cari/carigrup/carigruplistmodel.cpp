#include "carigruplistmodel.h"

CariGrupListModel::CariGrupListModel(mongocxx::database *_db)
    :DBClass (_db)
{
    setHorizontalHeaderLabels(QStringList() << "Gruplar");
    this->initModel();
}

void CariGrupListModel::initModel()
{

    list = CariGrub::CariGrupItem::GetList(this->db());
    this->clear();
    for( auto item : list )
    {
        this->setItem(this->rowCount(), new QStandardItem(item->grupName()));
    }
}

bool CariGrupListModel::deleteItem(const int &row)
{
    if( this->list[row]->deleteItem() ){
        this->removeRow(row);
        return true;
    }else{
        return false;
    }
}
