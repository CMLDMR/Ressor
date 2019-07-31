#ifndef STOKMAINDIALOG_H
#define STOKMAINDIALOG_H

#include <QDialog>
#include "base/dbclass.h"

namespace Ui {
class StokMainDialog;
}

class StokMainDialog :  public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit StokMainDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~StokMainDialog();

private slots:
    void on_pushButton_STOKKART_clicked();

private:
    Ui::StokMainDialog *ui;
};

#endif // STOKMAINDIALOG_H
