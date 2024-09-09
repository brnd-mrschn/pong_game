#include "menuwindow.h"
#include "ball.h"
#include "pongwindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent), difficultyLevel(2)                                       // Dificuldade média padrão
{
    // Fonte padrão escolhida
    QFont font("Courier New");

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Título do jogo
    titleLabel = new QLabel("Pong Game", this);
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 120px; font-weight: bold; color: white;");

    // Botões do menu
    playButton = new QPushButton("JOGAR", this);
    playButton->setFont(font);
    aboutButton = new QPushButton("SOBRE", this);
    aboutButton->setFont(font);
    exitButton = new QPushButton("SAIR", this);
    exitButton->setFont(font);

    // Botão de dificuldade
    difficultyLabel = new QLabel("DIFICULDADE: MÉDIO", this);
    difficultyLabel->setFont(font);
    difficultyLabel->setStyleSheet("background-color: #FFFFFF; font-weight: bold; font-size: 25px;  color: black;");
    difficultyLabel->setAlignment(Qt::AlignCenter);

    // Setas para alterar a dificuldade
    difficultyLeftButton = new QPushButton("<", this);
    difficultyLeftButton->setFont(font);
    difficultyLeftButton->setStyleSheet("font-size: 70px; font-weight: bold; color: black;");
    difficultyRightButton = new QPushButton(">", this);
    difficultyRightButton->setFont(font);
    difficultyRightButton->setStyleSheet("font-size: 70px; font-weight: bold; color: black;");

    // Estilo dos botões
    QString buttonStyle = "background-color: #FFFFFF; "
                          "font-weight: bold;"
                          "border-radius: 5px; "
                          "padding: 5px; "
                          "font-size: 25px; "
                          "color: black;";
    playButton->setStyleSheet(buttonStyle);
    aboutButton->setStyleSheet(buttonStyle);
    difficultyLeftButton->setStyleSheet(buttonStyle);
    difficultyRightButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    // Definir políticas de tamanho
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    playButton->setSizePolicy(sizePolicy);
    aboutButton->setSizePolicy(sizePolicy);
    difficultyLeftButton->setSizePolicy(sizePolicy);
    difficultyRightButton->setSizePolicy(sizePolicy);
    exitButton->setSizePolicy(sizePolicy);
    QSize fixedSize(390, 45);                                                   // Define o tamanho do botão
    playButton->setFixedSize(fixedSize);
    aboutButton->setFixedSize(fixedSize);
    exitButton->setFixedSize(fixedSize);
    difficultyLabel->setFixedSize(300, 30);
    difficultyLeftButton->setFixedSize(QSize(30, 30));
    difficultyRightButton->setFixedSize(QSize(30, 30));

    // Conexões dos botões as ruas respectivas funções
    connect(playButton, &QPushButton::clicked, this, &MenuWindow::startGame);
    connect(aboutButton, &QPushButton::clicked, this, &MenuWindow::showAbout);
    connect(difficultyLeftButton, &QPushButton::clicked, this, [this]() { changeDifficulty(-1); });
    connect(difficultyRightButton, &QPushButton::clicked, this, [this]() { changeDifficulty(1); });
    connect(exitButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);

    // Organização do campo de dificuldade
    QHBoxLayout *difficultyLayout = new QHBoxLayout();
    difficultyLayout->addWidget(difficultyLeftButton);
    difficultyLayout->addWidget(difficultyLabel);
    difficultyLayout->addWidget(difficultyRightButton);
    difficultyLayout->setAlignment(Qt::AlignCenter);

    // Widget para o layout de dificuldade
    QWidget *difficultyWidget = new QWidget(this);
    difficultyWidget->setLayout(difficultyLayout);
    difficultyWidget->setStyleSheet("background-color: #FFFFFF; font-weight: bold; border-radius: 5px; padding: 0px; color: black;");

    // Layout dos botões
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(playButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(difficultyWidget, 0, Qt::AlignCenter);
    buttonLayout->addWidget(aboutButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(exitButton, 0, Qt::AlignCenter);
    buttonLayout->addStretch();

    // Layout principal
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    // Inicialização
    setLayout(mainLayout);
    setWindowTitle("Pong Game");
    setStyleSheet("background-color: black; color: white;");
    showMaximized();
}

void MenuWindow::startGame()
{
    PongWindow *gameWindow = new PongWindow(difficultyLevel);
    connect(this, &MenuWindow::difficultyChanged, gameWindow, &PongWindow::updateBallSpeed);
    gameWindow->show();
    this->close();
}

void MenuWindow::showAbout()
{
    QMessageBox::about(this, "Sobre o Pong",
                    "Pong é um dos primeiros e mais icônicos videogames, simula um jogo de tênis de mesa onde dois jogadores controlam raquetes para rebater uma bola de um lado para o outro da tela. O objetivo é marcar pontos fazendo a bola passar pela raquete do adversário. Simples em sua mecânica, Pong é conhecido por sua jogabilidade viciante e por ter sido um marco na história dos videogames.\n\n\n"
                    "Criado por Amanda e Bernardo\n"
                    "Disciplina: Programação Orientada a Objetos\n"
                    "Professor: Hugo Marcondes\n"
                    "Instituto Federal de Santa Catarina - 2024");
}

void MenuWindow::changeDifficulty(int delta)
{
    difficultyLevel += delta;
    if (difficultyLevel < 1) difficultyLevel = 1;
    if (difficultyLevel > 3) difficultyLevel = 3;

    switch(difficultyLevel) {
        case 1:
            difficultyLabel->setText("DIFICULDADE: FÁCIL");
            qDebug() << "Difficulty Selected: 1";
            break;
        case 2:
            difficultyLabel->setText("DIFICULDADE: MÉDIO");
            qDebug() << "Difficulty Selected: 2";
            break;
        case 3:
            difficultyLabel->setText("DIFICULDADE: DIFÍCIL");
            qDebug() << "Difficulty Selected: 3";
            break;
    }
}

void MenuWindow::setDifficulty(int level) {
    difficultyLevel = level;
}
