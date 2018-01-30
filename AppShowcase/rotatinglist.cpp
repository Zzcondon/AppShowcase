#include "rotatinglist.h"
#include "rotatinglistwidget.h"

RotatingList::RotatingList(QWidget *parent) : QWidget(parent),
    activeWidgets(),
    hiddenWidgets(),
    maxActiveWidgets(5)
{

}

void RotatingList::addWidget(QString widgetText) {
    RotatingListWidget *nWidget = new RotatingListWidget(this);

    if (activeWidgets.size() <= maxActiveWidgets) {
        activeWidgets.push_front(nWidget);
    }
    else {
        hiddenWidgets.push_back(nWidget);
    }
}

void RotatingList::updatePositions() {
    int numWidgets = activeWidgets.size();



}
