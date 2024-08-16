#include "pongwindow.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QPen>

PongWindow::PongWindow(QWidget *parent)
    : QWidget(parent)
{
    _scene = new PongScene();
    _scene->setBackgroundBrush(Qt::black);
    _scene->setSceneRect(-450, -300, 900, 600);

    QGraphicsRectItem *rect = new QGraphicsRectItem(-450, -300, 900, 600);
    QPen borderPen(Qt::white);
    borderPen.setWidth(3);
    rect->setPen(borderPen);
    _scene->addItem(rect);

    _view = new QGraphicsView();
    _view->setScene(_scene);
    //_view->setRenderHint(QPainter::Antialiasing);
    //_view->setRenderHint(QPainter::SmoothPixmapTransform);

    _layout = new QVBoxLayout();
    _layout->addWidget(_view);
    setLayout(_layout);

    setWindowTitle("Pong Game");
    showMaximized();

    _timer = new QTimer;
    QObject::connect(_timer, &QTimer::timeout, _scene, &PongScene::advance);
    _timer->start(1000 / 60);
}

PongWindow::~PongWindow() {}
