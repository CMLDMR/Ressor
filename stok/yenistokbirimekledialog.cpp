#include "yenistokbirimekledialog.h"
#include "ui_yenistokbirimekledialog.h"

YeniStokBirimEkleDialog::YeniStokBirimEkleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YeniStokBirimEkleDialog)
{
    ui->setupUi(this);
}

YeniStokBirimEkleDialog::~YeniStokBirimEkleDialog()
{
    delete ui;
}
