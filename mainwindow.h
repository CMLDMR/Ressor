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
    void on_pushButton_Stok_clicked();

private:
    Ui::MainWindow *ui;


    mongocxx::client* mClient;

    mongocxx::database mDB;
};

#endif // MAINWINDOW_H