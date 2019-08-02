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

QString StokKart::KartAdi()
{
    return mKartAdi.get()->c_str();
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


    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::STOKADI,kartAdi.toStdString()))));
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
                this->mKartAdi = std::make_unique<std::string>(kartAdi.toStdString());
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



    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::STOKODU,stokKodu.toStdString()))));
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
                this->mStokKodu = std::make_unique<std::string>(stokKodu.toStdString());
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

bool StokKart::setKategori(const QString &stokKategori)
{
    if( mKategori )
    {
        if( mKategori.get()->c_str() == stokKategori )
        {
            return true;
        }
    }

    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::KategoriKEY,stokKategori.toStdString()))));
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
                this->mKategori = std::make_unique<std::string>(stokKategori.toStdString());
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

    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::BirimKEY,birim.toStdString()))));
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
                this->mBirim = std::make_unique<std::string>(birim.toStdString());
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

    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::AlisFiyatKEY,alisfiyati))));
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
                this->mAlisFiyati = std::make_unique<double>(alisfiyati);
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

    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::KdvOraniKEY,kdvOrani))));
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
                this->mKDVOrani = std::make_unique<double>(kdvOrani);
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

    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::OtvOraniKEY,otvOrani))));
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
                this->mOTVOrani = std::make_unique<double>(otvOrani);
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

    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKARTKEY::SatisFiyatiKEY,satisFiyati))));
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
                this->mSatisFiyati = std::make_unique<double>(satisFiyati);
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

double StokKart::SatisFiyati() const
{
    if( mSatisFiyati )
    {
        return *mSatisFiyati.get();
    }else{
        return 0.0;
    }
}


