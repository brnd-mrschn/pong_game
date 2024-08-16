#ifndef RACKET_H
#define RACKET_H

#include <QGraphicsRectItem>
#include <QVector2D>

class Racket : public QGraphicsRectItem
{
public:
    Racket(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void advance(int phase) override;
    QPainterPath shape() const;

    void setVelocity(QVector2D dir) { velocity = dir; }

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void checkBorders();

private:
    QVector2D position;
    QVector2D velocity;
    QVector2D acceleration;


};

#endif // RACKET_H
