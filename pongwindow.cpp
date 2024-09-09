#include "pongwindow.h"
#include "menuwindow.h"

PongWindow::PongWindow(int difficultyLevel, QWidget *parent)
    : QWidget(parent)
{
    // Define fonte padrão
    QFont font("Courier New");

    // Configura a cena do Pong
    _scene = new PongScene(difficultyLevel, this);
    _scene->setSceneRect(-450, -300, 900, 600);

    // Cria borda limite do jogo
    QGraphicsRectItem *rect = new QGraphicsRectItem(-450, -300, 900, 600);
    QPen borderPen(Qt::white);
    borderPen.setWidth(2);
    rect->setPen(borderPen);
    _scene->addItem(rect);

    // Visualizador da cena
    _view = new QGraphicsView(_scene, this);
    _view->setRenderHint(QPainter::Antialiasing, true);
    _view->setBackgroundBrush(QBrush("#1c1c1c"));
    _view->setStyleSheet("border: none;");
    _view->setMinimumSize(904, 604);
    _view->setMaximumSize(904, 604);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Layout horizontal
    QHBoxLayout *layoutX = new QHBoxLayout();
    layoutX->setContentsMargins(0, 0, 0, 0);
    layoutX->setSpacing(0);

    // Layout vertical
    QVBoxLayout *layoutY = new QVBoxLayout();
    layoutY->setContentsMargins(0, 0, 0, 0);
    layoutY->setSpacing(0);

    // Instruções para o Jogador 1 (à esquerda)
    QLabel *player1Controls = new QLabel("PLAYER 1:\n\n(SOBE)  W\n(DESCE) S", this);
    player1Controls->setFont(font);
    player1Controls->setStyleSheet("QLabel {"
                                   "background-color: black;"
                                   "color: white;"
                                   "font-size: 20px;"
                                   "padding: 10px;"
                                   "}");
    player1Controls->setAlignment(Qt::AlignRight);
    player1Controls->setFixedSize(150, 120);

    // Instruções para o Jogador 2 (à direita)
    QLabel *player2Controls = new QLabel("PLAYER 2:\n\n↑  (SOBE)\n↓ (DESCE)", this);
    player2Controls->setFont(font);
    player2Controls->setStyleSheet("QLabel {"
                                   "background-color: black;"
                                   "color: white;"
                                   "font-size: 20px;"
                                   "padding: 10px;"
                                   "}");
    player2Controls->setAlignment(Qt::AlignLeft);
    player2Controls->setFixedSize(150, 120);

    // Botão "Voltar ao Menu" (centralizado)
    menuButton = new QPushButton("← VOLTAR AO MENU", this);
    menuButton->setFont(font);
    menuButton->setStyleSheet("QPushButton {"
                              "background-color: #FFFFFF; "
                              "font-weight: bold;"
                              "border-radius: 5px; "
                              "padding: 10px; "
                              "font-size: 15px; "
                              "color: black;"
                              "}");
    menuButton->setFixedWidth(menuButton->sizeHint().width());
    connect(menuButton, &QPushButton::clicked, this, &PongWindow::returnToMenu);

    // Adiciona os itens aos layouts
    layoutX->addWidget(player1Controls, 0, Qt::AlignRight);
    layoutX->addWidget(_view);
    layoutX->addWidget(player2Controls, 0, Qt::AlignLeft);
    layoutY->addWidget(menuButton, 0, Qt::AlignHCenter);

    // Empilha os itens
    mainLayout->addLayout(layoutX);
    mainLayout->addLayout(layoutY);

    // Configurações da janela
    setStyleSheet("background-color: black;");
    setWindowTitle("Pong Game");
    showMaximized();

    // Inicia o jogo a 60fps
    _timer = new QTimer;
    QObject::connect(_timer, &QTimer::timeout, _scene, &PongScene::advance);
    _timer->start(1000 / 60);
}

void PongWindow::updateBallSpeed(int newSpeed)
{
    if (_scene) {
        _scene->updateBallSpeed(newSpeed);
    }
}

void PongWindow::returnToMenu() {
    MenuWindow* menu = new MenuWindow();
    menu->show();
    this->close();
}

PongWindow::~PongWindow() {}
