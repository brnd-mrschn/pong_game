#include "scoreboard.h"

Scoreboard::Scoreboard(QGraphicsItem *parent)
    : QGraphicsTextItem(parent),
    leftScore(0),
    rightScore(0)
{
    qDebug() << "Scoreboard constructed!";
    updateDisplay();
}

void Scoreboard::incrementLeftScore()
{
    if (leftScore < 10) {
        ++leftScore;
        updateDisplay();
    }
}

void Scoreboard::incrementRightScore()
{
    if (rightScore < 10) {
        ++rightScore;
        updateDisplay();
    }
}

void Scoreboard::resetScores()
{
    leftScore = 0;
    rightScore = 0;
    updateDisplay();
}

void Scoreboard::updateDisplay()
{
    setPlainText(QString("%1      %2")
                     .arg(leftScore)
                     .arg(rightScore));
}

bool Scoreboard::checkVictory() const {
    return leftScore >= 10 || rightScore >= 10;
}
