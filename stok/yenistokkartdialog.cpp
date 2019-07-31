#include "yenistokkartdialog.h"
#include "ui_yenistokkartdialog.h"

YeniStokKartDialog::YeniStokKartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YeniStokKartDialog)
{
    ui->setupUi(this);
}

YeniStokKartDialog::~YeniStokKartDialog()
{
    delete ui;
}
