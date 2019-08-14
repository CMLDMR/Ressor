#ifndef CARIITEM_H
#define CARIITEM_H

#include "base/itembase.h"

namespace CariItem {


namespace KEY {
static const std::string collection{"cariler"};
static const std::string grupAdi{"grupAdi"};
static const std::string firmaAdi{"firmaAdi"};
static const std::string yetkiliKisi{"yetkiliKisi"};
static const std::string telefon{"telefon"};
static const std::string fax{"fax"};
static const std::string cepTelefonu{"cepTelefonu"};
static const std::string eMail{"eMail"};
static const std::string web{"web"};
static const std::string postaKodu{"postaKodu"};
static const std::string vergiDairesi{"vergiDairesi"};
static const std::string vergiNo{"vergiNo"};
static const std::string sicilKodu{"sicilKodu"};
static const std::string il{"il"};
static const std::string ilce{"ilce"};
}


class CariItem : public ItemBase
{
public:
    static boost::optional<CariItem> Create_CariItem(mongocxx::database* _db , const QString &firmaAdi);

    static QVector<CariItem*> GetList(mongocxx::database* _db);

private:
    CariItem(mongocxx::database* _db);
    CariItem(mongocxx::database* _db , bsoncxx::document::view &_view);


};
}



#endif // CARIITEM_H
