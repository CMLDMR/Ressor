#ifndef STOKKART_H
#define STOKKART_H


#include "base/dbclass.h"
#include <boost/optional.hpp>

class QString;

namespace STOKKARTKEY {
    static const std::string STOKCOLLECTION{"stokkart"};
    static const std::string STOKADI{"stokadı"};
    static const std::string STOKODU{"stokodu"};
    static const std::string KategoriKEY{"stokKategori"};
    static const std::string BirimKEY{"stokBirimi"};
    static const std::string AlisFiyatKEY{"stokAlisFiyati"};
    static const std::string KdvOraniKEY{"stokKdvOrani"};
    static const std::string OtvOraniKEY{"stokOtvOrani"};
    static const std::string SatisFiyatiKEY{"stokSatisFiyati"};
}

class StokKart : public DBClass
{
public:

    ///
    /// \brief Veri Tabanına Bağlı ID Olan Boş Bir Adet Stok Kartı Oluşturur.
    /// \param _collection
    /// \return
    /// StokKart
    static boost::optional<StokKart> Create_StokKart(mongocxx::database *_db);




    ///
    /// \brief stokKartOid
    /// \return
    /// Stok Kart ID
    bsoncxx::oid stokKartOid() const;




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
    QString StokKodu() const;

    ///
    /// \brief setStokKodu: Stok Kodunu Veri Tabanında Set Eder.
    /// \param stokKodu
    /// \return
    /// Kayıt Başarılı ise "true" yoksa "false" döndürür.
    bool setStokKodu( const QString &stokKodu);

    bool setKategori( const QString &stokKategori );
    QString Kategori() const;

    bool setBirim( const QString &birim );
    const QString Birimi() const;

    bool setAlisFiyati(const double &alisfiyati);
    double AlisFiyati() const;

    bool setKDVOrani( const double &kdvOrani );
    double KDVOrani() const;

    bool setOTVOrani( const double &otvOrani );
    double OTVOrani() const;

    bool setSatisFiyati( const double &satisFiyati );
    double SatisFiyati() const;

private:
    StokKart(mongocxx::database *_db);

    std::unique_ptr<std::string> mStokKodu;
    std::unique_ptr<std::string> mKartAdi;
    std::unique_ptr<std::string> mKategori;
    std::unique_ptr<std::string> mBirim;
    std::unique_ptr<double> mAlisFiyati;
    std::unique_ptr<double> mKDVOrani;
    std::unique_ptr<double> mOTVOrani;
    std::unique_ptr<double> mSatisFiyati;



    bsoncxx::oid mStokKartOid;

    document filterByOid();


    bool isValid;

    template<typename T>
    bool setElement( const std::string &key , const T &value );
};

#endif // STOKKART_H
