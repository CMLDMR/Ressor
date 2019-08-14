#ifndef CARIGRUPLISTMODEL_H
#define CARIGRUPLISTMODEL_H


#include <QStandardItemModel>
#include "base/dbclass.h"
#include <QVector>
#include "carigrupitem.h"

class CariGrupListModel : public QStandardItemModel , public DBClass
{
public:
    CariGrupListModel(mongocxx::database* _db);

    void initModel();

    bool deleteItem(const int &row);


private:

    QVector<CariGrub::CariGrupItem*> list;
};

#endif // CARIGRUPLISTMODEL_H
