#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mongoheaders.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionStok_Kartlar_triggered();

    void on_actionStok_Birimleri_triggered();

    void on_actionStok_Kategorileri_triggered();

    void on_actionStok_Kart_Tan_mla_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionCari_Hesaplar_triggered();

    void on_actionYeni_Cari_Ekle_triggered();

    void on_actionYeni_Cari_Grup_Ekle_triggered();

    void on_actionStok_Depolar_triggered();

private:
    Ui::MainWindow *ui;


    mongocxx::client* mClient;

    mongocxx::database mDB;
};

#endif // MAINWINDOW_H
