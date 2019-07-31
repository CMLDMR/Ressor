#include "yenistokkartdialog.h"
#include "ui_yenistokkartdialog.h"

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
