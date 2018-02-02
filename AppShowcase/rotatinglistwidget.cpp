#include "rotatinglistwidget.h"

#include <QDebug>

RotatingListWidget::RotatingListWidget(QWidget *parent) : QLabel(parent)
{
//    QPixmap image("../AppShowcase/Resources/dummy.jpg");

//    if (image.isNull()) {
//        qDebug () << " NULL IMAGE";
//    }
//    setPixmap(image);

    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    setAlignment(Qt::AlignCenter);
    setFrameStyle(QFrame::Box);
}
