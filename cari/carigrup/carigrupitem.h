#ifndef CARIGRUPITEM_H
#define CARIGRUPITEM_H

#include "base/itembase.h"
#include <QString>
#include <QVector>

namespace CariGrub {

namespace KEY {

static const std::string collection{"cariGrup"};
static const std::string grupAdi{"grupAdi"};

}

class CariGrupItem : public ItemBase
{
public:
    static boost::optional<CariGrupItem> Create_CariGrup(mongocxx::database* _db , const QString &cariGrupName);

    static QVector<CariGrupItem*> GetList(mongocxx::database* _db);

    QString grupName();
    bool setGrupName(const QString &grupName);

private:
    CariGrupItem(mongocxx::database *_db);
    CariGrupItem(mongocxx::database* _db , bsoncxx::document::view &_view);

};


}



#endif // CARIGRUPITEM_H
