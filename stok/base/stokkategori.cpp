#include "stokkategori.h"



STOKKATEGORI::StokKategori STOKKATEGORI::StokKategori::Create_Kategori( mongocxx::collection *collection, const QString &kategoriName )
{
    StokKategori kat(collection,kategoriName);
    return kat;
}

QVector<STOKKATEGORI::StokKategori *> STOKKATEGORI::StokKategori::GetKategoriList( mongocxx::collection *collection )
{
    QVector<StokKategori*> list;
    try {
        auto cursor = collection->find(document{}.view());

        for( auto doc : cursor )
        {
            std::cout << "GETLIST: " << bsoncxx::to_json(doc) << std::endl;
            try {
                auto kat = new StokKategori(collection,doc["_id"].get_oid().value);
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

bool STOKKATEGORI::StokKategori::DeleteKategori( mongocxx::collection *collection, const bsoncxx::oid &oid )
{
    auto filter = document{};

    try {
        filter.append(kvp("_id",oid));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto del = collection->delete_one(filter.view());
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

bool STOKKATEGORI::StokKategori::DeleteKategori(mongocxx::collection *collection, const QString &kategoriName)
{
    auto filter = document{};

    try {
        filter.append(kvp(STOKKATEGORI::KATEGORIADI,kategoriName.toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto del = collection->delete_one(filter.view());
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
    auto setDoc = document{};


    try {
        setDoc.append(kvp("$set",make_document(kvp(STOKKATEGORI::KATEGORIADI,kategoriAdi.toStdString()))));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return false;
    }


    try {
        auto upt = this->mCollection->update_one(this->filter().view(),setDoc.view());

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
    try {
        auto val = this->mCollection->find_one(this->filter().view());
        if( val.has_value() )
        {
            try {
                return QString::fromStdString(val.value().view()[STOKKATEGORI::KATEGORIADI].get_utf8().value.to_string());
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

bool STOKKATEGORI::StokKategori::Deletekategori()
{
    try {
        auto del = mCollection->delete_one(this->filter().view());
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

STOKKATEGORI::StokKategori::StokKategori(mongocxx::collection *collection)
    :mCollection(collection)
{
    try {
        auto ins = this->mCollection->insert_one(document{}.view());

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

STOKKATEGORI::StokKategori::StokKategori(mongocxx::collection *collection, const QString &kategoriName)
    :mCollection(collection)
{
    auto filter = document{};

    try {
        filter.append(kvp(STOKKATEGORI::KATEGORIADI,kategoriName.toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;

    }


    try {
        auto val = collection->find_one(filter.view());

        if( val.has_value() )
        {
            try {
                this->setKategoriOid(val.value().view()["_id"].get_oid().value);
                this->setText(kategoriName);
                return;
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
            }
        }
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }



    try {
        auto ins = this->mCollection->insert_one(document{}.view());

        if( ins.has_value() )
        {
            try {
                this->setKategoriOid(ins.value().inserted_id().get_oid().value);
                this->setKategoriAdi(kategoriName);
                this->setText(kategoriName);
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
            }
        }
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }
}

STOKKATEGORI::StokKategori::StokKategori(mongocxx::collection *collection, const bsoncxx::oid &oid)
    :mCollection(collection)
{
    this->setKategoriOid(oid);
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

