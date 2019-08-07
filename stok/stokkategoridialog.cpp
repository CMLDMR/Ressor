#include "stokkategoridialog.h"
#include "ui_stokkategoridialog.h"
#include "base/stokkategori.h"
#include <QStandardItemModel>
#include <QMessageBox>

StokKategoriDialog::StokKategoriDialog(mongocxx::database *_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StokKategoriDialog),
    DBClass (_db)
{
    ui->setupUi(this);

    mKategoriModel = new QStandardItemModel();
    ui->listView_KategoriList->setModel(mKategoriModel);

    this->initList();

    mNewAdded = false;



}

StokKategoriDialog::~StokKategoriDialog()
{
    delete mKategoriModel;
    delete ui;
}

void StokKategoriDialog::on_pushButton_YeniKaydet_clicked()
{
    auto coll = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION);
    auto kat = STOKKATEGORI::StokKategori::Create_Kategori(this->db(),ui->lineEdit_YeniStokKategroi->text());

    if( kat )
    {
        mNewAdded = true;
    }

    this->initList();


}

void StokKategoriDialog::initList()
{

    auto coll = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION);
    auto list = STOKKATEGORI::StokKategori::GetKategoriList(this->db());

    mKategoriModel->removeRows(0,mKategoriModel->rowCount());

    for( auto item : list )
    {
        mKategoriModel->insertRow(0,item.value());
    }
}

void StokKategoriDialog::on_pushButton_SeciliSil_clicked()
{

    QMessageBox msg;


    if( ui->listView_KategoriList->selectionModel()->selectedIndexes().count() )
    {

        auto item = static_cast<STOKKATEGORI::StokKategori*>(mKategoriModel->item(ui->listView_KategoriList->selectionModel()->selectedIndexes().first().row()));

        auto isUsed = item->isUsedInStokKart();

        if( isUsed )
        {
            msg.setText(QString("Bu Kategori \"%1\"'de Kullanılıyor").arg(isUsed.value()));
            msg.setInformativeText("Önce Stok Kart Kategorisini Değiştiriniz");
            msg.setIcon(QMessageBox::Icon::Warning);
            msg.setWindowTitle("Bilgi");
        }else{

            if( item->Deletekategori() )
            {
                msg.setText("Kategori Silindi.");
                msg.setIcon(QMessageBox::Icon::Warning);
                msg.setWindowTitle("Bilgi");
                this->initList();
            }else{
                msg.setText("Bir Kategori Silinmedi");
                msg.setIcon(QMessageBox::Icon::Warning);
                msg.setWindowTitle("Uyarı");
            }

        }



    }else{
        msg.setText("Bir Kategori Seçmediniz");
        msg.setIcon(QMessageBox::Icon::Warning);
        msg.setWindowTitle("Uyarı");
    }

    msg.exec();
}

void StokKategoriDialog::on_pushButton_iptal_clicked()
{
    if( mNewAdded )
    {
        emit Added();
    }
    this->close();
}
