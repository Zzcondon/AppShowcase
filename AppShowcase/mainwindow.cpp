#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logger.h"
#include "rotatinglist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    centralStack(NULL),
    log(NULL),
    menuList(NULL),
    config_filename("config.txt")
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::init() {

    bool initSuccess_flag = true;

    // Initialize logger first
    log = new logger::Logger(this);

    if (log != NULL) {

        log->init("config.txt");

        centralStack = new QStackedWidget(this);

        setCentralWidget(centralStack);

        initSuccess_flag &= initTestBox();

        log->info("MainWindow.init: Completed");

    }
    else {
        initSuccess_flag = false;
    }

    return initSuccess_flag;
}

bool MainWindow::initTestBox() {
    bool success_flag = true;

    menuList = new RotatingList(this);
    menuList->setObjectName("Menu List");

    success_flag &= menuList->init(log);

    menuList->defineParameters(200, 300, 180, 50);
    menuList->addWidget("1");
    menuList->addWidget("2");
    menuList->addWidget("3");
    menuList->addWidget("4");
    menuList->addWidget("5");
    menuList->addWidget("6");
    menuList->addWidget("7");
    menuList->addWidget("8");

    QWidget *wrapperWidget = new QWidget(this);
    QGridLayout *wrapperLayout = new QGridLayout(wrapperWidget);

    wrapperLayout->addWidget(menuList, 0, 0, Qt::AlignCenter);

    centralStack->addWidget(wrapperWidget);
    centralStack->setMinimumSize(300, 300);

    return success_flag;
}
