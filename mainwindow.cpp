#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../url.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    try {
        mClient = new mongocxx::client(mongocxx::uri(_url));
    } catch (mongocxx::exception &e) {
        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
    }


    mClient->database("Ressor").collection("Test").insert_one(make_document(kvp("test333","test1")).view());



    try {
        auto cursor = mClient->database("Ressor").collection("Test").find(document{}.view());

        for( auto doc : cursor )
        {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }

    } catch (mongocxx::exception &e) {

    }



}

MainWindow::~MainWindow()
{
    delete ui;
}
