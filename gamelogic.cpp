#include "gamelogic.h"

// Construtor que inicializa a lógica do jogo com o nível especificado
GameLogic::GameLogic(int level)
    : selectedBall(nullptr)  // Nenhuma bola selecionada inicialmente
    , selectedTubeIndex(-1)  // Nenhum tubo selecionado inicialmente
    , currentLevel(level)  // Define o nível atual
{
    setupLevel(level);  // Configura o nível ao iniciar o jogo
}

// Configura o nível de jogo com base no número de tubos e cores
void GameLogic::setupLevel(int level)
{
    tubes.clear();  // Limpa os tubos
    balls.clear();  // Limpa as bolas

    int numTubes = 3;  // Número padrão de tubos
    int numColors = 2;  // Número padrão de cores

    // Ajusta o número de tubos e cores com base no nível
    if (level == 3 || level == 4) {
        numTubes = 5;
        numColors = 3;
    } else if (level >= 5) {
        numTubes = 6;
        numColors = 4;
    }

    // Cria as bolas e os tubos com base no nível
    balls = Ball::createBalls(numColors);
    tubes = Tube::createTubes(numTubes, balls);
}

// Verifica se o jogador venceu, ou seja, se todos os tubos têm bolas da mesma cor
bool GameLogic::checkWinCondition() const
{
    for (const Tube &tube : tubes) {
        if (!tube.isEmpty() && (!tube.allBallsSameColor() || tube.getBalls().size() != Tube::MAX_BALLS_PER_TUBE)) {
            return false;
        }
    }
    return true;
}

// Move uma bola de um tubo para outro, se possível
bool GameLogic::moveBall(int fromTubeIndex, int toTubeIndex)
{
    // Verifica se os índices dos tubos são válidos
    if (fromTubeIndex < 0 || toTubeIndex < 0 || fromTubeIndex >= tubes.size() || toTubeIndex >= tubes.size()) {
        return false;
    }

    Tube &fromTube = tubes[fromTubeIndex];  // Tubo de origem
    Tube &toTube = tubes[toTubeIndex];  // Tubo de destino

    // Verifica se a bola pode ser movida para o tubo de destino
    if (selectedBall && toTube.canReceiveBall(*selectedBall)) {
        toTube.addBall(*selectedBall);  // Adiciona a bola ao tubo de destino
        fromTube.removeTopBall();  // Remove a bola do tubo de origem
        delete selectedBall;  // Libera a memória da bola selecionada
        selectedBall = nullptr;  // Nenhuma bola está selecionada agora
        return true;
    }

    return false;
}

// Retorna os tubos atuais do jogo
QVector<Tube> GameLogic::getTubes() const {
    return tubes;
}

// Retorna a bola selecionada atualmente
Ball* GameLogic::getSelectedBall() const {
    return selectedBall;
}

// Seleciona a bola no topo do tubo especificado
void GameLogic::selectBall(int tubeIndex)
{
    if (tubeIndex >= 0 && tubeIndex < tubes.size() && !tubes[tubeIndex].isEmpty()) {
        selectedBall = new Ball(tubes[tubeIndex].topBall());  // Copia a bola do topo
        selectedTubeIndex = tubeIndex;  // Define o tubo como selecionado
    }
}

// Retorna o índice do tubo selecionado
int GameLogic::getSelectedTubeIndex() const {
    return selectedTubeIndex;
}

// Define o índice do tubo selecionado
void GameLogic::setSelectedTubeIndex(int tubeIndex) {
    selectedTubeIndex = tubeIndex;
}
