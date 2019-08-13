#include "yenicarigrupekledialog.h"
#include "ui_yenicarigrupekledialog.h"

YeniCariGrupEkleDialog::YeniCariGrupEkleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YeniCariGrupEkleDialog)
{
    ui->setupUi(this);
}

YeniCariGrupEkleDialog::~YeniCariGrupEkleDialog()
{
    delete ui;
}
