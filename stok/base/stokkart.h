#ifndef STOKKART_H
#define STOKKART_H


#include "mongoheaders.h"
#include <QString>

namespace STOKKARTKEY {
    static const std::string STOKADI{"stokadı"};
}

class StokKart
{
public:

    ///
    /// \brief Create_StokKart
    /// \param _collection
    /// \return
    /// Veri Tabanına Bağlı Bir Adet Stok Kartı Oluşturur.
    static StokKart Create_StokKart(mongocxx::collection &_collection);


    ///
    /// \brief StokKartDocument
    /// \return
    /// StokKartını BSON document olarak döndürür.
    const document StokKartDocument();

    ///
    /// \brief stokKartOid
    /// \return
    /// Stok Kart ID
    bsoncxx::oid stokKartOid() const;

    ///
    /// \brief setStokKartOid
    /// \param stokKartOid
    /// Stok Kart ID Degistirir
    void setStokKartOid(const bsoncxx::oid &stokKartOid);



    ///
    /// \brief stokKartAdi
    /// \return
    /// Stok Adı Verir.
    QString stokKartAdi();


private:
    ///
    /// \brief StokKart
    /// \param _collection
    /// StokKart Yapıcı Fonksiyon
    StokKart(mongocxx::collection &_collection);


    ///
    /// \brief collection
    /// Veri Tabanı Bağlı Koleksiyon
    mongocxx::collection& collection;



    ///
    /// \brief mStokKartOid
    /// Veri Tabanında ki StokKartın Adı.
    bsoncxx::oid mStokKartOid;


    ///
    /// \brief filterByOid
    /// \return
    /// Stok Kart için ID filtresini Geri Döndürür.
    document filterByOid();
};

#endif // STOKKART_H
