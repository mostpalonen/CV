#include "mainwindow.h"

#include <QApplication>

MainWindow * game;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow * game = new MainWindow();
    game->QMainWindow::show();
    return app.exec();
}
