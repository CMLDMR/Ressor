#ifndef STOKMAINDIALOG_H
#define STOKMAINDIALOG_H

#include <QDialog>

namespace Ui {
class StokMainDialog;
}

class StokMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StokMainDialog(QWidget *parent = nullptr);
    ~StokMainDialog();

private:
    Ui::StokMainDialog *ui;
};

#endif // STOKMAINDIALOG_H
