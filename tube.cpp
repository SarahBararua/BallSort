#include "tube.h"

// Construtor que define a posição e o tamanho do tubo
Tube::Tube(const QRect &rect) : m_rect(rect) {}

// Adiciona uma bola ao tubo, se ainda houver espaço
void Tube::addBall(const Ball &ball) {
    if (m_balls.size() < MAX_BALLS_PER_TUBE) {
        m_balls.push_back(ball);
    }
}

// Remove a bola no topo do tubo
void Tube::removeTopBall() {
    if (!m_balls.isEmpty()) {
        m_balls.pop_back();
    }
}

// Retorna a bola no topo do tubo, sem removê-la
Ball Tube::topBall() const {
    return m_balls.last();
}

// Verifica se o tubo está vazio
bool Tube::isEmpty() const {
    return m_balls.isEmpty();
}

// Retorna todas as bolas do tubo
QVector<Ball> Tube::getBalls() const {
    return m_balls;
}

// Retorna a posição e o tamanho do tubo na interface gráfica
QRect Tube::rect() const {
    return m_rect;
}

// Verifica se o tubo pode receber uma nova bola, baseado na cor e no limite de bolas
bool Tube::canReceiveBall(const Ball &ball) const {
    return isEmpty() || (topBall().getColor() == ball.getColor() && m_balls.size() < MAX_BALLS_PER_TUBE);
}

// Verifica se todas as bolas no tubo têm a mesma cor
bool Tube::allBallsSameColor() const {
    if (m_balls.isEmpty()) return false;

    QColor color = m_balls.first().getColor();
    for (const Ball &ball : m_balls) {
        if (ball.getColor() != color) {
            return false;
        }
    }
    return true;
}

// Desenha o tubo e as bolas dentro dele na interface gráfica
void Tube::draw(QPainter &painter) const {
    painter.setBrush(Qt::gray);  // Define a cor do tubo
    painter.drawRect(m_rect);  // Desenha o tubo como um retângulo

    if (!m_balls.isEmpty()) {
        // Define o diâmetro da bola e a posição inicial
        int ballDiameter = m_rect.width() - 20;
        int ballY = m_rect.bottom() - ballDiameter - 10;

        // Desenha cada bola dentro do tubo
        for (const Ball &ball : m_balls) {
            QRect ballRect(m_rect.left() + 10, ballY, ballDiameter, ballDiameter);
            ball.draw(painter, ballRect);
            ballY -= (ballDiameter + 10);  // Ajusta a posição da próxima bola
        }
    }
}

// Cria tubos e distribui as bolas entre eles
QVector<Tube> Tube::createTubes(int numTubes, QVector<Ball>& balls) {
    QVector<Tube> tubes;

    // Cria tubos com espaçamento fixo
    for (int i = 0; i < numTubes; ++i) {
        QRect tubeRect(i * 100, 50, 80, 300);  // Define a posição de cada tubo
        tubes.push_back(Tube(tubeRect));  // Adiciona o tubo ao vetor
    }

    // Distribui as bolas entre os tubos
    int tubeIndex = 0;
    for (Ball &ball : balls) {
        while (tubeIndex < numTubes && tubes[tubeIndex].getBalls().size() >= MAX_BALLS_PER_TUBE) {
            tubeIndex++;  // Avança para o próximo tubo se o atual estiver cheio
        }
        if (tubeIndex < numTubes) {
            tubes[tubeIndex].addBall(ball);  // Adiciona a bola ao tubo
        }
    }

    return tubes;
}
