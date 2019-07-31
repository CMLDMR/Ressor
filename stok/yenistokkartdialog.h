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

private:
    Ui::YeniStokKartDialog *ui;
};

#endif // YENISTOKKARTDIALOG_H
