#ifndef TUBE_H
#define TUBE_H

#include <QRect>
#include <QVector>
#include <QPainter>
#include "ball.h"

// Classe Tube que representa um tubo que armazena bolas
class Tube {
public:
    // Construtor que inicializa o tubo com uma posição e tamanho
    Tube(const QRect &rect);

    // Define o número máximo de bolas por tubo
    static const int MAX_BALLS_PER_TUBE = 4;

    // Métodos para adicionar e remover bolas do tubo
    void addBall(const Ball &ball);
    void removeTopBall();

    // Retorna a bola no topo do tubo
    Ball topBall() const;

    // Verifica se o tubo está vazio
    bool isEmpty() const;

    // Retorna todas as bolas no tubo
    QVector<Ball> getBalls() const;

    // Retorna a região ocupada pelo tubo na interface gráfica
    QRect rect() const;

    // Verifica se o tubo pode receber uma nova bola (checa cor e limite de bolas)
    bool canReceiveBall(const Ball &ball) const;

    // Verifica se todas as bolas no tubo têm a mesma cor
    bool allBallsSameColor() const;

    // Desenha o tubo e as bolas dentro dele
    void draw(QPainter &painter) const;

    // Cria tubos com bolas distribuídas aleatoriamente entre eles
    static QVector<Tube> createTubes(int numTubes, QVector<Ball>& balls);

private:
    QRect m_rect;  // A posição e o tamanho do tubo na interface gráfica
    QVector<Ball> m_balls;  // Vetor de bolas no tubo
};

#endif // TUBE_H
