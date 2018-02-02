#include "rotatinglist.h"
#include "rotatinglistwidget.h"

#include "logger.h"
#include "math.h"
#include <cmath>

#include <QDebug>
#include <QPainter>

#ifndef M_PI
const double M_PI = 3.14159265358979323846;
#endif

RotatingList::RotatingList(QWidget *parent) : QFrame(parent),
    activeWidgets(),
    firstIndex(0),
    angleOffset_deg(0),
    widgetHeight_pix(50),
    widgetWidth_pix(150),
    prevMouseHoldLocation(),
    borderOffset_pix(40)
{
    setMouseTracking(true);
    setFrameStyle(QFrame::Box);
}

bool RotatingList::init(logger::Logger *nLog) {
    bool initSuccess_flag = true;

    if (nLog != NULL) {
        log = nLog;

//        QPalette pal = palette();
//        pal.setColor(QPalette::Background, Qt::black);
//        setAutoFillBackground(true);
//        setPalette(pal);
    }
    else {
        initSuccess_flag = false;
    }

    return initSuccess_flag;
}

void RotatingList::defineParameters(int BoxWidth, int BoxHeight, int itemWidth, int itemHeight) {
    setFixedWidth(BoxWidth);
    setFixedHeight(BoxHeight);

    widgetWidth_pix = itemWidth;
    widgetHeight_pix = itemHeight;

    for (int i = 0; i < activeWidgets.size(); i++) {
        activeWidgets.at(i)->setFixedSize(widgetWidth_pix, widgetHeight_pix);
    }
}

void RotatingList::snapWidgetLocations() {
    double startingAngle_deg = 90;

    int numWidgets = activeWidgets.size();

    QQueue <RotatingListWidget *> copy(activeWidgets);

    if (numWidgets > 0) {

        RotatingListWidget *firstWidget = activeWidgets.at(0);

        if (firstWidget != NULL) {

            int centered_x = (this->geometry().width() - firstWidget->geometry().width()) / 2;

            if (numWidgets >= 4) {
                startingAngle_deg = 30;
            }
            else if (numWidgets > 1) {
                startingAngle_deg = 60;
            }
            else {
                startingAngle_deg = 90;
            }

            for (int i = 0; (i < numWidgets) && (i < 5); i++) {
                RotatingListWidget *currentWidget = copy.dequeue();

                double nAngle = (30 * i) + startingAngle_deg + angleOffset_deg;
                double y_val = angleToPos(nAngle) - currentWidget->height()/2; // offset position to center of widget
                currentWidget->move(centered_x, y_val);

                //log->info(QString("Text: %1 Angle: %2 Y: %3").arg(currentWidget->text()).arg(nAngle).arg(y_val));

                currentWidget->show();
            }

        }
    }
    setStackOrder();
}

void RotatingList::resizeEvent(QResizeEvent * /*event*/) {
    snapWidgetLocations();
}

void RotatingList::mousePressEvent(QMouseEvent *event) {
    log->trace("Mouse Event");
    if (event->buttons() & Qt::LeftButton) {
        prevMouseHoldLocation = event->pos();
    }
    else if (event->buttons() & Qt::RightButton) {

    }

    updatePositions();
}

void RotatingList::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        angleOffset_deg += calculateArcAngle(prevMouseHoldLocation.y(), event->pos().y());

        log->info(QString("ARC %1").arg(angleOffset_deg));

        if (angleOffset_deg > 30) {
            angleOffset_deg = 30;
        }
        else if (angleOffset_deg < -30) {
            angleOffset_deg = -30;
        }

        updatePositions();
    }
}

void RotatingList::paintEvent(QPaintEvent *e) {
//    QPainter painter;
//    painter.begin(this);

//    for (int i = 0; i < 5; i++) {
//        painter.drawLine(QPoint(0, angleToPos(30 * (i + 1))), QPoint(this->width(), angleToPos(30 * (i + 1))));
//    }

//    painter.end();

    QFrame::paintEvent(e);

}

void RotatingList::addWidget(QString widgetText) {

    log->trace("RotatingList.addWidget");

    RotatingListWidget *nWidget = new RotatingListWidget(this);

    nWidget->setFixedSize(widgetWidth_pix, widgetHeight_pix);
    nWidget->setText(widgetText);

    nWidget->hide();
    activeWidgets.enqueue(nWidget);

}

void RotatingList::updatePositions() {

    log->trace("RotatingList.updatePositions");

    snapWidgetLocations();


}

void RotatingList::setStackOrder() {

    QQueue <RotatingListWidget *>  copy(activeWidgets);

    int numWidgets = copy.size();
    if (numWidgets == 2) {
        RotatingListWidget *widget1 = copy.dequeue();
        RotatingListWidget *widget2 = copy.dequeue();

        widget1->stackUnder(widget2);
    }
    else if (numWidgets == 3) {
        RotatingListWidget *widget1 = copy.dequeue();
        RotatingListWidget *widget2 = copy.dequeue();
        RotatingListWidget *widget3 = copy.dequeue();

        widget1->stackUnder(widget2);
        widget3->stackUnder(widget2);
    }
    else if (numWidgets == 4) {
        RotatingListWidget *widget1 = copy.dequeue();
        RotatingListWidget *widget2 = copy.dequeue();
        RotatingListWidget *widget3 = copy.dequeue();
        RotatingListWidget *widget4 = copy.dequeue();

        widget1->stackUnder(widget2);
        widget2->stackUnder(widget3);
        widget4->stackUnder(widget3);
    }
    else if (numWidgets > 4) {
        RotatingListWidget *widget1 = copy.dequeue();
        RotatingListWidget *widget2 = copy.dequeue();
        RotatingListWidget *widget3 = copy.dequeue();
        RotatingListWidget *widget4 = copy.dequeue();
        RotatingListWidget *widget5 = copy.dequeue();

        widget1->stackUnder(widget2);
        widget2->stackUnder(widget3);
        widget4->stackUnder(widget3);
        widget5->stackUnder(widget4);
    }
}

void RotatingList::rotateDown() {

}

void RotatingList::rotateUp() {
}

double RotatingList::calculateCirclarIntercept(double posY) {
    double rVal = 0;

    double a1 = pow(posY - 50, 2);
    double a2 = pow(50, 2);

    double initial = a2 - a1;
    rVal = sqrt(initial);

    return rVal;
}

double RotatingList::calculateArcAngle(int posY_1, int posY_2) {

    double arc_deg = 0;

    double useableHeight = this->height() - (borderOffset_pix * 2);

    double normY_1 = (double(posY_1) / useableHeight) * 100;
    double normY_2 = (double(posY_2) / useableHeight) * 100;

    if ((normY_1 >= 0) && (normY_2 >= 0) &&
        (normY_1 <= 100) && (normY_2 <= 100)) {
        double posX_1 = calculateCirclarIntercept(normY_1);
        double posX_2 = calculateCirclarIntercept(normY_2);

        double s1 = dist(posX_1, normY_1, posX_2, normY_2);
        //log->info(QString("a: %1 b: %2 c: %3").arg(s2).arg(s3).arg(s1));
        //log->info(QString("Dist: %1").arg(s1));

        double arc_rad = (asin(((s1 - 50) / 50)));//(pow(s2, 2) + pow(s3, 2) - pow(s1, 2)) / (2 * s2 * s3);
        arc_deg = (arc_rad * 180) / M_PI + 90;
    }

    if (posY_1 > posY_2) {
        arc_deg *= -1;
    }

    return arc_deg;
}

double RotatingList::angleToPos(double angle_deg) {

    //Radius of 50 ~ Hypotenuse

    double angle_rad = (angle_deg * M_PI) / 180;
    double y_val = 100 - (cos(angle_rad) * 50 + 50); // percentage height of widget with radius of 50

    double useableHeight = this->height() - (borderOffset_pix * 2);

    y_val = (y_val * (useableHeight / 100.0)) + borderOffset_pix;

    return y_val;

}

double RotatingList::dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
