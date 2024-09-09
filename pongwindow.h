#ifndef PONGWINDOW_H
#define PONGWINDOW_H

#include "ball.h"
#include "racket.h"
#include "pongscene.h"
#include <QtWidgets>
#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QTimer>
#include <QPen>
#include <QGraphicsLineItem>
#include <QColor>
#include <QBrush>

class PongWindow : public QWidget
{
    Q_OBJECT

public:
    // Construtor
    explicit PongWindow(int difficultyLevel, QWidget *parent = nullptr);

    // Métodos
    void returnToMenu();
    void updateBallSpeed(int newSpeed);

    // Destruidor
    ~PongWindow();

private:
    // Atributos
    PongScene     * _scene;
    Ball          * _ball;
    QGraphicsView * _view;
    QTimer        * _timer;
    QVBoxLayout   * _layout;
    QLabel        * controlsLabel;
    QPushButton   * menuButton;
};

#endif // PONGWINDOW_H
