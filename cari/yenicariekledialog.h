#ifndef YENICARIEKLEDIALOG_H
#define YENICARIEKLEDIALOG_H

#include <QDialog>
#include "base/dbclass.h"

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
};

#endif // YENICARIEKLEDIALOG_H
