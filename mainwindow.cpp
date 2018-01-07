#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <model.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Model*model = new Model(this);

    ui->tableView->setModel(model);
    ui->tableView->restoreOrder();
    ui->tableView->restoreDefaultHidedColumns();
}

MainWindow::~MainWindow()
{
    delete ui;
}
