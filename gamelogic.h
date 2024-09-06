#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QVector>
#include "ball.h"
#include "tube.h"

// Classe que gerencia a lógica do jogo
class GameLogic {
public:
    // Construtor que inicializa o jogo em um nível específico
    GameLogic(int level = 1);

    // Configura o nível do jogo (número de tubos e bolas)
    void setupLevel(int level);

    // Verifica se o jogador venceu o jogo
    bool checkWinCondition() const;

    // Move uma bola de um tubo para outro
    bool moveBall(int fromTubeIndex, int toTubeIndex);

    // Retorna os tubos atuais no jogo
    QVector<Tube> getTubes() const;

    // Retorna a bola selecionada atualmente
    Ball* getSelectedBall() const;

    // Seleciona a bola do topo de um tubo
    void selectBall(int tubeIndex);

    // Retorna o índice do tubo selecionado
    int getSelectedTubeIndex() const;

    // Define o índice do tubo selecionado
    void setSelectedTubeIndex(int tubeIndex);

private:
    QVector<Tube> tubes;  // Vetor de tubos
    QVector<Ball> balls;  // Vetor de bolas
    Ball* selectedBall;  // Ponteiro para a bola selecionada
    int selectedTubeIndex;  // Índice do tubo selecionado
    int currentLevel;  // Nível atual do jogo
};

#endif // GAMELOGIC_H
