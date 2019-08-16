#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../url.h"


#include "stok/stokmaindialog.h"
#include "stok/yenistokbirimekledialog.h"
#include "stok/stokkategoridialog.h"
#include "stok/yenistokkartdialog.h"

#include "cari/carimainwidget.h"
#include "cari/yenicariekledialog.h"

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

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionStok_Kartlar_triggered()
{


    ui->tabWidget->insertTab(ui->tabWidget->count(),new StokMainDialog(&mDB),"Stok Kart Tanımlama");

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
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

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    auto widget = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    widget->deleteLater();
}

void MainWindow::on_actionCari_Hesaplar_triggered()
{
    ui->tabWidget->insertTab(ui->tabWidget->count(),new CariMainWidget(&mDB),"Cari Hesaplar");

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::on_actionYeni_Cari_Ekle_triggered()
{
    auto mDialog = new YeniCariEkleDialog(&mDB);

    mDialog->exec();

    mDialog->deleteLater();

}
