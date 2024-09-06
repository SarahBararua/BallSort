#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Cria uma instância de QApplication, que é necessária para qualquer aplicação Qt
    QApplication app(argc, argv);

    // Cria e exibe a janela principal do jogo
    MainWindow mainWindow;
    mainWindow.show();

    // Executa o loop de eventos da aplicação
    return app.exec();
}
