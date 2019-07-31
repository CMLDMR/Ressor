#ifndef STOKKARTDIALOG_H
#define STOKKARTDIALOG_H

#include <QDialog>
#include "base/dbclass.h"

namespace Ui {
class StokKartDialog;
}

class StokKartDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit StokKartDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~StokKartDialog();

private:
    Ui::StokKartDialog *ui;
};

#endif // STOKKARTDIALOG_H
