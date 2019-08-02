#ifndef YENISTOKBIRIMEKLEDIALOG_H
#define YENISTOKBIRIMEKLEDIALOG_H

#include <QDialog>

namespace Ui {
class YeniStokBirimEkleDialog;
}

class YeniStokBirimEkleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YeniStokBirimEkleDialog(QWidget *parent = nullptr);
    ~YeniStokBirimEkleDialog();

private:
    Ui::YeniStokBirimEkleDialog *ui;
};

#endif // YENISTOKBIRIMEKLEDIALOG_H
