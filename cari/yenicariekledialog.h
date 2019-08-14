#ifndef YENICARIEKLEDIALOG_H
#define YENICARIEKLEDIALOG_H

#include <QDialog>
#include "base/dbclass.h"

class CariGrupListModel;

namespace Ui {
class YeniCariEkleDialog;
}

class YeniCariEkleDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit YeniCariEkleDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~YeniCariEkleDialog();

private slots:
    void on_pushButton_CariGrpEkle_clicked();

private:
    Ui::YeniCariEkleDialog *ui;

    CariGrupListModel* mGrupModel;
};

#endif // YENICARIEKLEDIALOG_H
