#ifndef ROTATINGLISTWIDGET_H
#define ROTATINGLISTWIDGET_H

#include <QWidget>
#include <QLabel>

class RotatingListWidget : public QLabel
{
    Q_OBJECT
public:
    explicit RotatingListWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    bool paint_flag;

signals:

public slots:
};

#endif // ROTATINGLISTWIDGET_H
