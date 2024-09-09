#ifndef PONGSCENE_H
#define PONGSCENE_H

#include <QDebug>
#include <QFont>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QtWidgets>

class Ball;
class Racket;
class Scoreboard;

class PongScene : public QGraphicsScene
{
    Q_OBJECT

public:
    // Construtor
    explicit PongScene(int difficultyLevel, QObject *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    // Métodos
    void checkGameOver();
    void showGameOver(const QString& winner);
    void updateScoreboardPosition();

    // Atributos
    bool gameOverFlag;
    QGraphicsLineItem *_line;
    Ball              *_ball;
    Racket            *_racket_left;
    Racket            *_racket_right;
    QTimer            *_timer;
    Scoreboard        *_scoreboard;

public slots:
    void updateBallSpeed(int newSpeed);

private slots:
    void updateGame();

signals:
    void gameEnded();
};

#endif // PONGSCENE_H
