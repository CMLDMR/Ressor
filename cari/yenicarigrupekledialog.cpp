#include "yenicarigrupekledialog.h"
#include "ui_yenicarigrupekledialog.h"
#include "carigrup/carigrupitem.h"
#include <QMessageBox>

#include <QDebug>

YeniCariGrupEkleDialog::YeniCariGrupEkleDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass(_db),
    QDialog(parent),
    ui(new Ui::YeniCariGrupEkleDialog)
{
    ui->setupUi(this);


    mModel = new CariGrupListModel(this->db());

    ui->listView_CariGrupList->setModel(mModel);
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
        mModel->initModel();
    }else{
        QMessageBox msg;
        msg.setIcon(QMessageBox::Icon::Warning);
        msg.setText("Grup Oluşturulamadı");
        msg.setWindowTitle("Uyarı");
        msg.exec();
    }
}

void YeniCariGrupEkleDialog::on_pushButton_deleteSelected_clicked()
{
    auto selectedList = ui->listView_CariGrupList->selectionModel()->selectedIndexes();

    if( selectedList.count() )
    {
        auto item = selectedList.first();
        if( mModel->deleteItem(item.row()) )
        {

        }else{
            std::cout << __LINE__ << " " << __FUNCTION__ << " " << "silinmedi" << std::endl;
        }
    }

}
