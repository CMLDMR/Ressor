#include "stokbirim.h"

#include <QString>



boost::optional<StokBirim::StokBirim> StokBirim::StokBirim::CreateStokBirim(mongocxx::database *_db, const QString &stokBirim)
{
    auto val = exist(_db,stokBirim);

    if( val.has_value() )
    {
        return val;
    }else{
        return StokBirim( _db , stokBirim );
    }
}

QVector<StokBirim::StokBirim* > StokBirim::StokBirim::GetStokBirimList(mongocxx::database *_db)
{
    QVector<StokBirim*> list;
    try {
        auto cursor = _db->collection(StokBirimCollection).find(document{}.view());

        for( auto doc : cursor )
        {

            bool error = false;

            StokBirim *birim = new StokBirim(_db);

            try {
                birim->setBirimAdi(doc[StokBirimAdi].get_utf8().value.to_string().c_str());
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                error = true;
            }

            try {
                birim->setBirimOid(doc["_id"].get_oid().value.to_string().c_str());
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                error = true;
            }

            if( !error )
            {
                list.push_back(std::move(birim));
            }
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;

    }

    return list;
}

QStandardItem *StokBirim::StokBirim::newQStandardItem()
{
    QStandardItem* item = new QStandardItem();
    item->setText(this->mBirimAdi.get()->c_str());
    item->setData(this->mBirimOid.get()->c_str(),Qt::UserRole+1);
    return item;
}

void StokBirim::StokBirim::setBirimAdi(const QString &newBirimAdi)
{
    mBirimAdi = std::make_unique<std::string>(newBirimAdi.toStdString());
}

QString StokBirim::StokBirim::getBirimAdi() const
{
    return this->mBirimAdi->c_str();
}

void StokBirim::StokBirim::setBirimOid(const QString &birimOid)
{
    mBirimOid = std::make_unique<std::string>(birimOid.toStdString());
}

bsoncxx::oid StokBirim::StokBirim::getBirimOid() const
{
    return bsoncxx::oid{this->mBirimOid.get()->c_str()};
}

StokBirim::StokBirim::StokBirim(mongocxx::database *_db, const QString &stokBirim)
    :DBClass (_db)
{

    auto insDoc = document{};

    try {
        insDoc.append(kvp(StokBirimAdi,stokBirim.toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;

    }


    try {
        auto ins = this->db()->collection(StokBirimCollection).insert_one(insDoc.view());

        if( ins.has_value() )
        {
            this->setBirimAdi(stokBirim);
            this->setBirimOid(ins.value().inserted_id().get_oid().value.to_string().c_str());
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;

    }

}

StokBirim::StokBirim::StokBirim(mongocxx::database *_db)
    :DBClass (_db)
{

}

boost::optional<StokBirim::StokBirim> StokBirim::StokBirim::exist(mongocxx::database *_db, const QString &stokBirim)
{
    auto filter = document{};

    try {
        filter.append(kvp(StokBirimAdi,stokBirim.toStdString()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return boost::none;
    }

    try {
        auto val = _db->collection(StokBirimCollection).find_one(filter.view());
        if( val.has_value() )
        {
            try {
                StokBirim stokBirimObj(_db);
                stokBirimObj.setBirimAdi(stokBirim);
                stokBirimObj.setBirimOid(val.value().view()["_id"].get_oid().value.to_string().c_str());
                return std::move(stokBirimObj);
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                return boost::none;
            }
        }else{
            return boost::none;
        }

    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
        return boost::none;
    }
}
