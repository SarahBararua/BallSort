#include "ball.h"
#include <random>  // Necessário para embaralhar as bolas aleatoriamente

// Construtor que inicializa a bola com a cor fornecida
Ball::Ball(const QColor &color) : m_color(color) {}

// Construtor padrão que inicializa a bola com a cor preta
Ball::Ball() : m_color(Qt::black) {}

// Retorna a cor da bola
QColor Ball::getColor() const {
    return m_color;
}

// Cria bolas baseadas no número de cores e as embaralha
QVector<Ball> Ball::createBalls(int numColors) {
    QVector<Ball> balls;  // Vetor de bolas
    QVector<QColor> colors = {Qt::red, Qt::blue, Qt::green, Qt::yellow};  // Cores das bolas
    const int numBallsPerColor = 4;  // Número de bolas por cor

    // Cria 4 bolas de cada cor
    for (int i = 0; i < numColors; ++i) {
        for (int j = 0; j < numBallsPerColor; ++j) {
            balls.push_back(Ball(colors[i]));  // Adiciona bolas ao vetor
        }
    }

    // Embaralha as bolas para criar uma ordem aleatória
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(balls.begin(), balls.end(), g);

    return balls;  // Retorna o vetor de bolas
}

// Desenha a bola na interface gráfica, usando a cor definida
void Ball::draw(QPainter &painter, const QRect &rect) const {
    painter.setBrush(m_color);  // Define a cor da bola
    painter.drawEllipse(rect);  // Desenha a bola como um círculo
}
