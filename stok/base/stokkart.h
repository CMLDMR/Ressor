#ifndef STOKKART_H
#define STOKKART_H


#include "mongoheaders.h"
#include <QString>

namespace STOKKARTKEY {
    static const std::string STOKCOLLECTION{"stokkart"};
    static const std::string STOKADI{"stokadı"};
    static const std::string STOKODU{"stokodu"};
}

class StokKart
{
public:

    ///
    /// \brief Veri Tabanına Bağlı ID Olan Boş Bir Adet Stok Kartı Oluşturur.
    /// \param _collection
    /// \return
    /// StokKart
    static StokKart Create_StokKart(mongocxx::collection &_collection);


    ///
    /// \brief Load_StokKart
    /// \param _collection
    /// \param kartOid
    /// \return
    /// Stok Kartını Verilen ID ile veritabanından Yükler ve verir.
    static StokKart Load_StokKart(mongocxx::collection &_collection , const bsoncxx::oid &kartOid );

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
    /// \brief KartAdi
    /// \return
    /// Stok Adı Verir.
    QString KartAdi();

    ///
    /// \brief setKartAdi
    /// \param kartAdi
    /// \return
    /// Stok Kart Adını Veri Tabanın da Değiştirir.
    bool setKartAdi(const QString &kartAdi);


    ///
    /// \brief StokKodu: Stok Kodu Veri Tabanından Geri Döndürür.
    /// \return
    /// "QString"
    QString StokKodu();

    ///
    /// \brief setStokKodu: Stok Kodunu Veri Tabanında Set Eder.
    /// \param stokKodu
    /// \return
    /// Kayıt Başarılı ise "true" yoksa "false" döndürür.
    bool setStokKodu( const QString &stokKodu);


private:
    ///
    /// \brief StokKart
    /// \param _collection
    /// StokKart Yapıcı Fonksiyon
    StokKart(mongocxx::collection &_collection);

    ///
    /// \brief StokKart
    /// \param _collection
    /// \param kartOid
    /// Stok Kartını kartOid ile Yükler ve Verir.
    StokKart(mongocxx::collection &_collection , const bsoncxx::oid &kartOid);


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
