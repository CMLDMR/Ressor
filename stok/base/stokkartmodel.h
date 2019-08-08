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
    void insert(int row , StokKart *kart);
    bool deleteStokKart( const int &row );

    StokKart* stokKart(const int &index);


private:
    QVector<StokKart*> stokList;
};

#endif // STOKKARTMODEL_H
