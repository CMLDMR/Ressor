#include "carimainwidget.h"
#include "ui_carimainwidget.h"

CariMainWidget::CariMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CariMainWidget)
{
    ui->setupUi(this);
}

CariMainWidget::~CariMainWidget()
{
    delete ui;
}
