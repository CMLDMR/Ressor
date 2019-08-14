#ifndef CARIITEMLISTMODEL_H
#define CARIITEMLISTMODEL_H


#include <QStandardItemModel>
#include "cariitem.h"


class CariItemListModel : public QStandardItemModel , public DBClass
{
public:
    CariItemListModel(mongocxx::database* _db);

    void initModel();


private:
    QVector<CariItem::CariItem*> itemList;
};

#endif // CARIITEMLISTMODEL_H
