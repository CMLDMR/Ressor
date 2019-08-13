#include "carimainwidget.h"
#include "ui_carimainwidget.h"

#include "yenicariekledialog.h"

CariMainWidget::CariMainWidget(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QWidget(parent),
    ui(new Ui::CariMainWidget)
{
    ui->setupUi(this);
}

CariMainWidget::~CariMainWidget()
{
    delete ui;
}

void CariMainWidget::on_pushButton_YeniCariEkle_clicked()
{
    auto mDialog = new YeniCariEkleDialog(this->db());

    mDialog->exec();

    mDialog->deleteLater();
}
