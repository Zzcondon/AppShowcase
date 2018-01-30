#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    log(NULL)
{
    ui->setupUi(this);

    log = new logger::Logger(this);
    if (log->init("config.txt")) {
        log->info("Test Info");
        log->warn("Test warn");
        log->err("Test err");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
