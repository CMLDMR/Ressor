#ifndef ITEMBASEMODEL_H
#define ITEMBASEMODEL_H

#include "dbclass.h"
#include <QStandardItemModel>

#include <QDebug>

template<class T>
class ItemBaseModel : public QStandardItemModel , public DBClass
{

private:
    QVector<T*> itemList;

public:





    explicit ItemBaseModel(mongocxx::database* _db)
        :DBClass(_db)
    {

    }


    void initModel()
    {
        itemList = T::GetList(this->db());


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
};


#endif // ITEMBASEMODEL_H
