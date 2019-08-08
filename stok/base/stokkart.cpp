#include "stokkart.h"


#include <QString>

boost::optional<StokKart> StokKart::Create_StokKart(mongocxx::database *_db)
{
    StokKart kart(_db);
    if( kart.isValid )
    {
        return std::move(kart);
    }else{
        boost::none;
    }
}

QVector<boost::optional<StokKart *> > StokKart::GetList(mongocxx::database *_db)
{

    QVector<boost::optional<StokKart*>> list;



    try {
        auto cursor = _db->collection(STOKKARTKEY::STOKCOLLECTION).find(document{}.view());

        for( auto doc : cursor )
        {
            auto item = new StokKart(_db,doc);
            if( item->isValid )
            {
                list.push_back(item);
            }
        }


    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;

    }


    return list;

}





StokKart::StokKart(mongocxx::database *_db)
    :DBClass(_db)
{
    try {
        auto ins = this->db()->collection(STOKKARTKEY::STOKCOLLECTION).insert_one(document{}.view());

        if( ins.has_value() )
        {
            try {
                this->mStokKartOid = ins.value().inserted_id().get_oid().value;
                isValid = true;
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                isValid = false;
            }
        }else{
            isValid = false;
        }
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
    }
}

StokKart::StokKart(mongocxx::database *_db, const bsoncxx::document::view &view)
    :DBClass (_db)
{

    try {
        this->mStokKodu = std::make_unique<std::string>(view[STOKKARTKEY::STOKODU].get_utf8().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    try {
        this->mKartAdi = std::make_unique<std::string>(view[STOKKARTKEY::STOKADI].get_utf8().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    try {
        this->mKategori = std::make_unique<std::string>(view[STOKKARTKEY::KategoriKEY].get_utf8().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    try {
        this->mBirim = std::make_unique<std::string>(view[STOKKARTKEY::BirimKEY].get_utf8().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    try {
        this->mAlisFiyati = std::make_unique<double>(view[STOKKARTKEY::AlisFiyatKEY].get_double().value);
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    try {
        this->mKDVOrani = std::make_unique<double>(view[STOKKARTKEY::KdvOraniKEY].get_double().value);
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }


    try {
        this->mOTVOrani = std::make_unique<double>(view[STOKKARTKEY::OtvOraniKEY].get_double().value);
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    try {
        this->mSatisFiyati = std::make_unique<double>(view[STOKKARTKEY::SatisFiyatiKEY].get_double().value);
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    try {
        this->mStokKartOid = view["_id"].get_oid().value;
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        isValid = false;
        return;
    }

    isValid = true;
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

bool StokKart::deleteStokKart()
{
    try {
        auto del = this->db()->collection(STOKKARTKEY::STOKCOLLECTION).delete_one(this->filterByOid().view());

        if( del )
        {
            if( del.value().deleted_count() )
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

QString StokKart::KartAdi() const
{
    if( mKartAdi )
    {
        return mKartAdi.get()->c_str();
    }else{
        return QString();
    }
}

bool StokKart::setKartAdi(const QString &kartAdi)
{
    if( mKartAdi )
    {
        if( kartAdi.toStdString() == (mKartAdi.get()->c_str()) )
        {
            return true;
        }
    }

    if( this->setElement(STOKKARTKEY::STOKADI,kartAdi.toStdString()) ){
        this->mKartAdi = std::make_unique<std::string>(kartAdi.toStdString());
        return true;
    }else{
        return false;
    }



}

QString StokKart::StokKodu() const
{
    if( mStokKodu )
    {
        return mStokKodu->c_str();
    }else{
        return QString();
    }

}

bool StokKart::setStokKodu(const QString &stokKodu)
{

    if( mStokKodu )
    {
        if( stokKodu == QString::fromStdString(mStokKodu.get()->c_str()) )
        {
            return true;
        }
    }


    if( this->setElement(STOKKARTKEY::STOKODU,stokKodu.toStdString()) ){
        this->mStokKodu = std::make_unique<std::string>(stokKodu.toStdString());
        return true;
    }else{
        return false;
    }

}

bool StokKart::setKategori(const QString &stokKategori)
{
    if( mKategori )
    {
        if( mKategori.get()->c_str() == stokKategori )
        {
            return true;
        }
    }


    if( this->setElement(STOKKARTKEY::KategoriKEY,stokKategori.toStdString()) ){
        this->mKategori = std::make_unique<std::string>(stokKategori.toStdString());
        return true;
    }else{
        return false;
    }


}

QString StokKart::Kategori() const
{
    if( this->mKategori )
    {
        return this->mKategori.get()->c_str();
    }else{
        return QString();
    }
}

bool StokKart::setBirim(const QString &birim)
{
    if( mBirim )
    {
        if( mBirim.get()->c_str() == birim )
        {
            return true;
        }
    }


    if( this->setElement(STOKKARTKEY::BirimKEY,birim.toStdString()) ){
        this->mBirim = std::make_unique<std::string>(birim.toStdString());
        return true;
    }else{
        return false;
    }



}

const QString StokKart::Birimi() const
{
    if( mBirim )
    {
        return mBirim.get()->c_str();
    }else{
        return QString();
    }
}

bool StokKart::setAlisFiyati(const double &alisfiyati)
{

    if( mAlisFiyati )
    {
        if( *mAlisFiyati.get() == alisfiyati )
        {
            return true;
        }
    }

    if( this->setElement(STOKKARTKEY::AlisFiyatKEY,alisfiyati) ){
        this->mAlisFiyati = std::make_unique<double>(alisfiyati);
        return true;
    }else{
        return false;
    }

}

double StokKart::AlisFiyati() const
{
    if( mAlisFiyati )
    {
        return *mAlisFiyati.get();
    }else{
        return 0.0;
    }
}

bool StokKart::setKDVOrani(const double &kdvOrani)
{
//    KdvOraniKEY
    if( mKDVOrani )
    {
        if( *mKDVOrani.get() == kdvOrani )
        {
            return true;
        }
    }


    if( this->setElement(STOKKARTKEY::KdvOraniKEY,kdvOrani) ){
        this->mKDVOrani = std::make_unique<double>(kdvOrani);
        return true;
    }else{
        return false;
    }



}

double StokKart::KDVOrani() const
{
    if( mKDVOrani )
    {
        return *mKDVOrani.get();
    }else{
        return 0.0;
    }
}

bool StokKart::setOTVOrani(const double &otvOrani)
{
    if( mOTVOrani )
    {
        if( *mOTVOrani.get() == otvOrani )
        {
            return true;
        }
    }


    if( this->setElement(STOKKARTKEY::OtvOraniKEY,otvOrani) ){
        this->mOTVOrani = std::make_unique<double>(otvOrani);
        return true;
    }else{
        return false;
    }

}

double StokKart::OTVOrani() const
{
    if( mOTVOrani )
    {
        return *mOTVOrani.get();
    }else{
        return 0.0;
    }
}

bool StokKart::setSatisFiyati(const double &satisFiyati)
{
    if( mSatisFiyati )
    {
        if( *mSatisFiyati.get() == satisFiyati )
        {
            return true;
        }
    }


    if( this->setElement(STOKKARTKEY::SatisFiyatiKEY,satisFiyati) ){
        this->mSatisFiyati = std::make_unique<double>(satisFiyati);
        return true;
    }else{
        return false;
    }
}

double StokKart::SatisFiyati() const
{
    if( mSatisFiyati )
    {
        return *mSatisFiyati.get();
    }else{
        return 0.0;
    }
}



template<typename T>
bool StokKart::setElement(const std::string &key, const T &value)
{

    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(key,value))));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto upt = this->db()->collection(STOKKARTKEY::STOKCOLLECTION).update_one(this->filterByOid().view(),setDoc.view());

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
