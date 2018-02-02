#ifndef ROTATINGLIST_H
#define ROTATINGLIST_H

#include <QFrame>
#include <QList>
#include <QQueue>

#include <QPoint>

namespace logger {
class Logger;
}

class RotatingListWidget;

class RotatingList : public QFrame
{
    Q_OBJECT
public:
    explicit RotatingList(QWidget *parent = nullptr);

    bool init(logger::Logger* nLog);

    void defineParameters(int boxWidth, int boxHeight, int itemWidth, int itemHeight);

    void snapWidgetLocations();

    //Override Functions

    void resizeEvent(QResizeEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void paintEvent(QPaintEvent *event);

    void addWidget(QString widgetText);

    void updatePositions();
    void setStackOrder();

    void rotateDown();
    void rotateUp();
private:

    double calculateCirclarIntercept(double posY);
    double calculateArcAngle(int posY_1, int posY_2);
    double angleToPos(double angle_deg);
    double dist(double x1, double y1, double x2, double y2);

    logger::Logger      *log;

    QQueue<RotatingListWidget *> activeWidgets;

    int     firstIndex;
    double  angleOffset_deg;

    int     widgetHeight_pix;
    int     widgetWidth_pix;

    QPoint  prevMouseHoldLocation;

    int     borderOffset_pix;


signals:

public slots:
};

#endif // ROTATINGLIST_H
