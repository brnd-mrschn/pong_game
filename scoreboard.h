#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDebug>
#include <QGraphicsTextItem>

class Scoreboard : public QGraphicsTextItem
{
    Q_OBJECT

public:
    // Construtor
    explicit Scoreboard(QGraphicsItem *parent = nullptr);
    
    // Métodos
    bool checkVictory() const;
    void incrementLeftScore();
    void incrementRightScore();
    void resetScores();
    int getLeftScore() const { return leftScore; }
    int getRightScore() const { return rightScore; }

private:
    // Método
    void updateDisplay();

    // Atributos
    int leftScore;
    int rightScore;
};

#endif // SCOREBOARD_H
