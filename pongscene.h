#ifndef PONGSCENE_H
#define PONGSCENE_H

#include <QGraphicsScene>
#include "ball.h"
#include "racket.h"

class PongScene : public QGraphicsScene
{
public:
    explicit PongScene(QObject *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ball           * _ball;
    Racket         * _racket_left;
    Racket         * _racket_right;
};

#endif // PONGSCENE_H
