#ifndef STOKDEPODIALOG_H
#define STOKDEPODIALOG_H

#include <QDialog>
#include "base/stokdepomodel.h"

namespace Ui {
class StokDepoDialog;
}

class StokDepoDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit StokDepoDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~StokDepoDialog();

private slots:
    void on_pushButton_Ekle_clicked();

private:
    Ui::StokDepoDialog *ui;

    StokDepoModel* mModel;
};

#endif // STOKDEPODIALOG_H
