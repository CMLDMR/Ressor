#ifndef YENISTOKKARTDIALOG_H
#define YENISTOKKARTDIALOG_H

#include <QDialog>

namespace Ui {
class YeniStokKartDialog;
}

class YeniStokKartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YeniStokKartDialog(QWidget *parent = nullptr);
    ~YeniStokKartDialog();

private:
    Ui::YeniStokKartDialog *ui;
};

#endif // YENISTOKKARTDIALOG_H
