#ifndef STOKDEPO_H
#define STOKDEPO_H


#include "base/itembase.h"

namespace StokDepo {

namespace KEY {
static const std::string collection{"stokDepo"};
static const std::string depoAdi{"depoAdi"};
}


class StokDepo : public ItemBase
{
public:
    static boost::optional<StokDepo> Create_Depo( mongocxx::database* _db ,
                                           const QString &depoAdi );

    static boost::optional<StokDepo> Load_Depo(mongocxx::database* _db ,
                                        bsoncxx::document::view &view );

    static QVector<StokDepo*> GetList( mongocxx::database* _db ,
                                document filter = document{} ,
                                mongocxx::options::find findOptions = mongocxx::options::find() );

    QString depoAdi();

    bool setDepoAdi( const QString &depoAdi );

private:
    explicit StokDepo(mongocxx::database* _db);
    StokDepo(mongocxx::database* _db,
             bsoncxx::document::view &view);
};
}



#endif // STOKDEPO_H
