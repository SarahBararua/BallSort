#ifndef BALL_H
#define BALL_H

#include <QColor>
#include <QVector>
#include <QPainter>  // Necessário para desenhar as bolas

// Classe Ball que representa uma bola no jogo
class Ball {
public:
    // Construtores: um que inicializa a bola com uma cor, e outro que inicializa com a cor preta
    Ball(const QColor &color);
    Ball();

    // Retorna a cor da bola
    QColor getColor() const;

    // Método para desenhar a bola em uma posição específica da interface
    void draw(QPainter &painter, const QRect &rect) const;

    // Cria um conjunto de bolas, uma por cor, embaralhadas
    static QVector<Ball> createBalls(int numColors);

private:
    // A cor da bola
    QColor m_color;
};

#endif // BALL_H
