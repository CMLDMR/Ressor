#ifndef STOKDEPODIALOG_H
#define STOKDEPODIALOG_H

#include <QDialog>

namespace Ui {
class StokDepoDialog;
}

class StokDepoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StokDepoDialog(QWidget *parent = nullptr);
    ~StokDepoDialog();

private:
    Ui::StokDepoDialog *ui;
};

#endif // STOKDEPODIALOG_H
