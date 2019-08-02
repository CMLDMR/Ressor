#ifndef STOKKATEGORIDIALOG_H
#define STOKKATEGORIDIALOG_H

#include <QDialog>

namespace Ui {
class StokKategoriDialog;
}

class StokKategoriDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StokKategoriDialog(QWidget *parent = nullptr);
    ~StokKategoriDialog();

private:
    Ui::StokKategoriDialog *ui;
};

#endif // STOKKATEGORIDIALOG_H
