#include "cariitemlistmodel.h"

#include <QDebug>

CariItemListModel::CariItemListModel(mongocxx::database *_db)
    :DBClass (_db)
{
    this->setHorizontalHeaderLabels(QStringList()<<"Grup"
                                    <<"Firma Adı"
                                    <<"Yetkili"
                                    <<"Telefon"
                                    <<"Fax"
                                    <<"Cep Telefonu"
                                    <<"Mail"
                                    <<"Web"
                                    <<"Posta Kodu"
                                    <<"Vergi Dairesi"
                                    <<"Vergi NO"
                                    <<"Sicil Kodu"
                                    <<"İl"
                                    <<"İlçe");

    this->initModel();

}


void CariItemListModel::initModel()
{
    itemList = CariItem::CariItem::GetList(this->db());


    if( itemList.count() )
    {
        this->clear();
        auto firstItem = itemList.first();
        this->setHorizontalHeaderLabels(firstItem->keyList());

        int CurrentRow = 0;
        for( auto item : itemList )
        {

            QStringList noneExistKeyList;

            for( auto keyList : item->keyList() )
            {
                bool exist = false;

                for (int i = 0 ; i < this->columnCount() ; i++ ) {

                    if( this->horizontalHeaderItem(i)->text().toStdString() == keyList.toStdString() )
                    {
                        exist = true;
                    }
                }
                if( !exist )
                {
                    this->setHorizontalHeaderItem(this->columnCount(),new QStandardItem(keyList) );
                }
            }


            for (int i = 0 ; i < this->columnCount() ; i++ ) {
                for( auto keyList : item->keyList() )
                {
                    if( this->horizontalHeaderItem(i)->text().toStdString() == keyList.toStdString() )
                    {
                        if(item->Element(keyList.toStdString())->type() == bsoncxx::type::k_utf8 )
                        {
                            this->setItem(CurrentRow,i,new QStandardItem(item->Element(keyList.toStdString())->get_utf8().value.to_string().c_str()));
                        }
                        if(item->Element(keyList.toStdString())->type() == bsoncxx::type::k_oid )
                        {
                            this->setItem(CurrentRow,i,new QStandardItem(item->Element(keyList.toStdString())->get_oid().value.to_string().c_str()));
                        }
                    }
                }
            }




            CurrentRow++;
        }
    }



}
