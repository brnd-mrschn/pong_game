#include "racket.h"

Racket::Racket(qreal x, qreal y, qreal width, qreal height, bool isRightRacket, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent),
    _isRightRacket(isRightRacket)
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
