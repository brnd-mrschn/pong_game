#ifndef RACKET_H
#define RACKET_H

#include <QDebug>
#include <QGraphicsRectItem>
#include <QVector2D>
#include <QKeyEvent>

class Racket : public QGraphicsRectItem
{
public:
    // Construtor
    Racket(qreal x, qreal y, qreal width, qreal height, bool isRightRacket, QGraphicsItem *parent = nullptr);

    // Método
    void advance(int phase) override;
    void setVelocity(QVector2D dir) { velocity = dir; }

private:
    // Método
    void checkBorders();

    // Atributos
    bool _isRightRacket;
    QVector2D velocity;
    QVector2D position; 
    QVector2D acceleration;
};

#endif // RACKET_H
