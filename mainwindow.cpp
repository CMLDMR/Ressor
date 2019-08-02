#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../url.h"


#include "stok/stokmaindialog.h"
#include "stok/yenistokbirimekledialog.h"
#include "stok/stokkategoridialog.h"
#include "stok/yenistokkartdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    try {
        mClient = new mongocxx::client(mongocxx::uri(_url));
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }


    mDB = mClient->database("Ressor");

//    mClient->database("Ressor").collection("Test").insert_one(make_document(kvp("test333","test1")).view());



//    try {
//        auto cursor = mClient->database("Ressor").collection("Test").find(document{}.view());

//        for( auto doc : cursor )
//        {
//            std::cout << bsoncxx::to_json(doc) << std::endl;
//        }

//    } catch (mongocxx::exception &e) {

//    }



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionStok_Kartlar_triggered()
{


    ui->tabWidget->insertTab(ui->tabWidget->count(),new StokMainDialog(&mDB),"Stok Kart Tanımlama");

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

//    auto mDialog = new StokMainDialog(&mDB);

//    mDialog->exec();
}


void MainWindow::on_actionStok_Birimleri_triggered()
{
    auto mDialog = std::make_unique<YeniStokBirimEkleDialog>(&mDB);

    mDialog->exec();
}

void MainWindow::on_actionStok_Kategorileri_triggered()
{
    auto mDialog = std::make_unique<StokKategoriDialog>(&mDB);

    mDialog->exec();
}

void MainWindow::on_actionStok_Kart_Tan_mla_triggered()
{
    auto mDialog = std::make_unique<YeniStokKartDialog>(&mDB);

    mDialog->exec();
}
