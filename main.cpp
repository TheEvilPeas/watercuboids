#include "unittests.h"
#include "mainwindow.h"

#include <QApplication>

using namespace std;


/**
 * @brief Основная функция приложения.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения приложения.
 */
int main(int argc, char *argv[]) {
    unitTests();
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
