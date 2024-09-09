#ifndef BALL_H
#define BALL_H

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QRandomGenerator>
#include <QTimer>
#include <QtMath>
#include <QVector2D>

class Scoreboard;

class Ball : public QGraphicsEllipseItem
{

public:
    // Construtor
    Ball(qreal x,
         qreal y,
         qreal width,
         qreal height,
         QGraphicsItem *parent = nullptr,
         Scoreboard *scoreboard = nullptr,
         int difficulty = 2);

    // Métodos
    void startMovement();                                                       // ball.cpp
    void advance(int phase);                                                    // ball.cpp
    void resetPosition();                                                       // ball.cpp
    void updateGame();                                                          // ball.cpp
    void setDifficulty(int difficulty);                                         // ball.cpp | menuwindow.cpp
    void setLeftRacket(QGraphicsItem* racket) { _racket_left = racket; }        //pongscene.cpp
    void setRightRacket(QGraphicsItem* racket) { _racket_right = racket; }      //pongscene.cpp
    void setSpeed(qreal newSpeed) { speed = newSpeed; }                         //pongscene.cpp

private:
    // Método
    void handleCollisions();

    // Atributos
    bool goalFlag;
    int collisionBlockX;
    int collisionBlockY;
    int difficultyLevel;
    qreal speed;
    qreal _previousPosition;
    QGraphicsItem *_racket_left;
    QGraphicsItem *_racket_right;
    QVector2D velocity;
    QVector2D position;
    Scoreboard *_scoreboard;
};

#endif // BALL_H
