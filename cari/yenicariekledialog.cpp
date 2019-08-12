#include "yenicariekledialog.h"
#include "ui_yenicariekledialog.h"

YeniCariEkleDialog::YeniCariEkleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YeniCariEkleDialog)
{
    ui->setupUi(this);
}

YeniCariEkleDialog::~YeniCariEkleDialog()
{
    delete ui;
}
