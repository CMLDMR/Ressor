#include "yenistokkartdialog.h"
#include "ui_yenistokkartdialog.h"


#include "base/stokkart.h"
#include "stokkategoridialog.h"
#include "yenistokbirimekledialog.h"
#include "base/stokbirim.h"
#include "base/stokkategori.h"

#include <QMessageBox>

YeniStokKartDialog::YeniStokKartDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QDialog(parent),
    ui(new Ui::YeniStokKartDialog),
    mYeniEkle(true)
{
    ui->setupUi(this);

    mKategoriCollection = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION);



    auto KatList = STOKKATEGORI::StokKategori::GetKategoriList(this->db());
    ui->comboBox_StokKategori->clear();
    for( auto doc : KatList )
    {
        ui->comboBox_StokKategori->addItem(doc.value()->KategoriAdi(),doc.value()->kategoriOid().to_string().c_str());
    }


    auto BirList = StokBirim::StokBirim::GetStokBirimList(this->db());

    ui->comboBox_StokBirimi->clear();
    for( auto item : BirList )
    {
        ui->comboBox_StokBirimi->addItem(item->getBirimAdi(),item->getBirimOid().to_string().c_str());
    }


}

YeniStokKartDialog::YeniStokKartDialog(mongocxx::database* _db , StokKart *mStokKart)
    :DBClass (_db),
      ui(new Ui::YeniStokKartDialog),
      mCurrentStokKart(mStokKart),
      mYeniEkle(false)
{
    ui->setupUi(this);


    mKategoriCollection = this->db()->collection(STOKKATEGORI::KATEGORICOLLECTION);



    auto KatList = STOKKATEGORI::StokKategori::GetKategoriList(this->db());
    ui->comboBox_StokKategori->clear();
    for( auto doc : KatList )
    {
        ui->comboBox_StokKategori->addItem(doc.value()->KategoriAdi(),doc.value()->kategoriOid().to_string().c_str());
    }


    auto BirList = StokBirim::StokBirim::GetStokBirimList(this->db());

    ui->comboBox_StokBirimi->clear();
    for( auto item : BirList )
    {
        ui->comboBox_StokBirimi->addItem(item->getBirimAdi(),item->getBirimOid().to_string().c_str());
    }



    if( mCurrentStokKart )
    {
        ui->lineEdit_StokAdi->setText(mCurrentStokKart->KartAdi());
        ui->lineEdit_StokKodu->setText(mCurrentStokKart->StokKodu());
        ui->comboBox_StokKategori->setCurrentText(mCurrentStokKart->Kategori());
        ui->comboBox_StokBirimi->setCurrentText(mCurrentStokKart->Birimi());
        ui->doubleSpinBox_KDV->setValue(mCurrentStokKart->KDVOrani());
        ui->doubleSpinBox_OTV->setValue(mCurrentStokKart->OTVOrani());
        ui->doubleSpinBox_AlisFiyati->setValue(mCurrentStokKart->AlisFiyati());
        ui->doubleSpinBox_SatisFiyati->setValue(mCurrentStokKart->SatisFiyati());
    }

}

YeniStokKartDialog::~YeniStokKartDialog()
{
    delete ui;
}

void YeniStokKartDialog::on_pushButton_StokKaydet_clicked()
{
    if( mYeniEkle )
    {
        this->YeniKaydet();
    }else{
        this->Guncelle();
    }
}

void YeniStokKartDialog::on_pushButton_YeniKategoriEkle_clicked()
{
    auto mDialog = std::make_unique<StokKategoriDialog>(this->db());

    connect(mDialog.get(),&StokKategoriDialog::Added,[=](){
        auto KatList = STOKKATEGORI::StokKategori::GetKategoriList(this->db());
        ui->comboBox_StokKategori->clear();
        for( auto doc : KatList )
        {
            ui->comboBox_StokKategori->addItem(doc.value()->KategoriAdi(),doc.value()->kategoriOid().to_string().c_str());
        }
    });

    mDialog->exec();
}

void YeniStokKartDialog::on_pushButton_YeniBirimEkle_clicked()
{
    auto mDialog = std::make_unique<YeniStokBirimEkleDialog>(this->db());


    connect(mDialog.get(),&YeniStokBirimEkleDialog::birimListChanged,[=](){
        auto BirList = StokBirim::StokBirim::GetStokBirimList(this->db());

        ui->comboBox_StokBirimi->clear();
        for( auto item : BirList )
        {
            ui->comboBox_StokBirimi->addItem(item->getBirimAdi(),item->getBirimOid().to_string().c_str());
        }
    });


    mDialog->exec();
}

void YeniStokKartDialog::YeniKaydet()
{
    auto stokKart = StokKart::Create_StokKart(this->db());

    if( stokKart )
    {

        bool saveError = false;


        if( !stokKart->setKartAdi(ui->lineEdit_StokAdi->text()) )
        {
            saveError = true;
        }


        if( !stokKart->setStokKodu(ui->lineEdit_StokKodu->text()) )
        {
            saveError = true;
        }


        if( !stokKart->setKategori(ui->comboBox_StokKategori->currentText()) )
        {
            saveError = true;
        }


        if( !stokKart->setBirim(ui->comboBox_StokBirimi->currentText()) )
        {
            saveError = true;
        }


        if( !stokKart->setAlisFiyati(ui->doubleSpinBox_AlisFiyati->value()) )
        {
            saveError = true;
        }

        if( !stokKart->setKDVOrani(ui->doubleSpinBox_KDV->value()) )
        {
            saveError = true;
        }

        if( !stokKart->setOTVOrani(ui->doubleSpinBox_OTV->value()) )
        {
            saveError = true;
        }

        if( !stokKart->setSatisFiyati(ui->doubleSpinBox_SatisFiyati->value()) )
        {
            saveError = true;
        }




        if( saveError )
        {
            QMessageBox msg;
            msg.setText("Stok Kartı Oluşturuldu Ancak Bazi Bilgiler Girilemedi");
            msg.setIcon(QMessageBox::Icon::Warning);
            msg.setWindowTitle("UYARI");
            msg.exec();
        }else{
            QMessageBox msg;
            msg.setText("Stok Kartı oluşturuldu");
            msg.setIcon(QMessageBox::Icon::Information);
            msg.setWindowTitle("Bilgi");
            msg.exec();
            this->close();
        }
    }else{
        QMessageBox msg;
        msg.setText("Stok Kartı Oluşturulamadı");
        msg.setIcon(QMessageBox::Icon::Warning);
        msg.setWindowTitle("UYARI");
        msg.exec();
    }
}

void YeniStokKartDialog::Guncelle()
{
    auto stokKart = StokKart::Load_StokKart(this->db(),mCurrentStokKart->stokKartOid());

    if( stokKart )
    {

        bool saveError = false;


        if( !stokKart->setKartAdi(ui->lineEdit_StokAdi->text()) )
        {
            saveError = true;
        }


        if( !stokKart->setStokKodu(ui->lineEdit_StokKodu->text()) )
        {
            saveError = true;
        }


        if( !stokKart->setKategori(ui->comboBox_StokKategori->currentText()) )
        {
            saveError = true;
        }


        if( !stokKart->setBirim(ui->comboBox_StokBirimi->currentText()) )
        {
            saveError = true;
        }


        if( !stokKart->setAlisFiyati(ui->doubleSpinBox_AlisFiyati->value()) )
        {
            saveError = true;
        }

        if( !stokKart->setKDVOrani(ui->doubleSpinBox_KDV->value()) )
        {
            saveError = true;
        }

        if( !stokKart->setOTVOrani(ui->doubleSpinBox_OTV->value()) )
        {
            saveError = true;
        }

        if( !stokKart->setSatisFiyati(ui->doubleSpinBox_SatisFiyati->value()) )
        {
            saveError = true;
        }




        if( saveError )
        {
            QMessageBox msg;
            msg.setText("Stok Kartı Güncellendi Ancak Bazi Bilgiler Girilemedi");
            msg.setIcon(QMessageBox::Icon::Warning);
            msg.setWindowTitle("UYARI");
            msg.exec();
        }else{
            QMessageBox msg;
            msg.setText("Stok Kartı Güncellendi");
            msg.setIcon(QMessageBox::Icon::Information);
            msg.setWindowTitle("Bilgi");
            msg.exec();
            this->close();
        }
    }else{
        QMessageBox msg;
        msg.setText("Stok Kartı Güncellenemedi");
        msg.setIcon(QMessageBox::Icon::Warning);
        msg.setWindowTitle("UYARI");
        msg.exec();
    }
}
