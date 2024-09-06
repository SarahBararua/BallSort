#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include "tube.h"
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

// Construtor da janela principal que inicializa a interface e a lógica do jogo
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameStarted(false)
    , gameWon(false)
    , isMoving(false)
    , currentLevel(1)  // Inicializa o nível em 1
{
    ui->setupUi(this);  // Configura a interface gerada pelo Qt Designer
    setupUI();  // Configura os botões e rótulos
    gameLogic = new GameLogic();  // Inicializa a lógica do jogo
}

// Destrutor que libera a memória alocada
MainWindow::~MainWindow()
{
    delete ui;
    delete gameLogic;
}

// Configura os elementos da interface gráfica
void MainWindow::setupUI()
{
    startButton = new QPushButton("Iniciar Jogo", this);  // Botão para iniciar o jogo
    startButton->setGeometry(QRect(QPoint(10, 10), QSize(120, 30)));  // Define a posição do botão
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);  // Conecta o botão ao slot startGame

    resetButton = new QPushButton("Resetar Jogo", this);  // Botão para resetar o jogo
    resetButton->setGeometry(QRect(QPoint(150, 10), QSize(120, 30)));  // Define a posição do botão
    resetButton->hide();  // Esconde o botão de reset até que o jogo seja iniciado
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);  // Conecta o botão ao slot resetGame

    levelLabel = new QLabel("Nível: 1", this);  // Rótulo para exibir o nível
    levelLabel->setGeometry(QRect(QPoint(300, 10), QSize(120, 30)));  // Define a posição do rótulo
    levelLabel->setAlignment(Qt::AlignCenter);  // Centraliza o texto do rótulo
    levelLabel->setStyleSheet("font-size: 16px; font-weight: bold;");  // Define o estilo do rótulo
}

// Atualiza o rótulo de nível com o nível atual
void MainWindow::updateLevelLabel()
{
    levelLabel->setText(QString("Nível: %1").arg(currentLevel));  // Atualiza o texto do rótulo
}

// Configura o próximo nível do jogo
void MainWindow::setupLevel(int level)
{
    qDebug() << "Configurando nível: " << level;

    // Reinicia as flags antes de configurar o novo nível
    gameStarted = true;
    gameWon = false;
    isMoving = false;

    // Configura o nível na lógica do jogo
    gameLogic->setupLevel(level);

    // Atualiza a interface gráfica
    updateUI();
    updateLevelLabel();
}

// Inicia o jogo no nível atual
void MainWindow::startGame()
{
    gameStarted = true;
    gameWon = false;
    startButton->hide();  // Esconde o botão de iniciar
    resetButton->show();  // Exibe o botão de resetar
    setupLevel(currentLevel);  // Configura o nível inicial
}

// Reseta o jogo no nível atual
void MainWindow::resetGame()
{
    gameWon = false;
    setupLevel(currentLevel);  // Reinicia o nível atual
}

// Atualiza a interface gráfica e verifica a condição de vitória
void MainWindow::updateUI()
{
    update();  // Redesenha a interface

    if (gameStarted && !gameWon) {
        QTimer::singleShot(100, this, [this]() {
            if (gameLogic->checkWinCondition()) {  // Verifica se o jogador venceu
                gameWon = true;
                QMessageBox::information(this, "Vitória", "Parabéns, você passou para o próximo nível!");

                // Avança para o próximo nível
                currentLevel++;

                // Reinicia para o nível 1 após o nível 6
                if (currentLevel > 6) {
                    currentLevel = 1;
                }

                setupLevel(currentLevel);  // Configura o próximo nível
            }
        });
    }
}

// Lida com os cliques do mouse na interface
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (!gameStarted || gameWon || isMoving) return;  // Ignora cliques se o jogo não estiver ativo

    int clickedTubeIndex = -1;

    // Verifica em qual tubo o usuário clicou
    for (int i = 0; i < gameLogic->getTubes().size(); ++i) {
        if (gameLogic->getTubes()[i].rect().contains(event->pos())) {
            clickedTubeIndex = i;
            break;
        }
    }

    // Se um tubo foi clicado, tenta mover ou selecionar a bola
    if (clickedTubeIndex != -1) {
        if (gameLogic->getSelectedBall()) {  // Se há uma bola selecionada
            if (gameLogic->moveBall(gameLogic->getSelectedTubeIndex(), clickedTubeIndex)) {  // Move a bola para o tubo clicado
                isMoving = true;
                isMoving = false;
                updateUI();  // Atualiza a interface após o movimento
            } else {
                qDebug() << "Não é possível mover a bola. A cor do topo ou a capacidade do tubo não permite.";
            }
        } else {
            gameLogic->selectBall(clickedTubeIndex);  // Seleciona a bola no topo do tubo clicado
            gameLogic->setSelectedTubeIndex(clickedTubeIndex);  // Define o tubo selecionado
            qDebug() << "Bola selecionada. Cor:" << gameLogic->getSelectedBall()->getColor();
        }
    }
}

// Evento de desenho da interface gráfica
void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    // Desenha todos os tubos e suas bolas
    for (const Tube &tube : gameLogic->getTubes()) {
        tube.draw(painter);
    }
}
