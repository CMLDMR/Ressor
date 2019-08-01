#include "yenistokkartdialog.h"
#include "ui_yenistokkartdialog.h"


#include "base/stokkart.h"

#include <QMessageBox>

YeniStokKartDialog::YeniStokKartDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QDialog(parent),
    ui(new Ui::YeniStokKartDialog)
{
    ui->setupUi(this);
}

YeniStokKartDialog::~YeniStokKartDialog()
{
    delete ui;
}

void YeniStokKartDialog::on_pushButton_StokKaydet_clicked()
{
    auto coll = this->db()->collection(STOKKARTKEY::STOKCOLLECTION);
    auto stokKart = StokKart::Create_StokKart(coll);

    bool saveError = false;

    if( !stokKart.setKartAdi(ui->lineEdit_StokAdi->text()) )
    {
        saveError = true;
    }

    if( !stokKart.setStokKodu(ui->lineEdit_StokKodu->text()) )
    {
        saveError = true;
    }



    if( saveError )
    {
        QMessageBox msg;
        msg.setText("Stok Kartı Oluşturulamadı");
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
}
