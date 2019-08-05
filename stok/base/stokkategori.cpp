#include "stokkategori.h"



boost::optional<STOKKATEGORI::StokKategori*> STOKKATEGORI::StokKategori::Create_Kategori(mongocxx::database *_db, const QString &kategoriName )
{

    try {
        auto kat =new StokKategori(_db,kategoriName);
        return std::move(kat);
    } catch (std::string &e) {
        return boost::none;
    }


}

QVector<boost::optional<STOKKATEGORI::StokKategori *> > STOKKATEGORI::StokKategori::GetKategoriList( mongocxx::database *_db )
{
    QVector<boost::optional<StokKategori*>> list;
    try {
        auto cursor = _db->collection(STOKKATEGORI::KATEGORICOLLECTION).find(document{}.view());

        for( auto doc : cursor )
        {
            std::cout << bsoncxx::to_json(doc) << std::endl;
            try {
                auto kat = new StokKategori(_db,doc);
                list.push_back(kat);
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
            }
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }
    return list;
}

bool STOKKATEGORI::StokKategori::DeleteKategori( mongocxx::database *_db, const bsoncxx::oid &oid )
{
    auto filter = document{};

    try {
        filter.append(kvp("_id",oid));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto del = _db->collection(STOKKATEGORI::KATEGORICOLLECTION).delete_one(filter.view());
        if( del.has_value() )
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

bool STOKKATEGORI::StokKategori::DeleteKategori(mongocxx::database *_db, const QString &kategoriName)
{
    auto filter = document{};

    try {
        filter.append(kvp(STOKKATEGORI::KATEGORIADI,kategoriName.toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto del = _db->collection(STOKKATEGORI::KATEGORICOLLECTION).delete_one(filter.view());
        if( del.has_value() )
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

void STOKKATEGORI::StokKategori::setKategoriOid(const bsoncxx::oid &oid)
{
    mKategoriOid = oid;
    this->setData(mKategoriOid.to_string().c_str(),KategoriOid);
    this->setData(this->KategoriAdi(),KategotiName);
    this->setText(this->KategoriAdi());
    this->setData(this->KategoriAdi(),Qt::DisplayRole);
}

bsoncxx::oid STOKKATEGORI::StokKategori::kategoriOid() const
{
    return mKategoriOid;
}

bool STOKKATEGORI::StokKategori::setKategoriAdi(const QString &kategoriAdi)
{
    if( mKategoriAdi )
    {
        if( mKategoriAdi.get()->c_str() == kategoriAdi )
        {
            return true;
        }
    }



    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKATEGORI::KATEGORIADI,kategoriAdi.toStdString()))));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto upt = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION).update_one(this->filter().view(),setDoc.view());

        if( upt.has_value() )
        {
            if( upt.value().modified_count() )
            {
                this->setData(kategoriAdi.toStdString().c_str(),KategotiName);
                this->setText(kategoriAdi);
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

QString STOKKATEGORI::StokKategori::KategoriAdi()
{
    if( mKategoriAdi )
    {
        return mKategoriAdi->c_str();
    }else{
        return QString("");
    }
}

bool STOKKATEGORI::StokKategori::Deletekategori()
{
    try {
        auto del = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION).delete_one(this->filter().view());
        if( del.has_value() )
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

STOKKATEGORI::StokKategori::StokKategori(mongocxx::database *_db)
    :DBClass (_db)
{
    try {
        auto ins = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION).insert_one(document{}.view());

        if( ins.has_value() )
        {
            try {
                this->setKategoriOid(ins.value().inserted_id().get_oid().value);
                this->setData(this->kategoriOid().to_string().c_str(),KategoriOid);
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
            }
        }
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }
}

STOKKATEGORI::StokKategori::StokKategori(mongocxx::database *_db, const QString &kategoriName)
    :DBClass (_db)
{
    auto filter = document{};

    try {
        filter.append(kvp(STOKKATEGORI::KATEGORIADI,kategoriName.toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        throw ("filter Oluşturulamadı");
    }


    try {
        auto val = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION).find_one(filter.view());

        if( val.has_value() )
        {
            try {
                this->setKategoriOid(val.value().view()["_id"].get_oid().value);
                this->setText(kategoriName);
                this->setKategoriAdi(kategoriName);
                return;
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                throw ("Kategori insert Edilemedi");
            }
        }
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        throw ("Veri Tabanı Bağlantı/Operasyon Hatası");
    }



    try {
        auto ins = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION).insert_one(document{}.view());

        if( ins.has_value() )
        {
            try {
                this->setKategoriOid(ins.value().inserted_id().get_oid().value);
                this->setKategoriAdi(kategoriName);
                this->setText(kategoriName);
                this->setData(mKategoriOid.to_string().c_str(),KategoriOid);
                this->setData(this->KategoriAdi(),KategotiName);
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                throw ("Kategori insert Edilemedi");
            }
        }
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        throw ("Veri Tabanı Bağlantı/Operasyon Hatası");
    }
}

STOKKATEGORI::StokKategori::StokKategori(mongocxx::database *_db, const bsoncxx::document::view &view)
    :DBClass (_db)
{

    try {
        this->mKategoriAdi = std::make_unique<std::string>(view[STOKKATEGORI::KATEGORIADI].get_utf8().value.to_string());
        this->setText(this->mKategoriAdi.get()->c_str());
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        throw (std::to_string(__LINE__) + " HATA");
    }

    try {
        this->mKategoriOid = view["_id"].get_oid().value;
        this->setKategoriOid(view["_id"].get_oid().value);
        this->setData(mKategoriOid.to_string().c_str(),KategoriOid);
        this->setData(this->KategoriAdi(),KategotiName);
        this->setText(this->KategoriAdi());
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        throw (std::to_string(__LINE__) + " HATA");
    }

}

STOKKATEGORI::StokKategori::~StokKategori()
{
    std::cout << "Deleted StokKategori " << this->text().toStdString() << std::endl;
}

bsoncxx::builder::basic::document STOKKATEGORI::StokKategori::filter()
{
    auto filter = document{};
    try {
        filter.append(kvp("_id",this->kategoriOid()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return document{};
    }
    return filter;
}

