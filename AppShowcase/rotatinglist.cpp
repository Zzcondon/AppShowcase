#include "rotatinglist.h"
#include "rotatinglistwidget.h"

#include "logger.h"

RotatingList::RotatingList(QWidget *parent) : QWidget(parent),
    activeWidgets(),
    hiddenWidgets(),
    maxActiveWidgets(5),
    widgetHeight_pix(50),
    widgetWidth_pix(150)
{

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

    for (int j = 0; j < hiddenWidgets.size(); j++) {
        hiddenWidgets.at(j)->setFixedSize(widgetWidth_pix, widgetHeight_pix);
    }
}

void RotatingList::resizeEvent(QResizeEvent * /*event*/) {
    updatePositions();
}

void RotatingList::mousePressEvent(QMouseEvent *event) {
    log->trace("Mouse Event");
    if (event->buttons() & Qt::LeftButton) {
        rotateUp();
        log->trace("Mouse Event Up");
    }
    else if (event->button() & Qt::RightButton) {
        rotateDown();
        log->trace("Mouse Event Down");
    }

    updatePositions();
}

void RotatingList::addWidget(QString widgetText) {

    log->trace("RotatingList.addWidget");

    RotatingListWidget *nWidget = new RotatingListWidget(this);

    nWidget->setFixedSize(widgetWidth_pix, widgetHeight_pix);
    nWidget->setText(widgetText);

    if (activeWidgets.size() < maxActiveWidgets) {
        activeWidgets.push_front(nWidget);
    }
    else {
        hiddenWidgets.push_back(nWidget);
    }


}

void RotatingList::updatePositions() {

    log->trace("RotatingList.updatePositions");

    int numWidgets = activeWidgets.size();

    if (numWidgets > 0) {

        RotatingListWidget *centerWidget = activeWidgets.at(0);

        int containerHeight_pix = this->geometry().height();
        int containerWidth_pix = this->geometry().width();

        if (centerWidget != NULL) {

            int itemHeight_pix = widgetHeight_pix;
            int itemWidth_pix = widgetWidth_pix;

            if ((containerHeight_pix > itemHeight_pix) ||
                    (containerWidth_pix > itemWidth_pix)) {

                switch (numWidgets) {
                    case 1:
                        updatePositions_mid(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 0);
                        break;
                    case 2:
                        updatePositions_midTop(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 0);
                        updatePositions_mid(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 1);
                        break;
                    case 3:
                        updatePositions_midTop(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 0);
                        updatePositions_mid(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 1);
                        updatePositions_midBot(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 2);
                        break;
                    case 4:
                        updatePositions_top(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 0);
                        updatePositions_midTop(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 1);
                        updatePositions_mid(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 2);
                        updatePositions_midBot(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 3);
                        break;
                    case 5:
                        updatePositions_top(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 0);
                        updatePositions_midTop(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 1);
                        updatePositions_mid(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 2);
                        updatePositions_midBot(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 3);
                        updatePositions_bot(containerWidth_pix, containerHeight_pix, itemWidth_pix, itemHeight_pix, 4);
                        break;

                }
            }
            else {
                log->err(QString("RotatingList(%1).updatePostitions_1: [%2 %3] [%4 %5]").arg(objectName()).arg(containerWidth_pix).arg(containerHeight_pix).arg(widgetWidth_pix).arg(widgetHeight_pix));
                log->err(QString("RotatingList (%1).updatePositions_1: Unable to fit items in container").arg(objectName()));
            }
        } // CenterWidget != NULL
    } // Num Widgets


    for (int numActive = 0; numActive < activeWidgets.size(); numActive++) {
        activeWidgets.at(numActive)->show();
    }

    for (int numHidden = 0; numHidden < hiddenWidgets.size(); numHidden++) {
        hiddenWidgets.at(numHidden)->hide();
    }
}

void RotatingList::updatePositions_mid(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index) {


    RotatingListWidget *centerWidget = activeWidgets.at(index);

    if (centerWidget != NULL) {
        int top_pix = (bHeight_pix - iHeight_pix) / 2;
        int left_pix = (bWidth_pix - iWidth_pix) / 2;

        centerWidget->setFixedSize(iWidth_pix, iHeight_pix);
        centerWidget->move(left_pix, top_pix);
    }

}

void RotatingList::updatePositions_midTop(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index) {

    double sizeReduction_percent = 0.96;
    RotatingListWidget *midTopWidget = activeWidgets.at(index);


    if (midTopWidget != NULL) {

        int nItemHeight = iHeight_pix * sizeReduction_percent;
        int nItemWidth = iWidth_pix * sizeReduction_percent;

        int top_pix = (bHeight_pix - nItemHeight) / 5;
        int left_pix = (bWidth_pix - nItemWidth) / 2;

        midTopWidget->setFixedSize(nItemWidth, nItemHeight);
        midTopWidget->move(left_pix, top_pix);
    }

}

void RotatingList::updatePositions_midBot(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index) {


    double sizeReduction_percent = 0.96;
    RotatingListWidget *midBotWidget = activeWidgets.at(index);

    if (midBotWidget != NULL) {

        int nItemHeight = iHeight_pix * sizeReduction_percent;
        int nItemWidth = iWidth_pix * sizeReduction_percent;

        int top_pix = ((bHeight_pix - nItemHeight) / 5) * 4;
        int left_pix = (bWidth_pix - nItemWidth) / 2;

        midBotWidget->setFixedSize(nItemWidth, nItemHeight);
        midBotWidget->move(left_pix, top_pix);
    }

}

void RotatingList::updatePositions_top(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index) {

    double sizeReduction_percent = 0.90;
    RotatingListWidget *topWidget = activeWidgets.at(index);

    if (topWidget != NULL) {

        int nItemHeight = iHeight_pix * sizeReduction_percent;
        int nItemWidth = iWidth_pix * sizeReduction_percent;

        int top_pix = ((bHeight_pix - nItemHeight) / 10);
        int left_pix = (bWidth_pix - nItemWidth) / 2;

        topWidget->setFixedSize(nItemWidth, nItemHeight);
        topWidget->move(left_pix, top_pix);
    }
}

void RotatingList::updatePositions_bot(int bWidth_pix, int bHeight_pix, int iWidth_pix, int iHeight_pix, int index) {
    double sizeReduction_percent = 0.90;
    RotatingListWidget *botWidget = activeWidgets.at(index);

    if (botWidget != NULL) {

        int nItemHeight = iHeight_pix * sizeReduction_percent;
        int nItemWidth = iWidth_pix * sizeReduction_percent;

        int top_pix = ((bHeight_pix - nItemHeight) / 10) * 9;
        int left_pix = (bWidth_pix - nItemWidth) / 2;

        botWidget->setFixedSize(nItemWidth, nItemHeight);
        botWidget->move(left_pix, top_pix);
    }

}

void RotatingList::rotateDown() {
    hiddenWidgets.append(activeWidgets.takeLast());
    activeWidgets.prepend(hiddenWidgets.takeFirst());

}

void RotatingList::rotateUp() {

    hiddenWidgets.prepend(activeWidgets.takeFirst());
    activeWidgets.append(hiddenWidgets.takeLast());
}
