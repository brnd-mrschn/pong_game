#ifndef PONGWINDOW_H
#define PONGWINDOW_H

#include <QtWidgets>
//#include <QWidget>
//#include <QGraphicsScene>
//#include <QGraphicsView>
#include "ball.h"
#include "racket.h"
#include "pongscene.h"

class PongWindow : public QWidget
{
    Q_OBJECT

public:
    PongWindow(QWidget *parent = nullptr);
    ~PongWindow();

private:
    PongScene      * _scene;
    QGraphicsView  * _view;
    QTimer         * _timer;
    QVBoxLayout    * _layout;

};
#endif // PONGWINDOW_H
