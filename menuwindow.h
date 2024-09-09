#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QApplication>
#include <QFont>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class Ball;

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    // Construtor
    MenuWindow(QWidget *parent = nullptr);

private:
    // Atributos
    int difficultyLevel;
    Ball        *_ball;
    QVBoxLayout *layout;
    QPushButton *playButton;
    QPushButton *aboutButton;
    QPushButton *exitButton;
    QPushButton *difficultyLeftButton;
    QPushButton *difficultyRightButton;
    QLabel      *difficultyLabel;
    QLabel      *titleLabel;
    
private slots:
    void startGame();
    void showAbout();
    void changeDifficulty(int delta);
    void setDifficulty(int level);

signals:
    void difficultyChanged(int newSpeed);
};

#endif // MENUWINDOW_H
