#ifndef YENICARIGRUPEKLEDIALOG_H
#define YENICARIGRUPEKLEDIALOG_H

#include <QDialog>
#include "base/dbclass.h"
#include "carigrup/carigruplistmodel.h"

namespace Ui {
class YeniCariGrupEkleDialog;
}

class YeniCariGrupEkleDialog : public QDialog , public DBClass
{
    Q_OBJECT

public:
    explicit YeniCariGrupEkleDialog(mongocxx::database* _db , QWidget *parent = nullptr);
    ~YeniCariGrupEkleDialog();

private slots:
    void on_pushButton_YeniEkle_clicked();

    void on_pushButton_deleteSelected_clicked();

private:
    Ui::YeniCariGrupEkleDialog *ui;

    CariGrupListModel* mModel;

};

#endif // YENICARIGRUPEKLEDIALOG_H
