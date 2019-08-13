#ifndef YENICARIGRUPEKLEDIALOG_H
#define YENICARIGRUPEKLEDIALOG_H

#include <QDialog>

namespace Ui {
class YeniCariGrupEkleDialog;
}

class YeniCariGrupEkleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YeniCariGrupEkleDialog(QWidget *parent = nullptr);
    ~YeniCariGrupEkleDialog();

private:
    Ui::YeniCariGrupEkleDialog *ui;
};

#endif // YENICARIGRUPEKLEDIALOG_H
