#ifndef STOKKATEGORIDIALOG_H
#define STOKKATEGORIDIALOG_H

#include <QDialog>
#include "base/dbclass.h"

class QStandardItemModel;

namespace Ui {
class StokKategoriDialog;
}

class StokKategoriDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit StokKategoriDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~StokKategoriDialog();

signals:
    void Added();

private slots:
    void on_pushButton_YeniKaydet_clicked();

    void on_pushButton_SeciliSil_clicked();

    void on_pushButton_iptal_clicked();

private:
    Ui::StokKategoriDialog *ui;

    QStandardItemModel* mKategoriModel;

    void initList();


    bool mNewAdded;


};

#endif // STOKKATEGORIDIALOG_H
