#ifndef ROTATINGLIST_H
#define ROTATINGLIST_H

#include <QWidget>
#include <QList>

namespace logger {
class Logger;
}

class RotatingListWidget;

class RotatingList : public QWidget
{
    Q_OBJECT
public:
    explicit RotatingList(QWidget *parent = nullptr);

    bool init(logger::Logger* nLog);

    void defineParameters(int boxWidth, int boxHeight, int itemWidth, int itemHeight);

    //Override Functions

    void resizeEvent(QResizeEvent*);
    void mousePressEvent(QMouseEvent*);

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

    logger::Logger      *log;

    QList<RotatingListWidget *> activeWidgets;
    QList<RotatingListWidget *> hiddenWidgets;

    int     maxActiveWidgets;

    int    widgetHeight_pix;
    int    widgetWidth_pix;



signals:

public slots:
};

#endif // ROTATINGLIST_H
