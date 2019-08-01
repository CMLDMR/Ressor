#include "stokkart.h"

StokKart StokKart::Create_StokKart(mongocxx::collection &_collection)
{
    StokKart kart(_collection);
    return kart;
}

StokKart StokKart::Load_StokKart(mongocxx::collection &_collection, const bsoncxx::oid &kartOid)
{
    StokKart kart(_collection,kartOid);
    return kart;
}

const bsoncxx::builder::basic::document StokKart::StokKartDocument()
{

    auto rDoc = document{};

    try {
        rDoc.append(kvp(STOKKARTKEY::STOKADI,this->KartAdi().toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;

    }



    return rDoc;
}

StokKart::StokKart(mongocxx::collection &_collection)
    :collection(_collection)
{
    try {
        auto ins = this->collection.insert_one(document{}.view());

        if( ins.has_value() )
        {
            try {
                this->setStokKartOid(ins.value().inserted_id().get_oid().value);
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
            }
        }
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }
}

StokKart::StokKart(mongocxx::collection &_collection, const bsoncxx::oid &kartOid)
    :collection(_collection)
{
    this->setStokKartOid(kartOid);
}

bsoncxx::builder::basic::document StokKart::filterByOid()
{
    auto filter = document{};

    try {
        filter.append(kvp("_id",this->stokKartOid()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }

    return filter;
}

bsoncxx::oid StokKart::stokKartOid() const
{
    return mStokKartOid;
}

void StokKart::setStokKartOid(const bsoncxx::oid &stokKartOid)
{
    mStokKartOid = stokKartOid;
}

QString StokKart::KartAdi()
{

    mongocxx::options::find findOptions;


    auto project = document{};

    try {
        project.append(kvp(STOKKARTKEY::STOKADI,true));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }


    findOptions.projection(project.view());


    try {
        auto val = this->collection.find_one(this->filterByOid().view(),findOptions);

        if( val.has_value() )
        {
            try {
                return QString::fromStdString(val.value().view()[STOKKARTKEY::STOKADI].get_utf8().value.to_string());
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                return QString();
            }
        }else{
            return QString();
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return QString();
    }




}

bool StokKart::setKartAdi(const QString &kartAdi)
{
    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::STOKADI,kartAdi.toStdString()))));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto upt = this->collection.update_one(this->filterByOid().view(),setDoc.view());

        if( upt.has_value() )
        {
            if( upt.value().modified_count() )
            {
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }
}

QString StokKart::StokKodu()
{
    mongocxx::options::find findOptions;


    auto project = document{};

    try {
        project.append(kvp(STOKKARTKEY::STOKODU,true));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }


    findOptions.projection(project.view());


    try {
        auto val = this->collection.find_one(this->filterByOid().view(),findOptions);

        if( val.has_value() )
        {
            try {
                return QString::fromStdString(val.value().view()[STOKKARTKEY::STOKODU].get_utf8().value.to_string());
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                return QString();
            }
        }else{
            return QString();
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return QString();
    }
}

bool StokKart::setStokKodu(const QString &stokKodu)
{
    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::STOKADI,stokKodu.toStdString()))));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto upt = this->collection.update_one(this->filterByOid().view(),setDoc.view());

        if( upt.has_value() )
        {
            if( upt.value().modified_count() )
            {
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }
}
