#include "yenicarigrupekledialog.h"
#include "ui_yenicarigrupekledialog.h"
#include "carigrup/carigrupitem.h"

#include <QDebug>

YeniCariGrupEkleDialog::YeniCariGrupEkleDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass(_db),
    QDialog(parent),
    ui(new Ui::YeniCariGrupEkleDialog)
{
    ui->setupUi(this);
}

YeniCariGrupEkleDialog::~YeniCariGrupEkleDialog()
{
    delete ui;
}

void YeniCariGrupEkleDialog::on_pushButton_YeniEkle_clicked()
{

    auto item = CariGrub::CariGrupItem::Create_CariGrup(this->db(),ui->lineEdit_YeniCariGrupAdi->text());

    if( item )
    {
        std::cout << "eklendi." << std::endl;
        qDebug() << item.value().keyList();

        CariGrub::CariGrupItem::GetList(this->db());

    }else{
        std::cout << "error" << std::endl;
    }

}
