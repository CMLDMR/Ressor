#include "stokdepo.h"

boost::optional<StokDepo::StokDepo> StokDepo::StokDepo::Create_Depo(mongocxx::database *_db, const QString &depoAdi)
{
    StokDepo item(_db);

    if( item.isValid() )
    {
        if( item.addElement(KEY::depoAdi,depoAdi) )
        {
            return std::move(item);
        }
    }
    return boost::none;
}

boost::optional<StokDepo::StokDepo> StokDepo::StokDepo::Load_Depo(mongocxx::database *_db, bsoncxx::document::view &view)
{
    StokDepo item(_db,view);

    if( item.isValid() )
    {
        return std::move(item);
    }
    return boost::none;
}

QVector<StokDepo::StokDepo *> StokDepo::StokDepo::GetList(mongocxx::database *_db, bsoncxx::builder::basic::document filter, mongocxx::options::find findOptions)
{
    QVector<StokDepo*> list;

    try {
        auto cursor = _db->collection(KEY::collection).find(filter.view(),findOptions);

        for ( auto doc : cursor ) {

            auto item = new StokDepo(_db,doc);
            if( item->isValid() )
            {
                list.push_back(item);
            }
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;

    }


    return list;
}

QString StokDepo::StokDepo::depoAdi()
{
    if( this->Element(KEY::depoAdi) )
    {
        return QString(this->Element(KEY::depoAdi)->get_utf8().value.to_string().c_str());
    }else{
        return QString("error");
    }
}

bool StokDepo::StokDepo::setDepoAdi(const QString &depoAdi)
{
    return this->addElement(KEY::depoAdi,depoAdi);
}

StokDepo::StokDepo::StokDepo(mongocxx::database *_db)
    :ItemBase (_db,KEY::collection)
{

}

StokDepo::StokDepo::StokDepo(mongocxx::database *_db, bsoncxx::document::view &view)
    :ItemBase (_db,KEY::collection,view)
{

}
