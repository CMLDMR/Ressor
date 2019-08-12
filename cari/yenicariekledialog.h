#ifndef YENICARIEKLEDIALOG_H
#define YENICARIEKLEDIALOG_H

#include <QDialog>

namespace Ui {
class YeniCariEkleDialog;
}

class YeniCariEkleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YeniCariEkleDialog(QWidget *parent = nullptr);
    ~YeniCariEkleDialog();

private:
    Ui::YeniCariEkleDialog *ui;
};

#endif // YENICARIEKLEDIALOG_H
