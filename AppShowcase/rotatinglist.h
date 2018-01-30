#ifndef ROTATINGLIST_H
#define ROTATINGLIST_H

#include <QWidget>
#include <QList>

class RotatingListWidget;

class RotatingList : public QWidget
{
    Q_OBJECT
public:
    explicit RotatingList(QWidget *parent = nullptr);

    void addWidget(QString widgetText);

    void updatePositions();

private:

    QList<RotatingListWidget *> activeWidgets;
    QList<RotatingListWidget *> hiddenWidgets;


    int     maxActiveWidgets;
signals:

public slots:
};

#endif // ROTATINGLIST_H
