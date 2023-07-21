#ifndef SOLVERTHREAD_H
#define SOLVERTHREAD_H

#include <QThread>
#include "watervolumesolver.h"

/**
 * @brief Класс SolverThread представляет поток для выполнения вычислений.
 */
class SolverThread : public QThread {
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса SolverThread.
     * @param rows Количество строк в матрице.
     * @param cols Количество столбцов в матрице.
     * @param matrix Матрица с входными данными.
     */
    SolverThread(int rows, int cols, const vector<vector<int>>& matrix);

    /**
     * @brief Метод, выполняющий вычисления в потоке.
     * Этот метод будет вызван при запуске потока.
     */
    void run() override;

signals:
    /**
     * @brief Сигнал, отправляемый по завершению вычислений.
     * @param result Результат вычислений.
     * @param workingMatrix Матрица с промежуточными данными после вычислений.
     */
    void calculationComplete(ll result, const vector<vector<int>>& workingMatrix);

private:
    int rows; /**< Количество строк в матрице. */
    int cols; /**< Количество столбцов в матрице. */
    vector<vector<int>> matrix; /**< Матрица с входными данными. */
};

#endif // SOLVERTHREAD_H
