#ifndef YENISTOKBIRIMEKLEDIALOG_H
#define YENISTOKBIRIMEKLEDIALOG_H

#include <QDialog>
#include "base/dbclass.h"


class QStandardItemModel;

namespace Ui {
class YeniStokBirimEkleDialog;
}

class YeniStokBirimEkleDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit YeniStokBirimEkleDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~YeniStokBirimEkleDialog();

private slots:
    void on_pushButton_YeniBirimEkle_clicked();

private:
    Ui::YeniStokBirimEkleDialog *ui;

    QStandardItemModel* mModel;

    void initList();
};

#endif // YENISTOKBIRIMEKLEDIALOG_H
