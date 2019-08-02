#ifndef STOKBIRIM_H
#define STOKBIRIM_H

#include "base/dbclass.h"
#include <boost/optional.hpp>
#include <QStandardItem>
#include <QVector>

class QString;

namespace StokBirim {


static const std::string StokBirimAdi{"stokbirimadi"};
static const std::string StokBirimCollection{"StokBirim"};

class StokBirim : public DBClass
{
public:

    static boost::optional<StokBirim> CreateStokBirim(mongocxx::database* _db , const QString &stokBirim);


    static QVector<StokBirim *> GetStokBirimList(mongocxx::database *_db);


    QStandardItem* newQStandardItem();

    void setBirimAdi( const QString &newBirimAdi );

    QString getBirimAdi() const;

    void setBirimOid( const QString &birimOid );

    bsoncxx::oid getBirimOid() const;

private:
    StokBirim(mongocxx::database* _db , const QString &stokBirim );
    StokBirim(mongocxx::database* _db );


    std::unique_ptr<std::string> mBirimAdi;

    std::unique_ptr<std::string> mBirimOid;


    static boost::optional<StokBirim> exist(mongocxx::database* _db , const QString &stokBirim );
};


}




#endif // STOKBIRIM_H
