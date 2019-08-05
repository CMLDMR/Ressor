#ifndef STOKKARTMODEL_H
#define STOKKARTMODEL_H

#include "base/dbclass.h"
#include <QStandardItemModel>


class StokKart;

class StokKartModel : public QStandardItemModel , public DBClass
{
public:
    StokKartModel(mongocxx::database* _db);


    void initStokKartList();
    void insert(int row , const StokKart *kart);


private:
    QHash<int,const StokKart*> stokList;
};

#endif // STOKKARTMODEL_H
