#ifndef CARIMAINWIDGET_H
#define CARIMAINWIDGET_H

#include <QWidget>

namespace Ui {
class CariMainWidget;
}

class CariMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CariMainWidget(QWidget *parent = nullptr);
    ~CariMainWidget();

private:
    Ui::CariMainWidget *ui;
};

#endif // CARIMAINWIDGET_H
