#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGridLayout>
#include <QStackedWidget>

namespace logger {
class Logger;
}

class RotatingList;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool init();
    bool initTestBox();
private:
    Ui::MainWindow *ui;

    QStackedWidget *centralStack;

    logger::Logger *log;

    RotatingList   *menuList;

    QString         config_filename;
};

#endif // MAINWINDOW_H
