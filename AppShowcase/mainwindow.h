#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace logger {
class Logger;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    logger::Logger *log;
};

#endif // MAINWINDOW_H
