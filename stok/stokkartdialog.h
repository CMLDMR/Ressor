#ifndef STOKKARTDIALOG_H
#define STOKKARTDIALOG_H

#include <QDialog>
#include "base/dbclass.h"

class QAction;

namespace Ui {
class StokKartDialog;
}

class StokKartDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit StokKartDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~StokKartDialog();

private slots:
    void on_pushButton_YENISTOKKART_clicked();

private:
    Ui::StokKartDialog *ui;


};

#endif // STOKKARTDIALOG_H
