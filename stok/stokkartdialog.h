#ifndef STOKKARTDIALOG_H
#define STOKKARTDIALOG_H

#include <QDialog>

namespace Ui {
class StokKartDialog;
}

class StokKartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StokKartDialog(QWidget *parent = nullptr);
    ~StokKartDialog();

private:
    Ui::StokKartDialog *ui;
};

#endif // STOKKARTDIALOG_H
