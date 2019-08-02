#ifndef YENISTOKKARTDIALOG_H
#define YENISTOKKARTDIALOG_H

#include <QDialog>
#include "base/dbclass.h"
namespace Ui {
class YeniStokKartDialog;
}

class YeniStokKartDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit YeniStokKartDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~YeniStokKartDialog();

private slots:
    void on_pushButton_StokKaydet_clicked();

    void on_pushButton_YeniKategoriEkle_clicked();

private:
    Ui::YeniStokKartDialog *ui;
};

#endif // YENISTOKKARTDIALOG_H
