#include "carigrupitem.h"

boost::optional<CariGrub::CariGrupItem> CariGrub::CariGrupItem::Create_CariGrup( mongocxx::database *_db, const QString &cariGrupName )
{
    if( checkName(_db,cariGrupName) ){
        return boost::none;
    }else{
        CariGrupItem item(_db);
        if( item.isValid() )
        {
            if( item.setGrupName(cariGrupName) ){
                std::cout << bsoncxx::to_json(item.view()) << std::endl;
                return std::move(item);
            }else{
                return boost::none;
            }
        }else{
            return boost::none;
        }
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



bool CariGrub::CariGrupItem::checkName(mongocxx::database *_db, const QString &grupName)
{
    auto filter_ = document{};

    try {
        filter_.append(kvp(KEY::grupAdi,grupName.toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return true;
    }

    try {
        auto count = _db->collection(KEY::collection).count_documents(filter_.view());

        if( count )
        {
            return true;
        }else{
            return false;
        }

    } catch (mongocxx::query_exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return true;
    }

}

QString CariGrub::CariGrupItem::grupName() const
{
    return mGrupName;
}

bool CariGrub::CariGrupItem::setGrupName(const QString &grupName)
{
    return this->addElement(KEY::grupAdi,grupName.toStdString());
}

