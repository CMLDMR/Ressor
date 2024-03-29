#ifndef STOKKATEGORI_H
#define STOKKATEGORI_H


#include "mongoheaders.h"
#include <QString>
#include <QVector>
#include <QStandardItem>
#include "base/dbclass.h"

#include <boost/optional.hpp>

namespace STOKKATEGORI {

static const std::string KATEGORICOLLECTION{"stokkategori"};
static const std::string KATEGORIADI{"stokkategoriadi"};

class StokKategori : public QStandardItem , public DBClass
{
public:

    ~StokKategori();

    ///
    /// \brief Create_Kategori: Yeni Bir Kategori Oluşturur ve Geri Döndürür.
    /// \param collection
    /// \param kategoriName
    /// \return
    /// StokKategori
    static boost::optional<StokKategori*> Create_Kategori(mongocxx::database *_db , const QString &kategoriName );


    ///
    /// \brief GetKategoriList: Koleksiyonda Var Kategorileri Liste Olarak Döndürür.
    /// \param collection
    /// \return
    /// QVector<StokKategori>
    static QVector<boost::optional<StokKategori*>> GetKategoriList(mongocxx::database *_db);

    ///
    /// \brief DeleteKategori: Veritabanından oid IDli kategoriyi siler
    /// \param collection
    /// \param oid
    /// \return
    /// Başarılı ise true yoksa false döndürür.
    static bool DeleteKategori(mongocxx::database *_db , const bsoncxx::oid &oid);

    ///
    /// \brief DeleteKategori: Veritabanından kategoriName adlı kategoriyi siler
    /// \param collection
    /// \param kategoriName
    /// \return
    /// Başarılı ise true yoksa false döndürür.
    static bool DeleteKategori(mongocxx::database *_db , const QString &kategoriName );

    ///
    /// \brief setKategoriOid: Kategori item ID Set Eder.
    /// \param oid
    /// void
    void setKategoriOid( const bsoncxx::oid &oid );

    ///
    /// \brief kategoriOid: Kategorinin ID Geri Döndürür.
    /// \return
    /// bsoncxx::oid
    bsoncxx::oid kategoriOid() const;

    ///
    /// \brief setKategoriAdi
    /// \param kategoriAdi
    /// \return
    /// Başarılı ise true yoksa false Döndürür.
    bool setKategoriAdi( const QString &kategoriAdi);

    ///
    /// \brief KategoriAdi: Kategori Adını Döndürür.
    /// \return
    /// QString
    QString KategoriAdi();

    ///
    /// \brief Deletekategori: Bu Kategoriyi Siler.
    /// \return
    /// Başarılı ise true yoksa false Döndürür.
    bool Deletekategori();


    boost::optional<QString> isUsedInStokKart();

private:
    StokKategori(mongocxx::database *_db);
    StokKategori(mongocxx::database *_db, const QString &kategoriName);
    StokKategori(mongocxx::database *_db , const bsoncxx::document::view &view);

    std::unique_ptr<std::string> mKategoriAdi;

    mongocxx::collection* mCollection;



    bsoncxx::oid mKategoriOid;

    document filter();


    enum {
        KategoriOid = Qt::UserRole + 1,
        KategotiName
    };


};

}



#endif // STOKKATEGORI_H
