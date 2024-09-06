#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "gamelogic.h"

// Classe da janela principal que gerencia a interface gráfica do jogo
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Construtor e destrutor
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots para tratar eventos de botão
    void startGame();  // Inicia o jogo
    void resetGame();  // Reinicia o jogo
    void setupLevel(int level);  // Configura o nível

protected:
    // Funções que tratam eventos da interface
    void paintEvent(QPaintEvent *event) override;  // Desenha a interface
    void mousePressEvent(QMouseEvent *event) override;  // Lida com cliques do mouse

private:
    // Atualiza a interface do usuário
    void updateUI();
    void updateLevelLabel();
    void setupUI();

    Ui::MainWindow *ui;  // Interface gerada pelo Qt Designer
    QPushButton *startButton;  // Botão para iniciar o jogo
    QPushButton *resetButton;  // Botão para resetar o jogo
    QLabel *levelLabel;  // Rótulo que exibe o nível atual
    GameLogic *gameLogic;  // Lógica do jogo
    bool gameStarted;  // Flag para indicar se o jogo começou
    bool gameWon;  // Flag para indicar se o jogador venceu
    bool isMoving;  // Flag para controlar a movimentação das bolas

    int currentLevel;  // Nível atual do jogo
};

#endif // MAINWINDOW_H
