#include "racket.h"
#include <QDebug>
#include <QKeyEvent>

Racket::Racket(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{
    qDebug() << "Racket constructed!";
    acceleration.setX(0);
    acceleration.setY(0);
}

void Racket::advance(int phase)
{
    if (phase == 0)
        return;

    position.setX(pos().x());
    position.setY(pos().y());

    position += velocity;
    velocity += acceleration;

    checkBorders();

    setPos(position.toPointF());
}

QPainterPath Racket::shape() const
{
    QPainterPath path;
    path.addRect(-5,-50,100,100);
    return path;
}

void Racket::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key Press Event in Racket";

    if (event->key() == Qt::Key_W) {
        velocity.setY(-0.10);
    } else if (event->key() == Qt::Key_S) {
        velocity.setY(0.10);
    }

    QGraphicsRectItem::keyPressEvent(event);
}

void Racket::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "Key Release Event in Racket";

    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S) {
        velocity.setY(0);
    }

    QGraphicsRectItem::keyReleaseEvent(event);
}

void Racket::checkBorders()
{
    if (position.y() > 250) {
        velocity.setX(0);
        velocity.setY(0);
        position.setY(250);
    }

    if (position.y() < -250) {
        velocity.setX(0);
        velocity.setY(0);
        position.setY(-250);
    }
}
