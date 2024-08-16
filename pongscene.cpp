#include "pongscene.h"
#include <QDebug>
#include <QKeyEvent>

PongScene::PongScene(QObject *parent)
    : QGraphicsScene{parent}
{
    // Gera bola
    _ball = new Ball(-10, -10, 20, 20);
    _ball->setBrush(Qt::white);
    _ball->setScale(1);
    _ball->setFlag(QGraphicsItem::ItemIsFocusable);
    addItem(_ball);

    // Gera raquete 1
    _racket_left = new Racket(-5, -50, 10, 100);
    _racket_left->setBrush(Qt::white);
    _racket_left->setFlag(QGraphicsItem::ItemIsFocusable);
    _racket_left->setPos(QPointF(-430, 0));
    addItem(_racket_left);

    // Gera raquete 2
    _racket_right = new Racket(-5, -50, 10, 100);
    _racket_right->setBrush(Qt::white);
    _racket_right->setFlag(QGraphicsItem::ItemIsFocusable);
    _racket_right->setPos(QPointF(430, 0));
    addItem(_racket_right);
}

void PongScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W) {
        _racket_left->setVelocity(QVector2D(0, -10));
    } else if (event->key() == Qt::Key_S) {
        _racket_left->setVelocity(QVector2D(0, 10));
    }

    if (event->key() == Qt::Key_Up) {
        _racket_right->setVelocity(QVector2D(0, -10));
    } else if (event->key() == Qt::Key_Down) {
        _racket_right->setVelocity(QVector2D(0, 10));
    }

    QGraphicsScene::keyPressEvent(event);
}

void PongScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S) {
        _racket_left->setVelocity(QVector2D(0, 0));
    }

    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        _racket_right->setVelocity(QVector2D(0, 0));
    }

    QGraphicsScene::keyReleaseEvent(event);
}
