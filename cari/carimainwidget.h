#ifndef CARIMAINWIDGET_H
#define CARIMAINWIDGET_H

#include <QWidget>
#include "base/dbclass.h"

class CariItemListModel;

namespace Ui {
class CariMainWidget;
}

class CariMainWidget : public QWidget , public DBClass
{
    Q_OBJECT

public:
    explicit CariMainWidget(mongocxx::database* _db , QWidget *parent = nullptr);
    ~CariMainWidget();

private slots:
    void on_pushButton_YeniCariEkle_clicked();

    void on_pushButton_Guncelle_clicked();

private:
    Ui::CariMainWidget *ui;

    CariItemListModel* mModel;
};

#endif // CARIMAINWIDGET_H
