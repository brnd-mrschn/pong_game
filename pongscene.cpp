#include "ball.h"
#include "pongscene.h"
#include "racket.h"
#include "scoreboard.h"

PongScene::PongScene(int difficultyLevel, QObject *parent)
    : QGraphicsScene(parent), _scoreboard(new Scoreboard()), gameOverFlag(false)
{
    // Configura o fundo da cena
    QGraphicsRectItem *background = new QGraphicsRectItem(sceneRect());
    background->setBrush(Qt::black);
    addItem(background);

    // Define linha tracejada de divisão
    _line = new QGraphicsLineItem(0, -300, 0, 300);
    QPen linePen(Qt::white);
    linePen.setWidth(2);
    QVector<qreal> dashPattern;
    dashPattern << 12 << 12;
    linePen.setDashPattern(dashPattern);
    _line->setPen(linePen);
    addItem(_line);

    // Configura o placar
    _scoreboard->setDefaultTextColor(Qt::white);
    _scoreboard->setFont(QFont("Courier New", 35, QFont::Bold));
    _scoreboard->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);
    addItem(_scoreboard);
    updateScoreboardPosition();

    // Define a bola
    _ball = new Ball(-10, -10, 20, 20, nullptr, _scoreboard, difficultyLevel);
    _ball->setBrush(Qt::white);
    _ball->setScale(1);
    _ball->setFlag(QGraphicsItem::ItemIsFocusable);
    addItem(_ball);

    // Define a raquete esquerda
    _racket_left = new Racket(-5, -50, 10, 100, false);
    _racket_left->setBrush(Qt::white);
    _racket_left->setFlag(QGraphicsItem::ItemIsFocusable);
    _racket_left->setPos(QPointF(-430, 0));
    addItem(_racket_left);

    // Define a raquete direita
    _racket_right = new Racket(-5, -50, 10, 100, true);
    _racket_right->setBrush(Qt::white);
    _racket_right->setFlag(QGraphicsItem::ItemIsFocusable);
    _racket_right->setPos(QPointF(430, 0));
    addItem(_racket_right);

    // Associa as raquetes à bola
    _ball->setLeftRacket(_racket_left);
    _ball->setRightRacket(_racket_right);

    // Inicia o jogo a 60fps
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &PongScene::updateGame);
    _timer->start(1000 / 60);
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

void PongScene::updateBallSpeed(int newSpeed)
{
    if (_ball) {
        _ball->setSpeed(newSpeed);
    }
}

void PongScene::updateScoreboardPosition() {
    _scoreboard->setPos(sceneRect().center() - QPointF(_scoreboard->boundingRect().width() / 2, 280));
}

void PongScene::updateGame() {
    _ball->updateGame();
    updateScoreboardPosition();
    checkGameOver();
}

void PongScene::checkGameOver() {
    if (!gameOverFlag  && _scoreboard->checkVictory()) {
        gameOverFlag = true;
        _timer->stop();
        _line->hide();
        _scoreboard->hide();
        _ball->hide();
        _racket_left->hide();
        _racket_right->hide();
        QString winner = (_scoreboard->getLeftScore() >= 10) ? "Player 1" : "Player 2";
        showGameOver(winner);
    }
}

void PongScene::showGameOver(const QString& winner) {
    // Exibe "Game Over"
    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("GAME OVER!");
    gameOverText->setDefaultTextColor(Qt::white);
    gameOverText->setFont(QFont("Courier New", 65, QFont::Bold));
    gameOverText->setPos(sceneRect().center() - QPointF(gameOverText->boundingRect().width() / 2, 55));
    addItem(gameOverText);

    // Exibe o jogador vencedor
    QGraphicsTextItem* winnerText = new QGraphicsTextItem("Vencedor: " + winner);
    winnerText->setDefaultTextColor(Qt::white);
    winnerText->setFont(QFont("Courier New", 25, QFont::Bold));
    winnerText->setPos(sceneRect().center() - QPointF(winnerText->boundingRect().width() / 2, -40));
    addItem(winnerText);

    // Exibe o placar final
    QGraphicsTextItem* finalScoreText = new QGraphicsTextItem(QString("Placar final: %1 - %2").arg(_scoreboard->getLeftScore()).arg(_scoreboard->getRightScore()));
    finalScoreText->setDefaultTextColor(Qt::white);
    finalScoreText->setFont(QFont("Courier New", 25));
    finalScoreText->setPos(sceneRect().center() - QPointF(finalScoreText->boundingRect().width() / 2, 100));
    addItem(finalScoreText);
}
