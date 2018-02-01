#include "rotatinglistwidget.h"

#include <QDebug>

RotatingListWidget::RotatingListWidget(QWidget *parent) : QLabel(parent)
{
    QPixmap image("../AppShowcase/Resources/dummy.jpg");

    if (image.isNull()) {
        qDebug () << " NULL IMAGE";
    }
    setPixmap(image);

    setAlignment(Qt::AlignCenter);
    setFrameStyle(QFrame::Box);
}
