#include "cariitem.h"

boost::optional<CariItem::CariItem> CariItem::CariItem::Create_CariItem(mongocxx::database *_db, const QString &firmaAdi)
{
    CariItem item(_db);
    if( item.isValid() )
    {
        if( item.addElement(KEY::firmaAdi,firmaAdi.toStdString()) ){
            return std::move(item);
        }else{
            return boost::none;
        }
    }else{
        return boost::none;
    }
}

QVector<CariItem::CariItem *> CariItem::CariItem::GetList(mongocxx::database *_db)
{
    QVector<CariItem*> list;

    try {
        auto cursor = _db->collection(KEY::collection).find(document{}.view());

        for( auto doc : cursor )
        {
            CariItem *item = new CariItem(_db,doc);
            list.push_back((item));
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }
    return  list;
}

CariItem::CariItem::CariItem(mongocxx::database *_db)
    :ItemBase (_db,KEY::collection)
{

}

CariItem::CariItem::CariItem(mongocxx::database *_db, bsoncxx::document::view &_view)
    :ItemBase (_db,KEY::collection,_view)
{

}
