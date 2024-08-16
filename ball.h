#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QVector2D>

class Ball : public QGraphicsEllipseItem
{
public:
    Ball(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);

    void advance(int phase) override;
    void startMovement();

private:
    void resetPosition();
    void handleCollisions();

private:
    QVector2D position;
    QVector2D velocity;
    QVector2D acceleration;
    unsigned int collisionBlock;
};

#endif // BALL_H
