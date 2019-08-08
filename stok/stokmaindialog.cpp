#include "stokmaindialog.h"
#include "ui_stokmaindialog.h"

#include "stokkartdialog.h"
#include "yenistokkartdialog.h"
#include "base/stokkartmodel.h"


#include <QAction>
#include <QMenu>

StokMainDialog::StokMainDialog(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QDialog(parent),
    ui(new Ui::StokMainDialog)

{
    ui->setupUi(this);

    mkartModel = new StokKartModel (this->db());

    ui->tableView_StokKartView->setModel(mkartModel);

    this->initActions();


}

StokMainDialog::~StokMainDialog()
{
    std::cout << "Stok Main Destructor" << std::endl;
    delete ui;
}


void StokMainDialog::on_pushButton_StokKartTanimla_clicked()
{
        auto mDialog = std::make_unique<YeniStokKartDialog>(this->db());

        mDialog->exec();
}

void StokMainDialog::on_pushButton_ListeyiGuncelle_clicked()
{
    this->mkartModel->initStokKartList();
}

void StokMainDialog::on_tableView_StokKartView_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    menu.addAction(aDeleteStokKart);
    menu.exec(ui->tableView_StokKartView->mapToGlobal(pos));
}

void StokMainDialog::initActions()
{
    aDeleteStokKart = new QAction("Stok Kartı Sil");
    connect(aDeleteStokKart,&QAction::triggered,this,&StokMainDialog::deleteSelectedKart);

}

void StokMainDialog::deleteSelectedKart()
{
    int selectedIndex = -1;
    for( auto index : ui->tableView_StokKartView->selectionModel()->selectedIndexes() ){
        selectedIndex = index.row();
    }

    if( selectedIndex != -1 )
    {
        this->mkartModel->deleteStokKart(selectedIndex);
    }
}
