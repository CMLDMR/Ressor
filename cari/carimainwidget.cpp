#include "carimainwidget.h"
#include "ui_carimainwidget.h"

#include "yenicariekledialog.h"
#include "cariItem/cariitemlistmodel.h"

CariMainWidget::CariMainWidget(mongocxx::database *_db, QWidget *parent) :
    DBClass (_db),
    QWidget(parent),
    ui(new Ui::CariMainWidget)
{
    ui->setupUi(this);

    mModel = new CariItemListModel(this->db());

    ui->tableView->setModel(mModel);
    ui->tableView->resizeColumnsToContents();
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

void CariMainWidget::on_pushButton_Guncelle_clicked()
{
    mModel->initModel();
}
