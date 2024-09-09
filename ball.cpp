#include "ball.h"
#include "racket.h"
#include "scoreboard.h"

qreal getRandomAngle() {
    // Define todos os ângulos de disparos possíveis
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

Ball::Ball(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent, Scoreboard* scoreboard, int difficulty)
    : QGraphicsEllipseItem(x, y, width, height, parent),
    goalFlag(false),
    collisionBlockX(0),
    collisionBlockY(0),
    difficultyLevel(difficulty),
    speed(0),
    _racket_left(nullptr),
    _racket_right(nullptr),
    _scoreboard(scoreboard)
{
    qDebug() << "Ball constructed!";
    //acceleration.setX(0);
    //acceleration.setY(0);
    
    // Atraso para iniciar o jogo
    QTimer::singleShot(3000, [this]() {
        startMovement();
    });
}

void Ball::startMovement()
{
    if (difficultyLevel == 1) {
        speed = 4;
    } else if (difficultyLevel == 2) {
        speed = 7;
    } else if (difficultyLevel == 3) {
        speed = 12;
    }
    qreal angle = getRandomAngle();
    qreal radian = qDegreesToRadians(angle);
    QVector2D newVelocity(speed * qCos(radian), speed * qSin(radian));
    velocity = newVelocity;
}

void Ball::advance(int phase)
{
    if (phase == 0) return;

    // Armazena a posição da bola
    position.setX(pos().x());
    position.setY(pos().y());
    
    // Armazena o eixo X da bola antes de atualizá-la
    _previousPosition = position.x();

    // Atualiza a posição da bola com a velocidade
    position += velocity;

    // Anti repique eixo Y
    if(collisionBlockY) {
        collisionBlockY--;
    }

    // Verifica colisão com as bordas verticais
    if (position.x() < -460 || position.x() > 460) {
        resetPosition();
        startMovement();
    }

    // Verifica colisão com as bordas horizontais
    if (!collisionBlockY && (position.y() > 290 || position.y() < -290)) {
        collisionBlockY = 10;
        velocity.setY(-velocity.y());
    }

    // Verifica colisão com as raquetes
    handleCollisions();

    // Atualiza a posição na cena
    setPos(position.toPointF());
}

void Ball::handleCollisions()
{
    // Evita o crash
    if (!_racket_left || !_racket_right) {
        qDebug() << "Nenhuma raquete detectada";
        return;
    }

    // Armazena as posições atuais das raquetes
    QPointF leftRacketPos = _racket_left->pos();
    QPointF rightRacketPos = _racket_right->pos();

    // Anti repique eixo X
    if(collisionBlockX) {
        collisionBlockX--;
        return;
    }

    // Verifica se a bola está dentro da área de colisão com as raquetes
    if ((position.x() > -415) && (position.x() < 415)) {
        return;
    }

    // Lógica de colisão com a raquete esquerda
    if (position.x() <= leftRacketPos.x() + 15 && position.y() <= leftRacketPos.y() + 60 && position.y() >= leftRacketPos.y() - 60 && _previousPosition > (-415)) {
        qDebug() << "Collided Left";
        collisionBlockX = 20;
        qreal relativeY = (position.y() - leftRacketPos.y()) / 50;              
        qreal angle = 45 * relativeY;                                           // Ajusta o multiplicador para alterar a intensidade do ângulo
        qreal radian = qDegreesToRadians(angle);
        velocity = QVector2D(speed * qCos(radian), speed * qSin(radian));
        velocity.setX(velocity.x());

    // Lógica de colisão com a raquete direita
    } else if (position.x() >= rightRacketPos.x() - 15 && position.y() <= rightRacketPos.y() + 60 && position.y() >= rightRacketPos.y() - 60 && _previousPosition < 415) {
        qDebug() << "Collided Right";
        collisionBlockX = 20;
        qreal relativeY = (position.y() - rightRacketPos.y()) / 50;
        qreal angle = 45 * relativeY;                                           // Ajusta o multiplicador para alterar a intensidade do ângulo
        qreal radian = qDegreesToRadians(angle);
        velocity = QVector2D(speed * qCos(radian), speed * qSin(radian));
        velocity.setX(-velocity.x());
    }
}

void Ball::resetPosition()
{
    position = QVector2D(0, 0);
    setPos(position.toPointF());
    goalFlag = true;
    updateGame();
}

void Ball::updateGame()
{
    if (goalFlag) {
        if (_previousPosition > 430) {
            qDebug() << "Goal Player 1!";
            if (_scoreboard) {
                _scoreboard->incrementLeftScore();
            }
        } else if (_previousPosition < (-430)) {
            qDebug() << "Goal Player 2!";
            if (_scoreboard) {
                _scoreboard->incrementRightScore();
            }
        }
        goalFlag = false;
    }
}

void Ball::setDifficulty(int difficulty)
{
    difficultyLevel = difficulty;
}
