#ifndef ROTATINGLIST_H
#define ROTATINGLIST_H

#include <QFrame>
#include <QList>

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

    //Override Functions

    void resizeEvent(QResizeEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

    void addWidget(QString widgetText);

    void updatePositions();
    void updatePositions_mid(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index);
    void updatePositions_midTop(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index);
    void updatePositions_midBot(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index);
    void updatePositions_top(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index);
    void updatePositions_bot(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index);

    void rotateDown();
    void rotateUp();
private:

    double calculateCirclarIntercept(double posY);
    double calculateArcAngle(int posY_1, int posY_2);
    double dist(double x1, double y1, double x2, double y2);

    logger::Logger      *log;

    QList<RotatingListWidget *> activeWidgets;

    int     firstIndex;

    int     widgetHeight_pix;
    int     widgetWidth_pix;

    QPoint  prevMouseHoldLocation;


signals:

public slots:
};

#endif // ROTATINGLIST_H
