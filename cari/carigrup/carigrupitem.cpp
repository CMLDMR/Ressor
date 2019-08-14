#include "carigrupitem.h"

boost::optional<CariGrub::CariGrupItem> CariGrub::CariGrupItem::Create_CariGrup( mongocxx::database *_db, const QString &cariGrupName )
{

    CariGrupItem item(_db);
    if( item.isValid() )
    {
        if( item.setGrupName(cariGrupName) ){
            return std::move(item);
        }else{
            return boost::none;
        }
    }else{
        return boost::none;
    }
}

QVector<CariGrub::CariGrupItem*> CariGrub::CariGrupItem::GetList(mongocxx::database *_db)
{
    QVector<CariGrupItem*> list;

    try {
        auto cursor = _db->collection(KEY::collection).find(document{}.view());

        for( auto doc : cursor )
        {
            CariGrupItem *item = new CariGrupItem(_db,doc);
            list.push_back((item));
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }
    return  list;
}

CariGrub::CariGrupItem::CariGrupItem(mongocxx::database *_db)
    :ItemBase (_db,KEY::collection)
{

}

CariGrub::CariGrupItem::CariGrupItem(mongocxx::database *_db, bsoncxx::document::view &_view)
    :ItemBase (_db,KEY::collection,_view)
{

}





QString CariGrub::CariGrupItem::grupName()
{
    try {
        return QString::fromStdString(this->Element(KEY::grupAdi).get_utf8().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return "error";
    }
}

bool CariGrub::CariGrupItem::setGrupName(const QString &grupName)
{
    return this->addElement(KEY::grupAdi,grupName.toStdString());
}

