#include "ball.h"
#include "racket.h"
#include <QDebug>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QtMath>

qreal getRandomAngle() {

    qreal ranges[][3] = {
        {0, 45},
        {135, 180},
        {180, 225},
        {315, 360}
    };

    int rangeIndex = QRandomGenerator::global()->bounded(4);
    qreal min = ranges[rangeIndex][0];
    qreal max = ranges[rangeIndex][1];

    qreal angle = min + QRandomGenerator::global()->generateDouble() * (max - min);
    return angle;
}

Ball::Ball(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, width, height, parent)
{
    qDebug() << "Ball constructed!";
    acceleration.setX(0);
    acceleration.setY(0);

    startMovement();
}

void Ball::advance(int phase)
{
    if (phase == 0)
        return;

    position.setX(pos().x());
    position.setY(pos().y());

    position += velocity;
    velocity += acceleration;

    // Verifica colisão com as bordas verticais
    if (position.x() < -440 || position.x() > 440) {
        resetPosition();
        setPos(position.toPointF());
        startMovement();
    }

    // Verifica colisão com as bordas horizontais
    if (position.y() > 290 || position.y() < -290) {
        velocity.setY(-velocity.y());
    }

    // Verifica colisão com as raquetes
    handleCollisions();

    setPos(position.toPointF());
}

void Ball::handleCollisions()
{
    if(collisionBlock){
        collisionBlock--;
        return;
    }

    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (QGraphicsItem *item : collidingItems) {

        Racket *racket = dynamic_cast<Racket *>(item);
        qDebug() << "Ball Position:" << position.x();

        if (racket && !((position.x() < -430) || (position.x() > 430))) {
            qDebug() << "Racket Position:" << racket->pos();
            qDebug() << "Velo:" << velocity.x();
            velocity.setX(-velocity.x());
            collisionBlock = 30;
        }
    }
}

void Ball::startMovement()
{
    qreal angle = getRandomAngle();
    qreal speed = 6;

    qreal radian = qDegreesToRadians(angle);
    QVector2D newVelocity(speed * qCos(radian), speed * qSin(radian));
    velocity = newVelocity;
}

void Ball::resetPosition()
{
    position = QVector2D(0, 0);
    setPos(position.toPointF());
}
